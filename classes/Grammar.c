/*
 * Grammar.c
 *
 *  Created on: May 14, 2012
 *      Author: joseignaciosantiagogalindo
 */

# include <stdio.h>
# include <stdlib.h>
# include "../include/Grammar.h"
# include "../include/Productions.h"
# include "../include/Production.h"


typedef struct Grammar{
	char * terminals;
	char * nonterminals;
	char distinguished;
	ProductionsADT productions;
}Grammar;

/*Constructor-destructor*/
GrammarADT newGrammar(void){
	GrammarADT grammar;
	grammar = malloc(sizeof(GrammarADT));
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

/*Setters*/
void setTerminals(GrammarADT grammar, char * terminals){
	grammar->terminals = terminals;
}
void setNonTerminals(GrammarADT grammar, char * nonterminals){
	grammar->nonterminals = nonterminals;
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
	for(i=0; getTerminals(grammar)[i]!= '\0';i++){
		printf(" %c ",getTerminals(grammar)[i]);
	}
	printf("}\n");
	printf("Non Terminals: {");
	for(i=0;getNonTerminals(grammar)[i]!= '\0';i++){
		printf(" %c ",getNonTerminals(grammar)[i]);
	}
	printf("}\n");
	printProductions(getProductions(grammar));
	return;
}
