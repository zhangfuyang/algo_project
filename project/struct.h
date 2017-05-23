#pragma once
#ifndef _STRUCT_H_
#include <math.h>
#include "queue.h"
#define _STRUCT_H_
#define Distance(type1, type2, dist) do {			\
		dist = sqrt((type1.location.x - type2.location.x)*(type1.location.x - type2.location.x) + (type1.location.y - type2.location.y)*(type1.location.y - type2.location.y)); \
	} while(0) 

//计算两点间距离的宏函数

extern int C;

struct Location {            //坐标结构体
	int x;
	int y;
};

struct Restaurant {          //餐厅位置结构体
	Location location;
};

struct District {            //小区位置结构体
	Location location;
};

struct Order {               //订单具体信息：下单时间、餐厅id、小区id
	int time;
	int rid;
	int did;
};

struct Cavalier {            //骑手具体信息：当前位置的坐标信息、当前的时刻、当前的状态（三个列表中处于哪个列表）、身上的订单信息、链接结构体
	Location location;
	int now;			//current time
	int status;			//free or full or not full
	Order *order = new Order[C + 1];
	LIST_ENTRY(Cavalier) cav_link;
};

#endif /*_STRUCT_H_*/