#pragma once
#include "Tile.h"
#include "Estate.h"
#include "Vehicle.h"


class Coordination
{
public:
	Coordination();
	Coordination(Tile* tiles);
	~Coordination();
	Tile* getTile() { return tile; }
	Estate* getEstate() { return estate; }
	void setPeople(bool con) { isPeople=con ; }
	bool getIsPeople() { return isPeople; }
	void setEstate(Estate* Estate) { estate = Estate; }
	Vehicle* getVehicle() { return vehicle; }
	void setVehicle(Vehicle* Vehicle) { vehicle = Vehicle; }


private:
	Tile* tile;
	bool isPeople;
	Estate* estate=nullptr;
	Vehicle* vehicle=nullptr;
};
