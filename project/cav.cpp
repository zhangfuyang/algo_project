#include <string>
#include"queue.h"
#include"struct.h"
#include"globalvar.h"
#include"function.h"
using namespace std;


void cav_init()
{
	Station *temp;
	for (int i = 1; i <= cavalier_num; i++)
	{
		cavalier[i].status = INIT;
		cavalier[i].pack_num = 0;
		cavalier[i].id = i;
		cavalier[i].now = 0;
		cavalier[i].location = rst_center[i].location;
		LIST_INIT(&cavalier[i].station_list);
		cavalier[i].location = rst_center[i].location;
		temp = new Station[1];
		LIST_INSERT_HEAD(&cavalier[i].station_list, temp, station_link);
		temp->arrivetime = 0;
		temp->leavetime = 0;
		temp->location = cavalier[i].location;
		temp->oid = -1;
		temp->type = DISTRICT;
	}
}

void print_init()
{
	for (int i = 1; i <= cavalier_num; i++)
	{
		LIST_INIT(&print[i]);
	}
}

void cav_setstatus(Cavalier *cav)
{
	int status = cav->status;

	if (cav->pack_num < 0)
	{
		printf("pack_num error! cavalier id : %d\n", cav->id);
	}
	else if(cav->pack_num == 0)
	{
		cav->status = FREE;
	}
	else if (cav->pack_num >= C)
	{
		cav->status = FULL;
	}
	else
	{
		cav->status = AVAILABLE;
	}
//	printf("set cav %d status��%d -> %d\n", cav->id, status, cav->status);
}

void cav_update(float time)
{
//	printf("cav_update! time = %f\n", time);

	int i;
	for(i=1; i<=cavalier_num; i++)
	{
		Station *station, *temp = NULL, *last, *print_insert;
		Station *temp2;
		int pack_release_num = 0;
		//����״̬ΪFREE��INIT�����֣�����������������
		int center_num;//������ľ۵�
		Location unit;//��λ����
		float distance;
		if (cavalier[i].status == FREE)
		{
			center_num = find_near_center(i, cavalier[i].location);
			unit = unit_vector(cavalier[i].station_list.lh_first->location, rst_center[center_num].location);
			DISTANCE(cavalier[i], rst_center[center_num], distance);
			if (time - cavalier[i].station_list.lh_first->leavetime > distance)//�ܵ��˾۵�
			{
				cavalier[i].location = rst_center[center_num].location;
				cavalier[i].now = time;
			}
			else//û�ܵ��۵�
			{
				temp = cavalier[i].station_list.lh_first;
				cavalier[i].location.x = temp->location.x + unit.x * (time - temp->leavetime);
				cavalier[i].location.y = temp->location.y + unit.y * (time - temp->leavetime);
				cavalier[i].now = time;
			}
			if (cavalier[i].station_list.lh_first->station_link.le_next != NULL)
			{
				printf("free��ʿ��Ϊ�գ�������\n");
				system("pause");
			}
			continue;
		}
		if (cavalier[i].status == INIT)
		{
			cavalier[i].now = time;
			continue;
		}
		//Ѱ�������ڸ�ʱ�̵����DISTRICT
		LIST_FOREACH(station, &cavalier[i].station_list, station_link)
		{
			if (station == LIST_FIRST(&cavalier[i].station_list))//��һ��С���������ж�
				continue;
			if (station->arrivetime <= time)
			{
				if (station->type == DISTRICT)
				{
					temp = station;
					pack_release_num++;
				}
				else if (station->type == RESTAURANT)
				{
					continue;
				}
			}
			else
			{
				break;
			}
		}
		
		//���ҵ�DISTRICT֮ǰ��·���Ƴ���������print
		if (temp != NULL)
		{
		//	printf("update cav %d:	 order %d	type:%d		arrivetime: %f\n", i, temp->oid, temp->type, temp->arrivetime);
			LIST_LAST(last, &print[i], station_link);
			LIST_FOREACH(station, &cavalier[i].station_list, station_link)
			{	
				if (station == temp)
				{
					break;
				}
				else
				{
					print_insert = new Station[1];
					copy_station(station, print_insert);
					if (last != NULL)
					{
						LIST_INSERT_AFTER(last, print_insert, station_link);
						last = print_insert;
					}
					else
					{
						LIST_INSERT_HEAD(&print[i], print_insert, station_link);
						last = print_insert;
					}
					
				}
			}
			station = LIST_FIRST(&cavalier[i].station_list);
			while(station != temp)
			{
				temp2 = station->station_link.le_next;
				LIST_REMOVE(station, station_link);
				delete(station);
				station = temp2;
			}
			if (station->station_link.le_next != NULL)//����û����Ķ���
			{
				Station *rst, *rst_copy, *rst_print;
				rst = station->station_link.le_next;
				if (rst->leavetime <= time) //˵�����˲���
				{
					unit = unit_vector(rst->location, rst->station_link.le_next->location);
					cavalier[i].location.x = (time - rst->leavetime) * unit.x + rst->location.x;
					cavalier[i].location.y = (time - rst->leavetime) * unit.y + rst->location.y;
					cavalier[i].now = time;
				}
				else //��û������
				{
					unit = unit_vector(station->location, rst->location);
					cavalier[i].location.x = (time - station->leavetime) * unit.x + station->location.x;
					cavalier[i].location.y = (time - station->leavetime) * unit.y + station->location.y;
					cavalier[i].now = time;
				}
			}
			else //û�б�Ķ����ˣ������ͬ��free
			{
				temp = cavalier[i].station_list.lh_first;
				center_num = find_near_center(i, temp->location);
				unit = unit_vector(cavalier[i].station_list.lh_first->location, rst_center[center_num].location);
				DISTANCE((*temp), rst_center[center_num], distance);
				if (time - temp->leavetime > distance)//�ܵ��˾۵�
				{
					cavalier[i].location = rst_center[center_num].location;
					cavalier[i].now = time;
				}
				else//û�ܵ��۵�
				{
					cavalier[i].location.x = temp->location.x + unit.x * (time - cavalier[i].station_list.lh_first->leavetime);
					cavalier[i].location.y = temp->location.y + unit.y * (time - cavalier[i].station_list.lh_first->leavetime);
					cavalier[i].now = time;
				}
				if (cavalier[i].station_list.lh_first->station_link.le_next != NULL)
				{
					printf("free��ʿ��Ϊ�գ�������\n");
					system("pause");
				}
			}
		}
		//���¸�����״̬
		if (pack_release_num != 0)
		{
			cavalier[i].pack_num -= pack_release_num;
			cav_setstatus(&cavalier[i]);
			cavalier[i].bottlenecktime = cal_bottlenecktime(cavalier[i].station_list);
		}
	}
}





