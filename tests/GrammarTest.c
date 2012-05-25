/*
 * GrammarTest.c
 *
 *  Created on: May 14, 2012
 *      Author: joseignaciosantiagogalindo
 */
# include <stdio.h>
# include <stdlib.h>
# include "../include/Grammar.h"
# include "../include/Productions.h"
# include "../include/Production.h"


void init();
void destroy();
void basicTest();
void grammarToAutomata();
ProductionsADT prods;

GrammarADT g1;
char * term;
char * nonterm;
ProductionADT p1;
ProductionADT p2;

int main(void)
{
	init();
	basicTest();
	grammarToAutomata();
	destroy();
	return 0;
}

void init(){
	g1 = newGrammar();
	setDistinguished(g1, 'S');
	term = malloc(sizeof(char)*3);
	term[0] = 'S';
	term[1] = 'A';
	term[2] = 'B';
	setTerminals(g1,term,3);
	nonterm = malloc(sizeof(char)*2);
	nonterm[0] = 'a';
	nonterm[1] = 'b';
	setNonTerminals(g1,nonterm,2);

	/*S->aA*/
	p1 = newProduction('S','a','A');
	/*A-> b*/
	p2 = newProduction('A','/','b');

	prods = newProductions(2);
	setProduction(prods,0,p1);
	setProduction(prods,1,p2);

	setProductions(g1,prods);
}

void destroy(){
	free(term);
	free(nonterm);
	freeProduction(p1);
	freeProduction(p2);
	freeProductions(prods);
	/*freeGrammar(g1);*/
}

void basicTest(){
	printf("Testing Grammar Structures / Basic \n");
	printGrammar(g1);
}

void grammarToAutomata(){
	printf("\nTesting Grammar to Automata Conversion  \n");
	AutomataADT a = toAutomata(g1);
	printAutomata(a);
}

