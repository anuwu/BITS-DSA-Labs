void del_all_levellists (struct tree *t) ;
void create_all_simple_levellists (struct tree *t) ;
void create_all_space_levellists (struct tree *t) ;
void print_all_levellists (struct tree *t) ;

//Function needed from util.h
int max (int x , int y) ;
void just_enter () ;

//Function needed from dll.h
void del_all_dll (struct dll *list) ;
void insert_front_dll (struct dll *list , struct dllnode *ptr) ;
void insert_rear_dll (struct dll *list , struct dllnode *ptr) ;
struct dllnode* pop_front_dll (struct dll *list) ;
void print_all_dll (struct dll *list) ;
