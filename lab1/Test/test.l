%{
    #include <stdio.h>
%}
%option     yylineno
%x          COMMENT
INT_10      "0"|[1-9][0-9]*
DIGIT       [0-9]
EXPONENT    [eE][-+]?{DIGIT}+
FRACTION    {INT_10}\.{DIGIT}+|{DIGIT}+\.
FLOATING    {FRACTION}{EXPONENT}?|\.{DIGIT}+{EXPONENT}?
%%
{FLOATING} {printf("FLOAT:%s\n", yytext) ;}
[0][xX][0-9a-fA-F]+ {printf("INT:%s\n", yytext) ;}
";" {printf("SEMI:%s\n", yytext) ;}
"," {printf("COMMA:%s\n", yytext) ;}
"=" {printf("ASSIGNOP:%s\n", yytext) ;}
">"|"<"|">="|"<="|"=="|"!=" {printf("RELOP:%s\n", yytext) ;}
"+" {printf("PLUS:%s\n", yytext) ;}
"-" {printf("MINUS:%s\n", yytext) ;}
"*" {printf("STAR:%s\n", yytext) ;}
"/" {printf("DIV:%s\n", yytext) ;}
"&&" {printf("AND:%s\n", yytext) ;}
"||" {printf("OR:%s %d\n", yytext, yyleng) ;}
"." {printf("DOT:%s\n", yytext) ;}
"!" {printf("NOT:%s\n", yytext) ;}
"int"|"float" {printf("TYPE:%s\n", yytext) ;}
"(" {printf("LP:%s\n", yytext) ;}
")" {printf("RP:%s\n", yytext) ;}
"[" {printf("LB:%s\n", yytext) ;}
"]" {printf("RB:%s\n", yytext) ;}
"{" {printf("LC:%s\n", yytext) ;}
"}" {printf("RC:%s\n", yytext) ;}
"struct" {printf("STRUCT:%s\n", yytext) ;}
"return" {printf("RETURN:%s\n", yytext) ;}
"if" {printf("IF:%s\n", yytext) ;}
"else" {printf("ELSE:%s\n", yytext) ;}
"while" {printf("WHILE:%s\n", yytext) ;}
[a-zA-Z_][a-zA-Z0-9_]{0,31} {printf("ID:%s\n", yytext) ;}
[0][0-7]*/[ ;] {printf("INT:%s\n", yytext) ;}
{INT_10}/[ ;] {printf("INT:%s\n", yytext) ;}
" " {printf("空格:%s\n", yytext) ;}
"\t" {printf("tab:%s\n", yytext) ;}
"\n" {printf("回车:%s\n", yytext) ;}
"\r" {printf("岗r:%s\n", yytext) ;}
"//".* {}
"/*"        { BEGIN(COMMENT); }
<COMMENT>{
    "*/"    { BEGIN(INITIAL); }
    .|\n    ; /* 忽略注释中的其他字符 */
}
\"[^\"]*\" {if (yytext[yyleng - 2] == '\\') {yyless(yyleng - 1);yymore();}}
[^ \t\n\r;]+ {
    printf("Error type A at Line %d: Mysterious characters \"%s\"\n", yylineno, yytext);
}
%%

int main(int argc, char** argv)
{
    if (argc <= 1) {
        printf("input num <= 1\n");
        return 1;
    }
    yyin = fopen(argv[1], "r");
    yylineno = 1;
    yylex();
    return 0;
}