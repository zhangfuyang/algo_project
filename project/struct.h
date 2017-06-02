#ifndef _STRUCT_H_
#include <math.h>
#include "queue.h"
#define _STRUCT_H_
#define TEST "data01.txt"
//����״̬
#define INIT 0
#define FREE 1
#define AVAILABLE 2
#define FULL 3
//λ������
#define RESTAURANT 0
#define DISTRICT 1
#define LOCATIONNOW 2
//�ٶ�
#define SPEED 1

//������������
#define DISTANCE(type1, type2, dist) do {			\
		dist = sqrt((type1.location.x - type2.location.x)*(type1.location.x - type2.location.x) \
	+ (type1.location.y - type2.location.y)*(type1.location.y - type2.location.y)); \
	} while(0)

//������뵽ʱ��
#define TIME(dist, time) do{		\
		time = dist/SPEED;			\
}while(0)

//�������ֵ
#define MAX(a, b, max) do {		\
		max=(a>b)?a:b;			\
}while(0)

//������Сֵ
#define MIN(a, b, min) do {		\
		min=(a<b)?a:b;			\
}while(0)


struct Location {            //����ṹ��
	float x;
	float y;
};

struct Place {				//������С��λ�ýṹ��
	Location location;
};

typedef Place Restaurant;
typedef Place District;

struct Order {               //����������Ϣ���µ�ʱ�䡢����id��С��id����������ʱ�䡢����id
	int oid;
	float time;
	int rid;
	int did;
};

//���Ԫ���������Ϣ
struct Tuple {
	float attr1;
	float attr2;
};

struct Station {                   //ÿ������·���Ĺؼ�����Ϣ
	Location location;
	int type;					// District or Restaurant
	int oid;					//Order id
	float arrivetime;
	float leavetime;
	LIST_ENTRY(Station) station_link;
};

LIST_HEAD(Station_list,Station);

struct Cavalier {            //���־�����Ϣ����ǰλ�õ�������Ϣ����ǰ��ʱ�̡���ǰ��״̬�������б��д����ĸ��б������ϵĶ�����Ϣ�����ӽṹ��
	Location location;
	float now;				//��ʿ��ǰʱ��
	int id;					//����id
	int status;				//FREE or FULL or AVAILABLE
	int pack_num;
	float bottlenecktime;	//���ֵ�ǰ���������ȴ�ʱ��
	Station_list station_list;

};

#endif/*_STRUCT_H_*/