TLATPE
======

Regular Grammars - DFA converter.


for compiling (in "root" folder)
	(for grammar to automata parser)	$ make grammar 
	(for automata to gramamr parser)    	$ make automata
	(for both converters)			$make all


for start parsing
	cat parser/files/gr1.gr | ./grammar



//Deprecated


To Run Grammar Test
 sudo gcc -g -Wall  GrammarTest.c ../classes/Production.c ../classes/Derivation.c ../classes/Derivations.c ../classes/Productions.c ../classes/Grammar.c ../classes/Automata.c ../classes/Converter.c ../classes/Utils.c -o test
(situated inside test folder)

To Run Automata Test
sudo gcc -g -Wall -ansi AutomataTest.c ../classes/Production.c ../classes/Derivation.c ../classes/Derivations.c ../classes/Productions.c ../classes/Grammar.c ../classes/Automata.c -o test

(situated inside test folder)
