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
	int max_time = 0;
	Station *temp;
	Station *judge; //判断temp后面的station还是不是相同的
	int size; //骑士背包里还有多少order
	order_id = new int[C];
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
		if (cal_bottlenecktime(cavalier[i].station_list) > max_time)
			max_time = cal_bottlenecktime(cavalier[i].station_list);
	}
	cout << endl<<max_time;
}
