#include "mips_gene.hpp"
#include "IR_list.hpp"
#include <sstream>
using namespace std;

string ir_file_name = "./gene.ir";
string mips_file_name = "./gene.mips";
fstream ir_file;
ofstream mips_file;

int main() {
    mips32_gene_init();
    mips32_scan_and_set_table();
    ir_file.open(ir_file_name);
    
    while (true) {
        string cur_line = get_next_line();
        if (cur_line == "") {
            break;
        } 
        string mips_line = gene_target_code(cur_line);
        mips_file << mips_line << endl;
    }
    
    ir_file.close();
    mips32_gene_free();
    return 0;
}