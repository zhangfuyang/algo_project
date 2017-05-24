#include <string>
#include "struct.h"
#include "queue.h"
#include "function.h"
#include "globalvar.h"
using namespace std;

static struct Cav_list cav_free_list;
static struct Cav_list cav_available_list;
static struct Cav_list cav_full_list;

void queue_init()
{
	LIST_INIT(&cav_free_list);
	LIST_INIT(&cav_available_list);
	LIST_INIT(&cav_full_list);

	for (int i = cavalier_num; i >= 0; i--)
	{
		cavalier[i].status = INIT;
		cavalier[i].pack_num = 0;
		LIST_INIT(&cavalier[i].station_list);
		LIST_INSERT_HEAD(&cav_free_list, &cavalier[i], cav_link);
	}
}

void queue_update(int time, Cav_list cav_list)
{
	Cavalier *cav;
	LIST_FOREACH(cav, &cav_list, cav_link)
	{
		Station *station, *temp = NULL, *last;
		int pack_release_num = 0;
		//寻找骑手在该时刻到达的DISTRICT
		LIST_FOREACH(station, &cav->station_list, station_link)
		{
			if (station->arrivetime <= time)
			{
				if (station->type = DISTRICT)
				{
					temp = station;
					pack_release_num++;
				}
				else if (station->type = RESTAURANT)
				{
					continue;
				}
			}
			else
			{
				break;
			}
		}
		//将找的DISTRICT之前的路径移除，并插入print
		if (temp != NULL)
		{
			LIST_LAST(last, &print[cav->id], station_link);
			LIST_FOREACH(station, &cav->station_list, station_link)
			{
				if (station = temp)
				{
					break;
				}
				else
				{
					LIST_INSERT_AFTER(last, station, station_link);
					LIST_REMOVE(station, station_link);
				}
			}
		}
		//更新该骑手状态
		if (pack_release_num != 0)
		{
			cav->pack_num -= pack_release_num;
			if (cav->pack_num == 0)
			{
				cav->bottlenecktime = 0;
				cav->status = FREE;
				LIST_CHANGE(cav, &cav_free_list, cav_link);
			}
			else
			{
				cav->bottlenecktime = cal_bottlenecktime(cav->station_list);
				cav->status = AVAILABLE;
				LIST_CHANGE(cav, &cav_free_list, cav_link);
			}
		}
	}
}

float find_free_cavalier(Order *order, Cavalier *cav)  //当Free列表不为空时，给Free列表中的骑士分配订单
{
	float time = order->time;
	float distance;
	float origintime = 10000;
	float time_dst; //distance的距离
	Cavalier *luckyone;
	Station  *first;
	LIST_FOREACH(luckyone, &cav_free_list, cav_link)
	{
		first = LIST_FIRST(&luckyone->station_list);
		DISTANCE((*first), restaurant[order->rid], distance);
		TIME(distance, time_dst);
		if (first == NULL)
		{
			DISTANCE(did2district(order->did), rid2restaurant(order->rid), distance);
			TIME(distance, time);
			return time;
		}
		if (time_dst + first->arrivetime < time) {  //arrivetime和leavetime相同
			if (time - (time_dst + first->arrivetime) < origintime){
				origintime = time - (time_dst + first->arrivetime);
				cav = luckyone;
			}
		}
	}
	if (cav != NULL)
	{
		DISTANCE(did2district(order->did), rid2restaurant(order->rid), distance);
		TIME(distance, time);
		return origintime + time;
	}
	if (origintime == 10000) 
	{
		LIST_FOREACH(luckyone, &cav_free_list, cav_link)
		{
			first = LIST_FIRST(&luckyone->station_list);
			DISTANCE((*first), restaurant[order->rid], distance);
			TIME(distance, time_dst);
			if (time_dst + first->arrivetime < origintime) {
				origintime = time_dst +first->arrivetime;
				cav = luckyone;
			}
		}
	}
	if (cav == NULL)
		return -1;
	DISTANCE(did2district(order->did), rid2restaurant(order->rid), distance);
	TIME(distance, time);
	return time;
}


float Insert_order(Order *order, Station_list head) {           //返回插入后的最大时间
	Station *var = NULL;
	int x1 = restaurant[order->rid].location.x;
	int y1 = restaurant[order->rid].location.y;
	int x2 = restaurant[order->did].location.x;
	int y2 = restaurant[order->did].location.y;



	return 0;
}



