void print_tree_horizontal (struct node *ptr , int space) ;
void print_tree_vertical (struct tree* t) ;

void print_space (int count) ;
void print_node (struct node* ptr) ;
void print_node_detail (struct node *ptr) ;

//function needed from dll.h
void print_all_dll_node_edgewise (struct dll *list) ;
void print_all_dll_space_edgewise (struct dll *list , struct dll *prntlist) ;

//function needed from util.h
int max (int x , int y) ;
int get_nodelength (struct node *ptr) ;
