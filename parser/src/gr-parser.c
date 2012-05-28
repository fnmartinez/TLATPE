#include "gr-parser.h"
char * grammar_name;

static char * terminals;
static int term_size;
static int term_qty;
static char * non_terminals;
int nterm_size;
int nterm_qty;
static char distinguished;
static prod_list productions;
int valid_name, valid_grammar, valid_nt, valid_t, valid_d, valid_p;

int exists(char * s, char c, size_t l) {
	int i;
	for (i = 0; i < l && s[i] != c; i++)
		;
	return i < l;
}

prod_list new_prod_list() {
	prod_list pl = malloc(sizeof(prod_list_t));
	pl->size = 0;
	pl->head = NULL;
	pl->tail = NULL;
	return pl;
}

prod new_prod(char left, char r1, char r2) {
	prod p = malloc(sizeof(prod_t));
	p->left = left;
	p->right[0] = r1;
	p->right[1] = r2;
	return p;
}

int add_to_list(prod_list pl, prod p) {
	if (pl == NULL || p == NULL) {
		return 0;
	}

	if (pl->size == 0) {
		pl->head = p;
		pl->tail = p;
		p->next = p->prev = NULL;
	} else {
		pl->tail->next = p;
		p->prev = pl->tail;
		pl->tail = p;
		p->next = NULL;
	}
	pl->size++;
	return 1;
}

prod pop_prod(prod_list pl) {
	if (pl == NULL || pl->size == 0) {
		return NULL;
	}

	prod p = pl->head;
	pl->head = pl->head->next;
	if (pl->head == NULL) {
		pl->tail = NULL;
	} else {
		pl->head->prev = NULL;
	}
	pl->size--;
	return p;
}

void destroy_prod(prod p) {
	if (p == NULL) {
		return;
	}
	free(p);
}

void destroy_prod_list(prod_list pl) {
	if (pl == NULL) {
		return;
	}
	if (pl->size != 0) {
		while (pl->size > 0) {
			destroy_prod(pop_prod(pl));
		}
	}
	free(pl);
}

void add_terminal(char * s) {
	int i = 0;
	int l = strlen(s);
	for (i = 0; i < l && isspace(s[i]); i++)
		;

	if (isupper(s[i])) {
		printf(
				"Error: Invalid terminal. All terminal symbols must be lowercase letters.\n");
		exit(1);
	}

	if (!exists(terminals, s[i], term_qty)) {
		if (term_size == term_qty) {
			char * aux;
			aux = realloc(terminals, term_size *= 1.5);
			if (aux == NULL) {
				printf("Error: Not enought memory!\n");
				exit(1);
			}
			terminals = aux;
		}
		terminals[term_qty++] = s[i];
	} else {
		printf("Error: Repeated terminal symbols encountered.\n");
		exit(1);
	}
}

void add_non_terminal(char * s) {
	int i = 0;
	int l = strlen(s);
	for (i = 0; i < l && isspace(s[i]); i++)
		;

	if (islower(s[i])) {
		printf(
				"Error: Invalid non_terminal. All terminal symbol must be uppercase letters.\n");
		exit(1);
	}

	if (!exists(non_terminals, s[i], nterm_qty)) {
		if (nterm_size == nterm_qty) {
			char * aux;
			aux = realloc(non_terminals, term_size *= 1.5);
			if (aux == NULL) {
				printf("Error: Not enought memory!\n");
				exit(1);
			}
			non_terminals = aux;
		}
		non_terminals[nterm_qty++] = s[i];
	} else {
		printf("Error: Repeated non terminal symbol encountered.\n");
		exit(1);
	}
}

void add_production2(char le, char * s) {
	int i;
	char r1, r2;
	int l = strlen(s);
	for (i = 0; i < l && isspace(s[i]); i++)
		;
	r1 = s[i];
	if (!exists(terminals, r1,
			term_qty) && !exists(non_terminals, r1, nterm_qty) && r1 != LAMDA) {printf (
			"%c -> %c", le, r1)
;		printf("1Error: Invalid right-side production symbol\n");
		exit(1);
	}
	for (i = i + 1; i < l && isspace(s[i]); i++)
		;
	if (i < l && !ispunct(s[i]) && !isspace(s[i])) {
		r2 = s[i];
		if (((!exists(terminals, r2, term_qty)
				&& !exists(non_terminals, r2, nterm_qty)) && (r1 != LAMDA))
				|| ((exists(terminals, r2, term_qty)
						|| exists(non_terminals, r2, nterm_qty))
						&& (r1 == LAMDA))) {
			printf("Error: Invalid right-side production symbol\n");
			exit(1);
		}
	} else {
		r2 = LAMDA;
	}
	add_to_list(productions, new_prod(le, r1, r2));
}

void add_production(char * s) {
	int i;
	int l = strlen(s);
	for (i = 0; i < l && isspace(s[i]); i++)
		;
	char le = s[i];
	if (islower(le) || !exists(non_terminals, s[i], nterm_qty)) {
		printf("Error: Invalid left-side production symbol\n");
		exit(1);
	}
	for (i = i + 1; i < l && isspace(s[i]); i++)
		;
	for (i = i + 1; i < l && isspace(s[i]); i++)
		;
	add_production2(le, s + i + 1);

}

void set_distinguished(char d){
	distinguished = d;
}

void init() {
	term_size = INIT_QTY;
	term_qty = 0;
	terminals = malloc(term_size * sizeof(char));
	nterm_size = INIT_QTY;
	nterm_qty = 0;
	non_terminals = malloc(nterm_size * sizeof(char));
	productions = new_prod_list();
	valid_name = false;
	valid_grammar = false;
	valid_nt = false;
	valid_t = false;
	valid_d = false;
	valid_p = false;
	atexit(finale);
}

void printall() {
	int i;

	printf("G = <{");
	for (i = 0; i < nterm_qty; i++) {
		printf("%c%c ", non_terminals[i], (i == nterm_qty - 1 ? ' ' : ','));
	}
	printf("},{");
	for (i = 0; i < term_qty; i++) {
		printf("%c%c ", terminals[i], (i == term_qty - 1 ? ' ' : ','));
	}
	printf("}, ");
	printf("%c, ", distinguished);

	prod p;
	for (p = productions->head; p != NULL; p = p->next) {
		printf("%c -> %c%c, ", p->left, p->right[0], p->right[1]);
	}
	printf("}>\n");
}

void check_rg() {
	prod p = NULL;
	int gr_type = NONE;
	for(p = productions->head; p != NULL; p=p->next){
		if(!is_unitary(p)){
			if(is_terminal(p->right[0]) && is_non_terminal(p->right[1])){
				if(gr_type == NONE){
					gr_type = RIGHT;
				}
				if(gr_type == LEFT){
					printf("Error: Not a convertible Regular Grammar\n");
					exit(1);
				}
			} else if(is_terminal(p->right[1]) && is_non_terminal(p->right[0])){
				if(gr_type == NONE){
					gr_type = LEFT;
				}
				if(gr_type == RIGHT){
					printf("Error: Not a convertible Regular Grammar\n");
					exit(1);
				}
			} else {
				gr_type = NONE;
			}
		}
	}
}

int is_unitary(prod p){
	return is_non_terminal(p->right[0]) && p->right[1] == LAMDA;
}

void process() {
	if (!valid_name) {
		printf("Syntax Error: Not a valid grammar identifier\n");
		exit(1);
	}
	if (!valid_nt) {
		printf("Syntax Error: Valid non-terminal symbols not found\n");
		exit(1);
	}
	if (!valid_t) {
		printf("Syntax Error: Valid terminals symbols not found\n");
		exit(1);
	}
	if (!valid_d) {
		printf("Syntax Error: Valid distinguished element not found\n");
		exit(1);
	}
	if (!valid_p) {
		printf("Syntax Error: Valid productions not found\n");
		exit(1);
	}
	if (!valid_grammar) {
		printf("Syntax Error: Malformed grammar\n");
		exit(1);
	}

	check_rg();

	GrammarADT gr = newGrammar();

	setTerminals(gr, terminals, term_qty);
	setNonTerminals(gr, non_terminals, nterm_qty);
	setDistinguished(gr, distinguished);

	ProductionsADT ps = newProductions(0);

	prod p = NULL;
	for (p = productions->head; p != NULL; p = p->next) {
		addProduction(ps, newProduction(p->left, p->right[0], p->right[1]));
	}

	setProductions(gr, ps);

	printf("Grammar before Conversion\n");
	printGrammar(gr);

	AutomataADT at = toAutomata(gr);

	printf("Grammar after Conversion\n");
	printGrammar(gr);

	printf("Resultung Automata\n");
	printAutomata(at);

	toDot(at);
	system("dot -Tpng out.dot > out.png");
}

void finale(void){
	destroy_prod_list(productions);
	free(terminals);
	free(non_terminals);
}
