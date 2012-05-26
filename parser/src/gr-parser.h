#ifndef __GR_PARSER__
#define __GR_PARSER__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../include/Converter.h"
#include "../../include/Grammar.h"
#include "../../include/Automata.h"

#ifndef LAMDA
#define LAMDA '\\'
#endif
#define INIT_QTY 10
#define validate_name() valid_name=true
#define validate_grammar() valid_grammar=true
#define validate_non_terminals() valid_nt=true
#define validate_terminals() valid_t=true
#define validate_productions() valid_p=true
#define validate_distinguished() valid_d=true

typedef struct prod_t prod_t;
typedef struct prod_list_t prod_list_t;
typedef prod_t * prod;
typedef prod_list_t * prod_list;

enum{
	false,
	true
} bool;

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

void init();
void process();
void printall();
void add_production(char * s);
void add_production2(char le, char * s);
void add_non_terminal(char * s);
void add_terminal(char * s);
void destroy_prod_list(prod_list pl);
void destroy_prod(prod p);
prod pop_prod(prod_list pl);
int add_to_list(prod_list pl, prod p);
prod new_prod(char left, char r1, char r2);
prod_list new_prod_list();
int exists(char * s, char c, size_t l);
#endif
