#include <stdio.h>
#include <stdlib.h>

/*
-------------------------------------------------------------------------------------------------------------------------
Conclusion - Be naive and do memory allocation.
-------------------------------------------------------------------------------------------------------------------------
*/

void test1 (int no_of_int)
{
	int *ptr1 = (int *) malloc (no_of_int * sizeof(int)) ;
	int *ptr2 ;
	int i = 0 , num = 10 ;

	//Both are not null
	if (ptr1 == NULL)
		printf ("PTR1 IS NULL RIGHT AFTER MALLOC\n") ;
	if (ptr2 == NULL)
		printf ("PTR2 IS NULL BEFORE ASSIGNMENT\n") ;

	for (i = 0 ; i < no_of_int ; i++)
		ptr1[i] = num + i ;

	ptr2 = ptr1 ;

	printf ("Address of ptr1 = %d\n" , ptr1) ;
	printf("Before freeing - \n") ;
	for (i = 0 ; i < no_of_int ; i++)
		printf ("ptr1[%d] = %d\n" , i , ptr1[i]) ;
	
	free(ptr1) ;
	//free(ptr2) ;

	printf("\nAfter freeing - \n") ;
	printf ("Address of ptr1 = %d\n" , ptr1) ;
	printf("PTR1 - \n") ;
	for (i = 0 ; i < no_of_int ; i++)
		printf ("ptr1[%d] = %d\n" , i , ptr1[i]) ;
	printf ("PTR2 - \n") ;
	for (i = 0 ; i < no_of_int ; i++)
		printf ("ptr2[%d] = %d\n" , i , ptr2[i]) ;

	//Both are not null
	if (ptr1 == NULL)
		printf ("PTR1 IS NULL RIGHT AFTER MALLOC\n") ;
	if (ptr2 == NULL)
		printf ("PTR2 IS NULL BEFORE ASSIGNMENT\n") ;

	printf ("\n-----------------------------------------------------------------------------------------\n") ;

	//-----------------------------------------------------------------------------------------

	ptr1 = (int *) malloc (no_of_int * sizeof(int)) ;
	i = 0 ; num = 30 ;
	ptr2 = ptr1 ;

	for (i = 0 ; i < no_of_int ; i++)
		ptr1[i] = num + i ;

	printf ("\nAddress of ptr1 = %d\n" , ptr1) ;
	printf("Before freeing - \n") ;
	for (i = 0 ; i < no_of_int ; i++)
		printf ("ptr1[%d] = %d\n" , i , ptr1[i]) ;

	free(ptr1) ;

	printf("\nAfter freeing - \n") ;
	printf ("\nAddress of ptr1 = %d\n" , ptr1) ;
	printf("PTR1 - \n") ;
	for (i = 0 ; i < no_of_int ; i++)
		printf ("ptr1[%d] = %d\n" , i , ptr1[i]) ;
	printf ("PTR2 - \n") ;
	for (i = 0 ; i < no_of_int ; i++)
		printf ("ptr2[%d] = %d\n" , i , ptr2[i]) ;

	printf ("\n-----------------------------------------------------------------------------------------\n") ;
	
	//-----------------------------------------------------------------------------------------

	ptr1 = (int *) malloc (2 * sizeof(int)) ;
	i = 0 ; num = 50 ;

	for (i = 0 ; i < 2 ; i++)
		ptr1[i] = num + i ;

	ptr2 = (int *) malloc (8 * sizeof(int)) ;
	i = 0 ; num = 60 ;

	for (i = 0 ; i < 8 ; i++)
		ptr2[i] = num + i ;

	printf ("Address of ptr1 = %d\n" , ptr1) ;
	printf("Before freeing - \n") ;
	for (i = 0 ; i < no_of_int ; i++)
		printf ("ptr1[%d] = %d\n" , i , ptr1[i]) ;
	printf ("Address of ptr2 = %d\n" , ptr2) ;
	for (i = 0 ; i < 8 ; i++)
		printf ("ptr2[%d] = %d\n" , i , ptr2[i]) ;

}

void init_test ()
{
	int *ptr ;
	if (ptr == NULL)
		printf ("IT IS NULL\n") ;

	ptr = (int *) malloc (4) ;
	printf ("ptr = %d\n" , *ptr) ;
	*ptr = 10 ;
	printf ("ptr = %d\n" , *ptr) ;
	free(ptr) ;
	printf ("ptr = %d\n" , *ptr) ;
	ptr = NULL ;
	//free(ptr) ;

	if (ptr == NULL)
		printf ("IT IS NULL\n") ;
	printf ("NULL = %d\n" , NULL) ;
}




int main ()
{
	test1 (10) ;
	//init_test () ;

	
return 0 ;
}
