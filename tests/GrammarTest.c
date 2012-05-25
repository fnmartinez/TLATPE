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
void removeProductionsTest();
void addProductionsTest();
void removeUnreachableProductionsTest();

ProductionsADT prods;
GrammarADT g1;
char * nonterminals;
char * term;
ProductionADT p1;
ProductionADT p2;
ProductionADT p3;
ProductionADT p4;
ProductionADT p5;
ProductionADT p6;
ProductionADT p7;
ProductionADT p8;

int main(void)
{
	init();
	basicTest();
	//grammarToAutomata();
	removeProductionsTest();
	addProductionsTest();
	removeUnreachableProductionsTest();

	destroy();
	return 0;
}

void init(){
	g1 = newGrammar();
	setDistinguished(g1, 'S');
	nonterminals = malloc(sizeof(char)*5);
	nonterminals[0] = 'S';
	nonterminals[1] = 'A';
	nonterminals[2] = 'B';
	nonterminals[3] = 'C';
	nonterminals[4] = 'D';
	setNonTerminals(g1,nonterminals,5);
	term = malloc(sizeof(char)*2);
	term[0] = 'a';
	term[1] = 'b';
	setTerminals(g1,term,2);

	/*S-> aA*/
	p1 = newProduction('S','a','A');
	/*A-> b*/
	p2 = newProduction('A','/','b');
	/*B-> aB*/
	p7 = newProduction('B','b','B');
	/*A-> bA*/
	p3 = newProduction('A','b','A');
	/*A-> aB*/
	p8 = newProduction('A','a','a');
	/*B-> ab*/
	p4 = newProduction('B','c','b');
	/*A-> bB*/
	p5 = newProduction('A','b','B');
	/*A-> aB*/
	p6 = newProduction('A','b','B');


	prods = newProductions(8);
	setProduction(prods,0,p1);
	setProduction(prods,1,p2);
	setProduction(prods,2,p7);
	setProduction(prods,3,p3);
	setProduction(prods,4,p8);
	setProduction(prods,5,p4);
	setProduction(prods,6,p5);
	setProduction(prods,7,p6);


	setProductions(g1,prods);
}

void destroy(){
	free(nonterminals);
	free(term);
	freeProduction(p1);
	freeProduction(p2);
	freeProductions(prods);
	freeGrammar(g1);
}

void basicTest(){
	printf("Testing Grammar Structures / Basic \n");
	printGrammar(g1);
	printf("productions quant: %d\n", getQuant(getProductions(g1)));
}

void grammarToAutomata(){
	printf("\nTesting Grammar to Automata Conversion  \n");
	AutomataADT a = toAutomata(g1);
	printAutomata(a);
	printf("productions quant: %d\n", getQuant(getProductions(g1)));
}

void removeProductionsTest(){
	printf("\nTesting Remove Productions Method \n");
	printf("to remove: all starting with 'S' \n");
	removeProduction(getProductions(g1),'S');
	printGrammar(g1);
	printf("productions quant: %d\n", getQuant(getProductions(g1)));
}

void addProductionsTest(){
	printf("\nTesting Add Productions Method \n");
	addProduction(getProductions(g1), newProduction('C','C','C'));
	addProduction(getProductions(g1), newProduction('S','B','/'));
	addProduction(getProductions(g1), newProduction('B','B','B'));
	printGrammar(g1);
	printf("productions quant: %d\n", getQuant(getProductions(g1)));
}

void removeUnreachableProductionsTest(){
	printf("\nTesting Remove Unreachable Productions Method \n");
	removeUnreachableProductions( g1 );
	printGrammar(g1);
	printf("productions quant: %d\n", getQuant(getProductions(g1)));

}

