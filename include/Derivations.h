/*
 * Derivations.h
 *
 *  Created on: May 24, 2012
 *      Author: joseignaciosantiagogalindo
 */

#ifndef DERIVATIONS_H_
#define DERIVATIONS_H_

# include "Derivation.h"
# include "TADS.h"



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
