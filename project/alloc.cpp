#include <string>
#include "struct.h"
#include "queue.h"
#include "function.h"
#include "globalvar.h"

void alloc(int oid)
{
	queue_update(order[oid].time, cav_full_list);
	queue_update(order[oid].time, cav_available_list);
}