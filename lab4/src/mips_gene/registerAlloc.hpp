#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>

class RegisterAllocator {
private:
    std::vector<std::string> registers = {"$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7"};
    std::unordered_map<std::string, std::string> varToReg;
    std::unordered_map<std::string, bool> regUsed;
    std::unordered_map<std::string, int> varToOffset;
    std::string currentFunction;
    int lastUsedReg = -1;

public:
    RegisterAllocator(const map<string, map<string, int>>& offsetTable) {
        for (const auto& reg : registers) {
            regUsed[reg] = false;
        }
        for (const auto& func : offsetTable) {
            for (const auto& var : func.second) {
                varToOffset[func.first + ":" + var.first] = var.second;
            }
        }
    }

    std::string allocateRegister(const std::string& var, std::ostringstream& spillCode) {
        if (varToReg.find(var) != varToReg.end()) {
            return varToReg[var];
        }

        for (const auto& reg : registers) {
            if (!regUsed[reg]) {
                regUsed[reg] = true;
                varToReg[var] = reg;
                return reg;
            }
        }

        // All registers are used, need to spill
        lastUsedReg = (lastUsedReg + 1) % registers.size();
        std::string spilledReg = registers[lastUsedReg];
        std::string spilledVar = "";
        for (const auto& pair : varToReg) {
            if (pair.second == spilledReg) {
                spilledVar = pair.first;
                break;
            }
        }

        // Generate spill code
        int offset = varToOffset[currentFunction + ":" + spilledVar];
        spillCode << "    sw " << spilledReg << ", " << offset << "($fp)" << std::endl;

        varToReg.erase(spilledVar);
        varToReg[var] = spilledReg;
        return spilledReg;
    }

    void freeRegister(const std::string& var) {
        if (varToReg.find(var) != varToReg.end()) {
            regUsed[varToReg[var]] = false;
            varToReg.erase(var);
        }
    }

    std::string getRegister(const std::string& var, std::ostringstream& spillCode) {
        return allocateRegister(var, spillCode);
    }

    void setCurrentFunction(const std::string& funcName) {
        currentFunction = funcName;
    }

    std::string loadFromStack(const std::string& var) {
        int offset = varToOffset[currentFunction + ":" + var];
        std::ostringstream spillCode;
        std::string reg = allocateRegister(var, spillCode);
        std::ostringstream result;
        if (!spillCode.str().empty()) {
            result << spillCode.str() << std::endl;
        }
        result << "lw " << reg << ", " << std::to_string(offset) << "($fp)";
        return result.str();
    }
};
