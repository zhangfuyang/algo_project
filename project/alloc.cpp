#include <string>
#include"queue.h"
#include"struct.h"
#include"globalvar.h"
#include"function.h"


int alloc(Order order)
{
	int i,cavid = 0;
	float temptime, time = 1000000;

	for (i = 1; i <= cavalier_num; i++)
	{
		temptime = Insert_order2(&order, &cavalier[i].station_list, cavalier[i]);
		if (temptime < time)
		{
			time = temptime;
			cavid = i;
		}
	}
	return cavid;
}



