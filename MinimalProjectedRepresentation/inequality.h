#ifndef INEQUALITY_H
#define INEQUALITY_H


#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#define MAX_LEN 500

typedef struct {
	mpq_t * coef;
} inequality;

typedef inequality extremeray;

void makeNewInequality(inequality *, int);

void freeIneq(inequality *, int);

void setInequalityCoefs(inequality *, mpq_t *, int);

void copyIneq(inequality, inequality *, int);

void copyListOfInequalities(inequality *, inequality *, int, int);

int satis(inequality, extremeray, int);

void Simplify(inequality *, int);

int Same(inequality, inequality, int);

int IsZero(inequality, int);

int Compare(inequality, inequality, int);

void Elimequation(inequality *, inequality , inequality , int , int );

#endif
