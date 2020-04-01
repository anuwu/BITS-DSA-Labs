#include <stdio.h>
#include "lsdata.h"

struct Number* search (struct List *Ls , int num)
{
	if (Ls->size == 0)
		return NULL ;
	else
	{
		struct Number *ptr ;
		ptr = Ls->head ;

		while (ptr != NULL)
		{
			if (ptr->x == num)
				return ptr ;
			ptr = ptr->next ;
		}

		return ptr ;
	}
}

int decide ()
{
	int rand = random_gen (1 , 100) ;
	if (rand >= 50)
		return 1 ;
	else
		return 0 ;
}

void createCycle (struct List *Ls)
{
	if (decide())
	{
		int randins ;
		struct Number *ptr, *end ;

		while (search(Ls , randins) == NULL)
		{
			randins = random_gen (LOWER , UPPER) ;
			ptr = search(Ls , randins) ;
		} while (ptr == NULL) ;


		end = Ls->head ;
		while (end->next != NULL)
			end = end->next ;

		end->next = ptr ;

		//printf ("The random number = %d\n" , randins) ;
		//enter () ;
	}
}

void debug_createCycle (struct List* Ls)
{
	printf ("Proceed to possible infinite loop?\n") ;
	enter () ;
	displayList (*Ls) ;
}
