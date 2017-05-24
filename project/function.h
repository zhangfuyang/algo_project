#ifndef _FUNCTION_H_
#include<string>
void filein2(int &restaurant_num, int &district_num, int &cavalier_num, int &C, int &N, const char * fp);
void filein(Restaurant* restaurant, District* district, Order* order, int &restaurant_num, int &district_num, int &cavalier_num, int &C, int &N, const char * fp);
void output();

Location place2xy(Place);
Location  place2xy(Place place);
//District packid2district(Cavalier *cav, int packid);
//Restaurant packid2restaurant(Cavalier *cav, int packid);
District did2district(int did);
Restaurant rid2restaurant(int rid);

float cal_bottlenecktime(Station_list station_list);
void station_list_copy(Station_list *from, Station_list *to);

void queue_init();
void queue_update(int time, Cav_list cav_list);
void find_free_cavalier(Order *order, Cavalier *cav);

void alloc(int oid);
#endif