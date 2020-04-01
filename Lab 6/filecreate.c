#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include <string.h>
#include <math.h> 

int no_of_digit (int num)
{
	int cnt = 0 ;
	
	while (num != 0)
	{
		cnt++ ;
		num = num/10 ;
	}

	return cnt ;
}

char* create_filename (int filecount)
{
	int i,j,dig ;
	char *fcstr , *filename ;

	dig = no_of_digit (filecount) ;

	filename = (char *) malloc ((4 + dig + 4 + 1) * sizeof(char)) ;
	fcstr = (char *) malloc ((dig + 1) * sizeof(char)) ;
	
	sprintf (fcstr , "%d" , filecount) ;

	filename[0] = 'f' ;
	filename[1] = 'i' ;
	filename[2] = 'l' ;
	filename[3] = 'e' ;
	
	i = 0 ; j = 4 ;
	while (fcstr[i] != '\0')
	{
		filename[j] = fcstr[i] ;
		j++ ;
		i++ ;
	}
	
	
	filename[j++] = '.' ;
	filename[j++] = 't' ;
	filename[j++] = 'x' ;
	filename[j++] = 't' ;
	filename[j] = '\0' ;
	free(fcstr) ;

	return filename ;
}

char* stu_to_str (struct student stu)
{
	int i, j ;	
	char *cgpastr , *str;

	cgpastr = (char *) malloc (5 * sizeof(char)) ;
	str = (char *) malloc (RECLENGTH * sizeof(char)) ;

	strcpy (str, stu.name) ;

	gcvt(stu.cgpa , 3 , cgpastr) ;

	i = 0 ;	
	while (str[i] != '\0')
		i++ ;

	str[i++] = ',' ;
	for (j = 0 ; cgpastr[j] != '\0' ; j++)
	{
		str[i] = cgpastr[j] ;
		i++ ; 
	}

	str[i] = '\0' ;
	free(cgpastr) ;

	return str ;
}

void write_to_file (struct student *A , int size , int filecount)
{
	char *filename , *recbuf ;
	FILE *fout ;

	filename = create_filename (filecount) ;
	fout = fopen (filename , "w") ;

	//printf ("Filename : %s\n" , filename) ;
	//enter () ;

	for (int i = 0 ; i < size ; i++)
	{
		recbuf = stu_to_str (A[i]) ;
		//printf ("%s\n" , recbuf) ;
		fputs (recbuf , fout) ;
		fputs ("\n" , fout) ;
	}

	free(recbuf) ;
	free(filename) ;
	fclose(fout) ;
}

int filecreate (char *filename , int div)
{
	FILE *fin ;
	char *buf ,*tok ;
	int filecount, rec_no, buf_count ;
	struct student *A ;

	fin = fopen (filename , "r") ;
	filecount = 0 ;	
	rec_no = 0 ;
	buf_count = 0 ;
	buf = (char *) malloc (RECLENGTH * sizeof(char)) ;
	A = (struct student *) malloc (div * sizeof(struct student)) ;
	
	while (fgets (buf , RECLENGTH , fin) != NULL)
	{

		/*
		tok = strtok (buf , ",") ;
		strcpy (A[buf_count].name , tok) ;
		tok = strtok (NULL , ",") ;
		A[buf_count].cgpa = (double) atof(tok) ;
		*/
	
		str_to_stu (A + buf_count , buf) ;

		buf_count++ ;
		//printf ("%d %d %s\n" , rec_no , buf_count, buf) ;
		rec_no++ ;

		

		if (buf_count == div)
		{
			filecount++ ;
			//printf ("%d\n" , rec_no);
			//enter () ;
			merge_sort (A , div) ;
			//display_all_records (A , div) ;
			//enter () ;
			//printf ("Proceed to write to file!\n") ;
			//enter () ;
			write_to_file (A , div , filecount) ;
			//printf ("Done writing to file\n") ;
			//enter () ;
			
			buf_count = 0 ;
		}
	}

	/*
	if (feof(fin))
	{
		printf ("END OF FILE!\n") ;
		enter () ;
	} */

	if (buf_count != 0)	//not a multiple of div
	{
		//printf ("IT IS HERE %d \n" , buf_count) ;
		//enter () ;
		filecount++ ;
		merge_sort (A , buf_count) ; 
		write_to_file (A , buf_count , filecount) ;
	}

	free(A) ;
	free(buf) ;
	fclose (fin) ;
	//printf ("Record count = %d\n" , (rec_no)) ;
	return filecount ;
}

void delete_files (int filecount)
{
	for (int i = 1 ; i <= filecount ; i++)
		remove (create_filename(i)) ; 
}
