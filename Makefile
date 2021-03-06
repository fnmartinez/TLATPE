CC = gcc
FLEX = flex
FILES = ./classes/Automata.c ./classes/Converter.c ./classes/Derivation.c ./classes/Derivations.c ./classes/Grammar.c ./classes/Production.c ./classes/Productions.c ./classes/Utils.c
OUT_DIR=./
GR_OUT_EXE = grammar 
AT_OUT_EXE = automata
COPTS= -Wall -g
LDOPTS= -lfl
MATH = -lm

GR_FL_FILES = ./parser/lex/gr-parser.l
GR_CC_FILES = ./parser/src/gr-parser.c ./grammar.yy.c
grammar: $(FILES) $(GR_CC_FILES)
	$(CC) $(COPTS) -o $(GR_OUT_EXE) $(FILES) $(GR_CC_FILES) $(LDOPTS)
	-rm -f grammar.yy.c

grammar.yy.c:	
	$(FLEX) -o grammar.yy.c $(GR_FL_FILES) 
	
AT_FL_FILES = ./parser/lex/Automata.l
AT_CC_FILES = ./automata.yy.c ./parser/src/Automata.c
automata: $(FILES) $(AT_CC_FILES)
	$(CC) $(COPTS) -o $(AT_OUT_EXE) $(FILES) $(AT_CC_FILES) $(LDOPTS)
	-rm -f automata.yy.c
	
automata.yy.c:
	$(FLEX) -o automata.yy.c $(AT_FL_FILES)
	
all: grammar automata
	
clean_grammar:
	-rm -f *.o core
	-rm -f grammar

clean_automata:
	-rm -f *.o core
	_rm -f automata
clean_all:
	-rm -f *.o core
	-rm -f grammar
	-rm -f automata

#rebuild: clean build
