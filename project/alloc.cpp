#include <string>
#include"queue.h"
#include"struct.h"
#include"globalvar.h"
#include"function.h"

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

void alloc(Order order)
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