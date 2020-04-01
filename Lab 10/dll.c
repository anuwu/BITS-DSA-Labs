#include <stdlib.h>
#include <stdio.h>
#include "data.h"
#include "dll.h"


void insert_inorder_dll (struct dll *list, struct dllnode *ptr)
{
	if (list->count == 0)
	{
		list->front = ptr ;
		list->rear = ptr ;
		list->count += 1 ;
	}
	else if (ptr->nodeptr->val <= list->front->nodeptr->val)
		insert_front_dll (list , ptr) ;
	else if (ptr->nodeptr->val > list->rear->nodeptr->val)
		insert_rear_dll (list , ptr) ;
	else
	{
		struct dllnode *curr, *prev ;
		prev = NULL ;
		curr = list->front ;

		while (ptr->nodeptr->val > curr->nodeptr->val)
		{
			prev = curr ;
			curr = curr->next ;
		}

		ptr->prev = prev ;
		ptr->next = curr ;
		prev->next = ptr ;
		curr->prev = ptr ;

		list->count += 1 ;
	}

}

void insert_front_dll (struct dll *list , struct dllnode *ptr)
{
	//Will only be called after list has one element
	if (list->front == NULL)
	{
		list->front = ptr ;
		list->rear = ptr ;
	}
	else
	{
		ptr->next = list->front ;
		list->front->prev = ptr ;
		list->front = ptr ;
	}

	list->count += 1 ;
}

void insert_rear_dll (struct dll *list , struct dllnode *ptr)
{
	if (list->rear == NULL)
	{
		list->front = ptr ;
		list->rear = ptr ;
	}
	else
	{
		ptr->prev = list->rear ;
		list->rear->next = ptr ;
		list->rear = ptr ;
	}

	list->count += 1 ;
}

void del_all_dll (struct dll *list)
{
	if (list == NULL)		//For precaution, but list can never be NULL
		return ;
	else if (list->front == NULL)
		return ;

	struct dllnode *curr , *del ;
	curr = list->front ;

	while (curr != NULL)
	{
		del = curr ;
		curr = curr->next ;

		free (del) ;
	}

	list->count = 0 ;
}

void del_front_dll (struct dll *list)
{
	if (list == NULL)		//For precaution, but list can never be NULL
		return ;
	else if (list->front == NULL)
		return ;

	if (list->front == list->rear)
	{
		free (list->front) ;
		list->front = NULL ;
		list->rear = NULL ;
	}
	else
	{
		struct dllnode *del ;
		del = list->front ;

		list->front = del->next ;
		list->front->prev = NULL ;
		free (del) ;
	}

	list->count -= 1 ;
}

void del_rear_dll (struct dll *list)
{
	if (list == NULL)		//For precaution, but list can never be NULL
		return ;
	else if (list->rear == NULL)
		return ;

	if (list->front == list->rear)
	{
		free (list->front) ;
		list->front = NULL ;
		list->rear = NULL ;
	}
	else
	{
		struct dllnode *del ;
		del = list->rear ;

		list->rear = del->prev ;
		list->rear->next = NULL ;
		free (del) ;
	}

	list->count -= 1 ;
}

void del_ptr_dll (struct dll *list , int val)
{
	if (list == NULL)		//For precaution, but list can never be NULL
		return ;
	else if (list->front == NULL)
		return ;

	struct dllnode *curr, *prev, *del ;

	prev = NULL ;
	curr = list->front ;
	while (curr != NULL)
	{
		if (curr->nodeptr->val == val)
		{
			if (list->count == 1 || prev == NULL)
				del_front_dll (list) ;
			else if (curr->next == NULL)
				del_rear_dll (list) ;
			else
			{
				del = curr ;

				curr->next->prev = prev ;
				prev->next = curr->next ;
				free (del) ;

				list->count -= 1 ;
			}
		}

		prev = curr ;
		curr = curr->next ;
	}
}

struct dllnode* pop_front_dll (struct dll *list)
{
	if (list == NULL)		//For precaution, but list can never be NULL
		return NULL ;
	else if (list->front == NULL)
		return NULL ;

	struct dllnode *ret ;
	list->count -= 1 ;
	if (list->front == list->rear)
	{
		ret = list->front ;
		list->front = NULL ;
		list->rear = NULL ;

		return ret ;
	}
	else
	{
		ret = list->front ;
		list->front = list->front->next ;
		list->front->prev = NULL ;

		return ret ;
	}
}

struct dllnode* pop_rear_dll (struct dll *list)
{
	if (list == NULL)		//For precaution, but list can never be NULL
		return NULL ;
	else if (list->front == NULL)
		return NULL ;

	struct dllnode *ret ;
	list->count -= 1 ;
	if (list->front == list->rear)
	{
		ret = list->front ;
		list->front = NULL ;
		list->rear= NULL ;

		return ret ;
	}
	else
	{
		ret = list->rear ;
		list->rear = list->rear->prev ;
		list->rear->next = NULL ;

		return ret ;
	}
}

void print_all_dll (struct dll *list)
{
	struct dllnode *ptr ;

	ptr = list->front ;
	while (ptr != NULL)
	{
		printf ("%d(%d)" , ptr->nodeptr->val , ptr->space) ;
		if (ptr->next != NULL)
			printf (", ") ;

		ptr = ptr->next ;
	}
}

void print_all_dll_space_edgewise (struct dll *list , struct dll *prntlist)
{
	struct dllnode *ptr, *prev , *prnt ;
	char ptr_c , prev_c ;
	int prev_space , ptr_space ;

	ptr = list->front ;
	ptr_c = node_type (ptr->nodeptr) ;
	prnt = ret_ptr_dll (prntlist , ptr->nodeptr->parent->val) ;

	if (ptr_c == 'l')
	{
		ptr_space = (ptr->space + get_nodelength(ptr->nodeptr) + prnt->space)/2 ;
		print_space (ptr_space) ;
		printf ("/") ;
	}
	else
	{
		ptr_space = (ptr->space + get_nodelength(prnt->nodeptr) + prnt->space)/2 ;
		print_space (ptr_space) ;
		printf ("\\") ;
	}

	prev = ptr ;
	ptr = ptr->next ;

	while (ptr != NULL)
	{
		prev_c = ptr_c ;
		ptr_c = node_type (ptr->nodeptr) ;
			
		prnt = ret_ptr_dll (prntlist , ptr->nodeptr->parent->val) ;
		prev_space = ptr_space ;

		if (ptr_c == 'l')
		{
			ptr_space = (ptr->space + get_nodelength(ptr->nodeptr) + prnt->space)/2 ;
			print_space (ptr_space - prev_space - 1) ;
			printf ("/") ;
		}
		else
		{
			ptr_space = (ptr->space + get_nodelength(prnt->nodeptr) + prnt->space)/2 ;
			print_space (ptr_space - prev_space - 1) ;
			printf ("\\") ; 
		}
		prev = ptr ;
		ptr = ptr->next ;
	}
}

void print_all_dll_node_edgewise (struct dll *list)
{
	struct dllnode *ptr , *prev ;

	ptr = list->front ;
	print_space (ptr->space) ;
	print_node (ptr->nodeptr) ;

	prev = ptr ;
	ptr = ptr->next ;

	while (ptr != NULL)
	{
		print_space (ptr->space - prev->space - get_nodelength (prev->nodeptr)) ;
		print_node (ptr->nodeptr) ;

		prev = ptr ;
		ptr = ptr->next ;
	}
}

struct dllnode* ret_ptr_dll (struct dll *list , int val)
{
	struct dllnode *ptr ;
	ptr = list->front ;

	while (ptr->nodeptr->val != val)
		ptr = ptr->next ;

	return ptr ;
}
