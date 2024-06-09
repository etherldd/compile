# GNU make手册：http://www.gnu.org/software/make/manual/make.html
# ************ 遇到不明白的地方请google以及阅读手册 *************

# 编译器设定和编译选项
CC = gcc
FLEX = flex
BISON = bison
CFLAGS = -std=c99

# 编译目标：src目录下的所有.c文件
CFILES = $(shell find ./ -name "*.c")
HFILES = $(shell find ./ -name "*.h")
OBJS = $(CFILES:.c=.o)
LFILE = $(shell find ./ -name "*.l")
YFILE = $(shell find ./ -name "*.y")
LFC = $(shell find ./ -name "*.l" | sed s/[^/]*\\.l/lex.yy.c/)
YFC = $(shell find ./ -name "*.y" | sed s/[^/]*\\.y/syntax.tab.c/)
LFO = $(LFC:.c=.o)
YFO = $(YFC:.c=.o)

all: parser $(HFILES)

parser: syntax $(filter-out $(LFO),$(OBJS))
	$(CC) -g -o parser $(filter-out $(LFO),$(OBJS)) -ll

syntax: lexical syntax-c
	$(CC) -g -c $(YFC) -o $(YFO)

lexical: $(LFILE)
	$(FLEX) -o $(LFC) $(LFILE)

syntax-c: $(YFILE)
	$(BISON) -o $(YFC) -d -v $(YFILE)

-include $(patsubst %.o, %.d, $(OBJS))

# 定义的一些伪目标
.PHONY: clean test1 test2
error:
	./parser ../Test/test1.cmm
tree-file:
	mkdir outputs
	cp ../Test/C-1.exp ./outputs/c1exp
	cp ../Test/C-2.exp ./outputs/c2exp
	./parser ../Test/C-1.cmm > ./outputs/c1out
	./parser ../Test/C-2.cmm > ./outputs/c2out
tree2:
	./parser ../Test/C-2.cmm
tree1:
	./parser ../Test/C-1.cmm
tree3:
	./parser ../Test/newtest.cmm
a1:
	./parser ../test/inputs/A-1.cmm
a2:
	./parser ../test/inputs/A-2.cmm
a3:
	./parser ../test/inputs/A-3.cmm
a4:
	./parser ../test/inputs/A-4.cmm
a5:
	./parser ../test/inputs/A-5.cmm
a6:
	./parser ../test/inputs/A-6.cmm
a7:
	./parser ../test/inputs/A-7.cmm
a8:
	./parser ../test/inputs/A-8.cmm
a9:
	./parser ../test/inputs/A-9.cmm
a10:
	./parser ../test/inputs/A-10.cmm
a11:
	./parser ../test/inputs/A-11.cmm
a12:
	./parser ../test/inputs/A-12.cmm
a13:
	./parser ../test/inputs/A-13.cmm
a14:
	./parser ../test/inputs/A-14.cmm
a15:
	./parser ../test/inputs/A-15.cmm
a16:
	./parser ../test/inputs/A-16.cmm
a17:
	./parser ../test/inputs/A-17.cmm
a18:
	./parser ../test/inputs/A-18.cmm
a19:
	./parser ../test/inputs/A-19.cmm
a20:
	./parser ../test/inputs/A-20.cmm
b1:
	./parser ../test/inputs/B-1.cmm
b2:
	./parser ../test/inputs/B-2.cmm
c1:
	./parser ../test/inputs/C-1.cmm
c2:
	./parser ../test/inputs/C-2.cmm
d1:
	./parser ../test/inputs/D-1.cmm
d2:
	./parser ../test/inputs/D-2.cmm
d3:
	./parser ../test/inputs/D-3.cmm
e1:
	./parser ../test/inputs/E-1.cmm
e2:
	./parser ../test/inputs/E-2.cmm
e3:
	./parser ../test/inputs/E-3.cmm
listTest:
	gcc testList.c list.h -o test
	./test
listClean:
	rm ./test
clean:
	rm -f parser lex.yy.c syntax.tab.c syntax.tab.h syntax.output
	rm -f $(OBJS) $(OBJS:.o=.d)
	rm -f $(LFC) $(YFC) $(YFC:.c=.h)
	rm -rf ./outputs
	rm -f *~
