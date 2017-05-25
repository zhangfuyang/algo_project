#include <string>
#include"queue.h"
#include"struct.h"
#include"globalvar.h"
#include"function.h"
void order_init_insert(int cavid, Order order)
{
	Station *temp;
	temp = new Station[1];
	cavalier[cavid].status = AVAILABLE;
	LIST_FIRST(&cavalier[cavid].station_list) = temp;
	temp->arrivetime = order.time;
	temp->leavetime = order.time;
	temp->location = (rid2restaurant(order.rid)).location;
	temp->oid = order.oid;
	LIST_NEXT(temp, station_link) = NULL;
	temp->type = RESTAURANT;
	cavalier[cavid].pack_num++;
	cavalier[cavid].bottlenecktime = cal_bottlenecktime(cavalier[cavid].station_list);
}
void order_free_insert(int cavid, Order order)
{
	Station *temp1, *temp2;
	float distance;
	float time;
	temp2 = new Station[1];
	cavalier[cavid].status = AVAILABLE;
	temp1 = LIST_FIRST(&cavalier[cavid].station_list);
	LIST_NEXT(temp1, station_link) = temp2;
	DISTANCE((*temp2), rid2restaurant(order.rid), distance);
	TIME(distance, time);
	if (time + temp1->arrivetime < order.time)
	{
		temp2->arrivetime = temp1->leavetime + time;
		temp2->leavetime = order.time;
	}
	else
	{
		temp2->arrivetime = temp1->leavetime + time;
		temp2->leavetime = temp1->leavetime + time;
	}
	temp2->location = (rid2restaurant(order.rid)).location;
	temp2->oid = order.oid;
	LIST_NEXT(temp2, station_link) = NULL;
	temp2->type = RESTAURANT;
	cavalier[cavid].pack_num++;
	cavalier[cavid].bottlenecktime = cal_bottlenecktime(cavalier[cavid].station_list);
}
void order_insert(int cavid, Order order)
{
	switch (cavalier[cavid].status)
	{
	case INIT:
		order_init_insert(cavid, order);
		break;
	case FREE:
		order_free_insert(cavid, order);
		break;
	case AVAILABLE:
		order_available_insert(cavid, order);
		break;
	case FULL:
		order_full_insert(cavid, order);
		break;
	default:
		printf("invalid cavalier! id : %d", cavid);
		break;
	}
	printf("order %d -> cavalier %d", order.oid, cavid);
}

