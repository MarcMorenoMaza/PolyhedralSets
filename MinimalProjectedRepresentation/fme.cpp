#include "fme.h"

void sepSAT(inequality d, VlinkedList ext, linkedList* p, SAT* SATp, int varNum)
{
	bit_array_t** newrela = (bit_array_t**)malloc(SATp->col_bit * sizeof(bit_array_t*));
	for(int i = 0; i < SATp->col_bit; i++)
	{
		newrela[i] = BitArrayCreate(BITLONG);
		BitArrayClearAll(newrela[i]);
	}

	Vnode* current = ext.head->next;
	for(int j = 0; j < ext.number; j++)
	{
		if(satis(d, current->data, varNum) == 1)
		{
			BitArraySetBit(newrela[j/BITLONG], j%BITLONG);
		}
		current = current->next;
	}

	addList(p, d, varNum);
	addSAT_Data(SATp, newrela);

}

void separate(linkedList d, VlinkedList ext, linkedList* pos, linkedList* neg, linkedList* zer,
		SAT* SATpos, SAT* SATneg, SAT* SATzer, int v, int varNum)
{
	node * current = d.head->next;

	while(current != NULL)
	{
		for (int j = 0; j < current->fill; j++)
		{
			if (mpq_sgn(current->data[j].coef[v]) > 0)
				sepSAT(current->data[j], ext, pos, SATpos, varNum);
			else if (mpq_sgn(current->data[j].coef[v]) < 0)
				sepSAT(current->data[j], ext, neg, SATneg, varNum);
			else
				sepSAT(current->data[j], ext, zer, SATzer, varNum);
		}
		current = current->next;
	}
}

void Projvertex(VlinkedList * newext, int * extproj, VlinkedList ext, int v, int varNum)
{
	Vnode * current = ext.head->next;
	Vnode * newc = newext->head;

	int flag = 1;

	int i = 0;
	mpq_init(current->data.coef[v]);
	for(int j = 0; j < v; j++)
	{
		if(mpq_sgn(current->data.coef[j]) != 0)
		{
			flag = 0;
			break;
		}
	}

	if(flag == 0)
	{
		Vnode * p = makeVNode(varNum);
		p->data = current->data;
		p->next = NULL;
		newc->next = p;
		newc = newc->next;
		newext->number++;
		extproj[0] = 0;
		current = current->next;
		i++;
	}
	else
	{
		extproj[0] = -1;
		i++;
		current = current->next;
		mpq_init(current->data.coef[v]);

		Vnode * p = makeVNode(varNum);
		p->data = current->data;
		p->next = NULL;
		newc->next = p;
		newc = newc->next;
		extproj[1] = 0;
		newext->number++;
		current = current->next;
		i++;
	}

	while(current != NULL)
	{
		mpq_init(current->data.coef[v]);
		if(Same(current->data, newc->data, varNum) == 0)
		{
			Vnode * p = makeVNode(varNum);
			p->data = current->data;
			p->next = NULL;
			newc->next = p;
			newc = newc->next;
			extproj[i] = newext->number;
			newext->number++;
		}
		else
		{
			extproj[i] = newext->number-1;

		}
		current = current->next;
		i++;

	}

}

void MCSeqn(inequality equation, linkedList pos, linkedList neg, linkedList zer, linkedList* eqn, 
		SAT SATpos, SAT SATneg, SAT SATzer, int* extproj, int elimv, int varNum, 
		linkedList* Newpos, linkedList* Newneg, linkedList* Newzer,
		SAT* NewSATpos, SAT* NewSATneg, SAT* NewSATzer)
{
	linkedList Neweqn = makeList(varNum);

	inequality newdata; 
	makeNewInequality(&newdata, varNum);
	bit_array_t** newrela = (bit_array_t**)malloc(NewSATpos->col_bit * sizeof(bit_array_t*));
	for(int i = 0; i < NewSATpos->col_bit; i++)
	{
		newrela[i] = BitArrayCreate(BITLONG);
		BitArrayClearAll(newrela[i]);
	}

	int countbit = 0;
	node* current = pos.head->next;
	satnode* currentSAT = SATpos.head->next;
	while(current != NULL)
	{
		for(int i = 0; i < current->fill; i++)
		{
			Elimequation(&newdata, current->data[i], equation, elimv, varNum);
			if(IsZero(newdata, varNum) == 1)
				continue;
			for(int j = 0; j < NewSATpos->col_bit; j++)
			{
				BitArrayClearAll(newrela[j]);
			}
			for(int j = 0; j < SATpos.cols; j++)
			{
				if(extproj[j] >= 0)
				{
			        	if(BitArrayTestBit(currentSAT->SATcol[j], countbit) != 0)
			        	{
			        		BitArraySetBit( newrela[ extproj[j]/BITLONG], extproj[j]%BITLONG);
			        	}
				}
			}
			if(mpq_sgn(newdata.coef[elimv - 1]) > 0)
			{
				addList(Newpos, newdata, varNum);
				addSAT_Data(NewSATpos, newrela);
			}
			else if(mpq_sgn(newdata.coef[elimv-1]) < 0)
			{
				addList(Newneg, newdata, varNum);
				addSAT_Data(NewSATneg, newrela);
			}
			else
			{
				addList(Newzer, newdata, varNum);
				addSAT_Data(NewSATzer, newrela);
			}
			countbit++;
			if(countbit == BITLONG)
			{
				currentSAT = currentSAT->next;
				countbit = 0;
			}
		}
		current = current->next;
	}

	countbit = 0;
	current = neg.head->next;
	currentSAT = SATneg.head->next;
	while(current != NULL)
	{
		for(int i = 0; i < current->fill; i++)
		{
			Elimequation(&newdata, current->data[i], equation, elimv, varNum);
			if(IsZero(newdata, varNum) == 1)
				continue;
			for(int j = 0; j < NewSATpos->col_bit; j++)
			{
				BitArrayClearAll(newrela[j]);
			}
			for(int j = 0; j < SATpos.cols; j++)
			{
				if(extproj[j] >= 0)
				{
			        	if(BitArrayTestBit(currentSAT->SATcol[j], countbit) != 0)
			        	{
			        		BitArraySetBit( newrela[ extproj[j]/BITLONG], extproj[j]%BITLONG);
			        	}
				}
			}
			if(mpq_sgn(newdata.coef[elimv - 1]) > 0)
			{
				addList(Newpos, newdata, varNum);
				addSAT_Data(NewSATpos, newrela);
			}
			else if(mpq_sgn(newdata.coef[elimv-1]) < 0)
			{
				addList(Newneg, newdata, varNum);
				addSAT_Data(NewSATneg, newrela);
			}
			else
			{
				addList(Newzer, newdata, varNum);
				addSAT_Data(NewSATzer, newrela);
			}
			countbit++;
			if(countbit == BITLONG)
			{
				currentSAT = currentSAT->next;
				countbit = 0;
			}
		}
		current = current->next;
	}

	countbit = 0;
	current = zer.head->next;
	currentSAT = SATzer.head->next;
	while(current != NULL)
	{
		for(int i = 0; i < current->fill; i++)
		{
			for(int j = 0; j < NewSATpos->col_bit; j++)
			{
				BitArrayClearAll(newrela[j]);
			}
			for(int j = 0; j < SATpos.cols; j++)
			{
				if(extproj[j] >= 0)
				{
			        	if(BitArrayTestBit(currentSAT->SATcol[j], countbit) != 0)
			        	{
			        		BitArraySetBit( newrela[ extproj[j]/BITLONG], extproj[j]%BITLONG);
			        	}
				}
			}
			if(mpq_sgn(current->data[i].coef[elimv - 1]) > 0)
			{
				addList(Newpos, current->data[i], varNum);
				addSAT_Data(NewSATpos, newrela);
			}
			else if(mpq_sgn(current->data[i].coef[elimv-1]) < 0)
			{
				addList(Newneg, current->data[i], varNum);
				addSAT_Data(NewSATneg, newrela);
			}
			else
			{
				addList(Newzer, current->data[i], varNum);
				addSAT_Data(NewSATzer, newrela);
			}
			countbit++;
			if(countbit == BITLONG)
			{
				currentSAT = currentSAT->next;
				countbit = 0;
			}
		}
		current = current->next;
	}

	current = eqn->head->next;
	while(current != NULL)
	{
		for(int i = 0; i < current->fill; i++)
		{
			Elimequation(&newdata, current->data[i], equation, elimv, varNum);
			if(IsZero(newdata, varNum) == 1)
				continue;	
			addList(&Neweqn, newdata, varNum);
			
		}
		current = current->next;
	}

	freeList(eqn, varNum);
	eqn->number = Neweqn.number;
	eqn->head->next = Neweqn.head->next;
}

void RemoveRedExt(SAT* saturation, VlinkedList* ext, int* flag, int redcount, int elimv, int varNum)
{
	Vnode* currentV = ext->head->next;
	int* extflag = (int*)malloc(ext->number * sizeof(int));
	for(int i = 0; i < ext->number; i++)
	{
		extflag[i] = 1;
		currentV = currentV->next;
	}
	for(int i = 0; i < saturation->cols; i++)
	{
		if(saturation->countcol[i] < elimv - 1 )
		{
			extflag[i] = -1;
		}
		else if(saturation->countcol[i] == saturation->rows - redcount)
		{
			extflag[i] = 0;
		}
	}

	bit_array_t** intersect = (bit_array_t**)malloc(saturation->col_bit * sizeof(bit_array_t*));
	for(int j = 0; j < saturation->col_bit; j++)
	{
		intersect[j] = BitArrayCreate(BITLONG);
	}
	satnode* currentsat = saturation->head->next;
	for(int i = 0; i < saturation->cols; i++)
	{
		if(extflag[i] > 0)
		{
			for(int j = 0; j < saturation->col_bit; j++)
			{
				BitArraySetAll(intersect[j]);
			}
			for(int j = saturation->cols; j < saturation->col_bit * BITLONG; j++)
			{
				BitArrayClearBit(intersect[j/BITLONG], j%BITLONG);
			}
			currentsat = saturation->head->next;
			while(currentsat != NULL)
			{
				for(int s = 0; s < currentsat->rowfill; s++)
				{
					if(BitArrayTestBit(currentsat->SATcol[i], s) != 0)
					{
						for(int j = 0; j < saturation->col_bit; j++)
						{
							BitArrayAnd(intersect[j], intersect[j], 
									currentsat->SATrow[s][j]);
						}
					}
				}
				currentsat = currentsat->next;
			}
			for(int j = 0; j < saturation->cols; j++)
			{
				if(extflag[j] <= 0 || j == i )
				{
					BitArrayClearBit(intersect[j/BITLONG], j%BITLONG);
				}
			}
			for(int j = 0; j < saturation->col_bit; j++)
			{
				if(IsZeroBit(intersect[j]) != 1)
				{
					extflag[j] = -1;
				}
			}
		}
	}
//	for(int i = 0; i < ext->number; i++)
//	{
//		printf(" %d", extflag[i]);
//	}
//	printf("\n");

	VlinkedList Newext = makeVList(varNum);
	Vnode* currentext = ext->head->next;
	for(int i = 0; i < ext->number; i++)
	{
		if(extflag[i] >= 0)
			addVList(&Newext, currentext->data, varNum);
		currentext = currentext->next;
	}
	freeVList(ext, varNum);
	ext->number = Newext.number;
	ext->head->next = Newext.head->next;

	SAT NewSAT = makeSAT(Newext.number);
	bit_array_t** newrela = (bit_array_t**)malloc(NewSAT.col_bit * sizeof(bit_array_t*));
	for(int i = 0; i < NewSAT.col_bit; i++)
	{
		newrela[i] = BitArrayCreate(BITLONG);
		BitArrayClearAll(newrela[i]);
	}

	satnode* currentSAT = saturation->head->next;
	while(currentSAT != NULL)
	{
		for(int i = 0; i < currentSAT->rowfill; i++)
		{
			int newextnum = 0;
			for(int s = 0; s < NewSAT.col_bit; s++)
			{
				BitArrayClearAll(newrela[s]);
			}
			for(int j = 0; j < saturation->cols; j++)
			{
				if(extflag[j] >= 0)
				{
					if(BitArrayTestBit(currentSAT->SATcol[j], i) != 0)
						BitArraySetBit(newrela[newextnum/BITLONG],newextnum%BITLONG);
					newextnum++;
				}
			}
			addSAT_Data(&NewSAT, newrela);
		}
		currentSAT = currentSAT->next;
	}

	freeSAT(saturation);
	saturation->rows = NewSAT.rows;
	saturation->row_bit = NewSAT.row_bit;
	saturation->cols = NewSAT.cols;
	saturation->col_bit = NewSAT.col_bit;
	saturation->countcol = NewSAT.countcol;
	saturation->head->next = NewSAT.head->next;
}

void MCSnoeqn(linkedList pos, linkedList neg, linkedList zer, SAT SATpos, SAT SATneg, SAT SATzer, VlinkedList* Newext,
	       	int* extproj, int elimv, int varNum, linkedList* Newpos, linkedList* Newneg, linkedList* Newzer, 
		SAT* NewSATpos, SAT* NewSATneg, SAT* NewSATzer)
{
	Set Newine = makeSet();
	SAT NewSAT = makeSAT(NewSATpos->cols);

	bit_array_t** newrela = (bit_array_t**)malloc(NewSATpos->col_bit * sizeof(bit_array_t*));
	for(int i = 0; i < NewSATpos->col_bit; i++)
	{
		newrela[i] = BitArrayCreate(BITLONG);
		BitArrayClearAll(newrela[i]);
	}

	bit_array_t** intersect = (bit_array_t**)malloc(SATpos.col_bit * sizeof(bit_array_t*));
	for(int i = 0; i < SATpos.col_bit; i++)
	{
		intersect[i] = BitArrayCreate(BITLONG);
		BitArrayClearAll(intersect[i]);
	}

	int countpos = 0;
	int countneg = 0;
	satnode* relapos = SATpos.head->next;
	satnode* relaneg = SATneg.head->next;
	while(relapos != NULL)
	{
		for(int i = 0; i < relapos->rowfill; i++)
		{
			int countsupport = 0;
			countneg = 0;
			relaneg = SATneg.head->next;
			while(relaneg != NULL)
			{
				for(int j = 0; j < relaneg->rowfill; j++)
				{
					for(int s = 0; s < NewSATpos->col_bit; s++)
						BitArrayClearAll(newrela[s]);
					for(int s = 0; s < SATpos.col_bit; s++)
					{
						BitArrayAnd(intersect[s], relapos->SATrow[i][s], relaneg->SATrow[j][s]);
					}

					for(int s = 0; s < SATpos.cols; s++)
					{
						if(extproj[s] >= 0)
						{
							if(BitArrayTestBit(intersect[s/BITLONG],s%BITLONG) != 0)
							{
								countsupport++;
								BitArraySetBit(newrela[extproj[s]/BITLONG],extproj[s]%BITLONG);
							}
						}
					}

					if(countsupport >= elimv - 1)
					{
						int newdata[2];
						newdata[0] = countpos;
						newdata[1] = countneg;
						addSet(&Newine, newdata, 2);
						addSAT_Data(&NewSAT, newrela);

					}
					countneg++;
				}
				relaneg = relaneg->next;
			}
			countpos++;
		}
		relapos = relapos->next;
	}

	int countzer = 0;
	satnode* relazer = SATzer.head->next;
	while(relazer != NULL)
	{
		for(int i = 0; i < relazer->rowfill; i++)
		{
			int countsupport = 0;
			for(int s = 0; s < NewSATpos->col_bit; s++)
				BitArrayClearAll(newrela[s]);
			for(int s = 0; s < SATpos.cols; s++)
			{
				if(extproj[s] >= 0)
				{
					if(BitArrayTestBit(relazer->SATcol[s], i) != 0)
					{
						BitArraySetBit(newrela[extproj[s]/BITLONG],extproj[s]%BITLONG);
						countsupport++;
					}
				}
			}

			if(countsupport >= elimv - 1)
			{
				int newdata[1];
				newdata[0] = countzer;
	              		addSet(&Newine, newdata, 1);
				addSAT_Data(&NewSAT, newrela);
			}
			countzer++;
		}
		relazer = relazer->next;
	}
//	displaySet(Newine);
//	printSAT(NewSAT);

	int Newflag[Newine.number];
	for(int i = 0; i < Newine.number; i++)
	{
		Newflag[i] = 1;
	}
	int setnum = 0;
	int redcount = 0;
	satnode* currentSAT = NewSAT.head->next;
	while(currentSAT != NULL)
	{
		for(int i = 0; i < currentSAT->rowfill; i++)
		{
			//printf("%d:\n", setnum);
			Set support = makeSet();
			for(int j = 0; j < NewSAT.cols; j++)
			{
				if(BitArrayTestBit(currentSAT->SATcol[j], i) != 0)
				{
					int data[1];
					data[0] = j;
					addSet(&support , data, 1);
				}
			}
			//displaySet(support);
			satnode* currentInter = NewSAT.head->next;
			while(currentInter != NULL)
			{
				bit_array_t* interRela = BitArrayCreate(BITLONG);
				BitArraySetAll(interRela);
				setnode* currentsupport = support.head->next;
				while(currentsupport != NULL)
				{
					BitArrayAnd(interRela, interRela, currentInter->SATcol[currentsupport->data[0]]);
					currentsupport = currentsupport->next;
				}
				if(currentInter == currentSAT)
				{
					BitArrayClearBit(interRela, i);
				}
				if(IsZeroBit(interRela) != 1)
				{
					Newflag[setnum] = -1;
					redcount++;
					for(int k = 0; k < NewSAT.cols; k++)
					{
						BitArrayClearBit(currentSAT->SATrow[i][k/BITLONG], k%BITLONG);
						BitArrayClearBit(currentSAT->SATcol[k], i);
					}
					break;
				}
				currentInter = currentInter->next;
			}
			setnum++;
		}
		currentSAT = currentSAT->next;
	}
//	for(int i = 0; i < Newine.number; i++)
//	{
//		printf("%d ",Newflag[i]);
//	}
//	printf("\n");

//	if(redcount != NewSAT.rows)
//	{
//		RemoveRedExt(&NewSAT, Newext, Newflag, redcount, elimv, varNum);
//		NewSATpos->cols = Newext->number;
//		NewSATpos->col_bit = BITNUM(Newext->number);
//		NewSATneg->cols = Newext->number;
//		NewSATneg->col_bit = BITNUM(Newext->number);
//		NewSATzer->cols = Newext->number;
//		NewSATzer->col_bit = BITNUM(Newext->number);
//	}

	bit_array_t** uprela = (bit_array_t**)malloc(NewSAT.col_bit * sizeof(bit_array_t*));
	for(int j = 0; j < NewSAT.col_bit; j++)
	{
		uprela[j] = BitArrayCreate(BITLONG);
		BitArrayClearAll(uprela[j]);
	}
	inequality newdata;
	makeNewInequality(&newdata, varNum);
	setnum = 0;
	currentSAT = NewSAT.head->next;
	setnode* temp = Newine.head->next;
	node* currentpos = pos.head->next;
	node* currentneg = neg.head->next;
	node* currentzer = zer.head->next;
	while(currentSAT != NULL)
	{
		for(int i = 0; i < currentSAT->rowfill; i++)
		{
			if(Newflag[setnum] >= 0)
			{
				for(int j = 0; j < NewSAT.col_bit; j++)
					BitArrayCopy(uprela[j], currentSAT->SATrow[i][j]);
				if(temp->size == 2)
				{
					currentpos = pos.head->next;
					currentneg = neg.head->next;
					for(int s = 0; s < temp->data[0]/8; s++)
						currentpos = currentpos->next;
					for(int s = 0; s < temp->data[1]/8; s++)
						currentneg = currentneg->next;
					combine(currentpos->data[temp->data[0]%8], currentneg->data[temp->data[1]%8],
							&newdata, elimv, varNum);
				}
				else
				{
					currentzer = zer.head->next;
					for(int s = 0; s < temp->data[0]/8; s++)
						currentzer = currentzer->next;
					copyIneq(currentzer->data[temp->data[0]%8], &newdata, varNum);
				}
				if(mpq_sgn(newdata.coef[elimv - 1]) > 0)
				{
					addList(Newpos, newdata, varNum);
					addSAT_Data(NewSATpos, uprela);
				}
				else if(mpq_sgn(newdata.coef[elimv - 1]) < 0)
				{
					addList(Newneg, newdata, varNum);
					addSAT_Data(NewSATneg, uprela);
				}
				else
				{
					addList(Newzer, newdata, varNum);
					addSAT_Data(NewSATzer, uprela);
				}
			}
			setnum++;
			temp = temp->next;
		}
		currentSAT = currentSAT->next;
	}

	freeSAT(&NewSAT);
}

void MCSonestep(linkedList pos, linkedList neg, linkedList zer, linkedList* eqn, SAT SATpos, SAT SATneg, SAT SATzer, 
		VlinkedList* Newext, int* extproj, int elimv, int varNum, 
		linkedList* Newpos, linkedList* Newneg, linkedList* Newzer,
		SAT* NewSATpos, SAT* NewSATneg, SAT* NewSATzer)
{
	int Zeroeqn = 0;

	node* current = eqn->head->next;

	while(current != NULL)
	{
		for(int i = 0; i < current->fill; i++)
		{
			if(mpq_sgn(current->data[i].coef[elimv]) != 0)
			{
				MCSeqn(current->data[i], pos, neg, zer, eqn, SATpos, SATneg, SATzer, 
						extproj, elimv, varNum, Newpos, Newneg, Newzer,
						NewSATpos, NewSATneg, NewSATzer);
				Zeroeqn = 1;
				break;
			}
		}
		current = current->next;
	}

	if(Zeroeqn == 0)
	{
		MCSnoeqn(pos, neg, zer, SATpos, SATneg, SATzer, Newext, extproj, elimv, varNum, 
				Newpos, Newneg, Newzer, NewSATpos, NewSATneg, NewSATzer);
	}

}


/**
 * combine function
 */
//result should be allocated before
void combine(inequality a, inequality b, inequality * result, int v, int varNum)
{
	int i;
	int k = 0;

//	makeNewInequality(result, varNum, ineqNum); //// <<< ....

	mpq_t av, bv;
	mpq_t temp1, temp2, temp3, temp4;

	mpq_init(av);
	mpq_init(bv);

	mpq_init(temp1);
	mpq_init(temp2);
	mpq_init(temp3);
	mpq_init(temp4);

	mpq_set(av, a.coef[v]);
	mpq_set(bv, b.coef[v]);

	mpq_abs(temp3, b.coef[v]);
	mpq_abs(temp4, a.coef[v]);

	for (i = 0; i < varNum; i++)
	{
		mpq_mul(temp1, a.coef[i], temp3);
		mpq_mul(temp2, b.coef[i], temp4);
		mpq_add(result->coef[i], temp1, temp2);
	}
/////////////////////////////////////

	int nonZ = 0;
	for (i = 0; i < varNum; i++)
		if (mpq_sgn(result->coef[i]) != 0)
			nonZ++;

	mpq_t * tmp = (mpq_t *) malloc(nonZ * sizeof(mpq_t));
	for (i = 0; i < nonZ; i++)
		mpq_init(tmp[i]);

	int t = 0;
	for (i = 0; i < varNum; i++)
		if (mpq_sgn(result->coef[i]) != 0)
			mpq_set(tmp[t++], result->coef[i]);


	inequality * newIneq = (inequality *) malloc (sizeof(inequality));
//	makeNewInequality(newIneq, varNum, ineqNum);

	mpz_t gcd;
	mpz_init(gcd);
	mpz_t lcm;
	mpz_init(lcm);
	mpz_t num1, num2;
	mpz_init(num1);
	mpz_init(num2);

	mpq_get_num(num1, tmp[0]);
	mpz_set(gcd, num1);

	mpq_get_den(num2, tmp[0]);
	mpz_set(lcm, num2);

	for (i = 0; i < nonZ; i++)
	{
		mpq_get_num(num1, tmp[i]);
		mpz_gcd(gcd, gcd, num1);

		mpq_get_den(num2, tmp[i]);
		mpz_lcm(lcm, lcm, num2);
	}

	mpz_abs(gcd, gcd);
	mpz_abs(lcm, lcm);

	mpq_t gcdq;
	mpq_init(gcdq);
	mpq_set_z(gcdq,gcd);

	mpq_t lcmq;
	mpq_init(lcmq);
	mpq_set_z(lcmq,lcm);

	if (mpz_sgn(gcd) != 0)
	{
		for (i = 0; i < varNum; i++)
		{
			mpq_t pt;
			mpq_init(pt);
			mpq_set(pt, result->coef[i]);
			mpq_mul(pt,pt,lcmq);
			mpq_div(pt,pt,gcdq);
			mpq_set(result->coef[i], pt);
			mpq_clear(pt);
		}

	}
	for(int uu = 0 ; uu < nonZ ; uu++)
		mpq_clear(tmp[uu]);
	free(tmp);

	mpq_clear(temp1);
	mpq_clear(temp2);
	mpq_clear(temp3);
	mpq_clear(temp4);
	mpq_clear(av);
	mpq_clear(bv);

	mpz_clear(gcd);
	mpz_clear(lcm);
	mpz_clear(num1);
	mpz_clear(num2);

	mpq_clear(gcdq);
	mpq_clear(lcmq);
}


