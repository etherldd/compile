%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "stree.h"
    #include "syntax.tab.h"
    int yycolumn = 1;
    // #define YY_USER_ACTION \
    //     yylloc.first_line = yylloc.last_line = yylineno; \
    //     yylloc.first_column = yycolumn; \
    //     yylloc.last_column = yycolumn + yyleng - 1; \
    //     yycolumn += yyleng;
    unsigned int curline = 1;
    int flexError = 0;
%}
%option     yylineno
%x          COMMENT
INT_10      "0"|[1-9][0-9]*
DIGIT       [0-9]
EXPONENT    [eE][-+]?{DIGIT}+
FRACTION    {INT_10}\.{DIGIT}+|{DIGIT}+\.
FLOATING    {FRACTION}{EXPONENT}?|\.{DIGIT}+{EXPONENT}?
%%
{FLOATING} {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _FLOAT, curval);
    return FLOAT;
}
[0][xX][0-9a-fA-F]+/[; ,\])}+]  {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _INT, curval);
    return INT;
}
[0][0-7]*/[, ;\])}+]  {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _INT, curval);
    return INT;
}
{INT_10}/[, ;\])}+]  {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _INT, curval);
    return INT;
}
";" {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _SEMI, curval);
    return SEMI;
}
"," {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _COMMA, curval);
    return COMMA;
}
"=" {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _ASSIGNOP, curval);
    return ASSIGNOP;
}
">"|"<"|">="|"<="|"=="|"!=" {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _RELOP, curval);
    return RELOP;
}
"+" {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _PLUS, curval);
    return PLUS;
}
"-" {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _MINUS, curval);
    return MINUS;
}
"*" {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _STAR, curval);
    return STAR;
}
"/" {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _DIV, curval);
    return DIV;
}
"&&" {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _AND, curval);
    return AND;
}
"||" {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _OR, curval);
    return OR;
}
"." {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _DOT, curval);
    return DOT;
}
"!" {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _NOT, curval);
    return NOT;
}
"int"|"float" {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _TYPE, curval);
    return TYPE;
}
"(" {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _LP, curval);
    return LP;
}
")" {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _RP, curval);
    return RP;
}
"[" {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _LB, curval);
    return LB;
}
"]" {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _RB, curval);
    return RB;
}
"{" {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _LC, curval);
    return LC;
}
"}" {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _RC, curval);
    return RC;
}
"struct" {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _STRUCT, curval);
    return STRUCT;
}
"return" {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _RETURN, curval);
    return RETURN;
}
"if" {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _IF, curval);
    return IF;
}
"else" {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _ELSE, curval);
    return ELSE;
}
"while" {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _WHILE, curval);
    return WHILE;
}
[a-zA-Z_][a-zA-Z0-9_]{0,31} {
    char* curval = malloc(sizeof(char) * (yyleng + 1));
    strcpy(curval, yytext);
    curval[yyleng] = '\0';
    yylval.type_node = node_oftoken(curline, _ID, curval);
    return ID;
}
\n {
    curline += 1;
    yycolumn = 1;
}
[ \t\r] {}
"//".* {}
"/*"        { BEGIN(COMMENT); }
<COMMENT>{
    "*/"    { BEGIN(INITIAL); }
    .|\n    ; /* 忽略注释中的其他字符 */
}
\"[^\"]*\" {
    if (yytext[yyleng - 2] == '\\') {
        yyless(yyleng - 1);
        yymore();
    }
}
. {
    printf("Error type A at Line %d: Mysterious characters \"%c", yylineno, yytext[0]);
    flexError = 1;
    unsigned int p = 1;
    char c = input();
    while (!(c == ' ' || c == '\n' || c == ';'|| c == '\r')) {
        printf("%c", c);
        c = input();
    }
    unput(c);
    //printf("Error type A at Line %d: Mysterious characters \"%s\"\n", yylineno, pr_str);
    printf("\"\n");
    //return ID;
}
%%