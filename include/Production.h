/*
 * Production.h
 *
 *  Created on: May 14, 2012
 *      Author: joseignaciosantiagogalindo
 */

#ifndef PRODUCTION_H_
#define PRODUCTION_H_

# define PRODSIZE 3

typedef struct Production * ProductionADT;


/*Constructor-destructor*/
ProductionADT newProduction(char first, char sec, char third);
void freeProduction(ProductionADT  p);

/*Getters*/
char getComponent(ProductionADT p, int i);

/*Setters*/
void setComponent(ProductionADT p, int i, char comp);

/*Utility*/
void printProduction(ProductionADT p, int i);


#endif /* PRODUCTION_H_ */
