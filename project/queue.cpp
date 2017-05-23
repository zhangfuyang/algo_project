#include <string>
#include "struct.h"
#include "queue.h"
#include "function.h"
#include "globalvar.h"
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
		if (cav->end < time)
		{
			cav->now = cav->end;

			cav->location = place2xy(restaurant[0]);//某一个餐馆,有待修改
			cav->status = FREE;
			cav->pack_num = 0;
			cav->pack_num = 0;
			LIST_INSERT_HEAD(&cav_free_list, cav, cav_link);
		}
	}
}
