#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

void enter ()
{
	char ch ;
	printf ("Press enter to continue\n") ;
	scanf ("%c" , &ch) ;
}

void justenter ()
{
	char ch ;
	scanf ("%c" , &ch) ;
}

void debug1 () 
{
	char str[6] = "Hello" ;
	printf ("%s\n" , str) ;
	enter () ;
	for (int i = 0 ; i < 6 ; i++)
	{
		printf ("%d %d\n" , i , '\0') ;
	}		
}

void debugtok ()
{
	char buf[] = "abcdefgh,9.23";

	char *tok ;
	tok = strtok (buf , ",") ;

	printf ("%s\n" , tok) ;
	tok = strtok (NULL , ",") ;
	printf ("%s\n" , tok) ;
}

void split_record (struct student* stu , char *buf)
{
	char *tok ;
	tok = strtok (buf , ",") ;

	strcpy (stu->name , tok) ;
	tok = strtok (NULL , ",") ;
	stu->cgpa = (double) atof(tok) ;
}

void debugfile ()
{
	FILE *f ;
	char *buf ;
	struct student test ;

	int i = 0 ;

	f = fopen ("1024.txt" , "r") ;

	if (f == NULL)
	{	
		printf ("Error in opening file\n") ;
		enter () ;
	}

	buf = (char *) malloc (RECLENGTH * sizeof(char)) ;
	while (fgets (buf , RECLENGTH , f) != NULL)
	{
		printf ("%s" , buf) ;
		//justenter () ;
		split_record (&test , buf) ;
		printf ("Name = %s , cgpa = %f\n" , test.name , test.cgpa) ;
		//justenter();
	} 

	

	fclose(f) ;
}
