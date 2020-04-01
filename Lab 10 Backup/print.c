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
}

int print_tree_vertical_edgewise (struct tree *t, struct node *ptr , char c , int level)
{
	;
}

int print_tree_vertical_centred (struct tree *t, struct node *ptr , char c , int level)
{
	//print_tree_vertical_edgewise (t , ptr , c , level) ;
	;
}
