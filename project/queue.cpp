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
	Cavalier *luckyone;
	LIST_FOREACH(luckyone, &cav_free_list, cav_link)
	{
		DISTANCE((*LIST_FIRST(&luckyone->station_list)), restaurant[order->rid], distance);
		
		if (distance + LIST_FIRST(&luckyone->station_list)->arrivetime < time) {  //arrivetime和leavetime相同
			if (time - (distance + LIST_FIRST(&luckyone->station_list)->arrivetime) < origintime){
				origintime = time - (distance + LIST_FIRST(&luckyone->station_list)->arrivetime);
				cav = luckyone;
			}
	
		}
	}
	if (origintime == 10000) {
		LIST_FOREACH(luckyone, &cav_free_list, cav_link)
		{
			DISTANCE((*LIST_FIRST(&luckyone->station_list)), restaurant[order->rid], distance);

			if (distance + LIST_FIRST(&luckyone->station_list)->arrivetime < origintime) {
				origintime = distance + LIST_FIRST(&luckyone->station_list)->arrivetime;
				cav = luckyone;
			}
		}
	}
	
	if (cav == NULL)
	{
		return -1;
	}
	
}


float Insert_order(Order *order, Station_list *head) {           //返回插入后的最大时间
	Station *var = NULL;
	Station *choose = NULL;
	Station *newstation = NULL;
	int x1 = restaurant[order->rid].location.x;         //订单的餐厅坐标            
	int y1 = restaurant[order->rid].location.y;
	int x2 = district[order->did].location.x;		    //订单的小区坐标
	int y2 = district[order->did].location.y;
	float distance;
	float dist1;
	float dist2;
	float mindis = 10000;              //取最短距离变量
	float delaytime;                   //插入后修改后面的station所用的延迟时间
	float T;                           //返回的插入后的瓶颈时间


	LIST_FOREACH(var, head, station_link)             //取得餐厅插入位置         
	{
		if ((LIST_NEXT(var, station_link)) != NULL) {
			DISTANCE((*var), restaurant[order->rid], dist1);
			DISTANCE((*(LIST_NEXT(var, station_link))), restaurant[order ->rid], dist2);
			distance = dist1 + dist2;
		}
		if (distance < mindis) {
			mindis = distance;
			choose = var;
		}
	}

	newstation = new Station[1];           

	DISTANCE((*choose), restaurant[order->rid], dist1);

	newstation->arrivetime = choose->leavetime + dist1;         //更新新插入餐厅的各项信息
	if (newstation->arrivetime < order->time) {
		newstation->leavetime = order->time;
	}
	else {
		newstation->leavetime = newstation->arrivetime;
	}
	newstation->location.x = x1;
	newstation->location.y = y1;
	newstation->oid = order->orderid;
	newstation->type = RESTAURANT;

	LIST_INSERT_AFTER(choose, newstation, station_link);       //插入

	var = LIST_NEXT(newstation, station_link);

	DISTANCE((*var), restaurant[order->rid], dist2);

	delaytime = newstation->leavetime + dist2 - var->arrivetime;      //延迟时间


	LIST_FOREACH_FROM(var, head, station_link)
	{
		var->arrivetime = var->arrivetime + delaytime;
		if (var->leavetime >= var->arrivetime) {
			break;
		}
		else {
			delaytime = var->arrivetime - var->leavetime;      //更新delaytime
			var->leavetime = var->arrivetime;
		}
	}

	var = newstation;           //为插入小区做准备
	mindis = 10000;

	LIST_FOREACH_FROM(var, head, station_link)            //从已经插入的餐厅之后再遍历
	{
		if ((LIST_NEXT(var, station_link)) != NULL) {
			DISTANCE((*var), district[order->did], dist1);
			DISTANCE((*(LIST_NEXT(var, station_link))), district[order->did], dist2);
			distance = dist1 + dist2;
		}
		if (distance < mindis) {
			mindis = distance;
			choose = var;
		}
	}

	newstation = new Station[1];

	DISTANCE((*choose), district[order->did], dist1);

	newstation->arrivetime = choose->leavetime + dist1;      //更新新插入小区的各项信息

	newstation->leavetime = newstation->arrivetime;
	
	newstation->location.x = x2;
	newstation->location.y = y2;
	newstation->oid = order->orderid;
	newstation->type = DISTRICT;

	LIST_INSERT_AFTER(choose, newstation, station_link);     //插入小区

	var = LIST_NEXT(newstation, station_link);

	DISTANCE((*var), district[order->did], dist2);

	delaytime = newstation->leavetime + dist2 - var->arrivetime;


	LIST_FOREACH_FROM(var, head, station_link)             //更新插入小区之后的
	{
		var->arrivetime = var->arrivetime + delaytime;
		if (var->leavetime >= var->arrivetime) {
			break;
		}
		else {
			delaytime = var->arrivetime - var->leavetime;
			var->leavetime = var->arrivetime;
		}
	}

	T = cal_bottlenecktime(*head);
	return T;
}



