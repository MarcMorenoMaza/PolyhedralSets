#ifndef SATURATION_H
#define SATURATION_H

#include <stdio.h>
#include <stdlib.h>
#include "inequality.h"
#include "unrolledll.h"
#include "bitarray.h"

#define BITLONG 1024 //the length of bit array
#define NODENUM (BITLONG/8)  //how many nodes A bit array covers

int BITNUM(int number);

typedef struct satnode
{
	bit_array_t*** SATrow;
	bit_array_t** SATcol;
	int rowfill;

	struct satnode* next;
}satnode;

typedef struct SAT
{
	int rows;
	int row_bit;
	int cols;
	int col_bit;
	int* countcol;

	satnode* head;
}SAT;

satnode* makeSatNode(int cols);

SAT makeSAT(int cols);

void printSAT(SAT saturation);

void freeSAT(SAT* saturation);

void addSAT_Data(SAT* saturation, bit_array_t** SATdata);

bool IsZeroBit(bit_array_t* rela);

#endif
