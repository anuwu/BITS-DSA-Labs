#include <stdio.h>
#include "lsdata.h"

struct List* duplicateList (struct List * Ls)
{
	struct List *dup ;
	struct Number *lsptr , *dupptr , *dupprev, *dupend ;

	dup = (struct List *) myalloc (sizeof(struct List)) ;
	dup->size = Ls->size ;
	dup->head = (struct Number *) myalloc (sizeof(struct Number)) ;

	dupptr = dup->head ;
	lsptr = Ls->head ;
	dupptr->x = lsptr->x ;

	dupprev = dupptr ;
	lsptr = lsptr->next ;
	for (int i = 2 ; i <= Ls->size ; i++)
	{
		dupptr = (struct Number *) myalloc (sizeof(struct Number)) ;
		dupptr->next = NULL ;
		dupprev->next = dupptr ;
		dupptr->x = lsptr->x ;
		dupprev = dupptr ;
		lsptr = lsptr->next ;
	}

	dupend = NULL ;

	if (lsptr != NULL)
	{

		dupend = dup->head ;
		while (dupend->x != lsptr->x)
			dupend = dupend->next ;
	}

	dupprev->next = dupend ;


	return dup ;
}

void debug_testCyclic (struct List* Ls)
{
	struct List* dup ;
	printf ("This is the second function to test cyclic\n") ;

	printf("Heap space before duplication\n") ;
	print_heap () ;
	dup = duplicateList (Ls) ;
	printf ("Displaying duplicated list\n") ;
	displayList(*dup) ;
	printf("Heap space after duplication\n") ;
	print_heap () ;
	deleteListPointer (dup) ;
	printf("Heap space after deletion\n") ;
	print_heap () ;
}

int check_sublist (struct Number* ptr , struct Number *test)
{
	while (ptr != NULL)
	{
		if (ptr == test)
			return 1 ;
		ptr = ptr->next ;
	}

	return 0 ;
}

int reverse (struct List* Ls)
{
	if (Ls->size == 0 || Ls->size == 1)
		return 0 ;
	else
	{
		struct Number *p1, *p2 , *p3 ;
		p1 = NULL ;
		p2 = Ls->head ;
		p3 = p2->next ;

		int i = 0, check = 0 ;
	
		while (p3 != NULL)
		{	

			p2->next = p1 ;
			p1 = p2 ;
			p2 = p3 ;
			p3 = p3->next ;

			check = check_sublist(p1 , p3) ;
			if (p1->next == p3 && p2->next == p3 && p1 == p2)
			{
				//printf ("IT IS HERE\n") ;
				//enter () ;
				Ls->head = p2 ;
				return 1 ;
			}
			if (check == 1)
			{
				p2->next = p1 ;
				Ls->head = p2 ;
				return 1 ;
			}
			i++ ; 
		}		
		p2->next = p1 ;
		Ls->head = p2 ;
	}

	return 0 ;
}


int testCyclic (struct List* Ls)
{
	if (Ls->size == 1)
		return 1 ;

	struct List* dup ;
	dup = duplicateList (Ls) ;	//O(n)
	
	if (reverse(dup) == 0)		//O(n^2)
	{
		//print_heap () ;
		deleteListPointer(dup) ;	//O(n)
		return 0 ;
	}

	//print_heap () ;
	deleteListPointer (dup) ;	//O(n)
	return 1 ;
}
