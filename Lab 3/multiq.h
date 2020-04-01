typedef int Priority ;
typedef int ID ;

#define MAX 10

struct Task
{
	ID id ;
	Priority pri ;
	struct Task* next ;
} ;

struct Queue
{
	struct Task* head ;
	struct Task* tail ;
	int t_cnt ;
} ;

struct MultiQ
{
	struct Queue* qarr ;
	int q_cnt ;
} ;

struct MultiQ createMQ (int num) ;
struct MultiQ addMQ (struct MultiQ mq, struct Task t) ;
struct Task nextMQ (struct MultiQ mq) ;
struct Task delNextMQ (struct MultiQ mq) ;
struct Task isEmptyMQ (struct MultiQ mq) ;
int sizeMQ (struct MultiQ mq) ;
int sizeMQbyPriority (struct MultiQ mq, Priority p) ;
struct Queue getQueueFromMQ (struct MultiQ mq, Priority p) ;

void printMultiQ (struct MultiQ mq) ;
void printQ (struct Queue q) ;
void printTask (struct Task t) ;


