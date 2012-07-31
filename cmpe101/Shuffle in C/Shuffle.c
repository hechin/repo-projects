/* Herman Chin
   CMPS 101
   Summer 2011
   Tantalo
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 250

int main(int argc, char * argv[]){

   int n,i, count=0;
   int modBuild = 1;
   int marker = 1;
   int offend = 0;
   int equal = 0;
   int Pdata = 0;
   int Mdata = 0;
   int counter = 1;
   FILE *in, *out;
   char line[MAX_LEN];
   char tokenlist[MAX_LEN];
   char* token;
   ListRef modList = newList();
   ListRef permList = newList();
   ListRef modList2 = newList();

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
/* for every token add to perm list */
      while( token!=NULL ){
         strcat(tokenlist, "   ");
         strcat(tokenlist, token);
         strcat(tokenlist, "\n");
         n++;
	 if(count != 1){
		i = atoi(token);
		insertAfterCurrent(permList,i);
	 }
	 token = strtok(NULL, " \n");
      }
/* build mod list */
      if(count != 1){
	      for(modBuild = 1; modBuild < n+1; modBuild++){
			insertAfterCurrent(modList,modBuild);
			insertAfterCurrent(modList2,modBuild);
	      }
	      moveFirst(permList);
	      moveLast(modList);
	      offend = offEnd(permList);
/* traverse lists compare and apply changes */
	      while(offend != 1){
                        Mdata = getFirst(modList);
			Pdata = getCurrent(permList); 
/* fix marker */
			while(marker != Pdata){
				if(Pdata < marker){
					marker--;
					movePrev(modList);
				}else if(Pdata > marker){
					marker++;
					moveNext(modList);
				}
			}
/* insert after the marker */
                        insertAfterCurrent(modList,Mdata);
                        deleteFirst(modList);
/* move to next node in lists */
			moveNext(permList);
			offend = offEnd(permList);
	      }
/* print first permuation */
	      moveFirst(modList);
	      fprintf(out,"(");
	      offend = offEnd(modList);
	      while(offend != 1){
			Mdata = getCurrent(modList);
			fprintf(out,"%d ",Mdata);
			moveNext(modList);
			offend = offEnd(modList);
	      }
	      fprintf(out,") count = ");
/* do remaining permutations */
	      moveFirst(modList);
	      moveFirst(modList2);
	      equal = equals(modList,modList2);
	      marker = 1;
/* if not equal permute again and increment counter */
	      while(equal != 1){
			counter++;
			moveFirst(permList);
			moveLast(modList);
			offend = offEnd(permList);
	                while(offend != 1){
	                        Mdata = getFirst(modList);
	                        Pdata = getCurrent(permList);
	                        while(marker != Pdata){
	                                if(Pdata < marker){
	                                        marker--;
	                                        movePrev(modList);
	                                }else if(Pdata > marker){
	                                        marker++;
	                                        moveNext(modList);
	                                }
	                        }

	                        insertAfterCurrent(modList,Mdata);
	                        deleteFirst(modList);

	                        moveNext(permList);
	                        offend = offEnd(permList);
	              }
		      moveFirst(modList);
                      moveFirst(modList2);
		      equal = equals(modList,modList2);
	      }
/* print out counter and move to next line */
	      fprintf(out,"%d \n",counter);
	      counter = 1;
	      makeEmpty(modList);
	      makeEmpty(modList2);
      }
   }

   /* close files */
   fclose(in);
   fclose(out);

   return(0);
}
