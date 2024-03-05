#include "projection.h"
#include "unrolledll.h"
#include "saturation.h"
#include "fme.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <polylib/polylib.h>
#include <polylib/vector.h>
#include <polylib/arithmetique.h>

using namespace std;
/***********get number from file**********/
ifstream file;
/**************************************/

linkedList project(void)
{
	FILE* eachout = fopen("eachtime.txt", "a");
	fprintf(eachout, "\n");

	int varNum, ineqNum, extrNum;
	int i,j,k;
	mpq_t t; mpq_init(t);
	inequality inputData;

	clock_t start_t, end_t;
	double total_t;

	Matrix *H,*V;
	Polyhedron *POL;

	start_t = clock();

	H = Matrix_Read();
	POL = Constraints2Polyhedron(H,200);
	H = Polyhedron2Constraints(POL);
	V = Polyhedron2Rays(POL);
	
	end_t = clock();
	total_t = difftime(end_t,start_t)/CLOCKS_PER_SEC;
	fprintf(eachout , " polylibDDMtime: %f,", total_t);

	varNum = H->NbColumns - 1;
	ineqNum = H->NbRows;
	extrNum = V->NbRows;

//	BITLONG = (extrNum/8 + 1 )* 8;

	fprintf(eachout , " raynum: %d, ",extrNum);

	makeNewInequality(&inputData, varNum);

	linkedList ine;
	ine = makeList(varNum);
	linkedList eqn;
	eqn = makeList(varNum);

	for(i = 0; i < ineqNum; i++)
	{
		mpq_set_z(inputData.coef[0], H->p[i][varNum]);
		for(j = 1; j < varNum; j++)
		{
			mpq_set_z(inputData.coef[j], H->p[i][j]);
		}
		if(mpz_sgn(H->p[i][0]) == 0)
			addList(&eqn, inputData, varNum);
		else
			addList(&ine, inputData, varNum);
	}

	VlinkedList ext;
	ext = makeVList(varNum);
	for(i = 0; i < extrNum; i++)
	{
		mpq_set_z(inputData.coef[0], V->p[i][varNum]);
		for(j = 1; j < varNum; j++)
		{
			mpq_set_z(inputData.coef[j], V->p[i][j]);
		}
		Simplify(&inputData, varNum);
		addVList(&ext, inputData, varNum);
	}
	sortVList(&ext,varNum);
	
	linkedList outputll;
	outputll = makeList(varNum);

	linkedList pos = makeList(varNum);
	linkedList neg = makeList(varNum);
	linkedList zer = makeList(varNum);

	SAT SATpos = makeSAT(ext.number);
	SAT SATneg = makeSAT(ext.number);
	SAT SATzer = makeSAT(ext.number);

	separate(ine, ext, &pos, &neg, &zer, &SATpos, &SATneg, &SATzer, varNum-1, varNum);

	linkedList Newpos;
	linkedList Newneg;
	linkedList Newzer;

	VlinkedList Newext;

	SAT NewSATpos;
	SAT NewSATneg;
	SAT NewSATzer;

	cout << "pos:" << endl; 
	node * currentout = pos.head->next;
	while( currentout != NULL)
	{
		for(int j = 0 ; j < currentout->fill ; j++)
     	        {
			gmp_printf(" %Qd ", currentout->data[j].coef[0]);
			for(int k = 1 ; k < varNum ; k++)
				gmp_printf("+ (%Qd x_%d) ", currentout->data[j].coef[k], k);
			printf(">= 0 \n");
		}
		currentout = currentout->next;
	}
//	cout << "SATpos: " << endl;
//	printSAT(SATpos);

	cout << "neg: " << endl;
	currentout = neg.head->next;
	while( currentout != NULL)
	{
		for(int j = 0 ; j < currentout->fill ; j++)
     	        {
			gmp_printf(" %Qd ", currentout->data[j].coef[0]);
			for(int k = 1 ; k < varNum ; k++)
				gmp_printf("+ (%Qd x_%d) ", currentout->data[j].coef[k], k);
			printf(">= 0 \n");
		}
		currentout = currentout->next;
	}
//	cout << "SATneg: " << endl;
//	printSAT(SATneg);

	cout << "zer: " << endl;
	currentout = zer.head->next;
	while( currentout != NULL)
	{
		for(int j = 0 ; j < currentout->fill ; j++)
     	        {
			gmp_printf(" %Qd ", currentout->data[j].coef[0]);
			for(int k = 1 ; k < varNum ; k++)
				gmp_printf("+ (%Qd x_%d) ", currentout->data[j].coef[k], k);
			printf(">= 0 \n");
		}
		currentout = currentout->next;
	}
//	cout << "SATzer: " << endl;
//	printSAT(SATzer);
//	cout << endl;

	cout << "eqn:" << endl;
	currentout = eqn.head->next;
	while( currentout != NULL)
	{
		for(int j = 0 ; j < currentout->fill ; j++)
     	        {
			gmp_printf(" %Qd ", currentout->data[j].coef[0]);
			for(int k = 1 ; k < varNum ; k++)
				gmp_printf("+ (%Qd x_%d) ", currentout->data[j].coef[k], k);
			printf("= 0 \n");
		}
		currentout = currentout->next;
	}

//	Vnode* currents = ext.head->next;
//	while(currents != NULL)
//	{
//		for(int k = 0; k < varNum; k++)
//			gmp_printf("%Qd ", currents->data.coef[k]);
//		printf("\n");
//		currents = currents->next;
//	}

	cout << endl;
	
	for(int elimv = varNum - 1; elimv >= 2; elimv--)
	{
		cout << "elim variable: x" << elimv << endl;

		Newpos = makeList(varNum);
		Newneg = makeList(varNum);
		Newzer = makeList(varNum);

		Newext = makeVList(varNum);
		
		int extproj[ext.number];
		Projvertex(&Newext, extproj, ext, elimv, varNum);

		NewSATpos = makeSAT(Newext.number);
		NewSATneg = makeSAT(Newext.number);
		NewSATzer = makeSAT(Newext.number);

		MCSonestep(pos, neg, zer, &eqn, SATpos, SATneg, SATzer, &Newext, extproj, elimv, varNum,
				&Newpos, &Newneg, &Newzer, &NewSATpos, &NewSATneg, &NewSATzer);

		freeList(&pos, varNum);
		freeList(&neg, varNum);
		freeList(&zer, varNum);
		freeVList(&ext, varNum);
		freeSAT(&SATpos);
		freeSAT(&SATneg);
		freeSAT(&SATzer);

		pos.number = Newpos.number;
		pos.head->next = Newpos.head->next;

		neg.number = Newneg.number;
		neg.head->next = Newneg.head->next;
 
		zer.number = Newzer.number;
		zer.head->next = Newzer.head->next;

		SATpos.rows = NewSATpos.rows;
		SATpos.row_bit = NewSATpos.row_bit;
		SATpos.cols = NewSATpos.cols;
		SATpos.col_bit = NewSATpos.col_bit;
		SATpos.countcol = NewSATpos.countcol;
		SATpos.head->next = NewSATpos.head->next;

		SATneg.rows = NewSATneg.rows;
		SATneg.row_bit = NewSATneg.row_bit;
		SATneg.cols = NewSATneg.cols;
		SATneg.col_bit = NewSATneg.col_bit;
		SATneg.countcol = NewSATneg.countcol;
		SATneg.head->next = NewSATneg.head->next;

		SATzer.rows = NewSATzer.rows;
		SATzer.row_bit = NewSATzer.row_bit;
		SATzer.cols = NewSATzer.cols;
		SATzer.col_bit = NewSATzer.col_bit;
		SATzer.countcol = NewSATzer.countcol;
		SATzer.head->next = NewSATzer.head->next;

		ext.number = Newext.number;
        	ext.head->next = Newext.head->next;

        	cout << "pos: " << endl;	
                currentout = pos.head->next;
        	while( currentout != NULL)
                {
             		for(int j = 0 ; j < currentout->fill ; j++)
                  	{
             			gmp_printf(" %Qd ", currentout->data[j].coef[0]);
             			for(int k = 1 ; k < varNum ; k++)
             				gmp_printf("+ (%Qd x_%d) ", currentout->data[j].coef[k], k);
             			printf(">= 0 \n");
             		}
             		currentout = currentout->next;
             	}
             
             	cout << "neg: " << endl;
             	currentout = neg.head->next;
             	while( currentout != NULL)
             	{
             		for(int j = 0 ; j < currentout->fill ; j++)
                        {
             			gmp_printf(" %Qd ", currentout->data[j].coef[0]);
             			for(int k = 1 ; k < varNum ; k++)
             				gmp_printf("+ (%Qd x_%d) ", currentout->data[j].coef[k], k);
             			printf(">= 0 \n");
             		}
             		currentout = currentout->next;
             	}
             
             	cout << "zer: " << endl;
             	currentout = zer.head->next;
             	while( currentout != NULL)
             	{
             		for(int j = 0 ; j < currentout->fill ; j++)
                  	{
             			gmp_printf(" %Qd ", currentout->data[j].coef[0]);
             			for(int k = 1 ; k < varNum ; k++)
             				gmp_printf("+ (%Qd x_%d) ", currentout->data[j].coef[k], k);
             			printf(">= 0 \n");
             		}
             		currentout = currentout->next;
             	}
             
             	cout << "eqn:" << endl;
             	currentout = eqn.head->next;
             	while( currentout != NULL)
             	{
             		for(int j = 0 ; j < currentout->fill ; j++)
                        {
             			gmp_printf(" %Qd ", currentout->data[j].coef[0]);
             			for(int k = 1 ; k < varNum ; k++)
             				gmp_printf("+ (%Qd x_%d) ", currentout->data[j].coef[k], k);
             			printf("= 0 \n");
             		}
             		currentout = currentout->next;
                }

		end_t = clock();
		total_t = difftime(end_t, start_t)/CLOCKS_PER_SEC;
		fprintf(eachout," %d elimtime: %f, ", varNum - elimv, total_t);

		cout << endl;
		printf("inequality number after elimination: %d\n", pos.number + neg.number + zer.number + eqn.number);
                cout << endl;
//		printf("extreme ray number after elimination: %d\n", ext.number);
//		cout << endl;

		if(pos.number == 0 && neg.number == 0 && zer.number == 1 && eqn.number == 0)
		{
			printf(" There is only one inequality. Stop elimination.\n");
			break;
		}      
	
	}

//	fclose(eachout);

	cout << "pos: " << endl;	
        currentout = pos.head->next;
	while( currentout != NULL)
        {
     		for(int j = 0 ; j < currentout->fill ; j++)
          	{
     			gmp_printf(" %Qd ", currentout->data[j].coef[0]);
     			for(int k = 1 ; k < varNum ; k++)
     				gmp_printf("+ (%Qd x_%d) ", currentout->data[j].coef[k], k);
     			printf(">= 0 \n");
     		}
     		currentout = currentout->next;
     	}
     
     	cout << "neg: " << endl;
     	currentout = neg.head->next;
     	while( currentout != NULL)
     	{
     		for(int j = 0 ; j < currentout->fill ; j++)
                {
     			gmp_printf(" %Qd ", currentout->data[j].coef[0]);
     			for(int k = 1 ; k < varNum ; k++)
     				gmp_printf("+ (%Qd x_%d) ", currentout->data[j].coef[k], k);
     			printf(">= 0 \n");
     		}
     		currentout = currentout->next;
     	}
     
     	cout << "zer: " << endl;
     	currentout = zer.head->next;
     	while( currentout != NULL)
     	{
     		for(int j = 0 ; j < currentout->fill ; j++)
          	{
     			gmp_printf(" %Qd ", currentout->data[j].coef[0]);
     			for(int k = 1 ; k < varNum ; k++)
     				gmp_printf("+ (%Qd x_%d) ", currentout->data[j].coef[k], k);
     			printf(">= 0 \n");
     		}
     		currentout = currentout->next;
     	}
     
     	cout << "eqn:" << endl;
     	currentout = eqn.head->next;
     	while( currentout != NULL)
     	{
     		for(int j = 0 ; j < currentout->fill ; j++)
                {
     			gmp_printf(" %Qd ", currentout->data[j].coef[0]);
     			for(int k = 1 ; k < varNum ; k++)
     				gmp_printf("+ (%Qd x_%d) ", currentout->data[j].coef[k], k);
     			printf("= 0 \n");
     		}
     		currentout = currentout->next;
        }
//	cout << "final extreme rays:" << endl;
//	 Vnode* currentV = ext.head->next;
//	while(currentV != NULL)
//	{
//		for(int k = 0; k < varNum; k++)
//			gmp_printf("%Qd ", currentV->data.coef[k]);
//		printf("\n");
//		currentV = currentV->next;
//	}
//	cout << endl;


//	cout << "varNum: " << varNum << endl;
//	cout << "ineqNum: " << ineqNum << endl;
//	cout << "extrNum: " << extrNum << endl;

	return outputll;

}
