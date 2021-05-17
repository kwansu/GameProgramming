#ifndef __SHIP_AI_H__
#define __SHIP_AI_H__

#include "Const.h"
#include "Ship.h"
#include "GetDirection.h"

class Ship_AI;

struct Dumy
{
	int x, y;
	DIRECTION dir;
	bool CheckPoint(int _x, int _y, int(Ship_AI::*GetInt)(int, int), Ship_AI* ptr);
	bool Small_MoveForward(Ship_AI* ptr);
	bool Small_ClockwiseRotate(Ship_AI* ptr);
	bool Small_AntiClockwiseRotate(Ship_AI* ptr);
	bool Big_MoveForward(Ship_AI* ptr);
	bool Big_ClockwiseRotate(Ship_AI* ptr);
	bool Big_AntiClockwiseRotate(Ship_AI* ptr);
};

class Ship_AI
{
	A_Star get_direction;
	Dumy virtual_ship;
	Dumy move_ship;
	int priority_point[MAX_X][MAX_Y];
	int risk_point[MAX_X][MAX_Y];
	int risk_sum;
	int num;
	int* moving_point;
	char** moving_command;
	int len;
public:
	Ship_AI();
	bool CombinationCommand(char* _comand, char* _data, int index, int turn, int type, int rotate_n, int movement, bool moving);
	bool CommandToPriorityPoint(char* data, int movement, bool moving);
	void SetBigShipPathPriority(Big_Ship* _ship, bool moving);
	void SetSmallShipPathPriority(Small_Ship* _ship, bool moving);
	void SetBigShipPriority(Dumy _move_ship);
	void SetSmallShipPriority(Dumy _move_ship);
	void AddRiskPointSum(Dumy _move_ship, LAYOUT type);
	void AddPriority(int _x, int _y);
	void DeductPriority(int _x, int y, PRIORITY_MOVE_POINT distance);
	void ShowPriorityPointMap();
	void SetMapObjectData(Map* _map);
	void SetRiskPoint();
	void SetMovingPoint(Ship* ship);
	void SetBlockAroundPriorityPoint();
	void AddRiskPointAround(int _x, int _y, PRIORITY_MOVE_POINT distance);
	void AddObjectAroundRiskPoint(int _x, int _y);
	void RemoveShipPoint(Ship* ship);
	void DeductBlockAroundPriorityPoint(int _x, int _y);
	int AddMovingPointAround(int _x, int _y, bool _bool);
	int GetPriorityPoint(int _x, int _y) { return priority_point[_x][_y]; }
	int GetNum() const { return num; }
	bool CheckPoint(int _x, int _y);
	char* GetRandomMovingCommand(Ship* ship, Map* _map);
	A_Star& GetDirection()
	{
		return get_direction;
	}
};

#endif