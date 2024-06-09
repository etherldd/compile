%{
#include "sem.h"
#include "lex.yy.c" 
extern Node* syntax_tree;
%}
%union{Node* type_node;}
//终结符
%token <type_node> SEMI COMMA ASSIGNOP RELOP
%token <type_node> PLUS MINUS STAR DIV AND OR DOT NOT
%token <type_node> TYPE LP RP LB RB LC RC 
%token <type_node> STRUCT RETURN IF ELSE WHILE FLOAT INT ID
//非终结符
%type <type_node> Program ExtDefList ExtDef ExtDecList Specifier StructSpecifier 
%type <type_node> OptTag Tag VarDec FunDec VarList ParamDec CompSt StmtList Stmt
%type <type_node> DefList Def DecList Dec
%type <type_node> Exp Args
//优先级定义
%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right NOT
%left LP RP LB RB DOT
%nonassoc ELSE

%%

/*High-level Definitions*/
//全局变量以及函数定义，Program初始语法程序，整个函数；
//ExtDefList零个或多个ExtDef
//ExtDef全局变量、结构体、函数定义
Program : ExtDefList                          { syntax_tree=CreateUnterminalNode("Program",@$.first_line,$1); $$=syntax_tree; }
  ;
ExtDefList :                                  { $$=NULL;}
  | ExtDef ExtDefList                         { $$=CreateUnterminalNode("ExtDefList",@$.first_line,$1); AddChild($$,$2);}
  ;
ExtDef : Specifier ExtDecList SEMI            { $$=CreateUnterminalNode("ExtDef",@$.first_line,$1); AddChild($$,$2); AddChild($$,$3); }
  | Specifier SEMI                            { $$=CreateUnterminalNode("ExtDef",@$.first_line,$1); AddChild($$,$2);}
  | Specifier FunDec CompSt                   { $$=CreateUnterminalNode("ExtDef",@$.first_line,$1); AddChild($$,$2); AddChild($$,$3);}
  | Specifier ExtDecList error                { $$=NULL; Error("B",@2.last_line,"Expected ';'");}  //没有分号 ExtDef -> Specifier ExtDecList error | Specifier error | error SEMI
  | Specifier error                           { $$=NULL; Error("B",@1.last_line,"Expected ';'"); }  // 
  | error SEMI                                { $$=NULL; Error("B",@1.first_line,"Syntax error"); }  //仅有分号
  ;
ExtDecList : VarDec                           { $$=CreateUnterminalNode("ExtDecList",@$.first_line,$1);}
  | VarDec COMMA ExtDecList                   { $$=CreateUnterminalNode("ExtDecList",@$.first_line,$1); AddChild($$,$2); AddChild($$,$3); }
  | VarDec ExtDecList                         { $$=NULL; Error("B",@1.last_line,"Expected ','"); };  //无分号 ExtDecList -> VarDec ExtDecList  (Error)



/*Specifiers*/
//变量类型：基本类型、结构体
Specifier : TYPE                              { $$=CreateUnterminalNode("Specifier",@$.first_line,$1); }
  | StructSpecifier                           { $$=CreateUnterminalNode("Specifier",@$.first_line,$1); };
//StructSpecifier -> STRUCT OptTag DefList RC (Error)
StructSpecifier : STRUCT OptTag LC DefList RC { $$=CreateUnterminalNode("StructSpecifier",@$.first_line,$1);AddChild($$,$2);AddChild($$,$3);AddChild($$,$4);AddChild($$,$5);}
  | STRUCT Tag                                { $$=CreateUnterminalNode("StructSpecifier",@$.first_line,$1); AddChild($$,$2);}
  | STRUCT OptTag DefList RC                  { $$=NULL; Error("B",@2.last_line,"Expected '{'");}; // 缺少左括号 //StructSpecifier -> STRUCT OptTag DefList RC (Error)
OptTag :                                      { $$=NULL;}
  | ID                                        { $$=CreateUnterminalNode("OptTag",@$.first_line,$1);};
Tag : ID                                      { $$=CreateUnterminalNode("OptTag",@$.first_line,$1);};




/*Declarators*/
//变量定义、函数头定义
//VarDec -> VarDec INT RB | VarDec LB Exp RB | VarDec LB INT error (Error)
VarDec : ID                                   { $$=CreateUnterminalNode("VarDec",@$.first_line,$1);}
  | VarDec LB INT RB                          { $$=CreateUnterminalNode("VarDec",@$.first_line,$1); AddChild($$,$2); AddChild($$,$3); AddChild($$,$4);}
  | VarDec INT RB                             { $$=NULL; Error("B",@1.last_line,"Expected '['");}
  | VarDec LB Exp RB                          { $$=NULL; Error("B",@3.first_line,"Array initial capacity must be an integer constant"); } //不允许用一般表达式定义数组容量
  | VarDec LB INT error                       { $$=NULL; Error("B",@3.last_line,"Expected ']'");};

//FunDec -> ID VarList RP | ID LP VarList error | ID RP | ID LP error | LP VarList RP | ID LP error RP (Error)
FunDec : ID LP VarList RP                     { $$=CreateUnterminalNode("FunDec",@$.first_line,$1);AddChild($$,$2);AddChild($$,$3);AddChild($$,$4);}
  | ID LP RP                                  { $$=CreateUnterminalNode("FunDec",@$.first_line,$1);AddChild($$,$2);AddChild($$,$3);}
  | ID VarList RP                             { $$=NULL;Error("B",@1.last_line,"Expected '('");}
  | ID LP VarList error                       { $$=NULL;Error("B",@3.last_line,"Expected ')'");}
  | ID RP                                     { $$=NULL;Error("B",@1.last_line,"Expected '('");}
  | ID LP error                               { $$=NULL;Error("B",@2.last_line,"Expected ')'");} 
  | LP VarList RP                             { $$=NULL;Error("B",@1.first_line,"Missing function name");}
  | ID LP error RP                            { $$=NULL;Error("B",@3.first_line,"Syntax error");};
//形参列表
//VarList -> ParamDec VarList (Error)
VarList : ParamDec COMMA VarList              { $$=CreateUnterminalNode("VarList",@$.first_line,$1); AddChild($$,$2); AddChild($$,$3);}
  | ParamDec                                  { $$=CreateUnterminalNode("VarList",@$.first_line,$1);}
  | ParamDec VarList                          { $$=NULL;Error("B",@1.last_line,"Expected ','");};
//对一个形参的定义
ParamDec : Specifier VarDec                   { $$=CreateUnterminalNode("ParamDec",@$.first_line,$1); AddChild($$,$2);};



/*Statements*/
//语句：由一对花括号括起来的语句
//CompSt ->LC DefList StmtList error (Error)
CompSt : LC DefList StmtList RC               { $$=CreateUnterminalNode("CompSt",@$.first_line,$1); AddChild($$,$2); AddChild($$,$3);AddChild($$,$4);}
  | error DefList StmtList RC                 { $$=NULL; Error("B",@1.first_line,"Expected '{'"); }
  | LC DefList StmtList error                 { $$=NULL; Error("B",@3.last_line,"Expected '}'"); }
  | error RC                                  { $$=NULL; Error("B",@1.first_line,"Syntax error"); };

//StmtList → Stmt StmtList | e
StmtList :                                    { $$=NULL;}
  | Stmt StmtList                             { $$=CreateUnterminalNode("StmtList",@$.first_line,$1); AddChild($$,$2); };
//单条语句：末尾有分号的表达式、另一个语句块；返回语句；if；ifelse；while
//Stmt -> Exp error | RETURN Exp error | RETURN SEMI | RETURN error | IF LP Exp error | IF error
Stmt : Exp SEMI                               { $$=CreateUnterminalNode("Stmt",@$.first_line,$1); AddChild($$,$2); }
  | CompSt                                    { $$=CreateUnterminalNode("Stmt",@$.first_line,$1);}
  | RETURN Exp SEMI                           { $$=CreateUnterminalNode("Stmt",@$.first_line,$1); AddChild($$,$2); AddChild($$,$3);}
  | IF LP Exp RP Stmt                         { $$=CreateUnterminalNode("Stmt",@$.first_line,$1);AddChild($$,$2);AddChild($$,$3);AddChild($$,$4);AddChild($$,$5);}
  | IF LP Exp RP Stmt ELSE Stmt               { $$=CreateUnterminalNode("Stmt",@$.first_line,$1);AddChild($$,$2);AddChild($$,$3);AddChild($$,$4);AddChild($$,$5);AddChild($$,$6);AddChild($$,$7);}
  | WHILE LP Exp RP Stmt                      { $$=CreateUnterminalNode("Stmt",@$.first_line,$1);AddChild($$,$2);AddChild($$,$3);AddChild($$,$4);AddChild($$,$5);}
  | Exp error                                 { $$=NULL; Error("B",@1.last_line,"Expected ';'"); }
  | RETURN Exp error                          { $$=NULL; Error("B",@2.last_line,"Expected ';'");}
  | RETURN SEMI                               { $$=NULL; Error("B",@1.last_line,"Return an empty expression is not allowed in C--"); }//不允许return空表达式
  | RETURN error                              { $$=NULL; Error("B",@1.last_line,"Expected ';'");}
  | IF LP Exp error                           { $$=NULL; Error("B",@3.last_line,"Expected ')'"); }
  | IF error                                  { $$=NULL; Error("B",@1.last_line,"Expected '('");}
  | WHILE LP Exp error                        { $$=NULL; Error("B",@3.last_line,"Expected ')'");}
  | WHILE error                               { $$=NULL; Error("B",@1.last_line,"Expected '('");} 
  | error SEMI                                { $$=NULL; Error("B",@1.first_line,"Syntax error");};


/*Local Deffintions*/
//局部变量：一个Def是一条定义
//DefList → Def DefList | e
DefList :                                     { $$=NULL;}
  | Def DefList                               { $$=CreateUnterminalNode("DefList",@$.first_line,$1); AddChild($$,$2);};

Def : Specifier DecList SEMI                  { $$=CreateUnterminalNode("Def",@$.first_line,$1);AddChild($$,$2);AddChild($$,$3);}
  | Specifier DecList                         { $$=NULL; Error("B",@2.last_line,"Expected ';'");};

DecList : Dec                                 { $$=CreateUnterminalNode("DecList",@$.first_line,$1);}
  | Dec COMMA DecList                         { $$=CreateUnterminalNode("DecList",@$.first_line,$1);AddChild($$,$2); AddChild($$,$3);}
  | Dec DecList                               { $$=NULL; Error("B",@1.last_line,"Expected ','"); };

Dec : VarDec                                  { $$=CreateUnterminalNode("Dec",@$.first_line,$1);}
  | VarDec ASSIGNOP Exp                       { $$=CreateUnterminalNode("Dec",@$.first_line,$1); AddChild($$,$2); AddChild($$,$3); }
  | VarDec Exp                                { $$=NULL; Error("B",@1.last_line,"Expected '='"); };



/*Expressions*/
//基于优先级处理后的Exp产生式
Exp : Exp ASSIGNOP Exp                        { $$ = CreateUnterminalNode("Exp", @$.first_line, $1); AddChild($$, $2); AddChild($$, $3); }
    | Exp OR Exp                              { $$ = CreateUnterminalNode("Exp", @$.first_line, $1); AddChild($$, $2); AddChild($$, $3); }
    | Exp AND Exp                             { $$ = CreateUnterminalNode("Exp", @$.first_line, $1); AddChild($$, $2); AddChild($$, $3); }
    | Exp RELOP Exp                           { $$ = CreateUnterminalNode("Exp", @$.first_line, $1); AddChild($$, $2); AddChild($$, $3); }
    | Exp PLUS Exp                            { $$ = CreateUnterminalNode("Exp", @$.first_line, $1); AddChild($$, $2); AddChild($$, $3); }
    | Exp MINUS Exp                           { $$ = CreateUnterminalNode("Exp", @$.first_line, $1); AddChild($$, $2); AddChild($$, $3); }
    | Exp STAR Exp                            { $$ = CreateUnterminalNode("Exp", @$.first_line, $1); AddChild($$, $2); AddChild($$, $3); }
    | Exp DIV Exp                             { $$ = CreateUnterminalNode("Exp", @$.first_line, $1); AddChild($$, $2); AddChild($$, $3); }
    | LP Exp RP                               { $$ = CreateUnterminalNode("Exp", @$.first_line, $1); AddChild($$, $2); }
    | MINUS Exp %prec NOT                     { $$ = CreateUnterminalNode("Exp", @$.first_line, $1); AddChild($$, $2); }
    | NOT Exp                                 { $$ = CreateUnterminalNode("Exp", @$.first_line, $1); AddChild($$, $2); }
    | ID LP Args RP                           { $$ = CreateUnterminalNode("Exp", @$.first_line, $1); AddChild($$, $3); }
    | ID LP RP                                { $$ = CreateUnterminalNode("Exp", @$.first_line, $1); }
    | Exp LB Exp RB                           { $$ = CreateUnterminalNode("Exp", @$.first_line, $1); AddChild($$, $2); AddChild($$, $3); }
    | Exp DOT ID                              { $$ = CreateUnterminalNode("Exp", @$.first_line, $1); AddChild($$, $2); AddChild($$, $3); }
    | ID                                      { $$ = CreateUnterminalNode("Exp", @$.first_line, $1); }
    | INT                                     { $$ = CreateUnterminalNode("Exp", @$.first_line, $1); }
    | FLOAT                                   { $$ = CreateUnterminalNode("Exp", @$.first_line, $1); };

Args
    : Exp COMMA Args                          { $$ = CreateUnterminalNode("Args", @$.first_line, $1); AddChild($$, $2); AddChild($$, $3); }
    | Exp                                     { $$ = CreateUnterminalNode("Args", @$.first_line, $1); };


%%
void yyerror(const char* msg){}