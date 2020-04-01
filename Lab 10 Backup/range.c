#include <stdlib.h>
#include "data.h"
#include "range.h" 

void find_range (struct node *ptr , int r1 , int r2 , struct dll* rangelist)
{
	if (ptr == NULL)
		return ;

	if (ptr->val < r1)
		find_range (ptr->right , r1 , r2 , rangelist) ;
	else if (ptr->val > r2)
		find_range (ptr->left , r1 , r2 , rangelist) ;
	else
	{
		struct dllnode *ptr1; 
		ptr1 = (struct dllnode *) malloc (sizeof (struct dllnode)) ;
		ptr1->nodeptr = ptr ;
		ptr1->space = -1 ;
		ptr1->prev = NULL ;
		ptr1->next = NULL ;

		insert_inorder_dll (rangelist , ptr1) ;
		//printf ("%d\n" , ptr->val) ;
		find_range (ptr->left , r1 , r2 , rangelist) ;
		find_range (ptr->right , r1 , r2 , rangelist) ;
	}
}
