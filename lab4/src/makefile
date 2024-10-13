# Compiler and tool settings
CC = gcc
CXX = g++
FLEX = flex
BISON = bison
CFLAGS = -std=c99 -g
CXXFLAGS = -std=c++11 -g

# Source files
CFILES = $(shell find ./ -name "*.c")
HFILES = $(shell find ./include -name "*.h")
LFILE = $(shell find ./ -name "*.l")
YFILE = $(shell find ./ -name "*.y")

# Generated files
LFC = $(shell find ./ -name "*.l" | sed s/[^/]*\\.l/lex.yy.c/)
YFC = $(shell find ./ -name "*.y" | sed s/[^/]*\\.y/syntax.tab.c/)
LFO = $(LFC:.c=.o)
YFO = $(YFC:.c=.o)

# Main targets
all: parser mips $(HFILES)

# Build the parser
parser: syntax
	$(CC) $(CFLAGS) -o parser ./main.c ./mid/$(YFO) -ll

# Generate syntax
syntax: lexical syntax-c
	$(CC) $(CFLAGS) -c ./mid/$(YFC) -o ./mid/$(YFO)

# Generate lexical analyzer
lexical: $(LFILE)
	mkdir -p mid
	$(FLEX) -o ./mid/$(LFC) $(LFILE)

# Generate syntax parser
syntax-c: $(YFILE)
	$(BISON) -o ./mid/$(YFC) -d -v -Wno-conflicts-sr $(YFILE)

# Build MIPS generator
mips:
	$(CXX) $(CXXFLAGS) ./mips_gene/mips_gene.cpp ./mips_gene/main.cpp ./mips_gene/IR_list.cpp -o ./mips

# Include dependencies
-include $(patsubst %.o, %.d, $(OBJS))

# Phony targets
.PHONY: clean test_all

# Test targets
test_all: a0 a1 a2 a3 a4 a5 b1 b2 b3 c1 c2 e1-1 e1-2 e1-3 e2-1 e2-2 e2-3

# Function to generate test targets
define generate_test_target
$(1): all
	./parser ../test/inputs/$(2).cmm ./gene.ir
	./mips ./gene.ir
endef

# Individual test targets
$(eval $(call generate_test_target,a0,mips_test))
$(eval $(call generate_test_target,a1,A-1))
$(eval $(call generate_test_target,a2,A-2))
$(eval $(call generate_test_target,a3,A-3))
$(eval $(call generate_test_target,a4,A-4))
$(eval $(call generate_test_target,a5,A-5))
$(eval $(call generate_test_target,b1,B-1))
$(eval $(call generate_test_target,b2,B-2))
$(eval $(call generate_test_target,b3,B-3))
$(eval $(call generate_test_target,c1,C-1))
$(eval $(call generate_test_target,c2,C-2))
$(eval $(call generate_test_target,e1-1,E1-1))
$(eval $(call generate_test_target,e1-2,E1-2))
$(eval $(call generate_test_target,e1-3,E1-3))
$(eval $(call generate_test_target,e2-1,E2-1))
$(eval $(call generate_test_target,e2-2,E2-2))
$(eval $(call generate_test_target,e2-3,E2-3))

# Clean target
clean:
	rm -rf ./mid
	rm -f parser mips gene.ir gene.mips
