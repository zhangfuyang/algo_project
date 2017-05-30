#ifndef _FUNCTION_H_
#include<string>
#include <vector>
using namespace std;
//I/O����
void input_size(int &restaurant_num, int &district_num, int &cavalier_num, int &C, int &N, const char * fp);
void input_array(Restaurant* restaurant, District* district, Order* order, int &restaurant_num, int &district_num, int &cavalier_num, int &C, int &N, const char * fp);
void output();

//�������ܺ���
Location place2xy(Place);
Location  place2xy(Place place);
District did2district(int did);
Restaurant rid2restaurant(int rid);
float theoretically_time();
int find_near_center(int cavid);
Location unit_vector(Location a, Location b);

//���⹦�ܺ���
float cal_bottlenecktime(Station_list station_list);
void station_list_copy(Station_list *from, Station_list *to);
void copy_station(Station *listfrom, Station *listto);
float Insert_order(Order *order, Station_list *head, int status, Cavalier cav);
void free_list(Station_list *head);
void update_and_insert(Station *station, Order* order, Station_list *head, int station_status, int cav_status, int cavid);
//���ĺ���
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

//cluster
float getDistXY(Tuple t1, Tuple t2);
int clusterOfTuple(Tuple means[], Tuple tuple);
float getVar(vector<Tuple> clusters[], Tuple means[]);
Tuple getMeans(vector<Tuple> cluster);
void KMeans(vector<Tuple> tuples);
void main_cluster();
#endif