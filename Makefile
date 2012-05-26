CC = gcc
FLEX = flex
FILES = ./classes/Automata.c ./classes/Converter.c ./classes/Derivation.c ./classes/Derivations.c ./classes/Grammar.c ./classes/Production.c ./classes/Productions.c ./classes/Utils.c
OUT_DIR=./
GRAMAR_OUT_EXE = grammar 
#OUT_EXE = $(addprefix $(OUT_DIR)/,server)
COPTS= -Wall -g
LDOPTS= -lpthread -lfl
MATH = -lm

GR_FL_FILES = ./parser/lex/gr-parser.l
GR_CC_FILES = ./parser/src/gr-parser.c ./grammar.yy.c
grammar: $(FILES) $(GR_CC_FILES)
	$(CC) $(COPTS) -o $(OUT_EXE) $(FILES) $(GR_CC_FILES) $(LDOPTS)

grammar.yy.c:	
	$(FLEX) -o grammar.yy.c $(GR_FL_FILES) 
	
AT_FL_FILES = ./parser/lex/Automata.l
AT_CC_FILES = ./parser/src/Automata.c ./automata.yy.c
automata: $(FILES) $(AT_CC_FILES)
	$(FLEX) $(AT_FL_FILES)
	$(CC) $(COPTS) -o $(OUT_EXE) $(FILES) $(AT_CC_FILES) $(LDOPTS)
	
automata.yy.c:
	$(FLEX) -o automata.yy.c $(GR_FL_FILES)
	
clean:
	rm -f *.o core

rebuild: clean build