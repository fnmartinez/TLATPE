/*
 * Grammar.h
 *
 *  Created on: May 14, 2012
 *      Author: joseignaciosantiagogalindo
 */

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#include "Productions.h"

typedef struct Grammar * GrammarADT;

/*Constructor-destructor*/
GrammarADT newGrammar(void);
void freeGrammar(GrammarADT  grammar);

/*Getters*/
char * getTerminals(GrammarADT grammar);
char * getNonTerminals(GrammarADT grammar);
char getDistinguished(GrammarADT grammar);
ProductionsADT  getProductions(GrammarADT grammar);

/*Setters*/
void setTerminals(GrammarADT grammar, char * terminals);
void setNonTerminals(GrammarADT grammar, char * nonterminals);
void setDistinguished(GrammarADT grammar, char distinguished);
void setProductions(GrammarADT grammar,ProductionsADT productions);

/*Utility*/
void printGrammar(GrammarADT grammar);




#endif /* STRUCTURES_H_ */
