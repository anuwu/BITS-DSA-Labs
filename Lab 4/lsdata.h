#define LOWER 1
#define UPPER 1000000

struct Number
{
	int x ;
	struct Number* next ;
} ;

struct List
{
	struct Number* head ;
	int size ;
} ;

