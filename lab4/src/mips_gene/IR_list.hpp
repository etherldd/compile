#ifndef IR_LIST_H
#define IR_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

enum { IR_CONSTANT, IR_VARIABLE, IR_GET_ADDR, IR_DE_REF};

enum { IR_ASSIGN, IR_ADD, IR_SUB, IR_MUL, IR_DIV, IR_GOTO, IR_FUNC, 
           IR_LABEL, IR_IF, IR_RETURN, IR_DEC, IR_ARG, IR_CALL, IR_PARAM, IR_READ, IR_WRITE};


typedef struct Operand_* Operand;
struct Operand_ {
    unsigned int opr_kind;
    string       var_str;
};

Operand ir_Operand_init(unsigned int opr_kind, string var_str);

string ir_getOperandVal(Operand o);

typedef struct InterCode {
    unsigned int code_kind;
    union {
        struct { Operand right, left; }         assign;   //ASSIGN                      t0 := value          (3)
        struct { Operand result, op1, op2; }    op3;      //ADD, SUB, MUL, DIV          t4 := t5 * t6        (5)
        struct { Operand place; }               goto_st;  //GOTO                        GOTO v4              (2)
        struct { Operand label_name; }          label;    //LABEL                       LABEL v3 :           (3)
        struct { Operand func_name; }           func;     //FUNC                        FUNCTION main :      (3)
        struct { Operand op1, op2; 
                 char*  op;
                 Operand desti;}                if_st;    //IF                          IF t0 < t1 GOTO v0  (6)
        struct { Operand val; }                 return_st;//RETURN                      RETURN v15           (2)
        struct { Operand opr; Operand size; }   dec;      //DEC                         DEC src_tmp 12       (3) 
        struct { Operand val; }                 arg;      //ARG                         ARG t7               (2)
        struct { Operand ret, func; }           call;     //CALL                        t6 := CALL factorial (4)
        struct { Operand val; }                 param;    //PARAM                       PARAM m              (2)
        struct { Operand val; }                 read;     //READ                        READ t39             (2)
        struct { Operand val; }                 write;    //WRITE                       WRITE t39            (2)
    } u;
} IR;

string ir_getInterCodeStr(IR* o);

typedef struct IR_list_node {
    IR*                  node;
    struct IR_list_node* pnext;
} IR_list_NODE;

typedef struct IR_list {
    unsigned int    length;
    IR_list_NODE*   pfirst;
    IR_list_NODE*   plast;
} IR_LIST;

IR_LIST* ir_list_init();

int ir_list_empty(IR_LIST* l);

void ir_list_append(IR_LIST* l, IR_list_NODE* add);

void ir_list_append_IR(IR_LIST* l, IR* add);

void ir_write_to_file(IR_LIST* l, char* path);


vector<string>  ir_split(string s);
Operand         oprStringToOpr(string opr_s);
IR*             irStringToIR(string ir_s);
#endif