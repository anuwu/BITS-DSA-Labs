#include "hashtable.h"
#include "ex2data.h"
#include "hash.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

int ts = 5000 ;
int bn = 5077 ;
int init_now ;

struct Hashtable* createht ()
{
	struct Hashtable* ht ;
	ht = (struct Hashtable *) malloc (sizeof (struct Hashtable)) ;

	ht->strarr = NULL ;
	ht->heads = (struct ele **) malloc (ts * sizeof (struct ele*)) ;
	ht->elementCount = 0 ;
	ht->insertionCost = 0 ;
	ht->queryingCost = 0 ;

	for (int i = 0 ; i < ts ; i++)
		ht->heads[i] = NULL ;

	return ht ;
}

int compstr (char *str1 , char *str2)
{
	if (strlen (str1) != strlen (str2))
		return 0 ;
	else
	{
		int i , len = strlen (str1) ;
		for (i = 0 ; i < len ; i++)
		{
			if (tolower(str1[i]) != tolower(str2[i]))
				return 0 ;
		}

		return 1 ;
	}
}

void insert (struct Hashtable* ht , int index) 
{
	int hindex ;
	struct ele *head , *ins, *ptr , *prev ;

	hindex = hash (ht->strarr[index] , ts , bn) ;	
	head = ht->heads[hindex] ;

	if (head == NULL)
	{
		head = (struct ele*) malloc (sizeof (struct ele)) ;
		head->index = index ;
		head->occ = 1 ;
		head->next = NULL ;

		ht->heads[hindex] = head ;
	}
	else
	{
		ptr = head ;
		prev = ptr ;
		while (ptr != NULL)
		{
			if (compstr(ht->strarr[ptr->index] , ht->strarr[index]))
			{
				ptr->occ += 1 ;
				break ;
			}

			prev = ptr ;
			ptr = ptr->next ;
			ht->insertionCost += 1 ;
		}	

		if (ptr == NULL)
		{
			ptr = (struct ele*) malloc (sizeof(struct ele)) ;
			ptr->next = NULL ;
			ptr->occ = 1 ;
			ptr->index = index ;
			prev->next = ptr ;	
		}

	}

}

void insertAll (struct Hashtable *ht , char **strarr , int now)
{
	int i ; 

	ht->strarr = strarr ;
	ht->elementCount = now ;
	init_now = now ;
	
	for (i = 0 ; i < now ; i++)
	{
		//printf ("%s\n" , ht->strarr[i]) ;
		insert (ht , i) ;
	}
}

void traverse (struct Hashtable *ht , int div)
{
	int i , j ;
	struct ele* head ;

	for (i = 0 ; i < ts ; i++)
	{
		printf ("Hash entry %d - \n" , i) ;
		head = ht->heads[i] ;

		if (head == NULL)
			printf ("NULL\n") ;

		while (head != NULL)
		{
			for (j = 1 ; j <= head->occ ; j++)
				printf ("%s\n" , ht->strarr[head->index]) ;

			head = head->next ;
		}

		printf ("\n----------------\n") ;
		if (i % div == 0)
			just_enter () ;
	}
}


int lookup (struct Hashtable *ht , char *str) 
{
	int hindex ;
	struct ele *ptr ;

	hindex =  hash (str , ts , bn) ;
	ptr = ht->heads[hindex] ;

	while (ptr != NULL)
	{
		ht->queryingCost += 1 ;
		if (compstr(ht->strarr[ptr->index] , str))
			return ptr->index ;

		ptr = ptr->next ;
	}

	return -1 ;
}


void lookupall (struct Hashtable *ht ,  double m)
{
	int i , ind ;

	for (i = 0 ; i < m*init_now ; i++)
	{
		ind = lookup (ht , ht->strarr[i]) ;
		//printf ("%s , %s\n" , ht->strarr[i] , ht->strarr[ind]) ;
		//printf ("%d , %d\n" ,i , ind);
	}

}

double profile (struct Hashtable *ht)
{
	double m = 0.00 ;

	while (ht->queryingCost <= ht->insertionCost && m <= 1)
	{
		ht->queryingCost = 0 ;
		m += 0.0001 ;
		lookupall (ht , m) ;
		//printf("%d," , m) ;
	}
	//printf("\n") ;


	return m ;
}

int deleteht (struct Hashtable *ht , char *str)
{
	int hindex , no_del ;
	struct ele *head , *ptr , *prev, *del ;

	hindex = hash (str , ts , bn) ;
	head = ht->heads[hindex] ;

	//printf ("HINDEX = %d\n" , hindex) ;

	ptr = head ;
	prev = head ;
	while (ptr != NULL)
	{
		//printf ("%s %d %d\n" , ht->strarr[ptr->index] , strlen(str) , strlen(ht->strarr[ptr->index]));
		if (compstr(ht->strarr[ptr->index] , str))
		{
			//printf ("will be deleted %d times!" , ptr->occ) ;

			if (ptr == head)
			{
				head = head->next ;
				no_del = ptr->occ ;
				ht->elementCount -= no_del ;
				ht->heads[hindex] = head ;

				free(ptr) ;

			}
			else
			{
				del = ptr ;
				no_del = ptr->occ ;
				prev->next = ptr->next ;
				ht->elementCount -= no_del ;

				free(del) ;
				
			}

			return no_del ;
		}


		prev = ptr ;
		ptr = ptr->next ;
	}

	return 0 ;
}

char* fgets_fixup (char *str)
{
	int len ;
	char *newstr ;

	len = strlen (str) ;
	newstr = (char *) malloc ((len-1)* sizeof(char)) ;
	len -= 2 ;

	for (int i = 0 ; i < len ; i++)
		newstr[i] = str[i] ;
	
	newstr[len] = '\0' ;



	return newstr ;
}

int cleanup (struct Hashtable *ht , char *filename)
{
	FILE *f ;
	char buf[50] , *str ;
	int total_del = 0 ;

	f = fopen (filename , "r") ;

	while (fgets(buf , 50 , f) != NULL)
	{
		//str[strlen(str) - 1] = '\0' ;
		str = fgets_fixup (buf) ;
		//printf ("%s%d\n" , buf , strlen(buf)) ;
		//printf ("%s%d\n" , str , strlen(str)) ;
		//printf (" after function %d\n" , deleteht (ht , str)) ;
		total_del += deleteht(ht , str) ;

		//just_enter () ;
		free (str) ;
	}

	fclose (f) ;
	return total_del ;
}
