#include <stdio.h>
#include <stdlib.h>
#include "linkmem.h"

char* myalloc (int size)
{
	int *sz ;
	char *ptr ;
	ptr =  malloc (size + 4) ;

	if (ptr == NULL)
		return ptr ;
	
	sz = (int *) ptr ;
	*sz = size ;
	ptr += 4 ;

	heap += (size + 4) ;

	return ptr ;
}

void myfree (char *ptr)
{
	int *sz ;

	ptr -= 4 ;
	sz = (int *) (ptr) ;
	heap -= (*sz + 4) ;
	free (ptr) ;	
}

/*

char* myalloc_simple (int size)
{
	char *ptr ;
	ptr =  malloc (size) ;

	if (ptr == NULL)
		return ptr ;

	heap += size ;

	return ptr ;
}

void myfree2 (char *ptr , int size)
{
	heap -= size ;
	free (ptr) ;	
}

*/


void print_heap()
{
	printf ("The memory used in the heap = %d bytes\n", heap) ;
}

int ret_heap ()
{
	return heap ;
}
