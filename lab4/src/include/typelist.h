#ifndef TYPEDEF_H
#define TYPEDEF_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum {_INT_TYPE, _FLOAT_TYPE};


//typedef struct structField;


typedef struct typelist {
    int                 isArray;
    /*if isArray*/
    unsigned int        ArrayNum;
    struct typelist*    ArrayElemType;
    /*if not isArray*/
    int                 isStruct;
    /*if isStruct*/
    char*               structName;
    //struct structField* pstructField;
    /*else*/
    int                 type;

} TYPE_CMM;

// struct structField {
//     TYPE_CMM*           type;
//     struct structField* pnext;
// };


TYPE_CMM* typeArrayOfType(TYPE_CMM* t, unsigned int num) {
    TYPE_CMM* ret = (TYPE_CMM*)malloc(sizeof(TYPE_CMM));
    ret->isArray = 1;
    ret->ArrayNum = num;
    ret->ArrayElemType = t;
    return ret;
}

TYPE_CMM* typeOfINT() {
    TYPE_CMM* ret = (TYPE_CMM*)malloc(sizeof(TYPE_CMM));
    ret->isArray = 0;
    ret->isStruct = 0;
    ret->type = _INT_TYPE;
    ret->structName = NULL;
    return ret;
}

TYPE_CMM* typeOfFLOAT() {
    TYPE_CMM* ret = (TYPE_CMM*)malloc(sizeof(TYPE_CMM));
    ret->isArray = 0;
    ret->isStruct = 0;
    ret->type = _FLOAT_TYPE;
    ret->structName = NULL;
    return ret;
}

TYPE_CMM* typeOfStruct(char* s) {
    TYPE_CMM* ret = (TYPE_CMM*)malloc(sizeof(TYPE_CMM));
    ret->isArray = 0;
    ret->isStruct = 1;
    ret->structName = (char*)malloc(sizeof(char) * (strlen(s) + 1));
    strcpy(ret->structName, s);
    return ret;
}

int typeJudgeEquel(TYPE_CMM* ta, TYPE_CMM* tb) {
    if (ta == NULL || tb == NULL) {
        return 0;
    }
    if (ta->isArray != tb->isArray) {
        return 0;
    }
    if (ta->isArray == 1) {
        return typeJudgeEquel(ta->ArrayElemType, tb->ArrayElemType);
    } else {
        if (ta->isStruct != tb->isStruct) {
            return 0;
        }
        if (ta->isStruct == 0) {
            return ta->type == tb->type;
        } else {
            return strcmp(ta->structName, tb->structName) == 0;
        }
    }
    
}

void typeFree(TYPE_CMM* t) {
    if (t->isArray) {
        typeFree(t->ArrayElemType);
    }
    if (t->structName) {
        free(t->structName);
    }
    free(t);
}

char* typeToString(TYPE_CMM* t) {
    if (t->isArray) {
        char* sub_String = typeToString(t->ArrayElemType);
        char* ret = (char*)malloc(sizeof(char) * (strlen("Array()") + strlen(sub_String) + 1));
        strcpy(ret, "Array(");
        strcat(ret, sub_String);
        strcat(ret, ")");
        return ret;
    }
    if (t->isStruct) {
        char* ret = (char*)malloc(sizeof(char) * (1 + strlen("Struct:") + strlen(t->structName)));
        ret[0] = '\0';
        strcat(ret, "Struct:");
        strcat(ret, t->structName);
        return ret;
    }
    if (t->type == _INT_TYPE) {
        return "INT";
    } else {
        return "FLOAT";
    }
}
#endif