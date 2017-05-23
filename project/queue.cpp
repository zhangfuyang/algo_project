#include <string>
#include "struct.h"
#include "queue.h"
#include "function.h"
#include "globalvar.h"
using namespace std;

LIST_HEAD(Cav_list, Cavalier);

LIST_HEAD(Cav_print_list, Print);

static struct Cav_list cav_free_list;
static struct Cav_list cav_available_list;
static struct Cav_list cav_full_list;

extern Cavalier cavalier[];
extern int cavalier_num;
void cav_print_list_init()
{
	Cav_print_list *cav_print_list;
	cav_print_list = new Cav_print_list[cavalier_num + 1];
	for (int i = 1; i <= cavalier_num; i++)
	{
		cav_print_list[i].lh_first = NULL;
	}
}
void queue_init()
{

	LIST_INIT(&cav_free_list);
	LIST_INIT(&cav_available_list);
	LIST_INIT(&cav_full_list);

	for (int i = cavalier_num; i >= 0; i--)
	{
		cavalier[i].status = FREE;
		cavalier[i].pack_num = 0;
		cavalier[i].now = -1000; //初始时间为足够大的负数
		cavalier[i].end = cavalier[i].now;
		cavalier[i].location.x = 0;
		cavalier[i].location.y = 0;
		LIST_INSERT_HEAD(&cav_free_list, &cavalier[i], cav_link);
	}
}

void queue_update(int time)
{
	Cavalier *cav;

	LIST_FOREACH(cav, &cav_full_list, cav_link)
	{
		if (cav->end < time)
		{
			cav->location = place2xy(packid2district(cav, cav->pack_num));//某一个餐馆,有待修改
			cav->now = cav->end;
			cav->status = FREE;
			cav->pack_num = 0;
			LIST_INSERT_HEAD(&cav_free_list, cav, cav_link);
		}
		else
		{
			//部分更新
		}
	}
}

void find_free_cavalier(Order *order, Cavalier *cav)
{
	float time = order->time;
	float distance;
	float origintime = 1000;
	Cavalier *luckyone;
	LIST_FOREACH(luckyone, &cav_free_list, cav_link)
	{
		DISTANCE((*luckyone), restaurant[order->rid], distance);

		if ((distance + luckyone->now) < time) {
			if ((time - (distance + luckyone->now)) < origintime){
				origintime = time - (distance + luckyone->now);
				cav = luckyone;
			}
	
		}

   		 
	}
	if (origintime == 1000) {
		LIST_FOREACH(luckyone, &cav_free_list, cav_link)
		{
			DISTANCE((*luckyone), restaurant[order->rid], distance);

			if ((distance + luckyone->now) < origintime) {
				origintime = distance + luckyone->now;
				cav = luckyone;
			}
		
		
		}

	}
}
