#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOWER 1
#define UPPER 50000
#define MINSIZE 1
#define MAXSIZE 10000

int *stack_bottom ;
int *stack_top ;

int random_gen (int lower , int upper)
{
	int randno = (rand() % (upper - lower + 1)) + lower ;

	return randno ;
}

int * allocate_array_randomdist (int low , int high)
{
	int i ;
	int *A ;

	A = (int *) malloc((high - low + 1) * sizeof(int)) ;
	
	srand(time(0)) ;
	
	for (i = low ; i <= high ; i++)
	{
		A[i] = random_gen (LOWER , UPPER) ;
		//A[i] = high - i ;
	}

	//A[high] = 0 ;

	return A ;
}

int *allocate_array_repeatdist (int low , int high)
{
	int i ;
	int *A ;

	A = (int *) malloc ((high - low + 1) * sizeof (int)) ;
	srand (time(0)) ;
	
	for (i = low ; i <= high ; i++)
	{	
		int up = (high - low + 1)/100 ;
		if (up == 0)
			up = 1 ;

		A[i] = random_gen (1 , up) ;
	}

	return A ;
}

int *allocate_array_allrep (int low , int high)
{
	int i ;
	int *A ;
	
	A = (int *) malloc ((high - low + 1) * sizeof (int)) ;
	
	for (i = low ; i <= high ; i++)
		A[i] = 44 ;
}

int *allocate_array_sorted (int low , int high)
{
	int val = 1 ;

	int *A ;
	A = (int *) malloc ((high - low + 1) * sizeof (int)) ;

	for (int i = low ; i <= high ; i++)
	{	A[i] = val ;
		val++ ;
	}

	return A ;
}

int *allocate_array_reverse (int low , int high)
{
	int val = high+1 ;

	int *A ;
	A = (int *) malloc ((high - low + 1) * sizeof (int)) ;

	for (int i = low ; i <= high ; i++)
	{
		A[i] = val ;
		val-- ;	
	}

	return A ;
}

void enter ()
{
	char ch ;
	printf ("Press enter to continue\n") ;
	scanf ("%c" , &ch) ;
}

void display_array (int *A , int low , int high)
{
	for ( ; low <= high ; low++)
		printf ("%d\n" , A[low]) ;

	printf("\n") ;
}

void insert (int *A , int low , int high)
{
	//This assumes that the array A[low ... high-1] is sorted
	int key , index ;

	key = A[high] ;
	index = high - 1 ;
	int cnt = 1 ;

	while (index >= low && A[index] > key)		//short hand to avoid segementation fault by A[-1]
	{
		//printf ("count = %d key = %d and index = %d , A[index] = %d" , cnt++ , key , index, A[index]) ;
		A[index+1] = A[index] ;
		//printf (" P1") ;
		index-- ;		
		//printf (" P2\n") ;
	} 

	A[index+1] = key ;
	//printf ("AT THE INSERTION STATEMENT!\n") ;
}

void insertion_sort (int *A , int low, int high)
{
	
	/*
	--------------------------------------------------------------------
	Base case
	--------------------------------------------------------------------
	*/

	if (low == high)
	{	
		//printf ("WILL COME HERE FOR EVERY SIZE!\n") ;
		stack_top = &low ;
		return ;
	}


	/*
	--------------------------------------------------------------------
	General case
	--------------------------------------------------------------------
	*/
	
	insertion_sort (A , low , high - 1) ;	//sort the array preceding the last element

	//printf ("Before inserting index %d\n" , high) ;
	//display_array (A , low ,high) ;
	//enter () ;

	insert (A , low , high) ;		//insert the last element at the correct position

	//printf ("After inserting index %d\n" , high) ;
	//display_array (A , low , high) ;
	//enter () ;
	
}


int main ()
{
	int dummy , count = 0 ;
	int *A , *stacksize ;
	double *ins_time ;

	struct timeval t1, t2 ;
	double elapsedTime ;
	FILE *f ;
	
	//srand(time(0)) ;

	stack_bottom = &dummy ;
	stacksize = (int *) malloc (sizeof(int) * (MAXSIZE - MINSIZE + 1)) ;
	ins_time  = (double *) malloc (sizeof(double) * (MAXSIZE - MINSIZE + 1)) ;
	for (int i = MINSIZE ; i <= MAXSIZE ; i++)
	{
		A = allocate_array_reverse (0 , i-1) ;

		printf ("%d\n" , i) ;
		//printf ("Before sorting\n") ; 
		//display_array (A , 0 , i-1) ;	
		//enter () ;	

		gettimeofday (&t1, NULL) ;
		insertion_sort (A, 0 , i-1) ;
		gettimeofday (&t2 , NULL) ;
		//printf ("EXIT INSERTION SORT!\n") ;

		elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0 ;
		elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0 ;
		
		ins_time[i - MINSIZE] = elapsedTime ;
		stacksize[i - MINSIZE] = (stack_bottom - stack_top)/2 ;
		//printf ("THERE IS NO PROBLEM IN STORING STACKSIZE!\n") ;

		//printf ("After sorting\n") ; 		
		//display_array (A , 0 , i-1) ;
		//printf("Stack size used = %d\n" , (stack_bottom - stack_top)/2) ;
		//printf("\n") ;
		//enter () ;

		free(A) ;
		count++ ;
	}

	f = fopen ("reverse.txt" , "w") ;
	fprintf (f , "Size\t\tTime\t\tStack Size\n") ;

	for (int i = 0 ; i < MAXSIZE - MINSIZE + 1 ; i++)
		fprintf (f , "%d\t\t%f\t\t%d\n" , (MINSIZE + i) , ins_time[i] , stacksize[i]) ;


	fclose (f) ;

	return 0 ;
}
