#ifndef IR_MIPS_GENE
#define IR_MIPS_GENE

#include <bits/stdc++.h>
#include "IR_list.hpp"
#include "registerAlloc.hpp"
using namespace std;

/*for mips32_gene user*/
string      get_next_line();
void        mips32_gene_init(); 
void        mips32_gene_free(); 
void        mips32_scan_and_set_table(); 
string      mips32_generate_predefined_functions();
string      mips32_gene_target_code(string ir_line); 


#endif