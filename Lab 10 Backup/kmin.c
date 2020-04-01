#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "kmin.h"


struct node* k_bottom_inorder (struct node *ptr , int cnt , int order)
{
	if (cnt == order)
		return ptr ;

	if (ptr->right == NULL)
	{
		struct node *upto ;
		upto = ptr->parent ;

		while (upto->right == ptr)
		{
			ptr = upto ;
			upto = upto->parent ;
		}

		return k_bottom_inorder (ptr->parent , cnt+1 , order) ;
	}
	else
	{
		struct node *leftmost ;
		leftmost = ptr->right ;

		while (leftmost->left != NULL)
			leftmost = leftmost->left ;

		return k_bottom_inorder (leftmost , cnt+1 , order) ;
	}
}

struct node* find_kmin (struct tree *t , int k)
{
	struct node *ptr ;

	ptr = tree_min (t->root) ;
	return k_bottom_inorder (ptr , 1 , k) ;


}


