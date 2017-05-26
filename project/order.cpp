#include <string>
#include"queue.h"
#include"struct.h"
#include"globalvar.h"
#include"function.h"
void order_init_insert(int cavid, Order order)
{
	Station *temp;
	Station *temp_dst;
	float distance;
	float time;
	temp = new Station[1];
	LIST_INSERT_HEAD(&cavalier[cavid].station_list, temp, station_link);
	temp->arrivetime = order.time;
	temp->leavetime = order.time;
	temp->location = (rid2restaurant(order.rid)).location;
	temp->oid = order.oid;
	//加入小区的关键点
	temp_dst = new Station[1];
	temp->type = RESTAURANT;
	LIST_INSERT_TAIL(&cavalier[cavid].station_list, temp_dst, temp, station_link);
	temp_dst->location = (did2district(order.did)).location;
	temp_dst->oid = order.oid;
	temp_dst->type = DISTRICT;
	DISTANCE((*temp), (*temp_dst), distance);
	TIME(distance, time);
	temp_dst->arrivetime = temp->leavetime + time;
	temp_dst->leavetime = temp->leavetime + time;
	cavalier[cavid].pack_num++;
	cavalier[cavid].bottlenecktime = cal_bottlenecktime(cavalier[cavid].station_list);
	cav_setstatus(&cavalier[cavid]);
}
void order_free_insert(int cavid, Order order)
{
	Station *temp1, *temp2, *temp_dst;
	float distance;
	float time;
	temp2 = new Station[1];
	temp1 = LIST_FIRST(&cavalier[cavid].station_list);
	LIST_INSERT_TAIL(&cavalier[cavid].station_list, temp2, temp1, station_link);
	temp2->location = (rid2restaurant(order.rid)).location;
	temp2->type = RESTAURANT;
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
	temp2->oid = order.oid;
	temp_dst = new Station[1];
	LIST_INSERT_TAIL(&cavalier[cavid].station_list, temp_dst, temp1, station_link);
	temp_dst->oid = order.oid;
	temp_dst->type = DISTRICT;
	temp_dst->location = did2district(order.did).location;
	DISTANCE((*temp_dst), (*temp2), distance);
	TIME(distance, time);
	temp_dst->arrivetime = temp2->leavetime + time;
	temp_dst->leavetime = temp2->leavetime + time;
	cavalier[cavid].pack_num++;
	cavalier[cavid].bottlenecktime = cal_bottlenecktime(cavalier[cavid].station_list);
	cav_setstatus(&cavalier[cavid]);
}
void order_available_insert(int cavid, Order order)
{
	float time;
	time = Insert_order(&order, &(cavalier[cavid].station_list));
	cavalier[cavid].pack_num++;
	cavalier[cavid].bottlenecktime = cal_bottlenecktime(cavalier[cavid].station_list);
	cav_setstatus(&cavalier[cavid]);
}
Station *flag_first, *flag_second;
void order_full_insert(int cavid, Order order)
{
	Station *temp1, *temp2, *new_station;
	float distance;
	float time;
	Location location;
	temp1 = cavalier[cavid].station_list.lh_first;
	while(1)
	{
		if (temp1 == flag_first)
		{
			//插入餐厅并更新
			location = rid2restaurant(order.rid).location;
			new_station = new Station[1];
			new_station->location = location;
			new_station->oid = order.oid;
			new_station->type = RESTAURANT;
			DISTANCE((*temp1), restaurant[order.rid], distance);
			TIME(distance, time);
			new_station->arrivetime = temp1->leavetime + time;
			if (new_station->arrivetime < order.time)
			{
				new_station->leavetime = order.time;
			}
			else
			{
				new_station->leavetime = new_station->arrivetime;
			}
			LIST_INSERT_AFTER(temp1, new_station, station_link);
			update_after_insert_restaurant(new_station, &order, &(cavalier[cavid].station_list));
		}
		if (temp1 == flag_second)
		{ 
			//插入小区并更新
			location = did2district(order.did).location;
			new_station = new Station[1];
			new_station->location = location;
			new_station->oid = order.oid;
			new_station->type = DISTRICT;
			DISTANCE((*temp1), district[order.did], distance);
			TIME(distance, time);
			new_station->arrivetime = temp1->leavetime + time;
			new_station->arrivetime = new_station->leavetime;
			LIST_INSERT_AFTER(temp1, new_station, station_link);
			update_after_insert_district(new_station, &order, &(cavalier[cavid].station_list));
		}
		temp1 = temp1->station_link.le_next;
	}
	//LIST_INSERT_TAIL(&cavalier[cavid].station_list, temp2, temp1, station_link);
	////temp1是最后一个小区   temp2是新的order
	//temp2->location = (rid2restaurant(order.rid)).location;
	//temp2->type = RESTAURANT;
	//DISTANCE((*temp1), rid2restaurant(order.rid), distance);
	//TIME(distance, time);
	//if (time + temp1->arrivetime < order.time)
	//{
	//	temp2->arrivetime = temp1->leavetime + time;
	//	temp2->leavetime = order.time;
	//}
	//else
	//{
	//	temp2->arrivetime = temp1->leavetime + time;
	//	temp2->leavetime = temp1->leavetime + time;
	//}
	//temp2->oid = order.oid;
	//temp_dst = new Station[1];
	//LIST_INSERT_TAIL(&cavalier[cavid].station_list, temp_dst, temp1, station_link);
	//temp_dst->location = did2district(order.did).location;
	//temp_dst->oid = order.oid;
	//temp_dst->type = DISTRICT;
	//DISTANCE((*temp_dst), (*temp2), distance);
	//TIME(distance, time);
	//temp_dst->arrivetime = temp2->leavetime + time;
	//temp_dst->leavetime = temp2->leavetime + time;
	cavalier[cavid].pack_num++;
	cavalier[cavid].bottlenecktime = cal_bottlenecktime(cavalier[cavid].station_list);
	cav_setstatus(&cavalier[cavid]);
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

