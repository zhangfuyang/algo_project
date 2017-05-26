#ifndef _FUNCTION_H_
#include<string>
//I/O函数
void input_size(int &restaurant_num, int &district_num, int &cavalier_num, int &C, int &N, const char * fp);
void input_array(Restaurant* restaurant, District* district, Order* order, int &restaurant_num, int &district_num, int &cavalier_num, int &C, int &N, const char * fp);
void output();

//基本功能函数
Location place2xy(Place);
Location  place2xy(Place place);
District did2district(int did);
Restaurant rid2restaurant(int rid);
float theoretically_time();

//特殊功能函数
float cal_bottlenecktime(Station_list station_list);
void station_list_copy(Station_list *from, Station_list *to);
void copy_station(Station *listfrom, Station *listto);
float Insert_order(Order *order, Station_list *head, int status, Cavalier cav);
void free_list(Station_list *head);
void update_and_insert(Station *station, Order* order, Station_list *head, int station_status, int cav_status, int cavid);
//核心函数
//cav
void cav_init();
void cav_update(float time);
void print_init();
void cav_setstatus(Cavalier *cav);

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