/*
  Herman Chin
  hchin@ucsc.edu
  Summer 2011
  CMPS 101
  Tantalo
  Lab 4

  Description: Library for the creating a graph in C
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
        int* distance;
        int verticesOrder;
        int edgesSize;
        int sourceVertex;
}Graph;
/*** Constructors-Destructors ***/ 
GraphRef newGraph(int n){
	int i = 0;
        GraphRef G = malloc(sizeof(Graph));
	G->adj = (ListRef*)malloc((n+1)*sizeof(ListRef));
	for(i=1;i<n+1;i++){
		G->adj[i] = newList();
	} 
        G->color = calloc(n+1,sizeof(int));
        G->distance = calloc(n+1,sizeof(int));
        G->parent = calloc(n+1,sizeof(int));
        G->verticesOrder = n;
        G->edgesSize = 0;
        G->sourceVertex = 0;
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
	free((*pG)->distance);
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
int getDist(GraphRef G, int u){
        return(G->distance[u]);
}; 
void getPath(ListRef L, GraphRef G, int u){
	if(u == getSource(G)){
		insertAfterLast(L,getSource(G));
	}else if(G->parent[u] == NIL){
		insertAfterLast(L,NIL);
		return;
	}else{
		getPath(L,G,G->parent[u]);
		insertAfterLast(L,u);
	}
}; 
/*** Manipulation procedures ***/ 
void makeNull(GraphRef G){
        int i = 0;
	int n = getSource(G);
        for(i=1;i<n+1;i++){
                G->adj[i] = NULL;
        }
        G->color = NULL;
        G->distance = NULL;
        G->parent = NULL;
        G->verticesOrder = 0;
        G->edgesSize = 0;
        G->sourceVertex = 0;	
}; 
void addEdge(GraphRef G, int u, int v){
	if(u <= getOrder(G) && u >= 1 && v <= getOrder(G) && v >= 1){
		insertAfterLast(G->adj[v],u);
		insertAfterLast(G->adj[u],v);
		G->edgesSize++;
	}
}; 
void addArc(GraphRef G, int u, int v){
        if(u <= getOrder(G) && u >= 1){
                insertAfterLast(G->adj[u],v);
        }
}; 
void BFS(GraphRef G, int s){
	G->sourceVertex = s;
	int o = getOrder(G)+1;
	int x,u,v = 0;
	for(x=1; x<o; x++){
		G->color[x] = 0;
		G->distance[x] = INF;
		G->parent[x] = NIL;
	}
	G->color[s] = 1;
	G->distance[s] = 0;
	G->parent[s] = NIL;
	ListRef Q = newList();
	insertAfterLast(Q,s);
	while(!isEmpty(Q)){
		u = getFirst(Q);
		deleteFirst(Q);
                moveFirst(G->adj[u]);
		for(x=0;x<getLength(G->adj[u]);x++){
			v = getCurrent(G->adj[u]);
			if(G->color[v] == 0){
				G->color[v] = 1;
				G->distance[v] = G->distance[u]+1;
				G->parent[v] = u;
				insertAfterLast(Q,v);
			}
			moveNext(G->adj[u]);
		}
		G->color[u] = 2;
	}
	freeList(&Q);
}; 
/*** Other operations ***/ 
void printGraph(FILE* out, GraphRef G){
	int i = getOrder(G)+1;
	int v = 0;
	int x = 1;
	ListRef h;
	for(x=1;x<i;x++){
		fprintf(out,"%d: ",x);
		h = G->adj[x];
                for(moveFirst(h);
                     !atLast(h);moveNext(h)){
			v = getCurrent(h);
			fprintf(out,"%d ",v);
		}
		v = getCurrent(h);
                fprintf(out,"%d ",v);
		fprintf(out,"\n");
	}
};
void printPath(FILE* out, ListRef L){
	int x;
	moveFirst(L);
	for(x=0;x<getLength(L);x++){
		fprintf(out,"%d ",getCurrent(L));
		moveNext(L);
	}
	makeEmpty(L);
};
