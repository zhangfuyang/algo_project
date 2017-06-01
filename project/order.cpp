#include <string>
#include"queue.h"
#include"struct.h"
#include"globalvar.h"
#include"function.h"
void order_init_insert(int cavid, Order order)
{
	Station *temp1, *temp2;
	Station *temp_head;
	float distance;
	float time;
	temp1 = new Station[1];
	DISTANCE(restaurant[order.rid], cavalier[cavid], distance);
	TIME(distance, time);
	temp1->arrivetime = order.time + time;
	temp1->leavetime = temp1->arrivetime;
	temp1->location = restaurant[order.rid].location;
	temp1->oid = order.oid;
	temp1->type = RESTAURANT;
	temp_head = cavalier[cavid].station_list.lh_first;
	LIST_INSERT_AFTER(temp_head, temp1, station_link);
	temp2 = new Station[1];
	DISTANCE(restaurant[order.rid], district[order.did], distance);
	TIME(distance, time);
	temp2->arrivetime = temp1->leavetime + time;
	temp2->leavetime = temp2->arrivetime;
	temp2->location = district[order.did].location;
	temp2->oid = order.oid;
	temp2->type = DISTRICT;
	LIST_INSERT_AFTER(temp1, temp2, station_link);
	cavalier[cavid].pack_num++;
	cavalier[cavid].bottlenecktime = cal_bottlenecktime(cavalier[cavid].station_list);
	cav_setstatus(&cavalier[cavid]);
}
void order_free_insert(int cavid, Order order)
{
	Station *temp1, *temp2;
	Station *temp_head, *last;
	float distance;
	float time;
	int center_num;
	Location unit1, unit2;
	center_num = find_near_center(cavid, cavalier[cavid].location);
	unit1 = unit_vector(cavalier[cavid].location, rst_center[center_num].location);
	unit2 = unit_vector(cavalier[cavid].location, restaurant[order.rid].location);
	if (abs(unit1.x - unit2.x) <= 0.001 && abs(unit1.y - unit2.y) <= 0.001)//相同方向
	{

	}
	else
	{
		temp1 = new Station[1];
		temp1->location = cavalier[cavid].location;
		temp1->oid = -1;
		temp1->arrivetime = cavalier[cavid].now;
		temp1->leavetime = temp1->arrivetime;
		temp1->type = LOCATIONNOW;
		temp_head = LIST_FIRST(&cavalier[cavid].station_list);
		temp2 = new Station[1];
		copy_station(temp_head, temp2);
		LIST_LAST(last, &print[cavid], station_link);
		LIST_INSERT_AFTER(last, temp2, station_link);
		LIST_REMOVE(temp_head, station_link);
		delete(temp_head);
		LIST_INSERT_HEAD(&cavalier[cavid].station_list, temp1, station_link);
	}
	temp1 = new Station[1];
	DISTANCE(restaurant[order.rid], cavalier[cavid], distance);
	TIME(distance, time);
	temp1->arrivetime = cavalier[cavid].now + time;
	temp1->leavetime = temp1->arrivetime;
	temp1->location = restaurant[order.rid].location;
	temp1->oid = order.oid;
	temp1->type = RESTAURANT;
	temp_head = LIST_FIRST(&cavalier[cavid].station_list);
	LIST_INSERT_AFTER(temp_head, temp1, station_link);
	temp2 = new Station[1];
	DISTANCE(restaurant[order.rid], district[order.did], distance);
	TIME(distance, time);
	temp2->arrivetime = temp1->leavetime + time;
	temp2->leavetime = temp2->arrivetime;
	temp2->location = district[order.did].location;
	temp2->oid = order.oid;
	temp2->type = DISTRICT;
	LIST_INSERT_AFTER(temp1, temp2, station_link);
	cavalier[cavid].pack_num++;
	cavalier[cavid].bottlenecktime = cal_bottlenecktime(cavalier[cavid].station_list);
	cav_setstatus(&cavalier[cavid]);
}
void order_available_insert(int cavid, Order order)
{
	float time;
	time = Insert_order(&order, &(cavalier[cavid].station_list), FULL, cavalier[cavid]);
	cavalier[cavid].pack_num++;
	cavalier[cavid].bottlenecktime = cal_bottlenecktime(cavalier[cavid].station_list);
	cav_setstatus(&cavalier[cavid]);
}
void order_full_insert(int cavid, Order order)
{
	Station *temp2, *temp, *new_station;
	Station_list *copy_list = new Station_list[1];
	float distance;
	float time;
	Location location;
	Cavalier cav = cavalier[cavid];
	int size = 0, count = 0;
	LIST_FOREACH(temp, &cav.station_list, station_link)
	{
		if (temp->type == DISTRICT)
			size++;
	}
	size -= C;
	size += 1;
	//size表示过多少个小区变成available
	LIST_FOREACH(temp, &cav.station_list, station_link)
	{
		if (temp->type == DISTRICT)
		{
			count++;
		}
		if (count == size)
			break;
	}
	copy_list->lh_first = temp;
	time = Insert_order(&order, copy_list, FULL, cav);
	delete(copy_list);
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
	//printf("order %d -> cavalier %d", order.oid, cavid);
}

