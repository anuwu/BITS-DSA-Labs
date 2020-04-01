/*
-----------------------------------------------------------------------------
Sample result 1 - {recursion until 10}

Address of bits = 6295616

Address of pilani = 446415732
Value of n = 1 and address of n = 446415724	- gap of 8

Address of pilani = 446415684			- gap of 40 = 8 bytes for each pilani, n and 24 for function snapshot 
Value of n = 2 and address of n = 446415676	- gap of 8

Address of pilani = 446415636			- gap of 40
Value of n = 3 and address of n = 446415628	- gap of 8

Address of pilani = 446415588
Value of n = 4 and address of n = 446415580

Address of pilani = 446415540
Value of n = 5 and address of n = 446415532

Address of pilani = 446415492
Value of n = 6 and address of n = 446415484

Address of pilani = 446415444
Value of n = 7 and address of n = 446415436

Address of pilani = 446415396
Value of n = 8 and address of n = 446415388

Address of pilani = 446415348
Value of n = 9 and address of n = 446415340

Address of pilani = 446415300
Value of n = 10 and address of n = 446415292


(Same as the first address of pilani)
Address of goa = 446415732
Address of hyderabad = 446415732
Address of dubai = 446415732
-----------------------------------------------------------------------------


=============================================================================
=============================================================================



/*
-----------------------------------------------------------------------------
Sample result 2 - {infinite recursion}

Size of int = 4
Address of pilani = 2581957364
Value of n = 1 and address of n = 2581957356
.
.
.
.
.
Address of pilani = 2573575988
Value of n = 174613 and address of n = 2573575980

Gap between each integer allocation = 8
Size of int = 4 bytes
Bits allocated = 32 bits
Hypothesized content of each memory address = (32 bits/8 address gap) = 4 bits per address gap = 1 nibble per address


Observed Stack space = (2581957364 - 2573575980)/2 = 4,190,692 bytes = 4092.47 kb
The number is unnaturally close to 4096 kb. The difference = 3612 bytes. This stack space is probably used for some internal purpose
Hence stack size = 4096 kb = 4 * (1024 kb) = 4mb
-----------------------------------------------------------------------------
*/



#include <stdio.h>

int bits = 10 ;

void enter ()
{
	char ch ;

	printf ("Press enter to continue\n") ;
	scanf ("%c" , &ch) ;
}

void p (int n)
{
	int pilani = 1 ;
	printf ("Address of pilani = %u\n" , &pilani) ;
	printf ("Value of n = %u and address of n = %u\n\n" , n , &n) ;

	if (n == 1)
		enter () ;
	
	if (n < 10)
		p(n+1) ;
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
	printf ("Size of int = %u\n" , sizeof(int)) ;

	printf ("Address of bits = %u\n\n" , &bits) ;
	int init_n = 1 ;

	p(init_n) ;
	g() ;
	h() ;
	d() ;
	
	return 0 ;
}
