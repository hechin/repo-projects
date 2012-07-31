/*
  Herman Chin
  hchin@ucsc.edu
  Summer 2011
  CMPS 101
  Tantalo
  Lab 4
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 250

int main(int argc, char * argv[]){
	ListRef TEST = newList();
	ListRef COMP = newList();
	int i;
	FILE *out = fopen("data","w");
	for(i=1; i<=10; i++){
		insertBeforeFirst(TEST,i);
		insertAfterLast(COMP,i);
	}
	moveFirst(TEST);
	moveFirst(COMP);
/*int j = getLength(TEST);
printf("%d ",j);*/
	deleteFirst(TEST);
        deleteFirst(TEST);
	moveFirst(TEST);
	moveNext(TEST);
	moveNext(TEST);
	deleteCurrent(TEST);
	moveFirst(TEST);
	printList(out,TEST);
	printList(out,COMP);
        printf("%d ",getLength(TEST));
	printf("%d ",getLength(COMP));
	fclose(out);
}
