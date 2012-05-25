/*
 * Derivations.c
 *
 *  Created on: May 24, 2012
 *      Author: joseignaciosantiagogalindo
 */

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "../include/Derivations.h"

typedef struct Derivations{
	int n;
	DerivationADT * derivations;
}Derivations;

/*Constructor-destructor*/
DerivationsADT newDerivations(int n){
	DerivationsADT p = (DerivationsADT)calloc(1, sizeof(struct Derivations));
	p->derivations = calloc(n,sizeof(struct Derivations));
	p->n = n;
	return p;
}
void freeDerivations(DerivationsADT  productions){
	free(productions->derivations);
	free(productions);
}

/*Getters*/
int  getDerivationsQuant(DerivationsADT derivations){
	return derivations->n;
}
DerivationADT getDerivation(DerivationsADT derivations, int i){
	char first = getDerivationComponent(derivations->derivations[i], 0);
	char second = getDerivationComponent(derivations->derivations[i],1);
	char third = getDerivationComponent(derivations->derivations[i], 2);
	DerivationADT p = newDerivation(first, second, third);
	return p;

}

/*Setters*/
void setDerivation(DerivationsADT derivations, int i, DerivationADT derivation){
	derivations->derivations[i] = derivation;
}

/*Utility*/
void printDerivations(DerivationsADT derivations){
	printf("Derivations: { \n");
	int i;
	for(i=0; i<getDerivationsQuant(derivations);i++){
		printDerivation(getDerivation(derivations,i),i);
	}
	printf("}\n");
}



