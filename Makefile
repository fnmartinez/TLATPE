CC = gcc
FLEX = flex
FILES = ./classes/Automata.c ./classes/Converter.c ./classes/Derivation.c ./classes/Derivations.c ./classes/Grammar.c ./classes/Production.c ./classes/Productions.c ./classes/Utils.c ./lex.yy.c
OUT_DIR=./
GRAMAR_OUT_EXE = grammar 
#OUT_EXE = $(addprefix $(OUT_DIR)/,server)
COPTS= -Wall -g
LDOPTS= -lpthread -lfl
MATH = -lm

GR_FL_FILES = ./parser/lex/gr-parser.l
GR_CC_FILES = ./parser/src/gr-parser.c
grammar: $(FILES)
	$(FLEX) $(GR_FL_FILES)
	$(CC) $(COPTS) -o $(OUT_EXE) $(FILES) $(GR_CC_FILES) $(LDOPTS)
	
AT_FL_FILES = ./parser/lex/Automata.l
AT_CC_FILES = ./parser/src/Automata.c
automata: $(FILES)
	$(FLEX) $(GR_FL_FILES)
	$(CC) $(COPTS) -o $(OUT_EXE) $(FILES) $(GR_CC_FILES) $(LDOPTS)
	
clean:
	rm -f *.o core

rebuild: clean build