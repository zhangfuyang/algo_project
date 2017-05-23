#pragma once
#ifndef _STRUCT_H_
#include <math.h>
#include "queue.h"
#define _STRUCT_H_

//������������ĺ꺯��
#define DISTANCE(type1, type2, dist) do {			\
		dist = sqrt((type1.location.x - type2.location.x)*(type1.location.x - type2.location.x) + (type1.location.y - type2.location.y)*(type1.location.y - type2.location.y)); \
	} while(0) 

extern int C;

struct Location {            //����ṹ��
	int x;
	int y;
};

struct Restaurant {          //����λ�ýṹ��
	Location location;
};

struct District {            //С��λ�ýṹ��
	Location location;
};

struct Order {               //����������Ϣ���µ�ʱ�䡢����id��С��id
	int time;
	int rid;
	int did;
};

struct Pack {
	Order *order = NULL;
	int fetchtime;
	int completetime;
};

#define FREE 0
#define AVAILABLE 1
#define FULL 3

struct Cavalier {            //���־�����Ϣ����ǰλ�õ�������Ϣ����ǰ��ʱ�̡���ǰ��״̬�������б��д����ĸ��б������ϵĶ�����Ϣ�����ӽṹ��
	Location location;
	int now;				//current time
	int end;				//finish time
	int status;				//free or full or available
	int pack_num;
	Pack *pack = new Pack[C + 1];

	LIST_ENTRY(Cavalier) cav_link;
};

#endif /*_STRUCT_H_*/