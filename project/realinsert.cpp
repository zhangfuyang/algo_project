#include <iostream>
#include "struct.h"
#include "globalvar.h"
#include "function.h"
//��壬��startΪ��������ĵ�һ���ڵ㣬�ڵ�rn���ڵ�����͹ݣ���dn���ڵ�����С������ʱdnΪ�͹��Ѿ�������λ��
void really_insert(Station *start, Order *order, int rn, int dn)
{
	Station *newres = new Station[1];
	newres->location = restaurant[order->rid].location;
	newres->oid = order->oid;
	newres->type = RESTAURANT;

	Station *newdis = new Station[1];
	newdis->location = district[order->did].location;
	newdis->oid = order->oid;
	newdis->type = DISTRICT;

	int i = 0;
	float dist1,dist2;
	float delaytime;
	Station *var;

	int flag1=0, flag2=0;

	LIST_FOREACH_FROM2(start, station_link)
	{
		i++;
		if (i == rn){
			//����͹�
			LIST_INSERT_AFTER(start, newres, station_link);
			//�����²�������ĸ�����Ϣ
			DISTANCE((*start), restaurant[order->rid], dist1);	
			newres->arrivetime = start->leavetime + dist1;
			if (newres->arrivetime < order->time) {
				newres->leavetime = order->time;
			}
			else {
				newres->leavetime = newres->arrivetime;
			}
			//�����²������֮����ڵ�ĸ�����Ϣ
			var = LIST_NEXT(newres, station_link);
			DISTANCE((*var), restaurant[order->rid], dist2);
			//�ӳ�ʱ��
			delaytime = newres->leavetime + dist2 - var->arrivetime;
			LIST_FOREACH_FROM2(var, station_link)
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
			flag1++;
		}
		if (i == dn)
		{
			//�����²���С���ĸ�����Ϣ
			DISTANCE((*start), district[order->did], dist1);		
			newdis->arrivetime = start->leavetime + dist1;
			newdis->leavetime = newdis->arrivetime;

			//����С��
			LIST_INSERT_AFTER(start, newdis, station_link);
			var = LIST_NEXT(newdis, station_link);
			DISTANCE((*var), district[order->did], dist2);
			delaytime = newdis->leavetime + dist2 - var->arrivetime;

			//���²���С��֮��ĸ�����Ϣ
			LIST_FOREACH_FROM(var, head, station_link)
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
			flag2++;
		}
	}
	if (flag1 != 1 | flag2 != 1) {
		printf("������");
		system("pause");
	}
}

//���Խ�ĳ������������ʿ��Station�б��ز��������ʱ��
float Insert_order(Order *order, Station_list *head, int status, Cavalier cav) {
	Station *var = NULL;
	Station *choose = NULL;
	Station *newstation = NULL;
	Station *last = NULL;
	Station *last1 = NULL;
	Station *oldlast = new Station[1];
	Station *newlast = new Station[1];
	Station *newnewstation = new Station[1];

	//�����Ĳ�������

	int x1 = restaurant[order->rid].location.x;
	int y1 = restaurant[order->rid].location.y;

	//������С������

	int x2 = district[order->did].location.x;
	int y2 = district[order->did].location.y;
	float distance;
	float dist1;
	float dist2;
	float dist3;

	//ȡ��̾������

	float mindis = 10000;

	//������޸ĺ����station���õ��ӳ�ʱ��

	float delaytime;

	//���صĲ�����ƿ��ʱ��

	//	float T;                           
	float T1;

	//���ڱȽ����С�����ڵ����ڶ���λ�ã��ǲ��ڵ����ڶ���λ�úã����ǲ���β����

	float T2;

	//ȡ�ò�������λ��
	var = LIST_FIRST(head);
	while (LIST_NEXT(var, station_link) != NULL && var->location.x == LIST_NEXT(var, station_link)->location.x &&
		var->location.y == LIST_NEXT(var, station_link)->location.y)
		//order[var->oid].oid != order[LIST_NEXT(var, station_link)->oid].oid)
	{
		var = LIST_NEXT(var, station_link);
	}
	if (LIST_NEXT(var, station_link) == NULL) //ֻ��һ��Ԫ��
	{
		Station *ttemp;
		float time;
		float time2;
		float Time;
		newstation = new Station[1];
		ttemp = LIST_FIRST(head);
		DISTANCE((*ttemp), restaurant[order->rid], distance);
		TIME(distance, time);
		LIST_INSERT_AFTER(var, newstation, station_link);
		newstation->location = restaurant[order->rid].location;
		newstation->oid = order->oid;
		newstation->type = RESTAURANT;
		if (time + ttemp->leavetime > order->time) //��������
		{
			time2 = time + ttemp->leavetime;
			DISTANCE(district[order->did], restaurant[order->rid], distance);
			TIME(distance, time);
			newstation->arrivetime = time2;
			newstation->leavetime = newstation->arrivetime;
			Time = time + time2;
		}
		else
		{
			newstation->arrivetime = time + ttemp->leavetime;
			newstation->leavetime = order->time;
			DISTANCE(district[order->did], restaurant[order->rid], distance);
			TIME(distance, time);
			Time = time;
		}
		var = LIST_NEXT(var, station_link);
		newstation = new Station[1];
		LIST_INSERT_AFTER(var, newstation, station_link);
		newstation->location = district[order->did].location;
		newstation->oid = order->oid;
		newstation->type = DISTRICT;
		DISTANCE(district[order->did], restaurant[order->rid], distance);
		TIME(distance, time);
		newstation->arrivetime = var->arrivetime + time;
		newstation->leavetime = newstation->arrivetime;
		return Time;
	}

	LIST_FOREACH_FROM(var, head, station_link)
	{
		if ((LIST_NEXT(var, station_link)) != NULL) {
			if (var->location.x == LIST_NEXT(var, station_link)->location.x &&
				var->location.y == LIST_NEXT(var, station_link)->location.y)
			{
				continue;
			}
			DISTANCE((*var), restaurant[order->rid], dist1);
			DISTANCE((*(LIST_NEXT(var, station_link))), restaurant[order->rid], dist2);
			DISTANCE((*var), (*(LIST_NEXT(var, station_link))), dist3);
			distance = dist1 + dist2 - dist3;

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

	//�����²�������ĸ�����Ϣ

	newstation->arrivetime = choose->leavetime + dist1;
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

	//����

	LIST_INSERT_AFTER(choose, newstation, station_link);

	var = LIST_NEXT(newstation, station_link);

	DISTANCE((*var), restaurant[order->rid], dist2);

	//�ӳ�ʱ��

	delaytime = newstation->leavetime + dist2 - var->arrivetime;


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

	//Ϊ����С����׼��

	var = newstation;
	mindis = 10000;

	//���Ѿ�����Ĳ���֮���ٱ���

	LIST_FOREACH_FROM(var, head, station_link)
	{
		if ((LIST_NEXT(var, station_link)) != NULL) {
			if (var->location.x == LIST_NEXT(var, station_link)->location.x &&
				var->location.y == LIST_NEXT(var, station_link)->location.y && LIST_NEXT(LIST_NEXT(var, station_link), station_link) != NULL)
			{
				continue;
			}
			DISTANCE((*var), district[order->did], dist1);
			DISTANCE((*(LIST_NEXT(var, station_link))), district[order->did], dist2);
			DISTANCE((*var), (*(LIST_NEXT(var, station_link))), dist3);
			distance = dist1 + dist2 - dist3;
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

	//�����²���С���ĸ�����Ϣ

	newstation->arrivetime = choose->leavetime + dist1;

	newstation->leavetime = newstation->arrivetime;

	newstation->location.x = x2;
	newstation->location.y = y2;
	newstation->oid = order->oid;
	newstation->type = DISTRICT;

	//����С��

	LIST_INSERT_AFTER(choose, newstation, station_link);

	copy_station(newstation, newnewstation);

	var = LIST_NEXT(newstation, station_link);

	DISTANCE((*var), district[order->did], dist2);

	delaytime = newstation->leavetime + dist2 - var->arrivetime;

	LIST_LAST(last, head, station_link);

	copy_station(last, oldlast);

	//���²���С��֮��ĸ�����Ϣ

	LIST_FOREACH_FROM(var, head, station_link)
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

	copy_station(last, newlast);

	//����²�С�������������ڶ���λ�ã������²������ڱȽ��ǲ��ڵ����ڶ���λ�úû��ǲ�������β����

	T1 = cal_bottlenecktime(*head);

	if ((LIST_NEXT(LIST_NEXT(newstation, station_link), station_link)) == NULL) {

		LIST_REMOVE(newstation, station_link);
		LIST_REMOVE(last, station_link);

		copy_station(oldlast, last);


		DISTANCE(district[order->did], (*last), dist1);

		newstation->arrivetime = last->leavetime + dist1;
		newstation->leavetime = newstation->arrivetime;

		LIST_INSERT_TAIL(head, last, last1, station_link);
		LIST_INSERT_AFTER(last, newstation, station_link);

		T2 = cal_bottlenecktime(*head);
		if (T2 <= T1) {
			delete(oldlast);
			delete(newlast);
			delete(newnewstation);
			return T2;
		}
		else {
			LIST_REMOVE(newstation, station_link);
			LIST_REMOVE(last, station_link);

			copy_station(newlast, last);
			copy_station(newnewstation, newstation);

			LIST_INSERT_TAIL(head, newstation, last1, station_link);
			LIST_INSERT_AFTER(newstation, last, station_link);
			delete(oldlast);
			delete(newlast);
			delete(newnewstation);
			return T1;
		}
	}
	else {
		delete(oldlast);
		delete(newlast);
		delete(newnewstation);
		return T1;
	}
}