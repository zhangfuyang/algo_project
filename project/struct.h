#pragma once
#ifndef _STRUCT_H_
#include <math.h>
#include "queue.h"
#define _STRUCT_H_
#define Distance(type1, type2, dist) do {			\
		dist = sqrt((type1.location.x - type2.location.x)*(type1.location.x - type2.location.x) + (type1.location.y - type2.location.y)*(type1.location.y - type2.location.y)); \
	} while(0) 

//������������ĺ꺯��

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

struct Cavalier {            //���־�����Ϣ����ǰλ�õ�������Ϣ����ǰ��ʱ�̡���ǰ��״̬�������б��д����ĸ��б������ϵĶ�����Ϣ�����ӽṹ��
	Location location;
	int now;			//current time
	int status;			//free or full or not full
	Order *order = new Order[C + 1];
	LIST_ENTRY(Cavalier) cav_link;
};

#endif /*_STRUCT_H_*/