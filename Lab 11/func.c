#include <stdio.h>
#include <string.h>
#include "data.h"
#include "func.h"

struct STree* create_tree () 
{
	struct STree* st ;
	st = (struct STree*) malloc (sizeof (struct STree)) ;
	st->root = (struct node *) malloc (sizeof (struct node)) ;
	st->root->str = NULL ;
	st->root->no_children = 0 ;
	st->root->children = NULL ;
	st->root->parent = NULL ;

	return st ;
}

void justenter ()
{
	char ch ;
	scanf ("%c" , &ch) ;
}

int compstr (char *str1 , char *str2)
{
	if (strlen (str1) != strlen (str2))
		return 0 ;
	else
	{
		int i , len = strlen (str1) ;
		for (i = 0 ; i < len ; i++)
		{
			if (tolower(str1[i]) != tolower(str2[i]))
				return 0 ;
		}

		return 1 ;
	}
}


struct node* insertdomparts (struct STree* st , char **domparts , int num)
{
	//printf ("Inside insert domain parts\n") ;
	
	struct node* curr , *prnt , *childptr ;
	int domindex , childindex , child_has_dompart = 0 ;

	curr = st->root ;
	prnt = NULL ;
	for (domindex = num - 1 ; domindex >= 0 ; domindex--)
	{
		child_has_dompart = 0 ;
		for (childindex = 0 ; childindex < curr->no_children ; childindex++)
		{
			childptr = curr->children[childindex] ;
			if (compstr (domparts[domindex] , childptr->str))
			{
				child_has_dompart = 1 ;
				break ;
			}
		}

		if (child_has_dompart)
		{
			prnt = curr ;
			curr = childptr ;
		}
		else
		{
			//realloc
			if (curr->no_children == 0)
				curr->children = (struct node **) malloc (sizeof (struct node*)) ;
			else
				curr->children = (struct node **) realloc (curr->children , sizeof(struct node *) * (curr->no_children + 1)) ;

			childptr = (struct node *) malloc (sizeof (struct node)) ;
			childptr->no_children = 0 ;
			childptr->parent = curr ;
			childptr->children = NULL ;
			childptr->str = (char *) malloc (sizeof (char) * (strlen(domparts[domindex]) + 1)) ;
			strcpy (childptr->str , domparts[domindex]) ;

			curr->children[curr->no_children] = childptr ;
			curr->no_children += 1 ;

			prnt = curr ;
			curr = childptr ;
		}

	}

	return curr ;
}


void insertdomainip (struct STree *st , char *domip)
{
	//printf ("Inside insert domainup\n") ;

	char *tot_tok , *dom , *domcopy,  *ip , *domtok ;
	int no_in_dom = 0 , i = 0 ;
	char **domparts ;
	struct node *last , *ipnode ;


	tot_tok = strtok (domip , " ") ;
	dom = (char *) malloc (sizeof(char) * (strlen(tot_tok)+1)) ;
	domcopy = (char *) malloc (sizeof(char) * (strlen(tot_tok)+1)) ;
	strcpy(dom , tot_tok) ;
	strcpy (domcopy , dom) ;

	tot_tok = strtok (NULL , " ") ;
	ip = (char *) malloc (sizeof(char) * (strlen(tot_tok) + 1)) ;
	strcpy (ip , tot_tok) ;

	//justenter () ;

	tot_tok = strtok (NULL , " ") ; 		//now contains NULL

	//printf ("%s\n" , dom) ;
	//printf ("%s\n" , ip) ;

	//justenter () ;

	domtok = strtok (dom , ".") ;
	while (domtok != NULL)
	{
		//printf ("%s\n" , domtok) ;
		no_in_dom++ ;
		domtok = strtok (NULL , ".") ;
	}

	//printf ("Has calculated number!\n") ;
	//justenter () ;


	domparts = (char **) malloc (no_in_dom * sizeof(char*)) ;
	domtok = strtok (domcopy , ".") ;
	while (domtok != NULL)
	{
		//printf ("%s\n" , domtok) ;
		domparts[i] = (char *) malloc (sizeof(char) * (strlen(domtok) + 1)) ;
		strcpy (domparts[i] , domtok) ;
		domtok = strtok (NULL , ".") ;
		i++ ;
	}

	/*

	for (i = 0 ; i < no_in_dom ; i++)
		printf ("%s\n" , domparts[i]) ;

	printf ("%s\n" , ip) ;

	*/

	last = insertdomparts (st , domparts , no_in_dom) ;
	ipnode = (struct node *) malloc (sizeof(struct node)) ;
	ipnode->str = (char *) malloc (sizeof(char) * (strlen(ip)+1)) ;
	strcpy (ipnode->str , ip) ;
	ipnode->no_children = 0 ;
	ipnode->children = NULL ;
	ipnode->parent = last ;

	last->children = (struct node **) realloc (last->children , sizeof(struct node *) * (last->no_children + 1)) ;
	last->children[last->no_children] = ipnode ;
	last->no_children += 1 ;
	//delete each string in domparts and domparts
}


struct lookupres* lookup (struct STree *st, char *dom)
{
	//printf ("Inside lookup\n") ;
	struct lookupres* lk ;
	struct node *curr, *childptr ;
	char *domtok , *domcopy ;
	char **domparts ;
	int no_in_dom = 0 , domindex, level = 1 , childindex , fail = 0 ;

	curr = st->root ;

	lk = (struct lookupres*) malloc (sizeof(struct lookupres)) ;
	lk->breadtharr = NULL ;
	lk->level = 0 ;
	lk->success = 0 ;
	lk->no_ip = 0 ;
	lk->iparr = NULL ;

	domcopy = (char *) malloc (sizeof (char) * (strlen(dom)+1)) ;
	strcpy (domcopy , dom);

	domtok = strtok (dom , ".") ;
	while (domtok != NULL)
	{
		no_in_dom++ ;
		domtok = strtok (NULL , ".") ;
	}

	domparts = (char **) malloc (no_in_dom * sizeof(char*)) ;
	domtok = strtok (domcopy , ".") ;
	int i = 0 ;
	while (domtok != NULL)
	{
		domparts[i] = (char *) malloc (sizeof(char) * (strlen(domtok) + 1)) ;
		strcpy (domparts[i] , domtok) ;
		//printf ("domparts[%d] = %s\n" , i , domparts[i]) ;
		domtok = strtok (NULL , ".") ;
		i++ ;
	}

	//printf ("No_in_dom = %d" , no_in_dom);
	//justenter () ;

	for (domindex = no_in_dom - 1 ; domindex >= 0 ; domindex--)
	{
		//printf ("For domain part %s\n" , domparts[domindex]) ;
		for (childindex = 0 ; childindex < curr->no_children ; childindex++)
		{
			childptr = curr->children[childindex] ;
			if (compstr (domparts[domindex] , childptr->str))
				break ;
		}

		if (childindex == curr->no_children)
			break ;
		else
		{
			if (level == 1)
				lk->breadtharr = (int *) malloc (sizeof(int)) ;
			else
				lk->breadtharr = (int *) realloc (lk->breadtharr , sizeof(int) * level) ;

			lk->breadtharr[level-1] = curr->no_children ;
			curr = curr->children[childindex] ;
		}
		level++ ;
	}

	level-- ;
	lk->level = level ;

	/*

	printf ("domindex = %d and level = %d\n", domindex , level) ;
	level-- ;

	for (int i = 0 ; i < level ; i++)
		printf ("lk->breadtharr[%d] = %d\n" , i , lk->breadtharr[i]) ;

	printf ("curr->str = %s\n" , curr->str) ;
	*/
	
	if (domindex == -1)
	{
		lk->success = 1 ;
		for (childindex = 0 ; childindex < curr->no_children ; childindex++)
		{
			childptr = curr->children[childindex] ;
			if (childptr->children == NULL)
				lk->no_ip += 1 ;
		}

		lk->iparr = (char **) malloc (sizeof(char*) * lk->no_ip) ;

		int j = 0 ;
		for (childindex = 0 ; childindex < curr->no_children ; childindex++)
		{
			childptr = curr->children[childindex] ;
			if (childptr->children == NULL)
			{
				lk->iparr[j] = (char *) malloc (sizeof(char) * (strlen(childptr->str)+1)) ;
				strcpy (lk->iparr[j] , childptr->str) ;
				j++ ;
			}
		}
	}

	//printf ("lk->no_ip = %d\n" , lk->no_ip) ;
	return lk ;
}



struct node* visit_child_handler (struct node* ptr)
{
	int cont = 1 , childno ;

	do
	{
		printf ("Enter the number of the child to visit (less than %d) : " , ptr->no_children) ;
		scanf ("%d" , &childno) ;

		if (childno <= 0 || childno > ptr->no_children)
		{
			printf ("Incorrect input\n") ;
			continue ;
		}
		else
		{
			ptr = ptr->children[childno - 1] ;
			cont = 0 ;
		}
	} while (cont) ;

	return ptr ;
}

void print_manual_traverse_menu ()
{
	printf ("Enter your option - \n") ;
	printf ("1. Visit Parent\n") ;
	printf ("2. Visit child\n") ;
	printf ("3. Exit\n") ;
}

void printspace (int num)
{
	for (int i = 1 ; i <= num ; i++)
		printf(" ") ;
}


void manual_traverse (struct STree* st)
{
	//printf ("Inside manual_traverse\n\n") ;


	int cont = 1 , option , i ;
	struct node* ptr ;

	ptr = st->root ;
	do
	{
		if (ptr == st->root)
		{
			printspace (8) ;
			printf ("ROOT\n") ;
		}
		else
		{	
			printspace(8) ;
			if (ptr->parent == st->root)
				printf ("ROOT\n") ;
			else
				printf ("%s\n" , ptr->parent->str) ;
			printspace (8) ;
			printf ("|\n") ;
			printspace (8) ;
			printf ("%s <---- Number of children = %d\n" , ptr->str , ptr->no_children) ;
		}

		if (ptr->no_children > 0)
		{
			printspace (8) ;
			for (i = 0 ; i < ptr->no_children ; i++)
			{
				printf ("|") ;
				printspace (strlen(ptr->children[i]->str)) ;
			}
			printf("\n") ;

			printspace(8) ;
			for (i = 0 ; i < ptr->no_children ; i++)
				printf ("%s " , ptr->children[i]->str) ;
		}
		printf ("\n") ;

		print_manual_traverse_menu () ;
		scanf ("%d" , &option) ;

		switch (option)
		{
			case 1 :
				if (ptr->parent == NULL)
				{
					printf ("Already at root. Cannot go up!\n") ;
					break ;
				}

				ptr = ptr->parent ;
				break ;

			case 2 :
				if (ptr == st->root && ptr->no_children == 0)
				{
					printf ("The root has no children\n") ;
					break ;
				}
				if (ptr->children == NULL)
				{
					printf ("It is a leaf node with IP address. No children\n") ;
					break ;
				}

				ptr = visit_child_handler (ptr) ;		//guaranteed to return a node.
				break ;

			case 3 :
				cont = 0 ;
				break ;

			default :
				printf ("\n-----------------------------\n") ;
				printf ("Please enter correct option") ;
				printf ("\n-----------------------------\n") ;
		}

	} while (cont) ;
	
}