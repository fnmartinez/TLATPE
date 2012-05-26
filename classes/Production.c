/*
 * Production.c
 *
 *  Created on: May 14, 2012
 *      Author: joseignaciosantiagogalindo
 */

# include <stdio.h>
# include <stdlib.h>
# include "../include/Production.h"
# include "../include/Derivation.h"


typedef struct Production{
	char production[PRODSIZE];
}Production;

DerivationADT toDerivation(ProductionADT p);

/*Constructor-destructor*/
ProductionADT newProduction(char first, char sec, char third){
	ProductionADT p = malloc(sizeof(struct Production));
	setProductionComponent(p,0,first);
	setProductionComponent(p,1,sec);
	setProductionComponent(p,2,third);
	return p;
}
ProductionADT newEmptyProduction(){
	ProductionADT p = calloc(1,sizeof( Production));
	return p;
}
void freeProduction(ProductionADT p){
	free(p);
}

/*Getters*/
char getProductionComponent(ProductionADT p, int i){
	if(i < 0 ||i >= PRODSIZE){
		return -1;
	}
	return p->production[i];
}

/*Setters*/
void setProductionComponent(ProductionADT p, int i, char comp){
	p->production[i] = comp;
	return;
}

/*Conversion*/
DerivationADT toDerivation(ProductionADT p){
	return newDerivation( getProductionComponent(p,0),getProductionComponent(p,1),
			getProductionComponent(p,2) );
}

/*Utility*/
void printProduction(ProductionADT p, int i){
	printf("\t %c -> %c%c\n", p->production[0],p->production[1],p->production[2]);
	return;
}
int equals(ProductionADT p1, ProductionADT p2){
	if ( getProductionComponent(p1,0) == getProductionComponent(p2,0) &&
		getProductionComponent(p1,1) == getProductionComponent(p2,1) &&
		getProductionComponent(p1,2) == getProductionComponent(p2,2) ){
		return 1;
	}
	return 0;
}
int isUnitary(ProductionADT p){
	int first = getProductionComponent(p,0);
	int sec = getProductionComponent(p,1);
	int third = getProductionComponent(p,2);
	if (first == sec || first == third){
		return 1;
	}
	return 0;
}
