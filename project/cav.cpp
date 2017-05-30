#include <string>
#include"queue.h"
#include"struct.h"
#include"globalvar.h"
#include"function.h"
using namespace std;


void cav_init()
{
	//LIST_INIT(&cav_free_list);
	//LIST_INIT(&cav_available_list);
	//LIST_INIT(&cav_full_list);
	Station *temp;
	for (int i = 1; i <= cavalier_num; i++)
	{
		cavalier[i].status = INIT;
		cavalier[i].pack_num = 0;
		cavalier[i].id = i;
		cavalier[i].now = 0;
		cavalier[i].location = rst_center[i].location;
		LIST_INIT(&cavalier[i].station_list);
		/*temp = new Station[1];
		LIST_INSERT_HEAD(&cavalier[i].station_list, temp, station_link);
		temp->arrivetime = -1;
		temp->leavetime = -1;
		temp->location = cavalier[i].location;
		temp->oid = -1;
		temp->type = LOCATIONNOW;*/
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
//	printf("set cav %d status：%d -> %d\n", cav->id, status, cav->status);
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
		//更新状态为FREE或INIT的骑手！！！！！！！！！
		int center_num;//找最近的聚点
		Location unit;//单位向量
		float distance;
		if (cavalier[i].status == FREE | cavalier[i].status == INIT)
		{
			center_num = find_near_center(i);
			unit = unit_vector(cavalier[i].location, rst_center[center_num].location);
			DISTANCE(cavalier[i], rst_center[center_num], distance);
			if (time - cavalier[i].now > distance)//跑到了聚点
			{
				cavalier[i].location = rst_center[center_num].location;
			}
			else//没跑到聚点
			{
				cavalier[i].location.x = cavalier[i].location.x + unit.x * (time - cavalier[i].now);
				cavalier[i].location.y = cavalier[i].location.y + unit.y * (time - cavalier[i].now);
			}
			cavalier[i].now = time;
		}
		//寻找骑手在该时刻到达的DISTRICT
		LIST_FOREACH(station, &cavalier[i].station_list, station_link)
		{
			if (station == LIST_FIRST(&cavalier[i].station_list))//第一个小区不进行判断
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
		
		//将找的DISTRICT之前的路径移除，并插入print
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
		}
		//更新该骑手状态
		if (pack_release_num != 0)
		{
			cavalier[i].pack_num -= pack_release_num;
			cav_setstatus(&cavalier[i]);
			cavalier[i].bottlenecktime = cal_bottlenecktime(cavalier[i].station_list);
		}
	}
}





