#ifndef _STRUCT_H_
#include <math.h>
#include "queue.h"
#define _STRUCT_H_
#define TEST "data01.txt"
//骑手状态
#define INIT 0
#define FREE 1
#define AVAILABLE 2
#define FULL 3
//位置属性
#define RESTAURANT 0
#define DISTRICT 1
#define LOCATIONNOW 2
//速度
#define SPEED 1

//计算两点间距离
#define DISTANCE(type1, type2, dist) do {			\
		dist = sqrt((type1.location.x - type2.location.x)*(type1.location.x - type2.location.x) \
	+ (type1.location.y - type2.location.y)*(type1.location.y - type2.location.y)); \
	} while(0)

//计算距离到时间
#define TIME(dist, time) do{		\
		time = dist/SPEED;			\
}while(0)

//计算最大值
#define MAX(a, b, max) do {		\
		max=(a>b)?a:b;			\
}while(0)

//计算最小值
#define MIN(a, b, min) do {		\
		min=(a<b)?a:b;			\
}while(0)


struct Location {            //坐标结构体
	float x;
	float y;
};

struct Place {				//餐厅或小区位置结构体
	Location location;
};

typedef Place Restaurant;
typedef Place District;

struct Order {               //订单具体信息：下单时间、餐厅id、小区id、订单花费时间、订单id
	int oid;
	float time;
	int rid;
	int did;
};

//存放元组的属性信息
struct Tuple {
	float attr1;
	float attr2;
};

struct Station {                   //每个骑手路径的关键点信息
	Location location;
	int type;					// District or Restaurant
	int oid;					//Order id
	float arrivetime;
	float leavetime;
	LIST_ENTRY(Station) station_link;
};

LIST_HEAD(Station_list,Station);

struct Cavalier {            //骑手具体信息：当前位置的坐标信息、当前的时刻、当前的状态（三个列表中处于哪个列表）、身上的订单信息、链接结构体
	Location location;
	float now;				//骑士当前时间
	int id;					//骑手id
	int status;				//FREE or FULL or AVAILABLE
	int pack_num;
	float bottlenecktime;	//骑手当前订单中最大等待时间
	Station_list station_list;

};

#endif/*_STRUCT_H_*/