/*
 * Grammar.c
 *
 *  Created on: May 14, 2012
 *      Author: joseignaciosantiagogalindo
 */

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>
# include "../include/Grammar.h"
# include "../include/Automata.h"
# include "../include/Productions.h"
# include "../include/Production.h"
# include "../include/Derivations.h"
# include "../include/Derivation.h"
# include "../include/TADS.h"
# include "../include/utils.h"

static void removeOnlyRightTerminals(GrammarADT grammar);
DerivationADT toDerivation(ProductionADT p);
static int isTerminal(char symbol);
static int isNonTerminal(char symbol);

typedef struct Grammar{
	ProductionsADT productions;
	char * terminals;
	char * nonterminals;
	int quantterminals;
	int quantnonterminals;
	char distinguished;
}Grammar;



/*Constructor-destructor*/
GrammarADT newGrammar(void){
	GrammarADT grammar;
	grammar = malloc(sizeof(struct Grammar));
	//grammar->productions = malloc(sizeof(ProductionADT));
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

	/*the automata´s symbols are equal to the grammar´s terminal symbols*/
	setSymbols(a, getTerminals(grammar), getQuantTerminals(grammar));

	/*the automata´s states are equal to the grammar´s non terminal symbols*/
	setStates(a, getNonTerminals(grammar), getQuantNonTerminals(grammar));

	/*the automata´s inital state is equal to the grammar distinguished symbol*/
	setInitialstate(a, getDistinguished(grammar));

	ProductionsADT productions = getProductions(grammar);
	int n = getQuant(productions);
	int finalstatesquant = 0;
	char * finalstates = malloc(sizeof(char));
	int i,derivationquant=0;
	char * aux;
	for(i=0; i<n; i++){
		if ( getProductionComponent(getProduction(productions,i),1) == '/' &&
				 getProductionComponent(getProduction(productions,i),2) == '/' ){
			if ( (aux = realloc(finalstates,sizeof(char)*(finalstatesquant+1)) ) == NULL ){
				  fprintf(stderr, "Not enough space for finalstates\n");
			}
			finalstates = aux;
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


static void removeUnitaryProductions(GrammarADT grammar){
	ProductionsADT  productions = getProductions(grammar);
	int i, n = getQuant(productions), unitaryquant = 0;
	char * unitaries;//auxiliar array
	for (i=0; i<n; i++ ){
		if (  getProductionComponent(getProduction(productions,i),1) == '/' &&
				isNonTerminal(getProductionComponent(getProduction(productions,i),2)) ) {
			unitaries = realloc(unitaries, sizeof(char)*(unitaryquant+1)*2);
			unitaries[unitaryquant*2] = getProductionComponent(getProduction(productions,i),0);
			unitaries[(unitaryquant*2)+1] =  getProductionComponent(getProduction(productions,i),2);
		}else if( isNonTerminal(getProductionComponent(getProduction(productions,i),1))  &&
					getProductionComponent(getProduction(productions,i),2) == '/'  ){
			unitaries = realloc(unitaries, sizeof(char)*(unitaryquant+1)*2);
			unitaries[unitaryquant*2] = getProductionComponent(getProduction(productions,i),0);
			unitaries[(unitaryquant*2)+1] =  getProductionComponent(getProduction(productions,i),1);
		}
	}
}


void removeUnreachableProductions(GrammarADT grammar){
	ProductionsADT  productions = getProductions(grammar);
	int i, quantproductions = getQuant(productions), reachablesquant=0,lastreachablesquant=0;
	char * reachables = malloc(sizeof(char));
	char * aux1 = NULL;
	/*starts only with distinguished symbol, if it is in the current productions*/
	if(inCurrentProductions(productions,getDistinguished(grammar))){
		printf("\n\n HEREEEEEE: %d",inCurrentProductions(productions,getDistinguished(grammar)));
		reachables[reachablesquant++] = getDistinguished(grammar);
	}
	/*until something the quantity of reachables varies*/
	while (reachablesquant != lastreachablesquant){
		lastreachablesquant = reachablesquant;
		for(i=0; i<quantproductions; i++){
			char first = getProductionComponent(getProduction(productions,i),0);
			char sec = getProductionComponent(getProduction(productions,i),1);
			char third = getProductionComponent(getProduction(productions,i),2);
			/*if the symbol of the left is contained in the reachables, the non terminal
			 * symbols of the right must be added*/
			if (containsChar(reachables,reachablesquant,first)){
				/*if the second symbol is nonterminal and is not yet in the
				 * reachable list, it must be added*/
				if ( isNonTerminal( sec ) &&
						!containsChar(reachables,reachablesquant,sec)){
					 if ( ( aux1 = realloc(reachables, sizeof(char)*(reachablesquant+1)) ) == NULL ){
						fprintf(stderr, "Error doing realloc \n");
					 }
					 reachables = aux1;
					 reachables[reachablesquant++] = sec;
				}/*if the third symbol is nonterminal and is not yet in the
				 * reachable list, it must be added*/
				else if( isNonTerminal(third) &&
						!containsChar(reachables,reachablesquant,third) ){
					 if ( (aux1 = realloc(reachables, sizeof(char)*(reachablesquant+1)) ) == NULL ){
						fprintf(stderr, "Error doing realloc \n");
					 }
					 reachables = aux1;
					 reachables[reachablesquant++] = third;
				}
			}
		}
	}
	int symsToRemovequant=0;
	//remove the unreachable productions
	/*If the quantity of reachables is equal to the quantity of nonterminals,
	 * nothing should be removed*/
	if (reachablesquant != getQuantNonTerminals(grammar)){
		char * symsToRemove = NULL;
		symsToRemovequant = getDifferents(getNonTerminals(grammar),
				getQuantNonTerminals(grammar) ,reachables, reachablesquant, &symsToRemove);
		printf("\nTO REMOVE:");
		printArray(symsToRemove,symsToRemovequant );
		for(i=0; i<symsToRemovequant; i++){
			removeProduction(productions,symsToRemove[i]);
		}
	}

}


/*
static void removeOnlyRightTerminals(GrammarADT grammar){

}
static void convertToRight(){

}*/

static int isTerminal(char symbol){
	return islower(symbol);
}

static int isNonTerminal(char symbol){
	return isupper(symbol);
}


