TLATPE
======

Regular Grammars - DFA converter.


To Run Grammar Test
sudo gcc -g -Wall -ansi GrammarTest.c ../classes/Production.c ../classes/Derivation.c ../classes/Derivations.c ../classes/Productions.c ../classes/Grammar.c ../classes/Automata.c -o test | egrep Grammar.h
(situated inside test folder)

To Run Automata Test
sudo gcc -g -Wall -ansi AutomataTest.c ../classes/Production.c ../classes/Derivation.c ../classes/Derivations.c ../classes/Productions.c ../classes/Grammar.c ../classes/Automata.c -o test

(situated inside test folder)
