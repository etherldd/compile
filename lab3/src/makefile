# GNU make手册：http://www.gnu.org/software/make/manual/make.html
# ************ 遇到不明白的地方请google以及阅读手册 *************

# 编译器设定和编译选项
CC = gcc
FLEX = flex
BISON = bison
CFLAGS = -std=c99

# 编译目标：src目录下的所有.c文件
CFILES = $(shell find ./ -name "*.c")
HFILES = $(shell find ./include -name "*.h")
OBJS = $(CFILES:.c=.o)
LFILE = $(shell find ./ -name "*.l")
YFILE = $(shell find ./ -name "*.y")
LFC = $(shell find ./ -name "*.l" | sed s/[^/]*\\.l/lex.yy.c/)
YFC = $(shell find ./ -name "*.y" | sed s/[^/]*\\.y/syntax.tab.c/)
LFO = $(LFC:.c=.o)
YFO = $(YFC:.c=.o)

all: parser $(HFILES)

parser: syntax
	$(CC) -g -o parser ./main.c ./mid/$(YFO) -ll

syntax: lexical syntax-c
	$(CC) -g -c ./mid/$(YFC) -o ./mid/$(YFO)

lexical: $(LFILE)
	$(shell mkdir mid)
	$(FLEX) -o ./mid/$(LFC) $(LFILE)

syntax-c: $(YFILE)
	$(BISON) -o ./mid/$(YFC) -d -v $(YFILE)

-include $(patsubst %.o, %.d, $(OBJS))

# 定义的一些伪目标
.PHONY: clean test1 test2
a1: all
	./parser ../test/inputs/A-1.cmm ./gene.ir
a2: all
	./parser ../test/inputs/A-2.cmm ./gene.ir
a3: all
	./parser ../test/inputs/A-3.cmm ./gene.ir
a4: all
	./parser ../test/inputs/A-4.cmm ./gene.ir
a5: all
	./parser ../test/inputs/A-5.cmm ./gene.ir
b1: all
	./parser ../test/inputs/B-1.cmm ./gene.ir
b2: all
	./parser ../test/inputs/B-2.cmm ./gene.ir
b3: all
	./parser ../test/inputs/B-3.cmm ./gene.ir
c1: all
	./parser ../test/inputs/C-1.cmm ./gene.ir
c2: all
	./parser ../test/inputs/C-2.cmm ./gene.ir
e1-1: all
	./parser ../test/inputs/E1-1.cmm ./gene.ir
e1-2: all
	./parser ../test/inputs/E1-2.cmm ./gene.ir
e1-3: all
	./parser ../test/inputs/E1-3.cmm ./gene.ir
e2-1: all
	./parser ../test/inputs/E2-1.cmm ./gene.ir
e2-2: all
	./parser ../test/inputs/E2-2.cmm ./gene.ir
e2-3: all
	./parser ../test/inputs/E2-3.cmm ./gene.ir
clean:
	rm -rf ./mid
	rm -f parser
