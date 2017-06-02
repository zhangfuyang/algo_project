#include <string>
#include"queue.h"
#include"struct.h"
#include"globalvar.h"
#include"function.h"

float cal_free_costtime(Cavalier cav, Order order)  //当Free列表不为空时，给Free列表中的骑士分配订单
{
	float time1, time2;
	float distance1, distance2;
	DISTANCE(cav, restaurant[order.rid], distance1);
	TIME(distance1, time1);
			//printf("Free; 是订单等我的情况\n");
	DISTANCE(did2district(order.did), rid2restaurant(order.rid), distance2);
	TIME(distance2, time2);
	return time1 + time2;
}
float cal_init_costtime(Cavalier cav, Order order)
{
	float time1, time2;
	float distance1, distance2;
	DISTANCE(cav, restaurant[order.rid], distance1);
	TIME(distance1, time1);
	DISTANCE(did2district(order.did), rid2restaurant(order.rid), distance2);
	TIME(distance2, time2);
	//printf("init;我是init骑手\n");
	return time1 + time2;
}
float cal_full_costtime(Cavalier cav, Order order)
{
	float time;
	Station *temp;
	Station_list *copy_list1 = new Station_list[1];
	Station_list *copy_list2 = new Station_list[1];
	LIST_INIT(copy_list1);
	LIST_INIT(copy_list2);

	//	station_list_copy(&cav.station_list, copy_list2);
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
	copy_list1->lh_first = temp;
	station_list_copy(copy_list1, copy_list2);
	delete(copy_list1);
	time = Insert_order(&order, copy_list2, FULL, cav);
	free_list(copy_list2);
	return time;
}
float cal_available_costtime(Cavalier cav, Order order) {     //返回将order给该骑士后的瓶颈时间
	float T;
	Station_list *head_copy = new Station_list[1];

	LIST_INIT(head_copy);

	station_list_copy(&(cav.station_list), head_copy);
	T = Insert_order(&order, head_copy, AVAILABLE, cav);
	free_list(head_copy);

	return T;
}
int alloc(Order order)
{
	int i,cavid = 0;
	float temptime, costtime = -1;

	for (i = 1; i <= cavalier_num; i++)
	{
		switch (cavalier[i].status)
		{
		case INIT:
			temptime = cal_init_costtime(cavalier[i], order);
			break;
		case FREE:
			temptime = cal_free_costtime(cavalier[i], order);
			break;
		case AVAILABLE:
			temptime = cal_available_costtime(cavalier[i], order);
			break;
		case FULL:
			temptime = cal_full_costtime(cavalier[i], order);
			break;
		default:
			printf("invalid cavalier! id : %d",i);
			break;
		}
		if (costtime == -1)
		{
			costtime = temptime;
			cavid = i;
		}
		else
		{
			if (temptime < costtime)
			{
				costtime = temptime;
				cavid = i;
			}
		}
	}
	return cavid;
}



