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
Place *rst_center;
int main()
{
	input_size(restaurant_num, district_num, cavalier_num, C, N, TEST);

	restaurant = new Restaurant[restaurant_num+1];
	district = new District[district_num+1];
	order = new Order[N+1];
	cavalier = new  Cavalier[cavalier_num+1];
	print = new Station_list[N+1];
	rst_center = new Place[cavalier_num + 1];

	input_array(restaurant, district, order, restaurant_num, district_num, cavalier_num, C, N, TEST);
	
	cout << restaurant_num<<" "<<district_num<<" "<<cavalier_num<<" "<<C << " " << N << endl;

	print_init();

	main_cluster();

	cav_init();
	
	//printf("init completed!\n");
	
	for (int i = 1; i <= N; i++)
	{
		//cout << endl << "**********************************************" << endl;
		
		int cavid;
		cav_update(order[i].time);
		/*for (int j = 1; j <= cavalier_num; j++)
		{
			if (cavalier[j].station_list.lh_first->type != DISTRICT && cavalier[j].station_list.lh_first->type != LOCATIONNOW)
			{
				system("pause");
			}
			Station *temp;
			int count = 0;
			temp = LIST_FIRST(&cavalier[j].station_list);
			temp = LIST_NEXT(temp, station_link);
			while (temp != NULL)
			{
				if (temp->type == DISTRICT)
					count++;
				temp = temp->station_link.le_next;
			}
			if (count != cavalier[j].pack_num)
			{
				system("pause");
			}
		}*/

		cavid = alloc(order[i]);

		//printf("cav_alloc! cavid = %d status: %d\n", cavid, cavalier[cavid].status);

		order_insert(cavid, order[i]);

	}

	output();

	system("pause");
}




