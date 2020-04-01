void del_all_levellists (struct tree *t) ;
void create_all_simple_levellists (struct tree *t) ;
int create_all_space_levellists_edgewise (struct tree *t , struct node *ptr , char c , int level , int init_space) ;
int create_all_space_levellists_centred (struct tree *t , struct node *ptr , char c , int level , int init_space) ;
void print_all_levellists (struct tree *t) ;

//Function needed from util.h
int max (int x , int y) ;
void just_enter () ;
int get_nodelength (struct node *ptr) ;

//Function needed from dll.h
void del_all_dll (struct dll *list) ;
void insert_front_dll (struct dll *list , struct dllnode *ptr) ;
void insert_rear_dll (struct dll *list , struct dllnode *ptr) ;
struct dllnode* pop_front_dll (struct dll *list) ;
void print_all_dll (struct dll *list) ;
struct dllnode *ret_ptr_dll (struct dll* list, int val) ;
