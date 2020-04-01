#include <stdlib.h>
#include <stdio.h>
#include "data.h"
#include "breadth.h"

void delete_all_levellists (struct tree *t) 
{
	if (t == NULL)		//If tree is empty
		return ;
	else if (t->levellists == NULL)		//If the dll array hasn't been malloced
		return ;

	//Proceed only if dll has been malloced. This ensures that levellists[i] is a valid memory location.

	int i , maxlevel ;
	maxlevel = max (t->root->lh , t->root->rh) ;
	
	for (i = 0 ; i <= maxlevel ; i++)
		del_all_dll (t->levellists + i) ;
}

void create_all_simple_levellists (struct tree *t)
{
	if (t == NULL)		//If no tree has been created in the first place
		return ;
	else if (t->root == NULL)		//If the tree has no elements
		return ;

	delete_all_levellists (t) ;		//Will delete the previously created levellists and start fresh. If invoked for the first time, won't do anything.

	int i , maxlevel, levelcnt ;
	struct dll *temp1 , *temp2 ;
	struct dllnode *bufptr, *bufptrchild ;
	struct node *child ;

	maxlevel = max (t->root->lh , t->root->rh) ;
	t->levellists = (struct dll *) malloc ((maxlevel + 1) * sizeof (struct dll)) ;
	for (i = 0 ; i <= maxlevel ; i++)		//Initializing the levellists
	{	
		t->levellists[i].front = NULL ;
		t->levellists[i].rear = NULL ;
		t->levellists[i].count = 0 ;
	}
	
	//Initialising temp lists
	temp1 = (struct dll *) malloc (sizeof (struct dll)) ;
	temp2 = (struct dll *) malloc (sizeof (struct dll)) ;
	temp1->front = NULL ;
	temp1->rear = NULL ;
	temp1->count = 0 ;
	temp2->front = NULL ;
	temp2->rear = NULL ;
	temp2->count = 0 ;
	
	bufptr = (struct dllnode *) malloc (sizeof (struct dllnode)) ;
	bufptr->nodeptr = t->root ;
	bufptr->space = -1 ;
	bufptr->prev = NULL ;
	bufptr->next = NULL ;

	insert_front_dll (temp1 , bufptr) ;
	levelcnt = 0 ;
	while (temp1->front != NULL)
	{
		while (temp1->front != NULL)
		{
			bufptr = pop_front_dll (temp1) ;
			insert_rear_dll (t->levellists + levelcnt , bufptr) ;
			insert_rear_dll (temp2 , bufptr) ;

			//printf ("%d , " , bufptr->nodeptr->val) ;
		}
		//printf ("\n") ;

		while (temp2->front != NULL) 
		{
			bufptr = pop_front_dll (temp2) ;

			child = bufptr->nodeptr->left ;
			if (child != NULL)	//insert only if left child is not null
			{
				bufptrchild = (struct dllnode *) malloc (sizeof (struct dllnode)) ;
				bufptrchild->nodeptr = child ;
				bufptrchild->space = -1 ;
				bufptrchild->prev = NULL ;
				bufptrchild->next = NULL ;

				insert_rear_dll (temp1 , bufptrchild) ;
			}

			child = bufptr->nodeptr->right ;
			if (child != NULL)		//insert only if right child is not null
			{
				bufptrchild = (struct dllnode *) malloc (sizeof (struct dllnode)) ;
				bufptrchild->nodeptr = child ;
				bufptrchild->space = -1 ;
				bufptrchild->prev = NULL ;
				bufptrchild->next = NULL ;

				insert_rear_dll (temp1 , bufptrchild) ;
			}	
		}

		levelcnt++ ;	
	}
}

int create_all_space_levellists_edgewise (struct tree *t, struct node *ptr , char c , int level , int init_space)
{	
	if (ptr == NULL)		//Base case
		return 0 ;

	int left_subtree_space , childlength , right_subtree_space ;
	struct dllnode *retnode ;

	/*---------------------- left subtree call ----------------------*/
	left_subtree_space = 0 ;
	childlength = get_nodelength (ptr->left) ;
	left_subtree_space = create_all_space_levellists_edgewise (t , ptr->left , 'l' , level + 1 , init_space) ;
	if (childlength > 0)
		left_subtree_space++ ;
	/*---------------------- left subtree call ----------------------*/






	/*---------------------- present node value update ----------------------*/
	retnode = ret_ptr_dll (t->levellists + level , ptr->val) ;
	retnode->space = left_subtree_space + init_space ;
	/*---------------------- present node value update ----------------------*/



	//printf ("%d|%d , " , retnode->nodeptr->val , retnode->space) ;


	/*---------------------- right subtree call ----------------------*/
	right_subtree_space = create_all_space_levellists_edgewise (t , ptr->right , 'r' , level + 1 , retnode->space + get_nodelength(ptr) + 1) ;
	/*---------------------- right subtree call ----------------------*/
	
	
	//if (right_subtree_space != 0)
	//	printf ("RSS = %d\n" , right_subtree_space) ;



	/*---------------------- return cases ----------------------*/
	if (c == 'l' || c == 'x')
	{
		if (ptr->right == NULL)
			return left_subtree_space + get_nodelength (ptr)  ;
		else
			return left_subtree_space + right_subtree_space - (retnode->space + get_nodelength (ptr)) ;			
	}
	else if (c == 'r')
	{
		if (ptr->right == NULL)
			return retnode->space + get_nodelength (ptr) ;
		else
			return right_subtree_space ;
	}
	/*---------------------- return cases ----------------------*/
}

int create_all_space_levellists_centred (struct tree *t, struct node *ptr , char c , int level , int init_space)
{
	if (ptr == NULL)		//Base case
		return 0 ;

	int left_subtree_space , childlength , right_subtree_space ;
	struct dllnode *retnode ;

	/*---------------------- left subtree call ----------------------*/
	left_subtree_space = 0 ;
	childlength = get_nodelength (ptr->left) ;
	left_subtree_space = create_all_space_levellists_centred (t , ptr->left , 'l' , level + 1 , init_space) ;
	if (childlength > 0)
		left_subtree_space++ ;
	/*---------------------- left subtree call ----------------------*/






	/*---------------------- present node value update ----------------------*/
	retnode = ret_ptr_dll (t->levellists + level , ptr->val) ;
	retnode->space = left_subtree_space + init_space ;
	/*---------------------- present node value update ----------------------*/



	//printf ("%d|%d , " , retnode->nodeptr->val , retnode->space) ;


	/*---------------------- right subtree call ----------------------*/
	right_subtree_space = create_all_space_levellists_centred (t , ptr->right , 'r' , level + 1 , retnode->space + get_nodelength(ptr) + 1) ;
	/*---------------------- right subtree call ----------------------*/
	
	
	//if (right_subtree_space != 0)
	//	printf ("RSS = %d\n" , right_subtree_space) ;



	/*---------------------- return cases ----------------------*/
	if (c == 'l' || c == 'x')
	{
		if (ptr->right == NULL)
			return left_subtree_space + get_nodelength (ptr)  ;
		else
			return left_subtree_space + right_subtree_space - (retnode->space + get_nodelength (ptr)) ;			
	}
	else if (c == 'r')
	{
		if (ptr->left == NULL && ptr->right == NULL)
			return retnode->space + get_nodelength (ptr) ;
		else
			return right_subtree_space ;
	}
	/*---------------------- return cases ----------------------*/
}

void print_all_levellists (struct tree *t)
{
	//create_all_simple_levellists (t) ;

	int i , maxlevel ;
	maxlevel = max (t->root->lh , t->root->rh) ;

	for (i = 0 ; i <= maxlevel ; i++)
	{
		printf ("Level %d\n\n" , i) ;
		print_all_dll (t->levellists + i) ;
		printf ("\n") ;
		printf ("--------------------------------------------------\n") ;
	}
}

void del_all_levellists (struct tree *t)
{
	int i , maxlevel ;

	maxlevel = max (t->root->lh , t->root->rh) ;
	for (i = 0 ; i <= maxlevel ; i++)
		del_all_dll (t->levellists + i) ;
	
	free(t->levellists) ;
}
