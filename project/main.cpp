#include<iostream>
#include"queue.h"
#include"struct.h"
#include"globalvar.h"
#include"function.h"
#define TEST "data08.txt"
using namespace std;

int restaurant_num, district_num, cavalier_num;
int C, N;
Restaurant *restaurant;
District *district;
Order *order;
Cavalier *cavalier;
Station_list *print;
Station *flag_first_available;
Station *flag_second_available;
Station *flag_first_full;
Station *flag_second_full;
int main()
{
	input_size(restaurant_num, district_num, cavalier_num, C, N, TEST);

	restaurant = new Restaurant[restaurant_num+1];
	district = new District[district_num+1];
	order = new Order[N+1];
	cavalier = new  Cavalier[cavalier_num+1];
	print = new Station_list[N+1];
	
	flag_first_full = new Station[cavalier_num + 1];
	flag_second_full = new Station[cavalier_num+ 1];
	flag_first_available = new Station[cavalier_num + 1];
	flag_second_available = new Station[cavalier_num + 1];

	for (int i = 0; i < cavalier_num + 1; i++)
	{
		flag_first_full[i].arrivetime = -1;
		flag_first_full[i].leavetime = -1;
		flag_first_full[i].location.x = -1;
		flag_first_full[i].location.y = -1;
		flag_first_full[i].oid = -1;
		flag_first_full[i].type = -1;

		flag_second_full[i].arrivetime = -1;
		flag_second_full[i].leavetime = -1;
		flag_second_full[i].location.x = -1;
		flag_second_full[i].location.y = -1;
		flag_second_full[i].oid = -1;
		flag_second_full[i].type = -1;

		flag_first_available[i].arrivetime = -1;
		flag_first_available[i].leavetime = -1;
		flag_first_available[i].location.x = -1;
		flag_first_available[i].location.y = -1;
		flag_first_available[i].oid = -1;
		flag_first_available[i].type = -1;

		flag_second_available[i].arrivetime = -1;
		flag_second_available[i].leavetime = -1;
		flag_second_available[i].location.x = -1;
		flag_second_available[i].location.y = -1;
		flag_second_available[i].oid = -1;
		flag_second_available[i].type = -1;
	}

	/*for (int i = 0; i <= cavalier_num; i++)
	{
		flag_first_full[i] = new Station[1];
		flag_second_full[i] = new Station[1];
		flag_first_available[i] = new Station[1];
		flag_second_available[i] = new Station[1];
	}*/
	input_array(restaurant, district, order, restaurant_num, district_num, cavalier_num, C, N, TEST);
	
	cout << restaurant_num<<" "<<district_num<<" "<<cavalier_num<<" "<<C << " " << N << endl;

	print_init();

	cav_init();

	//printf("init completed!\n");

	for (int i = 1; i <= N; i++)
	{
		//cout << endl << "**********************************************" << endl;
		
		int cavid;

		cav_update(order[i].time);

		cavid = alloc(order[i]);

		//printf("cav_alloc! cavid = %d status: %d\n", cavid, cavalier[cavid].status);

		order_insert(cavid, order[i]);

	}

	output();

	system("pause");
}




