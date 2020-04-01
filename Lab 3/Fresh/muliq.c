#include <stdio.h>
#include <stdlib.h>
#include "multiq.h" 

void enter ()
{
	char ch ;
	printf ("Press enter to continue\n") ;
	scanf ("%c" , &ch) ;
}

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

struct MultiQ addMQ(struct MultiQ mq, struct Task* t)
{
	struct Queue *insq ;
	int q_no ;

	q_no = t->pri - 1 ;
	insq = &(mq.qarr[q_no]) ;


	if (insq->t_cnt == 0)
	{
		insq->head = t ;
		insq->tail = t ;
	}
	else
	{
		insq->tail->next = t ;
		insq->tail = t ;
	} 

	insq->t_cnt += 1 ;

	//printMultiQ (mq) ;
	//enter () ;
		
	return mq ;
} 

struct Task* nextMQ (struct MultiQ mq)
{
	if (isEmptyMQ(mq))
		return NULL ;
	else
	{
		int pri = 0 ;
		for (pri = 0 ; mq.qarr[pri].t_cnt == 0 ; pri++) ;
		
		return mq.qarr[pri].head ;
	}
}

struct Task* delNextMQ (struct MultiQ mq)
{
	if (isEmptyMQ(mq))
		return NULL ;
	else
	{
		struct Task *t ;
		int pri = 0 ;
		for (pri = 0 ; mq.qarr[pri].t_cnt == 0 ; pri++) ;
		
		t = mq.qarr[pri].head ;
		mq.qarr[pri].head = mq.qarr[pri].head->next ;
		mq.qarr[pri].t_cnt -= 1 ;

		return t ;
	}
}


int isEmptyMQ (struct MultiQ mq)
{
	int pri = 0 ;
	for (pri = 0 ; pri < MAX ; pri++)
	{
		if (mq.qarr[pri].t_cnt > 0)
			return 0 ;
	}

	return 1 ;
}

void printTask (struct Task t)
{
	printf ("%d\t%d\n", t.id , t.pri) ;

}

void printQueue (struct Queue q)
{
	//printf ("%d\n" , q.t_cnt) ;
	if (q.t_cnt == 0)
	{
		printf ("The queue is empty\n") ;
	}
	else
	{	
		printf ("ID\tPriority\n") ;
		struct Task* ptr = q.head ;
	
		while (ptr != NULL)
		{
			printTask (*ptr) ;
			ptr = ptr->next ;
		}
	}
}

void printMultiQ (struct MultiQ mq)
{
	//printf ("HAS COME HERE") ;
	//enter () ;
	int i ;
	for (i = 0 ; i < MAX ; i++)
	{
		printf ("Queue of priority %d - \n" , (i+1)) ;
		printQueue (mq.qarr[i]) ;
		printf ("\n") ;
	}
}
