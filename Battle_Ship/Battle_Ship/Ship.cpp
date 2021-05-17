#include "Ship.h"
#include "Base.h"

Ship::Ship(TEAM _team, int _t, int _s, int _hp) : position(NULL), dir(UP), team(_team), hp(_hp), straight(_s), turnabout(_t), attack_bomb(true) {}
int& Ship::GetHP()
{
	return hp;
}
int& Ship::GetStraight()
{
	return straight;
}
int& Ship::GetTurnabout()
{
	return turnabout;
}
int Ship::GetMovePoint()const
{
	return turnabout + straight;
}
bool& Ship::GetAttackBomb()
{
	return attack_bomb;
}
DIRECTION& Ship::GetDir()
{
	return dir;
}
TEAM& Ship::GetTeam()
{
	return team;
}
Location**& Ship::GetPosition()
{
	return position;
}

Small_Ship::Small_Ship(TEAM _team, int _hp) : Ship(_team, 2, 3, _hp)
{
	cross_len = 5;
}
int& Small_Ship::GetCrossLen()
{
	return cross_len;
}
Location**& Small_Ship::GetPosition_Stretch(int num)
{
	if (num > 1 || num < 0)
	{
		cout << "error~GetPosition_Stretch[0]." << endl;
		return stretch_position[0];
	}
	return stretch_position[num];
}
LAYOUT Small_Ship::GetLayout() const
{
	return SMALL_SHIP;
}
void Small_Ship::EndOfTurn()
{
	GetStraight() = 3; GetTurnabout() = 2;
	GetAttackBomb() = true;
}

Big_Ship::Big_Ship(TEAM _team, int _hp) : Ship(_team, 1, 3, _hp)
{
	cross_len = 4;
	nine_len = 5;
}
int& Big_Ship::GetCrossLen()
{
	return cross_len;
}
int& Big_Ship::GetNineLen()
{
	return nine_len;
}
Location**& Big_Ship::GetPosition_Stretch(int num)
{
	if (num > 3 || num < 0)
	{
		cout << "error~GetPosition_Stretch[0]." << endl;
		return stretch_position[0];
	}
	return stretch_position[num];
}
LAYOUT Big_Ship::GetLayout() const
{
	return BIG_SHIP;
}
void Big_Ship::EndOfTurn()
{
	GetStraight() = 3; GetTurnabout() = 1;
	GetAttackBomb() = true;
}