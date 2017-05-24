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

void station_list_copy(Station_list *from, Station_list *to)//将以head开头的链表复制给以head1开头的链表
{     
	Station *var1, *var2=NULL, *last=NULL;
	LIST_FOREACH(var1, from, station_link)
	{
		var2->arrivetime = var1->arrivetime;
		var2->leavetime = var1->leavetime;
		var2->location = var1->location;
		var2->oid = var1->oid;
		var2->station_link = var1->station_link;
		var2->type = var1->type;
		LIST_INSERT_TAIL(to, var2, last, station_link);

	}
}

float cal_bottlenecktime(Station_list station_list)	//计算一个stationlist中的瓶颈值
{
	float bottlenecktime = 0, temp = 0;
	Station *station;
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