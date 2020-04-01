#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "create.h"
#include "find.h"
#include "del.h"
#include "main.h"


void display_menu ()
{
	/*
	Either do one of the following -
	1. Never balance the tree in any of the operations.
	2. Always keep the tree balanced.
	*/

	printf ("Choose what you want to do - \n") ;
	printf ("1. Create a new tree \n") ;
	printf ("2. Insert a node into tree without balancing \n") ;
	printf ("3. Delete a node from tree without balancing \n") ;
	printf ("4. Find a node \n") ;
	printf ("5. Insert a node with balancing \n") ;		
	printf ("6. Delete a node with balancing \n") ;
	printf ("7. Balance the entire tree at one go\n") ;
	printf ("8. Print the tree horizontally \n")	 ;
	printf ("9. Print the tree vertically edgewise\n") ;		//Doesn't work well for unbalanced trees yet.
	printf ("10. Print the tree vertically centred\n") ;
	printf ("11. Manually Traverse the tree \n") ;
	printf ("12. Delete the tree \n") ;
	printf ("13. Find kth order element\n") ;
	printf ("14. Find elements in range\n") ;
	printf ("15. Create all simple breadth lists at once\n") ;
	printf ("16. Create all edgewise space breadth lists at once \n") ;
	printf ("17. Create all centred space breadth lists at once\n") ;
	printf ("18. Print all breadth lists \n") ;
	printf ("19. Exit\n") ;
}

int main ()
{
	int option , cont = 1 , val , korder , r1 ,r2 ;
	int always_balance  , set = 0 ;
	struct tree *t ;
	struct node* findres , *kmin ;
	struct dll *rangelist ;
	struct dllnode *rangeptr ;

	t = NULL ;

	while (cont)
	{
		//system("cls") ;
		printf("\n") ;
		display_menu () ;
		scanf ("%d" , &option) ;

		switch (option)
		{
			case 1 :	//Create Tree
				//printf ("Option 1\n") ;
				if (t != NULL)
				{
					printf ("Tree has already been created!\n") ;
					break ;
				}
				t = create_tree () ;
				printf ("Empty tree created!\n") ;
				break ;

			case 2 :	//Insertion without balance
				//printf ("Option 2\n") ;
				if (t == NULL)
				{
					printf ("Tree hasn't been created. Please create tree first\n") ;
					set = 0 ;
					break ;
				}
				if (set == 0)
				{
					set = 1 ;
					always_balance = 0 ;
				}


				if (always_balance == 1)
				{
					printf ("Cannot use this option. Please add node in balanced manner only\n") ;
					break ;
				}

				printf ("Enter the value that you want to insert : ") ;
				scanf ("%d" , &val) ;
				add (t , val) ;
				break ;	

			case 3 :		//Deletion without balancing
				//printf ("Option 3\n") ;
				if (t == NULL)
				{
					printf ("Tree hasn't been created. Please create tree first\n") ;
					set = 0 ;
					break ;
				}
				else if (t->root == NULL)
				{
					printf ("There is nothing to delete!\n") ;
					set = 0 ;
					break ;
				}


				if (always_balance == 1)
				{
					printf ("Cannot use this option. Please delete node in balanced manner only\n") ;
					break ;
				}

				printf ("Enter the value that you want to delete : ") ;
				scanf ("%d" , &val) ;
				del_node (t , val) ;
				break ;

			case 4 :		//Finding a node
				//printf ("Option 4\n") ;
				if (t == NULL)
				{
					printf ("Tree hasn't been created. Please create tree first\n") ;
					set = 0 ;
					break ;
				}
				else if (t->root == NULL)
				{
					printf ("There is nothing to find!\n") ;
					set = 0 ;
					break ;
				}

				printf ("Enter the value you want to search : ") ;
				scanf ("%d" , &val) ;
				findres = find (t , val) ;

				if (findres == NULL)
					printf ("Node does not exist!\n") ;
				else
				{
					printf ("Node found! Transporting to the node\n") ;
					//printf ("Value = %d, count = %d, left height = %d, right height = %d, height balance = %d\n" , findres->val , findres->count , findres->lh , findres->rh , findres->hb) ;
					manual_traverse (t , findres , always_balance) ;
				}
				break ;

			case 5 :		//Insertion with balancing
				//printf ("Option 5\n") ;
				if (t == NULL)
				{
					printf ("Tree hasn't been created. Please create tree first\n") ;
					set = 0 ;
					break ;
				}
				if (set == 0)
				{
					set = 1 ;
					always_balance = 1 ;
				}


				if (always_balance == 0)
				{
					printf ("Cannot use this option. Please add node in unbalanced manner only\n") ;
					break ;
				}

				printf ("Enter the value that you want to insert : ") ;
				scanf ("%d" , &val) ;
				add_bal (t , val) ;
				break ;

			case 6 :		//Deletion with balancing
				//printf ("Option 6\n") ;
				if (t == NULL)
				{
					printf ("Tree hasn't been created. Please create tree first\n") ;
					set = 0 ;
					break ;
				}
				else if (t->root == NULL)
				{
					printf ("There is nothing to delete!\n") ;
					set = 0 ;
					break ;
				}


				if (always_balance == 0)
				{
					printf ("Cannot use this option. Please delete node in unbalanced manner only\n") ;
					break ;
				}

				printf ("Enter the value that you want to delete : ") ;
				scanf ("%d" , &val) ;
				del_node_bal (t , val) ;
				break ;

			case 7 :		//Balancing entire tree at one go
				printf ("Option 7\n") ;
				all_bal (t , t->root) ;
				break ;	

			case 8 :		//Printing horizontal
				//printf ("Option 7\n") ;
				if (t == NULL)
				{
					printf ("The tree hasn't been created. Please create tree first\n") ;
					set = 0 ;
					break ;
				}
				else if (t->root == NULL)
				{
					printf ("The tree is empty!\n") ;
					set = 0 ;
					break ;
				}

				print_tree_horizontal (t->root , 0);
				break ;

			case 9 :		//Printing vertically edgewise
				//printf ("Option 9\n") ;
				if (t == NULL)
				{
					printf ("The tree hasn't been created. Please create tree first\n") ;
					set =  0 ;
					break ;
				}
				else if (t->root == NULL)
				{
					printf ("The tree is empty!\n") ;
					set = 0 ;
					break ;
				}

				create_all_simple_levellists (t) ;

				create_all_space_levellists_edgewise (t , t->root , 'x' , 0 , 0) ;
				print_tree_vertical (t) ;
				break ;

			case 10 :		//Printing vertically centred
				//printf ("Option 10\n") ;
				if (t == NULL)
				{
					printf ("The tree hasn't been created. Please create tree first\n") ;
					set =  0 ;
					break ;
				}
				else if (t->root == NULL)
				{
					printf ("The tree is empty!\n") ;
					set = 0 ;
					break ;
				}
				
				create_all_simple_levellists (t) ;

				create_all_space_levellists_centred (t , t->root , 'x' , 0 , 0) ;
				print_tree_vertical (t) ;
				break ;

			case 11 :		//Manual Traverse
				//printf ("Option 11\n") ;
				if (t == NULL)
				{
					printf ("The tree hasn't been created. Please create tree first\n") ;
					set =  0 ;
					break ;
				}
				else if (t->root == NULL)
				{
					printf ("The tree is empty!\n") ;
					set = 0 ;
					break ;
				}

				manual_traverse (t , t->root ,  always_balance) ;
				break ;

			case 12 :		//Deleting Tree
				//printf ("Option 12\n") ;
				if (t == NULL)
				{
					printf ("The tree hasn't been created. Please create tree first\n") ;
					set = 0 ;
					break ;
				}
				else
				{

					del_tree (t->root) ;
					//printf ("REACHING HERE\n") ;
					free(t) ;
					t = NULL ;
					//t->no = 0 ;

					printf ("Tree has been deleted!\n") ;
				}		
				break ;

			case 13 :	//kth order element
				if (t == NULL)
				{
					printf ("Tree hasn't been created. Please create tree first\n") ;
					set = 0 ;
					break ;
				}
				else if (t->root == NULL)
				{
					printf ("There is nothing to find!\n") ;
					set = 0 ;
					break ;
				}
				

				do
				{
					printf ("Enter the kth order minimum to find (less than %d) : " , t->no) ;
					scanf ("%d" , &korder) ;

					if (korder > t->no)
						printf ("Please choose a number less than %d\n" , t->no) ;

				} while (korder > t->no) ;

				kmin = find_kmin (t , korder) ;
				printf ("%dth minimum found! Transporting to the node\n\n" , korder) ;
				manual_traverse (t , kmin , always_balance) ;
				break ;

			case 14 :		//Elements in range
				if (t == NULL)
				{
					printf ("Tree hasn't been created. Please create tree first\n") ;
					set = 0 ;
					break ;
				}
				else if (t->root == NULL)
				{
					printf ("There is nothing to find!\n") ;
					set = 0 ;
					break ;
				}

			
				printf ("Enter the left limit : ") ;
				scanf ("%d" , &r1) ;
				printf ("Enter the right limit : ") ;
				scanf ("%d" , &r2) ;

				rangelist = (struct dll *) malloc (sizeof(struct dll)) ;
				rangelist->front = NULL ;
				rangelist->rear = NULL ;
				rangelist->count = 0 ;
				
				find_range (t->root , r1 , r2 , rangelist) ;
				
				if (rangelist->count == 0)
					printf ("No element in the range was found") ;
				else
				{
					rangeptr = rangelist->front ;
					printf ("Locating every element in the list\n\n") ;
					
					while (rangeptr != NULL)
					{
						//printf ("%d\n" , rangeptr->nodeptr->val) ;
						manual_traverse (t , rangeptr->nodeptr , always_balance) ;
						rangeptr = rangeptr->next ;
					}
				}

				del_all_dll (rangelist) ;
				free (rangelist) ;

				break ;

			case 15 :		//Simple breadth lists
				if (t == NULL)
				{
					printf ("Tree hasn't been created. Please create tree first\n") ;
					set = 0 ;
					break ;
				}
				else if (t->root == NULL)
				{
					printf ("Tree is empty. Cannot create breadth list!\n") ;
					set = 0 ;
					break ;
				}

				create_all_simple_levellists (t) ;
				printf ("Simple level lists created! \n") ;

				break ;

			case 16 :		//Space Edgewise breadth lists
				if (t == NULL)
				{
					printf ("Tree hasn't been created. Please create tree first\n") ;
					set = 0 ;
					break ;
				}
				else if (t->root == NULL)
				{
					printf ("Tree is empty. Cannot create breadth list!\n") ;
					set = 0 ;
					break ;
				}

				create_all_simple_levellists (t) ;

				create_all_space_levellists_edgewise (t , t->root , 'x' , 0 , 0) ;
				printf ("Space edgewise level lists created! \n") ;

				break ; 

			case 17 :		//Space Centred breadth lists
				if (t == NULL)
				{
					printf ("Tree hasn't been created. Please create tree first\n") ;
					set = 0 ;
					break ;
				}
				else if (t->root == NULL)
				{
					printf ("Tree is empty. Cannot create breadth list!\n") ;
					set = 0 ;
					break ;
				}

				create_all_simple_levellists (t) ;

				create_all_space_levellists_centred (t , t->root , 'x' , 0 , 0) ;
				printf ("Space centred level lists created! \n") ;

				break ;

			case 18 :
				if (t == NULL)
				{
					printf ("Tree hasn't been created. Please create tree first\n") ;
					set = 0 ;
					break ;
				}
				else if (t->root == NULL)
				{
					printf ("Tree is empty. Cannot create breadth list!\n") ;
					set = 0 ;
					break ;
				}

				if (t->levellists == NULL)
					create_all_simple_levellists (t) ;

				print_all_levellists (t) ;
				break ;


			case 19 :
				cont = 0 ;
				break ; 

			default :
				printf ("\n---------------------------------------------\n") ;
				printf ("Please enter correct option!\n") ;
				printf ("---------------------------------------------\n") ;

		}
	}

	//printf ("Exiting\n") ;
	//just_enter () ;

	if (t != NULL)
	{
		if (t->levellists != NULL)
			del_all_levellists (t) ;

		del_tree(t->root) ;
		free(t) ;
	}

	return 0 ;
}
