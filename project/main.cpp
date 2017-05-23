#include<iostream>
#include"struct.h"
#include"function.h"
#include"queue.h"
using namespace std;

int main()
{
	Restaurant *restaurant;
	District *district;
	Order *order;

	int restaurant_num, district_num, cavalier_num;
	int C, N;

	filein2(restaurant_num, district_num, cavalier_num, C, N, "large.txt");
	restaurant = new Restaurant[restaurant_num+1];
	district = new District[district_num+1];
	order = new Order[N+1];
	filein(restaurant, district, order, restaurant_num, district_num, cavalier_num, C, N, "large.txt");
	cout << restaurant_num<<" "<<district_num<<" "<<cavalier_num<<" "<<C << " " << N << endl;
	for (int i = 1; i <= restaurant_num; i++)
	{
		cout << restaurant[i].x << " " << restaurant[i].y << endl;
	}
	for (int i = 1; i <= district_num; i++)
	{
		cout << district[i].x << " " << district[i].y << endl;
	}
	for (int i = 1; i <= N; i++)
	{
		cout << order[i].time << " " << order[i].rid << " " << order[i].did << endl;
	}

	system("pause");
}