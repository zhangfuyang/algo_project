#include <string>
#include "struct.h"
#include "queue.h"
#include "function.h"
#include "globalvar.h"

void alloc(Order *order)
{
	queue_update(order->time, cav_available_list);
	
	queue_update(order->time, cav_full_list);

	Cavalier *cav;
	float free_bottlenecktime, available_bottlenecktime;
	
	free_bottlenecktime = find_free_cavalier(order, cav);

	available_bottlenecktime = find_available_cavalier(order, cav);


}