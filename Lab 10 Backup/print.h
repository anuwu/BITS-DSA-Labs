void print_tree_horizontal (struct node *ptr , int space) ;

int print_tree_vertical_edgewise (struct tree *t, struct node *ptr , char c , int level) ;
int print_tree_vertical_centred (struct tree *t, struct node *ptr , char c , int level) ;

void print_space (int count) ;
void print_node (struct node* ptr) ;
void print_node_detail (struct node *ptr) ;

//function needed from dll.h
struct dllnode *ret_ptr_dll (struct dll* list, struct dllnode *ptr) ;
