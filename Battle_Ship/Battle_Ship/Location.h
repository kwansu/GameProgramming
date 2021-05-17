#ifndef __LOCATION_H__
#define __LOCATION_H__

#include "Const.h"

class Location
{
	int x, y;
public:
	Location(int _x = 0, int _y = 0) : x(_x), y(_y) {}
	bool SetLocation(int _x, int _y)
	{
		if (!CheckValue(_x, _y))
			return false;

		x = _x; y = _y;
		return true;
	}
	bool CheckValue(int _x, int _y)
	{
		if (_x < 0 || _x >= MAX_X || _y < 0 || _y >= MAX_Y)
			return false;
		return true;
	}
	int& GetX() { return x; }
	int& GetY() { return y; }
	virtual DIRECTION& GetDir() = 0;
	virtual LAYOUT GetLayout() const { return EMPTY; }
};

class Block : public Location
{
	DIRECTION dir;
public:
	Block(int _x = 0, int _y = 0) : Location(_x, _y) {}
	LAYOUT GetLayout() const { return BLOCK; }
	DIRECTION& GetDir() { return dir; }
};

#endif