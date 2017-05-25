#include <string>
#include"queue.h"
#include"struct.h"
#include"globalvar.h"
#include"function.h"
using namespace std;

//static struct Cav_list cav_free_list;
//static struct Cav_list cav_available_list;
//static struct Cav_list cav_full_list;
//static struct Cav_list cav_list;

void cav_init()
{
	//LIST_INIT(&cav_free_list);
	//LIST_INIT(&cav_available_list);
	//LIST_INIT(&cav_full_list);

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
void cav_update(int time)
{
	int i;
	for(i=1; i<=cavalier_num; i++)
	{
		Station *station, *temp = NULL, *last;
		int pack_release_num = 0;
		//���ظ���״̬ΪFREE��INIT������
		if (cavalier[i].status == FREE | cavalier[i].status == INIT)
		{
			continue;
		}
		//Ѱ�������ڸ�ʱ�̵����DISTRICT
		LIST_FOREACH(station, &cavalier[i].station_list, station_link)
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
			LIST_FOREACH(last, &print[i], station_link)
			{
				if (last->station_link.le_next == NULL)
					break;
			}
			//LIST_LAST(last, &print[i], station_link);
			LIST_FOREACH(station, &cavalier[i].station_list, station_link)
			{
				if (station == temp)
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
			cavalier[i].pack_num -= pack_release_num;
			if (cavalier[i].pack_num == 0)
			{
				cavalier[i].bottlenecktime = 0;
				cavalier[i].status = FREE;
			}
			else
			{
				cavalier[i].bottlenecktime = cal_bottlenecktime(cavalier[i].station_list);
				cavalier[i].status = AVAILABLE;
			}
		}
	}
}

float Insert_order(Order *order, Station_list *head) {      //���Խ�ĳ������������ʿ��Station�б����ز��������ʱ��
	Station *var = NULL;
	Station *choose = NULL;
	Station *newstation = NULL;
	int x1 = restaurant[order->rid].location.x;         //�����Ĳ�������            
	int y1 = restaurant[order->rid].location.y;
	int x2 = district[order->did].location.x;		    //������С������
	int y2 = district[order->did].location.y;
	float distance;
	float dist1;
	float dist2;
	float mindis = 10000;              //ȡ��̾������
	float delaytime;                   //������޸ĺ����station���õ��ӳ�ʱ��
	float T;                           //���صĲ�����ƿ��ʱ��


	LIST_FOREACH(var, head, station_link)             //ȡ�ò�������λ��         
	{
		if ((LIST_NEXT(var, station_link)) != NULL) {
			DISTANCE((*var), restaurant[order->rid], dist1);
			DISTANCE((*(LIST_NEXT(var, station_link))), restaurant[order ->rid], dist2);
			distance = dist1 + dist2;
		}
		if (distance < mindis) {
			mindis = distance;
			choose = var;
		}
	}

	newstation = new Station[1];
	newstation->station_link.le_next = NULL;
	newstation->station_link.le_prev = NULL;

	DISTANCE((*choose), restaurant[order->rid], dist1);

	newstation->arrivetime = choose->leavetime + dist1;         //�����²�������ĸ�����Ϣ
	if (newstation->arrivetime < order->time) {
		newstation->leavetime = order->time;
	}
	else {
		newstation->leavetime = newstation->arrivetime;
	}
	newstation->location.x = x1;
	newstation->location.y = y1;
	newstation->oid = order->oid;
	newstation->type = RESTAURANT;

	LIST_INSERT_AFTER(choose, newstation, station_link);       //����

	var = LIST_NEXT(newstation, station_link);

	DISTANCE((*var), restaurant[order->rid], dist2);

	delaytime = newstation->leavetime + dist2 - var->arrivetime;      //�ӳ�ʱ��


	LIST_FOREACH_FROM(var, head, station_link)
	{
		var->arrivetime = var->arrivetime + delaytime;
		if (var->leavetime >= var->arrivetime) {
			break;
		}
		else {
			delaytime = var->arrivetime - var->leavetime;      //����delaytime
			var->leavetime = var->arrivetime;
		}
	}

	var = newstation;           //Ϊ����С����׼��
	mindis = 10000;

	LIST_FOREACH_FROM(var, head, station_link)            //���Ѿ�����Ĳ���֮���ٱ���
	{
		if ((LIST_NEXT(var, station_link)) != NULL) {
			DISTANCE((*var), district[order->did], dist1);
			DISTANCE((*(LIST_NEXT(var, station_link))), district[order->did], dist2);
			distance = dist1 + dist2;
		}
		if (distance < mindis) {
			mindis = distance;
			choose = var;
		}
	}

	newstation = new Station[1];
	newstation->station_link.le_next = NULL;
	newstation->station_link.le_prev = NULL;

	DISTANCE((*choose), district[order->did], dist1);

	newstation->arrivetime = choose->leavetime + dist1;      //�����²���С���ĸ�����Ϣ

	newstation->leavetime = newstation->arrivetime;
	
	newstation->location.x = x2;
	newstation->location.y = y2;
	newstation->oid = order->oid;
	newstation->type = DISTRICT;

	LIST_INSERT_AFTER(choose, newstation, station_link);     //����С��

	var = LIST_NEXT(newstation, station_link);

	DISTANCE((*var), district[order->did], dist2);

	delaytime = newstation->leavetime + dist2 - var->arrivetime;


	LIST_FOREACH_FROM(var, head, station_link)             //���²���С��֮���
	{
		var->arrivetime = var->arrivetime + delaytime;
		if (var->leavetime >= var->arrivetime) {
			break;
		}
		else {
			delaytime = var->arrivetime - var->leavetime;
			var->leavetime = var->arrivetime;
		}
	}

	T = cal_bottlenecktime(*head);
	return T;
}


