/*
 * Grammar.c
 *
 *  Created on: May 14, 2012
 *      Author: joseignaciosantiagogalindo
 */

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "../include/Grammar.h"
# include "../include/Automata.h"
# include "../include/Productions.h"
# include "../include/Production.h"
# include "../include/Derivations.h"
# include "../include/Derivation.h"
# include "../include/TADs.h"



typedef struct Grammar{
	ProductionsADT productions;
	char * terminals;
	char * nonterminals;
	int quantterminals;
	int quantnonterminals;
	char distinguished;
}Grammar;

DerivationADT toDerivation(ProductionADT p);


/*Constructor-destructor*/
GrammarADT newGrammar(void){
	GrammarADT grammar;
	grammar = malloc(sizeof(struct Grammar));
	return grammar;
}
void freeGrammar(GrammarADT grammar){
	free(grammar->nonterminals);
	free(grammar->terminals);
	free(grammar);
}

/*Getters*/
char * getTerminals(GrammarADT grammar){
	return grammar->terminals;
}
char * getNonTerminals(GrammarADT grammar){
	return grammar->nonterminals;
}
char getDistinguished(GrammarADT grammar){
	return grammar->distinguished;
}
ProductionsADT  getProductions(GrammarADT grammar){
	return grammar->productions;
}
int getQuantTerminals(GrammarADT grammar){
	return grammar->quantterminals;
}
int getQuantNonTerminals(GrammarADT grammar){
	return grammar->quantnonterminals;
}

/*Setters*/
void setTerminals(GrammarADT grammar, char * terminals, int quant){
	grammar->terminals = malloc(sizeof(char)*quant);
	memcpy(grammar->terminals, terminals, quant);
	grammar->quantterminals = quant;
}
void setNonTerminals(GrammarADT grammar, char * nonterminals, int quant){
	grammar->nonterminals = malloc(sizeof(char)*quant);
	memcpy(grammar->nonterminals,nonterminals, quant);
	grammar->quantnonterminals = quant;
}
void setDistinguished(GrammarADT grammar, char distinguished){
	grammar->distinguished = distinguished;
}
void setProductions(GrammarADT grammar,ProductionsADT productions){
	grammar->productions = productions;
}

/*Utility*/
void printGrammar(GrammarADT grammar){

	printf("Grammar\n");
	printf("Distinguished: %c \n",getDistinguished(grammar));
	int i ;
	printf("Terminals: {");
	for(i=0;i < getQuantTerminals(grammar);i++){
		printf(" %c ",getTerminals(grammar)[i]);
	}
	printf("}\n");
	printf("Non Terminals: {");
	for(i=0;i < getQuantNonTerminals(grammar);i++){
		printf(" %c ",getNonTerminals(grammar)[i]);
	}
	printf("}\n");
	printProductions(getProductions(grammar));
	return;
}

AutomataADT toAutomata(GrammarADT grammar){
	AutomataADT a = newAutomata();
	setSymbols(a, getTerminals(grammar), getQuantTerminals(grammar));
	setStates(a, getNonTerminals(grammar), getQuantNonTerminals(grammar));
	setInitialstate(a, getDistinguished(grammar));
	ProductionsADT productions = getProductions(grammar);
	int n = getQuant(productions);
	int finalstatesquant = 0;
	char * finalstates = malloc(sizeof(char));
	int i,derivationquant=0;
	for(i=0; i<n; i++){
		if ( getProductionComponent(getProduction(productions,i),1) == '/' &&
				 getProductionComponent(getProduction(productions,i),2) == '/' ){
			if ( realloc(finalstates,sizeof(char)*(finalstatesquant+1)) == NULL ){
				  fprintf(stderr, "Not enough space for finalstates\n");
			}
			finalstates[finalstatesquant++] = getProductionComponent(getProduction(productions,i),0);
		}
	}
	setFinalStates(a, finalstates, finalstatesquant);
	DerivationsADT derivations = newDerivations(n-finalstatesquant);
	for(i=0; i<n; i++){
		if ( getProductionComponent(getProduction(productions,i),1) != '/' ||
						 getProductionComponent(getProduction(productions,i),2) != '/' ){
			setDerivation(derivations,derivationquant++, (DerivationADT) toDerivation( getProduction(productions,i) ) );
		}
	}
	setDerivations(a,derivations);
	return a;
}

