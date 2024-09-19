#ifndef UTIL_H
#define UTIL_H


char* nontokens[] = {"Program", "Def", "ExtDefList", "DefList", "ExtDef", "Specifier", "Dec", "ExtDecList", "DecList",
                        "FunDec", "CompSt", "VarDec", "StructSpecifier", "OptTag", 
                        "Tag", "VarList", "ParamDec", "StmtList", "Stmt", 
                        "Exp", "Args", "ERROR"};
enum {_Program, _Def, _ExtDefList, _DefList, _ExtDef, _Specifier, _Dec, _ExtDecList, _DecList,
            _FunDec, _CompSt, _VarDec, _StructSpecifier, _OptTag, 
            _Tag, _VarList, _ParamDec, _StmtList, _Stmt, 
            _Exp, _Args, _ERROR};
#endif