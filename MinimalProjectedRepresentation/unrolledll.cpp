#include "unrolledll.h"

node * makeNode(int varNum)
{
	node * newn = (node *) malloc(sizeof(node));

	for(int i = 0 ; i < UNROLLED_LL_SIZE ; i++)
		makeNewInequality(&(newn->data[i]), varNum);

	newn->fill = 0;
	newn->next = NULL;
	
	return(newn);
}

Vnode * makeVNode(int varNum)
{
	Vnode * newvn = (Vnode *)malloc(sizeof(Vnode));

	makeNewInequality(&newvn->data, varNum);

	newvn->next = NULL;

	return newvn;
}

void copyNode(node s , node * des , int varNum)
{
	des->fill = s.fill;

	des->next = s.next;

	for(int i = 0 ; i < des->fill ; i++)
		copyIneq(s.data[i] , &(des->data[i]) , varNum);
}


linkedList makeList(int varNum)
{
	linkedList newll;
	node * s = makeNode(varNum);
	newll.head = s;
	newll.head->fill = 8;
	newll.number = 0;
	return (newll);
}

VlinkedList makeVList(int varNum)
{
	VlinkedList newvll;
	Vnode * s = makeVNode(varNum);
	newvll.head = s;
	newvll.number = 0;
	return (newvll);
}

void addList(linkedList * l , inequality d , int varNum)
{

	node * current = l->head;

	while(current->next != NULL)
		current = current->next;

	if(current->fill < 8)
	{
        for(int k = 0 ; k < varNum; k++)
            mpq_set(current->data[current->fill].coef[k] , d.coef[k]);

		current->fill++;
	}
	else
	{
		current->next = makeNode(varNum);

                for(int k = 0 ; k < varNum; k++)
			mpq_set(current->next->data[0].coef[k], d.coef[k]);

		current->next->fill ++;
	}
	l->number++;
}

void addVList(VlinkedList* vl, inequality d, int varNum)
{
	Vnode * current = vl->head;
	
	while(current->next != NULL)
		current = current->next;

	current->next = makeVNode(varNum);
	for(int k = 0; k < varNum; k++)
		mpq_set(current->next->data.coef[k], d.coef[k]);

	vl->number++;
}

void sortVList(VlinkedList* vl, int varNum)
{
	VlinkedList newvl = makeVList(varNum);

	Vnode* current = vl->head->next;
	while(current != NULL)
	{
		Vnode* newc = newvl.head;
		while(newc->next != NULL)
		{
			if(Compare(newc->next->data, current->data, varNum) < 0)
			{
				newc = newc->next;
			}
			else
				break;
		}

		Vnode* newnode = makeVNode(varNum);
		newnode->data = current->data;
		newnode->next = newc->next;
		newc->next = newnode;
		newvl.number++;

		current = current->next;
	}

	vl->number = newvl.number;
	vl->head->next = newvl.head->next;

}

inequality * searchIneq(linkedList l , int no , int da , int varNum)
{
	node * current = l.head;

	for(int i = 0 ; i < no ; i++)
		current = current->next;
	
	inequality * r = (inequality *) malloc(sizeof(inequality));
	copyIneq(current->data[da] , r , varNum);
	printf("from search\n\n");
	gmp_printf("%d ",current->fill);
	
	return(r);
}

void join(linkedList pos, linkedList neg, linkedList ze, linkedList * output, int varNum, int ineqNum)
{
	node * current = pos.head->next;

	while(current != NULL)
	{
		for (int j = 0; j < current->fill; j++)
			addList(output, current->data[j], varNum);
		current = current->next;
	}

	current = neg.head->next;

	while(current != NULL)
	{
		for (int j = 0; j < current->fill; j++)
			addList(output, current->data[j], varNum);
		current = current->next;
	}

	current = ze.head->next;

	while(current != NULL)
	{
		for (int j = 0; j < current->fill; j++)
			addList(output, current->data[j], varNum);
		current = current->next;
	}

}

void freeList(linkedList * d , int varNum)
{
	node * current = d->head->next;
	node * currenth = d->head->next;

	while(current != NULL)
	{
		for(int j = 0 ; j < current->fill ; j++)
			freeIneq(&(current->data[j]) , varNum);
		currenth = current;
		current = current->next;
		free(currenth);
	}
}

void freeVList(VlinkedList * vd , int varNum)
{
	Vnode * current = vd->head->next;
	Vnode * currenth = vd->head->next;

	while(current != NULL)
	{
		currenth = current;
		current = current->next;
		free(currenth);
	}

}

//
//* check whether an inequality is in the linkedList or not
//in, 1; not in, 0;
//when mode = 1 and not in, add the inequality into the linedList
int IsInll(linkedList * l, inequality d, int varNum, int mode)
{
	int flag = 0;

	node * current = l->head->next;

	while(current != NULL)
	{
		for(int i = 0; i < current->fill; i++)
		{
			if(Same(current->data[i], d ,varNum) == 1)
			{
				flag = 1;
				return flag;
			}
		}
		current = current->next;
	}

	if(mode == 1)
	{
		if(current->fill < 8)
		{
			for(int k = 0 ; k < varNum; k++)
				mpq_set(current->data[current->fill].coef[k] , d.coef[k]);
			current->fill++;
		}
		else
		{
         		current->next = makeNode(varNum);
         
         		for(int k = 0 ; k < varNum; k++)
         			mpq_set(current->next->data[0].coef[k], d.coef[k]);
         
         		current->next->fill ++;
		}
         	l->number++;
	}


	return(flag);
}	
