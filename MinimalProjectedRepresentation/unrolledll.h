#ifndef UNROLLEDLL_H
#define UNROLLEDLL_H

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "inequality.h"

#define UNROLLED_LL_SIZE 8

typedef struct node
{
	inequality data[UNROLLED_LL_SIZE];
	int fill;
	struct node* next;
}node;


typedef struct linkedList
{
	node * head;
	int number;
}linkedList;

typedef struct Vnode 
{
	inequality data;
	struct Vnode* next;
}vnode;

typedef struct VlinkedList
{
	Vnode* head;
	int number;
}VlinkedList;

node * makeNode(int varNum);

Vnode * makeVNode(int varNum);

linkedList makeList(int varNum);

VlinkedList makeVList(int varNum);

void addList(linkedList * l , inequality d , int varNum);

void addVList(VlinkedList * vl , inequality d , int varNum);

void sortVList(VlinkedList * vl , int varNum);

inequality * searchIneq (linkedList l , int no , int da , int varNum);

int IsInll(linkedList * l, inequality d, int varNum, int mode);

void freeList(linkedList * d, int varNum);

void freeVList(VlinkedList * vd, int varNum);

#endif
