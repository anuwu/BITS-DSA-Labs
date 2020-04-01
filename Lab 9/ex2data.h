struct Hashtable
{
	char **strarr ;
	struct ele** heads ;
	int elementCount ;
	int insertionCost ;
	int queryingCost ;
} ;

struct ele
{
	int index ;
	int occ ;
	struct ele* next ;
} ;

extern int ts ;
extern int bn ;
extern int init_now ;
