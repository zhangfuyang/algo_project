#include <iostream>
#include "struct.h"
#include "globalvar.h"

Location  place2xy(Place place)
{
	return place.location;
}

District packid2district(Cavalier *cav, int packid)
{
	return district[cav->pack[packid].order->did];
}

Restaurant packid2restaurant(Cavalier *cav, int packid)
{
	return restaurant[cav->pack[packid].order->rid];
}

District did2district(int did)
{
	return district[did];
}

Restaurant rid2restaurant(int rid)
{
	return restaurant[rid];
}