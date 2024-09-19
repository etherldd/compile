#ifndef SANALYSIS_H
#define SANALYSIS_H

//#define DEBUG

#include "list.h"
#include "stree.h"
#include "structList.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>

int DefListAnalysis(Snode* node, int isFromStruct, int isNotDetectStruct);
void CompStAnalysis(Snode* node, TYPE_CMM* retType);
TYPE_CMM* getTypeOfSpecifier(Snode* node, int detectStructInsideDuplicateName);
TYPE_CMM* getTypeOfVarDec(Snode* node, TYPE_CMM* outer, char** pname);
TYPE_CMM* ExprAnalysis(Snode* n);


Snode**           ExtDefs;
unsigned int      ExtDefsNum;
LIST*             symbolList;
structLIST*       structList;
funcLIST*         funcDefList;
unsigned int      globalCountForNonNameStruct;
TYPE_CMM* generateNonNameStruct() {
    char* name = (char*)malloc(sizeof(char) * 32);
    sprintf(name, "%d", globalCountForNonNameStruct);
    globalCountForNonNameStruct++;
    TYPE_CMM* ret = typeOfStruct(name);
    free(name);
    return ret;
}

/*for debuging*/
void ExtDefsPrint() {
    printf("ExtDefs(%d): ", ExtDefsNum);
    for (int i = 0; i < ExtDefsNum; i++) {
        printf("%p ", ExtDefs[i]);
    }
    printf("\n");
}

/*build ExtDefs recusively*/
void getExtDefsHelper(Snode* cur, unsigned int size) {
    if (cur == NULL) {
        ExtDefs = (Snode**)malloc(sizeof(Snode*) * size);
        ExtDefsNum = size;
        return;
    }
    getExtDefsHelper(cur->childs[1], size + 1);
    ExtDefs[size] = cur->childs[0];
}

int DecListAnalysis2(TYPE_CMM* t, Snode* node, StructNodeList* newInsert) { //if have error, return 1
    //DecList : Dec | Dec COMMA DecList
    //                Dec -> VarDec | VarDec ASSIGNOP Exp 
    int ret = 0;
    char* curName;
    TYPE_CMM* curT = getTypeOfVarDec(node->childs[0]->childs[0], t, &curName);
    TYPE_CMM* isHave = StructNodeListGetTypeIfHave(newInsert, curName);
    if (isHave) {
        ret = 0;
        printf("Error type 15 at Line %d: 结构体中域名重复定义:%s.\n", node->childs[0]->line, curName);
    } else {
        StructNodeListInsertValue(newInsert, curName, curT);
    }
    if (node->childs_num > 1) {
        if (ret) {
            DecListAnalysis2(t, node->childs[2], newInsert);
        } else {
            ret = DecListAnalysis2(t, node->childs[2], newInsert);
        }
    } 
    return ret;
}

int DefListAnalysis2(Snode* node, StructNodeList* newInsert) {
    //DefList -> Def DefList | e
    //             \ 
    //              -> Specifier DecList SEMI
    if (node == NULL) {
        return 0;
    }
    //Def DefList
    int isCurError = 0;
    //analysis Def
    TYPE_CMM* curType = getTypeOfSpecifier(node->childs[0]->childs[0], 0);
    isCurError = DecListAnalysis2(curType, node->childs[0]->childs[1], newInsert);
    if (isCurError == 0) {
        return node->childs[1] == NULL ? 0 : DefListAnalysis2(node->childs[1], newInsert);
    }
    DefListAnalysis2(node->childs[1], newInsert);
    return 1;
}
/*add struct Elem to StructNodeList and detect the error which might happen*/
int DefListAddElemToStructNode(Snode* node, StructNodeList* newInsert) {
    return DefListAnalysis2(node, newInsert);
}

/*get TYPE_CMM through Specifier node*/
TYPE_CMM* getTypeOfSpecifier(Snode* node, int notDetectStruct) {
    //Specifier : TYPE | StructSpecifier
    if (node->childs[0]->sname == tokens[_TYPE]) {
        //TYPE
        if (node->childs[0]->sval[0] == 'i') {
            //TYPE of int
            return typeOfINT();
        } else {
            //TYPE of float
            return typeOfFLOAT();
        }
    } else {
        //StructSpecifier
        if (node->childs[0]->childs_num == 2) {
            //STRUCT Tag
            char* curTagId = node->childs[0]->childs[1]->childs[0]->sval;
            StructNodeList*  curRet = structListGetNodeIfHave(structList, curTagId);
            if (!curRet) {
                printf("Error type 17 at Line %d: 直接使用未定义过的结构体来定义变量:%s.\n", 
                            node->childs[0]->childs[1]->childs[0]->line, curTagId);
                return NULL;
            }
            return typeOfStruct(curTagId);
        } else {
            //STRUCT OptTag LC DefList RC
            if (notDetectStruct) {
                char* curTagId = node->childs[0]->childs[1] == NULL ? "NonName" : node->childs[0]->childs[1]->childs[0]->sval;
                return typeOfStruct(curTagId);
            } else {
                char* curTagId = NULL;
                StructNodeList*  newInsert = NULL;
                if (node->childs[0]->childs[1] == NULL) {
                    //OptTag == NULL
                    TYPE_CMM* nonNameStructType = generateNonNameStruct();
                    curTagId = nonNameStructType->structName;
                } else {
                    curTagId = node->childs[0]->childs[1]->childs[0]->sval;
                }
                newInsert = structListGetNodeIfHave(structList, curTagId);
                if (newInsert) {
                    printf("Error type 16 at Line %d: 结构体的名字与前面定义过的结构体重复:%s.\n", 
                            node->childs[0]->childs[1]->childs[0]->line, curTagId);
                    return NULL;
                }
                newInsert = StructNodeListInit(curTagId);
                int isError = DefListAddElemToStructNode(node->childs[0]->childs[3], newInsert);
                TYPE_CMM* isHaveInSym = listGetTypeIfHave(symbolList, curTagId);
                if (isHaveInSym) {
                    printf("Error type 16 at Line %d: 结构体的名字与前面定义过的变量的名字重复:%s.\n", 
                                            node->childs[0]->childs[1]->childs[0]->line, curTagId);
                    return NULL;
                }
                if (isError) {
                    return NULL;
                }
                structListInsertNode(structList, newInsert);
                return typeOfStruct(curTagId);
            }
        }
        
    }
}

void ArgsTypesGetAndAnalysis(Snode* n, unsigned int cur, TYPE_CMM*** res, int* num) {
    //Args : Exp COMMA Args | Exp
    TYPE_CMM* curT = ExprAnalysis(n->childs[0]);
    if (n->childs_num == 1) {
        *num = cur + 1;
        *res = (TYPE_CMM**)malloc(sizeof(TYPE_CMM*) * (cur + 1));
        (*res)[cur] = curT;
        return;
    }
    ArgsTypesGetAndAnalysis(n->childs[2], cur + 1, res, num);
    (*res)[cur] = curT;
}



TYPE_CMM* ExprAnalysis(Snode* n) {
    if (n->childs[0]->sname == tokens[_INT]) {
        //INT
        return typeOfINT();
    } else if (n->childs[0]->sname == tokens[_FLOAT]) {
        //FLOAT
        return typeOfFLOAT();
    } else if (n->childs[0]->sname == tokens[_ID]) {
        if (n->childs_num == 1) {
            //ID
            TYPE_CMM* ret = listGetTypeIfHave(symbolList, n->childs[0]->sval);
            if (ret == NULL) {
                printf("Error type 1 at Line %d: 变量在使用时未经定义:%s.\n", n->childs[0]->line, n->childs[0]->sval);
            }
            return ret;
        } else {
            //ID  LP  RP
            //ID  LP  Args RP
            TYPE_CMM* retsym = listGetTypeIfHave(symbolList, n->childs[0]->sval);
            TYPE_CMM** trueTypes = NULL;
            unsigned int argsNum;
            TYPE_CMM* ret = funcListGetRetTypeIfHave(funcDefList, n->childs[0]->sval, &trueTypes, &argsNum);
            if (retsym != NULL) {
                printf("Error type 11 at Line %d: 对普通变量使用“(…)”或“()”（函数调用）操作符:%s.\n", n->childs[0]->line, n->childs[0]->sval);
                return NULL;
            } else if (ret == NULL) {
                printf("Error type 2 at Line %d: 函数在调用时未经定义:%s.\n", n->childs[0]->line, n->childs[0]->sval);
                return NULL;
            }
            int num = 0;
            TYPE_CMM** res;
            if (n->childs_num == 4) {
                ArgsTypesGetAndAnalysis(n->childs[2], 0, &res, &num);
                //error detected during Exp analysis, so return directly
                for (unsigned int i = 0; i < num; i++) {
                    if (res[i] == NULL) {
                        return NULL;
                    }
                }
            } 
            unsigned int trueNum = argsNum;
            char t1[5], t2[5];
            sprintf(t1, "%d", num);
            sprintf(t2, "%d", trueNum);
            if (num != trueNum) {
                printf("Error type 9 at Line %d: 函数调用时实参与形参的数目为%s(!=%s).\n", n->childs[2]->line, t1, t2);
                return NULL;
            }
            for (unsigned int i = 0; i < num; i++) {
                if (!typeJudgeEquel(res[i], trueTypes[i])) {
                    char* c1 = typeToString(res[i]);
                    char* c2 = typeToString(trueTypes[i]);
                    printf("Error type 9 at Line %d: 函数调用时实参与形参类型不匹配%s(!=%s).\n", n->childs[2]->line, c2, c1);
                    if (strncmp(c1, "Struct", 6) == 0) {
                        free(c1);
                    } 
                    if (strncmp(c2, "Struct", 6) == 0) {
                        free(c2);
                    } 
                    return NULL;
                }
            }
            return ret;
        }
    } else if (n->childs[0]->sname == tokens[_MINUS] || n->childs[0]->sname == tokens[_NOT]) {
        //MINUS Exp
        return ExprAnalysis(n->childs[1]);
    } else if (n->childs[0]->sname == tokens[_LP] && n->childs[2]->sname == tokens[_RP]) {
        //LP   Exp  RP
        return ExprAnalysis(n->childs[1]);
    }
    if (n->childs_num == 3) {
        if (n->childs[0]->sname == nontokens[_Exp] && n->childs[2]->sname == nontokens[_Exp]) {
            TYPE_CMM* t1 = ExprAnalysis(n->childs[0]);
            TYPE_CMM* t3 = ExprAnalysis(n->childs[2]);
            if (t1 == NULL || t3 == NULL) {
                return NULL;
            }
            int       isEqT = typeJudgeEquel(t1, t3);
            if (n->childs[1]->sname == tokens[_ASSIGNOP]) {
                //Exp ASSIGNOP Exp
                if (!isEqT) {
                    char* c1 = typeToString(t1);
                    char* c2 = typeToString(t3);
                    printf("Error type 5 at Line %d: 赋值号两边的表达式类型不匹配(b):(%s vs %s).\n", n->childs[2]->line, c1, c2);
                    if (strncmp(c1, "Struct", 6) == 0) {
                        free(c1);
                    } 
                    if (strncmp(c2, "Struct", 6) == 0) {
                        free(c2);
                    } 
                    return NULL;
                } else {
                    return t1;
                }
            } else {
                if (!isEqT) {
                    char* c1 = typeToString(t1);
                    char* c2 = typeToString(t3);
                    printf("Error type 7 at Line %d: 操作数类型不匹配或操作数类型与操作符不匹配:(%s vs %s).\n", 
                            n->childs[0]->line, c1, c2);
                    if (strncmp(c1, "Struct", 6) == 0) {
                        free(c1);
                    } 
                    if (strncmp(c2, "Struct", 6) == 0) {
                        free(c2);
                    } 
                    return NULL;
                }
                if (t1->isArray || t1->isStruct || t3->isArray || t3->isStruct) {
                    printf("Error type 7 at Line %d: 操作数类型不匹配或操作数类型与操作符不匹配:\n", 
                            n->childs[0]->line);
                    return NULL;
                }
                return t1;
            }
        } else {
            //Exp DOT ID
            TYPE_CMM* t1 = ExprAnalysis(n->childs[0]);
            if (t1 == NULL) {
                return NULL;
            }
            if (!t1->isStruct) {
                printf("Error type 13 at Line %d: 对非结构体型变量使用“.”操作符:\n", n->childs[1]->line);
                return NULL;
            } else {
                StructNodeList* isHaveInStruct = structListGetNodeIfHave(structList, t1->structName);
                if (!isHaveInStruct) {
                    printf("no corresping Struct exist\n");
                    return NULL;
                }
                TYPE_CMM* ret = StructNodeListGetTypeIfHave(isHaveInStruct, n->childs[2]->sval);
                if (!ret) {
                    printf("Error type 14 at Line %d: 访问结构体中未定义过的域:%s\n", n->childs[2]->line, n->childs[2]->sval);
                    return NULL;
                }
                return ret;
            }
        }
    } else {
        //Exp LB Exp RB
        //psn(n);
        TYPE_CMM* t1 = ExprAnalysis(n->childs[0]);
        TYPE_CMM* t3 = ExprAnalysis(n->childs[2]);
        TYPE_CMM* TEMP_INT_TYPE = typeOfINT();
        if (!typeJudgeEquel(t3, TEMP_INT_TYPE)) {
            printf("Error type 12 at Line %d: 数组访问操作符“[…]”中出现非整数:\n", n->childs[2]->line);
            return NULL;
        }
        if (!t1->isArray) {
            printf("Error type 10 at Line %d: 对非数组型变量使用“[…]”（数组访问）操作符:\n", n->childs[0]->line);
            return NULL;
        }
        return t1->ArrayElemType;
    }
    return NULL;
}



int structDetectDefSpecifier(Snode* node) {
    //Specifier -> StructSpecifier -> STRUCT OptTag LC DefList RC
    if (node->childs[0]->childs_num != 2) {
        return DefListAnalysis(node->childs[0]->childs[3], 1, 1);
    }
}

TYPE_CMM* getTypeOfVarDec(Snode* node, TYPE_CMM* outer, char** pname) {
    //VarDec -> VarDec LB INT RB | ID
    if (node->childs_num == 1) {
        if (pname) {
            *pname = node->childs[0]->sval;
        }
        return outer;
    }
    TYPE_CMM* newT = typeArrayOfType(outer, atoi(node->childs[2]->sval));
    return getTypeOfVarDec(node->childs[0], newT, pname);
}

TYPE_CMM* getTypeOfParamDec(Snode* node) {
    //ParamDec -> Specifier VarDec
    TYPE_CMM* outer = getTypeOfSpecifier(node->childs[0], 0);
    char* finalID = NULL;
    TYPE_CMM* ret = getTypeOfVarDec(node->childs[1], outer, &finalID);
    TYPE_CMM* isHaveSym = listGetTypeIfHave(symbolList, finalID);
    if (isHaveSym) {
        printf("Error type 3 at Line %d: 变量出现重复定义:%s.\n", node->childs[1]->line, finalID);
    } 
    StructNodeList* isHaveInStruct = structListGetNodeIfHave(structList, finalID);
    if (isHaveSym) {
        printf("Error type 3 at Line %d: 变量出现重复定义,与前面定义过的结构体名字重复:%s.\n", node->childs[1]->line, finalID);
    } 
    listInsertValue(symbolList, finalID, ret);
    return ret;
}

TYPE_CMM** getTypesVarList(Snode* node, TYPE_CMM*** pret, unsigned int cur, int* pnum) {
    //VarList : ParamDec COMMA VarList | ParamDec
    TYPE_CMM* curType = getTypeOfParamDec(node->childs[0]);
    if (node->childs_num == 1) {
        *pret = (TYPE_CMM**)malloc(sizeof(TYPE_CMM*) * (cur + 1));
        *pnum = cur + 1;
    } else {
        getTypesVarList(node->childs[2], pret, cur + 1, pnum);
    }
    (*pret)[cur] = curType;
}

TYPE_CMM** getTypesOfFunDec(Snode* node, int* pnum) {
    //FunDec : ID LP VarList RP | ID LP RP
    if (node->childs_num == 3) {
        return NULL;
    } else {
        //ID LP VarList RP
        TYPE_CMM** ret = NULL;
        getTypesVarList(node->childs[2], &ret, 0, pnum);
        return ret;
    }
}

int DecListAnalysis(TYPE_CMM* t, Snode* node, int isFromStruct) { //if have error, return 1
    //DecList : Dec | Dec COMMA DecList
    //                Dec -> VarDec | VarDec ASSIGNOP Exp 
    int ret = 0;
    char* curName;
    TYPE_CMM* curT = getTypeOfVarDec(node->childs[0]->childs[0], t, &curName);
    TYPE_CMM* isHave = listGetTypeIfHave(symbolList, curName);
    StructNodeList* isHaveInStruct = structListGetNodeIfHave(structList, curName);
    if (isHave || isHaveInStruct) {
        ret = 0;
        printf("Error type 3 at Line %d: 重复的变量定义/与之前的结构体重名:%s.\n", node->childs[0]->line, curName);
    } else {
        if (node->childs[0]->childs_num > 1) {//处理赋值时可能的错误
        //Dec -> VarDec ASSIGNOP Exp
            // printf("pre: %s\n", typeToString(t));
            // psn(node->childs[0]);
            // printf("\n");
            if (isFromStruct) {
                printf("Error type 15 at Line %d: 结构体定义时对域进行初始化.\n", node->childs[0]->childs[2]->line);
            } else {
                TYPE_CMM* exprType = ExprAnalysis(node->childs[0]->childs[2]);
                if (exprType != NULL) {
                    if (!typeJudgeEquel(exprType, curT)) {
                        ret = 0;
                        char* c1 = typeToString(exprType);
                        char* c2 = typeToString(curT);
                        printf("Error type 5 at Line %d: 赋值号两边的表达式类型不匹配(a):(%s vs %s).\n", node->childs[0]->childs[2]->line, c2, c1);
                        if (strncmp(c1, "Struct", 6) == 0) {
                            free(c1);
                        } 
                        if (strncmp(c2, "Struct", 6) == 0) {
                            free(c2);
                        } 
                    }
                }
            }
        }
        // if (curT->isStruct) {
        //     listInsertValue(structList, curT->structName, (TYPE_CMM*)1);
        // }
        listInsertValue(symbolList, curName, curT);
    }
    if (node->childs_num > 1) {
        if (ret) {
            DecListAnalysis(t, node->childs[2], isFromStruct);
        } else {
            ret = DecListAnalysis(t, node->childs[2], isFromStruct);
        }
    } 
    return ret;
}

void ExtDecListAnalysis(TYPE_CMM* t, Snode* node) {
    //VarDec COMMA ExtDecList
    char* curName;
    TYPE_CMM* curT = getTypeOfVarDec(node->childs[0], t, &curName);
    TYPE_CMM* isHave = listGetTypeIfHave(symbolList, curName);
    StructNodeList* isHaveInStruct = structListGetNodeIfHave(structList, curName);
    if (isHave || isHaveInStruct) {
        printf("Error type 3 at Line %d: 重复的变量定义/与之前的结构体重名:%s.\n", node->childs[0]->line, curName);
    } else {
        // if (curT->isStruct) {
        //     listInsertValue(structList, curT->structName, (TYPE_CMM*)1);
        // }
        listInsertValue(symbolList, curName, curT);
    }
    if (node->childs_num > 1) {
        ExtDecListAnalysis(t, node->childs[2]);
    } 
}

int DefListAnalysis(Snode* node, int isFromStruct, int isNotDetectStruct) {
    //DefList -> Def DefList | e
    //             \ 
    //              -> Specifier DecList SEMI
    if (node == NULL) {
        return 0;
    }
    //Def DefList
    int isCurError = 0;
    //analysis Def
    TYPE_CMM* curType = getTypeOfSpecifier(node->childs[0]->childs[0], isNotDetectStruct);
    isCurError = DecListAnalysis(curType, node->childs[0]->childs[1], isFromStruct);
    if (isCurError == 0) {
        return node->childs[1] == NULL ? 0 : DefListAnalysis(node->childs[1], isFromStruct, isNotDetectStruct);
    }
    DefListAnalysis(node->childs[1], isFromStruct, isNotDetectStruct);
    return 1;
}

void StmtAnalysis(Snode* node, TYPE_CMM* retType) {
    //analysis stmt:node->childs[0]
    if (node->childs[0]->sname == nontokens[_Exp]) {
        //Exp SEMI
        ExprAnalysis(node->childs[0]);
    } else if (node->childs[0]->sname == tokens[_RETURN]) {
        //RETURN Exp SEMI
        TYPE_CMM* CurRetType = ExprAnalysis(node->childs[1]);
        if (CurRetType != NULL && !typeJudgeEquel(retType, CurRetType)) {
            char* c1 = typeToString(retType);
            char* c2 = typeToString(CurRetType);
            printf("Error type 8 at Line %d: return语句的返回类型与函数定义的返回类型不匹配:(%s vs %s).\n", 
                    node->childs[1]->line, c1, c2);
            if (strncmp(c1, "Struct", 6) == 0) {
                free(c1);
            } 
            if (strncmp(c2, "Struct", 6) == 0) {
                free(c2);
            } 
        }
    } else if (node->childs[0]->sname == nontokens[_CompSt]) {
        //CompSt
        CompStAnalysis(node->childs[0], retType);
    } else if (node->childs_num == 5) {
        //IF LP Exp RP Stmt
        ExprAnalysis(node->childs[2]);
        StmtAnalysis(node->childs[4], retType);
    } else {
        //IF LP Exp RP Stmt ELSE Stmt
        ExprAnalysis(node->childs[2]);
        StmtAnalysis(node->childs[4], retType);
        StmtAnalysis(node->childs[6], retType);
    }
}

void StmtListAnalysis(Snode* node, TYPE_CMM* retType) {
    if (node == NULL) {
        return;
    }
    StmtAnalysis(node->childs[0], retType);
    StmtListAnalysis(node->childs[1], retType);
}

void CompStAnalysis(Snode* node, TYPE_CMM* retType) {
    DefListAnalysis(node->childs[1], 0, 0);
    StmtListAnalysis(node->childs[2], retType);
}

/*
ExtDef : Specifier ExtDecList SEMI | Specifier SEMI | Specifier FunDec CompSt
*/
void ExtDefAnalysis(Snode* node) {
    if (node->childs_num == 2) {
        //Specifier SEMI
        TYPE_CMM* curType = getTypeOfSpecifier(node->childs[0], 0);
        if (curType && curType->isStruct) {
            structDetectDefSpecifier(node->childs[0]);
        }
        // if (curType->isStruct) {
        //     TYPE_CMM* isHave = listGetTypeIfHave(symbolList, curType->structName);
        //     int       isHaveInStruct = (int)listGetTypeIfHave(structList, curType->structName);
        //     if (isHaveInStruct || isHave) {
        //         structDetectDefSpecifier(node->childs[0]);
        //         printf("Error type 16 at Line %d: 结构体的名字与前面定义过的结构体或变量的名字重复:%s.\n", node->childs[0]->line, curType->structName);
        //     } else {
        //         int isError = structDetectDefSpecifier(node->childs[0]);
        //         if (!isError) {
        //             listInsertValue(structList, curType->structName, (TYPE_CMM*)1);
        //         }
        //     }
        // }
    } else if (node->childs[1]->sname == nontokens[_FunDec]) {
        //Specifier FunDec CompSt
        TYPE_CMM*  retType = getTypeOfSpecifier(node->childs[0], 0);
        int        num = 0;
        TYPE_CMM** argsTypes = getTypesOfFunDec(node->childs[1], &num);
        char*      funcName  = node->childs[1]->childs[0]->sval;
        TYPE_CMM* ret = funcListGetRetTypeIfHave(funcDefList, funcName, NULL, NULL);
        if (ret) {
            printf("Error type 4 at Line %d: 重复的函数定义:%s.\n", node->childs[0]->line, funcName);
        } else {
            funcListInsertValue(funcDefList, funcName, retType, num, argsTypes);
        }
        CompStAnalysis(node->childs[2], retType);
    } else {
        //Specifier ExtDecList SEMI
        TYPE_CMM* curType = getTypeOfSpecifier(node->childs[0], 0);
        ExtDecListAnalysis(curType, node->childs[1]);
    }
}

void startAnalysis(Snode* root) {
    /*init stage*/
    symbolList = listInit();
    structList = structListInit();
    funcDefList = funcListInit();
    //for IR
    TYPE_CMM* tmp_int_type = typeOfINT();
    funcListInsertValue(funcDefList, "write", tmp_int_type, 1, &tmp_int_type);
    funcListInsertValue(funcDefList, "read", tmp_int_type, 0, NULL);
    /*get ExtDefs*/
    getExtDefsHelper(root->childs[0], 0);
    for (unsigned int i = 0; i < ExtDefsNum; i++) {
        ExtDefAnalysis(ExtDefs[i]);
    }
#ifdef DEBUG
    printf("###################### Below is helpful for DEBUGING ##############################\n");
    funcListPrint(funcDefList);
    printf("\n");
    structListPrint(structList);
    printf("\n");
    printf("All symbols def:\n\n\t");
    listPrint(symbolList);
    printf("\n");
    printf("###################################################################################\n");
#endif
}

void endAnalysis() {
    if (ExtDefs) {
        free(ExtDefs);
    }
    listFree(symbolList);
    structListFree(structList);
    funcListFree(funcDefList);
}

#include "IR_generator.h"
extern  char*  ir_filename;
void Analysis(Snode* root) {
    startAnalysis(root);
    //IR
    startIR(symbolList, structList, funcDefList, ExtDefs, ExtDefsNum, ir_filename);
    endAnalysis();
}




#endif