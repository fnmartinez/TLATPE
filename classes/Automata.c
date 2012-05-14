/*
 * Automata.c
 *
 *  Created on: May 14, 2012
 *      Author: joseignaciosantiagogalindo
 */

# include <stdio.h>
# include <stdlib.h>
# include "../include/Automata.h"
# include "../include/Productions.h"
# include "../include/Production.h"

typedef struct Automata{
	char initialstate;
	char * states;
	char * symbols;
	char * finalstates;
	ProductionsADT derivations;
}Automata;

/*Constructor-destructor*/
AutomataADT newAutomata(void){
	AutomataADT a = malloc(sizeof(AutomataADT));
	return a;
}
void freeAutomata(AutomataADT  automata){
	free(automata->finalstates);
	free(automata->states);
	free(automata->symbols);
	free(automata);
}

/*Getters*/
char * getStates(AutomataADT automata){
	return automata->states;
}
char * getSymbols(AutomataADT automata){
	return automata->symbols;
}
char * getFinalStates(AutomataADT automata){
	return automata->finalstates;
}
char getInitialstate(AutomataADT automata){
	return automata->initialstate;
}
ProductionsADT getDerivations(AutomataADT automata){
	return automata->derivations;
}

/*Setters*/
void setStates(AutomataADT automata, char * states){
	automata->states = states;
}
void setSymbols(AutomataADT automata, char * symbols){
	automata->symbols = symbols;
}
void setFinalStates(AutomataADT automata, char * finalstates){
	automata->finalstates = finalstates;
}
void setInitialstate(AutomataADT automata, char initialState){
	automata->initialstate = initialState;
}
void setDerivations(AutomataADT automata,ProductionsADT  derivations){
	automata->derivations = derivations;
}

/*Utility*/
void printAutomata(AutomataADT automata){
	printf("Automata\n");
		printf("InitialState: %c \n",getInitialstate(automata));
		int i ;
		printf("States: {");
		for(i=0;getStates(automata)[i] != '\0';i++){
			printf(" %c ",getStates(automata)[i]);
		}
		printf("}\n");
		printf("Symbols: {");
		for(i=0; getSymbols(automata)[i]!= '\0';i++){
			printf(" %c ",getSymbols(automata)[i]);
		}
		printf("}\n");
		printf("Final States: {");
		for(i=0;getFinalStates(automata)[i]!= '\0';i++){
			printf(" %c ",getFinalStates(automata)[i]);
		}
		printf("}\n");
		printProductions(getDerivations(automata));
		return;
}
