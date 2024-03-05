#ifndef SET_H
#define SET_H


#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

typedef struct setnode{
	int* data;
	int size;
	struct setnode* next;
}setnode;

typedef struct Set{
	int number;
	setnode* head;
}Set;

setnode* makesetNode(int size);

Set makeSet(void);

void addSet(Set* s, int* data, int size);

void removeSet(Set* s, int* data, int size);

int IsInSet(Set s, int* data, int size);

void displaySet(Set s);

#endif
