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
