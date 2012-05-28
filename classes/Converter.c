/*
 * Converter.c
 *
 */
#include "../include/Converter.h"


void formalize(GrammarADT grammar){
	/*unitary productions must be removed*/
	removeUnitaryProductions(grammar);
	printf("\n AFTER UNITARY1 ----------------------- ");
	printGrammar(grammar);


	/*unproductive productiones must be removed*/
	removeUnproductiveProductions(grammar);
	printf("\n AFTER UNPRODUCTIVE1 ----------------------- ");
	printGrammar(grammar);

	/*unreachable productions must be deleted*/
	removeUnreachableProductions(grammar);
	printf("\n AFTER UNREACHABLE1 ----------------------- ");
	printGrammar(grammar);

	/*all productions must be in the form A-Ba or A-> /*/
	removeOnlyRightTerminals(grammar);
	printf("\n AFTER OnlyRightTerminals ----------------------- ");
	printGrammar(grammar);

	/*the grammar must be right*/
	convertToRight(grammar);
	printf("\n AFTER convertToRight ----------------------- ");
	printGrammar(grammar);

	/*AGAIN ; unitary productions must be removed*/
	removeUnitaryProductions(grammar);
	printf("\n AFTER UNITARY2 ----------------------- ");
	printGrammar(grammar);

	/*AGAIN : unproductive productiones must be removed*/
	removeUnproductiveProductions(grammar);
	printf("\n AFTER UNPRODUCTIVE2 ----------------------- ");
	printGrammar(grammar);

	/*AGAIN : unreachable productions must be deleted*/
	removeUnreachableProductions(grammar);
	printf("\n AFTER UNREACHABLE2 ----------------------- ");
	printGrammar(grammar);

}

AutomataADT toAutomata(GrammarADT grammar){
	AutomataADT a = newAutomata();

	/*the automata´s symbols are equal to the grammar´s terminal symbols*/
	setSymbols(a, getTerminals(grammar), getQuantTerminals(grammar));

	/*the automata´s states are equal to the grammar´s non terminal symbols*/
	setStates(a, getNonTerminals(grammar), getQuantNonTerminals(grammar));

	/*the automata´s inital state is equal to the grammar distinguished symbol*/
	setInitialstate(a, getDistinguished(grammar));

	/*formalization*/
	formalize(grammar);

	/*to automata conversion*/
	ProductionsADT productions = getProductions(grammar);
	int n = getQuant(productions);
	int finalstatesquant = 0;
	char * finalstates = malloc(sizeof(char));
	int i,derivationquant=0;
	ProductionADT p = NULL;
	for(i=0; i<n; i++){
		p = getProduction(productions,i);
		char first = getProductionComponent(p,0);
		char sec = getProductionComponent(p,1);
		char third = getProductionComponent(p,2);
		if ( sec == LAMDA && third== LAMDA ){
			addChar(&finalstates,&finalstatesquant,first);
		}
	}
	setFinalStates(a, finalstates, finalstatesquant);
	DerivationsADT derivations = newDerivations(n-finalstatesquant);
	for(i=0; i<n; i++){
		p = getProduction(productions,i);
		char sec = getProductionComponent(p,1);
		char third = getProductionComponent(p,2);
		if ( sec == LAMDA && third == LAMDA ){
			continue;
		}
		setDerivation(derivations,derivationquant++, (DerivationADT) toDerivation( p ) );
	}
	setDerivations(a,derivations);
	return a;
}

GrammarADT toGrammar(AutomataADT automata){
	GrammarADT g = newGrammar();
	setNonTerminals(g,getStates(automata), getQuantStates(automata));
	setTerminals(g, getSymbols(automata), getQuantSymbols(automata));
	setDistinguished(g,getInitialstate(automata));
	DerivationsADT derivations = getDerivations(automata);
	int n = getDerivationsQuant(derivations);
	int quantfinals = getQuantFinalStates(automata);
	int i;
	ProductionsADT prods = newProductions(n+quantfinals);
	for (i=0; i<n; i++){
		setProduction(prods,i,toProduction(getDerivation(derivations,i)));
	}
	/*if P is in F , the production P->/ should be included*/
	for(; i-n<quantfinals; i++){
		setProduction(prods,i,newProduction(getFinalStates(automata)[i-n],LAMDA,LAMDA));
	}
	setProductions(g,prods);
	return g;
}

ProductionADT toProduction(DerivationADT d){
	return newProduction( getDerivationComponent(d,0),getDerivationComponent(d,1),
			getDerivationComponent(d,2) );
}

DerivationADT toDerivation(ProductionADT p){
	return newDerivation( getProductionComponent(p,0),getProductionComponent(p,1),
			getProductionComponent(p,2) );
}
