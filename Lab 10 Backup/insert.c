#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "util.h"
#include "insert.h"

void add (struct tree *t , int val)
{
	if (t->root == NULL)
	{
		t->root = (struct node*) malloc (sizeof(struct node)) ;

		t->root->val = val ;
		t->root->lh = 0 ;
		t->root->rh = 0 ;
		t->root->hb = 0 ;
		//t->root->space = 0 ;
		t->root->count = 1 ;

		t->root->left = NULL ;
		t->root->right = NULL ;
		t->root->parent = NULL ;

		printf ("Root created!\n") ;
	}
	else
	{
		struct node *ptr , *prnt ;
		ptr = t->root ;
		prnt = ptr ;

		while (ptr != NULL)
		{
			if (val < ptr->val)
			{
				prnt = ptr ;
				ptr = ptr->left ;
			}
			else if (val > ptr->val)
			{
				prnt = ptr ;
				ptr = ptr->right ;
			}
			else	//Value has been encountered before. Increase count by one.
			{
				ptr->count += 1 ;
				printf ("Count of already existing node incremented\n") ;
				break ;
			}
		}

		if (ptr == NULL)
		{

			//Value has not been encountered before. Need to insert a new node as ptr is null.
			ptr = (struct node*) malloc (sizeof(struct node)) ;
			ptr->val = val ;
			ptr->lh = 0 ;
			ptr->rh = 0 ;
			ptr->hb = 0 ;
			ptr->count = 1 ;
			//ptr->space = 0 ;

			ptr->left = NULL ;
			ptr->right = NULL ;
			ptr->parent = prnt ;

			if (val < prnt->val)
			{
				prnt->left = ptr ;
				prnt->lh = 1 ;
			}
			else
			{
				prnt->right = ptr ;
				prnt->rh = 1 ;
			}

			prnt->hb = prnt->rh - prnt->lh ;
			printf ("New node added!\n") ;
			update_balance (prnt) ;
		}
	}

	t->no += 1 ;
}

struct node* find_y_add (struct node *ptr , struct node *z)
{
	while (ptr->parent != z)
		ptr = ptr->parent ;

	return ptr ;
}

struct node* find_x_add (struct node *ptr , struct node *y)
{
	while (ptr->parent != y)
		ptr = ptr->parent ;

	return ptr ;
}

void add_bal (struct tree *t , int val)
{
	if (t->root == NULL)
	{
		t->root = (struct node*) malloc (sizeof(struct node)) ;

		t->root->val = val ;
		t->root->lh = 0 ;
		t->root->rh = 0 ;
		t->root->hb = 0 ;
		t->root->count = 1 ;
		//t->root->space = 0 ;

		t->root->left = NULL ;
		t->root->right = NULL ;
		t->root->parent = NULL ;

		printf ("Root created!\n") ;
	}
	else
	{
		struct node *ptr , *prnt ;
		ptr = t->root ;
		prnt = ptr ;

		while (ptr != NULL)
		{
			if (val < ptr->val)
			{
				prnt = ptr ;
				ptr = ptr->left ;
			}
			else if (val > ptr->val)
			{
				prnt = ptr ;
				ptr = ptr->right ;
			}
			else	//Value has been encountered before. Increase count by one.
			{
				ptr->count += 1 ;
				printf ("Count of already existing node incremented\n") ;
				break ;
			}
		}

		if (ptr == NULL)
		{
			//Value has not been encountered before. Need to insert a new node as ptr is null.
			struct node *z ,*y , *x ;
			ptr = (struct node*) malloc (sizeof(struct node)) ;
			ptr->val = val ;
			ptr->lh = 0 ;
			ptr->rh = 0 ;
			ptr->hb = 0 ;
			ptr->count = 1 ;
			//ptr->space = 0 ;

			ptr->left = NULL ;
			ptr->right = NULL ;
			ptr->parent = prnt ;

			if (val < prnt->val)
			{
				prnt->left = ptr ;
				prnt->lh = 1 ;
			}
			else
			{
				prnt->right = ptr ;
				prnt->rh = 1 ;
			}

			prnt->hb = prnt->rh - prnt->lh ;
			printf ("New node added!\n") ;
			update_balance (prnt) ;

			

			/********************
			Maintaining balanced property here
			*********************/


			z = find_z(ptr) ;
			if (z != NULL)
			{
				printf ("There is imbalance!\n") ;
				just_enter () ;

				y = find_y_add(ptr , z) ;
				x = find_x_add(ptr , y) ;
				//printf ("x = %d , y = %d , z = %d\n" , x->) ;
				//just_enter () ;

				int cas ;	//1 - LL, 2 - LR, 3 - RR, 4 - RL
				if (z->left == y && y->left == x)
					cas = 1 ;
				if (z->left == y && y->right == x)
					cas = 2 ;
				if (z->right == y && y->right == x)
					cas = 3 ;
				if (z->right == y && y->left == x)
					cas = 4 ;

				switch (cas)
				{
					case 1 :
						right_rotate (t , z) ;
						break ;

					case 2 :
						left_rotate (t , y) ;
						right_rotate (t , z) ;
						break ;

					case 3 :
						left_rotate (t , z) ;
						break ;

					case 4 :
						right_rotate (t , y) ;
						left_rotate (t , z) ;
						break ;
				}
			}
		}
	}

	t->no += 1 ;
}
