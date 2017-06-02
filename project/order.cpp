#include <string>
#include"queue.h"
#include"struct.h"
#include"globalvar.h"
#include"function.h"

void order_insert(int cavid, Order order)
{
	really_insert(&cavalier[cavid].station_list, &order, cavalier[cavid]);
	//printf("order %d -> cavalier %d", order.oid, cavid);
}

