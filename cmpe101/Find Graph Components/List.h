/*
  Herman Chin
  hchin@ucsc.edu
  Summer 2011
  CMPS 101
  Tantalo
  Lab 5 
*/

#if !defined(_LIST_H_INCLUDE_)
#define _LIST_H_INCLUDE_
typedef struct List* ListRef;
/*** Constructors-Destructors ***/ 
ListRef newList(void); 
void freeList(ListRef* pL); 
/*** Access functions ***/ 
int isEmpty(ListRef L); 
int offEnd(ListRef L); 
int atFirst(ListRef L); 
int atLast(ListRef L); 
int getFirst(ListRef L); 
int getLast(ListRef L); 
int getCurrent(ListRef L); 
int getLength(ListRef L); 
int equals(ListRef A, ListRef B); 
/*** Manipulation procedures ***/ 
void makeEmpty(ListRef L); 
void moveFirst(ListRef L); 
void moveLast(ListRef L); 
void movePrev(ListRef L); 
void moveNext(ListRef L); 
void insertBeforeFirst(ListRef L, int data); 
void insertAfterLast(ListRef L, int data); 
void insertBeforeCurrent(ListRef L, int data); 
void insertAfterCurrent(ListRef L, int data); 
void deleteFirst(ListRef L); 
void deleteLast(ListRef L); 
void deleteCurrent(ListRef L); 
/*** Other operations ***/ 
void printList(FILE* out, ListRef L); 
ListRef copyList(ListRef L); 
#endif
