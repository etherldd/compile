
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "IR_list.hpp"

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
