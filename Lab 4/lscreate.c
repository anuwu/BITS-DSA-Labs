#include <stdio.h>
#include "lsdata.h"

int random_gen (int lower , int upper)
{
	int randno = (rand() % (upper - lower + 1)) + lower ;

	return randno ;
}

void displayList (struct List Ls)
{
	struct Number *ptr ;

	ptr = Ls.head ;
	while (ptr != NULL)
	{
		printf ("%d\t%d\n",ptr->x , ptr) ;
		ptr = ptr->next ;
	}
}


void deleteListPointerElements (struct List* Ls)
{
	struct Number *ptr, *nextnum ;

	ptr = Ls->head ;
	if (Ls->size == 0)
	{
		//enter () ;
		return ;
	}
	else if (Ls->size == 1)
	{
		myfree(Ls->head) ;
	}
	else
	{
		int i = 1 ;
		while (ptr != NULL && i < Ls->size)
		{
			nextnum = ptr->next ;	
			myfree(ptr) ;
			ptr = nextnum ;
			i++ ;
		}

		myfree(nextnum) ;
		Ls->size = 0 ;
	}
}

void deleteListPointer (struct List* Ls)
{
	deleteListPointerElements (Ls) ;
	myfree (Ls) ;
}

void deleteList (struct List Ls)
{
	struct Number *ptr , *nextnum ;
	ptr = Ls.head ;
	if (Ls.size == 0)
		return ;
	else
	{
		int i = 1 ;
		while (ptr != NULL && i < Ls.size)
		{
			nextnum = ptr->next ;	
			myfree(ptr) ;
			ptr = nextnum ;
			i++ ;
		}

		myfree(nextnum) ;
		Ls.size = 0 ;
	}
}

void enter ()
{
	char ch ;
	printf ("Press enter to continue") ;
	scanf ("%c" , &ch) ;
}

struct List createList (int N)
{
	struct List Ls ;
	struct Number* curr, *ptr ;
	int i ;

	srand(time(0)) ;

	Ls.size = N ;
	Ls.head = (struct Number *) myalloc (sizeof(struct Number)) ;

	curr = Ls.head ;
	curr->x = random_gen (LOWER , UPPER) ;
	curr->next = NULL ;
	
	for (i = 2 ; i <= N ; i++)
	{
		ptr = (struct Number *) myalloc (sizeof(struct Number)) ;
		ptr->x = random_gen (LOWER, UPPER) ;
		ptr->next = NULL ;

		curr->next = ptr ;
		curr = ptr ;	
	}	

	return Ls ;
}

struct List* createListPointer (int N)
{
	struct List *Ls ;
	struct Number* curr, *ptr ;
	int i ;

	srand(time(0)) ;

	Ls = (struct List *) myalloc (sizeof(struct List)) ;
	Ls->size = N ;
	Ls->head = (struct Number *) myalloc (sizeof(struct Number)) ;

	curr = Ls->head ;
	curr->x = random_gen (LOWER , UPPER) ;
	curr->next = NULL ;
	
	for (i = 2 ; i <= N ; i++)
	{
		ptr = (struct Number *) myalloc (sizeof(struct Number)) ;
		ptr->x = random_gen (LOWER, UPPER) ;
		ptr->next = NULL ;

		curr->next = ptr ;
		curr = ptr ;	
	}	

	return Ls ;
}

void debug_create ()
{
	struct List Ls , *Lsptr ;
	printf ("Size of Number = %d\n" , sizeof(struct Number)) ;
	printf ("Size of List = %d\n" , sizeof(struct List)) ;
	printf("\n") ;

	Ls = createList (10) ;
	printf ("Heap status after first list creation - \n") ;
	print_heap () ;
	printf ("\n") ;

	Lsptr = createListPointer (10) ;
	printf ("Heap status after first second listpointer creation - \n") ;
	print_heap () ;
	printf ("\n") ;

	struct Number *dummy ;
	dummy = (struct Number *) myalloc (sizeof(struct Number)) ;
	printf ("Heap status after first dummy creation - \n") ;
	print_heap () ;
	myfree(dummy) ;
	printf ("Heap status after first dummy deletion - \n") ;
	print_heap () ;
	printf("\n") ;
	
	deleteList (Ls) ;
	printf ("Heap status after first list deletion - \n") ;
	print_heap () ;

	deleteListPointerElements (Lsptr) ;
	printf ("Heap status after second listpointer element deletion - \n") ;
	print_heap () ;

	deleteListPointer (Lsptr) ;
	printf ("Heap status after second listpointer deletion - \n") ;
	print_heap () ;

	
	/* 
	-------------------------------------------------------------------------
	This is erroneous because Ls is not dynamically created

		deleteList (&Ls) ;
		printf ("Heap status after first list deletion - \n") ;
		print_heap () ;
		printf ("\n") ;
	-------------------------------------------------------------------------
	*/
}
