#ifndef _FUNCTION_H_
#include<string>
//I/O函数
void input_size(int &restaurant_num, int &district_num, int &cavalier_num, int &C, int &N, const char * fp);
void input_array(Restaurant* restaurant, District* district, Order* order, int &restaurant_num, int &district_num, int &cavalier_num, int &C, int &N, const char * fp);
void output();
//基本功能函数
Location place2xy(Place);
Location  place2xy(Place place);
//District packid2district(Cavalier *cav, int packid);
//Restaurant packid2restaurant(Cavalier *cav, int packid);
District did2district(int did);
Restaurant rid2restaurant(int rid);
//特殊功能函数
float cal_bottlenecktime(Station_list station_list);
void station_list_copy(Station_list *from, Station_list *to);
//核心函数
void queue_init();
void queue_update(int time, Cav_list cav_list);
float find_free_cavalier(Order *order, Cavalier *cav);
float find_available_cavalier(Order *order, Cavalier *cav);
float find_full_cavalier(Order *order, Cavalier *cav);
void alloc(Order *order);
float find_free_costtime(Cavalier cav, Order order);
float find_init_costtime(Cavalier cav, Order order);
float find_full_costtime(Cavalier cav, Order order);
#endif