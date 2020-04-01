struct node
{
	char *str ;
	int no_children ;

	struct node* parent ;
	struct node** children ;
} ;

struct STree
{
	struct node* root ;
} ;

struct lookupres
{
	int success ;
	
	int *breadtharr ;
	int level ;

	int no_ip ;
	char **iparr ;
} ;