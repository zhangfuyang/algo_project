#include <iostream>
#include "struct.h"
#include "globalvar.h"

//��ȡ������С����λ��
Location  place2xy(Place place)                
{
	return place.location;
}

//��С��id��ȡС���Ľṹ��
District did2district(int did)                  
{
	return district[did];
}

//�ɲ���id��ȡ�����Ľṹ��
Restaurant rid2restaurant(int rid)              
{
	return restaurant[rid];
}

//����from��ͷ��Station�����Ƹ���to��ͷ��Station����
void station_list_copy(Station_list *from, Station_list *to)
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

//����һ��stationlist�е�ƿ��ֵ
float cal_bottlenecktime(Station_list station_list)	
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


//free�����ƺõ��������ͷſռ�
void free_list(Station_list *head) {                  
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

//��listfrom���Station�ṹ���е���Ϣȫ�����Ƹ�listo���Station�ṹ��
void copy_station(Station *listfrom, Station *listto) {          
	listto->arrivetime = listfrom->arrivetime;
	listto->leavetime = listfrom->leavetime;
	listto->location = listfrom->location;
	listto->oid = listfrom->oid;
	listto->station_link.le_next = listfrom->station_link.le_next;
	listto->station_link.le_prev = listfrom->station_link.le_prev;
	listto->type = listfrom->type;
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

//����������ݼ��������ϵ���̵ġ���ȴ�ʱ�䡱
float theoretically_time()                   
{
	int i, maxid = 0;
	float max = 0;
	float distance, time;
	for (i = 1; i <= N; i++)
	{
		DISTANCE(did2district(order[i].did), rid2restaurant(order[i].rid), distance);
		TIME(distance, time);
		if (time > max)
		{
			max = time;
			maxid = i;
		}
	}
	return max;
}

int find_near_center(int cavid)
{
	float max = 1000000;
	int i;
	int rst_center_num;
	float distance;
	for (i = 1; i <= cavalier_num; i++)
	{
		DISTANCE(rst_center[i], cavalier[cavid], distance);
		if (distance < max)
		{
			max = distance;
			rst_center_num = i;
		}
	}
	return rst_center_num;
}

Location unit_vector(Location a, Location b)
{
	Location temp;
	float x, y;
	float length;
	x = b.x - a.x;
	y = b.y - a.y;
	length = sqrt(x*x + y*y);
	temp.x = x / length;
	temp.y = y / length;
	return temp;
}
