/*
  Herman Chin
  hchin@ucsc.edu
  Summer 2011
  CMPS 101
  Tantalo
  Lab 4

  Description: Find the shortest path to another node on the inputs of this graph for more information refer to the README
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
   int i,v,a,dum,dist =0;
   GraphRef G;
   ListRef L = newList();

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
		if(dum == 1){printGraph(out,G);fprintf(out,"\n");}
	 }
	 if(dum == 0){
		 if(count == 1){
			G = newGraph(i);
		 }else if(count != 1 && n == 1){
			v = i;
		 }else if(count != 1 && n == 2){
			a = i;
			addEdge(G,v,a);
		 }
	 }else if(dum > 0 && i != 0){
		 if(n == 1){
                        v = i;
			BFS(G,v);
                 }else if(n == 2){
                        a = i;
                        getPath(L,G,a);
			dist = getDist(G,a);
			if(dist == INF){
				fprintf(out,"The distance from %d to %d is infinity\n",v,a);
				fprintf(out,"No %d-%d path exists",v,a);
			}else{
				fprintf(out,"The distance from %d to %d is %d\n",v,a,getDist(G,a));
				fprintf(out,"A shortest %d-%d path is: ",v,a);
				printPath(out,L);
			}
			fprintf(out,"\n\n");
                 }
	 }
         token = strtok(NULL, " \n");
      }
   }
   /* close files */
   fclose(in);
   fclose(out);
   freeGraph(&G);
   freeList(&L);
   return(0);
}
