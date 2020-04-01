void transplant (struct tree *t , struct node *u , struct node *v) ;
struct node* tree_min (struct node* succ) ;
struct node* find_z (struct node* ptr) ;
void update_balance (struct node *ptr) ;
void left_rotate (struct tree *t , struct node *x) ;
void right_rotate (struct tree *t , struct node *x) ;

void all_bal (struct tree *t , struct node *ptr) ;

void just_enter () ;
void enter () ;

int max (int x , int y) ;
int ret_lh (struct node *ptr) ;
int ret_rh (struct node *ptr);

int get_nodelength (struct node *ptr) ;
int get_nodespace (struct node *ptr) ;
char node_type (struct node *ptr) ;
