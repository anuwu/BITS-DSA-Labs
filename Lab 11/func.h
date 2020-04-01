struct STree* create_tree () ;

int compstr (char *str1 , char *str2) ;
struct node* insertdomparts (struct STree *st , char **domparts , int num) ;
void insertdomainip (struct STree *st , char *domip) ;

struct lookupres* lookup (struct STree *st , char *domname) ;

struct node* visit_child_handler (struct node* ptr) ;
void manual_traverse (struct STree *st) ;
void print_manual_traverse_menu () ;
