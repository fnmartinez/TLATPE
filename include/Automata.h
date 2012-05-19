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

/*Setters*/
void setStates(AutomataADT automata, char * states);
void setSymbols(AutomataADT automata, char * symbols);
void setFinalStates(AutomataADT automata, char * finalstates);
void setInitialstate(AutomataADT automata, char initialState);
void setDerivations(AutomataADT automata,ProductionsADT  derivations);

/*Utility*/
void printAutomata(AutomataADT automata);
int lenght(char * array);

/*Conversion*/
GrammarADT toGrammar(AutomataADT automata);


#endif /* AUTOMATA_H_ */
