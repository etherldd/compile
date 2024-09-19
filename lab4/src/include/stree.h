#ifndef STREE_H
#define STREE_H


#define N_TOKENS 27
#define N_NEEDPR 4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* tokens_np[] = {"ID", "INT", "FLOAT", "TYPE"};
char* tokens[] = {"SEMI", "COMMA", "ASSIGNOP", "RELOP", "PLUS", //5
    "MINUS", "STAR", "DIV", "AND",  "OR", "DOT", "NOT", "TYPE", "LP",   //9
    "RP", "LB", "RB", "LC", "RC", "STRUCT", "RETURN", "IF", "ELSE",     //9
    "WHILE", "ID", "INT", "FLOAT"}; //4

enum {_SEMI, _COMMA, _ASSIGNOP, _RELOP, _PLUS, //5
    _MINUS, _STAR, _DIV, _AND,  _OR, _DOT, _NOT, _TYPE, _LP,   //9
    _RP, _LB, _RB, _LC, _RC, _STRUCT, _RETURN, _IF, _ELSE,     //9
    _WHILE, _ID, _INT, _FLOAT}; //4



typedef struct snode
{
    /* data */
    unsigned int line;
    char*        sname;
    char*        sval;
    unsigned int childs_num;
    struct snode** childs;
    int          isRight;
} Snode;


Snode* node_oftoken(int line, unsigned int token_num, char* value) {
    Snode* ret = (Snode*)malloc(sizeof(Snode));
    ret->childs = NULL;
    ret->childs_num = 0;
    ret->line = line;
    ret->sname = tokens[token_num];
    ret->sval = value;
    ret->isRight = 0;
    return ret;
}

void delete_s(Snode* par) {
    if (par == NULL) {return;}
    if (par->childs) free(par->childs);
    if (par->sval) free(par->sval);
}

void delete_s_recu(Snode* par) {
    if (par == NULL) {return;}
    for (int i = 0; i < par->childs_num; i++) {
        delete_s_recu(par->childs[i]);
    }
    delete_s(par);
}

void insert(Snode* par, unsigned int childs_num, Snode** childs) {
    par->childs_num = childs_num;
    par->childs = (Snode**)malloc(sizeof(Snode*) * childs_num);
    for (int i = 0; i < childs_num; i++) {
        par->childs[i] = childs[i];
    }
}

int judgeToken(char* s) {
    for (int i = 0; i < N_NEEDPR; i++) {
        if  (strcmp(tokens_np[i], s) == 0) {
            return 2;
        }
    }
    for (int i = 0; i < N_TOKENS; i++) {
        if (strcmp(tokens[i], s) == 0) {
            return 1;
        }
    }
    return 0;
}

void psn_helper(Snode *p, unsigned int num_tab) {
    if (p == NULL) {return;}
    for (int i = 0; i < num_tab; i++) {
        printf("   ");
    }
    int res = judgeToken(p->sname);
    if (res == 2) {
        //token: ID
        printf("%s: %s\n", p->sname, p->sval);
    } else if (res == 1) {
        //token: non-ID
        printf("%s\n", p->sname);
    } else {
        //non-token
        printf("%s (%d)\n", p->sname, p->line);
        for (int i = 0; i < p->childs_num; i++) {
            psn_helper(p->childs[i], num_tab + 1);
        }
    }
}

void psn(Snode *p) {
    psn_helper(p, 0);
}

#endif
