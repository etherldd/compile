%{
#include "sem.h"
#include "syn.tab.h"
char error_msg[1024];
int yycolumn = 1;
#define YY_USER_ACTION \
    yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn; \
    yylloc.last_column = yycolumn + yyleng - 1; \
    yycolumn += yyleng;
%}

%x COMMENT
%option yylineno

INT8 0[1-7][0-7]*
INT10 (0|[1-9][0-9]*)
INT16 0[Xx][0-9a-fA-F]+
INT {INT8}|{INT10}|{INT16}
FLOAT ({INT10}\.[0-9]+)|([+-]?([0-9]*\.[0-9]+|[0-9]+\.[0-9]*)[Ee][+-]?[0-9]+)
ID [a-zA-Z_][a-zA-Z0-9_]*

%%

"//".*    {/*忽略单行注释*/}               
"/*"            { BEGIN(COMMENT); }
<COMMENT>"*/"   { BEGIN(INITIAL); } /* 遇到结束标记，结束多行注释 */
<COMMENT>.|\n   { /* 在注释状态下，忽略所有内容 */ }
<COMMENT><<EOF>> {
    Error("B",yylineno,"Syntax error");
    BEGIN(INITIAL); /* 在文件结束时返回到初始状态，报告错误 */
}
"*/" { //单独遇到*/
    Error("B",yylineno,"Syntax error");
}

";" { yylval.type_node = CreateTerminalNode(1, "SEMI", yylineno,yytext); return SEMI; }
"," { yylval.type_node = CreateTerminalNode(1, "COMMA", yylineno,yytext); return COMMA; }
"=" { yylval.type_node = CreateTerminalNode(1, "ASSIGNOP", yylineno,yytext); return ASSIGNOP; }
">"|"<"|">="|"<="|"=="|"!=" { yylval.type_node = CreateTerminalNode(1, "RELOP", yylineno,yytext); return RELOP; }
"+" { yylval.type_node = CreateTerminalNode(1, "PLUS", yylineno,yytext); return PLUS; }
"-" { yylval.type_node = CreateTerminalNode(1, "MINUS", yylineno,yytext); return MINUS; }
"*" { yylval.type_node = CreateTerminalNode(1, "STAR", yylineno,yytext); return STAR; }
"/" { yylval.type_node = CreateTerminalNode(1, "DIV", yylineno,yytext); return DIV; }
"&&" { yylval.type_node = CreateTerminalNode(1, "AND", yylineno,yytext); return AND; }
"||" { yylval.type_node = CreateTerminalNode(1, "OR", yylineno,yytext); return OR; }
"." { yylval.type_node = CreateTerminalNode(1, "DOT", yylineno,yytext); return DOT; }
"!" { yylval.type_node = CreateTerminalNode(1, "NOT", yylineno,yytext); return NOT; }
"int"|"float" { yylval.type_node = CreateTerminalNode(1, "TYPE", yylineno,yytext); return TYPE; }
"(" { yylval.type_node = CreateTerminalNode(1, "LP", yylineno,yytext); return LP; }
")" { yylval.type_node = CreateTerminalNode(1, "RP", yylineno,yytext); return RP; }
"[" { yylval.type_node = CreateTerminalNode(1, "LB", yylineno,yytext); return LB; }
"]" { yylval.type_node = CreateTerminalNode(1, "RB", yylineno,yytext); return RB; }
"{" { yylval.type_node = CreateTerminalNode(1, "LC", yylineno,yytext); return LC; }
"}" { yylval.type_node = CreateTerminalNode(1, "RC", yylineno,yytext); return RC; }
"struct" { yylval.type_node = CreateTerminalNode(1, "STRUCT", yylineno,yytext); return STRUCT; }
"return" { yylval.type_node = CreateTerminalNode(1, "RETURN", yylineno,yytext); return RETURN; }
"if" { yylval.type_node = CreateTerminalNode(1, "IF", yylineno,yytext); return IF; }
"else" { yylval.type_node = CreateTerminalNode(1, "ELSE", yylineno,yytext); return ELSE; }
"while" { yylval.type_node = CreateTerminalNode(1, "WHILE", yylineno,yytext); return WHILE; }

{INT} {//还需要加入具体属性值类型
    yylval.type_node = CreateTerminalNode(1, "INT", yylineno,yytext);
    // if(yytext[0] == '0' && (yytext[1] == 'x' || yytext[1] == 'X'))
    //     sscanf(yytext + 2,"%x",&node->int_val);
    // else if(yytext[0] == '0')
    //     sscanf(yytext,"%o",&node->int_val);
    // else
    //     sscanf(yytext,"%d",&node->int_val);
    // yylval.type_node = node;
    return INT;
}
{FLOAT} {
    yylval.type_node = CreateTerminalNode(1, "FLOAT", yylineno,yytext);
    return FLOAT;
}
{ID} {
    yylval.type_node  = CreateTerminalNode(1, "ID", yylineno,yytext);
    return ID;
}

[+-]?0[xX][0-9a-fA-F]*[g-zG-Z][0-9a-zA-Z]* {
    // ----------特定错误检测处理-----------
    // 非法的十六进制数(含有了g-z)
    sprintf(error_msg,"Illegal hexadecimal number '%s'",yytext);
    Error("A",yylineno,error_msg);
    yylval.type_node = NULL;
    return INT;
}


[+-]?0[0-7]*[a-zA-Z8-9][0-9a-zA-Z]* {
    // 非法的八进制数(含有8/9/字母)
    sprintf(error_msg,"Illegal octal number '%s'",yytext);
    Error("A",yylineno,error_msg);
    yylval.type_node = NULL;
    return INT;
}

[+-]?([0-9]+(\.[0-9]*)?|\.[0-9]+)[Ee][+-]? {
    // 缺少指数的浮点数
    sprintf(error_msg,"Floating number '%s' missing exponent part",yytext);
    Error("A",yylineno,error_msg);
    yylval.type_node = NULL;
    return FLOAT;
}

[0-9]([0-9]*[_A-Za-z][_A-Za-z0-9]*) {
    // 以数字开头的错误标识符
    sprintf(error_msg,"Illegal identifier '%s'",yytext);
    Error("A",yylineno,error_msg);
    yylval.type_node = NULL;
    return ID;
}

\n {yycolumn=1;  }

((" ")|(\t)|\r) {}

. { sprintf(error_msg,"Mysterious characters '%s'",yytext);
    Error("A",yylineno,error_msg); }


%%