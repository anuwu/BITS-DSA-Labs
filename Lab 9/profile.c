#include "ex1data.h"
#include "hash.h"

void init_prof ()
{
	p[0].ts = 100 ;
	p[0].bn[0] = 131 ;
	p[0].bn[1] = 239 ;
	p[0].bn[2] = 367 ;
	p[0].bn[3] = 433 ;
	p[0].bn[4] = 571 ;
	p[0].bn[5] = 829 ;

	p[1].ts = 300 ;
	p[1].bn[0] = 379 ;
	p[1].bn[1] = 433 ;
	p[1].bn[2] = 569 ;
	p[1].bn[3] = 659 ;
	p[1].bn[4] = 773 ;
	p[1].bn[5] = 911 ;

	p[2].ts = 5000 ;
	p[2].bn[0] = 5077 ;
	p[2].bn[1] = 7703 ;
	p[2].bn[2] = 9973 ;
	p[2].bn[3] = 5000011 ;
	p[2].bn[4] = 5085607 ;
	p[2].bn[5] = 5154811 ;
}

void print_prof ()
{
	int i, j ;

	for (i = 0 ; i < 3 ; i++)
	{
		printf ("Table size = %d\n" , p[i].ts) ;
		for (j = 0 ; j < 6 ; j++)
			printf ("Base number = %d\n" , p[i].bn[j]) ;

		printf ("\n") ;
	}
}

void profiling (struct best *b , char **book , int now)
{
	init_prof() ;

	int i , j , min ;
	min = now ;
	
	for (i = 0 ; i < 3 ; i++)
	{
		for (j = 0 ; j < 6 ; j++)
		{
			p[i].col[j] = col_count (book , now , p[i].ts , p[i].bn[j]) ;
			//printf ("Ts = %d , Bn = %d , col = %d\n" , p[i].ts , p[i].bn[j] , p[i].col[j]) ;
		}
	}

	for (i = 0 ; i < 3 ; i++)
	{
		for (j = 0 ; j < 6 ; j++)
		{
			if (p[i].col[j] < min)
			{
				min = p[i].col[j] ;
				b->ts = p[i].ts ;
				b->bn = p[i].bn[j] ;
			}

			//printf ("MIN = %d\n" , min) ;
		}
	}

}