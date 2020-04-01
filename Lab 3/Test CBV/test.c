#include <stdio.h>

struct data
{
	int *num ;
} ;

struct data insertdata2 (struct data de , int a)
{
	de.num = &a ;
	return de ;
}


struct data insertdata(struct data d)
{
	int *a ;
	a = (int *) malloc (sizeof(int)) ;
	*a = 4 ;

	d = insertdata2 (d, *a) ;
	printf ("%d\n" , *d.num) ;

	return d ;
}

struct data insertdata1(struct data d)
{
	int a = 4 ;

	d = insertdata2 (d,a) ;
	printf ("%d\n" , *d.num) ;

	return d ;
}


void main ()
{
	struct data test ;

	test = insertdata (test) ;
	printf ("%d\n" , *test.num) ;

	printf ("\n") ;
	struct data allah ;
	int b = 10 ;
	allah = insertdata2 (allah , b) ;
	printf ("%d\n" , *allah.num) ;		
}
