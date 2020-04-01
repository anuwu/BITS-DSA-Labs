#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main ()
{
	printf ("1\n") ;

	/*
	for (int i = 30 ; i <= 40 ; i++)
	{
		printf ("2\n") ;
		printf ("%d\n" , i) ;
	}

	for (int i = 1 ; i <= 29 ; i++)
	{
		printf ("2\n") ;
		printf ("%d\n" , i) ;
	}

	for (int i = 41 ; i <= 100 ; i++)
	{
		printf ("2\n") ;
		printf ("%d\n" , i) ;
	}
	return 0 ;
	*/

	//1073741823
	
	FILE *f ;
	int i ;
	f = fopen ("testcase2.txt" , "w") ;
	fprintf (f , "%d\n" , 1) ;

	for (i = 1 ; i <= 10000 ; i++)
	{
		fprintf (f , "%d\n" , 5) ;
		fprintf (f , "%d\n" , rand()) ;
	}

	fclose (f) ;
}
