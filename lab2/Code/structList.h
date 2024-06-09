#ifndef STRUCTLIST_H
#define STRUCTLIST_H

#include "typelist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct structNode {
    char*               dataName;
    TYPE_CMM*           dataType;
    struct structNode*     pnext;
}StructNode;

void structNodeAssign(StructNode* pn, char* ps, TYPE_CMM* t) {
    pn->dataName = (char*)malloc(sizeof(char) * (1 + strlen(ps)));
    strcpy(pn->dataName, ps);
    pn->dataType = t;
}

StructNode* structNodeMalloc(char* ps, TYPE_CMM* t) {
    StructNode* ret = (StructNode*)malloc(sizeof(StructNode));
    ret->dataName = NULL;
    ret->dataType = NULL;
    ret->pnext = NULL;
    structNodeAssign(ret, ps, t);
    return ret;
}

void structNodeFree(StructNode* node) {
    if (node->dataName) {
        free(node->dataName);
    }
    free(node);
}

////////////////// StructNodeList /////////////////////(one single struct)

typedef struct structNodeList {
    StructNode*     pfirst;
    unsigned int    num;
    char*           structName;
    struct structNodeList*     pnext;
}StructNodeList;

StructNodeList* StructNodeListInit(char* name) {
    StructNodeList* ret = (StructNodeList*)malloc(sizeof(StructNodeList));
    ret->num = 0;
    ret->pfirst = NULL;
    ret->structName = (char*)malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(ret->structName, name);
    ret->pnext = NULL;
    return ret;
}

int StructNodeListIsEmpty(StructNodeList* l) {
    return l->num == 0;
}

void StructNodeListInsertNode(StructNodeList* l, StructNode* pn) {
    if (StructNodeListIsEmpty(l)) {
        l->num++;
        l->pfirst = pn;
    } else {
        StructNode* cur = l->pfirst;
        for (int i = 0; i < l->num - 1; i++) {
            cur = cur->pnext;
        }
        cur->pnext = pn;
        l->num++;
    }
}

void StructNodeListInsertValue(StructNodeList* l, char* ps, TYPE_CMM* t) {
    StructNodeListInsertNode(l, structNodeMalloc(ps, t));
}

TYPE_CMM*  StructNodeListGetTypeIfHave(StructNodeList* l, char* s) {
    if (StructNodeListIsEmpty(l)) {
        return NULL;
    }
    StructNode* cur = l->pfirst;
    for (int i = 0; i < l->num; i++) {
        if (strcmp(cur->dataName, s) == 0) {
            return cur->dataType;
        }
        cur = cur->pnext;
    }
    return NULL;
}

void StructNodeListPrint(StructNodeList* l) {
    StructNode* cur = l->pfirst;
    printf("Struct(%s): ", l->structName);
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

void StructNodeListFree(StructNodeList* l) {
    StructNode* cur = l->pfirst;
    for (int i = 0; i < l->num; i++) {
        StructNode* old = cur;
        cur = cur->pnext;
        structNodeFree(old);
    }
    free(l->structName);
    free(l);
}

////////////////// StructList /////////////////////(save structs)

typedef struct structList {
    StructNodeList*     pfirst;
    unsigned int        num;
}structLIST;

structLIST* structListInit() {
    structLIST* ret = (structLIST*)malloc(sizeof(structLIST));
    ret->num = 0;
    ret->pfirst = NULL;
    return ret;
}

int structListIsEmpty(structLIST* l) {
    return l->num == 0;
}

void structListInsertNode(structLIST* l, StructNodeList* pn) {
    if (structListIsEmpty(l)) {
        l->num++;
        l->pfirst = pn;
    } else {
        StructNodeList* cur = l->pfirst;
        for (int i = 0; i < l->num - 1; i++) {
            cur = cur->pnext;
        }
        cur->pnext = pn;
        l->num++;
    }
}

void structListInsertNullStruct(structLIST* l, char* ps) {
    structListInsertNode(l, StructNodeListInit(ps));
}

StructNodeList*  structListGetNodeIfHave(structLIST* l, char* s) {
    if (structListIsEmpty(l)) {
        return NULL;
    }
    StructNodeList* cur = l->pfirst;
    for (int i = 0; i < l->num; i++) {
        if (strcmp(cur->structName, s) == 0) {
            return cur;
        }
        cur = cur->pnext;
    }
    return NULL;
}

void structListAddElemToStruct(structLIST* l, char* s, char* newaddElem, TYPE_CMM* newtype) {
    StructNodeList* CurStructNode = structListGetNodeIfHave(l, s);
    if (!CurStructNode) {
        printf("can't find struct with name %s", s);
        return;
    }
    StructNodeListInsertValue(CurStructNode, newaddElem, newtype);
}

void structListPrint(structLIST* l) {
    StructNodeList* cur = l->pfirst;
    printf("All structs below:\n\n");
    for (int i = 0; i < l->num; i++) {
        printf("\t\t");
        StructNodeListPrint(cur);
        cur = cur->pnext;
    }
    //printf("\n");
}

void structListFree(structLIST* l) {
    StructNodeList* cur = l->pfirst;
    for (int i = 0; i < l->num; i++) {
        StructNodeList* old = cur;
        cur = cur->pnext;
        StructNodeListFree(old);
    }
    free(l);
}


#endif