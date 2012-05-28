#include "Automata.h"
char* states;
char* finalStates;
char* symbols;
int symbolsCount=0;

AutomataADT  autom;
DerivationADT d1;
DerivationsADT derivations;

char ** nodes;
char ** ders;

char rankDir[2];

int der = -1;
int node = -1;
int finalCount=0;
char currentNodeIsFinal = 0;
char currentNodeLabel;
char currentNodeName;

char currentTransLabels=-1;
char currentTransFirst;
char currentTransSec;
char currentTransLabel[10];

int errors=0;
int line=0;
int containsNode(char name){
	int i,exists=0;
	for(i=0;i<100 && nodes[i][0]!='\0';i++){
		if(nodes[i][0]==name){
			exists=1;
			break;
		}
	}
	return exists;
}

int containsSymbol(char name){
	int i,exists=0;
	for(i=0;i<255 && symbols[i]!='\0';i++){
		if(symbols[i]==name){
			exists=1;
			break;
		}
	}
	return exists;
}

void addSymbol(char name){
	if(!containsSymbol(name)){
		symbols[symbolsCount++]=name;
	}
}

void addNode(char name, char label, char isFinal){
	if(!containsNode(name)){
		nodes[++node][0]=name;
		nodes[node][1]=label;
		nodes[node][2]=isFinal;
		if(isFinal){
			finalCount++;
		}
	}else{
		errors=1;
		printf("El nodo en la línea %d ya existe\n",line);
	}
}

void addDer(char f, char l, char s){
	if(containsNode(f)){
		if(containsNode(s)){
			der++;
			ders[der][0]=f;
			addSymbol(l);
			ders[der][1]=l;
			ders[der][2]=s;
		}else{
			errors=1;
			printf("Error en linea %d, no existe el nodo %c\n",line,s);
		}
	}else{
		errors=1;
		printf("Error en linea %d, no existe el nodo %c\n",line,f);
	}

}

void printNodes(){
	int i;
	printf("\nNodes parsed:\n");
	for(i=0;i<=node && nodes[i][0]!='\0';i++){
		printf("%c: %s, label: %c\n",nodes[i][0],(nodes[i][2]==0)?"not final":"final",nodes[i][1]);
	}
}

void printDers(){
	int i;
	printf("\nDerivations parsed:\n");
	for(i=0;i<=der && ders[i][0]!='\0';i++){
		printf("%c -> %c -> %c\n",ders[i][0],ders[i][1],ders[i][2]);
	}
}
void printSymbols(){
	int i;
	printf("\nSymbols parsed:\n");
	for(i=0;i<symbolsCount;i++){
		printf("%c\n",symbols[i]);
	}
}
