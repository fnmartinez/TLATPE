/*
 * Grammar.h
 *
 *  Created on: May 14, 2012
 *      Author: joseignaciosantiagogalindo
 */

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#include "Productions.h"
#include "Automata.h"
#include "TADS.h"


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

/*Conversion*/
AutomataADT toAutomata(GrammarADT grammar);



#endif /* STRUCTURES_H_ */
