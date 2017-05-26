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
	if (head->lh_first == NULL) //˵��ֻ����C = 1, ������full�����
	{
		Station *ttemp;
		float time;
		float time2;
		newstation = new Station[1];
		ttemp = LIST_FIRST(&cav.station_list);
		ttemp = LIST_NEXT(ttemp, station_link);
		flag_first_full[cav.id] = ttemp;
		flag_second_full[cav.id] = ttemp;
		DISTANCE((*ttemp), restaurant[order->rid], distance);
		TIME(distance, time);
		if (time + ttemp->arrivetime > order->time)
		{
			time2 = time + ttemp->arrivetime - order->time;
			DISTANCE(district[order->did], restaurant[order->rid], distance);
			TIME(distance, time);
			return time + time2;
		}
		else
		{
			DISTANCE(district[order->did], restaurant[order->rid], distance);
			TIME(distance, time);
			return time;
		}
	}
	if (head->lh_first->station_link.le_next == NULL) //ֻ��һ��С��
	{
		Station *ttemp;
		Station_list *cop = new Station_list[1];
		LIST_INIT(cop);
		float time, TT1, TT2, TT3;
		//ȫ����С��ǰ��
		station_list_copy(head, cop);
		newstation = new Station[1];
		newstation->location = restaurant[order->rid].location;
		newstation->oid = order->oid;
		newstation->type = RESTAURANT;
		LIST_INSERT_HEAD(cop, newstation, station_link);
		ttemp = LIST_FIRST(cop);
		DISTANCE((*ttemp), (*newstation), distance);
		TIME(distance, time);
		newstation->arrivetime = ttemp->leavetime + time;
		if (ttemp->leavetime + time > order->time) //��������
		{
			newstation->leavetime = newstation->arrivetime;
		}
		else //�ҵȶ���
		{
			newstation->leavetime = order->time;
		}
		newstation = new Station[1];
		newstation->location = district[order->did].location;
		newstation->oid = order->oid;
		newstation->type = DISTRICT;
		LIST_INSERT_AFTER(cop->lh_first, newstation, station_link);
		ttemp = cop->lh_first;
		DISTANCE((*ttemp), (*newstation), distance);
		TIME(distance, time);
		newstation->arrivetime = ttemp->leavetime + time;
		newstation->leavetime = newstation->arrivetime;
		ttemp = LIST_NEXT(newstation, station_link);
		DISTANCE((*ttemp), (*newstation), distance);
		TIME(distance, time);
		ttemp->arrivetime = newstation->leavetime + time;
		ttemp->leavetime = ttemp->arrivetime;
		TT1 = cal_bottlenecktime(*cop);
		free_list(cop);
		//finished

		//����С������
		cop = new Station_list[1];
		LIST_INIT(cop);
		newstation = new Station[1];
		station_list_copy(head, cop);
		newstation->location = restaurant[order->rid].location;
		newstation->oid = order->oid;
		newstation->type = RESTAURANT;
		LIST_INSERT_HEAD(cop, newstation, station_link);
		ttemp = LIST_FIRST(cop);
		DISTANCE((*ttemp), (*newstation), distance);
		TIME(distance, time);
		newstation->arrivetime = ttemp->leavetime + time;
		if (ttemp->leavetime + time > order->time) //��������
		{
			newstation->leavetime = newstation->arrivetime;
		}
		else //�ҵȶ���
		{
			newstation->leavetime = order->time;
		}
		ttemp = LIST_NEXT(newstation, station_link);
		DISTANCE((*ttemp), (*newstation), distance);
		TIME(distance, time);
		ttemp->arrivetime = newstation->leavetime + time;
		ttemp->leavetime = ttemp->arrivetime;
		newstation = new Station[1];
		newstation->location = district[order->did].location;
		newstation->oid = order->oid;
		newstation->type = DISTRICT;
		LIST_INSERT_AFTER(ttemp, newstation, station_link);
		DISTANCE((*ttemp), (*newstation), distance);
		TIME(distance, time);
		newstation->arrivetime = ttemp->leavetime + time;
		newstation->leavetime = newstation->arrivetime;
		TT2 = cal_bottlenecktime(*cop);
		free_list(cop);
		//finished

		//������С������
		cop = new Station_list[1];
		LIST_INIT(cop);
		newstation = new Station[1];
		station_list_copy(head, cop);
		ttemp = LIST_FIRST(cop);
		newstation->location = restaurant[order->rid].location;
		newstation->oid = order->oid;
		newstation->type = RESTAURANT;
		LIST_INSERT_AFTER(ttemp, newstation, station_link);
		DISTANCE((*ttemp), (*newstation), distance);
		TIME(distance, time);
		newstation->arrivetime = ttemp->leavetime + time;
		if (ttemp->leavetime + time > order->time) //��������
		{
			newstation->leavetime = newstation->arrivetime;
		}
		else //�ҵȶ���
		{
			newstation->leavetime = order->time;
		}
		ttemp = newstation;
		newstation = new Station[1];
		newstation->location = district[order->did].location;
		newstation->oid = order->oid;
		newstation->type = DISTRICT;
		LIST_INSERT_AFTER(ttemp, newstation, station_link);
		DISTANCE((*ttemp), (*newstation), distance);
		TIME(distance, time);
		newstation->arrivetime = ttemp->leavetime + time;
		newstation->leavetime = newstation->arrivetime;
		TT3 = cal_bottlenecktime(*cop);
		free_list(cop);
		//finish

		if (TT1 < TT2)
		{
			if (TT1 < TT3)
			{
				LIST_FOREACH(var, &cav.station_list, station_link)
				{
					if (LIST_NEXT(var, station_link)->oid == LIST_FIRST(head)->oid && LIST_NEXT(var, station_link)->type == LIST_FIRST(head)->type)
						break;
				}
				flag_first_full[cav.id] = var;
				flag_second_full[cav.id] = flag_first_full[cav.id];
				return TT1;
			}
			else
			{
				LIST_FOREACH(var, &cav.station_list, station_link)
				{
					if (LIST_NEXT(var, station_link)->oid == LIST_FIRST(head)->oid && LIST_NEXT(var, station_link)->type == LIST_FIRST(head)->type)
						break;
				}
				flag_second_full[cav.id] = LIST_NEXT(var, station_link);
				flag_first_full[cav.id] = flag_second_full[cav.id];
				return TT3;
			}
		}
		else
		{
			if (TT2 < TT3)
			{
				LIST_FOREACH(var, &cav.station_list, station_link)
				{
					if (LIST_NEXT(var, station_link)->oid == LIST_FIRST(head)->oid && LIST_NEXT(var, station_link)->type == LIST_FIRST(head)->type)
						break;
				}
				flag_first_full[cav.id] = var;
				flag_second_full[cav.id] = LIST_NEXT(var, station_link);
				return TT2;
			}
			else
			{
				LIST_FOREACH(var, &cav.station_list, station_link)
				{
					if (LIST_NEXT(var, station_link)->oid == LIST_FIRST(head)->oid && LIST_NEXT(var, station_link)->type == LIST_FIRST(head)->type)
						break;
				}
				flag_second_full[cav.id] = LIST_NEXT(var, station_link);
				flag_first_full[cav.id] = flag_second_full[cav.id];
				return TT3;
			}
		}
	}
	LIST_FOREACH(var, head, station_link)                      
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

	//�����²�������ĸ�����Ϣ
	LIST_FOREACH(var, &cav.station_list, station_link)
	{
		if (var->oid == choose->oid && var->type == choose->type)
		{
		//	printf("1111111111111111111\n");
			break;
		}
	}
	if (status == AVAILABLE)
		flag_first_available[cav.id] = var;
	if (status == FULL)
		flag_first_full[cav.id] = var;
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
	int ttt = 0;
	DISTANCE((*choose), district[order->did], dist1);
	LIST_FOREACH(var, &cav.station_list, station_link)
	{
		if (var->oid == choose->oid && var->type == choose->type)
		{
		//	printf("222222222222222222222222222\n");
			ttt = 1;
			break;
		}
	}
	if (ttt == 1)
	{
		if (status == AVAILABLE)
			flag_second_available[cav.id] = var;
		if (status == FULL)
			flag_second_full[cav.id] = var;
	}
	else
	{
		if (status == AVAILABLE)
			flag_second_available[cav.id] = flag_first_available[cav.id];
		if (status == FULL)
		{
			flag_second_full[cav.id] = flag_first_full[cav.id];
		}
	}
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

void update_and_insert(Station *station, Order* order, Station_list *head, int station_status, int cav_status, int cavid)
{
	float delaytime;
	float distance;
	float time;
	Station *var;
	station->location = restaurant[order->rid].location;
	station->oid = order->oid;
	if (station_status == RESTAURANT)
	{
		station->type = RESTAURANT;
		if (cav_status == FULL)
		{
			DISTANCE((*flag_first_full[cavid]), restaurant[order->rid], distance);
			TIME(distance, time);
			LIST_INSERT_AFTER(flag_first_full[cavid], station, station_link);
			station->arrivetime = flag_first_full[cavid]->leavetime + time;
		}
		if (cav_status == AVAILABLE)
		{
			DISTANCE((*flag_first_available[cavid]), restaurant[order->rid], distance);
			TIME(distance, time);
			LIST_INSERT_AFTER(flag_first_available[cavid], station, station_link);
			station->arrivetime = flag_first_available[cavid]->leavetime + time;
		}
		if (station->arrivetime < order->time)
		{
			station->leavetime = order->time;
		}
		else
		{
			station->leavetime = station->arrivetime;
		}
	}
	if (station_status == DISTRICT)
	{
		station->type = DISTRICT;
		if (cav_status == FULL)
		{
			DISTANCE((*flag_second_full[cavid]), district[order->did], distance);
			TIME(distance, time);
			LIST_INSERT_AFTER(flag_second_full[cavid], station, station_link);
			station->arrivetime = flag_second_full[cavid]->leavetime + time;
			station->leavetime = station->arrivetime;
		}
		if (cav_status == AVAILABLE)
		{
			DISTANCE((*flag_second_available[cavid]), district[order->did], distance);
			TIME(distance, time);
			LIST_INSERT_AFTER(flag_second_available[cavid], station, station_link);
			station->arrivetime = flag_second_available[cavid]->leavetime + time;
			station->leavetime = station->arrivetime;
		}
	}
	var = LIST_NEXT(station, station_link);
	if (var == NULL)
		return;
	DISTANCE((*station), restaurant[order->rid], distance);
	delaytime = station->leavetime + distance - var->arrivetime;

	LIST_FOREACH_FROM(var, head, station_link)
	{
		var->arrivetime = var->arrivetime + delaytime;
		if (var->leavetime >= var->arrivetime)
			break;
		else
		{
			delaytime = var->arrivetime - var->leavetime;
			var->leavetime = var->arrivetime;
		}
	}
}
