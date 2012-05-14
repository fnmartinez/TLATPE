/*
 * AutomataTest.c
 *
 *  Created on: May 14, 2012
 *      Author: joseignaciosantiagogalindo
 */
# include <stdio.h>
# include <stdlib.h>
# include "../include/Automata.h"
# include "../include/Productions.h"
# include "../include/Production.h"


void basicTest();

int main(void)
{
	basicTest();
	return 0;
}


void basicTest(){

	printf("Testing Automata Structures / Basic \n");
	AutomataADT a = newAutomata();
	setInitialstate(a,'S');
	char * states = malloc(sizeof(char)*3);
	states[0] = 'S';
	states[1] = 'A';
	states[2] = 'B';
	setStates(a,states);
	char * symbols = malloc(sizeof(char)*2);
	symbols[0] = 'a';
	symbols[1] = 'b';
	setSymbols(a,symbols);
	char * fnstates = malloc(sizeof(char)*2);
	fnstates[0] = 'A';
	fnstates[1] = 'B';
	setFinalStates(a,fnstates);

	/*S->aA*/
	ProductionADT p1 = newProduction('S','a','A');
	/*A-> bB*/
	ProductionADT p2 = newProduction('A','b','B');

	ProductionsADT prods = newProductions(2);
	setProduction(prods,0,p1);
	setProduction(prods,1,p2);

	setDerivations(a,prods);

	printAutomata(a);


	freeProduction(p1);
	freeProduction(p2);
	freeProductions(prods);
	/*freeAutomata(a);*/

}
