/*
 * Automata.h
 *
 *  Created on: May 14, 2012
 *      Author: joseignaciosantiagogalindo
 */

#ifndef AUTOMATA_H_
#define AUTOMATA_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "Derivation.h"
#include "Derivations.h"
#include "utils.h"

#ifndef LAMDA
#define LAMDA '\\'
#endif


typedef struct Automata{
	DerivationsADT derivations;
	char initialstate;
	char * states;
	char * finalstates;
	char * symbols;
	int quantstates;
	int quantsymbols;
	int quantfinalstates;
}Automata;

typedef struct Automata * AutomataADT;

/*Constructor-destructor*/
AutomataADT newAutomata(void);
void freeAutomata(AutomataADT  automata);

/*Getters*/
char * getStates(AutomataADT automata);
char * getSymbols(AutomataADT automata);
char * getFinalStates(AutomataADT automata);
char getInitialstate(AutomataADT automata);
DerivationsADT getDerivations(AutomataADT automata);
int getQuantStates(AutomataADT automata);
int getQuantSymbols(AutomataADT automata);
int getQuantFinalStates(AutomataADT automata);

/*Setters*/
void setStates(AutomataADT automata, char * states, int quant);
void setSymbols(AutomataADT automata, char * symbols, int quant);
void setFinalStates(AutomataADT automata, char * finalstates, int quant);
void setInitialstate(AutomataADT automata, char initialState);
void setDerivations(AutomataADT automata, DerivationsADT  derivations);


/*Utility*/
void printAutomata(AutomataADT automata);
int lenght(char * array);

/*Conversion*/
void toDot(AutomataADT automata);
void drawDot(char* dotLocation, char* source, char* dest);

#endif /* AUTOMATA_H_ */
