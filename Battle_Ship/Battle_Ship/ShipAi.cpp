#include "ShipAI.h"
#include "Base.h"

bool Dumy::CheckPoint(int _x, int _y, int(Ship_AI::*GetInt)(int, int), Ship_AI* ptr)
{
	if (_x < 0 || _x >= MAX_X || _y < 0 || _y >= MAX_Y)
		return false;

	if ((ptr->*GetInt)(_x, _y) < 0)
		return false;

	return true;
}
bool Dumy::Small_MoveForward(Ship_AI* ptr)
{
	switch (dir)
	{
	case UP:
		if (!CheckPoint(x, y - 2, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		y--;
		break;
	case DOWN:
		if (!CheckPoint(x, y + 2, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		y++;
		break;
	case LEFT:
		if (!CheckPoint(x - 2, y, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		x--;
		break;
	case RIGHT:
		if (!CheckPoint(x + 2, y, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		x++;
		break;
	}
	return true;
}
bool Dumy::Small_ClockwiseRotate(Ship_AI* ptr)
{
	switch (dir)
	{
	case UP:
		if (!CheckPoint(x - 1, y, &Ship_AI::GetPriorityPoint, ptr) || !CheckPoint(x + 1, y, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		dir = RIGHT;
		break;
	case DOWN:
		if (!CheckPoint(x - 1, y, &Ship_AI::GetPriorityPoint, ptr) || !CheckPoint(x + 1, y, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		dir = LEFT;
		break;
	case LEFT:
		if (!CheckPoint(x, y + 1, &Ship_AI::GetPriorityPoint, ptr) || !CheckPoint(x, y - 1, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		dir = UP;
		break;
	case RIGHT:
		if (!CheckPoint(x, y + 1, &Ship_AI::GetPriorityPoint, ptr) || !CheckPoint(x, y - 1, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		dir = DOWN;
		break;
	}
	return true;
}
bool Dumy::Small_AntiClockwiseRotate(Ship_AI* ptr)
{
	switch (dir)
	{
	case UP:
		if (!CheckPoint(x - 1, y, &Ship_AI::GetPriorityPoint, ptr) || !CheckPoint(x + 1, y, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		dir = LEFT;
		break;
	case DOWN:
		if (!CheckPoint(x - 1, y, &Ship_AI::GetPriorityPoint, ptr) || !CheckPoint(x + 1, y, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		dir = RIGHT;
		break;
	case LEFT:
		if (!CheckPoint(x, y + 1, &Ship_AI::GetPriorityPoint, ptr) || !CheckPoint(x, y - 1, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		dir = DOWN;
		break;
	case RIGHT:
		if (!CheckPoint(x, y + 1, &Ship_AI::GetPriorityPoint, ptr) || !CheckPoint(x, y - 1, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		dir = UP;
		break;
	}
	return true;
}
bool Dumy::Big_MoveForward(Ship_AI* ptr)
{
	switch (dir)
	{
	case UP:
		if (!CheckPoint(x, y - 3, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		y--;
		break;
	case DOWN:
		if (!CheckPoint(x, y + 3, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		y++;
		break;
	case LEFT:
		if (!CheckPoint(x - 3, y, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		x--;
		break;
	case RIGHT:
		if (!CheckPoint(x + 3, y, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		x++;
		break;
	}
	return true;
}
bool Dumy::Big_ClockwiseRotate(Ship_AI* ptr)
{
	switch (dir)
	{
	case UP:
		if (!CheckPoint(x - 2, y, &Ship_AI::GetPriorityPoint, ptr) || !CheckPoint(x + 2, y, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		if (!CheckPoint(x - 1, y, &Ship_AI::GetPriorityPoint, ptr) || !CheckPoint(x + 1, y, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		dir = RIGHT;
		break;
	case DOWN:
		if (!CheckPoint(x - 2, y, &Ship_AI::GetPriorityPoint, ptr) || !CheckPoint(x + 2, y, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		if (!CheckPoint(x - 1, y, &Ship_AI::GetPriorityPoint, ptr) || !CheckPoint(x + 1, y, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		dir = LEFT;
		break;
	case LEFT:
		if (!CheckPoint(x, y + 2, &Ship_AI::GetPriorityPoint, ptr) || !CheckPoint(x, y - 2, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		if (!CheckPoint(x, y + 1, &Ship_AI::GetPriorityPoint, ptr) || !CheckPoint(x, y - 1, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		dir = UP;
		break;
	case RIGHT:
		if (!CheckPoint(x, y + 2, &Ship_AI::GetPriorityPoint, ptr) || !CheckPoint(x, y - 2, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		if (!CheckPoint(x, y + 1, &Ship_AI::GetPriorityPoint, ptr) || !CheckPoint(x, y - 1, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		dir = DOWN;
		break;
	}
	return true;
}
bool Dumy::Big_AntiClockwiseRotate(Ship_AI* ptr)
{
	switch (dir)
	{
	case UP:
		if (!CheckPoint(x - 2, y, &Ship_AI::GetPriorityPoint, ptr) || !CheckPoint(x + 2, y, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		if (!CheckPoint(x - 1, y, &Ship_AI::GetPriorityPoint, ptr) || !CheckPoint(x + 1, y, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		dir = LEFT;
		break;
	case DOWN:
		if (!CheckPoint(x - 2, y, &Ship_AI::GetPriorityPoint, ptr) || !CheckPoint(x + 2, y, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		if (!CheckPoint(x - 1, y, &Ship_AI::GetPriorityPoint, ptr) || !CheckPoint(x + 1, y, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		dir = RIGHT;
		break;
	case LEFT:
		if (!CheckPoint(x, y + 2, &Ship_AI::GetPriorityPoint, ptr) || !CheckPoint(x, y - 2, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		if (!CheckPoint(x, y + 1, &Ship_AI::GetPriorityPoint, ptr) || !CheckPoint(x, y - 1, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		dir = DOWN;
		break;
	case RIGHT:
		if (!CheckPoint(x, y + 2, &Ship_AI::GetPriorityPoint, ptr) || !CheckPoint(x, y - 2, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		if (!CheckPoint(x, y + 1, &Ship_AI::GetPriorityPoint, ptr) || !CheckPoint(x, y - 1, &Ship_AI::GetPriorityPoint, ptr))
			return false;
		dir = UP;
		break;
	}
	return true;
}

Ship_AI::Ship_AI()
{
	for (int y = 0; y < MAX_Y; y++)
		for (int x = 0; x < MAX_X; x++)
			priority_point[x][y] = 0;

	for (int y = 0; y < MAX_Y; y++)
		for (int x = 0; x < MAX_X; x++)
			risk_point[x][y] = 0;

	num = 0; risk_sum = 0;
	moving_point = NULL; moving_command = NULL;
	len = 0;
}
bool Ship_AI::CombinationCommand(char* _command, char* _data, int index, int rotate, int type, int rotate_n, int movement, bool moving)
{
	if (type == 1 || type == 2)
		rotate++;

	if (rotate > rotate_n) //걸러내는 부분
		return false;

	_data[index] = _command[type]; //입력 부분

	if (index >= movement - 1) //실행 부분
	{
		CommandToPriorityPoint(_data, movement, moving);
		return true;
	}
	if (type == 3)
	{
		CommandToPriorityPoint(_data, movement, moving);
		return true;
	}

	if (index - rotate > 1) //예외처리 부분
	{
		CombinationCommand(_command, _data, index + 1, rotate, 1, rotate_n, movement, moving);
		CombinationCommand(_command, _data, index + 1, rotate, 2, rotate_n, movement, moving);
		CombinationCommand(_command, _data, index + 1, rotate, 3, rotate_n, movement, moving);
		return false;
	}

	CombinationCommand(_command, _data, index + 1, rotate, 0, rotate_n, movement, moving);
	CombinationCommand(_command, _data, index + 1, rotate, 1, rotate_n, movement, moving);
	CombinationCommand(_command, _data, index + 1, rotate, 2, rotate_n, movement, moving);
	CombinationCommand(_command, _data, index + 1, rotate, 3, rotate_n, movement, moving);
	return false;
}
void Ship_AI::SetBigShipPathPriority(Big_Ship* _ship, bool moving)
{
	RemoveShipPoint(_ship);
	char command[4] = { 'g', 't', 'r', 'e' };
	char data[4];
	virtual_ship.dir = _ship->GetDir();
	virtual_ship.x = _ship->GetX(); virtual_ship.y = _ship->GetY();
	num = 0;

	CombinationCommand(command, data, 0, 0, 0, 1, 4, moving);
	CombinationCommand(command, data, 0, 0, 1, 1, 4, moving);
	CombinationCommand(command, data, 0, 0, 2, 1, 4, moving);
	CombinationCommand(command, data, 0, 0, 3, 1, 4, moving);
}
void Ship_AI::SetSmallShipPathPriority(Small_Ship* _ship, bool moving)
{
	RemoveShipPoint(_ship);
	char command[4] = { 'g', 't', 'r', 'e' };
	char data[5];
	virtual_ship.dir = _ship->GetDir();
	virtual_ship.x = _ship->GetX(); virtual_ship.y = _ship->GetY();
	num = 0;

	CombinationCommand(command, data, 0, 0, 0, 2, 5, moving);
	CombinationCommand(command, data, 0, 0, 1, 2, 5, moving);
	CombinationCommand(command, data, 0, 0, 2, 2, 5, moving);
	CombinationCommand(command, data, 0, 0, 3, 2, 5, moving);
}
bool Ship_AI::CommandToPriorityPoint(char* data, int movement, bool moving)
{
	move_ship = virtual_ship;

	if (movement == 4)
	{
		for (int i = 0; i < movement; i++)
		{
			switch (data[i])
			{
			case 'g':
				if (!move_ship.Big_MoveForward(this))
					return false;
				break;
			case 't':
				if (!move_ship.Big_ClockwiseRotate(this))
					return false;
				break;
			case 'r':
				if (!move_ship.Big_AntiClockwiseRotate(this))
					return false;
				break;
			}
		}
		if (move_ship.dir == UP || move_ship.dir == DOWN)
		{
			risk_sum += risk_point[move_ship.x][move_ship.y];
			risk_sum += risk_point[move_ship.x][move_ship.y + 1];
			risk_sum += risk_point[move_ship.x][move_ship.y - 1];
			risk_sum += risk_point[move_ship.x][move_ship.y + 2];
			risk_sum += risk_point[move_ship.x][move_ship.y - 2];
		}
		else
		{
			risk_sum += risk_point[move_ship.x][move_ship.y];
			risk_sum += risk_point[move_ship.x + 1][move_ship.y];
			risk_sum += risk_point[move_ship.x - 1][move_ship.y];
			risk_sum += risk_point[move_ship.x + 2][move_ship.y];
			risk_sum += risk_point[move_ship.x - 2][move_ship.y];
		}
		SetBigShipPriority(move_ship);
	}
	else
	{
		for (int i = 0; i < movement; i++)
		{
			switch (data[i])
			{
			case 'g':
				if (!move_ship.Small_MoveForward(this))
					return false;
				break;
			case 't':
				if (!move_ship.Small_ClockwiseRotate(this))
					return false;
				break;
			case 'r':
				if (!move_ship.Small_AntiClockwiseRotate(this))
					return false;
				break;
			}
		}
		if (move_ship.dir == UP || move_ship.dir == DOWN)
		{
			risk_sum += risk_point[move_ship.x][move_ship.y];
			risk_sum += risk_point[move_ship.x][move_ship.y + 1];
			risk_sum += risk_point[move_ship.x][move_ship.y - 1];
		}
		else
		{
			risk_sum += risk_point[move_ship.x][move_ship.y];
			risk_sum += risk_point[move_ship.x + 1][move_ship.y];
			risk_sum += risk_point[move_ship.x - 1][move_ship.y];
		}
		SetSmallShipPriority(move_ship);
	}
	if (moving)
	{
		if (moving_command == NULL)
		{
			len = 1;
			moving_command = new char*[len];
			moving_command[0] = new char[5];
			for (int i = 0; i < 5; i++)
				moving_command[0][i] = data[i];
		}
		else
		{
			char** tem = new char*[len];
			for (int n = 0; n < len; n++)
				tem[n] = moving_command[n];

			delete[] moving_command;
			len++;
			moving_command = new char*[len];
			for (int n = 0; n < len - 1; n++)
				moving_command[n] = tem[n];

			moving_command[len - 1] = new char[5];
			for (int i = 0; i < 5; i++)
				moving_command[len - 1][i] = data[i];
			delete[] tem;
		}
	}
	num++;
	return true;
}
void Ship_AI::SetBigShipPriority(Dumy _move_ship)
{
	int x = _move_ship.x; int y = _move_ship.y;

	AddPriority(x, y);
	if (_move_ship.dir == UP || _move_ship.dir == DOWN)
	{
		AddPriority(x, y + 1);
		AddPriority(x, y - 1);
		AddPriority(x, y + 2);
		AddPriority(x, y - 2);
	}
	else
	{
		AddPriority(x - 1, y);
		AddPriority(x + 1, y);
		AddPriority(x - 2, y);
		AddPriority(x + 2, y);
	}
}
void Ship_AI::SetSmallShipPriority(Dumy _move_ship)
{
	int x = _move_ship.x; int y = _move_ship.y;

	AddPriority(x, y);
	if (_move_ship.dir == UP || _move_ship.dir == DOWN)
	{
		AddPriority(x, y + 1);
		AddPriority(x, y - 1);
	}
	else
	{
		AddPriority(x - 1, y);
		AddPriority(x + 1, y);
	}
}
void Ship_AI::AddRiskPointSum(Dumy _move_ship, LAYOUT type)
{
	int x = _move_ship.x; int y = _move_ship.y;

	if (type == BIG_SHIP)
	{
		risk_sum += risk_point[x][y];
		if (_move_ship.dir == UP || _move_ship.dir == DOWN)
		{
			risk_sum += risk_point[x][y + 1];
			risk_sum += risk_point[x][y - 1];
			risk_sum += risk_point[x][y + 2];
			risk_sum += risk_point[x][y - 2];
		}
		else
		{
			risk_sum += risk_point[x + 1][y];
			risk_sum += risk_point[x - 1][y];
			risk_sum += risk_point[x + 2][y];
			risk_sum += risk_point[x - 2][y];
		}
	}
	else if (type == SMALL_SHIP)
	{
		risk_sum += risk_point[x][y];
		if (_move_ship.dir == UP || _move_ship.dir == DOWN)
		{
			risk_sum += risk_point[x][y + 1];
			risk_sum += risk_point[x][y - 1];
		}
		else
		{
			risk_sum += risk_point[x + 1][y];
			risk_sum += risk_point[x - 1][y];
		}
	}
}
void Ship_AI::AddPriority(int _x, int _y)
{
	if (priority_point[_x][_y] < LOW)
		priority_point[_x][_y] += BASE;
	else if (priority_point[_x][_y] < USUALLY)
		priority_point[_x][_y] += NESTING;
	else if (priority_point[_x][_y] < HIGH)
		priority_point[_x][_y] += HIGH_NESTING;
	else
		priority_point[_x][_y] += MULTY_NESTING;
}
void Ship_AI::DeductPriority(int _x, int _y, PRIORITY_MOVE_POINT distance)
{
	if (!CheckPoint(_x, _y))
		return;

	if (priority_point[_x][_y] <= 0)
		return;

	if (priority_point[_x][_y] - distance < 0)
		priority_point[_x][_y] = 0;

	priority_point[_x][_y] -= distance;
}
void Ship_AI::ShowPriorityPointMap()
{
	for (int y = 0; y < MAX_Y; y++)
	{
		for (int x = 0; x < MAX_X; x++)
		{
			if (priority_point[x][y] < 10 && priority_point[x][y] >= 0)
				cout << " " << priority_point[x][y];
			else
				cout << priority_point[x][y];
		}
		cout << endl;
	}
}
void Ship_AI::SetMapObjectData(Map* _map)
{
	for (int y = 0; y < MAX_Y; y++)
	{
		for (int x = 0; x < MAX_X; x++)
		{
			switch (_map->GetLayout(x, y))
			{
			case EMPTY:
				priority_point[x][y] = 0;
				break;
			case BLOCK:
				priority_point[x][y] = -1;
				break;
			case SMALL_SHIP:
				priority_point[x][y] = -2;
				break;
			case BIG_SHIP:
				priority_point[x][y] = -3;
				break;
			default:
				priority_point[x][y] = -100;
				break;
			}
		}
	}
}
void Ship_AI::SetRiskPoint()
{
	for (int y = 0; y < MAX_Y; y++)
	{
		for (int x = 0; x < MAX_X; x++)
		{
			if (priority_point[x][y] < 0)
				AddObjectAroundRiskPoint(x, y);
			else
				risk_point[x][y] = 0;
		}
	}
	for (int y = -1; y <= MAX_Y; y++)
	{
		AddObjectAroundRiskPoint(-1, y);
		AddObjectAroundRiskPoint(MAX_X, y);
		if (y == -1 || y == MAX_Y)
			for (int x = 0; x < MAX_X; x++)
				AddObjectAroundRiskPoint(x, y);
	}
}
void Ship_AI::SetMovingPoint(Ship* ship)
{
	RemoveShipPoint(ship);
	char command[4] = { 'g', 't', 'r', 'e' };
	int size;
	int turn;
	if (ship->GetLayout() == BIG_SHIP)
		size = 4, turn = 1;
	else
		size = 5, turn = 2;

	char data[5];
	for (int n = 0; n < len; n++)
	{
		if (moving_point != NULL)
			delete[] moving_point;

		moving_point = new int[len];
		virtual_ship.dir = ship->GetDir();
		virtual_ship.x = ship->GetX(); virtual_ship.y = ship->GetY();
		for (int i = 0; i < size; i++)
		{
			switch (moving_command[n][i])
			{
			case 'g':
				virtual_ship.Small_MoveForward(this);
				break;
			case 't':
				virtual_ship.Small_ClockwiseRotate(this);
				break;
			case 'r':
				virtual_ship.Small_AntiClockwiseRotate(this);
				break;
			default:
				break;
			}
		}
		num = 0;
		risk_sum = 0;

		CombinationCommand(command, data, 0, 0, 0, turn, size, false);
		CombinationCommand(command, data, 0, 0, 1, turn, size, false);
		CombinationCommand(command, data, 0, 0, 2, turn, size, false);
		CombinationCommand(command, data, 0, 0, 3, turn, size, false);
		if (risk_sum == 0)
			moving_point[n] = 100;
		else
			moving_point[n] = 100 * num / (risk_sum * priority_point[virtual_ship.x][virtual_ship.y]);
	}
}
void Ship_AI::AddRiskPointAround(int _x, int _y, PRIORITY_MOVE_POINT distance)
{
	if (CheckPoint(_x, _y))
	{
		if (priority_point[_x][_y] > 0)
			risk_point[_x][_y] += BETWEEN;

		if (priority_point[_x][_y] >= 0)
			risk_point[_x][_y] += distance;
	}
}
void Ship_AI::AddObjectAroundRiskPoint(int _x, int _y)
{
	AddRiskPointAround(_x, _y + 1, AROUND);
	AddRiskPointAround(_x, _y + 2, VICINITY);
	AddRiskPointAround(_x, _y + 3, FAL);
	AddRiskPointAround(_x, _y - 1, AROUND);
	AddRiskPointAround(_x, _y - 2, VICINITY);
	AddRiskPointAround(_x, _y - 3, FAL);
	AddRiskPointAround(_x + 1, _y, AROUND);
	AddRiskPointAround(_x + 1, _y + 1, VICINITY);
	AddRiskPointAround(_x + 1, _y + 2, FAL);
	AddRiskPointAround(_x + 1, _y - 1, VICINITY);
	AddRiskPointAround(_x + 1, _y - 2, FAL);
	AddRiskPointAround(_x + 2, _y, VICINITY);
	AddRiskPointAround(_x + 2, _y + 1, FAL);
	AddRiskPointAround(_x + 2, _y - 1, FAL);
	AddRiskPointAround(_x + 3, _y, FAL);
	AddRiskPointAround(_x - 1, _y, AROUND);
	AddRiskPointAround(_x - 1, _y + 1, VICINITY);
	AddRiskPointAround(_x - 1, _y + 2, FAL);
	AddRiskPointAround(_x - 1, _y - 1, VICINITY);
	AddRiskPointAround(_x - 1, _y - 2, FAL);
	AddRiskPointAround(_x - 2, _y, VICINITY);
	AddRiskPointAround(_x - 2, _y + 1, FAL);
	AddRiskPointAround(_x - 2, _y - 1, FAL);
	AddRiskPointAround(_x - 3, _y, FAL);
}
void Ship_AI::RemoveShipPoint(Ship* ship)
{
	int x = ship->GetX();
	int y = ship->GetY();
	priority_point[x][y] = 0;
	if (ship->GetLayout() == BIG_SHIP)
	{
		if (ship->GetDir() == UP || ship->GetDir() == DOWN)
		{
			priority_point[x][y + 1] = 0;
			priority_point[x][y - 1] = 0;
			priority_point[x][y + 2] = 0;
			priority_point[x][y - 2] = 0;
		}
		else
		{
			priority_point[x + 1][y] = 0;
			priority_point[x - 1][y] = 0;
			priority_point[x + 2][y] = 0;
			priority_point[x - 2][y] = 0;
		}
	}
	else
	{
		if (ship->GetDir() == UP || ship->GetDir() == DOWN)
		{
			priority_point[x][y + 1] = 0;
			priority_point[x][y - 1] = 0;
		}
		else
		{
			priority_point[x + 1][y] = 0;
			priority_point[x - 1][y] = 0;
		}
	}
}
void Ship_AI::DeductBlockAroundPriorityPoint(int _x, int _y)
{
	DeductPriority(_x, _y + 1, VICINITY);
	DeductPriority(_x, _y + 2, FAL);
	DeductPriority(_x, _y - 1, VICINITY);
	DeductPriority(_x, _y - 2, FAL);
	DeductPriority(_x + 1, _y, VICINITY);
	DeductPriority(_x + 1, _y + 1, FAL);
	DeductPriority(_x + 1, _y - 1, FAL);
	DeductPriority(_x + 2, _y, FAL);
	DeductPriority(_x - 1, _y, VICINITY);
	DeductPriority(_x - 1, _y + 1, FAL);
	DeductPriority(_x - 1, _y - 1, FAL);
	DeductPriority(_x - 2, _y, FAL);
}
int Ship_AI::AddMovingPointAround(int _x, int _y, bool _bool)
{
	int num = 0;
	int moving_point = 0;
	if (CheckPoint(_x, _y))
	{
		num++;
		if (priority_point[_x][_y] < 0)
		{
			moving_point += 40;
		}
		else
			moving_point += priority_point[_x][_y];
	}
	if (_bool == true)
	{
		if (AddMovingPointAround(_x, _y + 1, false) > 0)
		{
			num++;
			moving_point += AddMovingPointAround(_x, _y + 1, false);
		}

		if (AddMovingPointAround(_x, _y + 2, false) > 0)
		{
			num++;
			moving_point += AddMovingPointAround(_x, _y + 2, false);
		}

		if (AddMovingPointAround(_x, _y + 3, false) > 0)
		{
			num++;
			moving_point += AddMovingPointAround(_x, _y + 3, false);
		}

		if (AddMovingPointAround(_x, _y - 1, false) > 0)
		{
			num++;
			moving_point += AddMovingPointAround(_x, _y - 1, false);
		}

		if (AddMovingPointAround(_x, _y - 2, false) > 0)
		{
			num++;
			moving_point += AddMovingPointAround(_x, _y - 2, false);
		}

		if (AddMovingPointAround(_x, _y - 3, false) > 0)
		{
			num++;
			moving_point += AddMovingPointAround(_x, _y - 3, false);
		}

		if (AddMovingPointAround(_x + 1, _y, false) > 0)
		{
			num++;
			moving_point += AddMovingPointAround(_x + 1, _y, false);
		}

		if (AddMovingPointAround(_x + 1, _y + 1, false) > 0)
		{
			num++;
			moving_point += AddMovingPointAround(_x + 1, _y + 1, false);
		}
		if (AddMovingPointAround(_x + 1, _y + 2, false) > 0)
		{
			num++;
			moving_point += AddMovingPointAround(_x + 1, _y + 2, false);
		}
		if (AddMovingPointAround(_x + 1, _y - 1, false) > 0)
		{
			num++;
			moving_point += AddMovingPointAround(_x + 1, _y - 1, false);
		}
		if (AddMovingPointAround(_x + 1, _y - 2, false) > 0)
		{
			num++;
			moving_point += AddMovingPointAround(_x + 1, _y - 2, false);
		}
		if (AddMovingPointAround(_x + 2, _y, false) > 0)
		{
			num++;
			moving_point += AddMovingPointAround(_x + 2, _y, false);
		}
		if (AddMovingPointAround(_x + 2, _y + 1, false) > 0)
		{
			num++;
			moving_point += AddMovingPointAround(_x + 2, _y + 1, false);
		}
		if (AddMovingPointAround(_x + 2, _y - 1, false) > 0)
		{
			num++;
			moving_point += AddMovingPointAround(_x + 2, _y - 1, false);
		}
		if (AddMovingPointAround(_x + 3, _y, false) > 0)
		{
			num++;
			moving_point += AddMovingPointAround(_x + 3, _y, false);
		}
		if (AddMovingPointAround(_x - 1, _y, false) > 0)
		{
			num++;
			moving_point += AddMovingPointAround(_x - 1, _y, false);
		}
		if (AddMovingPointAround(_x - 1, _y + 1, false) > 0)
		{
			num++;
			moving_point += AddMovingPointAround(_x - 1, _y + 1, false);
		}
		if (AddMovingPointAround(_x - 1, _y + 2, false) > 0)
		{
			num++;
			moving_point += AddMovingPointAround(_x - 1, _y + 2, false);
		}
		if (AddMovingPointAround(_x - 1, _y - 1, false) > 0)
		{
			num++;
			moving_point += AddMovingPointAround(_x - 1, _y - 1, false);
		}
		if (AddMovingPointAround(_x - 1, _y - 2, false) > 0)
		{
			num++;
			moving_point += AddMovingPointAround(_x - 1, _y - 2, false);
		}
		if (AddMovingPointAround(_x - 2, _y, false) > 0)
		{
			num++;
			moving_point += AddMovingPointAround(_x - 2, _y, false);
		}
		if (AddMovingPointAround(_x - 2, _y + 1, false) > 0)
		{
			num++;
			moving_point += AddMovingPointAround(_x - 2, _y + 1, false);
		}
		if (AddMovingPointAround(_x - 2, _y - 1, false) > 0)
		{
			num++;
			moving_point += AddMovingPointAround(_x - 2, _y - 1, false);
		}
		if (AddMovingPointAround(_x - 3, _y, false) > 0)
		{
			num++;
			moving_point += AddMovingPointAround(_x - 3, _y, false);
		}
	}
	if (num != 0)
		moving_point = moving_point / num;
	return moving_point;
}
bool Ship_AI::CheckPoint(int _x, int _y)
{
	if (_x < 0 || _x >= MAX_X || _y < 0 || _y >= MAX_Y)
		return false;

	return true;
}
char* Ship_AI::GetRandomMovingCommand(Ship* ship, Map* _map)
{
	if (moving_command != NULL)
	{
		delete[] moving_command;
		moving_command = NULL;
		len = 0;
	}
	SetMapObjectData(_map);
	if (ship->GetLayout() == BIG_SHIP)
		SetBigShipPathPriority(static_cast<Big_Ship*>(ship), true);
	else
		SetSmallShipPathPriority(static_cast<Small_Ship*>(ship), true);

	SetRiskPoint();
	SetMovingPoint(ship);
	int sum = 0;
	for (int n = 0; n < len; n++)
		sum += moving_point[n];

	srand(time(NULL));
	int r = rand() % sum;

	int n = 0;
	for (n = 0; n < len; n++)
	{
		if (r <= 0)
			break;

		r -= moving_point[n];
	}
	return moving_command[n];
}