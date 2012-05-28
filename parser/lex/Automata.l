%{
#include "parser/src/Automata.h"

extern char* states;
extern char* finalStates;
extern char* symbols;
extern int symbolsCount;

extern AutomataADT  autom;
extern DerivationADT d1;
extern DerivationsADT derivations;

extern char ** nodes;
extern char ** ders;

extern char rankDir[2];

extern int der;
extern int node;
extern int finalCount;
extern char currentNodeIsFinal;
extern char currentNodeLabel;
extern char currentNodeName;

extern char currentTransLabels;
extern char currentTransFirst;
extern char currentTransSec;
extern char currentTransLabel[10];

extern int errors;
extern int line;
%}
%x FINALSTATUS NODENAME NODELABEL TRANSITION_FIRST TRANSITION_SECOND TRANSITION_LABEL TRANSITION_LABEL_OK MIDDLE ERROR
start_new_node ^node\[shape=
notfinal "circle\] Node"
rankdir "rankdir = \"LR\";"
start [.]*digraph\{[\r]?\n
end \}
final "doublecircle\] Node"
word [^ \t\r\n]+
letter [^ \t\r\n]
node_label " [label=\""
not_node_label ^[node_label]
anything .*[\r]*[\n]?
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
<TRANSITION_LABEL>{node_label} {++line;BEGIN TRANSITION_LABEL_OK;}
<TRANSITION_LABEL>^[{node_label}] {++line;BEGIN ERROR;errors=1;}
<TRANSITION_LABEL_OK>{label} {addDer(currentTransFirst,*yytext,currentTransSec);}
<TRANSITION_LABEL_OK>{lambda} {addDer(currentTransFirst,*yytext,currentTransSec);}
<TRANSITION_LABEL_OK>"/" {;}
<TRANSITION_LABEL_OK>{line_end} {currentTransLabels=0;BEGIN MIDDLE;}
<ERROR>{anything} {;}
%%

int
main(int argc, char **argv)
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
	/*printNodes();*/
	/*printDers();*/
	/*printSymbols();*/
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
		setStates( autom,states,node+1);
		setSymbols( autom,symbols,symbolsCount);

		derivations = newDerivations(der+1);
		for(i=0;i<=der;i++){
			d1 = newDerivation(ders[i][0],ders[i][1],ders[i][2]);
			setDerivation(derivations,i,d1);
		}
		setDerivations( autom,derivations);
		GrammarADT gr = toGrammar(autom);
		toFile(gr);
		/*printAutomata( autom);
		toDot(autom);
		drawDot(".","out.dot","h.jpg");*/
	}else{
		printf("No se pudo cargar el archivo.");
	}
	return 0;
}
