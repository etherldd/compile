
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
vector<string> ir_split(string s) {
    const string delim = " ";
    int nPos = 0;
    vector<string> vec;
    nPos = s.find(delim.c_str());
    while(-1 != nPos) {
        string temp = s.substr(0, nPos);
        vec.push_back(temp);
        s = s.substr(nPos+1);
        nPos = s.find(delim.c_str());
    }
    vec.push_back(s);
    return vec;
}

Operand oprStringToOpr(string opr_s) {
    if (opr_s[0] == '#') {
        return ir_Operand_init(IR_CONSTANT, (opr_s.substr(1)));
    } else if (opr_s[0] == '*') {
        return ir_Operand_init(IR_DE_REF,   (opr_s.substr(1)));
    } else if (opr_s[0] == '&') {
        return ir_Operand_init(IR_GET_ADDR, (opr_s.substr(1)));
    } else {
        return ir_Operand_init(IR_VARIABLE, (opr_s));
    }
}

IR* irStringToIR(string ir_s) {
    vector<string> ir_vec = ir_split(ir_s);
    int length = ir_vec.size();
    IR* ret = (IR*) malloc(sizeof(IR));
    string copy_op; // 将变量声明移到switch语句之前

    switch (length)
    {
    case 2:
        if (ir_vec[0] == "GOTO") {
            ret->code_kind = IR_GOTO;
            ret->u.goto_st.place = oprStringToOpr(ir_vec[1]);
        } else if (ir_vec[0] == "RETURN") {
            ret->code_kind = IR_RETURN;
            ret->u.return_st.val = oprStringToOpr(ir_vec[1]);
        } else if (ir_vec[0] == "PARAM") {
            ret->code_kind = IR_PARAM;
            ret->u.param.val = oprStringToOpr(ir_vec[1]);
        } else if (ir_vec[0] == "READ") {
            ret->code_kind = IR_READ;
            ret->u.read.val = oprStringToOpr(ir_vec[1]);
        } else if (ir_vec[0] == "WRITE") {
            ret->code_kind = IR_WRITE;
            ret->u.write.val = oprStringToOpr(ir_vec[1]);
        } else if (ir_vec[0] == "ARG") {
            ret->code_kind = IR_ARG;
            ret->u.arg.val = oprStringToOpr(ir_vec[1]);
        } else {
            cout << "detect error in ir_code: num 2" << endl;
            free(ret);
            return NULL;
        }
        break;
    case 3:
        if (ir_vec[0] == "LABEL") {
            ret->code_kind = IR_LABEL;
            ret->u.label.label_name = oprStringToOpr(ir_vec[1]);
        } else if (ir_vec[0] == "FUNCTION") {
            ret->code_kind = IR_FUNC;
            ret->u.func.func_name = oprStringToOpr(ir_vec[1]);
        } else if (ir_vec[0] == "DEC") {
            ret->code_kind = IR_DEC;
            ret->u.dec.opr = oprStringToOpr(ir_vec[1]);
            ret->u.dec.size = oprStringToOpr(ir_vec[2]);
        } else {
            ret->code_kind = IR_ASSIGN;
            ret->u.assign.left = oprStringToOpr(ir_vec[0]);
            ret->u.assign.right = oprStringToOpr(ir_vec[2]);
        }
        break;
    case 4:
        ret->code_kind = IR_CALL;
        ret->u.call.func = oprStringToOpr(ir_vec[3]);
        ret->u.call.ret = oprStringToOpr(ir_vec[0]);
        break;
    case 5:
        if (ir_vec[3] == "+") {
            ret->code_kind = IR_ADD;
        } else if (ir_vec[3] == "-") {
            ret->code_kind = IR_SUB;
        } else if (ir_vec[3] == "*") {
            ret->code_kind = IR_MUL;
        } else if (ir_vec[3] == "/") {
            ret->code_kind = IR_DIV;
        } else {
            cout << "detect error in ir_code: num 2" << endl;
            free(ret);
            return NULL;
        }
        ret->u.op3.op1 = oprStringToOpr(ir_vec[2]);
        ret->u.op3.op2 = oprStringToOpr(ir_vec[4]);
        ret->u.op3.result = oprStringToOpr(ir_vec[0]);
        break;
    case 6:
        ret->code_kind = IR_IF;
        ret->u.if_st.desti = oprStringToOpr(ir_vec[5]);
        ret->u.if_st.op1 = oprStringToOpr(ir_vec[1]);
        ret->u.if_st.op2 = oprStringToOpr(ir_vec[3]);
        
        copy_op = ir_vec[2]; // 移动赋值操作到这里
        ret->u.if_st.op = (char*)copy_op.c_str();
        break;
    default:
        cout << "detect more than 6 args in ir_code" << endl;
        free(ret);
        return NULL;
        break;
    }
    return ret;
}
