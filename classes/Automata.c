/*
 * Automata.c
 *
 *  Created on: May 14, 2012
 *      Author: joseignaciosantiagogalindo
 */

# include "../include/Automata.h"

/*Constructor-destructor*/
AutomataADT newAutomata(void){
	AutomataADT a = (AutomataADT)malloc(sizeof(struct Automata));
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
/*DerivationsADT getDerivations(AutomataADT automata){*/
DerivationsADT getDerivations(AutomataADT automata){
	return automata->derivations;
}
int getQuantStates(AutomataADT automata){
	return automata->quantstates;
}
int getQuantSymbols(AutomataADT automata){
	return automata->quantsymbols;
}
int getQuantFinalStates(AutomataADT automata){
	return automata->quantfinalstates;
}

/*Setters*/
void setStates(AutomataADT automata, char * states, int quant){
	automata->states = malloc(sizeof(char)*quant);
	memcpy( automata->states, states, quant);
	automata->quantstates = quant;
}
void setSymbols(AutomataADT automata, char * symbols, int quant){
	automata->symbols = malloc(sizeof(char)*quant);
	memcpy( automata->symbols, symbols, quant);
	automata->quantsymbols = quant;
}
void setFinalStates(AutomataADT automata, char * finalstates, int quant){
	automata->finalstates = malloc(sizeof(char)*quant);
	memcpy( automata->finalstates, finalstates, quant);
	automata->quantfinalstates = quant;
}
void setInitialstate(AutomataADT automata, char initialState){
	automata->initialstate = initialState;
}
void setDerivations(AutomataADT automata, DerivationsADT  derivations){
	automata->derivations = derivations;
}


/*Utility*/
void printAutomata(AutomataADT automata){
	printf("Automata\n");
		printf("InitialState: %c \n",getInitialstate(automata));
		int i ;
		printf("States: {");
		for(i=0;i < getQuantStates(automata);i++){
			printf(" %c ",getStates(automata)[i]);
		}
		printf("}\n");
		printf("Symbols: {");
		for(i=0;i < getQuantSymbols(automata);i++){
			printf(" %c ",getSymbols(automata)[i]);
		}
		printf("}\n");
		printf("Final States: {");
		for(i=0;i < getQuantFinalStates(automata);i++){
			printf(" %c ",getFinalStates(automata)[i]);
		}
		printf("}\n");
		printDerivations(getDerivations(automata));
		return;
}

