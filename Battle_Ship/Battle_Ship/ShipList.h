#ifndef __SHIP_LIST_H__
#define __SHIP_LIST_H__

#include "Ship.h"
#include "Base.h"

class Ship_List
{
	Small_Ship* small_ships;
	Big_Ship* big_ships;
	int small_len;
	int big_len;
public:
	Ship_List() : small_ships(NULL), big_ships(NULL), small_len(0), big_len(0) {}
	Big_Ship& AddBigShip(TEAM _team, int _hp = 200);
	Small_Ship& AddSmallShip(TEAM _team, int _hp = 100);
	Small_Ship& GetSmallShip(int index);
	Big_Ship& GetBigShip(int index);
	int GetSmallLen();
	int GetBigLen();
	bool RemoveShip(Ship* _ship);
	~Ship_List();
};

#endif