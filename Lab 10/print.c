#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "print.h"

void print_tree_horizontal (struct node* ptr , int space)
{
	if (ptr == NULL)
	{
		print_space (space*2) ;
		printf ("X") ;
		printf ("\n") ;
		return ;
	}

	print_tree_horizontal (ptr->right , space + 1) ;
	print_space (space*2) ;
	print_node (ptr) ;
	printf ("\n") ;
	print_tree_horizontal (ptr->left , space + 1) ;
}

void print_node (struct node* ptr)
{
	if (ptr == NULL)
		printf ("NULL") ;
	else
	{
		//printf ("%d <---- count = %d, left height = %d, right height = %d, height balance = %d" , ptr->val , ptr->count , ptr->lh, ptr->rh , ptr->hb) ;
		printf ("%d" , ptr->val) ;
	}
}

void print_node_detail (struct node *ptr)
{
	printf ("%d  <---- count = %d, left height = %d, right height = %d, height balance = %d" , ptr->val , ptr->count , ptr->lh, ptr->rh , ptr->hb) ;
}

void print_space (int count) 
{
	int i ;

	for (i = 0 ; i < count ; i++)
		printf (" ") ;

	fflush (stdout) ;
}

void print_tree_vertical (struct tree *t)
{
	int i , maxlevel ;
	maxlevel = max (t->root->lh , t->root->rh) ;

	print_space (t->levellists->front->space) ;
	print_node (t->levellists->front->nodeptr) ;
	printf ("\n") ;
	
	for (i = 1 ; i <= maxlevel ; i++)
	{
		print_all_dll_space_edgewise (t->levellists + i , t->levellists + i - 1) ;
		printf ("\n") ;
		print_all_dll_node_edgewise (t->levellists + i) ;
		printf ("\n") ;
	}
}


