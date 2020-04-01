#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void funca()
{
	int *arr1 = (int *) myalloc (10 * sizeof(int)) ;	
	print_heap ();

	int *arr2 = (int *) myalloc (5 * sizeof(int)) ;
	print_heap ();

	char *str = myalloc (100 * sizeof(char)) ;
	print_heap ();

	myfree(str) ;
	print_heap() ;
}



void enter ()
{
	char ch ;
	printf ("Press enter to continue") ;
	scanf ("%c" , ch) ;
}

int random_gen (int lower , int upper)
{
	int num = (rand() % (upper - lower + 1)) + lower ;

	return num ;
}

void funcb ()
{
	int randno ;
	int *ptr ;
	srand (time(0)) ;

	for (int i = 1 ; i <= 100; i++)
	{	
		printf ("\nIteration %d - \n" , i) ;
		randno = random_gen (10000 , 40000) ;
		ptr = (int *) myalloc (randno * sizeof(int)) ;
		if (ptr == NULL)
		{
			enter () ;
		}
		printf ("Random number = %d\n" , randno) ;
		printf ("Starting address = %d , Ending address = %d \n" , ptr , &(ptr[randno-1])) ;
		myfree (ptr) ;
	}
}

int main ()
{
	//funca () ;
	funcb () ;

	
	return 0 ;
}
