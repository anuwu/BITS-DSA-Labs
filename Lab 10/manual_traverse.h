void print_manual_traverse_menu () ;
void print_manual_traverse_node (struct tree *t , struct node *ptr) ;
void manual_traverse (struct tree *t , struct node* ptr , int always_balance) ;

void del_node_manual (struct tree* t , int val , int always_balance) ;

//function needed from util.h
int get_nodespace (struct node *ptr) ;
