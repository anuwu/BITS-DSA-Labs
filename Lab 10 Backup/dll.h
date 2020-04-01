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
