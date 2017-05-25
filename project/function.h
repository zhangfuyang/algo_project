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
float Insert_order(Order *order, Station_list *head);
void free_list(Station_list *head);

//核心函数
//cav
void cav_init();
void cav_update(int time);
void print_init();
//alloc
int alloc(Order order);
float cal_init_costtime(Cavalier cavalier, Order order);
float cal_available_costtime(Cavalier cavalier, Order order);
float cal_free_costtime(Cavalier cavalier, Order order);
float cal_full_costtime(Cavalier cavalier, Order order);

//order
void order_insert(int cavid, Order order);
void order_init_insert(int cavid, Order order);
void order_free_insert(int cavid, Order order);
void order_available_insert(int cavid, Order order);
void order_full_insert(int cavid, Order order);
#endif