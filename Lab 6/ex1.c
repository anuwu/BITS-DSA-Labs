#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include <string.h>
#include <time.h>
#include <math.h>

#define DATASIZE 1024

int main ()
{
	//debugfile () ;

	struct student *A ;
	char filename[10] = "10240.txt" ;
	int div = 1 ;
	int filecount, fc ;
	FILE *f ;
	struct timeval t1, t2 ;
	double elapsedTime ;

	f = fopen ("2-3mid.txt" , "w") ;
	fprintf (f , "Divisions\t\tFiles Generated\t\tTime\n") ;

	int divarray[24] ;
	divarray[0] = 1 ;
	divarray[1] = 2;
	divarray[2] = 4;
	divarray[3] = 5;
	divarray[4] = 8;
	divarray[5] = 10;
	divarray[6] = 16;
	divarray[7] = 20;
	divarray[8] = 32;
	divarray[9] = 40;
	divarray[10] = 64;
	divarray[11] = 80;
	divarray[12] = 128;
	divarray[13] = 160;
	divarray[14] = 256;
	divarray[15] = 320;
	divarray[16] = 512;
	divarray[17] = 640;
	divarray[18] = 1024;
	divarray[19] = 1280;
	divarray[20] = 2048;
	divarray[21] = 2560;
	divarray[22] = 5120;
	divarray[23] = 10240;


	for (div = 5100 ; div <= 8949 ; div++)
	{
	
		//A = (struct student *) malloc (DATASIZE * sizeof(struct student)) ;
		//input_all_records (A , filename) ;	
		//display_all_records (A) ;

		//merge_sort (A, DATASIZE) ;
		//display_all_records (A, DATASIZE) ;

		//iter_merge_sort (A , DATASIZE) ;
		//display_all_records (A , DATASIZE) ;

		gettimeofday (&t1 , NULL) ;
		filecount = filecreate (filename , div) ;
		fc = filecount ;
		printf ("Divions = %d No of files generated = %d\n" , div , filecount) ;

		//printf ("Proceed to merge?\n") ;
		//justenter() ;
		mergeall (&filecount) ;
		gettimeofday (&t2 , NULL) ;

		elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0 ;
		elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0 ;
		
		fprintf (f , "%d\t\t%d\t\t%f\n" , div , fc , elapsedTime) ;

		//printf ("Final filecount = %d\n" , filecount) ;

		//printf ("Proceed to delete files? ") ;
		//enter () ;
		delete_files (filecount) ;
	}

	fclose (f) ;
	
	return 0 ;
}
