#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "util.h"

int max (int x , int y)
{
	if (x > y)
		return x ;
	else if (x < y)
		return y ;
	else
		return x ;
}

int ret_lh (struct node* ptr)
{
	if (ptr == NULL)
		return -1 ;
	else
		return ptr->lh ;
}

int ret_rh (struct node* ptr)
{
	if (ptr == NULL)
		return -1 ;
	else
		return ptr->rh ;
}

struct node* tree_min (struct node* succ)
{
	while (succ->left != NULL)
		succ = succ->left ;

	return succ ;
}

struct node* find_z (struct node *ptr)
{
	while (ptr != NULL)
	{
		if (ptr->hb > 1 || ptr->hb < -1)
			return ptr ;
		ptr = ptr->parent ;
	}

	return ptr ;
}

void transplant (struct tree *t , struct node *u , struct node *v)		//u cannot be NULL. v can be NULL.
{
	printf ("Transplanting!\n") ;

	if (u->parent == NULL)
		t->root = v ;
	else if (u == u->parent->left)
		u->parent->left = v ;
	else
		u->parent->right = v ;

	if (v != NULL)
		v->parent = u->parent ;
}

void update_balance (struct node *ptr)
{
	//Edit - works on the same principle as update_balanctf ("Added info!\n") ;

	struct node* prnt ;
	//char ch ; 

	prnt = ptr->parent ;

	while (prnt != NULL)
	{
		if (ptr == prnt->left)
			prnt->lh = max(ret_lh(ptr) , ret_rh(ptr)) + 1 ;
		else
			prnt->rh = max(ret_lh(ptr) , ret_rh(ptr)) + 1 ;

		prnt->hb = prnt->rh - prnt->lh ;
		ptr = prnt ;
		prnt = prnt->parent ;
	}
}

void left_rotate (struct tree *t , struct node* x)
{
	struct node *beta,  *y ;

	beta = x->right->left ;
	y = x->right ;

	x->right = y->left ;
	if (y->left != NULL)
		y->left->parent = x ;

	y->parent = x->parent ;
	if (x->parent == NULL)
		t->root = y ;
	else if (x == x->parent->left)
		x->parent->left = y ;
	else
		x->parent->right = y ;

	y->left = x ;
	x->parent = y ;

	x->rh = max(ret_lh(beta) , ret_rh(beta)) + 1 ;
	x->hb = x->rh - x->lh ;
	update_balance (x) ;
}

void right_rotate (struct tree *t , struct node *x)
{
	struct node *gamma, *y ;

	gamma = x->left->right ;
	y = x->left ;

	x->left = y->right ;
	if (y->right != NULL)
		y->right->parent = x ;

	y->parent = x->parent ;
	if (x->parent == NULL)
		t->root = y ;
	else if (x == x->parent->left)
		x->parent->left = y ;
	else
		x->parent->right = y ;

	y->right = x ;
	x->parent = y ;

	x->lh = max(ret_lh(gamma) , ret_rh(gamma)) + 1 ;
	x->hb = x->rh - x->lh ;
	update_balance (x) ;
}

void just_enter ()
{
	char ch ;
	scanf ("%c" , &ch) ;
}

void enter ()
{
	printf ("Press enter to continue\n") ;
	just_enter () ;
}

int get_nodelength (struct node *ptr)
{
	if (ptr == NULL)
		return 0 ;

	int num , dig ;

	num = ptr->val ;
	dig = 0 ;

	while (num != 0)
	{
		num = num/10 ;
		dig++ ;
	}

	return dig ;
}

char node_type (struct node *ptr)
{
	//ptr cannot be root

	if (ptr == NULL)
		return '\0' ;

	if (ptr == ptr->parent->left)
		return 'l' ;
	else
		return 'r' ;
}

void all_bal (struct tree *t , struct node *ptr)
{	
	if (ptr->hb == 1)
		left_rotate (t , ptr) ;
	else if (ptr->hb == -1)
		right_rotate (t , ptr) ;

	if (ptr->hb >= 2)
		all_bal (t , ptr->right) ;
	else if (ptr->hb <= -2)
		all_bal (t , ptr->left) ;

}
