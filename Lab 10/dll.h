void del_all_dll (struct dll *list) ;
void del_front_dll (struct dll *list) ;
void del_rear_dll (struct dll *list) ;
void del_ptr_dll (struct dll *list , int val) ;

void insert_inorder_dll (struct dll *list , struct dllnode *ptr) ;
void insert_front_dll (struct dll *list , struct dllnode *ptr) ;
void insert_rear_dll (struct dll *list , struct dllnode *ptr) ;

struct dllnode* pop_front_dll (struct dll *list) ;
struct dllnode* pop_rear_dll (struct dll *list) ; 
struct dllnode *ret_ptr_dll (struct dll* list, int val) ;

void print_all_dll (struct dll *list) ;
void print_all_dll_space_edgewise (struct dll *list , struct dll *prntlist) ;
void print_all_dll_node_edgewise (struct dll *list) ;

//function needed from print.h
void print_node (struct node* ptr) ;
void print_space (int count) ;

//function needed from util.h
int get_nodelength (struct node *ptr) ;
char node_type (struct node *ptr) ;
void just_enter () ;
