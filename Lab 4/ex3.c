#include <stdio.h>
#include <sys/time.h>
#include "lsdata.h"
#include "testcycle.h"

void main_debug ()
{
	//debug_create () ;
	
	struct List *Ls ;
	Ls = createListPointer (5) ;

	displayList (*Ls) ;
	createCycle (Ls) ;
	
	print_heap () ;

	if (testCyclic(Ls))
		printf("It is cyclic!\n") ;
	else
		printf("It is not cyclic!\n") ;

	//debug_createCycle (Ls) ;

	
	makeCircularList (Ls) ;

	printf ("After circularization and possible deletion of memory\n") ;

	if (testCyclic(Ls))
		printf("It is cyclic!\n") ;
	else
		printf("It is not cyclic!\n") ; 

	print_heap () ;
	enter () ;

	deleteListPointer(Ls) ;

	print_heap () ;
}

void process (int size , FILE *f)
{
	struct timeval t1, t2;
	double elapsedTime;
	struct List *Ls ;
	int init_heap, final_heap ;


					gettimeofday(&t1, NULL);
	Ls = createListPointer (size) ;					//O(n)
					gettimeofday(&t2, NULL);
					elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
					elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
					fprintf (f, "%f\t\t" , elapsedTime) ;


					gettimeofday(&t1, NULL);
	createCycle (Ls) ;						//O(n)
					gettimeofday(&t2, NULL);
					elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
					elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
					fprintf (f, "%f\t\t" , elapsedTime) ;

					init_heap = ret_heap () ;					
					fprintf(f, "%d\t\t\t" , ret_heap()) ;		//printing heapsize

	

					gettimeofday(&t1, NULL);
	makeCircularList (Ls) ;						//O(n) for nocycle1, O(n^2) for nocycle2. O(n^2) for cycle1, O(n^2) for cycle2 even more.
					gettimeofday(&t2, NULL);
					elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
					elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
					fprintf (f, "%f\t\t\t" , elapsedTime) ;

					final_heap = ret_heap () ;
					fprintf(f, "%d\t\t\t" , ret_heap()) ;		//printing heapsize


					fprintf(f , "%d\t\t\t" , (init_heap - final_heap)) ;


					gettimeofday(&t1, NULL);
	deleteListPointer(Ls) ;					        //O(n)
					gettimeofday(&t2, NULL);
					elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
					elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
					fprintf (f, "%f" , elapsedTime) ;
}

void plot ()
{
	int i ;
	FILE *f = fopen("random2.txt", "w");
	
	fprintf (f , "Size of list\tTime for creation\tTime for randomcycle\tHeap Size before Circ\tTime for circularization\tHeap Size after Circ\tBytes Deleted\tTime for Deletion\n") ;

	for (i = 100 ; i <= 5000 ; i++)
	{
		printf ("%d\n" , i) ;
		fprintf(f, "%d\t\t" , i) ;
		process (i , f) ;
		fprintf(f, "\n") ;
	}
	//fprintf (f,"THIS IS A TEST") ;

	fclose(f) ;
}

int main ()
{
	//main_debug () ;
	//print_heap () ;

	plot () ;

	return 0 ;
}
