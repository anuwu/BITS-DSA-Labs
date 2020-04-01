#include <time.h>

int random_gen (int lower , int upper)
{
	srand (time(0)) ;
	int num = (rand() % (upper - lower + 1)) + lower ;

	return num ;
}
