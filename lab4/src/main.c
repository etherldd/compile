#include <stdio.h>
extern FILE* yyin;
extern unsigned int yylineno;
extern int yyparse (void);
extern int yyrestart (FILE* f);
char*  ir_filename = "./sample.ir";
int main(int argc, char** argv)
{
    if (argc <= 1) {
        printf("usage: ./parser <cmm_file_name> <ir_file_name>\n");
        return 1;
    }
    if (argc == 3) {ir_filename = argv[2];}
    FILE* f = fopen(argv[1], "r");
    if (!f){
        perror(argv[1]);
        return 1;
    }
    yylineno = 1;
    yyrestart(f);
    yyparse();
    return 0;
}
