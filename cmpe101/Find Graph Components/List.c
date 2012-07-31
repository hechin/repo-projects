/*
  Herman Chin
  hchin@ucsc.edu
  Summer 2011
  CMPS 101
  Tantalo
  Lab 5 
*/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

typedef struct Node{
	int data;
	struct Node* next;
	struct Node* prev;
} Node;
typedef Node* NodeRef;

typedef struct List{
	NodeRef curr;
	NodeRef head;
	NodeRef tail;
	int size;
} List;


/*** Constructors-Destructors ***/
NodeRef newNode(int node_data){
        NodeRef N = malloc(sizeof(Node));
        N->data = node_data;
        N->next = NULL;
        N->prev = NULL;
        return(N);
}

void freeNode(NodeRef* pN){
        if( pN!=NULL && *pN!=NULL ){
                free(*pN);
                *pN = NULL;
        }
}

ListRef newList(void){
	ListRef L;
	L = malloc(sizeof(List));
	L->curr = NULL;
	L->head = NULL;
	L->tail = NULL;
	L->size = 0;
	return(L);
}

void freeList(ListRef* pL){
	if( pL!=NULL && *pL!=NULL ){
		while(!isEmpty(*pL)){
			deleteFirst(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}
/*** Access functions ***/
int isEmpty(ListRef L){
	if(L == NULL){
		printf("List Error: isEmpty()isEmpty()");
		exit(1);
	}
	return(L->size == 0);
}
int offEnd(ListRef L){
	return(L->curr == NULL);
}
int atFirst(ListRef L){
        if(isEmpty(L)){
                printf("List error: isEmpty");
                exit(1);
        }
	return(L->curr == L->head);
}

int atLast(ListRef L){
        if(isEmpty(L)){
                printf("List error: isEmpty,atLast");
                exit(1);
        }
	return(L->curr == L->tail);
}
int getFirst(ListRef L){
        if(isEmpty(L)){
                printf("List error: isEmpty");
                exit(1);
        }
	return(L->head->data);
}
int getLast(ListRef L){
        if(isEmpty(L)){
                printf("List error: isEmpty");
                exit(1);
        }
	return(L->tail->data);
}

int getCurrent(ListRef L){
        if(isEmpty(L)){
                printf("List error: isEmpty,getCurrent");
                exit(1);
        }
	return(L->curr->data);
}
int getLength(ListRef L){
        if(isEmpty(L)){
		return(0);
                printf("List error: isEmpty,getLength");
                exit(1);
        }
	return(L->size);
}
/* ret = 1 true, ret = 0 false*/
int equals(ListRef A, ListRef B){
	int ret = 0;
	if(A->head != NULL && B->head != NULL){
		moveFirst(A);
		moveFirst(B);
		while(A->curr != A->tail && B->curr != B->tail){
			if(A->curr->data == B->curr->data){
				ret = 1;
			}else{
				ret = 0;
			}
			A->curr = A->curr->next;
			B->curr = B->curr->next;
		}
                if(A->curr->data == B->curr->data){
                        ret = 1;
                }else{
                        ret = 0;
                }
	}
	return(ret);
};

/*** Manipulation procedures ***/
void makeEmpty(ListRef L){
	if(isEmpty(L)){
		printf("List error: isEmpty error");
		exit(1);
	}
	moveFirst(L);
	while(L->curr != L->tail){
		L->curr->data = 0;		
		L->curr = L->curr->next;
	}
	L->curr = L->head = L->tail = NULL;
	L->size = 0;
}
void moveFirst(ListRef L){
        if(isEmpty(L)){
                printf("List error: isEmpty,moveFirst");
                exit(1);
        }
	L->curr = L->head;
}
void moveLast(ListRef L){
        if(isEmpty(L)){
                printf("List error: isEmpty");
                exit(1);
        }
	L->curr = L->tail;
        if(offEnd(L)){
                printf("List error: moveLast");
                exit(1);
        }
}
void movePrev(ListRef L){
        if(isEmpty(L)){
                printf("List error: isEmpty");
                exit(1);
        }
	if(L->curr->prev != NULL){
	        L->curr = L->curr->prev;
	}
        if(offEnd(L)){
                printf("List error: movePrev");
                exit(1);
        }
}
void moveNext(ListRef L){
        if(isEmpty(L)){
                printf("List error: isEmpty,moveNext");
                exit(1);
        }
        if(L->curr->next != NULL){
                L->curr = L->curr->next;
        }
        if(offEnd(L)){
                printf("List error: movePrev");
                exit(1);
        }
}
void insertBeforeFirst(ListRef L, int data){
        NodeRef newN = newNode(data);
	if(offEnd(L)){
		L->curr = L->head = L->tail = newN;
	}else{
	        moveFirst(L);
		L->curr->prev = newN;
		newN->next = L->curr;
		L->head = newN;
	}
        L->size++;
}
void insertAfterLast(ListRef L, int data){
        NodeRef newN = newNode(data);
        if(offEnd(L)){
                L->curr = L->head = L->tail = newN;
        }else{
	        L->tail->next = newN;
	        newN->prev = L->tail;
		L->tail = newN;
	}
        L->size++;
}
void insertBeforeCurrent(ListRef L, int data){
        NodeRef newN = newNode(data);
        if(offEnd(L)){
		L->curr = L->head = L->tail = newN;
        }
	if(L->curr == L->head){
		insertBeforeFirst(L,data);
	}else{
		newN->prev = L->curr->prev;
		newN->next = L->curr;
		L->curr->prev->next = newN;
		L->curr->prev = newN;
	}
        L->size++;
}
void insertAfterCurrent(ListRef L, int data){
        NodeRef newN = newNode(data);
        if(offEnd(L)){
                L->curr = L->head = L->tail = newN;
        }
        if(L->curr == L->tail){
                insertAfterLast(L,data);
        }else{
                newN->next = L->curr->next;
                newN->prev = L->curr;
                L->curr->next->prev = newN;
                L->curr->next = newN;
        }
	L->size++;
}
void deleteFirst(ListRef L){
	NodeRef N = L->head;
	if(N->next == NULL ){
		L->head = L->curr = L->tail = NULL;
	}else{
		L->head = L->head->next;
		L->head->prev = NULL;
	}
	L->size--;
        freeNode(&N);
}
void deleteLast(ListRef L){
        NodeRef N = L->tail;
        if(N->prev == NULL){
		L->tail = NULL;
	}else{
		L->tail = L->tail->prev;
		L->tail->next = NULL;
        }
        L->size--;
	freeNode(&N);
}
void deleteCurrent(ListRef L){
        if(isEmpty(L) || offEnd(L)){
                printf("List error: isEmpty,deleteCurrent");
                exit(1);
        }
	if(L->curr == L->head){
		deleteFirst(L);
	}else if(L->curr == L->tail){
		deleteLast(L);
	}else{
        	NodeRef N = L->curr;
		L->curr->prev->next = L->curr->next;
		L->curr->next->prev = L->curr->prev;
        	L->size--;
        	freeNode(&N);
		L->curr = NULL;
	}
}
/*** Other operations ***/
void printList(FILE* out, ListRef L){
	if(isEmpty(L) || offEnd(L)){
                printf("List error: printList");
                exit(1);
        }
	NodeRef p = L->head;
	while(p->next != NULL){
		fprintf(out,"%d ",p->data);
		p = p->next;
	}
        fprintf(out,"%d ",p->data);
	fprintf(out,"\n");
}
ListRef copyList(ListRef L){
	moveFirst(L);
	ListRef N;
	N = malloc(sizeof(List));
	N->curr->data = L->curr->data;
	while(L->curr != NULL){
		insertAfterCurrent(N,L->curr->data);
		L->curr = L->curr->next;
		N->curr = N->curr->next;
	}
	return(N);
}

