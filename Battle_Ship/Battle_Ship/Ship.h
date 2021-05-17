#ifndef __SHIP_H__
#define __SHIP_H__

#include "Location.h"
#include "Bomb.h"

class Ship : public Location
{
	int hp;
	int straight;
	int turnabout;
	bool attack_bomb;
	DIRECTION dir;
	TEAM team;
	Location** position;
public:
	Ship(TEAM _team, int _t = 0, int _s = 0, int hp = 100);
	int& GetHP();
	int& GetStraight();
	int& GetTurnabout();
	int GetMovePoint() const;
	bool& GetAttackBomb();
	DIRECTION& GetDir();
	TEAM& GetTeam();
	Location**& GetPosition();
};

class Small_Ship : public Ship
{
	Location** stretch_position[2];
	int cross_len;

public:
	Small_Ship(TEAM _team = RED, int _hp = 100);
	int& GetCrossLen();
	Location**& GetPosition_Stretch(int num);
	LAYOUT GetLayout() const;
	void EndOfTurn();
};

class Big_Ship : public Ship
{
	Location** stretch_position[4];
	int cross_len;
	int nine_len;
public:
	Big_Ship(TEAM _team = RED, int _hp = 200);
	int& GetCrossLen();
	int& GetNineLen();
	Location**& GetPosition_Stretch(int num);
	LAYOUT GetLayout() const;
	void EndOfTurn();
};

#endif