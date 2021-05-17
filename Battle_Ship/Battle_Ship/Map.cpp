#include "Map.h"
#include "Ship.h"
#include "Base.h"

Map::Map() : turn(0)
{
	for (int y = 0; y < MAX_Y; y++)
		for (int x = 0; x < MAX_X; x++)
			point[x][y] = NULL;
}
LAYOUT Map::GetLayout(int _x, int _y) const
{
	if (!point[0][0]->CheckValue(_x, _y))
	{
		cout << "error~GetLayout : point[" << _x << "][" << _y << "]? -> EMPTY!" << endl;
		return EMPTY;
	}
	if (point[_x][_y] == NULL)
		return EMPTY;

	return point[_x][_y]->GetLayout();
}
void Map::ShowMap()
{

	cout << endl;
	for (int y = 0; y < MAX_Y; y++)
	{
		for (int x = 0; x < MAX_X; x++)
		{
			switch (GetLayout(x, y))
			{
			case EMPTY:
				if (bombs.CheckBombPoint(x, y))
					cout << "○";
				else
					cout << "□";
				break;
			case BLOCK:
				cout << "■";
				break;
			case SMALL_SHIP:
				if (static_cast<Ship*>(point[x][y])->GetTeam() == RED)
				{
					switch (static_cast<Ship*>(point[x][y])->GetDir())
					{
					case UP:
						cout << "▲";
						break;
					case DOWN:
						cout << "▼";
						break;
					case LEFT:
						cout << "◀";
						break;
					case RIGHT:
						cout << "▶";
						break;
					default:
						cout << " ?";
						break;
					}
				}
				else
				{
					switch (static_cast<Ship*>(point[x][y])->GetDir())
					{
					case UP:
						cout << "△";
						break;
					case DOWN:
						cout << "▽";
						break;
					case LEFT:
						cout << "◁";
						break;
					case RIGHT:
						cout << "▷";
						break;
					default:
						cout << " ?";
						break;
					}
				}
				break;
			case BIG_SHIP:
				if (static_cast<Ship*>(point[x][y])->GetTeam() == RED)
				{
					switch (static_cast<Ship*>(point[x][y])->GetDir())
					{
					case UP:
						cout << "▲";
						break;
					case DOWN:
						cout << "▼";
						break;
					case LEFT:
						cout << "◀";
						break;
					case RIGHT:
						cout << "▶";
						break;
					default:
						cout << " ?";
						break;
					}
				}
				else
				{
					switch (static_cast<Ship*>(point[x][y])->GetDir())
					{
					case UP:
						cout << "△";
						break;
					case DOWN:
						cout << "▽";
						break;
					case LEFT:
						cout << "◁";
						break;
					case RIGHT:
						cout << "▷";
						break;
					default:
						cout << " ?";
						break;
					}
				}
				break;
			default:
				cout << " ?";
				break;
			}
		}
		if (y < 10)
			cout << " " << y << " ";
		else
			cout << y << " ";

		if (y == 1)
			cout << "  TURN:" << turn;
		if (red_ships.GetBigLen() > 0)
		{
			if (y == 3)
				cout << "  Big_Ship(1)";
			if (y == 4)
				cout << "  HP : " << red_ships.GetBigShip(0).GetHP();
			if (y == 5)
				cout << "  전진(" << red_ships.GetBigShip(0).GetStraight() << ") , 회전(" << red_ships.GetBigShip(0).GetTurnabout() << ")";
			if (y == 6)
				cout << "  소역(" << red_ships.GetBigShip(0).GetCrossLen() << ") , 광역(" << red_ships.GetBigShip(0).GetNineLen() << ")";
		}

		if (red_ships.GetSmallLen() > 0)
		{
			if (y == 8)
				cout << "  Small_Ship(1)";
			if (y == 9)
				cout << "  HP : " << red_ships.GetSmallShip(0).GetHP();
			if (y == 10)
				cout << "  전진(" << red_ships.GetSmallShip(0).GetStraight() << ") , 회전(" << red_ships.GetSmallShip(0).GetTurnabout() << ")";
			if (y == 11)
				cout << "  소역(" << red_ships.GetSmallShip(0).GetCrossLen() << ")";
		}

		cout << endl;
	}
	for (int x = 0; x < MAX_X; x++)
	{
		if (x < 10)
			cout << " " << x;
		else
			cout << x;
	}
}
int& Map::GetTurn()
{
	return turn;
}
Location*& Map::GetPoint(int _x, int _y)
{
	if (!point[0][0]->CheckValue(_x, _y))
	{
		cout << "error~GetPoint : point[" << _x << "][" << _y << "]? -> point[0][0]!" << endl;
		return point[0][0];
	}
	return point[_x][_y];
}
Bombs& Map::GetBombs()
{
	return bombs;
}