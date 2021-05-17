#ifndef __MAP_H__
#define __MAP_H__

#include "Location.h"
#include "Bomb.h"
#include "ShipList.h"

class Map
{
	Bombs bombs;
	Location* point[MAX_X][MAX_Y];
	int turn;
public:
	Ship_List red_ships;
	Ship_List blue_ships;
	Map();
	LAYOUT GetLayout(int _x, int _y) const;
	void ShowMap();
	void Initialization()
	{
		for (int y = 0; y < MAX_Y; y++)
			for (int x = 0; x < MAX_X; x++)
				point[x][y] = NULL;
	}
	int& GetTurn();
	Location*& GetPoint(int _x, int _y);
	Bombs& GetBombs();
};

class Stage
{
	Block* block;
	int len;
	int now_stage; // 1.±ºµµ  2.¸Á¸Á´ëÇØ
public:
	void SetArchipelago()
	{
		now_stage = 1;
		len = 52;
		block = new Block[len];
		int n = 0;
		block[n++].SetLocation(2, 3);
		block[n++].SetLocation(2, 2);
		block[n++].SetLocation(3, 2);
		block[n++].SetLocation(4, 2);
		block[n++].SetLocation(5, 2);
		block[n++].SetLocation(4, 3);
		block[n++].SetLocation(5, 3);
		block[n++].SetLocation(6, 3);
		block[n++].SetLocation(6, 4);
		block[n++].SetLocation(3, 7);
		block[n++].SetLocation(3, 12);
		block[n++].SetLocation(3, 11);
		block[n++].SetLocation(3, 10);
		block[n++].SetLocation(4, 9);
		block[n++].SetLocation(4, 10);
		block[n++].SetLocation(4, 11);
		block[n++].SetLocation(5, 9);
		block[n++].SetLocation(5, 10);
		block[n++].SetLocation(6, 9);
		block[n++].SetLocation(6, 10);
		block[n++].SetLocation(10, 0);
		block[n++].SetLocation(10, 1);
		block[n++].SetLocation(11, 1);
		block[n++].SetLocation(12, 1);
		block[n++].SetLocation(12, 2);
		block[n++].SetLocation(12, 7);
		block[n++].SetLocation(13, 7);
		block[n++].SetLocation(13, 6);
		block[n++].SetLocation(14, 7);
		block[n++].SetLocation(14, 6);
		block[n++].SetLocation(14, 5);
		block[n++].SetLocation(11, 13);
		block[n++].SetLocation(11, 12);
		block[n++].SetLocation(12, 13);
		block[n++].SetLocation(12, 12);
		block[n++].SetLocation(13, 13);
		block[n++].SetLocation(13, 12);
		block[n++].SetLocation(17, 2);
		block[n++].SetLocation(18, 1);
		block[n++].SetLocation(18, 0);
		block[n++].SetLocation(18, 2);
		block[n++].SetLocation(19, 2);
		block[n++].SetLocation(19, 1);
		block[n++].SetLocation(19, 0);
		block[n++].SetLocation(19, 6);
		block[n++].SetLocation(19, 7);
		block[n++].SetLocation(19, 8);
		block[n++].SetLocation(19, 9);
		block[n++].SetLocation(19, 10);
		block[n++].SetLocation(18, 10);
		block[n++].SetLocation(18, 9);
		block[n++].SetLocation(17, 10);
	}
	void SetShip(Ship_List& red, Ship_List& blue, bool(MapHandler::*move)(int, int, Ship*), MapHandler* handler)
	{
		red.AddBigShip(RED);
		red.AddSmallShip(RED);
		red.GetSmallShip(0).GetDir() = RIGHT;
		(handler->*move)(7, 9, &red.GetBigShip(0));
		(handler->*move)(4, 5, &red.GetSmallShip(0));

		blue.AddBigShip(BLUE);
		blue.AddSmallShip(BLUE);
		blue.GetBigShip(0).GetDir() = LEFT;
		(handler->*move)(13, 4, &blue.GetBigShip(0));
		(handler->*move)(15, 9, &blue.GetSmallShip(0));
	}
	Block* GetBlock(int index)
	{
		return &block[index];
	}
	int GetNowStage() const
	{
		return now_stage;
	}
};

#endif