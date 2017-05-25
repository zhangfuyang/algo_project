#include<iostream>
#include"queue.h"
#include"struct.h"
#include"globalvar.h"
#include"function.h"
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
	input_size(restaurant_num, district_num, cavalier_num, C, N, "small.txt");

	restaurant = new Restaurant[restaurant_num+1];
	district = new District[district_num+1];
	order = new Order[N+1];
	cavalier = new  Cavalier[cavalier_num+1];
	print = new Station_list[N+1];

	input_array(restaurant, district, order, restaurant_num, district_num, cavalier_num, C, N, "small.txt");
	
	cout << restaurant_num<<" "<<district_num<<" "<<cavalier_num<<" "<<C << " " << N << endl;
	//
	//for (int i = 1; i <= restaurant_num; i++)
	//{
	//	cout << restaurant[i].location.x << " " << restaurant[i].location.y << endl;
	//}
	//for (int i = 1; i <= district_num; i++)
	//{
	//	cout << district[i].location.x << " " << district[i].location.y << endl;
	//}
	//for (int i = 1; i <= N; i++)
	//{
	//	cout << order[i].time << " " << order[i].rid << " " << order[i].did << endl;
	//}
	print_init();
	cav_init();

	for (int i = 1; i <= N; i++)
	{
		int cavid;
		/*for (j = 1; i <= cavalier_num; i++)
		{
			cout << i << endl;
			if (cavalier[i].status == AVAILABLE)
				cout << "AVAILABE" << "  ";
			if (cavalier[i].status == FULL)
				cout << "FULL" << "  ";
			if (cavalier[i].status == FREE)
				cout << "FREE" << "  ";
			if (cavalier[i].status == INIT)
				cout << "INIT" << "  ";
		}*/
		cav_update(order[i].time);
		
		cavid = alloc(order[i]);

		order_insert(cavid, order[i]);
	}

	//cout << place2xy(restaurant[2]).x << " " << place2xy(restaurant[2]).y << endl;
	
	output();

	system("pause");
}




