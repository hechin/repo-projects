/*
  Herman Chin
  hchin@ucsc.edu
  Summer 2011
  CMPS 101
  Tantalo
  Lab 5 

  Description: Find all the components of the inputed graph
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"
#define MAX_LEN 250


int main(int argc, char * argv[]){

   int n, count=0;
   FILE *in, *out;
   char line[MAX_LEN];
   char tokenlist[MAX_LEN];
   char* token;
   int i,v,a,dum,comp =0;
   GraphRef G;
   GraphRef GT;
   ListRef L = newList();
   ListRef Lt = newList();

   /* check command line for correct number of arguments */
   if( argc != 3 ){
      printf("Usage: %s infile outfile\n", argv[0]);
      exit(1);
   }

   /* open files for reading and writing */
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   /* read each line of input file, then count and print tokens */
   while( fgets(line, MAX_LEN, in) != NULL)  {
      count++;
      n = 0;
      token = strtok(line, " \n");
      tokenlist[0] = '\0';
      while( token!=NULL ){
         strcat(tokenlist, "   ");
         strcat(tokenlist, token);
         strcat(tokenlist, "\n");
         n++;
	 i = atoi(token);
	 if(i == 0){
		dum++;
		if(dum == 1){
			fprintf(out,"Adjacency list representation of G: \n");
			printGraph(out,G);
			fprintf(out,"\n");
			DFS(G,L);
			GT = transpose(G);
			DFS(GT,Lt);
			moveFirst(Lt);
			a = getCurrent(Lt);
			fprintf(out,"G contains %d strong connected components:",a);
			moveNext(Lt);
			i = getLength(Lt)-1;
			for(a =0;a<i;a++){
				v = getCurrent(Lt);
				if(getParent(GT,v) == NIL){
					comp++;
					fprintf(out,"\nComponent %d: ",comp);
				}
				fprintf(out,"%d ",v);
				moveNext(Lt);
			}
			fprintf(out,"\n");
		}
	 }
	 if(dum == 0){
		 if(count == 1){
			G = newGraph(i);
		 }else if(count != 1 && n == 1){
			v = i;
		 }else if(count != 1 && n == 2){
			a = i;
			addArc(G,v,a);
		 }
	 }
         token = strtok(NULL, " \n");
      }
   }
   /* close files */
   fclose(in);
   fclose(out);
   freeGraph(&GT);
   freeGraph(&G);
   freeList(&L);
   freeList(&Lt);
   return(0);
}
