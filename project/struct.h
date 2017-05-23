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

struct Place {          //������С��λ�ýṹ��
	Location location;
};
typedef Place Restaurant;
typedef Place District;

struct Order {               //����������Ϣ���µ�ʱ�䡢����id��С��id
	int time;
	int rid;
	int did;
};

struct Pack {                      //һ�����ֵĶ�����Ϣ��ȡ��ʱ�䡢���ʱ��
	Order *order = NULL;
	int fetchtime;
	int completetime;
};

#define FREE 0
#define AVAILABLE 1
#define FULL 3

struct Print {                   //ÿ�����ֵĴ�ӡ��Ϣ
	Location location;
	float arrivetime;
	float leavetime;
	int pack_num;
	int *packid = new int[C + 1];
	Print *link;
};





struct Cavalier {            //���־�����Ϣ����ǰλ�õ�������Ϣ����ǰ��ʱ�̡���ǰ��״̬�������б��д����ĸ��б������ϵĶ�����Ϣ�����ӽṹ��
	Location location;
	float now;				//current time
	float end;				//finish time
	int status;				//free or full or available
	int pack_num;
	Pack *pack = new Pack[C + 1];
	Print *print = NULL;



	LIST_ENTRY(Cavalier) cav_link;
};

#endif /*_STRUCT_H_*/