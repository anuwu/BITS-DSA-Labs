#include <stdio.h>
#include <stdlib.h>
#include "mem.h"

char* myalloc (int n)
{
	int i ;
	char *ptr ;
	int *size ;

	ptr = (char*) malloc (n+4) ;

	if (ptr == NULL)
		return ptr ;

	size = (int *)ptr ;
	*size = n+4 ;		//first allocated byte stores the size of the memory
	heap += (n+4) ;

	return ptr ;
}

void myfree (char *ptr)
{
	int *size ;
	size = (int *) ptr ;
	heap -= *size ;

	free (ptr) ;	
}

void print_heap()
{
	printf ("The memory used in the heap = %d bytes\n", heap) ;
}
