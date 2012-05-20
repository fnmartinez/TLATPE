/*
 * Automata.h
 *
 *  Created on: May 14, 2012
 *      Author: joseignaciosantiagogalindo
 */

#ifndef AUTOMATA_H_
#define AUTOMATA_H_

#include "Productions.h"
#include "Grammar.h"

typedef struct Automata * AutomataADT;

/*Constructor-destructor*/
AutomataADT newAutomata(void);
void freeAutomata(AutomataADT  automata);

/*Getters*/
char * getStates(AutomataADT automata);
char * getSymbols(AutomataADT automata);
char * getFinalStates(AutomataADT automata);
char getInitialstate(AutomataADT automata);
ProductionsADT getDerivations(AutomataADT automata);
int getQuantStates(AutomataADT automata);
int getQuantSymbols(AutomataADT automata);
int getQuantFinalStates(AutomataADT automata);

/*Setters*/
void setStates(AutomataADT automata, char * states, int quant);
void setSymbols(AutomataADT automata, char * symbols, int quant);
void setFinalStates(AutomataADT automata, char * finalstates, int quant);
void setInitialstate(AutomataADT automata, char initialState);
void setDerivations(AutomataADT automata,ProductionsADT  derivations);

/*Utility*/
void printAutomata(AutomataADT automata);
int lenght(char * array);

/*Conversion*/
GrammarADT toGrammar(AutomataADT automata);


#endif /* AUTOMATA_H_ */
