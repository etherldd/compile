#ifndef IR_MIPS_GENE
#define IR_MIPS_GENE

#include <bits/stdc++.h>
#include "IR_list.hpp"
#include "registerAlloc.hpp"
using namespace std;

/*Part 1: read the ir file and generate mips code*/
void        mips32_scan_and_set_table(); //cal size and remind offset
void        mips32_gene_init(); //init
void        mips32_gene_free(); //free
string      get_next_line();
string      mips_gene_target_code(string ir_line); //turn ir_code to mips_code

//helper for func table
map<string, int>    mips32_getfunc_table(string func);
int                 mips32_getfunc_size(string func);


/*Part 2: The procedure of generating*/
string          generate_predefined_functions();
long            getRegOfVar_noNumberConstrain(string var);
string          getRegOfVar(string var);




#endif