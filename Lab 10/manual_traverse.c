#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "print.h"
#include "util.h"
#include "del.h"
#include "manual_traverse.h"

void del_node_manual (struct tree* t , int val , int always_balance)
{
	if (always_balance == 1)
		del_node_bal (t , val) ;
	else
		del_node (t , val) ;
}

void print_manual_traverse_menu ()
{
	printf ("1. Visit left node\n") ;
	printf ("2. Visit right node\n") ;
	printf ("3. Visit parent\n") ;
	printf ("4. Back to root\n") ;
	printf ("5. Rotate left\n") ;
	printf ("6. Rotate right\n") ;
	printf ("7. Delete node\n") ;
	printf ("8. Exit\n") ;
}

int get_nodespace (struct node *ptr)
{
	if (ptr == NULL)
		return 4 ;
	else
	{
		int num, dig ;

		num = ptr->val ;
		dig = 0 ;

		while (num != 0)
		{
			dig++ ;
			num /= 10 ;
		}

		return dig ;
	}
}

void print_manual_traverse_node (struct tree *t , struct node *ptr)
{
	int leftspace ;
	int ptrspace ;

	if (ptr == t->root)
	{
		leftspace = get_nodespace (ptr->left) ;
		ptrspace = get_nodespace (ptr) ;

		print_space (leftspace + 1) ;		//printing NULL above root
		printf ("NULL") ;
		printf ("\n") ;

		print_space (leftspace + 1) ;		//printing vertical line
		printf ("|") ;
		printf ("\n") ;

		print_space (leftspace + 1) ;		//printing root
		print_node_detail (ptr) ;
		printf ("\n") ;

		print_space (leftspace) ;			//printing lines below root
		printf ("/") ;
		print_space (ptrspace) ;
		printf ("\\") ;
		printf ("\n") ;

		print_node (ptr->left) ;			//printing left and right children
		print_space (ptrspace + 1) ;
		print_node (ptr->right) ;

	}
	else if (ptr == ptr->parent->left)
	{
		leftspace = get_nodespace (ptr->left) ;
		ptrspace = get_nodespace (ptr) ;

		print_space (leftspace + 1 + ptrspace + 1) ;		//printing left parent
		print_node (ptr->parent) ;
		printf ("\n") ;

		print_space (leftspace + 1 + ptrspace) ;			//printing front slash
		printf ("/") ;
		printf ("\n") ;

		print_space (leftspace + 1) ;						//printing node
		print_node_detail (ptr) ;
		printf ("\n") ;

		print_space (leftspace) ;							//printing lines below node
		printf ("/") ;
		print_space (ptrspace) ;
		printf ("\\") ;
		printf ("\n") ;

		print_node (ptr->left) ;							//printing left and right children
		print_space (1 + ptrspace + 1) ;
		print_node (ptr->right) ;

	}
	else 
	{
		//printf ("AT RighT CHiLD CONDITION\n") ;
		//just_enter () ;
		int parentspace ;

		parentspace = get_nodespace (ptr->parent) ;
		leftspace = get_nodespace (ptr->left) ;
		ptrspace = get_nodespace (ptr) ;

		if (leftspace > parentspace)
		{
			//printf ("Left space > parent space\n") ;
			//just_enter () ;

			print_space (leftspace - parentspace) ;		//printing parent
			print_node (ptr->parent) ;
			printf ("\n") ;

			//just_enter () ;

			print_space (leftspace) ;				//printing backslash
			printf ("\\") ;
			printf ("\n") ;

			//just_enter () ;

			print_space (leftspace + 1) ;			//printing node
			print_node_detail (ptr) ;
			printf ("\n") ;

			//just_enter () ;

			print_space (leftspace) ;				//printing lines below node
			printf ("/") ;
			print_space (ptrspace) ;
			printf ("\\") ;
			printf ("\n") ;

			//just_enter () ;

			print_node (ptr->left) ;
			print_space (1 + ptrspace + 1) ;
			print_node (ptr->right) ;

			//just_enter () ;
		}
		else
		{	
			//printf ("Left space <= parent space\n") ;
			//just_enter () ;

			print_node (ptr->parent) ;				//printing parent
			printf ("\n") ;

			//just_enter () ;

			print_space (parentspace) ;				//printing backslash
			printf ("\\") ;
			printf ("\n") ;

			//just_enter () ;

			print_space (parentspace + 1) ;			//printing node
			print_node_detail (ptr) ;
			printf ("\n") ;

			//just_enter () ;

			print_space (parentspace) ;				//printing lines below node
			printf ("/") ;
			print_space (ptrspace) ;
			printf ("\\") ;
			printf ("\n") ;

			//just_enter () ;

			print_space (parentspace - leftspace) ;
			print_node (ptr->left) ;
			print_space (1 + ptrspace + 1) ;
			print_node (ptr->right) ;

			//just_enter () ;
		}
	}
}

void manual_traverse (struct tree *t , struct node *ptr , int always_balance)
{
	int cont = 1 , option ;
	char dummy ;

	do
	{
		if (t->root == NULL)
		{
			printf ("Tree is empty!\n") ;
			return ;
		}

		print_manual_traverse_node (t , ptr) ;
		printf ("\n\n") ;
		printf ("---------------------------------------------------\n\n") ;

		print_manual_traverse_menu () ;
		scanf ("%d" , &option) ;
		scanf ("%c" , &dummy) ;

		switch (option)
		{
			case 1 :
				if (ptr->left == NULL)
					printf ("\nLeft child is empty. Cannot visit. Choose another option\n\n") ;
				else
					ptr = ptr->left ;
				break ;

			case 2 :
				if (ptr->right == NULL)
					printf ("\nRight child is empty. Cannot visit. Choose another option\n\n") ;
				else
					ptr = ptr->right ;
				break ;

			case 3 :
				if (ptr->parent == NULL)
					printf ("\nAt parent. Cannot go upward. Choose another option\n\n") ;
				else
					ptr = ptr->parent ;
				break ;

			case 4 :
				ptr = t->root ;
				break ;

			case 5 :
				if (always_balance == 1)
				{
					printf ("Tree needs to be balanced! Cannot rotate\n") ;
					break ;
				}

				if (ptr->right == NULL)
					printf ("Cannot rotate! Choose a node with a right child\n") ;
				else
				{
					left_rotate (t , ptr) ;
					//printf ("ROTATE DONE!\n") ;
					//just_enter () ;
					ptr = ptr->parent ;
				}
				break ;

			case 6 :
				if (always_balance == 1)
				{
					printf ("Tree needs to be balanced! Cannot rotate\n") ;
					break ;
				}

				if (ptr->left == NULL)
					printf ("Cannot rotate! Choose a node with a left child\n") ;
				else
				{
					right_rotate (t , ptr) ;
					//printf ("ROTATE DONE\n") ;
					//just_enter () ;
					ptr = ptr->parent ;
				}
				break ;

			case 7 :
				//printf ("Option 6\n") ;

				if (ptr->count > 1)
					ptr->count -= 1 ;
				else
				{
					if (ptr->left == NULL && ptr->right == NULL)
					{
						if (ptr->parent == NULL)
						{
							del_node_manual(t , ptr->val , always_balance) ;
							ptr = NULL ;
						}
						else
						{
							if (ptr->parent->left == ptr)
							{
								ptr = ptr->parent ;
								del_node_manual (t , ptr->left->val , always_balance) ;
							}
							else
							{
								ptr = ptr->parent ;
								del_node_manual (t , ptr->right->val , always_balance) ;
							}
						}
					}
					else if (ptr->left == NULL)
					{
						ptr = ptr->right ;
						del_node_manual (t , ptr->parent->val , always_balance) ;
					}
					else if (ptr->right == NULL)
					{
						ptr = ptr->left ;
						del_node_manual (t , ptr->parent->val , always_balance) ;
					}
					else
					{
						struct node* succ ;
						succ = tree_min (ptr->right) ;
						if (succ == ptr->right)
						{
							ptr = succ ;
							del_node_manual(t , succ->parent->val , always_balance);
						}
						else
							del_node_manual(t , ptr->val , always_balance) ;
					}
				}
				break ;

			case 8 :
				cont = 0 ;
				break ;

			default : 
				printf ("\n---------------------------------------------\n") ;
				printf ("Please enter correct option!\n") ;
				printf ("---------------------------------------------\n") ;
		}


	} while (cont) ;
}
