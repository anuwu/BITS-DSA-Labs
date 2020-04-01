#include <stdlib.h>
#include "data.h"
#include "find.h"

struct node* find (struct tree* t , int val)
{
	struct node* ptr ;
	ptr = t->root ;

	while (ptr != NULL)
	{
		if (val < ptr->val)
			ptr = ptr->left ;
		else if (val > ptr->val)
			ptr = ptr->right ;
		else
		{
			return ptr ;
		}
	}

	return ptr ;
}
