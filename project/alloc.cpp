#include <string>
#include "struct.h"
#include "queue.h"
#include "function.h"
#include "globalvar.h"

float pack_insert(Cavalier *cav, Order *order)
{
	int status = cav->status;
	if (status == FULL)
	{
		printf("pack_insert failed: cavalier is FULL!");
		exit(0);
	}
	else if (status == FREE)
	{
		cav->status = AVAILABLE;
		cav->pack_num ++;

	}
}


void insertstation(Order *order, Cavalier *cav)


