#include "mips_gene.hpp"
#include "IR_list.hpp"
using namespace std;

string ir_file_name = "./gene.ir";
string mips_file_name = "./gene.mips";
fstream ir_file;
ofstream mips_file;

int main() {
    mips32_gene_init();
    while (true) {
        string cur_line = get_next_line();
        if (cur_line == "") {
            break;
        } 
        string mips_line = gene_target_code(cur_line);
        mips_file << cur_line << endl;
    }
    mips32_gene_free();
    return 0;
}