#include <stdio.h>
#include "lsdata.h"

int testCyclic (struct List* Ls)
{
	//printf ("This is the first function to test cyclic\n") ;
	if (Ls->size == 0 || Ls->size == 1 || Ls->size == 2)
		return 0 ;
	else
	{
		
		//int cyc = 0 ;

		struct Number *hare, *tort ;
		tort = Ls->head ;
		hare = tort->next->next ;
		//enter () ;


		//printf ("Tort\tHare\n") ;
		while (!(hare->next == tort || tort == hare))
		{
			if (hare->next == NULL || hare->next->next == NULL)
				return 0 ;

			//printf("%d\t%d\n" , tort->x , hare->x) ;
			//enter () ;

			tort = tort->next ;
			hare = hare->next->next ;
		} 

	}
	
	return 1 ;
}
