#include <iostream>
#include "struct.h"
#include "globalvar.h"

Location  place2xy(Place place)
{
	return place.location;
}
//
//District packid2district(Cavalier *cav, int packid)
//{
//	return district[cav->pack[packid].order->did];
//}
//
//Restaurant packid2restaurant(Cavalier *cav, int packid)
//{
//	return restaurant[cav->pack[packid].order->rid];
//}

District did2district(int did)
{
	return district[did];
}

Restaurant rid2restaurant(int rid)
{
	return restaurant[rid];
}

void List_copy_station(Station_list *head, Station_list *head1) {     //将以head开头的链表复制给以head1开头的链表

	Station *var1;
	Station *var2;
	Station *var3;
	LIST_FOREACH(var1, head, station_link)
	{
		var2->arrivetime = var1->arrivetime;
		var2->leavetime = var1->leavetime;
		var2->location = var1->location;
		var2->oid = var1->oid;
		var2->station_link = var1->station_link;
		var2->type = var1->type;
		LIST_INSERT_TAIL(head1, var2, var3, station_link);

	}



}