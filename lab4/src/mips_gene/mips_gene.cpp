#include "mips_gene.hpp"
#include "IR_list.hpp"
#include <map>
#include <sstream>

extern string ir_file_name;
extern string mips_file_name;
extern fstream ir_file;
extern ofstream mips_file;

map<string, int> RegOfVar;  // Mapping from variable name to register number
map<string, map<string, int>> FuncVarOffsetTable;  // Mapping from function name to (variable name, offset) mapping
int globalRegCounter = 1;  // Global register counter
string currentFuncName = "";  // Current function being processed

map<string, int> mips32_getfunc_table(string func) {
    if (FuncVarOffsetTable.find(func) == FuncVarOffsetTable.end()) {
        return map<string, int>();
    }
    return FuncVarOffsetTable[func];
}

int mips32_getfunc_size(string func) {
    if (FuncVarOffsetTable.find(func) == FuncVarOffsetTable.end()) {
        return 0;
    }
    int maxOffset = 0;
    for (const auto& pair : FuncVarOffsetTable[func]) {
        maxOffset = max(maxOffset, pair.second);
    }
    return maxOffset + 4;  // Assume each variable occupies 4 bytes
}

void mips32_scan_and_set_table() {
    //store the (key, value) pair
    //key: value_name
    //val: offset
    int size = 0;
    ir_file.open(ir_file_name);
    string cur_scan_funcname = "";
    while (true) {
        string cur_line = get_next_line();
        if (cur_line == "") {
            if (cur_scan_funcname != "") {
                // No additional operation needed, as we store directly in FuncVarOffsetTable
            }
            break;
        } 
        IR* cur_IR = irStringToIR(cur_line);
        if (cur_IR->code_kind == IR_FUNC) {
            if (!currentFuncName.empty()) {
                // No additional operation needed, as we store directly in FuncVarOffsetTable
            }
            currentFuncName = cur_IR->u.func.func_name->var_str;
            FuncVarOffsetTable[currentFuncName] = map<string, int>();
            size = 0;
        }
        switch (cur_IR->code_kind)
        {
            case IR_ASSIGN:
                /* a = b */
                if (FuncVarOffsetTable[currentFuncName].find(cur_IR->u.assign.left->var_str) == FuncVarOffsetTable[currentFuncName].end()) {
                    FuncVarOffsetTable[currentFuncName][cur_IR->u.assign.left->var_str] = size;
                    size += 4;
                }
                break;
            case IR_ADD:
                /* t4 := t5 + t6 */
                if (FuncVarOffsetTable[currentFuncName].find(cur_IR->u.op3.result->var_str) == FuncVarOffsetTable[currentFuncName].end()) {
                    FuncVarOffsetTable[currentFuncName][cur_IR->u.op3.result->var_str] = size;
                    size += 4;
                }
                break;
            case IR_SUB:
                /* t4 := t5 - t6 */
                if (FuncVarOffsetTable[currentFuncName].find(cur_IR->u.op3.result->var_str) == FuncVarOffsetTable[currentFuncName].end()) {
                    FuncVarOffsetTable[currentFuncName][cur_IR->u.op3.result->var_str] = size;
                    size += 4;
                }
                break;
            case IR_MUL:
                /* t4 := t5 * t6 */
                if (FuncVarOffsetTable[currentFuncName].find(cur_IR->u.op3.result->var_str) == FuncVarOffsetTable[currentFuncName].end()) {
                    FuncVarOffsetTable[currentFuncName][cur_IR->u.op3.result->var_str] = size;
                    size += 4;
                }
                break;
            case IR_DIV:
                /* t4 := t5 / t6 */
                if (FuncVarOffsetTable[currentFuncName].find(cur_IR->u.op3.result->var_str) == FuncVarOffsetTable[currentFuncName].end()) {
                    FuncVarOffsetTable[currentFuncName][cur_IR->u.op3.result->var_str] = size;
                    size += 4;
                }
                break;
            case IR_CALL:
                /* t6 := CALL factorial */
                if (FuncVarOffsetTable[currentFuncName].find(cur_IR->u.call.ret->var_str) == FuncVarOffsetTable[currentFuncName].end()) {
                    FuncVarOffsetTable[currentFuncName][cur_IR->u.call.ret->var_str] = size;
                    size += 4;
                }
                break;
            default:
                break;
        }
    }
    ir_file.close();
}

void mips32_gene_init() {
    mips_file.open(mips_file_name, ios::trunc);
    RegOfVar = map<string, int>();
    FuncVarOffsetTable = map<string, map<string, int>>();
}

void mips32_gene_free() {
    //1. close file
    mips_file.close();
    //2. free mem
    RegOfVar.clear();
    FuncVarOffsetTable.clear();
}

string get_next_line() {
    string ret;
    getline(ir_file, ret);
    return ret;
}

long getRegOfVar_noNumberConstrain(string var) {
    if (RegOfVar.find(var) != RegOfVar.end()) {
        return RegOfVar[var];
    } else {
        long ret = globalRegCounter++;
        RegOfVar[var] = ret;
        return ret;
    }
}

string getRegOfVar(string var) {
    long num = getRegOfVar_noNumberConstrain(var);
    ostringstream oss;
    oss << "$t" << num;
    string res = oss.str();
    return res;
}
// enum { IR_ASSIGN, IR_ADD, IR_SUB, IR_MUL, IR_DIV, IR_GOTO, IR_FUNC, 
//         IR_LABEL, IR_IF, IR_RETURN, IR_DEC, IR_ARG, 
//         IR_CALL, IR_PARAM, IR_READ, IR_WRITE};
string gene_target_code(string ir_line) {
    IR*     cur_IR = irStringToIR(ir_line);
    string  res;
    string  left, op1, op2, right;
    ostringstream oss_start, oss_end;
    
    int     size;
    switch (cur_IR->code_kind)
    {
    case IR_ASSIGN:
        /* t0 := value  */
        left = getRegOfVar(cur_IR->u.assign.left->var_str);
        if (cur_IR->u.assign.right->opr_kind == IR_CONSTANT) {
            res = "li " + left + ", " + cur_IR->u.assign.right->var_str;
        } else if (cur_IR->u.assign.right->opr_kind == IR_VARIABLE) {
            op2 = getRegOfVar(cur_IR->u.assign.right->var_str);
            res = "add " + left + ", $r0, " + op2;
        } else if (cur_IR->u.assign.right->opr_kind == IR_GET_ADDR) {
            int total_size = mips32_getfunc_size(currentFuncName);
            int cur_offset = mips32_getfunc_table(currentFuncName)[cur_IR->u.assign.right->var_str];
            int delta = total_size - cur_offset;
            oss_start << "add " + left + ", $sp, " << delta;
            res = oss_start.str();
            oss_start.str("");
        } else {//IR_DE_REF
            op1 = cur_IR->u.assign.right->var_str; 
            res = "la " + left + ", " + op1;
        }
        return res;
        break;
    case IR_ADD:
        /* t4 := t5 + t6 */
        left = getRegOfVar(cur_IR->u.op3.result->var_str);
        op1 = getRegOfVar(cur_IR->u.op3.op1->var_str);
        op2 = getRegOfVar(cur_IR->u.op3.op2->var_str);
        res = "add " + left + ", " + op1 + ", " + op2;
        return res;
        break;
    case IR_SUB:
        /* t4 := t5 - t6 */
        left = getRegOfVar(cur_IR->u.op3.result->var_str);
        op1 = getRegOfVar(cur_IR->u.op3.op1->var_str);
        op2 = getRegOfVar(cur_IR->u.op3.op2->var_str);
        res = "sub " + left + ", " + op1 + ", " + op2;
        return res;
        break;
    case IR_MUL:
        /* t4 := t5 * t6 */
        left = getRegOfVar(cur_IR->u.op3.result->var_str);
        op1 = getRegOfVar(cur_IR->u.op3.op1->var_str);
        op2 = getRegOfVar(cur_IR->u.op3.op2->var_str);
        res = "mult " + left + ", " + op1 + ", " + op2;
        return res;
        break;
    case IR_DIV:
        /* t4 := t5 / t6 */
        left = getRegOfVar(cur_IR->u.op3.result->var_str);
        op1 = getRegOfVar(cur_IR->u.op3.op1->var_str);
        op2 = getRegOfVar(cur_IR->u.op3.op2->var_str);
        res = "div " + left + ", " + op1 + ", " + op2;
        return res;
        break;
    case IR_GOTO:
        /* GOTO v4 */
        break;
    case IR_FUNC:
        /* FUNCTION main : */
        currentFuncName = cur_IR->u.func.func_name->var_str;
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
        size = mips32_getfunc_size(cur_IR->u.call.func->var_str);
        //pre
        oss_start << "addi $sp, $sp, -" << size;
        mips_file << oss_start.str() << endl;
        oss_start.str("");
        //mid
        mips_file << "jal " + cur_IR->u.call.func->var_str << endl;
        //end
        oss_end << "addi $sp, $sp, " << size;
        mips_file << oss_end.str() << endl;
        oss_end.str("");
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
        return ir_Operand_init(IR_CONSTANT, (opr_s.substr(1)));
    } else if (opr_s[0] == '*') {
        return ir_Operand_init(IR_DE_REF,   (opr_s.substr(1)));
    } else if (opr_s[0] == '&') {
        return ir_Operand_init(IR_GET_ADDR, (opr_s.substr(1)));
    } else {
        return ir_Operand_init(IR_VARIABLE, (opr_s));
    }
}

void print_vec(vector<string>& ir_vec) {
    for (auto& i : ir_vec) {
        cout << i << " ";
    }
    cout << endl;
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