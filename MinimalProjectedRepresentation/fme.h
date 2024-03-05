#include "unrolledll.h"
#include "saturation.h"
#include "set.h"

void separate(linkedList , VlinkedList , linkedList * , linkedList *, linkedList *,	       SAT* , SAT* , SAT* , int , int );


void Projvertex(VlinkedList * newext, int * extproj, VlinkedList ext, int v, int varNum);

void combine(inequality, inequality, inequality *, int, int);

void MCSonestep(linkedList pos, linkedList neg, linkedList zer, linkedList* eqn, SAT SATpos, SAT SATneg, SAT SATzer, 
		VlinkedList* Newext, int* extproj, int elimv, int varNum, 
		linkedList* Newpos, linkedList* Newneg, linkedList* Newzer,
		SAT* NewSATpos, SAT* NewSATneg, SAT* NewSATzer);
/*
void RedundantExt( VlinkedList* ext, crossList* relatpos, crossList* relatneg, crossList* relatzer );
*/
