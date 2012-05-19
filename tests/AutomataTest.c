/*
 * AutomataTest.c
 *
 *  Created on: May 14, 2012
 *      Author: joseignaciosantiagogalindo
 */
# include <stdio.h>
# include <stdlib.h>
# include "../include/Automata.h"
# include "../include/Grammar.h"
# include "../include/Productions.h"
# include "../include/Production.h"

void init();
void destroy();
void basicTest();
void automataToGrammarTest();

AutomataADT a;
ProductionADT p1;
ProductionADT p2;
ProductionsADT prods;

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
	setInitialstate(a,'S');
	char * states = malloc(sizeof(char)*4);
	states[0] = 'S';
	states[1] = 'A';
	states[2] = 'B';
	states[3] = '\0';

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
	p1 = newProduction('S','a','A');
	/*A-> bB*/
	p2 = newProduction('A','b','B');

	prods = newProductions(2);
	setProduction(prods,0,p1);
	setProduction(prods,1,p2);

	setDerivations(a,prods);
}

void destroy(){
	freeProduction(p1);
	freeProduction(p2);
	freeProductions(prods);
	/*freeAutomata(a);*/
}
void basicTest(){
	printf("Testing Automata Structures / Basic \n");
	printAutomata(a);
	printf("\n");
}


void automataToGrammarTest(){
	printf("Testing Automata to Grammar Conversion \n");
	GrammarADT g = toGrammar(a);
	printGrammar(g);
	printf("\n");
}
