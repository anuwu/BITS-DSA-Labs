#include <stdlib.h>
#include "data.h"
#include "create.h"

struct tree* create_tree ()
{
	struct tree* t ;
	t = (struct tree*) malloc (sizeof(struct tree)) ;
	t->root = NULL ;
	t->no = 0 ;
	t->levellists = NULL ;

	return t ;
}
