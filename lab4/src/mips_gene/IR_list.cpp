
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "IR_list.hpp"

Operand ir_Operand_init(unsigned int opr_kind, string var_str) {
    Operand ret = new Operand_();
    ret->opr_kind = opr_kind;
    ret->var_str = var_str;
    return ret;
}

string ir_getOperandVal(Operand o) {
    string res;
    if (o->opr_kind == IR_VARIABLE) { 
        return o->var_str;
    } else if (o->opr_kind == IR_CONSTANT) {
        res = "#" + o->var_str;
    } else if (o->opr_kind == IR_GET_ADDR) {
        res = "&" + o->var_str;
    } else if (o->opr_kind == IR_DE_REF) {
        res = "*" + o->var_str;
    }
    return res;
}

string ir_getInterCodeStr(IR* o) {
    string ret;
    if (o->code_kind == IR_ASSIGN) {
        string left =  ir_getOperandVal(o->u.assign.left);
        string right = ir_getOperandVal(o->u.assign.right);
        ret = left + " := " + right;
    } else if (o->code_kind == IR_ADD || o->code_kind == IR_SUB || o->code_kind == IR_MUL || o->code_kind == IR_DIV) {
        string op1 = ir_getOperandVal(o->u.op3.op1);
        string op2 = ir_getOperandVal(o->u.op3.op2);
        string res = ir_getOperandVal(o->u.op3.result);
        ret = res + " := " + op1;
        if (o->code_kind == IR_ADD) {
            ret += " + ";
        } else if (o->code_kind == IR_SUB) {
            ret += " - ";
        } else if (o->code_kind == IR_MUL) {
            ret += " * ";
        } else {
            ret += " / ";
        }
        ret += op2;
    } else if (o->code_kind == IR_GOTO) {
        string x =  ir_getOperandVal(o->u.goto_st.place);
        ret = "GOTO " + x; 
    } else if (o->code_kind == IR_FUNC) {
        string x =  ir_getOperandVal(o->u.func.func_name);
        ret = "FUNCTION " + x + " :";
    } else if (o->code_kind == IR_LABEL) {
        string x =  ir_getOperandVal(o->u.label.label_name);
        ret = "LABEL " + x + " :";
    } else if (o->code_kind == IR_IF) {
        string desti =  ir_getOperandVal(o->u.if_st.desti);
        string op1   =  ir_getOperandVal(o->u.if_st.op1);
        string op2   =  ir_getOperandVal(o->u.if_st.op2);
        ret = "IF " + op1 + " " + o->u.if_st.op + " " + op2 + " GOTO " + desti;
    } else if (o->code_kind == IR_RETURN) {
        string x =  ir_getOperandVal(o->u.return_st.val);
        ret = "RETURN " + x;
    } else if (o->code_kind == IR_DEC) {
        string opr =  ir_getOperandVal(o->u.dec.opr);
        string size =  ir_getOperandVal(o->u.dec.size);
        ret = "DEC " + opr + " " + size;
    } else if (o->code_kind == IR_ARG) {
        string x =  ir_getOperandVal(o->u.arg.val);
        ret = "ARG " + x;
    } else if (o->code_kind == IR_CALL) {
        string cur_ret =  ir_getOperandVal(o->u.call.ret);
        string func_name = ir_getOperandVal(o->u.call.func);
        ret = cur_ret + " := CALL " + func_name;
    } else if (o->code_kind == IR_PARAM) {
        string x =  ir_getOperandVal(o->u.param.val);
        ret = "PARAM " + x;
    } else if (o->code_kind == IR_READ) {
        string x =  ir_getOperandVal(o->u.read.val);
        ret = "READ " + x;
    } else if (o->code_kind == IR_WRITE) {
        string x =  ir_getOperandVal(o->u.write.val);
        ret = "WRITE " + x;
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
        char* curStr = (char*)ir_getInterCodeStr(cur->node).c_str();
        fputs(curStr, f);
        fputs("\n", f);
        free(curStr);
        cur = cur->pnext;
    }
    fclose(f);
}
