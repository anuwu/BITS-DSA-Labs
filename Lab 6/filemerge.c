
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include <string.h>
#include <math.h>

void mergefile (FILE *f1 , FILE *f2 , FILE *fout)
{
	struct student *stu1 , *stu2 ;
	char *buf1 , *buf2, *buf1_for_sts, *buf2_for_sts ;
	
	buf1 = (char *) malloc (RECLENGTH * sizeof(char)) ;
	buf1_for_sts = (char *) malloc (RECLENGTH * sizeof(char)) ;
	buf2 = (char *) malloc (RECLENGTH * sizeof(char)) ;
	buf2_for_sts = (char *) malloc (RECLENGTH * sizeof(char)) ;
	stu1 = (struct student *) malloc (sizeof (struct student)) ;
	stu2 = (struct student *) malloc (sizeof (struct student)) ;

	int count1 = 0, count2 = 0 ;
	int cond1 = 0 ;
	int cond2 = 0 ;

	while ((cond1 || fgets (buf1 , RECLENGTH , f1) != NULL) && (cond2 || fgets (buf2 , RECLENGTH , f2) != NULL))
	{
		//printf ("%s\n%s\n" , buf1 , buf2) ;
		strcpy (buf1_for_sts , buf1) ;
		strcpy (buf2_for_sts , buf2) ;
		str_to_stu (stu1 , buf1_for_sts) ;
		str_to_stu (stu2 , buf2_for_sts) ;

		//printf ("%s\n%s\n" , buf1 , buf2) ;


		if (stu1->cgpa < stu2->cgpa)
		{
			count1++ ;
			//printf("File 1 %d %s\n",count1,buf1) ;
			fputs (buf1 , fout) ;
			cond1 = 0 ;
			cond2 = 1 ;

		}
		else
		{
			count2++ ;
			//printf("File 2 %d %s\n",count2,buf2) ;
			fputs (buf2 , fout) ;
			cond1 = 1 ;
			cond2 = 0 ;
		}
		//fputs ("\n" , fout) ;
	}

	//printf ("FALSE\n") ;
	//justenter ();

	if (feof(f1))
	{
		//printf ("FILE 1 IS OVER\n") ;
		//justenter () ;
		count2++ ;
		//printf ("File 2 %d %s\n" , count2 , buf2) ;
		fputs (buf2 , fout) ;
		while (fgets (buf2 , RECLENGTH , f2) != NULL)
		{
			count2++ ;
			//printf("File 2 %d %s\n",count2,buf2) ;
			fputs (buf2 , fout) ;
			//fputs ("\n" , fout) ;
		}
	}
	else if (feof(f2))
	{
		//printf ("FILE 2 IS OVER\n") ;
		//justenter () ;
		count1++ ;
		//printf("File 1 %d %s\n",count1,buf1) ;
		fputs (buf1 , fout) ;
		
		while (fgets (buf1 , RECLENGTH , f1) != NULL)
		{
			count1++ ;
			//printf("File 1 %d %s\n",count1,buf1) ;
			fputs (buf1 , fout) ;
			//fputs ("\n" , fout) ;
		}
	}
	
	free (buf1) ;
	free (buf2) ;
	free (stu1) ;
	free (stu2) ;
	free (buf1_for_sts) ;
	free (buf2_for_sts) ;

	//printf ("FINAL COUNT = %d\n" , count1+count2) ;
}

void mergeall (int* filecount)
{
	//debug_merge (filecount) ;

	
	int fc, filenum, no_of_merge ;
	char *fn1 , *fn2 , *fnout, *fnlast ;
	FILE *f1 , *f2 , *fout ;

	fc = *filecount ;

	if (fc == 1)
		return ;
	
	while (fc != 1)
	{	
		no_of_merge = fc/2 ;

		for (filenum = 1 ; filenum < fc ; filenum += 2)
		{
			fn1 = create_filename (filenum) ;
			fn2 = create_filename (filenum + 1) ;
			fnout = create_filename (filenum/2 + 1) ;

			f1 = fopen (fn1 , "r") ;
			f2 = fopen (fn2 , "r") ;
			fout = fopen ("temp.txt" , "w") ;

			//printf ("Filenum %d %s %s %s\n" , filenum , fn1 , fn2 , fnout) ;
			//justenter();
			mergefile (f1 , f2 , fout) ;
			//printf ("before rename") ;
			//justenter () ;

			fclose (f1) ;
			fclose (f2) ;
			fclose (fout) ;
			remove (fn1) ;
			remove (fn2) ;
			rename ("temp.txt" , fnout) ;

			free (fn1) ;
			free (fn2) ;
			free (fnout) ;
		}	

		if (fc % 2 == 1)
		{
			fnlast = create_filename (no_of_merge + 1) ;
			fn1 = create_filename (fc) ;
			rename (fn1 , fnlast) ;	

			//printf ("Filenum %d %s %s\n" , filenum , fn1 , fnlast) ;
		}

		fc -= no_of_merge ;
	}


	//printf ("Filecount = %d .Proceed to rename file1?\n" , fc) ;
	//justenter () ;
	rename ("file1.txt" , "final.txt") ;
	*filecount = fc ; 

	
}

void debug_merge (int *filecount)
{
	FILE *f1 , *f2 , *fout ;

	f1 = fopen ("file1.txt" , "r") ;
	f2 = fopen ("file2.txt" , "r") ;
	fout = fopen ("temp.txt" , "w") ;

	//printf ("IT IS HERE BEFORE MERGE\n") ;
	//justenter () ;

	mergefile (f1 , f2 , fout) ;

	//printf ("IT IS HERE AFTER MERGE\n") ;
	//justenter () ;

	fclose (f1) ;
	fclose (f2) ;
	fclose (fout) ;

	*filecount -= 1 ;
}


