/*
 * Utils.c
 *
 *  Created on: May 25, 2012
 *      Author: joseignaciosantiagogalindo
 */

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
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
