/*
 * Automata.c
 *
 *  Created on: May 14, 2012
 *      Author: joseignaciosantiagogalindo
 */

#include "../include/Automata.h"

/*Constructor-destructor*/
AutomataADT newAutomata(void){
	AutomataADT a = (AutomataADT)malloc(sizeof(struct Automata));
	return a;
}
void freeAutomata(AutomataADT  automata){
	free(automata->finalstates);
	free(automata->states);
	free(automata->symbols);
	free(automata);
}

/*Getters*/
char * getStates(AutomataADT automata){
	return automata->states;
}

char * getSymbols(AutomataADT automata){
	return automata->symbols;
}
char * getFinalStates(AutomataADT automata){
	return automata->finalstates;
}
char getInitialstate(AutomataADT automata){
	return automata->initialstate;
}
/*DerivationsADT getDerivations(AutomataADT automata){*/
DerivationsADT getDerivations(AutomataADT automata){
	return automata->derivations;
}
int getQuantStates(AutomataADT automata){
	return automata->quantstates;
}
int getQuantSymbols(AutomataADT automata){
	return automata->quantsymbols;
}
int getQuantFinalStates(AutomataADT automata){
	return automata->quantfinalstates;
}

/*Setters*/
void setStates(AutomataADT automata, char * states, int quant){
	automata->states = malloc(sizeof(char)*quant);
	memcpy( automata->states, states, quant);
	automata->quantstates = quant;
}
void setSymbols(AutomataADT automata, char * symbols, int quant){
	automata->symbols = malloc(sizeof(char)*quant);
	memcpy( automata->symbols, symbols, quant);
	automata->quantsymbols = quant;
}
void setFinalStates(AutomataADT automata, char * finalstates, int quant){
	automata->finalstates = malloc(sizeof(char)*quant);
	memcpy( automata->finalstates, finalstates, quant);
	automata->quantfinalstates = quant;
}
void setInitialstate(AutomataADT automata, char initialState){
	automata->initialstate = initialState;
}
void setDerivations(AutomataADT automata, DerivationsADT  derivations){
	automata->derivations = derivations;
}


/*Utility*/
void printAutomata(AutomataADT automata){
	printf("Automata\n");
		printf("InitialState: %c \n",getInitialstate(automata));
		int i ;
		printf("States: {");
		for(i=0;i < getQuantStates(automata);i++){
			printf(" %c ",getStates(automata)[i]);
		}
		printf("}\n");
		printf("Symbols: {");
		for(i=0;i < getQuantSymbols(automata);i++){
			printf(" %c ",getSymbols(automata)[i]);
		}
		printf("}\n");
		printf("Final States: {");
		for(i=0;i < getQuantFinalStates(automata);i++){
			printf(" %c ",getFinalStates(automata)[i]);
		}
		printf("}\n");
		printDerivations(getDerivations(automata));
		return;
}

int isFinal(AutomataADT automata, char c){
	char* finals = getFinalStates(automata);
	int i,size=getQuantFinalStates(automata);
	for(i=0;i<size;i++){
		if(finals[i]==c){
			return 1;
		}
	}
	return 0;
}

void toDot(AutomataADT automata){
	FILE *p = NULL;
	  char *file = "./out.dot";
	  char buffer[80] = "digraph{\r\n";
	  size_t len = 0;
	  p = fopen(file, "w");
	  if (p== NULL) {
	  printf("Error in opening a file..%s", file);
	  }
	  len = strlen(buffer);
	  fwrite(buffer, len, 1, p);
		int i, statesCount = getQuantStates(automata);
		char* states = getStates(automata);
		char c = getInitialstate(automata);
		
			if(isFinal(automata,states[i])){
				strcpy(buffer,"node[shape=doublecircle] Node4 [label=\"4\"];\r\n");
				buffer[29]=c;
				buffer[39]=c;
			}else{
				strcpy(buffer,"node[shape=circle] Node3 [label=\"3\"];\r\n");
				buffer[23]=c;
				buffer[33]=c;
			}
		fwrite(buffer, strlen(buffer), 1, p);
		
		for(i=0;i<statesCount;i++){
			if(states[i]!=c){
				if(isFinal(automata,states[i])){
					strcpy(buffer,"node[shape=doublecircle] Node4 [label=\"4\"];\r\n");
					buffer[29]=states[i];
					buffer[39]=states[i];
				}else{
					strcpy(buffer,"node[shape=circle] Node3 [label=\"3\"];\r\n");
					buffer[23]=states[i];
					buffer[33]=states[i];
				}
			fwrite(buffer, strlen(buffer), 1, p);
			}
		}
		DerivationsADT derivations = getDerivations(automata);
		int n = getDerivationsQuant(derivations);
		for (i=0; i<n; i++){
			DerivationADT d = getDerivation(derivations,i);
			if(getDerivationComponent(d,1)=='\\'){
				strcpy(buffer,"Node0->Node1 [label=\"\\\\\"];\r\n");
				buffer[4]=getDerivationComponent(d,0);
				buffer[11]=getDerivationComponent(d,2);
			}else{
				strcpy(buffer,"Node0->Node1 [label=\"a\"];\r\n");
				buffer[4]=getDerivationComponent(d,0);
				buffer[11]=getDerivationComponent(d,2);
				buffer[21]=getDerivationComponent(d,1);
			}
			fwrite(buffer, strlen(buffer), 1, p);
		}
		strcpy(buffer,"}\r\n");
		fwrite(buffer, strlen(buffer), 1, p);
	  fclose(p);
	  printf("\nWritten Successfuly in the file.\n");
	 
}


