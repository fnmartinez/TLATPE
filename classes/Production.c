/*
 * Production.c
 *
 *  Created on: May 14, 2012
 *      Author: joseignaciosantiagogalindo
 */

# include <stdio.h>
# include <stdlib.h>
# include "../include/Production.h"

typedef struct Production{
	char production[3];
}Production;

/*Constructor-destructor*/
ProductionADT newProduction(char first, char sec, char third){
	ProductionADT p = malloc(sizeof(ProductionADT));
	setComponent(p,0,first);
	setComponent(p,1,sec);
	setComponent(p,2,third);
	return p;
}
void freeProduction(ProductionADT p){
	free(p);
}

/*Getters*/
char getComponent(ProductionADT p, int i){
	if(i < 0 ||i > 3){
		return -1;
	}
	return p->production[i];
}

/*Setters*/
void setComponent(ProductionADT p, int i, char comp){
	p->production[i] = comp;
	return;
}

/*Utility*/
void printProduction(ProductionADT p, int i){
	printf("%c -> %c%c\n", p->production[0],p->production[1],p->production[2]);
	return;
}
