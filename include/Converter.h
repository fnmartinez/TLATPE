/*
 * Converter.h
 *
 *  Created on: 26/05/2012
 *      Author: neon
 */

#ifndef CONVERTER_H_
#define CONVERTER_H_

#include "Automata.h"
#include "Grammar.h"

void formalize(GrammarADT grammar);
AutomataADT toAutomata(GrammarADT grammar);
GrammarADT toGrammar(AutomataADT automata);

ProductionADT toProduction(DerivationADT d);
DerivationADT toDerivation(ProductionADT p);


#endif /* CONVERTER_H_ */
