/*
 * AutomataTest.c
 *
 *  Created on: May 14, 2012
 *      Author: joseignaciosantiagogalindo
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Converter.h"
#include "../include/Automata.h"
#include "../include/Grammar.h"
#include "../include/Productions.h"
#include "../include/Production.h"

void init();
void destroy();
void basicTest();
void automataToGrammarTest();

AutomataADT  a;
DerivationADT d1;
DerivationADT d2;
DerivationsADT dervs;

int main(void)
{
	init();
	basicTest();
	automataToGrammarTest();
	destroy();
	return 0;

}

void init(){
	 a = newAutomata();
	setInitialstate( a,'S');
	char * states = malloc(sizeof(char)*3);
	char * symbols = malloc(sizeof(char)*2);
	char * fnstates = malloc(sizeof(char)*2);

	fnstates[0] = 'A';
	fnstates[1] = 'B';
	setFinalStates( a,fnstates,2);

	states[0] = 'S';
	states[1] = 'A';
	states[2] = 'B';
	setStates( a,states,3);

	symbols[0] = 'a';
	symbols[1] = 'b';
	setSymbols( a,symbols,2);


	/*S->aA*/
	d1 = newDerivation('S','a','A');
	/*A-> bB*/
	d2 = newDerivation('A','b','B');

	dervs = newDerivations(2);
	setDerivation(dervs,0,d1);
	setDerivation(dervs,1,d2);

	setDerivations( a,dervs);


	free(states);
	free(symbols);
	free(fnstates);
}

void destroy(){
	freeDerivation(d1);
	freeDerivation(d2);
	freeDerivations(dervs);
	freeAutomata( a);
}
void basicTest(){
	printf("Testing Automata Structures / Basic \n");
	printAutomata( a);
	printf("\n");
}


void automataToGrammarTest(){
	printf("Testing Automata to Grammar Conversion \n");
	GrammarADT g = toGrammar( a);
	printGrammar(g);
	printf("\n");
}
