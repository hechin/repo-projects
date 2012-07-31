/*
  Herman Chin
  hchin@ucsc.edu
  Summer 2011
  CMPS 101
  Tantalo
  Lab 4
*/

#include "List.h"
#if !defined(_GRAPH_H_INCLUDE_)
#define _GRAPH_H_INCLUDE_
#define INF -2
#define NIL -3 

typedef struct Graph * GraphRef;
/*** Constructors-Destructors ***/ 
GraphRef newGraph(int n); 
void freeGraph(GraphRef* pG); 
/*** Access functions ***/ 
int getOrder(GraphRef G); 
int getSize(GraphRef G); 
int getSource(GraphRef G); 
int getParent(GraphRef G, int u); 
int getDist(GraphRef G, int u); 
void getPath(ListRef L, GraphRef G, int u); 
/*** Manipulation procedures ***/ 
void makeNull(GraphRef G); 
void addEdge(GraphRef G, int u, int v); 
void addArc(GraphRef G, int u, int v); 
void BFS(GraphRef G, int s); 
/*** Other operations ***/ 
void printGraph(FILE* out, GraphRef G);
void printPath(FILE* out, ListRef L);
#endif
