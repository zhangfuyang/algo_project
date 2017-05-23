#include <string>
#include "struct.h"
#include "queue.h"
using namespace std;

LIST_HEAD(Cav_list, Cavalier);

static struct Cav_list cav_free_list;
static struct Cav_list cav_available_list;
static struct Cav_list cav_full_list;

extern Cavalier cavalier[];
extern int cavalier_num;

void queue_init()
{

	LIST_INIT(&cav_free_list);
	LIST_INIT(&cav_available_list);
	LIST_INIT(&cav_full_list);

	for (int i = cavalier_num; i >= 0; i--)
	{
		LIST_INSERT_HEAD(&cav_free_list, &cavalier[i], cav_link);
	}
}

void queue_update(int time)
{
	struct Cavalier *cav;

	LIST_FOREACH(cav, &cav_full_list, cav_link)
	{
		;
}
}