#include <string>
#include "struct.h"
#include "queue.h"
#include "function.h"
#include "globalvar.h"

void alloc(Order *order)
{
	Cavalier *cav, *free_cav, *available_cav, *full_cav;
	float free_costtime, available_costtime, full_costtime;
	
	free_costtime = find_free_cavalier(order, free_cav);

	available_costtime = find_available_cavalier(order, available_cav);

	full_costtime = find_full_cavalier(order, full_cav);

	if (free_costtime > 0 & available_costtime > 0 & full_costtime > 0)
	{
	
	}
}



float cav_bottletime(Cavalier cav, Order order) {     //返回将order给该骑士后的瓶颈时间
	float T;
	Station_list *head_copy = NULL;

	station_list_copy(&(cav.station_list), head_copy);
	T = Insert_order(&order, head_copy);
	free_list(head_copy);
	
	return T;
}

