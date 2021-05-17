#ifndef __BOMB_H__
#define __BOMB_H__

#include "Location.h"
#include "Base.h"

class MapHandler;
class Bombs;

class Bomb
{
	int x, y;
	int power;
	int delay;
	int end_turn;
	bool player_team;
public:
	Bomb(int _x, int _y, int _turn, int _power = 40, int _delay = 1);
	int GetPower() const;
	int GetEndTurn() const;
	int GetX() const;
	int GetY() const;
	bool GetPlayerTeam() const { return player_team; }
	virtual LAYOUT GetLayout() const { return BOMB; }
	virtual void ExplosionRange(Bombs* _bombs, void(Bombs::*Range)(int, int, bool), bool _bool);
	virtual void Explosion(MapHandler* _map, void(MapHandler::*explo)(int, int, int));
};

class Nine_Bomb : public Bomb
{
public:
	Nine_Bomb(int _x, int _y, int _turn, int _power = 30, int _delay = 2);
	LAYOUT GetLayout() const { return NINE_BOMB; }
	void ExplosionRange(Bombs* _bombs, void(Bombs::*Range)(int, int, bool), bool _bool);
	void Explosion(MapHandler* _map, void(MapHandler::*explo)(int, int, int));
};

class Cross_Bomb : public Bomb
{
public:
	Cross_Bomb(int _x, int _y, int _turn, int _power = 35, int _delay = 2);
	LAYOUT GetLayout() const { return CROSS_BOMB; }
	void ExplosionRange(Bombs* _bombs, void(Bombs::*Range)(int, int, bool), bool _bool);
	void Explosion(MapHandler* _map, void(MapHandler::*explo)(int, int, int));
};

class Bombs
{
	Bomb** bombs;
	int len;
	bool bomb_point[MAX_X][MAX_Y];
public:
	Bombs();
	template <typename T>
	bool SetBombs(int _x, int _y, int _turn, bool player_team = true)
	{
		if (_x < 0 || _x >= MAX_X || _y < 0 || _y >= MAX_Y)
			return false;

		if (bombs == NULL)
		{
			len = 1;
			bombs = new Bomb*[len];
			bombs[0] = new T(_x, _y, _turn);
			if (player_team)
				bombs[0]->ExplosionRange(this, &Bombs::SetPoint, true);

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
		if (player_team)
			bombs[len - 1]->ExplosionRange(this, &Bombs::SetPoint, true);

		delete[] tem;
		return true;
	}
	bool CheckBombPoint(int _x, int _y);
	bool RemoveBomb(int index);
	void SetPoint(int _x, int _y, bool _bool)
	{
		if (_x < 0 || _x >= MAX_X || _y < 0 || _y >= MAX_Y)
			return;

		bomb_point[_x][_y] = _bool;
	}
	int GetLen() const;
	Bomb*& GetBomb(int index);
};

#endif