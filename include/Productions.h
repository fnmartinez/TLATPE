/*
 * Productions.h
 *
 *  Created on: May 14, 2012
 *      Author: joseignaciosantiagogalindo
 */

#ifndef PRODUCTIONS_H_
#define PRODUCTIONS_H_

# include "Production.h"
# include "TADs.h"


/*Constructor-destructor*/
ProductionsADT newProductions(int n);
void freeProductions(ProductionsADT productions);

/*Getters*/
char getQuant(ProductionsADT productions);
ProductionADT getProduction(ProductionsADT productions, int i);

/*Setters*/
void setProduction(ProductionsADT productions, int i, ProductionADT pr);

/*Utility*/
void printProductions(ProductionsADT productions);


#endif /* PRODUCTIONS_H_ */
