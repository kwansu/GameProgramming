#include "Map.h"

class Stage
{
	Block* block;
public:
	void SetArchipelago()
	{
		block = new Block[51];
		int n = 0;
		block[n++].SetLocation(3, 3);
		block[n++].SetLocation(3, 2);
		block[n++].SetLocation(4, 2);
		block[n++].SetLocation(5, 2);
		block[n++].SetLocation(6, 2);
		block[n++].SetLocation(5, 3);
		block[n++].SetLocation(6, 3);
		block[n++].SetLocation(7, 3);
		block[n++].SetLocation(7, 4);
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
	void SetShip(Ship_List& red, Ship_List& blue)
	{
		red.AddBigShip(RED);
		red.AddSmallShip(RED);
		red.GetBigShip(0).SetLocation(7, 9);
		red.GetSmallShip(0).SetLocation(3, 5);
		red.GetSmallShip(0).GetDir() = RIGHT;

		blue.AddBigShip(BLUE);
		blue.AddSmallShip(BLUE);
		blue.GetBigShip(0).SetLocation(13, 4);
		blue.GetBigShip(0).GetDir() = LEFT;
		blue.GetSmallShip(0).SetLocation(15, 9);
	}
};