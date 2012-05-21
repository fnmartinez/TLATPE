%{
#include <ctype.h>;
#include "../include/Productions.h"

char nodes[100][3];

char rankDir[2];

int node = -1;
char currentNodeIsFinal = 0;
char currentNodeLabel[20];
char currentNodeName;

char currentTransLabels=-1;
char currentTransFirst;
char currentTransSec;
char currentTransLabel[10];

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

void addNode(char name, char* label, char isFinal){
	if(containsNode(name)==0){
		nodes[++node][0]=name;
		nodes[node][1]=*label;
		nodes[node][2]=isFinal;
	}
}

void addLabel(char f, char l, char s){
	printf("%c-%c->%c\n",f,l,s);
}

void printNodes(){
	int i,exists=0;
	printf("\nNodes parsed:\n");
	for(i=0;i<100 && nodes[i][0]!='\0';i++){
		printf("%c: %s, label: %c\n",nodes[i][0],(nodes[i][2]==0)?"not final":"final",nodes[i][1]);
	}
}

%}
%x FINALSTATUS NODENAME NODELABEL TRANSITION_FIRST TRANSITION_SECOND TRANSITION_LABEL MIDDLE
start_new_node ^node\[shape=
notfinal "circle\] Node"
rankdir "rankdir = \"LR\";"
start [.]*digraph\{\n
end \}
final "doublecircle\] Node"
word [^ \t\n]+
letter [^ \t\n]
node_label " [label=\""
line_end "\"];\n"
label [a-z|A-Z|0-9]+
lambda \\\\
enter \n
comment "//"[^\n]*\n
first_trans_node "Node"
second_trans_node "->Node"
%%
<INITIAL>{start} {BEGIN MIDDLE;}
<MIDDLE>{end} {BEGIN INITIAL;}
<MIDDLE>{start_new_node} {BEGIN FINALSTATUS;}
<MIDDLE>{comment} {;}
<MIDDLE>{enter} {;}
<MIDDLE>{rankdir} {;}
<MIDDLE>{first_trans_node} {BEGIN TRANSITION_FIRST;}
<FINALSTATUS>{final} { currentNodeIsFinal = 1; BEGIN NODENAME;}
<FINALSTATUS>{notfinal} { currentNodeIsFinal = 0; BEGIN NODENAME;}
<NODENAME>{letter} { currentNodeName = *yytext; BEGIN NODELABEL;}
<NODELABEL>{node_label} {;}
<NODELABEL>{label} {memcpy(currentNodeLabel,yytext,yyleng); currentNodeLabel[yyleng]='\0';}
<NODELABEL>{line_end} {addNode(currentNodeName,currentNodeLabel,currentNodeIsFinal);BEGIN MIDDLE;}
<TRANSITION_FIRST>{letter} {currentTransFirst=*yytext;BEGIN TRANSITION_SECOND;}
<TRANSITION_SECOND>{second_trans_node} {;}
<TRANSITION_SECOND>{letter} {currentTransSec=*yytext;BEGIN TRANSITION_LABEL;}
<TRANSITION_LABEL>{node_label} {;}
<TRANSITION_LABEL>{label} {addLabel(currentTransFirst,*yytext,currentTransSec);}
<TRANSITION_LABEL>{lambda} {addLabel(currentTransFirst,*yytext,currentTransSec);}
<TRANSITION_LABEL>"/" {;}
<TRANSITION_LABEL>{line_end} {currentTransLabels=0;BEGIN MIDDLE;}
%%


int
main()
{
int i;
for(i=0;i<100;i++){
	nodes[i][0]='\0';
	nodes[i][0]='\0';
	nodes[i][0]='\0';
}
yylex();
printNodes();
return 0;
}
