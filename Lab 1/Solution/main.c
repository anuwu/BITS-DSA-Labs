#include <stdio.h>
#include "seqListOps.h"

void enter ()
{
	char ch ;
	scanf ("%c" , &ch) ;
}

int main(void)
{
 int i;
 seqarr seq;
 joblist arr;

 printf ("Initialising elements\n") ;
 enter () ;

 initialize_elements (arr);	//initialises the job list. this is unsorted

 printf ("Printing job list\n") ;
 enter () ;

 printjoblist(arr);
 printf("\n") ;

 printf ("Creating seqarr\n") ;
 enter () ;


 seq[0] = createlist();		//creates an empty bucket
 seq[1] = createlist();		//creates an empty bucket
 seq[2] = createlist();		//creates an empty bucket

 printf ("Insert elements into buckets\n") ;
 enter () ;

 insertelements (arr,seq);	//inserts elements into the buckets

 printf ("Printing seqlist 0\n") ;
 enter () ;


 printseqlist (seq[0]);
 printf("\n") ;

 printf ("Printing seqlist 1\n") ;
 enter () ;

 printseqlist (seq[1]);
 printf("\n") ;

 printf ("Printing seqlist 2\n") ;
 enter () ;

 printseqlist (seq[2]);
 printf("\n") ;

 printf ("Copying sorted buckets\n") ;
 enter () ;

 copy_sorted_ele (seq , arr); 

 printf ("Sorted List\n");
 enter () ;

 printjoblist(arr);
}
 
