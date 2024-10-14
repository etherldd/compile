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

map<string, map<string, int>> FuncVarOffsetTable;
string currentFuncName = "";
RegisterAllocator* regAllocator = nullptr;

/*only used in mips_gene.cpp as helper function*/
map<string, int>    getfunc_table(string func);
int                 getfunc_size(string func);
string              getRegWithSpill(const string& var);

map<string, int> getfunc_table(string func) {
    return FuncVarOffsetTable.count(func) ? FuncVarOffsetTable[func] : map<string, int>();
}

int getfunc_size(string func) {
    if (FuncVarOffsetTable.count(func) == 0) return 0;
    int maxOffset = 0;
    for (const auto& pair : FuncVarOffsetTable[func]) {
        maxOffset = max(maxOffset, pair.second);
    }
    return maxOffset + 4;
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


/*for mips32_gene user*/


void mips32_scan_and_set_table() {
    ir_file.open(ir_file_name);
    int cur_offset = 0;
    while (true) {
        string cur_line = get_next_line();
        if (cur_line.empty()) break;
        
        IR* cur_IR = irStringToIR(cur_line);
        if (cur_IR->code_kind == IR_FUNC) {
            currentFuncName = cur_IR->u.func.func_name->var_str;
            FuncVarOffsetTable[currentFuncName] = map<string, int>();
            cur_offset = 0;
        }
        
        Operand result = nullptr;
        switch (cur_IR->code_kind) {
            case IR_ASSIGN: result = cur_IR->u.assign.left; break;
            case IR_ADD:
            case IR_SUB:
            case IR_MUL:
            case IR_DIV: result = cur_IR->u.op3.result; break;
            case IR_CALL: result = cur_IR->u.call.ret; break;
            default: continue;
        }
        
        if (result && FuncVarOffsetTable[currentFuncName].count(result->var_str) == 0) {
            FuncVarOffsetTable[currentFuncName][result->var_str] = cur_offset;
            cur_offset += 4;
        }
    }
    regAllocator = new RegisterAllocator(FuncVarOffsetTable);
    ir_file.close();
}

void mips32_gene_init() {
    mips_file.open(mips_file_name, ios::trunc);
    FuncVarOffsetTable.clear();
}

void mips32_gene_free() {
    mips_file.close();
    FuncVarOffsetTable.clear();
}

string mips32_gene_target_code(string ir_line) {
    IR* cur_IR = irStringToIR(ir_line);
    ostringstream oss;
    string left, op1, op2;

    switch (cur_IR->code_kind) {
        case IR_ASSIGN:
            left = getRegWithSpill(cur_IR->u.assign.left->var_str);
            if (cur_IR->u.assign.right->opr_kind == IR_CONSTANT) {
                oss << "    li " << left << ", " << cur_IR->u.assign.right->var_str;
            } else if (cur_IR->u.assign.right->opr_kind == IR_VARIABLE) {
                op2 = getRegWithSpill(cur_IR->u.assign.right->var_str);
                oss << "    move " << left << ", " << op2;
            } else if (cur_IR->u.assign.right->opr_kind == IR_GET_ADDR) {
                int cur_offset = getfunc_table(currentFuncName)[cur_IR->u.assign.right->var_str];
                oss << "    sub " << left << ", $sp, " << cur_offset + 4;
            } else {
                op2 = getRegWithSpill(cur_IR->u.assign.right->var_str);
                oss << "    lw " << left << ", " << op2;
            }
            break;
        case IR_ADD:
        case IR_SUB:
        case IR_MUL:
        case IR_DIV:
            left = getRegWithSpill(cur_IR->u.op3.result->var_str);
            op1 = getRegWithSpill(cur_IR->u.op3.op1->var_str);
            op2 = getRegWithSpill(cur_IR->u.op3.op2->var_str);
            oss << "    " << (cur_IR->code_kind == IR_ADD ? "add" : 
                              cur_IR->code_kind == IR_SUB ? "sub" : 
                              cur_IR->code_kind == IR_MUL ? "mult" : "div")
                << " " << left << ", " << op1 << ", " << op2;
            break;
        case IR_GOTO:
            oss << "    j " << cur_IR->u.goto_st.place->var_str;
            break;
        case IR_FUNC:
            currentFuncName = cur_IR->u.func.func_name->var_str;
            regAllocator->setCurrentFunction(currentFuncName);
            oss << currentFuncName << ":\n"
                << "    addi $sp, $sp, -" << getfunc_size(currentFuncName) << "\n"
                << "    sw $ra, 0($sp)";
            break;
        case IR_LABEL:
            oss << cur_IR->u.label.label_name->var_str << ":";
            break;
        case IR_IF:
            op1 = getRegWithSpill(cur_IR->u.if_st.op1->var_str);
            op2 = getRegWithSpill(cur_IR->u.if_st.op2->var_str);
            oss << "    b" << (strcmp(cur_IR->u.if_st.op, "<") == 0 ? "lt" :
                               strcmp(cur_IR->u.if_st.op, ">") == 0 ? "gt" :
                               strcmp(cur_IR->u.if_st.op, "<=") == 0 ? "le" :
                               strcmp(cur_IR->u.if_st.op, ">=") == 0 ? "ge" :
                               strcmp(cur_IR->u.if_st.op, "==") == 0 ? "eq" : "ne")
                << " " << op1 << ", " << op2 << ", " << cur_IR->u.if_st.desti->var_str;
            break;
        case IR_RETURN:
            op1 = getRegWithSpill(cur_IR->u.return_st.val->var_str);
            oss << "    move $v0, " << op1 << "\n"
                << "    lw $ra, 0($sp)\n"
                << "    addi $sp, $sp, " << getfunc_size(currentFuncName) << "\n"
                << "    jr $ra";
            break;
        case IR_ARG:
            op1 = getRegWithSpill(cur_IR->u.arg.val->var_str);
            oss << "    addi $sp, $sp, -4\n"
                << "    sw " << op1 << ", 0($sp)";
            break;
        case IR_CALL:
            oss << "    addi $sp, $sp, -" << getfunc_size(cur_IR->u.call.func->var_str) << "\n"
                << "    jal " << cur_IR->u.call.func->var_str << "\n"
                << "    addi $sp, $sp, " << getfunc_size(cur_IR->u.call.func->var_str);
            break;
        case IR_READ:
            left = getRegWithSpill(cur_IR->u.read.val->var_str);
            oss << "    jal read\n"
                << "    move " << left << ", $v0";
            break;
        case IR_WRITE:
            op1 = getRegWithSpill(cur_IR->u.write.val->var_str);
            oss << "    move $a0, " << op1 << "\n"
                << "    jal write";
            break;
    }
    return oss.str();
}

string mips32_generate_predefined_functions() {
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
