/*
 * Grammar.c
 *
 *  Created on: May 14, 2012
 *      Author: joseignaciosantiagogalindo
 */
#include "../include/Grammar.h"

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

void removeUnitaryProductions(GrammarADT grammar){
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


void removeOnlyRightTerminals(GrammarADT grammar){
	char abc[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int l = strlen(abc);
	int i, j;

	for(i = 0; i<l; i++){
		for(j = 0; j< getQuantNonTerminals(grammar) &&
				getNonTerminals(grammar)[j] != abc[i]; j++);
		if(j==getQuantNonTerminals(grammar))
		{
			break;
		}
	}

	char * nterm = getNonTerminals(grammar);
	int ntermQty = getQuantNonTerminals(grammar);

	char * aux = realloc(nterm, (ntermQty+1)*sizeof(char));
	if(aux == NULL)
	{
		printf("Error: Not enought memory\n");
		exit(1);
	}
	nterm[ntermQty] = abc[i];
	ntermQty++;
	setNonTerminals(grammar, nterm, ntermQty);

	for(j=0; j< getQuant(getProductions(grammar)); j++)
	{
		if(isTerminal(getProductionComponent(getProduction(getProductions(grammar),j), 1)) &&
				getProductionComponent(getProduction(getProductions(grammar),j), 2) == LAMDA )
		{
			printProduction(getProduction(getProductions(grammar),j),0);
			setProductionComponent(getProduction(getProductions(grammar),j), 2, getProductionComponent(getProduction(getProductions(grammar),j), 1));
			setProductionComponent(getProduction(getProductions(grammar),j), 1, abc[i]);
		}
		if(isTerminal(getProductionComponent(getProduction(getProductions(grammar),j), 2)) &&
				getProductionComponent(getProduction(getProductions(grammar),j), 1) == LAMDA )
		{
			printProduction(getProduction(getProductions(grammar),j),0);
			setProductionComponent(getProduction(getProductions(grammar),j), 1, abc[i]);
		}
	}

	addProduction(getProductions(grammar), newProduction(abc[i],LAMDA,LAMDA));

	return;
}

void convertToRight(){


}

void grammarToFile(GrammarADT grammar){
	FILE * fp = fopen("grammar.gr", "w");
	if(fp == NULL){
		printf("Error: File could not be created\n");
		fclose(fp);
		return;
	}

	fprintf(fp, "G1 = ({");

	int i;

	for(i = 0; i < getQuantNonTerminals(grammar); i++)	{
		fprintf(fp, "%c%s", getNonTerminals(grammar)[i], (i == getQuantNonTerminals(grammar)-1?"}":", "));
	}

	fprintf(fp, ", {");

	for(i = 0; i < getQuantTerminals(grammar); i++)	{
		fprintf(fp, "%c%s", getTerminals(grammar)[i], (i == getQuantTerminals(grammar)-1?"}":", "));
	}

	fprintf(fp, ", %c, {", getDistinguished(grammar));

	for(i = 0; i < getQuant(getProductions(grammar)); i++){
		fprintf(fp, "%c -> %c%c%s", getProductionComponent(getProduction(getProductions(grammar), i), 0),
				getProductionComponent(getProduction(getProductions(grammar), i), 1),
				getProductionComponent(getProduction(getProductions(grammar), i), 2),
				(i == getQuant(getProductions(grammar))? "}": ", "));
	}

	fprintf(fp, ")");
	fclose(fp);
	return;

}

int isTerminal(char symbol){
	return islower(symbol);
}

int isNonTerminal(char symbol){
	return isupper(symbol);
}


