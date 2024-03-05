#include "inequality.h"

/*
 * constructor function
 */

void makeNewInequality(inequality * newIneq, int varNum)
{
	int i;

	newIneq->coef = (mpq_t *) malloc(varNum * sizeof(mpq_t));

	for (i = 0; i < varNum; i++)
		mpq_init(newIneq->coef[i]);

}


void freeIneq(inequality * a , int varNum)
{
	for(int i = 0 ; i < varNum; i++)
		mpq_clear(a->coef[i]);
	free(a->coef);
}

/*
 * set inequality
 */
void setInequalityCoefs(inequality * a, mpq_t * coefs, int varNum)
{
	int i;
	for (i = 0; i < varNum; i++)
		mpq_set(a->coef[i], coefs[i]);
}

void copyIneq(inequality a, inequality * b, int varNum)
{
	int i;
	makeNewInequality(b, varNum);

	for (i = 0; i < varNum; i++)
		mpq_set(b->coef[i], a.coef[i]);

}
//
///**
// * copy a list of inequalities
// 
//dataSave should be allocated before
void copyListOfInequalities(inequality * data, inequality * dataSave,
		int varNum, int ineqNum)
{

	int i;

	for (i = 0; i < ineqNum; i++)
		copyIneq(data[i], &(dataSave[i]), varNum);

}

//
//* check whether an extreme ray satisfies an inequality or not
//
int satis(inequality a, extremeray b, int varNum)
{
	mpq_t sum;mpq_init(sum);
	
	int i;

	for(i = 0; i < varNum; i++)
	{
		mpq_t product;mpq_init(product);
		mpq_mul(product, a.coef[i], b.coef[i]);
		mpq_add(sum, sum, product);
	}
	if(mpq_sgn(sum) == 0)
		return 1;
	else
		return 0;
}
//
//* simplify the inequality
//
void Simplify(inequality * a, int varNum)
{
	int i;
	for(i = 0; i < varNum; i++)
	{
		if(mpq_sgn(a->coef[i])!= 0)
		{
			mpq_t divnum; mpq_init(divnum);
			mpq_abs(divnum, a->coef[i]);
			int j;
			for(j = i; j < varNum; j++)
			{
				mpq_div(a->coef[j],a->coef[j],divnum);
			}
			break;
		}
	}

}
//
//* compare whether two simpilified inequalities are the same or not
//same, 1; not same, 0;
int Same(inequality a, inequality b, int varNum)
{
	for(int i = 0; i < varNum; i++)
	{
		if(mpq_equal(a.coef[i], b.coef[i]) == 0)
		{
			return 0;
		}
	}

	return 1;
}
//
//* check whether the inequality is zero inequality or not
//zero, 1; not zero, 0;
int IsZero(inequality a, int varNum)
{
	for(int i = 0; i < varNum; i++)
	{
		if(mpq_sgn(a.coef[i]) != 0)
		{
			return 0;
		}
	}

	return 1;
}
//
//*compare which one is bigger under index order
//a>b, 1; a=b, 0; a<b, -1;
int Compare(inequality a, inequality b, int varNum)
{
	int flag = 0;
	for(int i = 0; i < varNum; i++)
	{
		int flag = mpq_cmp(a.coef[i], b.coef[i]);
		if(flag > 0)
		{
			return 1;
		}
		else if(flag < 0)
		{
			return -1;
		}
	}

	return 0;

}
//
//*
//
void Elimequation(inequality* newine, inequality a, inequality eqn, int elimv, int varNum)
{
	for(int i = 0; i < elimv; i++)
	{
		mpq_t temp; mpq_init(temp);
		mpq_mul(temp, a.coef[elimv], eqn.coef[i]);
		mpq_div(temp, temp, eqn.coef[elimv]);
		mpq_sub(newine->coef[i], a.coef[i], temp);
	}


}
