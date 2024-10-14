#include "mips_gene.hpp"
#include "IR_list.hpp"
#include <map>
#include <sstream>
#include <vector>
#include <unordered_map>

extern string ir_file_name;
extern string mips_file_name;
extern fstream ir_file;
extern ofstream mips_file;

map<string, map<string, int>> FuncVarOffsetTable;  // Mapping from function name to (variable name, offset) mapping
int globalRegCounter = 1;  // Global register counter
string currentFuncName = "";  // Current function being processed
RegisterAllocator* regAllocator = nullptr;

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
    int cur_offset = 0;
    ir_file.open(ir_file_name);
    string cur_scan_funcname = "";
    while (true) {
        string cur_line = get_next_line();
        if (cur_line == "") {
            break;
        } 
        IR* cur_IR = irStringToIR(cur_line);
        if (cur_IR->code_kind == IR_FUNC) {
            currentFuncName = cur_IR->u.func.func_name->var_str;
            FuncVarOffsetTable[currentFuncName] = map<string, int>();
            cur_offset = 0;
        }
        switch (cur_IR->code_kind)
        {
            case IR_ASSIGN:
                /* a = b */
                if (FuncVarOffsetTable[currentFuncName].find(cur_IR->u.assign.left->var_str) == FuncVarOffsetTable[currentFuncName].end()) {
                    FuncVarOffsetTable[currentFuncName][cur_IR->u.assign.left->var_str] = cur_offset;
                    cur_offset += 4;
                }
                break;
            case IR_ADD:
                /* t4 := t5 + t6 */
                if (FuncVarOffsetTable[currentFuncName].find(cur_IR->u.op3.result->var_str) == FuncVarOffsetTable[currentFuncName].end()) {
                    FuncVarOffsetTable[currentFuncName][cur_IR->u.op3.result->var_str] = cur_offset;
                    cur_offset += 4;
                }
                break;
            case IR_SUB:
                /* t4 := t5 - t6 */
                if (FuncVarOffsetTable[currentFuncName].find(cur_IR->u.op3.result->var_str) == FuncVarOffsetTable[currentFuncName].end()) {
                    FuncVarOffsetTable[currentFuncName][cur_IR->u.op3.result->var_str] = cur_offset;
                    cur_offset += 4;
                }
                break;
            case IR_MUL:
                /* t4 := t5 * t6 */
                if (FuncVarOffsetTable[currentFuncName].find(cur_IR->u.op3.result->var_str) == FuncVarOffsetTable[currentFuncName].end()) {
                    FuncVarOffsetTable[currentFuncName][cur_IR->u.op3.result->var_str] = cur_offset;
                    cur_offset += 4;
                }
                break;
            case IR_DIV:
                /* t4 := t5 / t6 */
                if (FuncVarOffsetTable[currentFuncName].find(cur_IR->u.op3.result->var_str) == FuncVarOffsetTable[currentFuncName].end()) {
                    FuncVarOffsetTable[currentFuncName][cur_IR->u.op3.result->var_str] = cur_offset;
                    cur_offset += 4;
                }
                break;
            case IR_CALL:
                /* t6 := CALL factorial */
                if (FuncVarOffsetTable[currentFuncName].find(cur_IR->u.call.ret->var_str) == FuncVarOffsetTable[currentFuncName].end()) {
                    FuncVarOffsetTable[currentFuncName][cur_IR->u.call.ret->var_str] = cur_offset;
                    cur_offset += 4;
                }
                break;
            default:
                break;
        }
    }
    regAllocator = new RegisterAllocator(FuncVarOffsetTable);
    ir_file.close();
}

void mips32_gene_init() {
    mips_file.open(mips_file_name, ios::trunc);
    FuncVarOffsetTable = map<string, map<string, int>>();
}

void mips32_gene_free() {
    //1. close file
    mips_file.close();
    //2. free mem
    FuncVarOffsetTable.clear();
}

string get_next_line() {
    string ret;
    getline(ir_file, ret);
    return ret;
}

string getRegWithSpill(const string& var) {
    ostringstream spillCode;
    string reg = regAllocator->getRegister(var, spillCode);
    if (!spillCode.str().empty()) {
        mips_file << spillCode.str();
    }
    return reg;
}
// enum { IR_ASSIGN, IR_ADD, IR_SUB, IR_MUL, IR_DIV, IR_GOTO, IR_FUNC, 
//         IR_LABEL, IR_IF, IR_RETURN, IR_DEC, IR_ARG, 
//         IR_CALL, IR_PARAM, IR_READ, IR_WRITE};
string mips_gene_target_code(string ir_line) {
    IR*     cur_IR = irStringToIR(ir_line);
    string  res;
    string  left, op1, op2, right;
    ostringstream oss;
    
    int     size;

    // 将所有可能用到的变量声明移到switch语句之前
    const char* condition;
    string jump_label;

    

    switch (cur_IR->code_kind)
    {
    case IR_ASSIGN:
        /* t0 := value  */
        left = getRegWithSpill(cur_IR->u.assign.left->var_str);
        if (cur_IR->u.assign.right->opr_kind == IR_CONSTANT) {
            res = "    li " + left + ", " + cur_IR->u.assign.right->var_str;
        } else if (cur_IR->u.assign.right->opr_kind == IR_VARIABLE) {
            op2 = getRegWithSpill(cur_IR->u.assign.right->var_str);
            res = "    move " + left + ", " + op2;
        } else if (cur_IR->u.assign.right->opr_kind == IR_GET_ADDR) {
            int cur_offset = mips32_getfunc_table(currentFuncName)[cur_IR->u.assign.right->var_str];
            oss << "    sub " + left + ", $sp, " << cur_offset + 4;
            res = oss.str();
            oss.str("");
        } else {//IR_DE_REF
            op1 = cur_IR->u.assign.right->var_str;
            res =  "    lw " + left + ", " + op1;
        }
        return res;
    case IR_ADD:
        /* t4 := t5 + t6 */
        left = getRegWithSpill(cur_IR->u.op3.result->var_str);
        op1 = getRegWithSpill(cur_IR->u.op3.op1->var_str);
        op2 = getRegWithSpill(cur_IR->u.op3.op2->var_str);
        res = "    add " + left + ", " + op1 + ", " + op2;
        return res;
    case IR_SUB:
        /* t4 := t5 - t6 */
        left = getRegWithSpill(cur_IR->u.op3.result->var_str);
        op1 = getRegWithSpill(cur_IR->u.op3.op1->var_str);
        op2 = getRegWithSpill(cur_IR->u.op3.op2->var_str);
        res = "    sub " + left + ", " + op1 + ", " + op2;
        return res;
    case IR_MUL:
        /* t4 := t5 * t6 */
        left = getRegWithSpill(cur_IR->u.op3.result->var_str);
        op1 = getRegWithSpill(cur_IR->u.op3.op1->var_str);
        op2 = getRegWithSpill(cur_IR->u.op3.op2->var_str);
        res = "    mult " + left + ", " + op1 + ", " + op2;
        return res;
    case IR_DIV:
        /* t4 := t5 / t6 */
        left = getRegWithSpill(cur_IR->u.op3.result->var_str);
        op1 = getRegWithSpill(cur_IR->u.op3.op1->var_str);
        op2 = getRegWithSpill(cur_IR->u.op3.op2->var_str);
        res = "    div " + left + ", " + op1 + ", " + op2;
        return res;
    case IR_GOTO:
        /* GOTO v4 */
        oss << "    j " << cur_IR->u.goto_st.place->var_str;
        res = oss.str();
        return res;
    case IR_FUNC:
        /* FUNCTION main : */
        currentFuncName = cur_IR->u.func.func_name->var_str;
        regAllocator->setCurrentFunction(currentFuncName);
        oss << cur_IR->u.func.func_name->var_str << ":\n";
        oss << "    addi $sp, $sp, -" << mips32_getfunc_size(currentFuncName) << "\n";
        oss << "    sw $ra, 0($sp)";
        res = oss.str();
        return res;
    case IR_LABEL:
        /* LABEL v3 : */
        oss << cur_IR->u.label.label_name->var_str << ":";
        res = oss.str();
        return res;
    case IR_IF:
        /* IF t0 < t1 GOTO v0 */
        op1 = getRegWithSpill(cur_IR->u.if_st.op1->var_str);
        op2 = getRegWithSpill(cur_IR->u.if_st.op2->var_str);
        condition = cur_IR->u.if_st.op;
        jump_label = cur_IR->u.if_st.desti->var_str;
        
        if (strcmp(condition, "<") == 0) {
            oss << "    blt " << op1 << ", " << op2 << ", " << jump_label;
        } else if (strcmp(condition, ">") == 0) {
            oss << "    bgt " << op1 << ", " << op2 << ", " << jump_label;
        } else if (strcmp(condition, "<=") == 0) {
            oss << "    ble " << op1 << ", " << op2 << ", " << jump_label;
        } else if (strcmp(condition, ">=") == 0) {
            oss << "    bge " << op1 << ", " << op2 << ", " << jump_label;
        } else if (strcmp(condition, "==") == 0) {
            oss << "    beq " << op1 << ", " << op2 << ", " << jump_label;
        } else if (strcmp(condition, "!=") == 0) {
            oss << "    bne " << op1 << ", " << op2 << ", " << jump_label;
        }
        res = oss.str();
        return res;
    case IR_RETURN:
        /* RETURN v15 */
        op1 = getRegWithSpill(cur_IR->u.return_st.val->var_str);
        oss << "    move $v0, " << op1 << "\n";
        oss << "    lw $ra, 0($sp)\n";
        oss << "    addi $sp, $sp, " << mips32_getfunc_size(currentFuncName) << "\n";
        oss << "    jr $ra";
        res = oss.str();
        return res;
    case IR_DEC:
        /* DEC src_tmp 12 */
        break;
    case IR_ARG:
        /* ARG t7 */
        op1 = getRegWithSpill(cur_IR->u.arg.val->var_str);
        oss << "    addi $sp, $sp, -4\n";
        oss << "    sw " << op1 << ", 0($sp)";
        res = oss.str();
        return res;
    case IR_CALL:
        /* t6 := CALL factorial */
        size = mips32_getfunc_size(cur_IR->u.call.func->var_str);
        //pre
        oss << "    addi $sp, $sp, -" << size;
        mips_file << oss.str() << endl;
        oss.str("");
        //mid
        mips_file << "    jal " + cur_IR->u.call.func->var_str << endl;
        //end
        oss << "    addi $sp, $sp, " << size;
        mips_file << oss.str() << endl;
        oss.str("");
        break;
    case IR_PARAM:
        /* PARAM m */
        break;
    case IR_READ:
        /* READ t39 */
        left = getRegWithSpill(cur_IR->u.read.val->var_str);
        oss << "    jal read\n";
        oss << "    move " << left << ", $v0";
        res = oss.str();
        return res;
    case IR_WRITE:
        /* WRITE t39 */
        right = getRegWithSpill(cur_IR->u.write.val->var_str);
        oss << "    move $a0, " << right << "\n";
        oss << "    jal write";
        res = oss.str();
        return res;
    default:
        return "";
    }
    return res;
}



void print_vec(vector<string>& ir_vec) {
    for (auto& i : ir_vec) {
        cout << i << " ";
    }
    cout << endl;
}


string generate_predefined_functions() {
    return R"(
.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
read:
    li $v0, 4
    la $a0, _prompt
    syscall
    li $v0, 5
    syscall
    jr $ra

write:
    li $v0, 1
    syscall
    li $v0, 4
    la $a0, _ret
    syscall
    move $v0, $0
    jr $ra

)";
}

