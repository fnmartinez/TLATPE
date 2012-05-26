/*
 * Converter.c
 *
 */
#include "../include/Converter.h"


void formalize(GrammarADT grammar){
	/*unitary productions must be removed*/
	removeUnitaryProductions(grammar);

	/*unproductive productiones must be removed*/
	removeUnproductiveProductions(grammar);

	/*unreachable productions must be deleted*/
	removeUnreachableProductions(grammar);

	/*all productions must be in the form A-Ba or A-> /*/
	removeOnlyRightTerminals(grammar);

	/*the grammar must be right*/
	convertToRight(grammar);

	/*AGAIN : unproductive productiones must be removed*/
	removeUnproductiveProductions(grammar);

	/*AGAIN : unreachable productions must be deleted*/
	removeUnreachableProductions(grammar);

}

AutomataADT toAutomata(GrammarADT grammar){
	AutomataADT a = newAutomata();

	/*the automata´s symbols are equal to the grammar´s terminal symbols*/
	setSymbols(a, getTerminals(grammar), getQuantTerminals(grammar));

	/*the automata´s states are equal to the grammar´s non terminal symbols*/
	setStates(a, getNonTerminals(grammar), getQuantNonTerminals(grammar));

	/*the automata´s inital state is equal to the grammar distinguished symbol*/
	setInitialstate(a, getDistinguished(grammar));



	/*to automata conversion*/
	ProductionsADT productions = getProductions(grammar);
	int n = getQuant(productions);
	int finalstatesquant = 0;
	char * finalstates = malloc(sizeof(char));
	int i,derivationquant=0;
	char * aux;
	for(i=0; i<n; i++){
		if ( getProductionComponent(getProduction(productions,i),1) == '/' &&
				 getProductionComponent(getProduction(productions,i),2) == '/' ){
			if ( (aux = realloc(finalstates,sizeof(char)*(finalstatesquant+1)) ) == NULL ){
				  fprintf(stderr, "Not enough space for finalstates\n");
			}
			finalstates = aux;
			finalstates[finalstatesquant++] = getProductionComponent(getProduction(productions,i),0);
		}
	}
	setFinalStates(a, finalstates, finalstatesquant);
	DerivationsADT derivations = newDerivations(n-finalstatesquant);
	for(i=0; i<n; i++){
		if ( getProductionComponent(getProduction(productions,i),1) != '/' ||
						 getProductionComponent(getProduction(productions,i),2) != '/' ){
			setDerivation(derivations,derivationquant++, (DerivationADT) toDerivation( getProduction(productions,i) ) );
		}
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
		setProduction(prods,i,newProduction(getFinalStates(automata)[i-n],'/','/'));
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
