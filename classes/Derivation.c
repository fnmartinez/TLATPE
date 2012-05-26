/*
 * Derivation.c
 *
 *  Created on: May 25, 2012
 *      Author: joseignaciosantiagogalindo
 */

#include "../include/Derivation.h"


DerivationADT newDerivation(char first, char sec, char third){
	DerivationADT p = malloc(sizeof(struct Derivation));
	setDerivationComponent(p,0,first);
	setDerivationComponent(p,1,sec);
	setDerivationComponent(p,2,third);
	return p;
}
DerivationADT newEmptyDerivation(){
	DerivationADT p = malloc(sizeof(struct Derivation));
	return p;
}
void freeDerivation(DerivationADT p){
	free(p);
}

/*Getters*/
char getDerivationComponent(DerivationADT p, int i){
	if(i < 0 ||i >= DERVSIZE){
		return -1;
	}
	return p->derivation[i];
}

/*Setters*/
void setDerivationComponent(DerivationADT p, int i, char comp){
	p->derivation[i] = comp;
	return;
}

/*Utility*/
void printDerivation(DerivationADT p, int i){
	printf("\t delta(%c,%c) = %c \n", p->derivation[0],p->derivation[1],p->derivation[2]);
	return;
}
