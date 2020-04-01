#include <stdio.h>
#include "ex1data.h"
#include "hash.h"


int main ()
{
	FILE *f ;
	char **book ;
	int col , now ;
	struct best b ;

	init_prof () ;
	//print_prof () ;
	
	book = parser ("random.txt") ;
	now = ret_now ("random.txt") ;
	printf ("Number of words = %d\n" , now) ;

	//col = col_count (book , now ,  100 , 257) ;
	//printf ("The number of words = %d and collisions = %d\n" , now , col) ;

	profiling (&b , book , now) ;
	printf ("Best hashing function has ts = %d and bn = %d\n" , b.ts , b.bn) ;

	return 0 ;
}
