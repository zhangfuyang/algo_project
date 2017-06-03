#include <iostream>
#include <fstream>
#include "struct.h"
#include "queue.h"
#include "globalvar.h"
#include "function.h"

using namespace std;

void output()
{
	int i,num; //i����ʿ��ѭ������ num����ʿ[i]�ж��ٸ��ؼ�·��
	int *order_id;
	int io;
	float max_time = 0;
	Station *temp, *temp1;
	char file[20];
	ofstream out;
	int size; //��ʿ�����ﻹ�ж���order
	order_id = new int[C];
	cout << "����̨�������밴1.\n";
	cout << "���������ļ��밴2.\n";
	cin >> io;
	if (io == 2)
	{
		cout << "������������ļ���:";
		cin >> file;
		out.open(file, ios::out);
		//		out.open(file, ios::out, 0);
	}
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
		size = 0; //size��0
		if (io == 2)
		{
			out << endl << "**********************************************" << endl;
		}
		else
		{
			cout << endl << "**********************************************" << endl;
		}
		LIST_SIZE(temp, &print[i], station_link, num);
		if (io == 2)
		{
			out << i << " " << num << endl;
		}
		else
		{
			cout << i << " " << num << endl;
		}
		if (num == 0)
			continue;
		temp = LIST_FIRST(&print[i]);
		while (1)
		{
			if (io == 2)
			{
				out << temp->location.x << " " << temp->location.y << " "
					<< temp->arrivetime << " " << temp->leavetime << " ";
				out << size;
			}
			else
			{
				cout << temp->location.x << " " << temp->location.y << " "
					<< temp->arrivetime << " " << temp->leavetime << " ";
				cout << size;
			}
			for (int l = 0; l < size; l++)
			{
				if (io == 2)
				{
					out << " " << order_id[l];
				}
				else
				{
					cout << " " << order_id[l];
				}
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
			if (io == 2)
			{
				out << endl;
			}
			else
			{
				cout << endl;
			}
		}
	}
	for (i = 1; i <= cavalier_num; i++)
	{
		if (cal_bottlenecktime(print[i]) > max_time)
		{
			max_time = cal_bottlenecktime(print[i]);
		}

	}
	if (io == 2)
	{
		out << endl << "**********************************************" << endl;
		out << "the least bottlenecktime " << max_time << endl;
		out << "the least costtime of all orders theoretically:" << theoretically_time();
		out << endl << "**********************************************" << endl;
	}
	else
	{
		cout << endl << "**********************************************" << endl;
		cout << "the least bottlenecktime " << max_time << endl;
		cout << "the least costtime of all orders theoretically:" << theoretically_time();
		cout << endl << "**********************************************" << endl;
	}
}

