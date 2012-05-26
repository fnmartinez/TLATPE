/*
 * Derivation.h
 *
 *  Created on: May 25, 2012
 *      Author: joseignaciosantiagogalindo
 */

#ifndef DERIVATION_H_
#define DERIVATION_H_

#include <stdio.h>
#include <stdlib.h>
#define DERVSIZE 3

typedef struct Derivation{
	char derivation[DERVSIZE];
}Derivation;

typedef struct Derivation * DerivationADT;

/*Constructor-destructor*/
DerivationADT newDerivation(char first, char sec, char third);
DerivationADT newEmptyDerivation();
void freeDerivation(DerivationADT p);

/*Getters*/
char getDerivationComponent(DerivationADT p, int i);

/*Setters*/
void setDerivationComponent(DerivationADT p, int i, char comp);

/*Utility*/
void printDerivation(DerivationADT p, int i);

/*Conversion*/
/*ProductionADT toProduction(DerivationADT d);*/

#endif /* DERIVATION_H_ */
