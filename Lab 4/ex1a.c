/*
-----------------------------------------------------------------------------
Sample result 1 - {serial calling of p,g,h,d from main ()}

Address of bits = 6295616

(Notice how all the asddresses below are the same. Once a function is called,
stack space is pushed and popped after the function exits)

Address of pilani = 2612888404
Address of goa = 2612888404
Address of hyderabad = 2612888404
Address of dubai = 2612888404
-----------------------------------------------------------------------------


=============================================================================
=============================================================================


/*
-----------------------------------------------------------------------------
Sample result 2 - {serial calling p,h,d from main(). nested calling of g from p}


Address of bits = 6295616
Address of pilani = 755733316
Address of goa = 755733284		- gap of 32 = 8 bytes for pushing pilani and 24 for function snapshot
Address of hyderabad = 755733316
Address of dubai = 755733316

-----------------------------------------------------------------------------
*/




#include <stdio.h>
int bits = 10 ;

void p ()
{
	int pilani = 1 ;

	printf ("Address of pilani = %u\n" , &pilani) ;

	g () ;
}

void g ()
{
	int goa = 2 ;

	printf ("Address of goa = %u\n" , &goa) ;
}

void h ()
{
	int hyd = 3 ;

	printf ("Address of hyderabad = %u\n" , &hyd) ;
}

void d ()
{
	int dub = 4 ;

	printf ("Address of dubai = %u\n" , &dub) ;
}




int main ()
{
	printf ("Address of bits = %u\n" , &bits) ;

	p() ;
	//g() ;
	h() ;
	d() ;
	
	return 0 ;
}
