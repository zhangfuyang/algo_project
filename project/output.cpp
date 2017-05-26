#include <iostream>
#include "struct.h"
#include "queue.h"
#include "globalvar.h"
#include "function.h"

using namespace std;

void output()
{
	int i,num; //i是骑士的循环变量 num是骑士[i]有多少个关键路径
	int *order_id;
	float max_time = 0;
	Station *temp, *temp1;
	Station *judge; //判断temp后面的station还是不是相同的
	int size; //骑士背包里还有多少order
	order_id = new int[C];
	for (i = 1; i <= cavalier_num; i++)
	{
		temp = LIST_FIRST(&cavalier[i].station_list);
		if (LIST_FIRST(&print[i]) == NULL)
		{
			print[i].lh_first = temp;
		}
		else
		{
			LIST_LAST(temp1, &print[i], station_link);
			temp1->station_link.le_next = temp;
		}
	}
	for (i = 1; i <= cavalier_num; i++)
	{
		for (int l = 0; l < C; l++)
		{
			order_id[l] = 0;
		}
		size = 0; //size归0
		cout << endl << "**********************************************" << endl;
		LIST_SIZE(temp, &print[i], station_link, num);
		cout << i << " " << num << endl;
		if (num == 0)
			continue;
		temp = LIST_FIRST(&print[i]);
		order_id[size] = temp->oid;
		size++;
		while (1)
		{
			cout << temp->location.x << " " << temp->location.y << " "
				<< temp->arrivetime << " " << temp->leavetime<<" ";
			cout << size;
			for (int l = 0; l < size; l++)
			{
				cout << " " << order_id[l];
			}
			temp = LIST_NEXT(temp, station_link);
			if (temp == NULL)
			{
				break;
			}
			if (temp->type == RESTAURANT)
			{
				order_id[size++] = temp->oid;
			}
			if (temp->type == DISTRICT)
			{
				int l;
				for (l = 0; l < size; l++)
					if (order_id[l] == temp->oid)
						break;
				for (int j = l; j < size - 1; j++)
				{
					order_id[j] = order_id[j + 1];
				}
				size--;
			}
			cout << endl;
		}
	}
	for (i = 1; i <= cavalier_num; i++)
	{
		if (cal_bottlenecktime(print[i]) > max_time)
			max_time = cal_bottlenecktime(print[i]);
	}
	cout << endl <<"**********************************************" << endl;
	cout <<"the least bottlenecktime "<<max_time << endl;
	cout << "the least costtime of all orders theoretically:" << theoretically_time();
	cout << endl << "**********************************************" << endl;
}

void update_after_insert_restaurant(Station *rst, Order* order, Station_list *head)
{
	float delaytime;
	float distance;
	Station *var;
	var = LIST_NEXT(rst, station_link);
	DISTANCE((*var), restaurant[order->rid], distance);
	delaytime = rst->leavetime + distance - var->arrivetime;

	LIST_FOREACH_FROM(var, head, station_link)
	{
		var->arrivetime = var->arrivetime + delaytime;
		if (var->leavetime >= var->arrivetime)
			break;
		else
		{
			delaytime = var->arrivetime - var->leavetime;
			var->leavetime = var->arrivetime;
		}
	}
}

void update_after_insert_district(Station *dst, Order* order, Station_list *head)
{
	Station *var, *last;
	float distance, delaytime, T1, T2;
	var = LIST_NEXT(dst, station_link);
	DISTANCE((*var), district[order->did], distance);
	delaytime = dst->leavetime + distance - var->arrivetime;
	LIST_LAST(last, head, station_link);
	LIST_FOREACH_FROM(var, head, station_link)
	{
		var->arrivetime = var->arrivetime + delaytime;
		if (var->leavetime >= var->arrivetime)
		{
			break;
		}
		else
		{
			delaytime = var->arrivetime - var->leavetime;
			var->leavetime = var->arrivetime;
		}
	}
}