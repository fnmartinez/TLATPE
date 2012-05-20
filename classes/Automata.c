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
	ProductionsADT derivations;
	char initialstate;
	char * states;
	char * finalstates;
	char * symbols;
	int quantstates;
	int quantsymbols;
	int quantfinalstates;
}Automata;

/*Constructor-destructor*/
AutomataADT newAutomata(void){
	AutomataADT a = (AutomataADT)malloc(sizeof(AutomataADT));
	return a;
}
void freeAutomata(AutomataADT  automata){
	free(automata->finalstates);
	/*free(automata->states);
	free(automata->symbols);
	free(automata);*/
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
void setDerivations(AutomataADT automata,ProductionsADT  derivations){
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
		printProductions(getDerivations(automata));
		return;
}

/*Conversion*/
GrammarADT toGrammar(AutomataADT automata){
	GrammarADT g = newGrammar();
	setNonTerminals(g,getStates(automata), getQuantStates(automata));
	setTerminals(g, getSymbols(automata), getQuantSymbols(automata));
	setDistinguished(g,getInitialstate(automata));
	ProductionsADT derivations = getDerivations(automata);
	int n = getQuant(derivations);
	int quantfinals = getQuantFinalStates(automata);
	int i;
	ProductionADT deriv;
	ProductionsADT prods = newProductions(n+quantfinals);
	ProductionADT array[n+quantfinals];
	for (i=0; i<n; i++){
		deriv = getProduction(derivations,i);
		setComponent(array[i],0,getComponent(deriv,0));
		setComponent(array[i],1,getComponent(deriv,1));
		setComponent(array[i],2,getComponent(deriv,2));
		setProduction(prods,i,array[i]);
	}
	/*if P is in F , the production P->/ should be included*/
	for(; i-n<quantfinals; i++){
		setComponent(array[i],0,getFinalStates(automata)[i-n]);
		setComponent(array[i],1,'/');
		setComponent(array[i],2,'/');
		setProduction(prods,i,array[i]);
	}
	setProductions(g,prods);

	return g;
}


