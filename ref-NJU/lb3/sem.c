#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "sem.h"

FieldList* head = NULL;
char errorMessage[100] = {0};

// 初始化符号表
void initSymTab() {
    head = newField();
}

int lastErrorLine = 0;  // 上次报错的行号

// 输出错误信息
void Error(const char* errorType, int line, const char* message) {
    if (line > lastErrorLine) {
        printf("Error type %s at Line %d: %s\n", errorType, line, message);
        lastErrorLine = line;
    }
}

// 检查是否可以向符号表中添加新符号
int checkSym(FieldList* field) {
    FieldList* p = head->tail;
    while (p) {
        if (!strcmp(p->name, field->name))
            return 0;  // 已存在
        p = p->tail;
    }
    return 1;  // 不存在，可以添加
}

// 向符号表添加新符号
void addSym(FieldList* field) {
    field->tail = head->tail;
    head->tail = field;
}

// 查找符号
FieldList* findSym(char* name) {
    FieldList* p = head->tail;
    while (p) {
        if (!strcmp(p->name, name))
            return p;
        p = p->tail;
    }
    return NULL;
}

// 打印符号表
void printSymTab() {
    FieldList* p = head->tail;
    while (p) {
        printf("Symbol: %s\n", p->name);
        p = p->tail;
    }
}

// 创建新类型
Type* newType(TypeKind kind, int num, ...) {
    Type* t = (Type*)malloc(sizeof(Type));
    t->kind = kind;
    va_list args;
    va_start(args, num);
    switch (kind) {
        case BASIC_TYPE:
            t->u.basic = va_arg(args, BasicType);
            break;
        case ARRAY_TYPE:
            t->u.array.size = va_arg(args, int);
            t->u.array.elem = va_arg(args, Type*);
            break;
        case STRUCT_TYPE:
            // 结构体类型处理
            break;
    }
    va_end(args);
    return t;
}

// 创建新符号
FieldList* newField() {
    FieldList* f = (FieldList*)malloc(sizeof(FieldList));
    f->name = (char*)malloc(35 * sizeof(char));
    f->type = NULL;
    f->tail = NULL;
    return f;
}

// 释放字段资源
void freeField(FieldList* field) {
    free(field->name);
    FieldList* next;
    while (field->tail) {
        next = field->tail;
        freeField(next);
        field->tail = next->tail;
    }
    free(field);
}

// 外部定义处理
// ExtDef -> Specifier ExtDecList SEMI
//         | Specifier SEMI
//         | Specifier FunDec CompSt
void ExtDef(Node* root) {
    Type* type = Specifier(root->child);
    if (!strcmp(root->child->next->type, "ExtDecList")) {
        ExtDecList(root->child->next, type);
    }
    return ;
}

// 类型说明符分析
Type* Specifier(Node* root) {
    if (!strcmp(root->child->type, "TYPE")) {
        if (!strcmp(root->child->val, "int"))
            return newType(BASIC_TYPE, 1, INT_TYPE);
        else if (!strcmp(root->child->val, "float"))
            return newType(BASIC_TYPE, 1, FLOAT_TYPE);
    }
    // 结构体和数组类型处理
    return NULL;
}

// 外部声明列表处理
// ExtDecList -> VarDec
//             | VarDec COMMA ExtDecList
void ExtDecList(Node* root, Type* type) {
    Node* p = root;
    while (p) {
        VarDec(p->child, type);
        if (p->child->next)
            p = p->child->next->next;
        else
            break;
    }
}

// 变量声明处理
// VarDec -> ID
//         | VarDec LB INT RB
void VarDec(Node* root, Type* type) {
    // 迭代访问到最深层的 ID 节点，以获取变量名
    Node* idNode = root;
    while (idNode->child) {
        idNode = idNode->child;
    }

    // 创建新的字段，用于存储变量名和类型
    FieldList* field = newField();
    strcpy(field->name, idNode->val);  // 拷贝变量名

    // 判断是基本类型还是数组类型
    if (!strcmp(root->child->type, "ID")) {
        // 基本类型变量
        field->type = type;
    } else {
        // 数组类型
        Node* varDecNode = root->child;
        Type* currentType = type;
        while (varDecNode->next) {
            // 解析数组大小，并创建数组类型
            int size = atoi(varDecNode->next->next->val);  // 获取数组大小
            Type* arrayType = newType(ARRAY_TYPE, 2, size, currentType);
            currentType = arrayType;
            varDecNode = varDecNode->child;
        }
        field->type = currentType;  // 最终的数组类型
    }

/*-----------------------错误类型3：变量出现重复定义或变量与前面定义过的结构体名字重复。------------------------*/
    // 检查变量是否已在符号表中定义
    if (!checkSym(field)) {
        // 如果已定义，报错并释放资源
        char errorMessage[128];
        sprintf(errorMessage, "Redefined variable \"%s\".", field->name);
        Error("3", root->line, errorMessage);
        freeField(field);  // 释放字段资源
    } else {
        // 如果未定义，添加到符号表
        addSym(field);
    }
}


// 处理定义
// Def -> Specifier DecList SEMI
void Def(Node* root) {
    Type* type = Specifier(root->child);  // 获取类型
    DecList(root->child->next, type);  // 处理声明列表
}

// 处理声明列表
// DecList -> Dec
//          | Dec COMMA DecList
void DecList(Node* root, Type* type) {
    Node* p = root;
    while (p) {
        Dec(p->child, type);
        if (p->child->next)  // 如果后面还有声明，继续处理
            p = p->child->next->next;
        else break;
    }
}

// 处理单个声明
// Dec -> VarDec
//      | VarDec ASSIGNOP Exp
void Dec(Node* root, Type* type) {
    VarDec(root->child, type);
    // if (root->child->next) {  // 如果有初始化表达式
    //     Type* expType = Exp(root->child->next->next);  // 获取表达式的类型
    //     if (type->kind == BASIC && expType->kind == BASIC && type->u.basic == expType->u.basic) {
    //         // 类型匹配，合法的赋值
    //         printf("Initialization valid\n");
    //     } else {
    //         printf("Error: Type mismatch during initialization\n");
    //     }
    // }
}

// 表达式类型分析
// Exp -> Exp ASSIGNOP Exp
//      | Exp AND Exp
//      | Exp OR Exp
//      | Exp RELOP Exp
//      | Exp PLUS Exp
//      | Exp MINUS Exp
//      | Exp STAR Exp
//      | Exp DIV Exp
//      | LP Exp RP
//      | MINUS Exp
//      | NOT Exp
//      | ID LP Args RP
//      | ID LP RP
//      | Exp LB Exp RB
//      | Exp DOT ID
//      | ID
//      | INT
//      | FLOAT

Type* Exp(Node* root) {
    // 进入表达式解析
    Node* p = root->child;
    if (!strcmp(p->type, "INT")) {
        // 处理整数常量
        return newType(BASIC_TYPE, 1, INT_TYPE);
    } else if (!strcmp(p->type, "FLOAT")) {
        // 处理浮点数常量
        return newType(BASIC_TYPE, 1, FLOAT_TYPE);
    } else if (!strcmp(p->type, "ID")) {
        // 处理标识符
        FieldList* sym = findSym(p->val);
        if (!sym) {
/*------------------------错误类型1：变量在使用时未经定义。---------------------------------------------------------*/
            sprintf(errorMessage, "Undefined variable '%s'.", p->val);
            Error("1", p->line, errorMessage);
            return NULL;
        }
        return sym->type;

    } else if (!strcmp(p->type, "Exp")) {
        // 处理嵌套表达式
        if (p->next && !strcmp(p->next->type, "LB")) {
            // 数组访问
            Type* arrayType = Exp(p);
            Type* indexType = Exp(p->next->next);
            if (!arrayType || !indexType) return NULL;

            if (arrayType->kind != ARRAY_TYPE) {
/*------------------------错误类型10：对非数组型变量使用数组访问操作符。---------------------------------------------------------*/

                sprintf(errorMessage, "\"%s\" is not an array.", p->child->val);
                Error("10", p->line, errorMessage);
                return NULL;
            }
            if (indexType->kind != BASIC_TYPE || indexType->u.basic != INT_TYPE) {
/*------------------------错误类型12：数组访问操作符“[…]”中出现非整数（例如a[1.5]）---------------------------------------------------------*/

                sprintf(errorMessage, "Array index is not an integer.");
                Error("12", p->line, errorMessage);
                return NULL;
            }
            return arrayType->u.array.elem;  // 返回数组元素的类型
        } else if (p->next && !strcmp(p->next->type, "DOT")) {
            // 结构体成员访问
            Type* structType = Exp(p);
            if (!structType || structType->kind != STRUCT_TYPE) {
/*------------------------错误类型13：对非结构体类型变量使用“.”操作符。---------------------------------------------------------*/

                sprintf(errorMessage, "\"%s\" is not a struct.", p->child->val);
                Error("13", p->line, errorMessage);
                return NULL;
            }
            
        } 
        else if (p->next) {
            Type* t1 = Exp(p);
            Type* t2 = Exp(p->next->next);
            if (!t1 || !t2) return NULL;  // 如果任一操作数类型未知，则无法进行类型检查

            // 赋值运算符的特殊处理
            if (!strcmp(p->next->type, "ASSIGNOP")) {
                if (!strcmp(p->child->type, "ID")) {
                    // 只有标识符可以作为赋值的左侧
                    if (t1->kind == BASIC_TYPE && t2->kind == BASIC_TYPE && t1->u.basic != t2->u.basic) {

/*------------------------错误类型5：赋值号两边的表达式类型不匹配。---------------------------------------------------------*/

                        sprintf(errorMessage, "Type mismatched for assignment.");
                        Error("5", p->line, errorMessage);
                        return NULL;
                    }
                    return t1;  // 赋值表达式的类型是左侧变量的类型
                } else {//不是ID

/*------------------------错误类型6：赋值号左边出现一个只有右值的表达式。---------------------------------------------------------*/
             
                    sprintf(errorMessage, "The left-hand side of an assignment must be a variable.");
                    Error("6", p->line, errorMessage);
                    return NULL;
                }
            } else {
                // 处理其他二元运算符，除了赋值运算
                if (t1->kind == BASIC_TYPE && t2->kind == BASIC_TYPE && t1->u.basic != t2->u.basic) {

/*------------------------错误类型7：操作数类型不匹配或操作数类型与操作符不匹配---------------------------------------------------------*/            
                    
                    sprintf(errorMessage, "Type mismatched for operands.");
                    Error("7", p->line, errorMessage);
                    return NULL;
                }
                return t1;  // 返回左侧操作数的类型
            }
        }
    }
    return NULL;  // 未知或不支持的表达式类型
}


// 递归进行语义分析
void analyze(Node* root) {
    if (!root) return;
    if (!strcmp(root->type, "ExtDef")) {
        ExtDef(root);
    } else if (!strcmp(root->type, "Def")) {
        Def(root);
    } else if (!strcmp(root->type, "Exp")) {
        Exp(root);
    }

    analyze(root->child);  // 递归处理子节点
    analyze(root->next);  // 递归处理兄弟节点
}

