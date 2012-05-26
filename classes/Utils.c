/*
 * Utils.c
 *
 *  Created on: May 25, 2012
 *      Author: joseignaciosantiagogalindo
 */

# include "../include/utils.h"


int getDifferents( char * first, int firstquant, char * sec, int secquant, char ** notinfirst){
	int i,n=0;
	char * aux = NULL;
	char * aux2 = NULL;
	for(i=0; i<firstquant; i++){
		if (i < secquant){
			if ( containsChar(first,firstquant,sec[i]) ){
				continue;
			}
		}
		if ( ( aux = realloc(aux2,sizeof(char)*(n+1)) ) == NULL ){
				fprintf(stderr, "Error doing realloc \n");
		}
		aux2 = aux;
		aux2[n++] = first[i];
	}
	*notinfirst = aux2;
	return n;
}

int containsChar(char * array , int size, char c){
	int i;
	for(i=0; i< size; i++){
		if (array[i] == c){
			return 1;
		}
	}
	return 0;
}

void printArray(char * array, int size){
	int i;
	printf("\narray: {");
	for (i =0; i<size; i++){
		printf("%c", array[i] );
	}
	printf("}\n");
}

void addPair(char ** unitaries, int * size,char first, char sec ){
	char * aux = NULL;
	if (!containsPair(*unitaries,*size,first,sec)){
		if ( ( aux = realloc(*unitaries, sizeof(char)*(2+(*size))) ) == NULL ){
			fprintf(stderr, "Error doing realloc \n");
		}
		*unitaries = aux;
		(*unitaries)[*size] = first;
		(*unitaries)[(*size)+1] = sec;
		(*size) = (*size) +2;
	}
}

int containsPair(char * unitaries, int size, char first, char sec){
	int i;
	for (i=0; i<size; i+=2){
		if (unitaries[i] == first && unitaries[i+1] == sec){
			return 1;
		}
	}
	return 0;
}


void printByPairs(char * unitaries,int size){
	printf("\nunitaries: ");
	int i;
	for(i =0; i< size; i+=2){
		printf("(%c,%c)", unitaries[i],unitaries[i+1]);
	}
	printf("\n");

}

int isTerminal(char symbol){
	return islower(symbol);
}

int isNonTerminal(char symbol){
	return isupper(symbol);
}

