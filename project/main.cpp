#include<iostream>
#include"queue.h"
#include"struct.h"
#include"globalvar.h"
#include"function.h"
#define TEST "large.txt"
using namespace std;

int restaurant_num, district_num, cavalier_num;
int C, N;
Restaurant *restaurant;
District *district;
Order *order;
Cavalier *cavalier;
Station_list *print;

int main()
{
	input_size(restaurant_num, district_num, cavalier_num, C, N, TEST);

	restaurant = new Restaurant[restaurant_num+1];
	district = new District[district_num+1];
	order = new Order[N+1];
	cavalier = new  Cavalier[cavalier_num+1];
	print = new Station_list[N+1];

	input_array(restaurant, district, order, restaurant_num, district_num, cavalier_num, C, N, TEST);
	
	cout << restaurant_num<<" "<<district_num<<" "<<cavalier_num<<" "<<C << " " << N << endl;

	print_init();

	cav_init();

	//printf("init completed!\n");

	for (int i = 1; i <= N; i++)
	{
		//cout << endl << "**********************************************" << endl;
		
		int cavid;


		cavid = alloc(order[i]);

		//printf("cav_alloc! cavid = %d status: %d\n", cavid, cavalier[cavid].status);

		order_insert(cavid, order[i]);

	}
	for (int i = 1; i <= cavalier_num; i++)
	{
		station_list_copy(&cavalier[i].station_list, &print[i]);
	}
	output();

	system("pause");
}




