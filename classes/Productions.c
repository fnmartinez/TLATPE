/*
 * Productions.c
 *
 *  Created on: May 14, 2012
 *      Author: joseignaciosantiagogalindo
 */

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "../include/Production.h"
# include "../include/Productions.h"

typedef struct Productions{
	int n;
	ProductionADT * productions;
}Productions;

/*Constructor-destructor*/
ProductionsADT newProductions(int n){
	ProductionsADT p = malloc(sizeof(ProductionsADT));
	p->productions = malloc(sizeof(ProductionADT)*n);
	p->n = n;
	return p;
}
void freeProductions(ProductionsADT  productions){
	free(productions->productions);
	free(productions);
}

/*Getters*/
char  getQuant(ProductionsADT productions){
	return productions->n;
}
ProductionADT getProduction(ProductionsADT productions, int i){
	return productions->productions[i];
}

/*Setters*/
void setProduction(ProductionsADT productions, int i, ProductionADT pr){
	productions->productions[i] = malloc(sizeof(ProductionADT));
	memcpy(productions->productions[i], pr, sizeof(ProductionADT) );
}

/*Utility*/
void printProductions(ProductionsADT productions){
	printf("Productions: { \n");
	int i;
	for(i=0; i<getQuant(productions);i++){
		printProduction(getProduction(productions,i),i);
	}
	printf("}\n");
}



