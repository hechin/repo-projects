/*
  Herman Chin
  hchin@ucsc.edu
  Summer 2011
  CMPS 101
  Tantalo
  Lab 5 

  Description: The graph library used to create the graph
*/
#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Graph.h"
#define MAX_LEN 150

typedef struct Graph{
        ListRef* adj;
        int* color;
        int* parent;
        int* discover;
	int* finish;
        int verticesOrder;
        int edgesSize;
        int sourceVertex;
	int time;
}Graph;
/*** Constructors-Destructors ***/ 
GraphRef newGraph(int n){
	int i = 0;
        GraphRef G = malloc(sizeof(Graph));
	G->adj = (ListRef*)malloc((n+1)*sizeof(ListRef));
	for(i=0;i<n+1;i++){
		G->adj[i] = newList();
	} 
        G->color = calloc(n+1,sizeof(int));
        G->discover = calloc(n+1,sizeof(int));
        G->finish = calloc(n+1,sizeof(int));
        G->parent = calloc(n+1,sizeof(int));
        G->verticesOrder = n;
        G->edgesSize = 0;
        G->sourceVertex = 0;
	G->time = 0;
	return(G);
}; 
void freeGraph(GraphRef* pG){
	if ( pG == NULL || *pG == NULL ) { return; }
	if((*pG)->adj != NULL){
	        int i = getOrder(*pG)+1;
	        int x = 0;
	        for(x=1;x<i;x++){
			freeList(&(*pG)->adj[x]);
	        }
	}

	free((*pG)->color);
	free((*pG)->discover);
	free((*pG)->finish);
        free((*pG)->parent);
	free(*pG);
	*pG = NULL;
}; 
/*** Access functions ***/ 
int getOrder(GraphRef G){
	return(G->verticesOrder);
}; 
int getSize(GraphRef G){
        return(G->edgesSize);
}; 
int getSource(GraphRef G){
	return(G->sourceVertex);
}; 
int getParent(GraphRef G, int u){
        return(G->parent[u]);
};
int getDiscover(GraphRef G,int u){
	return(G->discover[u]);
}; 
int getFinish(GraphRef G,int u){
	return(G->finish[u]);
};
/*** Manipulation procedures ***/ 
void addArc(GraphRef G, int u, int v){
        if(u <= getOrder(G) && u >= 1){
                insertAfterLast(G->adj[u],v);
        }
}; 
void DFS(GraphRef G, ListRef S){
	int o = getOrder(G)+1;
	int x = 0;
	for(x=1; x<o; x++){
		G->color[x] = 0;
		G->parent[x] = NIL;
	}
	for(x=1; x<o; x++){
		if(G->color[x] == 0){
			Visit(G,x);
		}
	}
	int dob = o+o;
	int arr[dob];
	int count = 0;
	for(x=0;x<dob;x++){
		arr[x] = 0;
	}
	for(x=1;x<o;x++){
		arr[G->discover[x]] = x;
		if(G->parent[x] == NIL)count++;
	}
	insertAfterLast(S,count);
	for(x=1;x<dob;x++){
		if(arr[x] != 0){
			insertAfterLast(S,arr[x]);
		}
	}
};
void Visit(GraphRef G, int u){
        G->color[u] = 1;
        G->time++;
        G->discover[u] = G->time;
        int k,v,GL = 0;
	GL = getLength(G->adj[u]);
	if(GL != 0){
	moveFirst(G->adj[u]);
        for(k=0;k<GL;k++){
		v = getCurrent(G->adj[u]);
                if(G->color[v] == 0){
                        G->parent[v] = u;
                        Visit(G,v);
                }
		moveNext(G->adj[u]);
        }
	}
        G->color[u] = 2;
        G->time++;
        G->finish[u] = G->time;
};
/*** Other operations ***/ 
GraphRef transpose(GraphRef G){
        int i = getOrder(G)+1;
	GraphRef GT = newGraph(i-1);
        int v = 0;
        int x = 1;
        ListRef h;
        for(x=1;x<i;x++){
                h = G->adj[x];
                if(!isEmpty(h)){
                        for(moveFirst(h);
                             !atLast(h);moveNext(h)){
                                v = getCurrent(h);
				addArc(GT,v,x);
                        }
                        v = getCurrent(h);
			addArc(GT,v,x);
                }
        }
	return(GT);
};
GraphRef copyGraph(GraphRef G);
void printGraph(FILE* out, GraphRef G){
	int i = getOrder(G)+1;
	int v = 0;
	int x = 1;
	ListRef h;
	for(x=1;x<i;x++){
		fprintf(out,"%d: ",x);
		h = G->adj[x];
		if(!isEmpty(h)){
	                for(moveFirst(h);
	       	             !atLast(h);moveNext(h)){
				v = getCurrent(h);
				fprintf(out,"%d ",v);
			}
			v = getCurrent(h);
	                fprintf(out,"%d ",v);
		}
		fprintf(out,"\n");
	}
};

