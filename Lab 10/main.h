//intrinsic to main.h
void display_menu () ;

//functions needed from insert.h
void add (struct tree *t , int val) ; 
void add_bal (struct tree *t , int val) ; 

//function needed from manual_traverse.h
void manual_traverse (struct tree *t, struct node *ptr , int always_balance) ;

//Only function needed from print.h
void print_tree_horizontal (struct node *ptr , int space) ;
void print_tree_vertical (struct tree *t) ;

//function needed from kmin_range.h
struct node* find_kmin (struct tree *t , int korder) ;
void find_range (struct node* ptr , int r1 , int r2 , struct dll *rangelist) ;

//function needed from dll.h
void del_all_dll (struct dll *list) ;

//function needed from util.h
void all_bal (struct tree *t , struct node *ptr) ;
void just_enter () ;

//function needed from breadth.h
void create_all_simple_levellists (struct tree *t) ;
int create_all_space_levellists_edgewise (struct tree *t, struct node *ptr , char c , int level , int init_space) ;
int create_all_space_levellists_centred (struct tree *t, struct node *ptr , char c , int level , int init_space) ;
void print_all_levellists (struct tree *t) ;
void del_all_levellists (struct tree *t) ;
