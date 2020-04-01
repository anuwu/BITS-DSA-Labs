#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "del.h"
#include "util.h"

void del_node (struct tree* t , int val)
{
	struct node *ptr , *prnt , *del ;
	ptr = t->root ;

	while (ptr != NULL)
	{
		if (val < ptr->val)
			ptr = ptr->left ;
		else if (val > ptr->val)
			ptr = ptr->right ;
		else
		{
			if (ptr->count > 1)
			{
				printf ("Multiple occurences. Trivial\n") ;
				ptr->count -= 1 ;			
				return ;
			}
			else
			{
				if (ptr->left == NULL && ptr->right == NULL)		//Leaf node.
				{
					printf ("Leaf node\n") ;
					prnt = ptr->parent ;

					if (prnt == NULL)
					{
						free (ptr) ;
						t->root = NULL ;
					}
					else
					{
						if (ptr == prnt->left)
						{
							prnt->lh -= 1 ;
							prnt->left = NULL ;
						}
						else
						{
							prnt->rh -= 1 ;
							prnt->right = NULL ;
						}

						prnt->hb = prnt->rh - prnt->lh ;
						update_balance(prnt) ;
					}
				}
				else if (ptr->left == NULL)						//Right child only
				{
					printf ("Has right child only\n") ;
					transplant (t , ptr , ptr->right) ;

					prnt = ptr->parent ;
					if (prnt != NULL)
					{
						if (ptr->right == prnt->left)
							prnt->lh -= 1 ;
						else
							prnt->rh -= 1 ;

						prnt->hb = prnt->rh - prnt->lh ;
						update_balance(prnt) ;
					}


				}
				else if (ptr->right == NULL)				//Left child only.
				{
					printf ("Has left node only\n") ;
					transplant (t , ptr , ptr->left) ;

					prnt = ptr->parent ;

					if (prnt != NULL)
					{
						if (ptr->left == prnt->left)
							prnt->lh -= 1 ;
						else
							prnt->rh -= 1 ;

						prnt->hb = prnt->rh - prnt->lh ;
						update_balance(prnt) ;
					}
				}
				else														//node to be deleted has both children.
				{
					//call to tree_min is guaranteed to return a non-NULL node. This might be the node's right child or not.
					printf ("Has both children\n") ;
					struct node* succ ;
					succ = tree_min (ptr->right) ;

					if (succ->parent == ptr)
					{
						printf ("Successor is right child!\n") ;

						transplant (t , ptr , succ) ;
						succ->left = ptr->left ;
						ptr->left->parent = succ;
						succ->lh = ptr->lh ;
						succ->hb = succ->rh - succ->lh ;


						del = ptr ;
						free (del) ;
						update_balance(succ) ;
					}
					else
					{	
						printf ("Successor is not right child!\n") ;

						transplant (t , succ , succ->right) ;
						ptr->val = succ->val ;
						ptr->count = succ->count ;
						prnt = succ->parent ;
						prnt->lh -= 1 ;

						del = succ ;
						free (del) ;
						prnt->hb = prnt->rh - prnt->lh ;
						update_balance (prnt) ;
					}
				}
			}

			t->no -= 1 ;
			return ;

		}

	}

	if (ptr == NULL)
		printf ("Node doesn't exist in the tree\n") ;
}

void del_tree (struct node *ptr)
{
	if (ptr == NULL)
	{
		//printf("Null node\n") ;
		return ;
	}

	struct node *l , *r ;
	l = ptr->left ;
	r = ptr->right ;

	//printf ("%d\n" , ptr->val) ;
	free (ptr) ;
	del_tree(l) ;
	del_tree(r) ;
	//	printf ("GOT YA!\n") ;
}

void del_node_bal (struct tree *t , int val)
{
	struct node *ptr , *prnt , *del ;
	ptr = t->root ;

	while (ptr != NULL)
	{
		if (val < ptr->val)
			ptr = ptr->left ;
		else if (val > ptr->val)
			ptr = ptr->right ;
		else
		{
			if (ptr->count > 1)
			{
				printf ("Multiple occurences. Trivial\n") ;
				ptr->count -= 1 ;			
				return ;
			}
			else
			{
				struct node *x , *y , *z ;

				if (ptr->left == NULL && ptr->right == NULL)		//Leaf node.
				{
					printf ("Leaf node\n") ;
					prnt = ptr->parent ;

					if (prnt == NULL)
					{
						free (ptr) ;
						t->root = NULL ;
						z = NULL ;
					}
					else
					{
						if (ptr == prnt->left)
						{
							prnt->lh -= 1 ;
							prnt->left = NULL ;
						}
						else
						{
							prnt->rh -= 1 ;
							prnt->right = NULL ;
						}

						prnt->hb = prnt->rh - prnt->lh ;
						update_balance(prnt) ;

						z = find_z(prnt) ;

						//printf("Non-root lead node\n") ;
					}
				}
				else if (ptr->left == NULL)						//Right child only
				{
					printf ("Has right child only\n") ;
					transplant (t , ptr , ptr->right) ;

					prnt = ptr->parent ;
					if (prnt != NULL)
					{
						if (ptr->right == prnt->left)
							prnt->lh -= 1 ;
						else
							prnt->rh -= 1 ;

						prnt->hb = prnt->rh - prnt->lh ;
						update_balance(prnt) ;

						z = find_z (prnt) ;
					}
					else
						z = NULL ;
				}
				else if (ptr->right == NULL)				//Left child only.
				{
					printf ("Has left node only\n") ;
					transplant (t , ptr , ptr->left) ;

					prnt = ptr->parent ;

					if (prnt != NULL)
					{
						if (ptr->left == prnt->left)
							prnt->lh -= 1 ;
						else
							prnt->rh -= 1 ;

						prnt->hb = prnt->rh - prnt->lh ;
						update_balance(prnt) ;

						z = find_z (prnt) ;
					}
					else
						z = NULL ;
				}
				else														//node to be deleted has both children.
				{
					//call to tree_min is guaranteed to return a non-NULL node. This might be the node's right child or not.
					printf ("Has both children\n") ;
					struct node* succ ;
					succ = tree_min (ptr->right) ;

					if (succ->parent == ptr)
					{
						printf ("Successor is right child!\n") ;

						transplant (t , ptr , succ) ;
						succ->left = ptr->left ;
						ptr->left->parent = succ;
						succ->lh = ptr->lh ;
						succ->hb = succ->rh - succ->lh ;


						del = ptr ;
						free (del) ;
						update_balance(succ) ;

						z = find_z (succ) ;
					}
					else
					{	
						printf ("Successor is not right child!\n") ;

						transplant (t , succ , succ->right) ;
						ptr->val = succ->val ;
						ptr->count = succ->count ;
						prnt = succ->parent ;
						prnt->lh -= 1 ;

						del = succ ;
						free (del) ;
						prnt->hb = prnt->rh - prnt->lh ;
						update_balance (prnt) ;

						z = find_z(prnt->left) ;
					}
				}

				/********************
				Maintaining balanced property here
				*********************/

				if (z != NULL)
				{
					if (z->lh > z->rh)
						y = z->left ;
					else
						y = z->right ;

					if (y->lh > y->rh)
						x = y->left ;
					else
						x = y->right ;

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

			t->no -= 1 ;
			return ;
		}

	}

	if (ptr == NULL)
		printf ("Node doesn't exist in the tree\n") ;
}