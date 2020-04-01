#include "hash.h"
#include <string.h>
#include <stdio.h>

void just_enter ()
{
	char ch ;
	scanf ("%c" , &ch) ;
}

void enter ()
{
	printf ("Press enter to continue\n") ;
	just_enter () ;
}

int hash (char *str , int ts , int bn)
{
	int i , len , val ;
	long long sum = 0 ;

	len = strlen (str) ;
	sum = 0 ;

	for (i = 0 ; i < len ; i++)
		sum += (int) str[i] ;

	val = (sum % bn) % ts ;

	//printf ("%d, " , sum) ;

	return val ;
}

int col_count (char **strarr , int now ,  int ts , int bn)
{
	int i , j , col = 0 , *hashbook ;

	hashbook = (int *) malloc (sizeof(int) * now) ;

	for (i = 0 ; i < now ; i++)
		hashbook[i] = hash (strarr[i] , ts , bn) ;

	for (i = 0 ; i < now ; i++)
	{
		for (j = 0 ; j < i ; j++)
		{
			if (hashbook[i] == hashbook[j])
			{
				col++ ;
				break ;
			}
		}
	}

	free(hashbook) ;
	return col ;
}


int ret_now (char *filename)
{
	int now = 0 ;
	FILE *f ;
	char ch[2] ;

	f = fopen (filename , "r") ;

	while (fgets (ch , 2 , f) != NULL)
	{
		//printf ("%s" , ch) ;
		if (isspace(ch[0]))
			now++ ;
	}

	return now ;
}

char **parser (char *filename)
{
	int wd_ind = 0 , wd_no , now ;
	FILE *f ;
	char buf[100] ;
	char ch[2] ;
	char **book ;

	f = fopen (filename , "r") ;
	wd_ind = 0 ;
	wd_no = 0 ;
	now = ret_now (filename) ;
	book = (char **) malloc (now * sizeof(char *)) ;
	
	//printf ("It is here\n") ;
	//just_enter() ;

	while (fgets (ch , 2 , f) != NULL)
	{
		if (isspace(ch[0]))
		{
			buf[wd_ind] = '\0' ;
			book[wd_no] = (char *) malloc (wd_ind * sizeof(char)) ;
			strcpy (book[wd_no] , buf) ;

			//printf ("%s %d\n" , book[wd_no] , wd_ind) ;
			wd_ind = 0 ;
			wd_no++ ;
		}
		else
		{
			buf[wd_ind] = ch[0] ;
			wd_ind++ ;
		}
	}
	
	//for (int i = 0 ; i < number_of_words ; i++)
		//printf ("69%s %d\n" , book[i] , strlen (book[i])) ;
	
	fclose(f) ;

	return book ;	
}
