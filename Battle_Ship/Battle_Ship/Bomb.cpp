/*#include "Bomb.h"
#include "Base.h"

Bomb::Bomb(int _x, int _y, int _turn, int _power, int _delay)
	: x(_x), y(_y), power(_power), delay(_delay)
{
	end_turn = _turn + delay;
}
int Bomb::GetPower() const
{
	return power;
}
int Bomb::GetEndTurn() const { return end_turn; }
int Bomb::GetX() const { return x; }
int Bomb::GetY() const { return y; }
void Bomb::ExplosionRange(Bombs* _bombs, void(Bombs::*Range)(int, int))
{
	(_bombs->*Range)(x, y);
}
void Bomb::Explosion(MapHandler* _map, void(MapHandler::*explo)(int, int, int))
{
	cout << "here!!" << endl;
	(_map->*explo)(x, y, power);
	cout << "here!!!" << endl;
}

Nine_Bomb::Nine_Bomb(int _x, int _y, int _turn, int _power, int _delay)
	:Bomb(_x, _y, _turn, _power, _delay) {}
void Nine_Bomb::ExplosionRange(Bombs* _bombs, void(Bombs::*Range)(int, int))
{
	int x = GetX(); int y = GetY();
	(_bombs->*Range)(x, y);
	(_bombs->*Range)(x, y + 1);
	(_bombs->*Range)(x, y - 1);
	(_bombs->*Range)(x + 1, y);
	(_bombs->*Range)(x + 1, y + 1);
	(_bombs->*Range)(x + 1, y - 1);
	(_bombs->*Range)(x - 1, y);
	(_bombs->*Range)(x - 1, y + 1);
	(_bombs->*Range)(x - 1, y - 1);
}
void Nine_Bomb::Explosion(MapHandler* _map, void(MapHandler::*explo)(int, int, int))
{
	cout << "here~" << endl;
	int x = GetX(); int y = GetY();
	(_map->*explo)(x, y, GetPower());
	(_map->*explo)(x, y + 1, GetPower());
	(_map->*explo)(x, y - 1, GetPower());
	(_map->*explo)(x + 1, y, GetPower());
	(_map->*explo)(x + 1, y + 1, GetPower());
	(_map->*explo)(x + 1, y - 1, GetPower());
	(_map->*explo)(x - 1, y, GetPower());
	(_map->*explo)(x - 1, y + 1, GetPower());
	(_map->*explo)(x - 1, y - 1, GetPower());
}

Cross_Bomb::Cross_Bomb(int _x, int _y, int _turn, int _power, int _delay)
	: Bomb(_x, _y, _turn, _power, _delay) {}
void Cross_Bomb::ExplosionRange(Bombs* _bombs, void(Bombs::*Range)(int, int))
{
	int x = GetX(); int y = GetY();
	(_bombs->*Range)(x, y);
	(_bombs->*Range)(x, y + 1);
	(_bombs->*Range)(x, y - 1);
	(_bombs->*Range)(x + 1, y);
	(_bombs->*Range)(x - 1, y);
}
void Cross_Bomb::Explosion(MapHandler* _map, void(MapHandler::*explo)(int, int, int))
{
	int x = GetX(); int y = GetY();
	(_map->*explo)(x, y, GetPower());
	(_map->*explo)(x, y + 1, GetPower());
	(_map->*explo)(x, y - 1, GetPower());
	(_map->*explo)(x + 1, y, GetPower());
	(_map->*explo)(x - 1, y, GetPower());
}

Bombs::Bombs() : bombs(NULL), len(0)
{
	for (int x = 0; x < MAX_X; x++)
		for (int y = 0; y < MAX_Y; y++)
			bomb_point[x][y] = false;
}
/*template <typename T>
bool SetBombs(int _x, int _y, int _turn)
{
	if (_x < 0 || _x >= MAX_X || _y < 0 || _y >= MAX_Y)
		return false;

	if (bombs == NULL)
	{
		len = 1;
		bombs = new Bomb*[len];
		bombs[0] = new T(_x, _y, _turn);
		return true;
	}

	Bomb** tem = new Bomb*[len];
	for (int i = 0; i < len; i++)
		tem[i] = bombs[i];

	delete[] bombs;
	len++;
	bombs = new Bomb*[len];
	for (int i = 0; i < len - 1; i++)
		bombs[i] = tem[i];

	bombs[len - 1] = new T(_x, _y, _turn);
	delete[] tem;
	return true;
}
bool& Bombs::CheckBombPoint(int _x, int _y)
{
	return bomb_point[_x][_y];
}
bool Bombs::RemoveBomb(int index)
{
	if (index < 0 || index >= len)
		return false;

	delete bombs[index];
	for (int n = index; n < len - 1; n++)
		bombs[n] = bombs[n + 1];

	len--;
	Bomb** tem = new Bomb*[len];
	for (int n = 0; n < len; n++)
		tem[n] = bombs[n];

	delete[] bombs;
	bombs = new Bomb*[len];
	for (int n = 0; n < len; n++)
		bombs[n] = tem[n];

	delete[] tem;
	return true;
}
int Bombs::GetLen() const { return len; }
Bomb*& Bombs::GetBomb(int index)
{
	if (index < 0 || index >= len)
	{
		cout << "error~GetBomb: index " << index << "?->bombs[0]!" << endl;
		return bombs[0];
	}
	return bombs[index];
}*/