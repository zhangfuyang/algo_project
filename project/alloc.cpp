#include <string>
#include"queue.h"
#include"struct.h"
#include"globalvar.h"
#include"function.h"

int alloc(Order order)
{
	int i,cavid = 0;
	float temptime, costtime = -1;

	for (i = 1; i <= cavalier_num; i++)
	{
		switch (cavalier[i].status)
		{
		case INIT:
			temptime = cal_init_costtime(cavalier[i], order);
			break;
		case FREE:
			temptime = cal_free_costtime(cavalier[i], order);
			break;
		case AVAILABLE:
			temptime = cal_available_costtime(cavalier[i], order);
			break;
		case FULL:
			temptime = cal_full_costtime(cavalier[i], order);
			break;
		default:
			printf("invalid cavalier! id : %d",i);
			break;
		}
		if (costtime == -1)
		{
			costtime = temptime;
			cavid = i;
		}
		else
		{
			if (temptime < costtime)
			{
				costtime = temptime;
				cavid = i;
			}
		}
	}
	return cavid;
}