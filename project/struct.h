#pragma once
#ifndef _STRUCT_H_
#include <math.h>
#include "queue.h"
#define _STRUCT_H_
#define Distance(type1, type2, dist) do {			\
		dist = sqrt((type1.location.x - type2.location.x)*(type1.location.x - type2.location.x) + (type1.location.y - type2.location.y)*(type1.location.y - type2.location.y)); \
	} while(0) 

extern int C;

struct Location {
	int x;
	int y;
};

struct Restaurant {
	Location location;
};

struct District {
	Location location;
};

struct Order {
	int time;
	int rid;
	int did;
};

struct Cavalier {
	Location location;
	int now;			//current time
	int status;			
	Order *order = new Order[C + 1];
	LIST_ENTRY(Cavalier) cav_link;
};

#endif /*_STRUCT_H_*/