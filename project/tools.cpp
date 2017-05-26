#include <iostream>
#include "struct.h"
#include "globalvar.h"

Location  place2xy(Place place)
{
	return place.location;
}

District did2district(int did)
{
	return district[did];
}

Restaurant rid2restaurant(int rid)
{
	return restaurant[rid];
}

void station_list_copy(Station_list *from, Station_list *to)//����head��ͷ�������Ƹ���head1��ͷ������
{     
	Station *var1, *var2=NULL, *last=NULL;
	LIST_FOREACH(var1, from, station_link)
	{
		var2 = new Station[1];
		var2->station_link.le_next = NULL;
		var2->station_link.le_prev = NULL;
		var2->arrivetime = var1->arrivetime;
		var2->leavetime = var1->leavetime;
		var2->location = var1->location;
		var2->oid = var1->oid;
		var2->type = var1->type;
		LIST_LAST(last, to, station_link);
		if (last == NULL) {
			LIST_INSERT_HEAD(to, var2, station_link);
		}
		else {
			LIST_INSERT_AFTER(last, var2, station_link);
		}

	}
}

float cal_bottlenecktime(Station_list station_list)	//����һ��stationlist�е�ƿ��ֵ
{
	float bottlenecktime = 0, temp = 0;
	Station *station;
	if (LIST_FIRST(&station_list) == NULL)
		return bottlenecktime;
	LIST_FOREACH2(station, &station_list, station_link)
	{
		if (station->type == DISTRICT)
		{
			temp = station->arrivetime - order[station->oid].time;
			MAX(bottlenecktime, temp, bottlenecktime);
		}
	}
	return bottlenecktime;
}


void free_list(Station_list *head) {                  //free�����ƺõ��������ͷſռ�
	Station *fp = NULL;
	Station *bp = NULL;

	fp = LIST_FIRST(head);
	
	while (fp != NULL) {
		bp = LIST_NEXT(fp, station_link);
		delete(fp);
		fp = bp;
	}

	delete(fp);
	delete(bp);
	delete(head);

}

void copy_station(Station *listfrom, Station *listto) {
	listto->arrivetime = listfrom->arrivetime;
	listto->leavetime = listfrom->leavetime;
	listto->location = listfrom->location;
	listto->oid = listfrom->oid;
	listto->station_link = listfrom->station_link;
	listto->type = listfrom->type;
}

float Insert_order(Order *order, Station_list *head) {      //���Խ�ĳ������������ʿ��Station�б��ز��������ʱ��
	Station *var = NULL;
	Station *choose = NULL;
	Station *newstation = NULL;
	Station *last = NULL;
	Station *oldlast = new Station[1];
	Station *newlast = new Station[1];
	Station *newnewstation = new Station[1];
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
	float T1;
	float T2;                          //���ڱȽ����С�����ڵ����ڶ���λ�ã��ǲ��ڵ����ڶ���λ�úã����ǲ���β����


	LIST_FOREACH(var, head, station_link)             //ȡ�ò�������λ��         
	{
		if ((LIST_NEXT(var, station_link)) != NULL) {
			DISTANCE((*var), restaurant[order->rid], dist1);
			DISTANCE((*(LIST_NEXT(var, station_link))), restaurant[order->rid], dist2);
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

	copy_station(newstation, newnewstation);

	var = LIST_NEXT(newstation, station_link);

	DISTANCE((*var), district[order->did], dist2);

	delaytime = newstation->leavetime + dist2 - var->arrivetime;

	LIST_LAST(last, head, station_link);

	copy_station(last, oldlast);


	LIST_FOREACH_FROM(var, head, station_link)             //���²���С��֮��ĸ�����Ϣ
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

	T1 = cal_bottlenecktime(*head);

	if ((LIST_NEXT(LIST_NEXT(newstation, station_link), station_link)) == NULL) {
		copy_station(oldlast, last);
		LIST_REMOVE(newstation, station_link);
		DISTANCE(district[order->did], (*last), dist1);

		newstation->arrivetime = last->leavetime + dist1;
		newstation->leavetime = newstation->arrivetime;

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
			copy_station(newlast, last);
			copy_station(newnewstation, newstation);
			LIST_INSERT_BEFORE(last, newstation, station_link);
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