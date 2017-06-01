#include <string>
#include"queue.h"
#include"struct.h"
#include"globalvar.h"
#include"function.h"
using namespace std;


void cav_init()
{
	for (int i = 1; i <= cavalier_num; i++)
	{
		cavalier[i].status = INIT;
		cavalier[i].pack_num = 0;
		cavalier[i].id = i;
		LIST_INIT(&cavalier[i].station_list);
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
		//不必更新状态为FREE或INIT的骑手
		if (cavalier[i].status == FREE | cavalier[i].status == INIT)
		{
			continue;
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





