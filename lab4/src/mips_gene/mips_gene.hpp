#ifndef IR_MIPS_GENE
#define IR_MIPS_GENE

#include <bits/stdc++.h>
#include "IR_list.hpp"
using namespace std;

/*Part 1: read the ir file and generate mips code*/

void mips32_gene_init(); //init
void mips32_gene_free(); //free
string get_next_line();
string gene_target_code(string ir_line); //turn ir_code to mips_code


/*Part 2: The procedure of generating*/
long getRegOfVar_noNumberConstrain(string var);
vector<string> ir_split(string s);
Operand oprStringToOpr(string opr_s);
IR* irStringToIR(string ir_s);


#endif