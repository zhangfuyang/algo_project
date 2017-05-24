#ifndef _FUNCTION_H_
#include<string>
void filein2(int &restaurant_num, int &district_num, int &cavalier_num, int &C, int &N, const char * fp);
void filein(Restaurant* restaurant, District* district, Order* order, int &restaurant_num, int &district_num, int &cavalier_num, int &C, int &N, const char * fp);
Location place2xy(Place);
Location  place2xy(Place place);
//District packid2district(Cavalier *cav, int packid);
//Restaurant packid2restaurant(Cavalier *cav, int packid);
District did2district(int did);
Restaurant rid2restaurant(int rid);

void List_copy_station(Station_list *head, Station_list *head1)
void output();
#endif