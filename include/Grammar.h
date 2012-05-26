/*
 * Grammar.h
 *
 *  Created on: May 14, 2012
 *      Author: joseignaciosantiagogalindo
 */

#ifndef GRAMMAR_H_
#define GRAMMAR_H_
#ifndef LAMDA
#define LAMDA '\\'
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Productions.h"
#include "Production.h"
#include "utils.h"

typedef struct Grammar{
	ProductionsADT productions;
	char * terminals;
	char * nonterminals;
	int quantterminals;
	int quantnonterminals;
	char distinguished;
}Grammar;

typedef struct Grammar * GrammarADT;

/*Constructor-destructor*/
GrammarADT newGrammar(void);
void freeGrammar(GrammarADT  grammar);

/*Getters*/
char * getTerminals(GrammarADT grammar);
char * getNonTerminals(GrammarADT grammar);
char getDistinguished(GrammarADT grammar);
ProductionsADT  getProductions(GrammarADT grammar);
int getQuantTerminals(GrammarADT grammar);
int getQuantNonTerminals(GrammarADT grammar);

/*Setters*/
void setTerminals(GrammarADT grammar, char * terminals, int quant);
void setNonTerminals(GrammarADT grammar, char * nonterminals, int quant);
void setDistinguished(GrammarADT grammar, char distinguished);
void setProductions(GrammarADT grammar,ProductionsADT productions);

/*Utility*/
void printGrammar(GrammarADT grammar);
void removeUnreachableProductions(GrammarADT grammar);
void removeOnlyRightTerminals(GrammarADT grammar);
void grammarToFile(GrammarADT grammar);
int isTerminal(char symbol);
int isNonTerminal(char symbol);


#endif /* STRUCTURES_H_ */
