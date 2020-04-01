#include <stdio.h>
#include "multiq.h"
#include <stdlib.h>
#include <sys/time.h>


void debug_createMQ (struct MultiQ mq)
{
	int i ;
	
	printf ("Displaying the MQ\n") ;
	printf ("Queue\tHead\tTail\tT_Cnt\n") ;
	for (i = 0 ; i < MAX ; i++)
		printf ("%d\t%d\t%d\t%d\n" , i , mq.qarr[i].head , mq.qarr[i].tail , mq.qarr[i].t_cnt) ;
	printf ("Q_cnt = %d\n" , mq.q_cnt) ;
}

void debug_loadData (FILE *f)
{
	int i = 0 ;
	int id, pri ;
	char comma ; 
	printf ("ID\tPriority\n") ;
	while (!feof(f))
	{
		i++ ;
		fscanf (f,"%d" , &id) ;
		fscanf (f, "%c" , &comma) ;
		fscanf (f,"%d", &pri) ;
		printf ("%d\t%d\n" , id, pri) ;

		if (feof(f))
		{
			printf ("End of file %d\n" , i) ;
			enter () ;
		}
	}	
}

struct MultiQ loadData (struct MultiQ mq, FILE *f)
{
	int i ;
	int id, pri ;
	char comma ;	
	struct Task* taskptr ;

	/*	---------------------------------------------------------------------
		For some reason, the last priority accessed is 0, so to avoid it, use 
		a for loop. Segmentation fault occurs because q[-1] is being accessed.
		---------------------------------------------------------------------
	*/

	for (i = 1 ; i <= 10 ; i++) 
	{	
		taskptr = (struct Task*) malloc(sizeof(struct Task)) ;
		
		fscanf (f,"%d" , &(taskptr->id)) ;
		fscanf (f, "%c" , &comma) ;
		fscanf (f,"%d", &(taskptr->pri)) ;
		taskptr->next = NULL ;

		mq = addMQ (mq , taskptr) ;
		//enter () ;
	}

	return mq ;
}

int main ()
{
	struct MultiQ mq ;
	FILE *f = fopen("test.txt" , "r") ;

	if (f == NULL)
	{
		printf ("File has not opened\n") ;
		exit (0) ;
	}

	mq = createMQ (MAX) ;
	mq = loadData (mq , f) ;
	
	
	struct Task *t ;
	//t = nextMQ (mq) ;
	//if (t == NULL)
	//	printf ("None\n") ;
	
	struct timeval t1, t2;
	double elapsedTime;
	gettimeofday(&t1, NULL);
	mq = loadData (mq , f) ;
	gettimeofday(&t2, NULL);

	/*
	t = nextMQ (mq) ;
	if (t == NULL)
		printf ("None\n") ;
	else
		printTask (*t) ;
	*/

	printMultiQ (mq) ;
	t = delNextMQ (mq) ;

	//if (!isEmptyMQ(mq))
	//	printf ("IT IS not EMPTY\n") ;

	fclose (f) ;

	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
	printf("Total time is %f ms.\n",elapsedTime);
	return 0 ;
}
