#ifndef _GLOBALVAR_H_
#include "struct.h"
extern Restaurant *restaurant;
extern District *district;
extern Order *order;
extern Cavalier *cavalier;
extern Station_list *print;
extern int restaurant_num, district_num, cavalier_num;
extern int C, N;
extern Station **flag_first_available;
extern Station **flag_second_available;
extern Station **flag_first_full;
extern Station **flag_second_full;
//extern Cav_list cav_free_list;
//extern Cav_list cav_available_list;
//extern Cav_list cav_full_list;
#endif