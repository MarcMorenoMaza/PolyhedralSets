#include "set.h"

setnode* makesetNode(int size)
{
	setnode* newnode = (setnode*)malloc(sizeof(setnode));

	newnode->size = size;
	newnode->data = (int*)malloc(size * sizeof(int));
	newnode->next = NULL;

	return newnode;
}

Set makeSet(void)
{
	Set newSet;
	newSet.number = 0;
	newSet.head = makesetNode(1);

	return newSet;
}

void addSet(Set* s, int* data, int size)
{
	setnode* currentset = s->head;

	while(currentset->next != NULL)
	{
		currentset = currentset->next;
	}

	setnode* newnode = makesetNode(size);
	for(int i = 0; i < size; i++)
	{
		newnode->data[i] = data[i];
	}

	currentset->next = newnode;
	s->number++;
}

void removeSet(Set* s, int* data, int size)
{
	setnode* currentset = s->head;

	while(currentset->next != NULL)
	{
		if(currentset->next->size == size == 1)
		{
			if(currentset->next->data[0] == data[0])
				break;
		}
		else if(currentset->next->size == size == 2)
		{
			if(currentset->next->data[0] == data[0] && currentset->next->data[1] == data[1])
				break;
		}
		currentset = currentset->next;
	}

	setnode* currenth = currentset->next;
	currentset->next = currentset->next->next;
	free(currenth);

	s->number--;

}

//if data is in Set,return 1; if not, return 0
int IsInSet(Set s, int* data, int size)
{
	int flag = 0;
	setnode* currentset = s.head->next;

	while(currentset != NULL)
	{
		if(currentset->size == 1 && size == 1)
		{
			if(currentset->data[0] == data[0])
			{
				flag = 1;
				break;
			}
		}
		else if(currentset->size == 2 && size == 2)
		{
			if(currentset->data[0] == data[0] && currentset->data[1] == data[1])
			{
				flag = 1;
				break;
			}
		}
		currentset = currentset->next;
	}

	return flag;
}

void displaySet(Set s)
{
	printf("{ ");
	setnode* currentset = s.head->next;
	while(currentset != NULL)
	{
		if(currentset->size == 1)
		{
			printf("(%d) ", currentset->data[0]);
		}
		else if(currentset->size == 2)
		{
			printf("(%d,%d) ", currentset->data[0], currentset->data[1]);
		}
		currentset = currentset->next;
	}
	printf("}\n");
}
