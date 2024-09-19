#ifndef IR_LIST_H
#define IR_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum { IR_CONSTANT, IR_VARIABLE, IR_GET_ADDR, IR_DE_REF};

enum { IR_ASSIGN, IR_ADD, IR_SUB, IR_MUL, IR_DIV, IR_GOTO, IR_FUNC, 
           IR_LABEL, IR_IF, IR_RETURN, IR_DEC, IR_ARG, IR_CALL, IR_PARAM, IR_READ, IR_WRITE};


typedef struct Operand_* Operand;
struct Operand_ {
    unsigned int opr_kind;
    char*        var_str;
};

Operand ir_Operand_init(unsigned int opr_kind, char* var_str) {
    Operand ret = (Operand)malloc(sizeof(struct Operand_));
    ret->opr_kind = opr_kind;
    ret->var_str = var_str;
    return ret;
}

char* ir_getOperandVal(Operand o) {
    char* ret = (char*)calloc(sizeof(char), 20);
    if (o->opr_kind == IR_VARIABLE) { 
        strcpy(ret, o->var_str);
    } else if (o->opr_kind == IR_CONSTANT) {
        strcat(ret, "#");
        strcat(ret, o->var_str);
    } else if (o->opr_kind == IR_GET_ADDR) {
        strcat(ret, "&");
        strcat(ret, o->var_str);
    } else if (o->opr_kind == IR_DE_REF) {
        strcat(ret, "*");
        strcat(ret, o->var_str);
    }
    return ret;
}

typedef struct InterCode {
    unsigned int code_kind;
    union {
        struct { Operand right, left; }         assign;   //ASSIGN                      t0 := value          (3)
        struct { Operand result, op1, op2; }    op3;      //ADD, SUB, MUL, DIV          t4 := t5 * t6        (5)
        struct { Operand place; }               goto_st;  //GOTO                        GOTO v4              (2)
        struct { Operand label_name; }          label;    //LABEL                       LABEL v3 :           (3)
        struct { Operand func_name; }           func;     //FUNC                        FUNCTION main :      (3)
        struct { Operand op1, op2; 
                 char*   op;
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
char* ir_getInterCodeStr(IR* o) {
    char* ret = (char*)calloc(sizeof(char), 50);
    if (o->code_kind == IR_ASSIGN) {
        char* left =  ir_getOperandVal(o->u.assign.left);
        char* right = ir_getOperandVal(o->u.assign.right);
        strcat(ret, left);
        strcat(ret, " := ");
        strcat(ret, right);
        free(left);
        free(right);
    } else if (o->code_kind == IR_ADD || o->code_kind == IR_SUB || o->code_kind == IR_MUL || o->code_kind == IR_DIV) {
        char* op1 = ir_getOperandVal(o->u.op3.op1);
        char* op2 = ir_getOperandVal(o->u.op3.op2);
        char* res = ir_getOperandVal(o->u.op3.result);
        strcat(ret, res);
        strcat(ret, " := ");
        strcat(ret, op1);
        if (o->code_kind == IR_ADD) {
            strcat(ret, " + ");
        } else if (o->code_kind == IR_SUB) {
            strcat(ret, " - ");
        } else if (o->code_kind == IR_MUL) {
            strcat(ret, " * ");
        } else {
            strcat(ret, " / ");
        }
        strcat(ret, op2);
        free(op1);
        free(op2);
        free(res);
    } else if (o->code_kind == IR_GOTO) {
        char* x =  ir_getOperandVal(o->u.goto_st.place);
        strcat(ret, "GOTO ");
        strcat(ret, x);
        free(x);
    } else if (o->code_kind == IR_FUNC) {
        char* x =  ir_getOperandVal(o->u.func.func_name);
        strcat(ret, "FUNCTION ");
        strcat(ret, x);
        strcat(ret, " :");
        free(x);
    } else if (o->code_kind == IR_LABEL) {
        char* x =  ir_getOperandVal(o->u.label.label_name);
        strcat(ret, "LABEL ");
        strcat(ret, x);
        strcat(ret, " :");
        free(x);
    } else if (o->code_kind == IR_IF) {
        char* desti =  ir_getOperandVal(o->u.if_st.desti);
        char* op1   =  ir_getOperandVal(o->u.if_st.op1);
        char* op2   =  ir_getOperandVal(o->u.if_st.op2);
        strcat(ret, "IF ");
        strcat(ret, op1);
        strcat(ret, " ");
        strcat(ret, o->u.if_st.op);
        strcat(ret, " ");
        strcat(ret, op2);
        strcat(ret, " GOTO ");
        strcat(ret, desti);
        free(op1);
        free(op2);
        free(desti);
    } else if (o->code_kind == IR_RETURN) {
        char* x =  ir_getOperandVal(o->u.return_st.val);
        strcat(ret, "RETURN ");
        strcat(ret, x);
        free(x);
    } else if (o->code_kind == IR_DEC) {
        char* opr =  ir_getOperandVal(o->u.dec.opr);
        char* size =  ir_getOperandVal(o->u.dec.size);
        strcat(ret, "DEC ");
        strcat(ret, opr);
        strcat(ret, " ");
        strcat(ret, size);
        free(opr);
    } else if (o->code_kind == IR_ARG) {
        char* x =  ir_getOperandVal(o->u.arg.val);
        strcat(ret, "ARG ");
        strcat(ret, x);
        free(x);
    } else if (o->code_kind == IR_CALL) {
        char* cur_ret =  ir_getOperandVal(o->u.call.ret);
        char* func_name = ir_getOperandVal(o->u.call.func);
        strcat(ret, cur_ret);
        strcat(ret, " := CALL ");
        strcat(ret, func_name);
        free(cur_ret);
        free(func_name);
    } else if (o->code_kind == IR_PARAM) {
        char* x =  ir_getOperandVal(o->u.param.val);
        strcat(ret, "PARAM ");
        strcat(ret, x);
        free(x);
    } else if (o->code_kind == IR_READ) {
        char* x =  ir_getOperandVal(o->u.read.val);
        strcat(ret, "READ ");
        strcat(ret, x);
        free(x);
    } else if (o->code_kind == IR_WRITE) {
        char* x =  ir_getOperandVal(o->u.write.val);
        strcat(ret, "WRITE ");
        strcat(ret, x);
        free(x);
    }
    return ret;
}

typedef struct IR_list_node {
    IR*                  node;
    struct IR_list_node* pnext;
} IR_list_NODE;

typedef struct IR_list {
    unsigned int    length;
    IR_list_NODE*   pfirst;
    IR_list_NODE*   plast;
} IR_LIST;

IR_LIST* ir_list_init() {
    IR_LIST* ret = (IR_LIST*)malloc(sizeof(IR_LIST));
    ret->length = 0;
    ret->pfirst = NULL;
    ret->plast = NULL;
    return ret;
}

int ir_list_empty(IR_LIST* l) {
    return l->length == 0;
}

void ir_list_append(IR_LIST* l, IR_list_NODE* add) {
    if (ir_list_empty(l)) {
        l->length = 1;
        l->pfirst = add;
        l->plast = add;
    } else {
        l->plast->pnext = add;
        l->length++;
        l->plast = add;
    }
}

void ir_list_append_IR(IR_LIST* l, IR* add) {
    IR_list_NODE* to_add = (IR_list_NODE*)malloc(sizeof(IR_list_NODE));
    to_add->node = add;
    to_add->pnext = NULL;
    ir_list_append(l, to_add);
}

void ir_write_to_file(IR_LIST* l, char* path) {
    FILE* f = fopen(path, "w");
    IR_list_NODE* cur = l->pfirst;
    for (int i = 0; i < l->length; i++) {
        char* curStr = ir_getInterCodeStr(cur->node);
        fputs(curStr, f);
        fputs("\n", f);
        free(curStr);
        cur = cur->pnext;
    }
    fclose(f);
}
#endif