#include <stdio.h>
#include <stdlib.h>
#include "multiq.h" 

struct MultiQ createMQ (int num)
{
	int i ;
	struct MultiQ mq ;

	mq.qarr = (struct Queue*) malloc (num * sizeof(struct Queue)) ;
	for (i = 0 ; i < num ; i++)
	{
		mq.qarr[i].head = NULL ;
		mq.qarr[i].tail = NULL ;
		mq.qarr[i].t_cnt = 0 ;
	}

	mq.q_cnt = num ;

	return mq ;
}

struct MultiQ addMQ(struct MultiQ mq, struct Task t)
{
	struct Queue *insq ;
	int q_no ;

	//printf("%d %d\n" , t.id , t.pri) ;

	q_no = t.pri - 1 ;
	insq = &(mq.qarr[q_no]) ;

	
	if (insq->head != NULL)
	{
		printf ("Manual BEFore COND %d %d %d %d\n", q_no, insq->head->id , insq->head->pri , insq->t_cnt) ;
	enter () ;
	}



	/*
	printf ("addMQ\n") ;
	printf ("%d %d\n" , t.id , t.pri) ;
	printf ("%d %d %d\n" , insq->head , insq->tail , insq->t_cnt) ;
	enter () ;
	*/

	//printf ("addMQ\n") ;
	//enter () ;
	//printf ("The value of t_cnt = %d\n" , insq->t_cnt) ;


	if (insq->t_cnt == 0)
	{
		printf ("Inside first node insertion of queue no. %d\n" , q_no) ;
		enter () ;

		insq->head = &t ;
		insq->tail = &t ;
		insq->t_cnt += 1 ;

		/*
		if (insq->head->next == NULL)
		{
			printf ("IT IS NULL!\n") ;
			enter () ;
		} */


		//printf("%d %d\n" , insq->head->id , insq->head->pri) ;
		printQueue (mq.qarr[q_no]) ;
	//printf ("The grand finale before I prove my laptop is fucking me over\n") ;
	//enter () ;
	//printQueue (mq.qarr[q_no]) ;

		//printMultiQ(mq) ;
		printf("\n") ;
	}

	else
	{
		printf ("Inside further node insertion of queue no. %d\n" , q_no) ;
		//enter () ;
		printf ("Manual %d %d\n", insq->tail->id , insq->tail->pri) ;
		printf ("Manual %d %d\n", insq->head->id , insq->head->pri) ;
		//printf ("Manual %d %d\n", t.id , t.pri) ;
		enter () ;


		insq->tail->next = &t ;
		insq->tail = &t ;
		insq->t_cnt += 1 ;

		//printf("%d %d\n" , insq->tail->id , insq->tail->pri) ;
		printQueue (mq.qarr[q_no]) ;

		//printMultiQ (mq) ;
		printf("\n") ;
	} 
	
	//insq->t_cnt += 1 ; 
	
	
	printf ("BEFORE RETURN!\n") ;
	printf ("%d %d %d\n" , mq.qarr[t.pri - 1].head->id, mq.qarr[t.pri - 1].head->pri , mq.qarr[t.pri - 1].head->next) ;
	enter () ;
	/*
	if (mq.qarr[q_no].head->next == NULL)
	{
		printf ("IT IS NULL AGAIN\n") ;
		printf ("%d %d %d\n", mq.qarr[q_no].head->id , mq.qarr[q_no].head->pri , mq.qarr[q_no].head->next) ;
		enter () ;
	}*/

	printMultiQ(mq) ;
	
	return mq ;
} 

void printTask (struct Task t)
{
	//printf ("HAS COME HERE\n") ;
	//enter () ;


	printf ("%d\t%d\t%d\t%d\n" , &t, t.id , t.pri , t.next) ;

}

void printQueue (struct Queue q)
{
	//printf ("HAS COME INSIDE PRINTQueUE HERE\n") ;
	//enter () ;

	//printf ("%d %d %d\n" , q.head , q.tail, q.t_cnt) ;
	
	if (q.t_cnt == 0)
	{
		printf ("The queue is empty\n") ;
	}
	else
	{	
		//printf ("HAS COME INSIDE ELSE OF PRINTQUEUE\n") ;
		//enter () ;m
		printf ("ID\tPriority\n") ;

		struct Task* ptr = q.head ;

		
		if (ptr->next == NULL)
		{
			printf ("IT IS NULL INSIDE PRINTQUEUE!\n") ;
			enter () ;
			//ptr = ptr->next ;
		} 

		while (ptr != NULL)
		{
			printf ("HAS COME INSIDE PRINTING LOOP OF QUEUE\n") ;
			enter () ;
			printTask (*ptr) ;
			ptr = ptr->next ;
		}
	}
}

void printMultiQ (struct MultiQ mq)
{
	int i ;
	for (i = 0 ; i < MAX ; i++)
	{
		printf ("Queue of priority %d - \n" , (i+1)) ;
		printQueue (mq.qarr[i]) ;
		printf ("\n") ;
	}
}
