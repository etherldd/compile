#ifndef SEMANTIC_H
#define SEMANTIC_H

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
void yyerror(const char* s);

typedef struct node {
    int T;                 //是否为终结符
    char* type;               //类型，对于终结符和非终结符有不同的意义
    int line;               //涉及到第一个终结符的行号
    char*  val;              //值
    struct node* next;     //右兄弟指针
    struct node* child;    //最左的儿子指针
}Node;


Node* CreateTerminalNode(int terminal, char* type, int line,char* val);
Node* CreateUnterminalNode(char* type, int line, Node* firstChild);
void AddChild(Node* parent, Node* childToAdd);
void Error(const char*, int,const char*);

// 类型分类枚举。
typedef enum { BASIC_TYPE, ARRAY_TYPE, STRUCT_TYPE } TypeKind;
typedef enum { INT_TYPE, FLOAT_TYPE } BasicType;

// 类型定义前置声明。
typedef struct Type_ Type;
typedef struct FieldList_ FieldList;

// 类型结构定义。
struct Type_ {
    TypeKind kind; // 类型种类：基本、数组、结构体。
    union {
        BasicType basic;        // 基本类型。
        struct {                // 数组类型。
            Type* elem; 
            int size;
        } array;
        FieldList* structure;   // 结构体类型。
    } u;
};

// 字段或符号结构定义。
struct FieldList_ {
    char* name;        // 字段或符号名称。
    Type* type;        // 类型。
    FieldList* tail;   // 链表中的下一个元素。
};

// 符号表定义
void initSymTab();                         // 初始化符号表。
int checkSym(FieldList* field);            // 检查符号是否存在。
void addSym(FieldList* field);             // 添加符号。
FieldList* findSym(char* name);            // 查找符号。
void printSymTab();                        // 显示符号表。
Type* newType(TypeKind kind, int num, ...);// 创建新类型。
FieldList* newField();                     // 创建新字段。
void freeField(FieldList* field);          // 释放字段资源。

//语义分析检测
void ExtDef(Node* root);                   // 分析外部定义。
Type* Specifier(Node* root);               // 分析类型说明符。
void ExtDecList(Node* root, Type* type);   // 分析外部声明列表。
void VarDec(Node* root, Type* type);       // 分析变量声明。
void Def(Node* root);                      // 分析定义。
void DecList(Node* root, Type* type);      // 分析声明列表。
void Dec(Node* root, Type* type);          // 分析声明。
Type* Exp(Node* root);                     // 分析表达式。
void analyze(Node* root);                  // 执行语义分析。

#endif