#ifndef _STRUCT_H_
#include <math.h>
#include "queue.h"
#define _STRUCT_H_

//计算两点间距离的宏函数
#define DISTANCE(type1, type2, dist) do {			\
		dist = sqrt((type1.location.x - type2.location.x)*(type1.location.x - type2.location.x) + (type1.location.y - type2.location.y)*(type1.location.y - type2.location.y)); \
	} while(0) 

LIST_HEAD(Cav_list, Cavalier);

LIST_HEAD(Print_list, Print);
extern int C;

struct Location {            //坐标结构体
	int x;
	int y;
};

struct Place {          //餐厅或小区位置结构体
	Location location;
};
typedef Place Restaurant;
typedef Place District;

struct Order {               //订单具体信息：下单时间、餐厅id、小区id
	float time;
	int rid;
	int did;
};

struct Pack {                      //一个骑手的订单信息：取得时间、完成时间
	Order *order = NULL;
	float fetchtime;
	float completetime;
};

#define FREE 0
#define AVAILABLE 1
#define FULL 2

struct Print {                   //每个骑手的打印信息
	Location location;
	float arrivetime;
	float leavetime;
	int pack_num;
	int *packid = new int[C + 1];
	LIST_ENTRY(Print) print_link;
};

struct Cavalier {            //骑手具体信息：当前位置的坐标信息、当前的时刻、当前的状态（三个列表中处于哪个列表）、身上的订单信息、链接结构体
	Location location;
	float now;				//骑士当前时间
	float end;				//骑士完成所有任务的时间
	int status;				//FREE or FULL or AVAILABLE
	//对于FREE骑士：now = end
	Print_list print_list;
	LIST_ENTRY(Cavalier) cav_link;
};

#endif /*_STRUCT_H_*/