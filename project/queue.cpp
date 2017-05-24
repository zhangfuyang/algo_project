#include <string>
#include "struct.h"
#include "queue.h"
#include "function.h"
#include "globalvar.h"
using namespace std;

static struct Cav_list cav_free_list;
static struct Cav_list cav_available_list;
static struct Cav_list cav_full_list;

void queue_init()
{
	LIST_INIT(&cav_free_list);
	LIST_INIT(&cav_available_list);
	LIST_INIT(&cav_full_list);

	for (int i = cavalier_num; i >= 0; i--)
	{
		cavalier[i].status = INIT;
		cavalier[i].pack_num = 0;
		LIST_INIT(&cavalier[i].station_list);
		LIST_INSERT_HEAD(&cav_free_list, &cavalier[i], cav_link);
	}
}

void queue_update(int time, Cav_list cav_list)
{
	Cavalier *cav;
	LIST_FOREACH(cav, &cav_list, cav_link)
	{
		Station *station, *temp = NULL, *last;
		int pack_release_num = 0;
		//Ѱ�������ڸ�ʱ�̵����DISTRICT
		LIST_FOREACH(station, &cav->station_list, station_link)
		{
			if (station->arrivetime <= time)
			{
				if (station->type = DISTRICT)
				{
					temp = station;
					pack_release_num++;
				}
				else if (station->type = RESTAURANT)
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
			LIST_LAST(last, &print[cav->id], station_link);
			LIST_FOREACH(station, &cav->station_list, station_link)
			{
				if (station = temp)
				{
					break;
				}
				else
				{
					LIST_INSERT_AFTER(last, station, station_link);
					LIST_REMOVE(station, station_link);
				}
			}
		}
		//���¸�����״̬
		if (pack_release_num != 0)
		{
			cav->pack_num -= pack_release_num;
			if (cav->pack_num == 0)
			{
				cav->bottlenecktime = 0;
				cav->status = FREE;
				LIST_CHANGE(cav, &cav_free_list, cav_link);
			}
			else
			{
				cav->bottlenecktime = cal_bottlenecktime(cav->station_list);
				cav->status = AVAILABLE;
				LIST_CHANGE(cav, &cav_free_list, cav_link);
			}
		}
	}
}

void find_free_cavalier(Order *order, Cavalier *cav)  //��Free�б�Ϊ��ʱ����Free�б��е���ʿ���䶩��
{
	float time = order->time;
	float distance;
	float origintime = 10000;
	Cavalier *luckyone;
	LIST_FOREACH(luckyone, &cav_free_list, cav_link)
	{
		DISTANCE((*LIST_FIRST(&luckyone->station_list)), restaurant[order->rid], distance);
		
		if (distance + LIST_FIRST(&luckyone->station_list)->arrivetime < time) {  //arrivetime��leavetime��ͬ
			if (time - (distance + LIST_FIRST(&luckyone->station_list)->arrivetime) < origintime){
				origintime = time - (distance + LIST_FIRST(&luckyone->station_list)->arrivetime);
				cav = luckyone;
			}
	
		}
	}
	if (origintime == 10000) {
		LIST_FOREACH(luckyone, &cav_free_list, cav_link)
		{
			DISTANCE((*LIST_FIRST(&luckyone->station_list)), restaurant[order->rid], distance);
			
			if (distance + LIST_FIRST(&luckyone->station_list)->arrivetime < origintime) {
				origintime = distance + LIST_FIRST(&luckyone->station_list)->arrivetime;
				cav = luckyone;
			}
		}

	}
}


float Insert_order(Order *order, Station_list head) {           //���ز��������ʱ��
	Station *var = NULL;
	int x1 = restaurant[order->rid].location.x;
	int y1 = restaurant[order->rid].location.y;
	int x2 = restaurant[order->did].location.x;
	int y2 = restaurant[order->did].location.y;




}



