#ifndef __MAP_HANDLER_H__
#define __MAP_HANDLER_H__

#include "Map.h"
#include "Const.h"
#include "ShipAI.h"

class MapHandler : public Map
{
	Ship_AI enermy_ai;
	TEAM player_team;
	MAPMENU* menu_list;
	int list_len;
	Stage stage;
public:
	MapHandler();
	void StartMenu();
	void MapMenu();
	void RemoveShip(Ship* _ship);
	void MoveMode();
	void AttackMode();
	void MenuListArray(int num);
	template<class T>
	bool EnermyShipAttack(Ship_List* player_ships);
	void EnermyAttackMode();
	void EnermyMoveMode();
	void EndOfTurn();
	void SaveGame();
	void LoadGame();
	void HiddenAIMode();
	bool MoveShip(int _x, int _y, Ship* _ship);
	void BombExplosion(int _x, int _y, int _power);
};

#endif