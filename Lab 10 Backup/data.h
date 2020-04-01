struct node
{
	int val ;
	int count ;

	int lh ;
	int rh ;
	int hb ;

	struct node* left ;
	struct node* right ;
	struct node* parent ;
} ;

struct tree
{
	struct node* root ;
	int no ;

	struct dll *levellists ;	
} ;

struct dll
{
	struct dllnode *front ;
	struct dllnode *rear ;
	int count ;
} ;

struct dllnode
{
	struct node *nodeptr ;
	int space ;		//by defaut -1

	struct dllnode *next ;
	struct dllnode *prev ;
} ;
