%define parse.error verbose
%{
    #include <stdio.h>
    #include "lex.yy.c"
    void yyerror(const char* msg) { 
        //printf("\tError type B at Line %d: %s\n", yylineno, msg);
    }
    char* nontokens[] = {"Program", "Def", "ExtDefList", "DefList", "ExtDef", "Specifier", "Dec", "ExtDecList", "DecList",
                        "FunDec", "CompSt", "VarDec", "StructSpecifier", "OptTag", 
                        "Tag", "VarList", "ParamDec", "StmtList", "Stmt", 
                        "Exp", "Args", "ERROR"};
    enum {_Program, _Def, _ExtDefList, _DefList, _ExtDef, _Specifier, _Dec, _ExtDecList, _DecList,
            _FunDec, _CompSt, _VarDec, _StructSpecifier, _OptTag, 
            _Tag, _VarList, _ParamDec, _StmtList, _Stmt, 
            _Exp, _Args, _ERROR};
    #include "Sanalysis.h"

    Snode* final_tree = NULL;
    int isError = 0;
    unsigned int max_child_num = 10;

    Snode* node_ofNONtoken(int line, unsigned int token_num) {
        Snode* ret = malloc(sizeof(Snode));
        ret->childs = NULL;
        ret->childs_num = 0;
        ret->line = line;
        ret->sname = nontokens[token_num];
        ret->sval = NULL;
        ret->isRight = 0;
        return ret;
    }

    void add_child(Snode* n, Snode* child) {
        if (n->childs == NULL) {
            n->childs = malloc(sizeof(Snode*) * max_child_num);
        }
        n->childs[n->childs_num] = child;
        n->childs_num++;
    }

%}

%union{
    Snode* type_node;
}
%token <type_node> SEMI COMMA ASSIGNOP RELOP PLUS MINUS STAR DIV AND OR DOT NOT TYPE LP RP LB RB LC RC STRUCT RETURN IF ELSE WHILE ID INT FLOAT
%type <type_node> Program Def ExtDefList DefList ExtDef Specifier Dec ExtDecList DecList FunDec CompSt VarDec StructSpecifier OptTag Tag VarList ParamDec StmtList Stmt Exp Args
%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%left NOT
%left LP RP
%left LB RB
%left DOT
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%
Program : ExtDefList {
    final_tree = node_ofNONtoken($1->line, _Program);
    $$ = final_tree;
    add_child($$, $1);
    if(!isError && !flexError) {
        //psn(final_tree);
        Analysis(final_tree);
    }
    delete_s_recu(final_tree);
};
ExtDefList :  /* empty */{$$ = NULL;}
 | ExtDef ExtDefList {$$ = node_ofNONtoken($1->line, _ExtDefList);add_child($$, $1);add_child($$, $2);}
 | error ExtDefList {isError = 1;$$ = node_ofNONtoken($2->line, _ExtDefList);add_child($$, $2);}
 ;
ExtDef : Specifier ExtDecList SEMI {$$ = node_ofNONtoken($1->line, _ExtDef);add_child($$, $1);add_child($$, $2);add_child($$, $3);}
 | error ExtDecList SEMI {isError = 1;$$ = node_ofNONtoken($2->line, _ERROR);add_child($$, $2);add_child($$, $3);printf("Error type B at Line %d: Illegal type specifier(in global).\n", $2->line);}
 | Specifier ExtDecList error SEMI {isError = 1;$$ = node_ofNONtoken($1->line, _ERROR);add_child($$, $1);add_child($$, $2);add_child($$, $4);printf("Error type B at Line %d: Global variable cannot have initializer.\n", $1->line);}
 | Specifier SEMI {$$ = node_ofNONtoken($1->line, _ExtDef);add_child($$, $1);add_child($$, $2);}
 | Specifier FunDec CompSt {$$ = node_ofNONtoken($1->line, _ExtDef);add_child($$, $1);add_child($$, $2);add_child($$, $3);}
 ;
ExtDecList : VarDec {$$ = node_ofNONtoken($1->line, _ExtDecList);add_child($$, $1);}
 | VarDec COMMA ExtDecList {$$ = node_ofNONtoken($1->line, _ExtDecList);add_child($$, $1);add_child($$, $2);add_child($$, $3);}
 ;
Specifier : TYPE  {$$ = node_ofNONtoken($1->line, _Specifier);add_child($$, $1);}
 | StructSpecifier {$$ = node_ofNONtoken($1->line, _Specifier);add_child($$, $1);}
 ;
StructSpecifier : STRUCT OptTag LC DefList RC {$$ = node_ofNONtoken($1->line, _StructSpecifier);add_child($$, $1);add_child($$, $2);add_child($$, $3);add_child($$, $4);}
 | STRUCT Tag {$$ = node_ofNONtoken($1->line, _StructSpecifier);add_child($$, $1);add_child($$, $2);}
 ;
OptTag : /* empty */ {$$ = NULL;}
 | ID {$$ = node_ofNONtoken($1->line, _OptTag);add_child($$, $1);}
 ;
Tag : ID {$$ = node_ofNONtoken($1->line, _Tag);add_child($$, $1);}
 ;
VarDec : ID {$$ = node_ofNONtoken($1->line, _VarDec);add_child($$, $1);}
 | VarDec LB INT RB {$$ = node_ofNONtoken($1->line, _VarDec);add_child($$, $1);add_child($$, $2);add_child($$, $3);add_child($$, $4);}
 | VarDec LB error {isError = 1;$$ = node_ofNONtoken($1->line, _ERROR);add_child($$, $1);add_child($$, $2);printf("Error type B at Line %d: Illegal input between [ and ] or no ].\n", $1->line);}
 ;
FunDec : ID LP VarList RP {$$ = node_ofNONtoken($1->line, _FunDec);add_child($$, $1);add_child($$, $2);add_child($$, $3);add_child($$, $4);}
 | ID LP error RP {isError = 1;$$ = node_ofNONtoken($1->line, _ERROR);add_child($$, $1);add_child($$, $2);add_child($$, $4);printf("Error type B at Line %d: Illegal function parameters format\n", $1->line);}
 | ID LP RP {$$ = node_ofNONtoken($1->line, _FunDec);add_child($$, $1);add_child($$, $2);add_child($$, $3);}
 ;
VarList : ParamDec COMMA VarList {$$ = node_ofNONtoken($1->line, _VarList);add_child($$, $1);add_child($$, $2);add_child($$, $3);}
 | ParamDec {$$ = node_ofNONtoken($1->line, _VarList);add_child($$, $1);}
 ;
ParamDec : Specifier VarDec {$$ = node_ofNONtoken($1->line, _ParamDec);add_child($$, $1);add_child($$, $2);}
 ;
CompSt : LC DefList StmtList RC {$$ = node_ofNONtoken($1->line, _CompSt);add_child($$, $1);add_child($$, $2);add_child($$, $3);add_child($$, $4);}
 | LC DefList StmtList error {isError = 1;$$ = node_ofNONtoken($1->line, _ERROR);add_child($$, $1);add_child($$, $2);add_child($$, $3);printf("Error type B at Line %d: Expected }.\n", $1->line);}
 ;
StmtList : /* empty */ {$$ = NULL;}
 | Stmt StmtList {$$ = node_ofNONtoken($1->line, _StmtList);add_child($$, $1);add_child($$, $2);}
 | error StmtList {isError = 1;$$ = node_ofNONtoken($2->line, _StmtList);add_child($$, $2);}
 ;
Stmt : Exp SEMI {$$ = node_ofNONtoken($1->line, _Stmt);add_child($$, $1);add_child($$, $2);}
 | CompSt {$$ = node_ofNONtoken($1->line, _Stmt);add_child($$, $1);}
 | RETURN Exp SEMI {$$ = node_ofNONtoken($1->line, _Stmt);add_child($$, $1);add_child($$, $2);add_child($$, $3);}
 | RETURN error SEMI {isError = 1;$$ = node_ofNONtoken($1->line, _ERROR);add_child($$, $1);add_child($$, $3);printf("Error type B at Line %d: Expect an Exp between return and ;\n", $1->line);}
 | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE {$$ = node_ofNONtoken($1->line, _Stmt);add_child($$, $1);add_child($$, $2);add_child($$, $3);add_child($$, $4);add_child($$, $5);}
 | IF LP Exp RP Stmt ELSE Stmt {
    $$ = node_ofNONtoken($1->line, _Stmt);
    add_child($$, $1);add_child($$, $2);add_child($$, $3);add_child($$, $4);add_child($$, $5);
    add_child($$, $6);add_child($$, $7);
    //psn($3);
 }
 | IF LP Exp RP error ELSE Stmt {
    isError = 1;$$ = node_ofNONtoken($1->line, _ERROR);add_child($$, $1);add_child($$, $2);
    add_child($$, $3);add_child($$, $4);add_child($$, $6);add_child($$, $7);
    printf("Error type B at Line %d: Expect statement between 'if' and 'else'.\n", $1->line);
 }
 | WHILE LP Exp RP Stmt {$$ = node_ofNONtoken($1->line, _Stmt);add_child($$, $1);add_child($$, $2);add_child($$, $3);add_child($$, $4);add_child($$, $5);}
 | WHILE LP Exp error RP Stmt {isError = 1;$$ = node_ofNONtoken($1->line, _ERROR);add_child($$, $1);add_child($$, $2);add_child($$, $3);add_child($$, $5);add_child($$, $6);printf("Error type B at Line %d: Illegal 'while' condition.\n", $1->line);}
 | WHILE LP Exp RP error {isError = 1;$$ = node_ofNONtoken($1->line, _ERROR);add_child($$, $1);add_child($$, $2);add_child($$, $3);add_child($$, $4);printf("Error type B at Line %d: Expect statement after 'while' condition.\n", $1->line);}
 ;
DefList : /* empty */  {$$ = NULL;}
 | Def DefList {$$ = node_ofNONtoken($1->line, _DefList);add_child($$, $1);add_child($$, $2);}
 | error DefList {$$ = node_ofNONtoken($2->line, _DefList);add_child($$, $2);}
 ;
Def : Specifier DecList SEMI {$$ = node_ofNONtoken($1->line, _Def);add_child($$, $1);add_child($$, $2);add_child($$, $3);}
 | Specifier error SEMI {isError = 1;$$ = node_ofNONtoken($1->line, _ERROR);add_child($$, $1);add_child($$, $3);printf("Error type B at Line %d: Expect correct DecList input.\n", $1->line);}
 | error DecList SEMI {isError = 1;$$ = node_ofNONtoken($2->line, _ERROR);add_child($$, $2);add_child($$, $3);printf("Error type B at Line %d: Illegal type specifier(in a func).\n", $2->line);}
 ;
DecList : Dec {$$ = node_ofNONtoken($1->line, _DecList);add_child($$, $1);}
 | Dec COMMA DecList {$$ = node_ofNONtoken($1->line, _DecList);add_child($$, $1);add_child($$, $2);add_child($$, $3);}
 ;
Dec : VarDec {$$ = node_ofNONtoken($1->line, _Dec);add_child($$, $1);}
 | VarDec ASSIGNOP Exp {$$ = node_ofNONtoken($1->line, _Dec);add_child($$, $1);add_child($$, $2);add_child($$, $3);}
 | error ASSIGNOP Exp {isError = 1;$$ = node_ofNONtoken($2->line, _ERROR);add_child($$, $2);add_child($$, $3);printf("Error type B at Line %d: Illegal/no ID before \"=\".\n", $2->line);}
 | VarDec ASSIGNOP error {isError = 1;$$ = node_ofNONtoken($1->line, _ERROR);add_child($$, $1);add_child($$, $2);printf("Error type B at Line %d: Expected Exp after '='\n", $1->line);}
 ;
Exp : Exp ASSIGNOP Exp {$$ = node_ofNONtoken($1->line, _Exp);add_child($$, $1);add_child($$, $2);add_child($$, $3);
                            if ($1->isRight == 0) {
                                //isError = 1;
                                printf("Error type B at Line %d: Leftvalue can't be assigned\n", $1->line);
                            }
                        }
 | Exp AND   Exp  {$$ = node_ofNONtoken($1->line, _Exp);add_child($$, $1);add_child($$, $2);add_child($$, $3);}
 | Exp OR    Exp  {$$ = node_ofNONtoken($1->line, _Exp);add_child($$, $1);add_child($$, $2);add_child($$, $3);}
 | Exp RELOP Exp  {$$ = node_ofNONtoken($1->line, _Exp);add_child($$, $1);add_child($$, $2);add_child($$, $3);}
 | Exp PLUS  Exp  {$$ = node_ofNONtoken($1->line, _Exp);add_child($$, $1);add_child($$, $2);add_child($$, $3);}
 | Exp MINUS Exp  {$$ = node_ofNONtoken($1->line, _Exp);add_child($$, $1);add_child($$, $2);add_child($$, $3);}
 | Exp STAR  Exp  {$$ = node_ofNONtoken($1->line, _Exp);add_child($$, $1);add_child($$, $2);add_child($$, $3);}
 | Exp DIV   Exp  {$$ = node_ofNONtoken($1->line, _Exp);add_child($$, $1);add_child($$, $2);add_child($$, $3);}
 | Exp AND   error Exp {isError = 1;$$ = node_ofNONtoken($1->line, _ERROR);add_child($$, $1);add_child($$, $2);add_child($$, $4);printf("Error type B at Line %d: Error OP input between 2 Exps.\n", $1->line);}
 | Exp OR    error Exp {isError = 1;$$ = node_ofNONtoken($1->line, _ERROR);add_child($$, $1);add_child($$, $2);add_child($$, $4);printf("Error type B at Line %d: Error OP input between 2 Exps.\n", $1->line);}
 | Exp RELOP error Exp {isError = 1;$$ = node_ofNONtoken($1->line, _ERROR);add_child($$, $1);add_child($$, $2);add_child($$, $4);printf("Error type B at Line %d: Error OP input between 2 Exps.\n", $1->line);}
 | Exp PLUS  error Exp {isError = 1;$$ = node_ofNONtoken($1->line, _ERROR);add_child($$, $1);add_child($$, $2);add_child($$, $4);printf("Error type B at Line %d: Error OP input between 2 Exps.\n", $1->line);} 
 | Exp MINUS error Exp {isError = 1;$$ = node_ofNONtoken($1->line, _ERROR);add_child($$, $1);add_child($$, $2);add_child($$, $4);printf("Error type B at Line %d: Error OP input between 2 Exps.\n", $1->line);}
 | Exp STAR  error Exp {isError = 1;$$ = node_ofNONtoken($1->line, _ERROR);add_child($$, $1);add_child($$, $2);add_child($$, $4);printf("Error type B at Line %d: Error OP input between 2 Exps.\n", $1->line);}
 | Exp DIV   error Exp {isError = 1;$$ = node_ofNONtoken($1->line, _ERROR);add_child($$, $1);add_child($$, $2);add_child($$, $4);printf("Error type B at Line %d: Error OP input between 2 Exps.\n", $1->line);}
 | LP   Exp  RP {$$ = node_ofNONtoken($1->line, _Exp);add_child($$, $1);add_child($$, $2);add_child($$, $3);}
 | MINUS Exp    {$$ = node_ofNONtoken($1->line, _Exp);add_child($$, $1);add_child($$, $2);}
 | NOT   Exp    {$$ = node_ofNONtoken($1->line, _Exp);add_child($$, $1);add_child($$, $2);}
 | ID  LP Args RP   {$$ = node_ofNONtoken($1->line, _Exp);add_child($$, $1);add_child($$, $2);add_child($$, $3);add_child($$, $4);}
 | ID  LP  RP       {$$ = node_ofNONtoken($1->line, _Exp);add_child($$, $1);add_child($$, $2);add_child($$, $3);}
 | ID  LP  error    {isError = 1;$$ = node_ofNONtoken($1->line, _ERROR);add_child($$, $1);add_child($$, $2);printf("Error type B at Line %d: Illegal input between ( and ) or no ).\n", $2->line);}
 | Exp LB  Exp  RB  {$$ = node_ofNONtoken($1->line, _Exp);add_child($$, $1);add_child($$, $2);add_child($$, $3);add_child($$, $4);$$->isRight = 1;}
 | Exp LB  error    {isError = 1;$$ = node_ofNONtoken($1->line, _ERROR);add_child($$, $1);add_child($$, $2);/*add_child($$, $3);*/printf("Error type B at Line %d: Illegal input between [ and ] or no ].\n", $2->line);}
 | Exp DOT ID       {$$ = node_ofNONtoken($1->line, _Exp);add_child($$, $1);add_child($$, $2);add_child($$, $3);$$->isRight = 1;}
 | ID               {$$ = node_ofNONtoken($1->line, _Exp);add_child($$, $1);$$->isRight = 1;}
 | INT              {$$ = node_ofNONtoken($1->line, _Exp);add_child($$, $1);}
 | FLOAT            {$$ = node_ofNONtoken($1->line, _Exp);add_child($$, $1);}
 ;
Args : Exp COMMA Args {$$ = node_ofNONtoken($1->line, _Args);add_child($$, $1);add_child($$, $2);add_child($$, $3);}
 | Exp {$$ = node_ofNONtoken($1->line, _Args);add_child($$, $1);}
 ;
%%
/* | VarDec ASSIGNOP Exp error {isError = 1;$$ = node_ofNONtoken($1->line, _ERROR);add_child($$, $1);add_child($$, $2);add_child($$, $3);printf("Error type B at Line %d: Illegal assigned value\n", $1->line);}
 | Exp LB Exp error RB {isError = 1;$$ = node_ofNONtoken($1->line, _ERROR);add_child($$, $1);add_child($$, $2);add_child($$, $3);add_child($$, $5);printf("Error type B at Line %d: Illegal input between [ and ]4.\n", $2->line);}
 | Exp LB error RB {isError = 1;$$ = node_ofNONtoken($1->line, _ERROR);add_child($$, $1);add_child($$, $2);add_child($$, $4);printf("Error type B at Line %d: Illegal input between [ and ]3.\n", $2->line);}
 | ID LP error RP {isError = 1;$$ = node_ofNONtoken($1->line, _ERROR);add_child($$, $1);add_child($$, $2);add_child($$, $4);printf("Error type B at Line %d: Illegal input between ( and ).\n", $2->line);}
*/
