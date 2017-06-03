#include <iostream>
#include <fstream>
#include <string>
#include "struct.h"
using namespace std;
void input_size(int &restaurant_num, int &district_num, int &cavalier_num, int &c, int &N, const char * file)
{
	ifstream fp(file);
	if (fp.fail())
	{
		cout << "ÊäÈëÎÄ¼þ´íÎó£¡\n";
		system("pause");
		exit(0);
	}
	string str;
	getline(fp, str);
	int i = 0;
	//cout << str.length();
	restaurant_num = 0;
	district_num = 0;
	cavalier_num = 0;
	c = 0;
	N = 0;
	while (i < str.length() && str[i] != ' ')
	{
		restaurant_num = restaurant_num * 10 + str[i] - '0';
		i++;
	}
	i++;
	while (i < str.length() && str[i] != ' ')
	{
		district_num = district_num * 10 + str[i] - '0';
		i++;
	}
	i++;
	while (i < str.length() && str[i] != ' ')
	{
		cavalier_num = cavalier_num * 10 + str[i] - '0';
		i++;
	}
	i++;
	while (i < str.length() && str[i] != ' ')
	{
		c = c * 10 + str[i] - '0';
		i++;
	}
	i++;
	while (i < str.length() && str[i] != ' ')
	{
		N = N * 10 + str[i] - '0';
		i++;
	}
	fp.close();
}
void input_array(Restaurant* restaurant, District* district, Order* order, int &restaurant_num, int &district_num, int &cavalier_num, int &c, int &N, const char * file)
{
	ifstream fp(file);
	string str;
	//cout << restaurant_num << endl << district_num << endl << cavalier_num << endl << c << endl << N;
	int i = 1;
	int j = 0;
	getline(fp, str);
	while (i <= restaurant_num && getline(fp, str))
	{
		restaurant[i].location.x = 0;
		restaurant[i].location.y = 0;
		j = 0;
		while (j < str.length() && str[j] != ' ')
		{
			restaurant[i].location.x = restaurant[i].location.x * 10 + str[j] - '0';
			j++;
		}
		j++;
		while (j < str.length() && str[j] != ' ')
		{
			restaurant[i].location.y = restaurant[i].location.y * 10 + str[j] - '0';
			j++;
		}
		i++;
	}
	i = 1;
	j = 0;
	while (i <= district_num && getline(fp, str))
	{
		district[i].location.x = 0;
		district[i].location.y = 0;
		j = 0;
		while (j < str.length() && str[j] != ' ')
		{
			district[i].location.x = district[i].location.x * 10 + str[j] - '0';
			j++;
		}
		j++;
		while (j < str.length() && str[j] != ' ')
		{
			district[i].location.y = district[i].location.y * 10 + str[j] - '0';
			j++;
		}
		i++;
	}
	i = 1;
	j = 0;
	while (i <= N && getline(fp, str))
	{
		j = 0;
		order[i].time = 0;
		order[i].rid = 0;
		order[i].did = 0;
		order[i].oid = i;
		while (j < str.length() && str[j] != ' ')
		{
			order[i].time = order[i].time * 10 + str[j] - '0';
			j++;
		}
		j++;
		while (j < str.length() && str[j] != ' ')
		{
			order[i].rid = order[i].rid * 10 + str[j] - '0';
			j++;
		}
		j++;
		while (j < str.length() && str[j] != ' ')
		{
			order[i].did = order[i].did * 10 + str[j] - '0';
			j++;
		}
		i++;
	}
	fp.close();
}