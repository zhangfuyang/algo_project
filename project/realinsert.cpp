#include <iostream>
#include "struct.h"
#include "globalvar.h"
#include "function.h"
//真插，且start为被插链表的第一个节点，在第rn个节点后插入餐馆，第dn个节点后插入小区，此时dn为餐馆已经插入后的位置
void really_insert(Station *start, Order *order, int rn, int dn)
{
	Station *newres = new Station[1];
	newres->location = restaurant[order->rid].location;
	newres->oid = order->oid;
	newres->type = RESTAURANT;

	Station *newdis = new Station[1];
	newdis->location = district[order->did].location;
	newdis->oid = order->oid;
	newdis->type = DISTRICT;

	int i = 0;
	float dist1,dist2;
	float delaytime;
	Station *var;

	int flag1=0, flag2=0;

	LIST_FOREACH_FROM2(start, station_link)
	{
		i++;
		if (i == rn){
			//插入餐馆
			LIST_INSERT_AFTER(start, newres, station_link);
			//更新新插入餐厅的各项信息
			DISTANCE((*start), restaurant[order->rid], dist1);	
			newres->arrivetime = start->leavetime + dist1;
			if (newres->arrivetime < order->time) {
				newres->leavetime = order->time;
			}
			else {
				newres->leavetime = newres->arrivetime;
			}
			//更新新插入餐厅之后各节点的各项信息
			var = LIST_NEXT(newres, station_link);
			DISTANCE((*var), restaurant[order->rid], dist2);
			//延迟时间
			delaytime = newres->leavetime + dist2 - var->arrivetime;
			LIST_FOREACH_FROM2(var, station_link)
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
			flag1++;
		}
		if (i == dn)
		{
			//更新新插入小区的各项信息
			DISTANCE((*start), district[order->did], dist1);		
			newdis->arrivetime = start->leavetime + dist1;
			newdis->leavetime = newdis->arrivetime;

			//插入小区
			LIST_INSERT_AFTER(start, newdis, station_link);
			var = LIST_NEXT(newdis, station_link);
			DISTANCE((*var), district[order->did], dist2);
			delaytime = newdis->leavetime + dist2 - var->arrivetime;

			//更新插入小区之后的各项信息
			LIST_FOREACH_FROM(var, head, station_link)
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
			flag2++;
		}
	}
	if (flag1 != 1 | flag2 != 1) {
		printf("真插错误！");
		system("pause");
	}
}

//尝试将某个订单插入骑士的Station列表返回插入后的最大时间
float Insert_order(Order *order, Station_list *head, int status, Cavalier cav) {
	Station *var = NULL;
	Station *choose = NULL;
	Station *newstation = NULL;
	Station *last = NULL;
	Station *last1 = NULL;
	Station *oldlast = new Station[1];
	Station *newlast = new Station[1];
	Station *newnewstation = new Station[1];

	//订单的餐厅坐标

	int x1 = restaurant[order->rid].location.x;
	int y1 = restaurant[order->rid].location.y;

	//订单的小区坐标

	int x2 = district[order->did].location.x;
	int y2 = district[order->did].location.y;
	float distance;
	float dist1;
	float dist2;
	float dist3;

	//取最短距离变量

	float mindis = 10000;

	//插入后修改后面的station所用的延迟时间

	float delaytime;

	//返回的插入后的瓶颈时间

	//	float T;                           
	float T1;

	//用于比较如果小区插在倒数第二个位置，是插在倒数第二个位置好，还是插在尾部好

	float T2;

	//取得餐厅插入位置
	var = LIST_FIRST(head);
	while (LIST_NEXT(var, station_link) != NULL && var->location.x == LIST_NEXT(var, station_link)->location.x &&
		var->location.y == LIST_NEXT(var, station_link)->location.y)
		//order[var->oid].oid != order[LIST_NEXT(var, station_link)->oid].oid)
	{
		var = LIST_NEXT(var, station_link);
	}
	if (LIST_NEXT(var, station_link) == NULL) //只有一个元素
	{
		Station *ttemp;
		float time;
		float time2;
		float Time;
		newstation = new Station[1];
		ttemp = LIST_FIRST(head);
		DISTANCE((*ttemp), restaurant[order->rid], distance);
		TIME(distance, time);
		LIST_INSERT_AFTER(var, newstation, station_link);
		newstation->location = restaurant[order->rid].location;
		newstation->oid = order->oid;
		newstation->type = RESTAURANT;
		if (time + ttemp->leavetime > order->time) //订单等我
		{
			time2 = time + ttemp->leavetime;
			DISTANCE(district[order->did], restaurant[order->rid], distance);
			TIME(distance, time);
			newstation->arrivetime = time2;
			newstation->leavetime = newstation->arrivetime;
			Time = time + time2;
		}
		else
		{
			newstation->arrivetime = time + ttemp->leavetime;
			newstation->leavetime = order->time;
			DISTANCE(district[order->did], restaurant[order->rid], distance);
			TIME(distance, time);
			Time = time;
		}
		var = LIST_NEXT(var, station_link);
		newstation = new Station[1];
		LIST_INSERT_AFTER(var, newstation, station_link);
		newstation->location = district[order->did].location;
		newstation->oid = order->oid;
		newstation->type = DISTRICT;
		DISTANCE(district[order->did], restaurant[order->rid], distance);
		TIME(distance, time);
		newstation->arrivetime = var->arrivetime + time;
		newstation->leavetime = newstation->arrivetime;
		return Time;
	}

	LIST_FOREACH_FROM(var, head, station_link)
	{
		if ((LIST_NEXT(var, station_link)) != NULL) {
			if (var->location.x == LIST_NEXT(var, station_link)->location.x &&
				var->location.y == LIST_NEXT(var, station_link)->location.y)
			{
				continue;
			}
			DISTANCE((*var), restaurant[order->rid], dist1);
			DISTANCE((*(LIST_NEXT(var, station_link))), restaurant[order->rid], dist2);
			DISTANCE((*var), (*(LIST_NEXT(var, station_link))), dist3);
			distance = dist1 + dist2 - dist3;

		}
		if (distance < mindis) {
			mindis = distance;
			choose = var;
		}
	}

	newstation = new Station[1];
	newstation->station_link.le_next = NULL;
	newstation->station_link.le_prev = NULL;

	DISTANCE((*choose), restaurant[order->rid], dist1);

	//更新新插入餐厅的各项信息

	newstation->arrivetime = choose->leavetime + dist1;
	if (newstation->arrivetime < order->time) {
		newstation->leavetime = order->time;
	}
	else {
		newstation->leavetime = newstation->arrivetime;
	}
	newstation->location.x = x1;
	newstation->location.y = y1;
	newstation->oid = order->oid;
	newstation->type = RESTAURANT;

	//插入

	LIST_INSERT_AFTER(choose, newstation, station_link);

	var = LIST_NEXT(newstation, station_link);

	DISTANCE((*var), restaurant[order->rid], dist2);

	//延迟时间

	delaytime = newstation->leavetime + dist2 - var->arrivetime;


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

	//为插入小区做准备

	var = newstation;
	mindis = 10000;

	//从已经插入的餐厅之后再遍历

	LIST_FOREACH_FROM(var, head, station_link)
	{
		if ((LIST_NEXT(var, station_link)) != NULL) {
			if (var->location.x == LIST_NEXT(var, station_link)->location.x &&
				var->location.y == LIST_NEXT(var, station_link)->location.y && LIST_NEXT(LIST_NEXT(var, station_link), station_link) != NULL)
			{
				continue;
			}
			DISTANCE((*var), district[order->did], dist1);
			DISTANCE((*(LIST_NEXT(var, station_link))), district[order->did], dist2);
			DISTANCE((*var), (*(LIST_NEXT(var, station_link))), dist3);
			distance = dist1 + dist2 - dist3;
		}
		if (distance < mindis) {
			mindis = distance;
			choose = var;
		}
	}

	newstation = new Station[1];
	newstation->station_link.le_next = NULL;
	newstation->station_link.le_prev = NULL;
	DISTANCE((*choose), district[order->did], dist1);

	//更新新插入小区的各项信息

	newstation->arrivetime = choose->leavetime + dist1;

	newstation->leavetime = newstation->arrivetime;

	newstation->location.x = x2;
	newstation->location.y = y2;
	newstation->oid = order->oid;
	newstation->type = DISTRICT;

	//插入小区

	LIST_INSERT_AFTER(choose, newstation, station_link);

	copy_station(newstation, newnewstation);

	var = LIST_NEXT(newstation, station_link);

	DISTANCE((*var), district[order->did], dist2);

	delaytime = newstation->leavetime + dist2 - var->arrivetime;

	LIST_LAST(last, head, station_link);

	copy_station(last, oldlast);

	//更新插入小区之后的各项信息

	LIST_FOREACH_FROM(var, head, station_link)
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

	copy_station(last, newlast);

	//如果新插小区插在链表倒数第二个位置，则以下部分用于比较是插在倒数第二个位置好还是插在链表尾部好

	T1 = cal_bottlenecktime(*head);

	if ((LIST_NEXT(LIST_NEXT(newstation, station_link), station_link)) == NULL) {

		LIST_REMOVE(newstation, station_link);
		LIST_REMOVE(last, station_link);

		copy_station(oldlast, last);


		DISTANCE(district[order->did], (*last), dist1);

		newstation->arrivetime = last->leavetime + dist1;
		newstation->leavetime = newstation->arrivetime;

		LIST_INSERT_TAIL(head, last, last1, station_link);
		LIST_INSERT_AFTER(last, newstation, station_link);

		T2 = cal_bottlenecktime(*head);
		if (T2 <= T1) {
			delete(oldlast);
			delete(newlast);
			delete(newnewstation);
			return T2;
		}
		else {
			LIST_REMOVE(newstation, station_link);
			LIST_REMOVE(last, station_link);

			copy_station(newlast, last);
			copy_station(newnewstation, newstation);

			LIST_INSERT_TAIL(head, newstation, last1, station_link);
			LIST_INSERT_AFTER(newstation, last, station_link);
			delete(oldlast);
			delete(newlast);
			delete(newnewstation);
			return T1;
		}
	}
	else {
		delete(oldlast);
		delete(newlast);
		delete(newnewstation);
		return T1;
	}
}