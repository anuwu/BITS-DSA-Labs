#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include <string.h>
#include <math.h>

void str_to_stu (struct student *stu , char* str)
{
	char *tok ;

	tok = strtok (str , ",") ;
	strcpy (stu->name , tok) ;
	tok = strtok (NULL , ",") ;
	stu->cgpa = (double) atof(tok) ;
}

void input_all_records (struct student* A , char *filename)
{
	FILE *f ;
	char *buf ;
	int i = 0 ;

	f = fopen (filename , "r") ;

	if (f == NULL)
		printf("WTF?") ;

	buf = (char *) malloc (RECLENGTH * sizeof(char)) ;
	while (fgets (buf , RECLENGTH ,f) != NULL)
	{
		/*
		tok = strtok (buf , ",") ;
		strcpy (A[i].name , tok) ;
		tok = strtok (NULL , ",") ;
		A[i].cgpa = (double) atof(tok) ; */

		str_to_stu (A + i , buf) ;

		//printf ("Name = %s CGPA = %f\n" , A[i].name , A[i].cgpa) ;

		i++ ;
	}

	free(buf);
	fclose (f) ;
}

void display_record (struct student stu)
{
	printf ("Name = %s CGPA = %f" , stu.name , stu.cgpa) ;
}

void display_all_records (struct student *A , int size)
{
	int i ;
	for (i = 0 ; i < size ; i++)
	{	
		printf("%d " , i+1) ;
		display_record (A[i]) ;
		printf("\n") ;
	}
}
