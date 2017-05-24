#include <string>
#include "struct.h"
#include "queue.h"
#include "function.h"
#include "globalvar.h"

float find_free_costtime(Cavalier cav, Order order)  //��Free�б�Ϊ��ʱ����Free�б��е���ʿ���䶩��
{
	float time = order.time;
	float distance;
	float origintime;
	float time_dst; //distance�ľ���
	DISTANCE((*cav.station_list.lh_first), restaurant[order.rid], distance);
	TIME(distance, time_dst);
	if (time_dst + cav.station_list.lh_first->arrivetime > time)
	{
		printf("Free; �Ƕ������ҵ����\n");
		origintime = (time_dst + cav.station_list.lh_first->arrivetime) - time;
		DISTANCE(did2district(order.did), rid2restaurant(order.rid), distance);
		TIME(distance, time);
		return origintime + time;
	}
	else
	{
		printf("Free; ���ҵȶ��������\n");
		DISTANCE(did2district(order.did), rid2restaurant(order.rid), distance);
		TIME(distance, time);
		return time;
	}
}
float find_init_costtime(Cavalier cav, Order order)
{
	float time;
	float distance;

	DISTANCE(did2district(order.did), rid2restaurant(order.rid), distance);
	TIME(distance, time);
	printf("init;����init����\n");
	return time;
}
float find_full_costtime(Cavalier cav, Order order)
{
	float time = order.time;
	float time_dst;
	float distance;
	float origintime;
	Station *temp;
	DISTANCE((*cav.station_list.lh_first), restaurant[order.rid], distance);
	TIME(distance, time_dst);
	temp = cav.station_list.lh_first;
	while (LIST_NEXT(temp, station_link) != NULL)
	{
		temp = LIST_NEXT(temp, station_link);
	}
	if (time_dst + temp->arrivetime > time)
	{
		printf("full;����full����\n");
		origintime = time_dst + temp->arrivetime - time;
		DISTANCE(did2district(order.did), rid2restaurant(order.rid), distance);
		TIME(distance, time);
		return origintime + time;
	}
	else
	{
		printf("full;���ǲ�Ӧ�ý������!!!!!!�����ˣ��Ͻ�ȥ��\n");
		DISTANCE(did2district(order.did), rid2restaurant(order.rid), distance);
		TIME(distance, time);
		return time;
	}
}

void alloc(Order *order)
{
	Cavalier *cav, *free_cav, *available_cav, *full_cav;
	float free_costtime, available_costtime, full_costtime;
	
	free_costtime = find_free_cavalier(order, free_cav);

	available_costtime = find_available_cavalier(order, available_cav);

	full_costtime = find_full_cavalier(order, full_cav);

	if (free_costtime > 0 & available_costtime > 0 & full_costtime > 0)
	{
		MIN(free_time, 
	}
}