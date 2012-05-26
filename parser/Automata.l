%{
#include <ctype.h>;
#include "../include/Automata.h"

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


%}
%x FINALSTATUS NODENAME NODELABEL TRANSITION_FIRST TRANSITION_SECOND TRANSITION_LABEL MIDDLE
start_new_node ^node\[shape=
notfinal "circle\] Node"
rankdir "rankdir = \"LR\";"
start [.]*digraph\{[\r]?\n
end \}
final "doublecircle\] Node"
word [^ \t\r\n]+
letter [^ \t\r\n]
node_label " [label=\""
line_end "\"];"[\r]?\n
label [a-z|A-Z|0-9]
lambda \\\\
enter [\r]?\n
comment "//"[^\n]*[\r]?\n
first_trans_node "Node"
second_trans_node "->Node"
%%
<INITIAL>{start} {BEGIN MIDDLE;++line;}
<MIDDLE>{end} {BEGIN INITIAL;++line;}
<MIDDLE>{start_new_node} {BEGIN FINALSTATUS;}
<MIDDLE>{comment} {++line;}
<MIDDLE>{enter} {++line;}
<MIDDLE>{rankdir} {;}
<MIDDLE>{first_trans_node} {BEGIN TRANSITION_FIRST;}
<FINALSTATUS>{final} { currentNodeIsFinal = 1; BEGIN NODENAME;}
<FINALSTATUS>{notfinal} { currentNodeIsFinal = 0; BEGIN NODENAME;}
<NODENAME>{letter} { currentNodeName = *yytext; BEGIN NODELABEL;}
<NODELABEL>{node_label} {;}
<NODELABEL>{label} {currentNodeLabel=*yytext;}
<NODELABEL>{line_end} {++line;addNode(currentNodeName,currentNodeLabel,currentNodeIsFinal);BEGIN MIDDLE;}
<TRANSITION_FIRST>{letter} {currentTransFirst=*yytext;BEGIN TRANSITION_SECOND;}
<TRANSITION_SECOND>{second_trans_node} {;}
<TRANSITION_SECOND>{letter} {currentTransSec=*yytext;BEGIN TRANSITION_LABEL;}
<TRANSITION_LABEL>{node_label} {++line;}
<TRANSITION_LABEL>{label} {addDer(currentTransFirst,*yytext,currentTransSec);}
<TRANSITION_LABEL>{lambda} {addDer(currentTransFirst,*yytext,currentTransSec);}
<TRANSITION_LABEL>"/" {;}
<TRANSITION_LABEL>{line_end} {currentTransLabels=0;BEGIN MIDDLE;}
%%


int
main()
{
int i;
nodes = calloc(100,1);
ders = calloc(10000,1);
symbols = calloc(256,1);
for(i=0;i<100;i++){
	nodes[i] = calloc(3,1);
}
for(i=0;i<10000;i++){
	ders[i] = calloc(3,1);
}
yylex();
printNodes();
printDers();
printSymbols();
if(!errors){
	autom = newAutomata();
	setInitialstate( autom,nodes[0][0]);
	states = malloc(sizeof(char)*(node+1));
	finalStates = malloc(sizeof(char)*(finalCount));
	
	int j=0;
	for(i=0;i<=node;i++){
		states[i]=nodes[i][0];
		if(nodes[i][2]){
			finalStates[j++]=nodes[i][0];
		}
	}
	setFinalStates( autom,finalStates,finalCount);
	setStates( autom,states,symbolsCount);
	setSymbols( autom,symbols,2);
	
	derivations = newDerivations(der+1);
	for(i=0;i<=der;i++){
		d1 = newDerivation(ders[i][0],ders[i][1],ders[i][2]);
		setDerivation(derivations,i,d1);
	}
	setDerivations( autom,derivations);
		printAutomata( autom);
		/*sudo gcc -g -Wall -ansi lex.yy.c -lfl ../classes/Production.c ../classes/Derivation.c ../classes/Derivations.c ../classes/Productions.c ../classes/Grammar.c ../classes/Automata.c -o test */
}else{
	printf("No se pudo cargar el archivo.");
}
return 0;
}
