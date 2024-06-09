#ifndef LIST_H
#define LIST_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "typelist.h"
////////////////// Node /////////////////////(for varible)
typedef struct VarNode {
    char*               dataName;
    TYPE_CMM*           dataType;
    struct VarNode*     pnext;
}Node;

void nodeAssign(Node* pn, char* ps, TYPE_CMM* t) {
    pn->dataName = (char*)malloc(sizeof(char) * (1 + strlen(ps)));
    strcpy(pn->dataName, ps);
    pn->dataType = t;
}

Node* nodeMalloc(char* ps, TYPE_CMM* t) {
    Node* ret = (Node*)malloc(sizeof(Node));
    ret->dataName = NULL;
    ret->dataType = NULL;
    ret->pnext = NULL;
    nodeAssign(ret, ps, t);
    return ret;
}

void nodeFree(Node* node) {
    if (node->dataName) {
        free(node->dataName);
    }
    free(node);
}
////////////////// Node /////////////////////(for function)

typedef struct FuncNode {
    char*               funcName;
    TYPE_CMM*           retType;
    unsigned int        argsNum;
    TYPE_CMM**          argsTypes;
    struct FuncNode*    pnext;
}funcNode;

void funcNodeAssign(funcNode* pn, char* ps, TYPE_CMM* retType, unsigned int argsNum, TYPE_CMM** argsTypes) {
    pn->funcName = (char*)malloc(sizeof(char) * (1 + strlen(ps)));
    strcpy(pn->funcName, ps);
    pn->retType = retType;
    pn->argsNum = argsNum;
    pn->argsTypes = argsTypes;
}

funcNode* funcNodeMalloc(char* ps, TYPE_CMM* retType, unsigned int argsNum, TYPE_CMM** argsTypes) {
    funcNode* ret = (funcNode*)malloc(sizeof(funcNode));
    funcNodeAssign(ret, ps, retType, argsNum, argsTypes);
    return ret;
}

void funcNodeFree(funcNode* node) {
    free(node->funcName);
    free(node);
}

////////////////// List /////////////////////
typedef struct VarList {
    Node*           pfirst;
    unsigned int    num;
}LIST;

LIST* listInit() {
    LIST* ret = (LIST*)malloc(sizeof(LIST));
    ret->num = 0;
    ret->pfirst = NULL;
    return ret;
}

int isEmpty(LIST* l) {
    return l->num == 0;
}

void listInsertNode(LIST* l, Node* pn) {
    if (isEmpty(l)) {
        l->num++;
        l->pfirst = pn;
    } else {
        Node* cur = l->pfirst;
        for (int i = 0; i < l->num - 1; i++) {
            cur = cur->pnext;
        }
        cur->pnext = pn;
        l->num++;
    }
}

void listInsertValue(LIST* l, char* ps, TYPE_CMM* t) {
    listInsertNode(l, nodeMalloc(ps, t));
}

TYPE_CMM*  listGetTypeIfHave(LIST* l, char* s) {
    if (isEmpty(l)) {
        return NULL;
    }
    Node* cur = l->pfirst;
    for (int i = 0; i < l->num; i++) {
        if (strcmp(cur->dataName, s) == 0) {
            return cur->dataType;
        }
        cur = cur->pnext;
    }
    return NULL;
}

void listPrint(LIST* l) {
    Node* cur = l->pfirst;
    for (int i = 0; i < l->num; i++) {
        char* typeStr = typeToString(cur->dataType);
        printf("%s(%s) ", cur->dataName, typeStr);
        if (strncmp(typeStr, "Struct", 6) == 0) {
            free(typeStr);
        } 
        if (i != l->num - 1) {
            printf("-> ");
        }
        cur = cur->pnext;
    }
    printf("\n");
}

void listFree(LIST* l) {
    Node* cur = l->pfirst;
    for (int i = 0; i < l->num; i++) {
        Node* old = cur;
        cur = cur->pnext;
        nodeFree(old);
    }
    free(l);
}
////////////////// funcList ///////////////////// 
typedef struct FuncList {
    funcNode*       pfirst;
    unsigned int    num;
}funcLIST;

funcLIST* funcListInit() {
    funcLIST* ret = (funcLIST*)malloc(sizeof(funcLIST));
    ret->num = 0;
    ret->pfirst = NULL;
    return ret;
}

int funcIsEmpty(funcLIST* l) {
    return l->num == 0;
}

void funcListInsertNode(funcLIST* l, funcNode* pn) {
    if (funcIsEmpty(l)) {
        l->num++;
        l->pfirst = pn;
    } else {
        funcNode* cur = l->pfirst;
        for (int i = 0; i < l->num - 1; i++) {
            cur = cur->pnext;
        }
        cur->pnext = pn;
        l->num++;
    }
}

void funcListInsertValue(funcLIST* l, char* ps, TYPE_CMM* retType, unsigned int argsNum, TYPE_CMM** argsTypes) {
    funcListInsertNode(l, funcNodeMalloc(ps, retType, argsNum, argsTypes));
}

TYPE_CMM*  funcListGetRetTypeIfHave(funcLIST* l, char* s, TYPE_CMM*** pArgsTypes, int* pargsNum) {
    if (funcIsEmpty(l)) {
        return NULL;
    }
    funcNode* cur = l->pfirst;
    for (int i = 0; i < l->num; i++) {
        if (strcmp(cur->funcName, s) == 0) {
            if (pArgsTypes) {
                *pArgsTypes = cur->argsTypes;
            }
            if (pargsNum) {
                *pargsNum = cur->argsNum;
            }
            return cur->retType;
        }
        cur = cur->pnext;
    }
    return NULL;
}

void funcListPrint(funcLIST* l) {
    funcNode* cur = l->pfirst;
    printf("All funcs below:\n\n");
    for (int i = 0; i < l->num; i++) {
        printf("\t\tFUNC: %s(", cur->funcName);
        if (cur->argsNum) {
            char* typeStr2 = typeToString(cur->argsTypes[0]);
            printf("%s", typeStr2);
            if (strncmp(typeStr2, "Struct", 6) == 0) {
                free(typeStr2);
            } 
            if (cur->argsNum > 1) {
                for (int i = 0; i < cur->argsNum - 1; i++) {
                    typeStr2 = typeToString(cur->argsTypes[i + 1]);
                    printf(", %s", typeStr2);
                    if (strncmp(typeStr2, "Struct", 6) == 0) {
                        free(typeStr2);
                    } 
                }
            }
        }
        char* typeStr = typeToString(cur->retType);
        printf(") -> %s", typeStr);
        if (strncmp(typeStr, "Struct", 6) == 0) {
            free(typeStr);
        } 
        printf("\n");
        cur = cur->pnext;
    }
}

void funcListFree(funcLIST* l) {
    funcNode* cur = l->pfirst;
    for (int i = 0; i < l->num; i++) {
        funcNode* old = cur;
        cur = cur->pnext;
        funcNodeFree(old);
    }
    free(l);
}


#endif