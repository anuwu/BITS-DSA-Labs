#include "ex2data.h"
#include "hashtable.h"
#include <stdio.h>
#include <string.h>

int main ()
{
	char **book ;
	int now , col , total_del ;
	double cutoff , cutoff_after_cleanup ;
	struct Hashtable* ht ;
	ht = createht () ;
	//printf ("hello world!") ;

	book = parser ("random.txt") ;
	now = ret_now ("random.txt") ;
	col = col_count (book , now , ts , bn) ;
	insertAll (ht , book, now) ;

	//printf ("The number of words = %d and ts = %d and collisions = %d and insertion cost = %d\n" , now , ts , col , ht->insertionCost) ;
	//just_enter () ;
	
	//traverse (ht , 500) ;
	//lookupall (ht , 0.52) ;

	//printf ("The number of words = %d\nts = %d\ncollisions = %d\ninsertion cost = %d\nquery cost = %d\n" , ht->elementCount , ts , col , ht->insertionCost , ht->queryingCost) ;
	//ht->queryingCost = 0 ;
	
	//printf("%d\n",strcmp("znwesh" , "anwesh")) ;

	cutoff = profile (ht) ;
	printf ("The number of words = %d\nts = %d\ncollisions = %d\ninsertion cost = %d\nquery cost = %d\ncutoff = %f\n" , ht->elementCount , ts , col , ht->insertionCost , ht->queryingCost , cutoff) ;
	just_enter() ;

	total_del = cleanup (ht , "stopwords.txt") ;

	//printf ("Sample delete = %d\n\n" , deleteht(ht , "above")) ;
	printf ("The number of words = %d\nts = %d\ncollisions = %d\ninsertion cost = %d\nquery cost = %d\ncutoff = %f\ntotal deleted = %d\n" , ht->elementCount , ts , col , ht->insertionCost , ht->queryingCost , cutoff , total_del) ;
	just_enter () ;

	ht->queryingCost = 0 ;
	cutoff_after_cleanup = profile (ht) ;

	printf ("\nNew cutoff = %f\nQuerying cost = %d" , cutoff_after_cleanup , ht->queryingCost) ;
	
	return 0 ;
}
