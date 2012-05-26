/*
 * utils.h
 *
 *  Created on: May 25, 2012
 *      Author: joseignaciosantiagogalindo
 */

#ifndef UTILS_H_
#define UTILS_H_

// sudo gcc -g -Wall  UtilTest.c ../classes/Utils.c -o utils

int containsChar(char * array , int size, char c);
int getDifferents( char * first,  int firstquant, char * sec, int secquant, char ** notinfirst);
void printArray(char * array, int size);

/*for unitaries auxiliar array*/
void addPair(char ** unitaries, int * size,char first, char sec );
int containsPair(char * unitaries,int size, char first, char sec);
void printByPairs(char * unitaries,int size);
#endif /* UTILS_H_ */
