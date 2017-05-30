#include <iostream>
#include "struct.h"
#include "globalvar.h"

//获取餐厅或小区的位置
Location  place2xy(Place place)                
{
	return place.location;
}

//由小区id获取小区的结构体
District did2district(int did)                  
{
	return district[did];
}

//由餐厅id获取餐厅的结构体
Restaurant rid2restaurant(int rid)              
{
	return restaurant[rid];
}

//将以from开头的Station链表复制给以to开头的Station链表
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

//计算一个stationlist中的瓶颈值
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


//free掉复制好的链表以释放空间
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

//将listfrom这个Station结构体中的信息全部复制给listo这个Station结构体
void copy_station(Station *listfrom, Station *listto) {          
	listto->arrivetime = listfrom->arrivetime;
	listto->leavetime = listfrom->leavetime;
	listto->location = listfrom->location;
	listto->oid = listfrom->oid;
	listto->station_link.le_next = listfrom->station_link.le_next;
	listto->station_link.le_prev = listfrom->station_link.le_prev;
	listto->type = listfrom->type;
}

//尝试将某个订单插入骑士的Station列表返回插入后的最大时间
float Insert_order(Order *order, Station_list *head, int status, Cavalier cav) {      
	Station *var = NULL;
	Station *choose = NULL;
	Station *newstation = NULL;
	Station *last = NULL;
	Station *last1 = NULL;
	Station *oldlast = new Station[1];
	Station *newlast = new Station[1];
	Station *newnewstation = new Station[1];

	//订单的餐厅坐标

	int x1 = restaurant[order->rid].location.x;                     
	int y1 = restaurant[order->rid].location.y;

	//订单的小区坐标

	int x2 = district[order->did].location.x;		    
	int y2 = district[order->did].location.y;
	float distance;
	float dist1;
	float dist2;

	//取最短距离变量

	float mindis = 10000;

	//插入后修改后面的station所用的延迟时间

	float delaytime;

	//返回的插入后的瓶颈时间

//	float T;                           
	float T1;

	//用于比较如果小区插在倒数第二个位置，是插在倒数第二个位置好，还是插在尾部好

	float T2;                          

	//取得餐厅插入位置
	var = LIST_FIRST(head);
	while (LIST_NEXT(var, station_link) != NULL && var->location.x == LIST_NEXT(var, station_link)->location.x && 
			var->location.y == LIST_NEXT(var, station_link)->location.y)
		//order[var->oid].oid != order[LIST_NEXT(var, station_link)->oid].oid)
	{
		var = LIST_NEXT(var, station_link);
	}
	if (LIST_NEXT(var, station_link) == NULL) //只有一个元素
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
		if (time + ttemp->leavetime > order->time) //订单等我
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

	//更新新插入餐厅的各项信息

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

	//插入

	LIST_INSERT_AFTER(choose, newstation, station_link);       

	var = LIST_NEXT(newstation, station_link);

	DISTANCE((*var), restaurant[order->rid], dist2);

	//延迟时间

	delaytime = newstation->leavetime + dist2 - var->arrivetime;      


	LIST_FOREACH_FROM(var, head, station_link)
	{
		var->arrivetime = var->arrivetime + delaytime;
		if (var->leavetime >= var->arrivetime) {
			break;
		}
		else {
			delaytime = var->arrivetime - var->leavetime;      //更新delaytime
			var->leavetime = var->arrivetime;
		}
	}

	//为插入小区做准备

	var = newstation;           
	mindis = 10000;

	//从已经插入的餐厅之后再遍历

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
		
	//更新新插入小区的各项信息

	newstation->arrivetime = choose->leavetime + dist1;     

	newstation->leavetime = newstation->arrivetime;

	newstation->location.x = x2;
	newstation->location.y = y2;
	newstation->oid = order->oid;
	newstation->type = DISTRICT;

	//插入小区

	LIST_INSERT_AFTER(choose, newstation, station_link);     

	copy_station(newstation, newnewstation);

	var = LIST_NEXT(newstation, station_link);

	DISTANCE((*var), district[order->did], dist2);

	delaytime = newstation->leavetime + dist2 - var->arrivetime;

	LIST_LAST(last, head, station_link);

	copy_station(last, oldlast);

	//更新插入小区之后的各项信息

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

	//如果新插小区插在链表倒数第二个位置，则以下部分用于比较是插在倒数第二个位置好还是插在链表尾部好

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

//计算给定数据集中理论上的最短的“最长等待时间”
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
