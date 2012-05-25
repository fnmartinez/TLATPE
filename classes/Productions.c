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
	ProductionsADT p = (ProductionsADT)calloc(1, sizeof(struct Productions));
	p->productions = calloc(n,sizeof(struct Productions));
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
	char first = getProductionComponent(productions->productions[i],0);
	char second = getProductionComponent(productions->productions[i],1);
	char third = getProductionComponent(productions->productions[i], 2);
	ProductionADT p = newProduction(first, second, third);
	return p;

}

/*Setters*/
void setProduction(ProductionsADT productions, int i, ProductionADT pr){
	productions->productions[i] = pr;
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



