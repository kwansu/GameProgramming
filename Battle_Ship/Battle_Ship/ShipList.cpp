#include "ShipList.h"

Big_Ship& Ship_List::AddBigShip(TEAM _team, int _hp)
{
	if (big_len == 0)
	{
		big_ships = new Big_Ship(_team, _hp);
		big_len++;
		return big_ships[0];
	}
	Big_Ship* tem = new Big_Ship[big_len];
	for (int n = 0; n < big_len; n++)
		tem[n] = big_ships[n];

	delete[] big_ships;
	big_ships = new Big_Ship[big_len + 1];
	for (int n = 0; n < big_len; n++)
		big_ships[n] = tem[n];

	delete[] tem;
	big_ships[big_len].GetHP() = _hp;
	big_ships[big_len].GetTeam() = _team;
	big_len++;
	return big_ships[big_len - 1];
}
Small_Ship& Ship_List::AddSmallShip(TEAM _team, int _hp)
{
	if (small_len == 0)
	{
		small_ships = new Small_Ship(_team, _hp);
		small_len++;
		return small_ships[0];
	}
	Small_Ship* tem = new Small_Ship[small_len];
	for (int n = 0; n < small_len; n++)
		tem[n] = small_ships[n];

	delete[] small_ships;
	small_ships = new Small_Ship[small_len + 1];
	for (int n = 0; n < small_len; n++)
		small_ships[n] = tem[n];

	delete[] tem;
	small_ships[small_len].GetHP() = _hp;
	small_ships[small_len].GetTeam() = _team;
	small_len++;
	return small_ships[small_len - 1];
}
Small_Ship& Ship_List::GetSmallShip(int index)
{
	if (index > small_len || index < 0)
	{
		cout << "error~GetSmallShip : index? -> small_ships[0]!" << endl;
		return small_ships[0];
	}
	return small_ships[index];
}
Big_Ship& Ship_List::GetBigShip(int index)
{
	if (index > small_len || index < 0)
	{
		cout << "error~GetBigShip : index? -> big_ships[0]!" << endl;
		return big_ships[0];
	}
	return big_ships[index];
}
int Ship_List::GetSmallLen()
{
	return small_len;
}
int Ship_List::GetBigLen()
{
	return big_len;
}
bool Ship_List::RemoveShip(Ship* _ship)
{
	for (int n = 0; n < small_len; n++)
	{
		if (&small_ships[n] == _ship)
		{
			for (int i = n; i < small_len - 1; i++)
				small_ships[i] = small_ships[i + 1];

			small_len--;
			Small_Ship* tem = new Small_Ship[small_len];
			for (int i = 0; i < small_len; i++)
				tem[i] = small_ships[i];

			delete[] small_ships;
			small_ships = new Small_Ship[small_len];
			for (int i = 0; i < small_len; i++)
				small_ships[i] = tem[i];

			delete[] tem;
			return true;
		}
	}
	for (int n = 0; n < big_len; n++)
	{
		if (&big_ships[n] == _ship)
		{
			for (int i = n; i < big_len - 1; i++)
				big_ships[i] = big_ships[i + 1];

			big_len--;
			Big_Ship* tem = new Big_Ship[big_len];
			for (int i = 0; i < big_len; i++)
				tem[i] = big_ships[i];

			delete[] big_ships;
			big_ships = new Big_Ship[big_len];
			for (int i = 0; i < big_len; i++)
				big_ships[i] = tem[i];

			delete[] tem;
			return true;
		}
	}
	return false;
}
Ship_List::~Ship_List()
{
	if (small_ships != NULL)
		delete[] small_ships;
	if (big_ships != NULL)
		delete[] big_ships;
}