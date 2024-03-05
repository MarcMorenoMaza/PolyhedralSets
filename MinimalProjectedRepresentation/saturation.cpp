#include "saturation.h"

int BITNUM(int number)
{
	if(number == 0)
		return 0;
	else
		return ((number - 1)/BITLONG + 1);
}

satnode* makeSatNode(int cols, int col_bit)
{
	satnode* newSatNode = (satnode*)malloc(sizeof(satnode));
	newSatNode->SATrow = (bit_array_t***)malloc(BITLONG * sizeof(bit_array_t**));
	for(int i = 0; i < BITLONG; i++)
	{
		newSatNode->SATrow[i] = (bit_array_t**)malloc(col_bit * sizeof(bit_array_t*));
		for(int j = 0; j < col_bit; j++)
		{
			newSatNode->SATrow[i][j] = BitArrayCreate(BITLONG);
			BitArrayClearAll(newSatNode->SATrow[i][j]);
		}
	}

	newSatNode->SATcol = (bit_array_t**)malloc(cols * sizeof(bit_array_t*));
	for(int j = 0; j < cols; j++)
	{
		newSatNode->SATcol[j] = BitArrayCreate(BITLONG);
		BitArrayClearAll(newSatNode->SATcol[j]);
	}

	newSatNode->rowfill = 0;
	newSatNode->next = NULL;

	return newSatNode;
}

SAT makeSAT(int cols)
{
	SAT newSAT;
	newSAT.rows = 0;
	newSAT.row_bit = 0;
	newSAT.cols = cols;
	newSAT.col_bit = BITNUM(cols);
	newSAT.countcol = (int*)malloc(cols * sizeof(int));
	for(int i = 0; i < cols; i++)
	{
		newSAT.countcol[i] = 0;
	}

	newSAT.head = makeSatNode(newSAT.cols, newSAT.col_bit);
	newSAT.head->rowfill = BITLONG;

	return newSAT;
}

void printSAT(SAT saturation)
{
	satnode* current = saturation.head->next;
	
	int count = 0;
	while(current != NULL)
	{
		printf(" node %d:\n", count);
		for(int i = 0; i < current->rowfill; i++)
		{
			printf(" row %d: ", i);
			for(int j = 0; j < saturation.col_bit; j++)
			{
				BitArrayDump(current->SATrow[i][j],stdout);
				printf(" ");
			}
			printf("\n");
		}
		for(int j = 0; j < saturation.cols; j++)
		{
			printf("col %d: ", j);
			BitArrayDump(current->SATcol[j],stdout);
			printf("\n");
		}

		count++;
		current = current->next;
	}

}

void freeSAT(SAT* saturation)
{
	satnode * current = saturation->head->next;
	satnode * currenth = saturation->head->next;

	while(current != NULL)
	{
		for(int i = 0; i < BITLONG; i++)
		{
			for(int j = 0; j < saturation->col_bit; j++)
			{
				BitArrayDestroy(current->SATrow[i][j]);
			}
			free(current->SATrow[i]);
		}
		free(current->SATrow);

		for(int j = 0; j < saturation->cols; j++)
		{
			BitArrayDestroy(current->SATcol[j]);
		}
		free(current->SATcol);

		currenth = current;
		current = current->next;
		free(currenth);
	}
	free(saturation->countcol);

}

void addSAT_Data(SAT* saturation, bit_array_t** SATdata)
{
	satnode* current = saturation->head;
	while(current->next != NULL)
		current = current->next;

	if(current->rowfill == BITLONG)
	{
		satnode* newnode = makeSatNode(saturation->cols, saturation->col_bit);
		current->next = newnode;
		current = current->next;
		saturation->row_bit++;
	}

	for(int j = 0; j < saturation->cols; j++)
	{
		if(BitArrayTestBit(SATdata[j/BITLONG], j%BITLONG) != 0)
		{
			BitArraySetBit(current->SATrow[current->rowfill][j/BITLONG], j%BITLONG);
			BitArraySetBit(current->SATcol[j], current->rowfill);
			saturation->countcol[j]++;
		}
	}
	current->rowfill++;
	saturation->rows++;
}

bool IsZeroBit(bit_array_t* rela)
{
	bit_array_t* zero = BitArrayCreate(BITLONG);
	BitArrayClearAll(zero);

	if(BitArrayCompare(rela, zero) == 0)
		return 1;
	else
		return 0;
}
