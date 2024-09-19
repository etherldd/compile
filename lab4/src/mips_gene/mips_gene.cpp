
#include "mips_gene.hpp"
#include "IR_list.hpp"
#include <map>

extern string ir_file_name;
extern string mips_file_name;
extern fstream ir_file;
extern ofstream mips_file;

map<string, int>*  RegOfVar_noNumberConstrain = NULL;
long global_counter = 1; 


void mips32_gene_init() {
    ir_file.open(ir_file_name);
    mips_file.open(mips_file_name, ios::trunc);
    RegOfVar_noNumberConstrain = new map<string, int>();
}

void mips32_gene_free() {
    //1. close file
    ir_file.close();
    mips_file.close();
    //2. free mem
    delete RegOfVar_noNumberConstrain;
}

string get_next_line() {
    string ret;
    getline(ir_file, ret);
    return ret;
}



long getRegOfVar_noNumberConstrain(string var) {
    if (RegOfVar_noNumberConstrain->count(var)) {
        return RegOfVar_noNumberConstrain->at(var);
    } else {
        long ret = global_counter;
        global_counter++;
        return ret;
    }
}
// enum { IR_ASSIGN, IR_ADD, IR_SUB, IR_MUL, IR_DIV, IR_GOTO, IR_FUNC, 
//         IR_LABEL, IR_IF, IR_RETURN, IR_DEC, IR_ARG, 
//         IR_CALL, IR_PARAM, IR_READ, IR_WRITE};
string gene_target_code(string ir_line) {
    IR* cur_IR = irStringToIR(ir_line);
    switch (cur_IR->code_kind)
    {
    case IR_ASSIGN:
        /* t0 := value  */
        break;
    case IR_ADD:
        /* t4 := t5 * t6 */
        break;
    case IR_SUB:
        /* t4 := t5 * t6 */
        break;
    case IR_MUL:
        /* t4 := t5 * t6 */
        break;
    case IR_DIV:
        /* t4 := t5 * t6 */
        break;
    case IR_GOTO:
        /* GOTO v4 */
        break;
    case IR_FUNC:
        /* FUNCTION main : */
        break;
    case IR_LABEL:
        /* LABEL v3 : */
        break;
    case IR_IF:
        /* IF t0 < t1 GOTO v0 */
        break;
    case IR_RETURN:
        /* RETURN v15 */
        break;
    case IR_DEC:
        /* DEC src_tmp 12 */
        break;
    case IR_ARG:
        /* ARG t7 */
        break;
    case IR_CALL:
        /* t6 := CALL factorial */
        break;
    case IR_PARAM:
        /* PARAM m */
        break;
    case IR_READ:
        /* READ t39 */
        break;
    case IR_WRITE:
        /* WRITE t39 */
        break;
    default:
        break;
    }
    return "";
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
        return ir_Operand_init(IR_CONSTANT, (char*)(opr_s.substr(1).c_str()));
    } else if (opr_s[0] == '*') {
        return ir_Operand_init(IR_DE_REF,   (char*)(opr_s.substr(1).c_str()));
    } else if (opr_s[0] == '&') {
        return ir_Operand_init(IR_GET_ADDR, (char*)(opr_s.substr(1).c_str()));
    } else {
        return ir_Operand_init(IR_VARIABLE, (char*)(opr_s.c_str()));
    }
}

IR* irStringToIR(string ir_s) {
    vector<string> ir_vec = ir_split(ir_s);
    int length = ir_vec.size();
    IR* ret = (IR*) malloc(sizeof(IR));
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
        ret->u.if_st.op = (char*)ir_vec[2].c_str();
        break;
    default:
        cout << "detect more than 6 args in ir_code" << endl;
        free(ret);
        return NULL;
        break;
    }
    return ret;
}






