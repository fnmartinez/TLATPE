%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define INIT_QTY 10
#ifndef LAMDA
#define LAMDA '\\'
#endif
typedef struct prod_t prod_t;
typedef struct prod_list_t prod_list_t;
typedef prod_t * prod;
typedef prod_list_t * prod_list;

struct prod_t{
	prod prev;
	prod next;
	char left;
	char right[2];
};
struct prod_list_t{
	prod head;
	prod tail;
	size_t size;
};

char * grammar_name;
char previous;
int h, k;

char * terminals;
int term_size;
int term_qty;
char * non_terminals;
int nterm_size;
int nterm_qty;
char distinguished;
prod_list productions;

int exists(char * s, char c, size_t l)
{
	int i;
	for(i = 0; i<l && s[i] != c; i++);
	return i < l;
}
prod_list new_prod_list()
{
	prod_list pl = malloc(sizeof(prod_list_t));
	pl->size = 0;
	pl->head = NULL;
	pl->tail = NULL;
	return pl;
}

prod new_prod(char left, char r1, char r2)
{
	prod p = malloc(sizeof(prod_t));
	p->left = left;
	p->right[0] = r1;
	p->right[1] = r2;
	return p;
}

int add_to_list(prod_list pl, prod p)
{
	if(pl == NULL || p == NULL)
	{
		return 0;
	}
	
	if(pl->size == 0)
	{
		pl->head = p;
		pl->tail = p;
		p->next = p->prev = NULL;
	}
	else
	{
		pl->tail->next = p;
		p->prev = pl->tail;
		pl->tail = p;
		p->next = NULL;
	}
	pl->size++;
	return 1;
}

prod pop_prod(prod_list pl)
{
	if(pl == NULL || pl->size == 0)
	{
		return NULL;
	}
	
	prod p = pl->head;
	pl->head = pl->head->next;
	if(pl->head == NULL)
	{
		pl->tail = NULL;
	}
	else
	{
		pl->head->prev = NULL;
	}
	pl->size--;
	return p;
}

void destroy_prod(prod p)
{
	if(p == NULL)
	{
		return;
	}
	free(p);
}

void destroy_prod_list(prod_list pl)
{
	if(pl == NULL)
	{
		return;
	}
	if(pl->size != 0)
	{
		while(pl->size>0)
		{
			destroy_prod(pop_prod(pl));			
		}		
	}
	free(pl);
}

void add_terminal(char * s)
{
	int i = 0;
	int l = strlen(s);
	for(i=0; i<l && isspace(s[i]); i++);
	
	if(isupper(s[i]))
	{
		printf("Error: Invalid terminal. All terminal symbols must be lowercase letters.\n");
		exit(1);
	}
	
	if(!exists(terminals, s[i], term_qty))
	{
		if(term_size == term_qty)
		{
			char * aux;
			aux = realloc(terminals, term_size *= 1.5);
			if(aux == NULL)
			{
				printf("Error: Not enought memory!\n");
				exit(1);
			}
			terminals = aux;
		}
		terminals[term_qty++] = s[i];
	}
	else
	{
		printf("Error: Repeated terminal symbols encountered.\n");
		exit(1);
	}
}

void add_non_terminal(char * s)
{
	int i = 0;
	int l = strlen(s);
	for(i=0; i<l && isspace(s[i]); i++);
	
	if(islower(s[i]))
	{
		printf("Error: Invalid non_terminal. All terminal symbol must be uppercase letters.\n");
		exit(1);
	}
	
	if(!exists(non_terminals, s[i], nterm_qty))
	{
		if(nterm_size == nterm_qty)
		{
			char * aux;
			aux = realloc(non_terminals, term_size *= 1.5);
			if(aux == NULL)
			{
				printf("Error: Not enought memory!\n");
				exit(1);
			}
			non_terminals = aux;
		}
		non_terminals[nterm_qty++] = s[i];
	}
	else
	{
		printf("Error: Repeated non terminal symbol encountered.\n");
		exit(1);
	}
}

void add_production2(char le, char * s)
{
	int i;
	char r1, r2;
	int l = strlen(s);
	for(i = 0; i<l && isspace(s[i]); i++);
	r1 = s[i];
	if(!exists(terminals, r1, term_qty) && !exists(non_terminals, r1, nterm_qty) && r1 != LAMDA)
	{
		printf("%c -> %c", le, r1);
		printf("1Error: Invalid right-side production symbol\n");
		exit(1);
	}
	for(i = i+1; i<l && isspace(s[i]); i++);
	if(i < l && !ispunct(s[i]) && !isspace(s[i]))
	{
		r2 = s[i];
		if(((!exists(terminals, r2, term_qty) && !exists(non_terminals, r2, nterm_qty)) && (r1 != LAMDA)) ||
			((exists(terminals, r2, term_qty) || exists(non_terminals, r2, nterm_qty)) && (r1 == LAMDA)))
		{
			printf("Error: Invalid right-side production symbol\n");
			exit(1);
		}	
	}
	else
	{
		r2 = LAMDA;
	}
	add_to_list(productions, new_prod(le, r1, r2));
}

void add_production(char * s)
{
	int i;
	int l = strlen(s);
	for(i = 0; i<l && isspace(s[i]); i++);
	char le = s[i];
	if(islower(le) || !exists(non_terminals, s[i], nterm_qty))
	{
		printf("Error: Invalid left-side production symbol\n");
		exit(1);
	}
	for(i = i+1; i<l && isspace(s[i]); i++);
	for(i = i+1; i<l && isspace(s[i]); i++);
	add_production2(le, s+i+1);
	
}

void init()
{
	term_size = INIT_QTY;
	term_qty = 0;
	terminals = malloc(term_size*sizeof(char));
	nterm_size = INIT_QTY;
	nterm_qty = 0;
	non_terminals = malloc(nterm_size*sizeof(char));
	productions = new_prod_list();
}

void printall()
{
	int i;
	printf("G = <{");
	for(i=0; i<nterm_qty; i++)
	{
		printf("%c%c ", non_terminals[i], (i== nterm_qty-1?' ':','));
	}
	printf("},{");
	for(i=0; i<term_qty;i++)
	{
		printf("%c%c ", terminals[i], (i== term_qty-1?' ':','));
	}
	printf("}, ");
	printf("%c, ", distinguished);
	
	prod p;
	for(p=productions->head; p != NULL; p = p->next)
	{
		printf("%c -> %c%c, ", p->left, p->right[0], p->right[1]);
	}
	printf("}>\n");
}

%}
%x TO_VN 
%x VN 
%x TO_VT 
%x VT 
%x TO_D 
%x DISTINGUISHED
%x TO_PR 
%x PRODUCTION 
%x PROD_TRNSTN 
%x TO_FIN 
%x FIN 
%x ERROR
space [ \t\n(\r\n)]
non_terminal [A-Z]
terminal [a-z]
number [0-9]
grammar_name [gG]{number}
lamda \\
valid_left_side {non_terminal}
valid_right_side ({non_terminal}{terminal})|({terminal}{non_terminal})|{lamda}|{terminal}|{non_terminal}
%%
<INITIAL>{space}*{grammar_name}{space}*={space}*\(	{for(h=0; h<yyleng && isspace(yytext[h]); h++);
							 for(k=yyleng; k>0 && isspace(yytext[k]); k--);
								BEGIN(TO_VN);}
<TO_VN>{space}*\{				;BEGIN(VN);
<VN>{space}*{non_terminal}{space}*[,\}]			{
								add_non_terminal(yytext);
								if(yytext[yyleng-1]==',')
									BEGIN(VN);
								else if(yytext[yyleng-1]=='}')
									BEGIN(TO_VT);
								else
									BEGIN(ERROR);}
<TO_VT>{space}*,{space}*\{			;BEGIN(VT);
<VT>{space}*{terminal}{space}*[,\}]			{
								add_terminal(yytext);
								if(yytext[yyleng-1]==',')
									BEGIN(VT);
								else if(yytext[yyleng-1]=='}')
									BEGIN(TO_D);
								else
									BEGIN(ERROR);}
<TO_D>{space}*,					; BEGIN(DISTINGUISHED);
<DISTINGUISHED>{space}*{non_terminal}		{for(h=0; h<yyleng && isspace(yytext[h]); h++);
								distinguished = yytext[h];
								yytext[0]=yytext[h];
								yytext[1]='\0';
								BEGIN(TO_PR);}
<TO_PR>{space}*,{space}*\{			;BEGIN(PRODUCTION);
<PRODUCTION>{space}*({valid_left_side}){space}*\-{space}*\>{space}*({valid_right_side}){space}*[,\|\}]	{
													add_production(yytext);
													if(yytext[yyleng-1]==',')
														BEGIN(PRODUCTION);
													else if(yytext[yyleng-1]=='}')
														BEGIN(TO_FIN);
													else if(yytext[yyleng-1]=='|')
													{
														for(h=0; h<yyleng && isspace(yytext[h]); h++);
														previous=yytext[h];
														BEGIN(PROD_TRNSTN);
													}
													else
														BEGIN(ERROR);}
<PROD_TRNSTN>{space}*({valid_right_side}){space}*[,\|\}]	{
								add_production2(previous, yytext);
								if(yytext[yyleng-1]==',')
									BEGIN(PRODUCTION);
								else if(yytext[yyleng-1]=='}')
									BEGIN(TO_FIN);
								else if(yytext[yyleng-1]=='|')
								{
									BEGIN(PROD_TRNSTN);
								}
								else
									BEGIN(ERROR);
								}
<TO_FIN>{space}*\)	;BEGIN(FIN);
<FIN>[.{space}]*	;
<ERROR>.{space}*	;
%%

int main()
{
	init();
	yylex();
	printall();
	return 0;
}

