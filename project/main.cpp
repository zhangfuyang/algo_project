#include<iostream>
#include"struct.h"
#include"function.h"
#include"globalvar.h"
#include"queue.h"
using namespace std;

int main()
{
	filein2(restaurant_num, district_num, cavalier_num, C, N, "sample.txt");

	restaurant = new Restaurant[restaurant_num+1];
	district = new District[district_num+1];
	order = new Order[N+1];

	filein(restaurant, district, order, restaurant_num, district_num, cavalier_num, C, N, "sample.txt");
	
	cout << restaurant_num<<" "<<district_num<<" "<<cavalier_num<<" "<<C << " " << N << endl;
	
	for (int i = 1; i <= restaurant_num; i++)
	{
		cout << restaurant[i].location.x << " " << restaurant[i].location.y << endl;
	}
	for (int i = 1; i <= district_num; i++)
	{
		cout << district[i].location.x << " " << district[i].location.y << endl;
	}
	for (int i = 1; i <= N; i++)
	{
		cout << order[i].time << " " << order[i].rid << " " << order[i].did << endl;
	}
	//cout << place2xy(restaurant[2]).x << " " << place2xy(restaurant[2]).y << endl;
	system("pause");
}