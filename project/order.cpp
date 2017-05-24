#include <string>
#include"queue.h"
#include"struct.h"
#include"globalvar.h"
#include"function.h"

void order_insert(int cavid, Order order)
{
	switch (cavalier[cavid].status)
	{
	case INIT:
		order_init_insert(cavid, order);
		break;
	case FREE:
		order_free_insert(cavid, order);
		break;
	case AVAILABLE:
		order_available_insert(cavid, order);
		break;
	case FULL:
		order_full_insert(cavid, order);
		break;
	default:
		printf("invalid cavalier! id : %d", i);
		break;
	}
	printf("order %d -> cavalier %d", order.oid, cavid);
}

