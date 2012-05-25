/*
 * Production.h
 *
 *  Created on: May 25, 2012
 *      Author: joseignaciosantiagogalindo
 */

#ifndef PRODUCTION_H_
#define PRODUCTION_H_

#include "Derivation.h"
#define PRODSIZE 3


typedef struct Production * ProductionADT;


/*Constructor-destructor*/
ProductionADT newProduction(char first, char sec, char third);
ProductionADT newEmptyProduction();
void freeProduction(ProductionADT p);

/*Getters*/
char getProductionComponent(ProductionADT p, int i);

/*Setters*/
void setProductionComponent(ProductionADT p, int i, char comp);

/*Utility*/
void printProduction(ProductionADT p, int i);
int equals(ProductionADT p1, ProductionADT p2);

/*Conversion*/
/*DerivationADT toDerivation(ProductionADT p);*/

#endif /* PRODUCTION_H_ */
