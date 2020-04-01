#include <stdio.h>
#include "lsdata.h"
#include "testcycle.h"

struct Number* is_cycstart (struct List* Ls , struct Number *start)
{
	struct Number *ptr ;
	ptr = start->next ;

	for (int i = 1 ; i <= Ls->size ; i++)
	{
		if (ptr == start)
			return ptr ;

		ptr = ptr->next ;
	}
	
	return NULL ;
}

void deleteupto (struct List * Ls, struct Number* cycstart)
{
	struct Number *ptr , *nextnum ;
	ptr = Ls->head ;
	
	int i = 0 ;

	while (ptr != cycstart)
	{
		nextnum = ptr->next ;
		//printf ("REACHED HERE. Deleting element %d\n" , ptr->x) ;
		//enter () ;
		myfree (ptr) ;
		ptr = nextnum ;
		i++ ;
	}

	Ls->head = cycstart ;
	Ls->size -= i ;
}

void makeCircularList(struct List* Ls)
{
	if (!testCyclic(Ls))	//O(n) for testcycle1 and O(n^2) for testcycle2
	{
		struct Number *end ;
		end = Ls->head ;
		while (end->next != NULL)
			end = end->next ;

		end->next = Ls->head ;
	}
	else
	{
		//printf ("REACHED HERE\n") ;
		//enter () ;

		struct Number *ptr , *cycstart ;
		ptr = Ls->head ;

		while (ptr != NULL)
		{
			cycstart = is_cycstart (Ls , ptr) ;	//O(n^2)

			if (cycstart != NULL)
			{
				//printf ("Start of cycle = %d" , cycstart->x) ;

				if (cycstart == Ls->head)
					return ;
				else
					deleteupto (Ls , cycstart) ;

				return ;
			}

			ptr = ptr->next ;
		}
	}
}
