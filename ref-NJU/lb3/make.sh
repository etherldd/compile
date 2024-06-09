#!/bin/sh
bison -d syn.y
flex lex.l
# bison -d syntax.y
gcc main.c syn.tab.c sem.c -ly -lfl -o cc
