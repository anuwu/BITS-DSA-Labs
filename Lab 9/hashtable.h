struct Hashtable* createht () ;

void insert (struct Hashtable* ht , int index) ;
void insertAll (struct Hashtable *ht , char **strarr , int now) ;

int lookup (struct Hashtable *ht , char *str) ;
void lookupall (struct Hashtable *ht , double m) ;

double profile (struct Hashtable *ht) ;

int cleanup (struct Hashtable *ht , char *filename) ;
int deleteht (struct Hashtable *ht , char *str) ;
char* fgets_fixup (char *str) ;

void traverse (struct Hashtable *ht , int div) ;
int compstr (char *str1 , char *str) ;



