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
		cout << "**********************************************" << endl;
		LIST_SIZE(temp, &cavalier[i].station_list, station_link, num);
		cout << i << " " << num << endl;
		temp = LIST_FIRST(&cavalier[i].station_list);
		size++;
		order_id[size] = temp->oid;
		while (temp != NULL)
		{
			cout << temp->location.x << " " << temp->location.y << " "
				<< temp->arrivetime << " " << temp->leavetime<<" ";
			judge = LIST_NEXT(temp, station_link);
			while (judge->type == temp->type)
			{
				if (temp->type = RESTAURANT)
				{
					size++;
					order_id[size] = judge->oid;
				}
				if (temp->type = DISTRICT)
				{
					size--;
				}
				judge = LIST_NEXT(judge, station_link);
			}
			cout << size;
			for (int l = 0; l < size; l++)
			{
				cout << " " << order_id[l];
			}
			cout << endl;
			temp = judge;
		}
	}
}
