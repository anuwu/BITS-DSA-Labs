#include <stdio.h>
#include "data.h"
#include "func.h"

void print_menu ()
{
	printf ("Enter your option\n") ;
	printf ("1. Create tree\n") ;
	printf ("2. Insert domain with IP\n") ;
	printf ("3. Lookup a domain\n") ;
	printf ("4. Traverse the tree\n") ;
	printf ("5. Exit\n") ;
}

int main ()
{
	int cont = 1 , option , i ;
	char domip[100] , dom[100] ;
	char dummy ;
	struct STree *st ;
	st = NULL ;

	struct lookupres *lk ;

	do
	{	
		print_menu () ;
		scanf ("%d" , &option) ;
		scanf ("%c" , &dummy) ;

		switch (option)
		{
			case 1 :
				if (st != NULL)
				{
					printf ("Tree has already been created!\n") ;
					break ;
				}

				st = create_tree () ;
				printf ("Tree created!\n") ;

				break ;

			case 2 :
				if (st == NULL)
				{
					printf ("Please create tree first\n") ;
					break ;
				}
				printf ("Enter the domain name and IP separated by space : ") ;

				fgets (domip , 100 , stdin) ;
				if (strlen(domip) > 0 && (domip[strlen(domip) - 1] == '\n'))
					domip[strlen(domip) - 1] = '\0' ;

				insertdomainip (st , domip) ;
				break ;

			case 3 :
				if (st == NULL)
				{
					printf ("Please create tree first\n") ;
					break ;
				}

				printf ("Enter the domain name only to look up : ") ;
				
				fgets (dom , 100 , stdin) ;
				if (strlen(dom) > 0 && (dom[strlen(dom) - 1] == '\n'))
					dom[strlen(dom) - 1] = '\0' ;

				lk = lookup (st , dom) ;

				if (lk->success)
				{
					//printf ("SUCCESS!\n") ;
					printf ("The number of ip addresses = %d\n" , lk->no_ip) ;
					for (i = 0 ; i < lk->no_ip ; i++)
						printf ("%s\n" , lk->iparr[i]) ;
				}
				else
				{
					printf ("IP Address not found!\n") ;
					for (i = 0 ; i < lk->level ; i++)
					{
						printf ("%d" , lk->breadtharr[i]) ;
						if (i != lk->level -1)
							printf (", ") ;
					}
					printf("\n") ;
				}
				break ;

			case 4 :
				if (st == NULL)
				{
					printf ("Please create tree first\n") ;
					break ;
				}
				
				manual_traverse (st) ;
				break ;

			case 5 :
				cont = 0 ;
				break ;


			default :
				printf ("\n-----------------------------\n") ;
				printf ("Please enter correct option") ;
				printf ("\n-----------------------------\n") ;
		}

		printf("\n") ;

	} while (cont) ;
	
	/*
	int *test ;
	test = (int *) malloc (sizeof(int) * 4) ;
	test[0] = 0 ;
	test[1] = 1 ;
	test[2] = 2 ;
	test[3] = 3 ;

	for (int i = 0 ; i < 4 ; i++)
		printf ("%d\n" , test[i]) ;

	test = (int *) realloc (test , sizeof(int) * 5) ;
	test[4] = 4 ;

	for (int i = 0 ; i < 5 ; i++)
		printf ("%d\n" , test[i]) ;

	*/

	return 0 ;
}