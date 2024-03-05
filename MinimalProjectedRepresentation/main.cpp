//varNum in this program conclude the constant number 1.

#ifdef _cplusplus
extern "C"
#endif

#include <iostream>
#include <fstream>
#include <time.h>
#include "inequality.h"
#include "unrolledll.h"
#include "projection.h"

using namespace std;

/***************************************/
int main(int argc,char* argv[])
{
	clock_t start_t, end_t;
	double total_t;

	start_t = clock();

	project();

	end_t = clock();
	total_t = difftime(end_t,start_t)/CLOCKS_PER_SEC;

	cout << " total time: " << total_t << endl;;

	FILE* outfile = fopen("time.txt","a");
	fprintf(outfile, "\nMCS time: %f", total_t);


	return 0;
}
