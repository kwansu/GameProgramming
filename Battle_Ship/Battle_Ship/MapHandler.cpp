#include "MapHandler.h"
#include "Base.h"

MapHandler::MapHandler() : Map()
{
	player_team = RED;
	list_len = 3;
	menu_list = new MAPMENU[list_len];
	menu_list[0] = END_OF_TURN;
	menu_list[1] = SAVE;
	menu_list[2] = EXIT;
}
void MapHandler::StartMenu()
{
	while (1)
	{
		cout << "<Battle Ship>" << endl;
		cout << "1.새 게임  2.불러오기  3.게임 종료" << endl;
		int select;
		cin >> select;
		switch (select)
		{
		case 1:
			stage.SetArchipelago();
			for (int n = 0; n < 52; n++)
			{
				GetPoint(stage.GetBlock(n)->GetX(), stage.GetBlock(n)->GetY()) = stage.GetBlock(n);
			}
			stage.SetShip(red_ships, blue_ships, &MapHandler::MoveShip, this);
			MapMenu();
			break;
		case 2:
			LoadGame();
			break;
		case 3:
			return;
		default:
			cout << "잘못 입력하였습니다." << endl;
			break;
		}
	}
}
void MapHandler::MapMenu()
{
	Ship_List* ships;
	if (player_team == RED)
		ships = &red_ships;
	else
		ships = &blue_ships;

	while (1)
	{
		delete[] menu_list;
		list_len = 3;
		menu_list = new MAPMENU[list_len];
		menu_list[0] = END_OF_TURN;
		menu_list[1] = SAVE;
		menu_list[2] = EXIT;
		ShowMap();
		cout << "<메뉴>" << endl;
		int move_point = 0;
		int num = 1;
		bool attack_mode = false;
		for (int n = 0; n < ships->GetBigLen(); n++)
			move_point += ships->GetBigShip(n).GetMovePoint();
		for (int n = 0; n < ships->GetSmallLen(); n++)
			move_point += ships->GetSmallShip(n).GetMovePoint();

		for (int n = 0; n < ships->GetBigLen(); n++)
			if (ships->GetBigShip(n).GetAttackBomb())
				attack_mode = true;
		for (int n = 0; n < ships->GetSmallLen(); n++)
			if (ships->GetSmallShip(n).GetAttackBomb())
				attack_mode = true;

		if (move_point > 0)
		{
			cout << num++ << ".이동  ";
			MAPMENU* tem = new MAPMENU[list_len];
			for (int n = 0; n < list_len; n++)
				tem[n] = menu_list[n];

			delete[] menu_list;
			menu_list = new MAPMENU[++list_len];
			menu_list[0] = MOVE;
			for (int n = 1; n < list_len; n++)
				menu_list[n] = tem[n - 1];

			delete[] tem;
		}
		if (attack_mode)
		{
			cout << num++ << ".폭탄설치  ";
			MAPMENU* tem = new MAPMENU[list_len];
			for (int n = 0; n < list_len; n++)
				tem[n] = menu_list[n];

			delete[] menu_list;
			menu_list = new MAPMENU[++list_len];
			menu_list[0] = ATTACK;
			for (int n = 1; n < list_len; n++)
				menu_list[n] = tem[n - 1];
			if (menu_list[1] == MOVE)
			{
				menu_list[0] = MOVE;
				menu_list[1] = ATTACK;
			}

			delete[] tem;
		}
		cout << num++ << ".턴종료  ";
		cout << num++ << ".저장  ";
		cout << num << ".종료" << endl;
		int select;
		cin >> select;
		if (select == -1)
		{
			HiddenAIMode();
			continue;
		}
		if (select < 1 || select > list_len)
		{
			cout << "잘못 눌렀습니다." << endl;
		}
		else
		{
			switch (menu_list[select - 1])
			{
			case MOVE:
				MoveMode();
				break;
			case ATTACK:
				AttackMode();
				break;
			case END_OF_TURN:
				EndOfTurn();
				break;
			case SAVE:
				SaveGame();
				break;
			case EXIT:
				cout << endl << "정말로 종료합니까?" << endl;
				cout << "1.종료  2.취소 (현재 데이터는 사라집니다.)" << endl;
				cin >> select;
				if (select == 1)
				{
					for (int n = red_ships.GetBigLen() - 1; n >= 0; n--)
						red_ships.RemoveShip(&red_ships.GetBigShip(n));
					for (int n = red_ships.GetSmallLen() - 1; n >= 0; n--)
						red_ships.RemoveShip(&red_ships.GetSmallShip(n));
					for (int n = blue_ships.GetBigLen() - 1; n >= 0; n--)
						blue_ships.RemoveShip(&red_ships.GetBigShip(n));
					for (int n = blue_ships.GetSmallLen() - 1; n >= 0; n--)
						blue_ships.RemoveShip(&blue_ships.GetSmallShip(n));

					Initialization();
					return;
				}
				cout << "취소 되었습니다." << endl;
				continue;		
			}
		}
	}
}
void MapHandler::RemoveShip(Ship* _ship)
{
	int x = _ship->GetX();
	int y = _ship->GetY();
	GetPoint(x, y) = NULL;
	if (_ship->GetLayout() == BIG_SHIP)
	{
		if (_ship->GetDir() == UP || _ship->GetDir() == DOWN)
		{
			GetPoint(x, y + 1) = NULL;
			GetPoint(x, y - 1) = NULL;
			GetPoint(x, y + 2) = NULL;
			GetPoint(x, y - 2) = NULL;
		}
		else
		{
			GetPoint(x + 1, y) = NULL;
			GetPoint(x - 1, y) = NULL;
			GetPoint(x + 2, y) = NULL;
			GetPoint(x - 2, y) = NULL;
		}
	}
	else
	{
		if (_ship->GetDir() == UP || _ship->GetDir() == DOWN)
		{
			GetPoint(x, y + 1) = NULL;
			GetPoint(x, y - 1) = NULL;
		}
		else
		{
			GetPoint(x + 1, y) = NULL;
			GetPoint(x - 1, y) = NULL;
		}
	}
	red_ships.RemoveShip(_ship);
	blue_ships.RemoveShip(_ship);
}
void MapHandler::MoveMode()
{
	Ship_List* ships;
	Ship* ship;
	if (player_team == RED)
		ships = &red_ships;
	else
		ships = &blue_ships;

	int small_len = ships->GetSmallLen();
	int big_len = ships->GetBigLen();
	if (small_len + big_len == 0)
	{
		cout << "더 이상 이동할 배가 없습니다." << endl;
		return;
	}
	cout << "어떤 배를 이동합니까?" << endl;
	for (int n = 1; n <= big_len; n++)
		cout << n << ".big_ship(" << n << ")  ";
	for (int n = 1; n <= small_len; n++)
		cout << n + big_len << ".small_ship(" << n << ")  ";
	cout << endl;
	int select;
	cin >> select;
	if (select < 1 || select > big_len + small_len)
	{
		cout << "잘못 눌렀습니다." << endl;
		return;
	}
	if (select > big_len)
		ship = &(ships->GetSmallShip(select - big_len - 1));
	else
		ship = &(ships->GetBigShip(select - 1));
	int &straight = ship->GetStraight();
	int &turn = ship->GetTurnabout();
	if (straight + turn == 0)
	{
		cout << "이 배는 더 이상 이동할 수 없습니다." << endl;
		return;
	}
	cout << "어떻게 움직입니까?" << endl;
	cout << "1.전진  2.시계방향회전  3.반시계방향회전 (남은 이동 횟수 : 전진(" << straight << "), 회전(" << turn << ")" << endl;
	char move[10];
	cin >> move;
	for (int n = 0; n < 10; n++)
	{
		if (move[n] > '0' && move[n] < '4')
		{
			switch (move[n])
			{
			case '1':
				if (straight == 0)
					continue;

				switch (ship->GetDir())
				{
				case UP:
					if (!MoveShip(ship->GetX(), ship->GetY() - 1, ship))
					{
						cout << "이동불가능한 장소입니다." << endl;
						return;
					}
					break;
				case DOWN:
					if (!MoveShip(ship->GetX(), ship->GetY() + 1, ship))
					{
						cout << "이동불가능한 장소입니다." << endl;
						return;
					}
					break;
				case LEFT:
					if (!MoveShip(ship->GetX() - 1, ship->GetY(), ship))
					{
						cout << "이동불가능한 장소입니다." << endl;
						return;
					}
					break;
				case RIGHT:
					if (!MoveShip(ship->GetX() + 1, ship->GetY(), ship))
					{
						cout << "이동불가능한 장소입니다." << endl;
						return;
					}
					break;
				}
				straight--;
				break;
			case '2':
				if (turn == 0)
					continue;

				switch (ship->GetDir())
				{
				case UP:
					ship->GetDir() = RIGHT;
					if (!MoveShip(ship->GetX(), ship->GetY(), ship))
					{
						cout << "이동불가능한 장소입니다." << endl;
						ship->GetDir() = UP;
						return;
					}
					break;
				case DOWN:
					ship->GetDir() = LEFT;
					if (!MoveShip(ship->GetX(), ship->GetY(), ship))
					{
						cout << "이동불가능한 장소입니다." << endl;
						ship->GetDir() = DOWN;
						return;
					}
					break;
				case LEFT:
					ship->GetDir() = UP;
					if (!MoveShip(ship->GetX(), ship->GetY(), ship))
					{
						cout << "이동불가능한 장소입니다." << endl;
						ship->GetDir() = LEFT;
						return;
					}
					break;
				case RIGHT:
					ship->GetDir() = DOWN;
					if (!MoveShip(ship->GetX(), ship->GetY(), ship))
					{
						cout << "이동불가능한 장소입니다." << endl;
						ship->GetDir() = RIGHT;
						return;
					}
					break;
				}
				turn--;
				break;
			case '3':
				if (turn == 0)
					continue;

				switch (ship->GetDir())
				{
				case UP:
					ship->GetDir() = LEFT;
					if (!MoveShip(ship->GetX(), ship->GetY(), ship))
					{
						cout << "이동불가능한 장소입니다." << endl;
						ship->GetDir() = UP;
						return;
					}
					break;
				case DOWN:
					ship->GetDir() = RIGHT;
					if (!MoveShip(ship->GetX(), ship->GetY(), ship))
					{
						cout << "이동불가능한 장소입니다." << endl;
						ship->GetDir() = DOWN;
						return;
					}
					break;
				case LEFT:
					ship->GetDir() = DOWN;
					if (!MoveShip(ship->GetX(), ship->GetY(), ship))
					{
						cout << "이동불가능한 장소입니다." << endl;
						ship->GetDir() = LEFT;
						return;
					}
					break;
				case RIGHT:
					ship->GetDir() = UP;
					if (!MoveShip(ship->GetX(), ship->GetY(), ship))
					{
						cout << "이동불가능한 장소입니다." << endl;
						ship->GetDir() = RIGHT;
						return;
					}
					break;
				}
				turn--;
			}
		}
	}
}
void MapHandler::AttackMode()
{
	Ship_List* ships;
	Ship* ship;
	if (player_team == RED)
		ships = &red_ships;
	else
		ships = &blue_ships;

	int big_len = ships->GetBigLen();
	int small_len = ships->GetSmallLen();

	int num = 1;
	cout << "어떤 배로 공격하시겠습니까?" << endl;
	for (int n = 1; n <= big_len; n++)
		cout << n << ".big_ship(" << n << ")  ";
	for (int n = 1; n <= small_len; n++)
		cout << n + big_len << ".small_ship(" << n << ")  ";
	cout << endl;
	int select;
	cin >> select;
	if (select < 1 || select > big_len + small_len)
	{
		cout << "잘못 눌렀습니다." << endl;
		return;
	}
	if (select > big_len)
		ship = &(ships->GetSmallShip(select - big_len - 1));
	else
		ship = &(ships->GetBigShip(select - 1));

	if (!ship->GetAttackBomb())
	{
		cout << "이 배는 더 이상 공격할 수 없습니다." << endl;
		return;
	}
	else
	{
		int x, y;
		num = 2;
		cout << "어떤 폭탄을 사용하시겠습니까?" << endl;
		cout << "1.단발폭탄  ";
		if (ship->GetLayout() == BIG_SHIP)
		{
			//if (static_cast<Big_Ship*>(ship)->GetCrossLen() > 0)
			//	cout << num++ << ".소역폭탄";
			//if (static_cast<Big_Ship*>(ship)->GetNineLen() > 0)
			//	cout << num << ".광역폭탄  ";
			cout << "2.소역폭탄  3.광역폭탄 ";
			cout << "(남은 폭탄: 소역(" << static_cast<Big_Ship*>(ship)->GetCrossLen() << "), 광역(" << static_cast<Big_Ship*>(ship)->GetNineLen() << ")" << endl;
			cin >> select;
			cout << "어디에 설치 합니까?(x, y)" << endl;
			cin >> x >> y;
			switch (select)
			{
			case 1:
				if (!GetBombs().SetBombs<Bomb>(x, y, GetTurn()))
				{
					cout << "설치 할 수없는 장소입니다. (" << x << " , " << y << ")" << endl;
					return;
				}
				ship->GetAttackBomb() = false;
				break;
			case 2:
				if (static_cast<Big_Ship*>(ship)->GetCrossLen() <= 0)
				{
					cout << "이 배는 소역폭탄이 더 이상 없습니다." << endl;
					return;
				}
				if (!GetBombs().SetBombs<Cross_Bomb>(x, y, GetTurn()))
				{
					cout << "설치 할 수없는 장소입니다. (" << x << " , " << y << ")" << endl;
					return;
				}
				static_cast<Big_Ship*>(ship)->GetCrossLen()--;
				ship->GetAttackBomb() = false;
				break;
			case 3:
				if (static_cast<Big_Ship*>(ship)->GetNineLen() <= 0)
				{
					cout << "이 배는 광역폭탄이 더 이상 없습니다." << endl;
					return;
				}
				if (!GetBombs().SetBombs<Nine_Bomb>(x, y, GetTurn()))
				{
					cout << "설치 할 수없는 장소입니다. (" << x << " , " << y << ")" << endl;
					return;
				}
				static_cast<Big_Ship*>(ship)->GetNineLen()--;
				ship->GetAttackBomb() = false;
				break;
			default:
				cout << "잘못 입력하셨습니다." << endl;
				return;
			}
		}
		else
		{
			//if (static_cast<Small_Ship*>(ship)->GetCrossLen() > 0)
			//	cout << num++ << ".소역지뢰";
			cout << "2.소역지뢰" << endl;
			cin >> select;
			cout << "어디에 설치 합니까?(x, y)" << endl;
			cin >> x >> y;
			switch (select)
			{
			case 1:
				if (!GetBombs().SetBombs<Bomb>(x, y, GetTurn()))
				{
					cout << "설치 할 수없는 장소입니다. (" << x << " , " << y << ")" << endl;
					return;
				}
				ship->GetAttackBomb() = false;
				break;
			case 2:
				if (static_cast<Small_Ship*>(ship)->GetCrossLen() <= 0)
				{
					cout << "이 배는 소역폭탄이 더 이상 없습니다." << endl;
					return;
				}
				if (!GetBombs().SetBombs<Cross_Bomb>(x, y, GetTurn()))
				{
					cout << "설치 할 수없는 장소입니다. (" << x << " , " << y << ")" << endl;
					return;
				}
				static_cast<Small_Ship*>(ship)->GetCrossLen()--;
				ship->GetAttackBomb() = false;
				break;
			default:
				cout << "잘못 입력하셨습니다." << endl;
				return;
			}
		}
		cout << "(" << x << ", " << y << " ) 에 설치를 하였습니다." << endl;
	}
}
template<class T>
bool MapHandler::EnermyShipAttack(Ship_List* player_ships)
{
	enermy_ai.SetMapObjectData(this);
	for (int n = 0; n < player_ships->GetBigLen(); n++)
		enermy_ai.SetBigShipPathPriority(&player_ships->GetBigShip(n), false);
	for (int n = 0; n < player_ships->GetSmallLen(); n++)
		enermy_ai.SetSmallShipPathPriority(&player_ships->GetSmallShip(n), false);

	int sum_point = 0;
	for (int y = 0; y < MAX_Y; y++)
		for (int x = 0; x < MAX_X; x++)
			if (enermy_ai.GetPriorityPoint(x, y) > 0)
				sum_point += enermy_ai.GetPriorityPoint(x, y);

	srand(time(NULL));
	int r = rand() % sum_point;
	for (int y = 0; y < MAX_Y; y++)
	{
		for (int x = 0; x < MAX_X; x++)
		{
			if (enermy_ai.GetPriorityPoint(x, y) > 0)
			{
				r -= enermy_ai.GetPriorityPoint(x, y);
				if (r <= 0)
				{
					GetBombs().SetBombs<T>(x, y, GetTurn(), false);
					return true;
				}
			}
		}
	}
	return false;
}
void MapHandler::EnermyAttackMode()
{
	Ship_List* ships;
	Ship_List* player_ships;
	if (player_team == RED)
	{
		ships = &blue_ships;
		player_ships = &red_ships;
	}
	else
	{
		ships = &red_ships;
		player_ships = &blue_ships;
	}

	int r;
	srand(time(NULL));
	for (int n = 0; n < ships->GetBigLen(); n++)
	{
		if (!ships->GetBigShip(n).GetAttackBomb())
			continue;

		r = rand() % 7;
		if (r == 1 || r == 4 || r == 6 || r == 3)
		{
			if (ships->GetBigShip(n).GetCrossLen() > 0)
			{
				ships->GetBigShip(n).GetCrossLen()--;
				ships->GetBigShip(n).GetAttackBomb() = false;
				EnermyShipAttack<Cross_Bomb>(player_ships);
			}
			else
				r = 2;
		}
		else if (r == 2 || r == 5)
		{
			if (ships->GetBigShip(n).GetNineLen() > 0)
			{
				ships->GetBigShip(n).GetNineLen()--;
				ships->GetBigShip(n).GetAttackBomb() = false;
				EnermyShipAttack<Nine_Bomb>(player_ships);
			}
			else
				r = 0;
		}
		else if (r == 0)
		{
			ships->GetBigShip(n).GetAttackBomb() = false;
			EnermyShipAttack<Bomb>(player_ships);
		}
	}
	for (int n = 0; n < ships->GetSmallLen(); n++)
	{
		if (!ships->GetSmallShip(n).GetAttackBomb())
			continue;

		r = rand() % 5;
		if (r == 1 || r == 2 || r == 3 || r == 4)
		{
			if (ships->GetSmallShip(n).GetCrossLen() > 0)
			{
				ships->GetSmallShip(n).GetCrossLen()--;
				ships->GetSmallShip(n).GetAttackBomb() = false;
				EnermyShipAttack<Cross_Bomb>(player_ships);
			}
			else
				r = 0;
		}
		else if (r == 0)
		{
			ships->GetSmallShip(n).GetAttackBomb() = false;
			EnermyShipAttack<Bomb>(player_ships);
		}
	}
}
void MapHandler::EndOfTurn()
{
	cout << "정말로 턴을 종료합니까?" << endl;
	cout << "1.턴 종료  2.취소 (행동이 남아있어도 턴이 종료됩니다.)" << endl;
	int select;
	cin >> select;
	if (select != 1)
		return;

	int &turn = GetTurn();
	turn++;
	int len = GetBombs().GetLen();

	for (int n = 0; n < len; n++)
	{
		if (GetBombs().GetBomb(n)->GetEndTurn() == turn)
		{
			GetBombs().GetBomb(n)->ExplosionRange(&GetBombs(), &Bombs::SetPoint, false);
			GetBombs().GetBomb(n)->Explosion(this, &MapHandler::BombExplosion);
			GetBombs().RemoveBomb(n);
			n--; len--;
		}
	}
	EnermyAttackMode();
	EnermyMoveMode();

	for (int n = 0; n < red_ships.GetBigLen(); n++)
		red_ships.GetBigShip(n).EndOfTurn();
	for (int n = 0; n < red_ships.GetSmallLen(); n++)
		red_ships.GetSmallShip(n).EndOfTurn();
	for (int n = 0; n < blue_ships.GetBigLen(); n++)
		blue_ships.GetBigShip(n).EndOfTurn();
	for (int n = 0; n < blue_ships.GetSmallLen(); n++)
		blue_ships.GetSmallShip(n).EndOfTurn();
}
void MapHandler::SaveGame()
{
	int num;
	cout << "어디에 저장 하겠습니까?" << endl;
	cout << "(0 ~ 9) : ";
	cin >> num;
	if (num < 0 || num > 9)
	{
		cout << "그 곳에는 저장 할 수 없습니다." << endl;
		return;
	}
	ofstream save;
	char n = num + '0';
	char fileName[10] = "save0.txt";
	fileName[4] = n;
	save.open(fileName);

	if (save.is_open())
	{
		save << stage.GetNowStage() << endl << GetTurn() << endl << player_team << endl;
		for (int n = 0; n < red_ships.GetBigLen(); n++)
		{
			Big_Ship ship = red_ships.GetBigShip(n);
			save << -1 << endl << -4 << endl << ship.GetHP() << endl << ship.GetDir() << endl << ship.GetStraight() << endl << ship.GetTurnabout() << endl << ship.GetAttackBomb() << endl << ship.GetCrossLen() << endl << ship.GetNineLen() << endl << ship.GetX() << endl << ship.GetY() << endl;
		}
		for (int n = 0; n < red_ships.GetSmallLen(); n++)
		{
			Small_Ship ship = red_ships.GetSmallShip(n);
			save << -1 << endl << -5 << endl << ship.GetHP() << endl << ship.GetDir() << endl << ship.GetStraight() << endl << ship.GetTurnabout() << endl << ship.GetAttackBomb() << endl << ship.GetCrossLen() << endl << ship.GetX() << endl << ship.GetY() << endl;
		}
		for (int n = 0; n < blue_ships.GetBigLen(); n++)
		{
			Big_Ship ship = blue_ships.GetBigShip(n);
			save << -2 << endl << -4 << endl << ship.GetHP() << endl << ship.GetDir() << endl << ship.GetStraight() << endl << ship.GetTurnabout() << endl << ship.GetAttackBomb() << endl << ship.GetCrossLen() << endl << ship.GetNineLen() << endl << endl << ship.GetX() << endl << ship.GetY() << endl;
		}
		for (int n = 0; n < blue_ships.GetSmallLen(); n++)
		{
			Small_Ship ship =blue_ships.GetSmallShip(n);
			save << -2 << endl << -5 << endl << ship.GetHP() << endl << ship.GetDir() << endl << ship.GetStraight() << endl << ship.GetTurnabout() << endl << ship.GetAttackBomb() << endl << ship.GetCrossLen() << endl << ship.GetX() << endl << ship.GetY() << endl;
		}
		for (int n = 0; n < GetBombs().GetLen(); n++)
		{	
			Bomb* bomb = GetBombs().GetBomb(n);
			save << -3 << endl << bomb->GetLayout() << endl << bomb->GetX() << endl << bomb->GetY() << endl << bomb->GetEndTurn() << endl;
		}
		save << -100 << endl;
		cout << "저장 성공!" << endl;
		return;
	}
	cout << "저장 실패!" << endl;
}
void MapHandler::LoadGame()
{
	int num;
	cout << "어떤 파일을 불러오겠습니까?" << endl;
	cout << "(0 ~ 9) : ";
	cin >> num;
	if (num < 0 || num > 9)
	{
		cout << "그 파일은 불러올 수 없습니다." << endl;
		return;
	}

	ifstream read;
	char fileName[10] = "save0.txt";
	char n = num + '0';
	fileName[4] = n;
	read.open(fileName);

	if (read.is_open())
	{
		int x, y;
		read >> num;
		if (num == 1)
		{
			stage.SetArchipelago();
			for (int n = 0; n < 52; n++)
			{
				GetPoint(stage.GetBlock(n)->GetX(), stage.GetBlock(n)->GetY()) = stage.GetBlock(n);
			}
		}
		read >> num;
		GetTurn() = num; //팀선택
		while (num != -100)
		{
			read >> num;
			switch (num)
			{
			case -1:
				read >> num;
				if (num == -4)
				{
					read >> num;
					Big_Ship &b_ship = red_ships.AddBigShip(RED, num);
					read >> num;
					switch (num)
					{
					case 0:
						b_ship.GetDir() = UP;
						break;
					case 1:
						b_ship.GetDir() = DOWN;
						break;
					case 2:
						b_ship.GetDir() = LEFT;
						break;
					case 3:
						b_ship.GetDir() = RIGHT;
						break;
					}
					read >> num;
					b_ship.GetStraight() = num;
					read >> num;
					b_ship.GetTurnabout() = num;
					read >> num;
					b_ship.GetAttackBomb() = num;
					read >> num;
					b_ship.GetCrossLen() = num;
					read >> num;
					b_ship.GetNineLen() = num;
					read >> x >> y;
					MoveShip(x, y, &b_ship);
				}
				if (num == -5)
				{
					read >> num;
					Small_Ship &b_ship = red_ships.AddSmallShip(RED, num);
					read >> num;
					switch (num)
					{
					case 0:
						b_ship.GetDir() = UP;
						break;
					case 1:
						b_ship.GetDir() = DOWN;
						break;
					case 2:
						b_ship.GetDir() = LEFT;
						break;
					case 3:
						b_ship.GetDir() = RIGHT;
						break;
					}
					read >> num;
					b_ship.GetStraight() = num;
					read >> num;
					b_ship.GetTurnabout() = num;
					read >> num;
					b_ship.GetAttackBomb() = num;
					read >> num;
					b_ship.GetCrossLen() = num;
					read >> x >> y;
					MoveShip(x, y, &b_ship);
				}
				break;
			case -2:
				read >> num;
				if (num == -4)
				{
					read >> num;
					Big_Ship &b_ship = blue_ships.AddBigShip(BLUE, num);
					read >> num;
					switch (num)
					{
					case 0:
						b_ship.GetDir() = UP;
						break;
					case 1:
						b_ship.GetDir() = DOWN;
						break;
					case 2:
						b_ship.GetDir() = LEFT;
						break;
					case 3:
						b_ship.GetDir() = RIGHT;
						break;
					}
					read >> num;
					b_ship.GetStraight() = num;
					read >> num;
					b_ship.GetTurnabout() = num;
					read >> num;
					b_ship.GetAttackBomb() = num;
					read >> num;
					b_ship.GetCrossLen() = num;
					read >> num;
					b_ship.GetNineLen() = num;
					read >> x >> y;
					MoveShip(x, y, &b_ship);
				}
				if (num == -5)
				{
					read >> num;
					Small_Ship &b_ship = blue_ships.AddSmallShip(BLUE, num);
					read >> num;
					switch (num)
					{
					case 0:
						b_ship.GetDir() = UP;
						break;
					case 1:
						b_ship.GetDir() = DOWN;
						break;
					case 2:
						b_ship.GetDir() = LEFT;
						break;
					case 3:
						b_ship.GetDir() = RIGHT;
						break;
					}
					read >> num;
					b_ship.GetStraight() = num;
					read >> num;
					b_ship.GetTurnabout() = num;
					read >> num;
					b_ship.GetAttackBomb() = num;
					read >> num;
					b_ship.GetCrossLen() = num;
					read >> x >> y;
					MoveShip(x, y, &b_ship);
				}
				break;
			case -3:
				read >> num;
				switch (num)
				{
				case 4:
					read >> x >> y >> num;
					GetBombs().SetBombs<Bomb>(x, y, GetTurn() * 2 - num);
					break;
				case 5:
					read >> x >> y >> num;
					GetBombs().SetBombs<Cross_Bomb>(x, y, GetTurn() * 2 - num);
					break;
				case 6:
					read >> x >> y >> num;
					GetBombs().SetBombs<Nine_Bomb>(x, y, GetTurn() * 2 - num);
					break;
				}
			}
		}
		MapMenu();
	}
}
void MapHandler::EnermyMoveMode()
{
	Ship_List* ships;
	if (player_team == RED)
		ships = &blue_ships;
	else
		ships = &red_ships;

	for (int n = 0; n < ships->GetBigLen(); n++)
	{
		char* command = enermy_ai.GetRandomMovingCommand(&ships->GetBigShip(n), this);
		for (int i = 0; i < 4; i++)
		{
			int x = ships->GetBigShip(n).GetX();
			int y = ships->GetBigShip(n).GetY();
			DIRECTION &dir = ships->GetBigShip(n).GetDir();
			switch (command[i])
			{
			case 'g':
				switch (dir)
				{
				case UP:
					MoveShip(x, y - 1, &ships->GetBigShip(n));
					break;
				case DOWN:
					MoveShip(x, y + 1, &ships->GetBigShip(n));
					break;
				case LEFT:
					MoveShip(x - 1, y, &ships->GetBigShip(n));
					break;
				case RIGHT:
					MoveShip(x + 1, y, &ships->GetBigShip(n));
					break;
				}
				break;
			case 't':
				switch (dir)
				{
				case UP:
					dir = RIGHT;
					MoveShip(x, y, &ships->GetBigShip(n));
					break;
				case DOWN:
					dir = LEFT;
					MoveShip(x, y, &ships->GetBigShip(n));
					break;
				case LEFT:
					dir = UP;
					MoveShip(x, y, &ships->GetBigShip(n));
					break;
				case RIGHT:
					dir = DOWN;
					MoveShip(x, y, &ships->GetBigShip(n));
					break;
				}
				break;
			case 'r':
				switch (dir)
				{
				case UP:
					dir = LEFT;
					MoveShip(x, y, &ships->GetBigShip(n));
					break;
				case DOWN:
					dir = RIGHT;
					MoveShip(x, y, &ships->GetBigShip(n));
					break;
				case LEFT:
					dir = DOWN;
					MoveShip(x, y, &ships->GetBigShip(n));
					break;
				case RIGHT:
					dir = UP;
					MoveShip(x, y, &ships->GetBigShip(n));
					break;
				}
				break;
			default:
				break;
			}
		}
	}
	for (int n = 0; n < ships->GetSmallLen(); n++)
	{
		char* command = enermy_ai.GetRandomMovingCommand(&ships->GetSmallShip(n), this);
		for (int i = 0; i < 5; i++)
		{
			int x = ships->GetSmallShip(n).GetX();
			int y = ships->GetSmallShip(n).GetY();
			DIRECTION &dir = ships->GetSmallShip(n).GetDir();
			switch (command[i])
			{
			case 'g':
				switch (dir)
				{
				case UP:
					MoveShip(x, y - 1, &ships->GetSmallShip(n));
					break;
				case DOWN:
					MoveShip(x, y + 1, &ships->GetSmallShip(n));
					break;
				case LEFT:
					MoveShip(x - 1, y, &ships->GetSmallShip(n));
					break;
				case RIGHT:
					MoveShip(x + 1, y, &ships->GetSmallShip(n));
					break;
				}
				break;
			case 't':
				switch (dir)
				{
				case UP:
					dir = RIGHT;
					MoveShip(x, y, &ships->GetSmallShip(n));
					break;
				case DOWN:
					dir = LEFT;
					MoveShip(x, y, &ships->GetSmallShip(n));
					break;
				case LEFT:
					dir = UP;
					MoveShip(x, y, &ships->GetSmallShip(n));
					break;
				case RIGHT:
					dir = DOWN;
					MoveShip(x, y, &ships->GetSmallShip(n));
					break;
				}
				break;
			case 'r':
				switch (dir)
				{
				case UP:
					dir = LEFT;
					MoveShip(x, y, &ships->GetSmallShip(n));
					break;
				case DOWN:
					dir = RIGHT;
					MoveShip(x, y, &ships->GetSmallShip(n));
					break;
				case LEFT:
					dir = DOWN;
					MoveShip(x, y, &ships->GetSmallShip(n));
					break;
				case RIGHT:
					dir = UP;
					MoveShip(x, y, &ships->GetSmallShip(n));
					break;
				}
				break;
			default:
				break;
			}
		}
	}
}
void MapHandler::BombExplosion(int _x, int _y, int _power)
{
	if (_x < 0 || _x >= MAX_X || _y < 0 || _y >= MAX_Y)
		return;

	if (GetLayout(_x, _y) == SMALL_SHIP || GetLayout(_x, _y) == BIG_SHIP)
	{
		static_cast<Ship*>(GetPoint(_x, _y))->GetHP() -= _power;
		cout << "배가 (" << _x << ", " << _y << ")에 폭탄에 의해 " << _power << "의 피해를 입습니다." << endl;
		if (static_cast<Ship*>(GetPoint(_x, _y))->GetHP() < 0)
		{
			RemoveShip(static_cast<Ship*>(GetPoint(_x, _y)));

			cout << "(" << _x << ", " << _y << ")의 배가 침몰합니다." << endl;
		}
	}
}
void MapHandler::HiddenAIMode()
{
	Ship_List* ships;
	if (player_team == RED)
		ships = &red_ships;
	else
		ships = &blue_ships;

	int select;
	cin >> select;
	if (select == 1)
	{
		enermy_ai.SetMapObjectData(this);
		for (int n = 0; n < ships->GetBigLen(); n++)
			enermy_ai.SetBigShipPathPriority(&ships->GetBigShip(n), false);
		cout << enermy_ai.GetNum() << endl;
		for (int n = 0; n < ships->GetSmallLen(); n++)
			enermy_ai.SetSmallShipPathPriority(&ships->GetSmallShip(n), false);
		cout << enermy_ai.GetNum() << endl;
		enermy_ai.ShowPriorityPointMap();
	}
	if (select == 2)
	{
		for (int n = 0; n < red_ships.GetBigLen(); n++)
			cout << red_ships.GetBigShip(n).GetLayout() << " : " << red_ships.GetBigShip(n).GetX() << ", " << red_ships.GetBigShip(n).GetY() << endl;
		for (int n = 0; n < red_ships.GetSmallLen(); n++)
			cout << red_ships.GetSmallShip(n).GetLayout() << " : " << red_ships.GetSmallShip(n).GetX() << ", " << red_ships.GetSmallShip(n).GetY() << endl;
	}
}
bool MapHandler::MoveShip(int _x, int _y, Ship* _ship)
{
	DIRECTION dir = _ship->GetDir();

	if (_ship->GetLayout() == BIG_SHIP)
	{
		Big_Ship* big_ship = static_cast<Big_Ship*>(_ship);
		if (GetPoint(_x, _y) != NULL && GetPoint(_x, _y) != _ship)
			return false;

		if (dir == UP || dir == DOWN)
		{
			if (!GetPoint(0, 0)->CheckValue(_x, _y + 2) || !GetPoint(0, 0)->CheckValue(_x, _y - 2))
				return false;
			if (GetPoint(_x, _y + 1) != NULL && GetPoint(_x, _y + 1) != _ship)
				return false;
			if (GetPoint(_x, _y - 1) != NULL && GetPoint(_x, _y - 1) != _ship)
				return false;
			if (GetPoint(_x, _y + 2) != NULL && GetPoint(_x, _y + 2) != _ship)
				return false;
			if (GetPoint(_x, _y - 2) != NULL && GetPoint(_x, _y - 2) != _ship)
				return false;
		}
		else
		{
			if (!GetPoint(0, 0)->CheckValue(_x + 2, _y) || !GetPoint(0, 0)->CheckValue(_x - 2, _y))
				return false;
			if (GetPoint(_x + 2, _y) != NULL && GetPoint(_x + 2, _y) != _ship)
				return false;
			if (GetPoint(_x - 2, _y) != NULL && GetPoint(_x - 2, _y) != _ship)
				return false;
			if (GetPoint(_x + 1, _y) != NULL && GetPoint(_x + 1, _y) != _ship)
				return false;
			if (GetPoint(_x - 1, _y) != NULL && GetPoint(_x - 1, _y) != _ship)
				return false;
		}
		if (big_ship->GetPosition() != NULL)
			*big_ship->GetPosition() = NULL;
		for (int n = 0; n < 4; n++)
		{
			if (big_ship->GetPosition_Stretch(n) != NULL)
				*big_ship->GetPosition_Stretch(n) = NULL;
		}
		GetPoint(_x, _y) = big_ship;
		big_ship->GetPosition() = &GetPoint(_x, _y);
		if (dir == UP || dir == DOWN)
		{
			GetPoint(_x, _y + 1) = big_ship;
			GetPoint(_x, _y - 1) = big_ship;
			GetPoint(_x, _y + 2) = big_ship;
			GetPoint(_x, _y - 2) = big_ship;
			big_ship->GetPosition_Stretch(0) = &GetPoint(_x, _y + 1);
			big_ship->GetPosition_Stretch(1) = &GetPoint(_x, _y - 1);
			big_ship->GetPosition_Stretch(2) = &GetPoint(_x, _y + 2);
			big_ship->GetPosition_Stretch(3) = &GetPoint(_x, _y - 2);
		}
		else
		{
			GetPoint(_x + 1, _y) = big_ship;
			GetPoint(_x - 1, _y) = big_ship;
			GetPoint(_x + 2, _y) = big_ship;
			GetPoint(_x - 2, _y) = big_ship;
			big_ship->GetPosition_Stretch(0) = &GetPoint(_x + 1, _y);
			big_ship->GetPosition_Stretch(1) = &GetPoint(_x - 1, _y);
			big_ship->GetPosition_Stretch(2) = &GetPoint(_x + 2, _y);
			big_ship->GetPosition_Stretch(3) = &GetPoint(_x - 2, _y);
		}
	}
	else
	{
		Small_Ship* big_ship = static_cast<Small_Ship*>(_ship);
		if (GetPoint(_x, _y) != NULL && GetPoint(_x, _y) != _ship)
			return false;

		if (dir == UP || dir == DOWN)
		{
			if (!GetPoint(0, 0)->CheckValue(_x, _y + 1) || !GetPoint(0, 0)->CheckValue(_x, _y - 1))
				return false;
			if (GetPoint(_x, _y + 1) != NULL && GetPoint(_x, _y + 1) != _ship)
				return false;
			if (GetPoint(_x, _y - 1) != NULL && GetPoint(_x, _y - 1) != _ship)
				return false;
		}
		else
		{
			if (!GetPoint(0, 0)->CheckValue(_x + 1, _y) || !GetPoint(0, 0)->CheckValue(_x - 1, _y))
				return false;
			if (GetPoint(_x + 1, _y) != NULL && GetPoint(_x + 1, _y) != _ship)
				return false;
			if (GetPoint(_x - 1, _y) != NULL && GetPoint(_x - 1, _y) != _ship)
				return false;
		}
		if (big_ship->GetPosition() != NULL)
			*big_ship->GetPosition() = NULL;
		for (int n = 0; n < 2; n++)
		{
			if (big_ship->GetPosition_Stretch(n) != NULL)
				*big_ship->GetPosition_Stretch(n) = NULL;
		}
		GetPoint(_x, _y) = big_ship;
		big_ship->GetPosition() = &GetPoint(_x, _y);
		if (dir == UP || dir == DOWN)
		{
			GetPoint(_x, _y + 1) = big_ship;
			GetPoint(_x, _y - 1) = big_ship;
			big_ship->GetPosition_Stretch(0) = &GetPoint(_x, _y + 1);
			big_ship->GetPosition_Stretch(1) = &GetPoint(_x, _y - 1);
		}
		else
		{
			GetPoint(_x + 1, _y) = big_ship;
			GetPoint(_x - 1, _y) = big_ship;
			big_ship->GetPosition_Stretch(0) = &GetPoint(_x + 1, _y);
			big_ship->GetPosition_Stretch(1) = &GetPoint(_x - 1, _y);
		}
	}
	_ship->GetX() = _x; _ship->GetY() = _y;
	return true;
}

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
void Bomb::ExplosionRange(Bombs* _bombs, void(Bombs::*Range)(int, int, bool), bool _bool)
{
	(_bombs->*Range)(x, y, _bool);
}
void Bomb::Explosion(MapHandler* _map, void(MapHandler::*explo)(int, int, int))
{
	(_map->*explo)(x, y, power);
}

Nine_Bomb::Nine_Bomb(int _x, int _y, int _turn, int _power, int _delay)
	:Bomb(_x, _y, _turn, _power, _delay) {}
void Nine_Bomb::ExplosionRange(Bombs* _bombs, void(Bombs::*Range)(int, int, bool), bool _bool)
{
	int x = GetX(); int y = GetY();
	(_bombs->*Range)(x, y, _bool);
	(_bombs->*Range)(x, y + 1, _bool);
	(_bombs->*Range)(x, y - 1, _bool);
	(_bombs->*Range)(x + 1, y, _bool);
	(_bombs->*Range)(x + 1, y + 1, _bool);
	(_bombs->*Range)(x + 1, y - 1, _bool);
	(_bombs->*Range)(x - 1, y, _bool);
	(_bombs->*Range)(x - 1, y + 1, _bool);
	(_bombs->*Range)(x - 1, y - 1, _bool);
}
void Nine_Bomb::Explosion(MapHandler* _map, void(MapHandler::*explo)(int, int, int))
{
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
void Cross_Bomb::ExplosionRange(Bombs* _bombs, void(Bombs::*Range)(int, int, bool), bool _bool)
{
	int x = GetX(); int y = GetY();
	(_bombs->*Range)(x, y, _bool);
	(_bombs->*Range)(x, y + 1, _bool);
	(_bombs->*Range)(x, y - 1, _bool);
	(_bombs->*Range)(x + 1, y, _bool);
	(_bombs->*Range)(x - 1, y, _bool);
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
}*/
bool Bombs::CheckBombPoint(int _x, int _y)
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
}