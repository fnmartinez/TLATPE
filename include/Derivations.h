/*
 * Derivations.h
 *
 *  Created on: May 24, 2012
 *      Author: joseignaciosantiagogalindo
 */

#ifndef DERIVATIONS_H_
#define DERIVATIONS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Derivation.h"

typedef struct Derivations{
	int n;
	DerivationADT * derivations;
}Derivations;

typedef struct Derivations * DerivationsADT;

/*Constructor-destructor*/
DerivationsADT newDerivations(int n);
void freeDerivations(DerivationsADT derivations);

/*Getters*/
int getDerivationsQuant(DerivationsADT derivations);
DerivationADT getDerivation(DerivationsADT derivations, int i);

/*Setters*/
void setDerivation(DerivationsADT derivations, int i, DerivationADT derivation);
void setDerivationQuant(DerivationsADT derivations, int n);

/*Utility*/
void printDerivations(DerivationsADT derivations);


#endif /* DERIVATIONS_H_ */
