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


void basicTest();

int main(void)
{
	basicTest();
	return 0;
}


void basicTest(){

	printf("Testing Grammar Structures / Basic \n");
	GrammarADT g1 = newGrammar();
	setDistinguished(g1, 'S');
	char * term = malloc(sizeof(char)*3);
	term[0] = 'S';
	term[1] = 'A';
	term[2] = 'B';
	setTerminals(g1,term);
	char * nonterm = malloc(sizeof(char)*2);
	nonterm[0] = 'a';
	nonterm[1] = 'b';
	setNonTerminals(g1,nonterm);

	/*S->aA*/
	ProductionADT p1 = newProduction('S','a','A');
	/*A-> b*/
	ProductionADT p2 = newProduction('A',' ','b');

	ProductionsADT prods = newProductions(2);
	setProduction(prods,0,p1);
	setProduction(prods,1,p2);

	setProductions(g1,prods);

	printGrammar(g1);

	freeProduction(p1);
	freeProduction(p2);
	freeProductions(prods);
	/*freeGrammar(g1);*/

}
