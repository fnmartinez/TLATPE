/*
 * UtilTest.c
 *
 *  Created on: May 25, 2012
 *      Author: joseignaciosantiagogalindo
 */

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "../include/utils.h"

void containsCharTest();
void getDifferentsTest();

char array1[5] = {'A','B','C','D','E'};
char array2[3] = {'A','B','C'};
char * array3;

int main(){
	containsCharTest();
	getDifferentsTest();
	return 0;
}



void containsCharTest(){
	printf("\n Testing containsChar Method \n");
	printArray(array1, 5);
	printf("contains A: %d\n",containsChar(array1,sizeof(array1),'A'));
	printf("contains E: %d\n",containsChar(array1,sizeof(array1),'E'));
	printf("contains F: %d\n",containsChar(array1,sizeof(array1),'F'));

}

void getDifferentsTest(){
	printf("\n Testing getDifferents Method \n");
	printArray(array1, 5);
	printArray(array2, 3);
	int size = getDifferents(array1, 5,array2, 3, &array3);
	printf("size: %i\n",size);
	printArray(array3, size);
}
