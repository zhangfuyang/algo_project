#include <iostream>
#include "struct.h"
#include "queue.h"
#include "globalvar.h"
#include "function.h"

using namespace std;

void output(Station_list *print)
{
	int i,num; //i����ʿ��ѭ������ num����ʿ[i]�ж��ٸ��ؼ�·��
	int *order_id;
	Station *temp;
	Station *judge; //�ж�temp�����station���ǲ�����ͬ��
	int size; //��ʿ�����ﻹ�ж���order
	order_id = new int[C];
	for (i = 1; i <= cavalier_num; i++)
	{
		size = 0; //size��0
		cout << "**********************************************" << endl;
		LIST_SIZE(temp, &cavalier[i].station_list, station_link, num);
		cout << i << " " << num << endl;
		temp = LIST_FIRST(&cavalier[i].station_list);
		size++;
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
				}
				if (temp->type = DISTRICT)
				{
					size--;
				}
				judge = LIST_NEXT(judge, station_link);
			}
			cout << size << " ";
			
			cout << endl;
			temp = judge;
		}
	}
}
