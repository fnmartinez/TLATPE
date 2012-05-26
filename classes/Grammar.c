/*
 * Grammar.c
 *
 *  Created on: May 14, 2012
 *      Author: joseignaciosantiagogalindo
 */
#include "../include/Grammar.h"
#include "../include/Automata.h"


/*Constructor-destructor*/
GrammarADT newGrammar(void){
	GrammarADT grammar;
	grammar = malloc(sizeof(struct Grammar));
	/*grammar->productions = malloc(sizeof(ProductionADT));*/
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
	int i,j,k, productionquant = getQuant(productions), unitaryquant = 0, lastunitaryquant = 0;
	/*auxiliar array for unitary productions*/
	char * unitaries = NULL;
	/*iterate over productions and determine first unitaries*/
	for (i=0; i< productionquant; i++){
		char first = getProductionComponent(getProduction(productions,i),0);
		char sec = getProductionComponent(getProduction(productions,i),1);
		char third = getProductionComponent(getProduction(productions,i),2);
		if ( isNonTerminal(sec) && third == '/' ){
			addPair(&unitaries,&unitaryquant,first, sec);
		}else if( isNonTerminal(third) && sec == '/'){
			addPair(&unitaries,&unitaryquant,first, third);
		}
	}
	/*iterate over unitaries, adding the closure*/
	while(unitaryquant != lastunitaryquant){
		lastunitaryquant = unitaryquant;
		for (i=0; i<unitaryquant ; i+=2){
			char first1 = unitaries[i];
			char sec1 = unitaries[i+1];
			for (j=0; j<unitaryquant ; j+=2){
				char first2 = unitaries[j];
				char sec2 = unitaries[j+1];
				/*(A,B)(B,C)-> (A,C)*/
				if (sec1 == first2 ){
					if (!containsPair(unitaries,unitaryquant,first1,sec2) &&
							first1 != sec2 ){
						addPair(&unitaries,&unitaryquant,first1,sec2);
					}
				}
			}
		}
	}
	printByPairs(unitaries,unitaryquant);
	printf("unitaries quant: %d\n", unitaryquant/2);
	/*create the new productions and remove the unitaries*/
	for(i=0; i<productionquant; i++){
		ProductionADT p1 = getProduction(productions,i);
		if ( isUnitary(p1) ){
			char first1 = getProductionComponent(p1,0);
			char sec1 = getProductionComponent(p1,1);
			char third1 = getProductionComponent(p1,2);
			for(j=0;j<unitaryquant;j+=2){
				char uni1 = unitaries[j];
				char uni2 = unitaries[j+1];
				//A->B and (A,B)
				if ((first1 == uni1) && (sec1 == uni2 || third1 == uni2 )){
					for(k=0; k<productionquant; k++ ){
						ProductionADT p2 = getProduction(productions,k);
						char first2 = getProductionComponent(p2,0);
						char sec2 = getProductionComponent(p2,1);
						char third2 = getProductionComponent(p2,2);
						if(first2 == uni2 ){
							if(!isUnitary(p2)){
								addProduction(productions,newProduction(first1,sec2,third2));
							}
						}
					}
				}
			}
			removeParticularProduction(productions,p1);
			free(p1);
		}
	}


}


void removeUnproductiveProductions(GrammarADT grammar){
	ProductionsADT  productions = getProductions(grammar);
	int i, quantproductions = getQuant(productions), productivequant=0,lastproductivequant=0;
	char * productives = NULL;
	char * aux1 = NULL;
	while(productivequant != lastproductivequant){
		lastproductivequant = productivequant;
		for( i=0; i< quantproductions;i++ ){
			ProductionADT p1 = getProduction(productions,i);
			int first1 = getProductionComponent(p1,0);
			int sec1 = getProductionComponent(p1,1);
			int third1 = getProductionComponent(p1,2);

			if ( ( sec1 == '/' && third1 == '/' ) || /*lamda*/
				 (isTerminal(sec1) && isTerminal(third1) ) || /*both terminal*/
				 (   isTerminal(sec1) && third1 == '/'   ) || /*one terminal*/
				 (   isTerminal(third1) && sec1 == '/'   ) ||
				 /*one terminal and one productive*/
				 (isTerminal(sec1) && ( isNonTerminal(third1) && containsChar(productives,productivequant,third1) ) ) ||
				 (isTerminal(third1) && ( isNonTerminal(sec1) && containsChar(productives,productivequant,sec1) ) ) ){
				 if ( ( aux1 = realloc(productives, sizeof(char)*(productivequant+1)) ) == NULL ){
						fprintf(stderr, "Error doing realloc \n");
				 }
				 productives[productivequant++] = first1;
			}
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
	/*remove the unreachable productions*/
	/*If the quantity of reachables is equal to the quantity of nonterminals,
	 * nothing should be removed*/
	if (reachablesquant != getQuantNonTerminals(grammar)){
		char * symsToRemove = NULL;
		symsToRemovequant = getDifferents(getNonTerminals(grammar),
				getQuantNonTerminals(grammar) ,reachables, reachablesquant, &symsToRemove);
		/*printf("\nTO REMOVE:");
		printArray(symsToRemove,symsToRemovequant );*/
		for(i=0; i<symsToRemovequant; i++){
			removeProduction(productions,symsToRemove[i]);
		}
	}

}


void removeOnlyRightTerminals(GrammarADT grammar){
	char abc[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int l = strlen(abc);
	int i, j;
	int found = FALSE;

	for(j=0; j< getQuant(getProductions(grammar)); j++)
	{
		if((isTerminal(getProductionComponent(getProduction(getProductions(grammar),j), 1)) &&
				getProductionComponent(getProduction(getProductions(grammar),j), 2) == LAMDA) ||
				(isTerminal(getProductionComponent(getProduction(getProductions(grammar),j), 2)) &&
						getProductionComponent(getProduction(getProductions(grammar),j), 1) == LAMDA ))
		{
			found = TRUE;
			break;
		}
	}

	if(!found){
		return;
	}
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
			printProduction(getProduction(getProductions(grammar),j));
			setProductionComponent(getProduction(getProductions(grammar),j), 2, getProductionComponent(getProduction(getProductions(grammar),j), 1));
			setProductionComponent(getProduction(getProductions(grammar),j), 1, abc[i]);
		}
		if(isTerminal(getProductionComponent(getProduction(getProductions(grammar),j), 2)) &&
				getProductionComponent(getProduction(getProductions(grammar),j), 1) == LAMDA )
		{
			printProduction(getProduction(getProductions(grammar),j));
			setProductionComponent(getProduction(getProductions(grammar),j), 1, abc[i]);
		}
	}

	addProduction(getProductions(grammar), newProduction(abc[i],LAMDA,LAMDA));

	return;
}

void convertToRight(GrammarADT grammar){

	int i;
	char nd = 0;
	int ml = FALSE;

	for(i=0; i < getQuant(getProductions(grammar)); i++){
		if(getProductionComponent(getProduction(getProductions(grammar), i), 1) == LAMDA &&
				getProductionComponent(getProduction(getProductions(grammar), i), 2) == LAMDA){
			if(nd != 0)
			{
				ml = TRUE; //More than one lamda production exist.
				break;
			}
			nd = getProductionComponent(getProduction(getProductions(grammar), i), 0);
		}
	}

	ProductionsADT ps = newProductions(0);
	for(i = 0; i < getQuant(getProductions(grammar)); i++){
		if(isNonTerminal(getProductionComponent(getProduction(getProductions(grammar), i), 1))){
			addProduction(ps, newProduction(getProductionComponent(getProduction(getProductions(grammar), i), 1),
					getProductionComponent(getProduction(getProductions(grammar), i), 2),
					getProductionComponent(getProduction(getProductions(grammar), i), 0)));
		}
	}

	setProductions(grammar, ps);
	if(!ml){
		addProduction(ps, newProduction(getDistinguished(grammar), LAMDA, LAMDA));
		setDistinguished(grammar, nd);
	}
}

void toFile(GrammarADT grammar){
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

void actualizeTerminals(GrammarADT grammar){
	int termquant = getQuantTerminals(grammar);
	char * termsfounded = NULL ;
	char * aux1= NULL;
	int termsfoundedsize =0;
	ProductionsADT productions = getProductions(grammar);
	int productionquant = getQuant(productions),i;
	/*detect current terminals*/
	for (i=0; i<productionquant; i++){
		ProductionADT p = getProduction(productions,i);
		char sec = getProductionComponent(p,1);
		char third = getProductionComponent(p,2);
		if (isTerminal(sec) && !containsChar(termsfounded,termsfoundedsize,sec) ){
			addChar(&termsfounded, &termsfoundedsize, sec);
		}
		if(isTerminal(third) && !containsChar(termsfounded,termsfoundedsize,third)){
			addChar(&termsfounded, &termsfoundedsize, third);
		}
	}
	/*actualize terminals*/
	if( termsfoundedsize != termquant ){
		/*there are less current terminals*/
		setTerminals(grammar,termsfounded,termsfoundedsize);
	}
}

void actualizeNonTerminals(GrammarADT grammar){
	int nontermquant = getQuantTerminals(grammar);
	char * nontermsfounded = NULL ;
	char * aux1= NULL;
	int nontermsfoundedsize =0;
	ProductionsADT productions = getProductions(grammar);
	int productionquant = getQuant(productions),i;
	/*detect current terminals*/
	for (i=0; i<productionquant; i++){
		ProductionADT p = getProduction(productions,i);
		char first = getProductionComponent(p,0);
		char sec = getProductionComponent(p,1);
		char third = getProductionComponent(p,2);
		if (isNonTerminal(first) && !containsChar(nontermsfounded,nontermsfoundedsize,first) ){
			addChar(&nontermsfounded, &nontermsfoundedsize, first);
		}
		if (isNonTerminal(sec) && !containsChar(nontermsfounded,nontermsfoundedsize,sec) ){
			addChar(&nontermsfounded, &nontermsfoundedsize, sec);
		}
		if(isNonTerminal(third) && !containsChar(nontermsfounded,nontermsfoundedsize,third)){
			addChar(&nontermsfounded, &nontermsfoundedsize, third);
		}
	}
	/*actualize terminals*/
	if( nontermsfoundedsize != nontermquant ){
		/*there are less current terminals*/
		setNonTerminals(grammar,nontermsfounded,nontermsfoundedsize);
	}

}

