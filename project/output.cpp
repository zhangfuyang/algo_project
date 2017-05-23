#include <iostream>
#include "struct.h"
#include "queue.h"
#include "globalvar.h"
#include "function.h"

using namespace std;

void output(Cavalier cavalier[])
{
	int i,j,num;
	Print *temp;

	for (i = 1; i <= cavalier_num; i++)
	{
		cout << "**********************************************" << endl;
		LIST_SIZE(temp, &cavalier[i].print_list, print_link, num);
		cout << i << " " << num << endl;
		temp = LIST_FIRST(&cavalier[i].print_list);
		while (temp != NULL)
		{
			cout << temp->location.x << " " << temp->location.y << " "
				<< temp->arrivetime << " " << temp->leavetime << temp->pack_num;
			for (j = 1; j <= temp->pack_num; j++)
			{
				cout << temp->packid[j] << " ";
			}
			cout << endl;
			temp = LIST_NEXT(temp, print_link);
		}
	}
}