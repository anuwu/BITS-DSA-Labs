#include <stdio.h>
#include "multiq.h"
#include <stdlib.h>


void enter ()
{
	char ch ;
	printf ("Press enter to continue\n") ;
	scanf ("%c" , &ch) ;
}

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
	int id, pri ;
	char comma ; 
	printf ("ID\tPriority\n") ;
	while (!feof(f))
	{
		fscanf (f,"%d" , &id) ;
		fscanf (f, "%c" , &comma) ;
		fscanf (f,"%d", &pri) ;
		printf ("%d\t%d\n" , id, pri) ;
	}	

	f = fopen("input10.txt" , "r") ;
}

struct MultiQ loadData (struct MultiQ mq, FILE *f)
{
	//debug_loadData (f) ;
	//enter () ;

	f = fopen("input10.txt" , "r") ;

	int id, pri ;
	char comma ;	
	struct Task* taskptr ;

	while (!feof(f))
	{	
		taskptr = (struct Task*) malloc(sizeof(struct Task)) ;
		
		fscanf (f,"%d" , &(taskptr->id)) ;
		fscanf (f, "%c" , &comma) ;
		fscanf (f,"%d", &(taskptr->pri)) ;
		taskptr->next = NULL ;

		//printf ("loadData loop\n") ;		
		//enter () ;
	
		printf ("%d %d\n" , taskptr->id,taskptr->pri) ;
		enter () ;
		mq = addMQ (mq , *taskptr) ;

		printf ("Printing queue after addMQ\n") ;
		if (mq.qarr[taskptr->pri - 1].head != NULL)
		{
			printf ("Head of the queue has changed\n") ;

			enter () ;
		}
		printf ("%d %d %d %d\n" , mq.qarr[taskptr->pri - 1].head , mq.qarr[taskptr->pri - 1].head->id, mq.qarr[taskptr->pri - 1].head->pri , mq.qarr[taskptr->pri - 1].head->next) ;
		enter () ;
		printQueue (mq.qarr[taskptr->pri - 1]) ;

		//printMultiQ (mq) ;

		printf ("ENTER AFTER ADDMQ\n") ;
		enter () ;

		//printf ("AFTER MQ PRINT%d %d\n" , mq.qarr[5].head->id , mq.qarr[5].head->pri) ;
		//enter () ;
	}

	printMultiQ (mq) ;

	return mq ;
}

int main ()
{
	struct MultiQ mq ;
	FILE *f = fopen("input10.txt" , "r") ;

	if (f == NULL)
	{
		printf ("File has not opened\n") ;
		exit (0) ;
	}

	mq = createMQ (MAX) ;
	//debug_createMQ (mq) ;
	//printMultiQ(mq) ;


	mq = loadData (mq , f) ;	
	fclose (f) ;
	
	return 0 ;
}
