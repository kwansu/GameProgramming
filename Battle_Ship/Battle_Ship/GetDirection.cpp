#include "GetDirection.h"
#include "Base.h"

void Node::SetCost(int _value)
{
	if (_value > 0)
		cost = _value;
}
void Node::SetRemain(int _value)
{
	if (_value > 0)
		remain = _value;
}
void Node::SetParents(Node* _parents)
{
	parents = _parents;
}
void Node::SetActivation(bool _bool)
{
	active = _bool;
}
void Node::SetPassing(bool _bool)
{
	pass = _bool;
}
int Node::GetCost() const
{
	return cost;
}
int Node::GetRemain() const
{
	return remain;
}
bool Node::GetActive() const
{
	return active;
}
bool Node::GetPass() const
{
	return pass;
}
Node* Node::GetParents() const
{
	return parents;
}
DIRECTION& Node::GetDir()
{
	DIRECTION a;
	return a;
}

A_Star::A_Star()
{
	for (int y = 0; y < MAX_Y; y++)
		for (int x = 0; x < MAX_X; x++)
			node[x][y].SetLocation(x, y);

	start_node = NULL;
	goal_node = NULL;
	find = true;
}
int A_Star::Abs(int _value)
{
	if (_value < 0)
		return -_value;

	return _value;
}
bool A_Star::CheckPassing(int x, int y)
{
	if (!node[0][0].CheckValue(x, y))
		return false;

	if (!node[x][y].GetPass())
		return false;

	return true;
}
bool A_Star::SetStartNode(Ship* ship, Map* _map)
{
	GetMapData(_map);
	int x = ship->GetX();
	int y = ship->GetY();
	node[x][y].SetPassing(true);
	if (ship->GetLayout() == BIG_SHIP)
	{
		if (ship->GetDir() == UP || ship->GetDir() == DOWN)
		{
			node[x][y + 1].SetPassing(true);
			node[x][y - 1].SetPassing(true);
			node[x][y - 2].SetPassing(true);
			node[x][y + 2].SetPassing(true);
		}
		else
		{
			node[x + 1][y].SetPassing(true);
			node[x - 1][y].SetPassing(true);
			node[x + 2][y].SetPassing(true);
			node[x - 2][y].SetPassing(true);
		}
	}
	else
	{
		if (ship->GetDir() == UP || ship->GetDir() == DOWN)
		{
			node[x][y + 1].SetPassing(true);
			node[x][y - 1].SetPassing(true);
		}
		else
		{
			node[x + 1][y].SetPassing(true);
			node[x - 1][y].SetPassing(true);
		}
	}

	open_list.Initialization();
	close_list.Initialization();

	start_node = &node[x][y];
	node[x][y].SetActivation(true);
	open_list = &node[x][y];
	return true;
}
bool A_Star::SetGoalNode(int x, int y)
{
	if (!CheckPassing(x, y))
		return false;
	if (start_node == NULL)
		return false;

	goal_node = &node[x][y];
	start_node->SetRemain(Abs(x - start_node->GetX()) + Abs(y - start_node->GetY()));
	return true;
}
bool A_Star::AddOpenListNode(int x, int y, Node* parents, LAYOUT size, DIRECTION dir)
{
	if (size == BIG_SHIP)
	{
		switch (dir)
		{
		case UP:
			if (!CheckPassing(x, y - 1) || !CheckPassing(x, y - 2) || !CheckPassing(x, y + 2))
				return false;
			break;
		case DOWN:
			if (!CheckPassing(x, y + 1) || !CheckPassing(x, y + 2) || !CheckPassing(x, y - 2))
				return false;
			break;
		case LEFT:
			if (!CheckPassing(x - 1, y) || !CheckPassing(x - 2, y) || !CheckPassing(x + 2, y))
				return false;
			break;
		case RIGHT:
			if (!CheckPassing(x + 1, y) || !CheckPassing(x + 2, y) || !CheckPassing(x - 2, y))
				return false;
			break;
		}
	}
	else
	{
		switch (dir)
		{
		case UP:
			if (!CheckPassing(x, y - 1))
				return false;
			break;
		case DOWN:
			if (!CheckPassing(x, y + 1))
				return false;
			break;
		case LEFT:
			if (!CheckPassing(x - 1, y))
				return false;
			break;
		case RIGHT:
			if (!CheckPassing(x + 1, y))
				return false;
			break;
		}
	}
	if (&node[x][y] == goal_node)
	{
		find = false;
		node[x][y].SetParents(parents);
		return true;
	}
	if (node[x][y].GetActive())
	{
		if (node[x][y].GetCost() > parents->GetCost() + 1)
		{
			node[x][y].SetCost(parents->GetCost() + 1);
			node[x][y].SetParents(parents);
			open_list.RemoveMember(&node[x][y]);
			close_list.RemoveMember(&node[x][y]);
			open_list = &node[x][y];
			return true;
		}
		return false;
	}
	else
	{
		node[x][y].SetActivation(true);
		node[x][y].SetCost(parents->GetCost() + 1);
		node[x][y].SetParents(parents);
		node[x][y].SetRemain(Abs(x - goal_node->GetX()) + Abs(y - goal_node->GetY()));
		open_list = &node[x][y];
		return true;
	}
}
void A_Star::GetMapData(Map* _map)
{
	NodeInitialization();
	for (int y = 0; y < MAX_Y; y++)
	{
		for (int x = 0; x < MAX_X; x++)
		{
			switch (_map->GetLayout(x, y))
			{
			case EMPTY:
				break;
			default:
				node[x][y].SetPassing(false);
				break;
			}
		}
	}
}
void A_Star::NodeInitialization()
{
	for (int y = 0; y < MAX_Y; y++)
	{
		for (int x = 0; x < MAX_X; x++)
		{
			node[x][y].SetCost(0);
			node[x][y].SetActivation(false);
			node[x][y].SetParents(NULL);
			node[x][y].SetPassing(true);
			node[x][y].SetRemain(0);
		}
	}
}
void A_Star::ListExpansion(LAYOUT size)
{
	int len = open_list.GetLen();
	List<Node> tem = open_list;
	for (int n = 0; n < len; n++)
	{
		int x = tem.GetMember(n)->GetX();
		int y = tem.GetMember(n)->GetY();
		AddOpenListNode(x, y - 1, tem.GetMember(n), size, UP);
		AddOpenListNode(x, y + 1, tem.GetMember(n), size, DOWN);
		AddOpenListNode(x - 1, y, tem.GetMember(n), size, LEFT);
		AddOpenListNode(x + 1, y, tem.GetMember(n), size, RIGHT);
		open_list.RemoveMember(tem.GetMember(n));
		close_list.AddMember(tem.GetMember(n));
	}
}
Node* A_Star::GetDirection(LAYOUT size)
{
	if (start_node == NULL || goal_node == NULL)
	{
		cout << "error~A_Star:GetDirection() start_node and goal_node? -> node[0][0]!" << endl;
		return &node[0][0];
	}
	
	while (find)
	{
		ListExpansion(size);
		if (open_list.GetLen() == 0)
		{
			close_list.Sort(&Node::GetRemain);
			return close_list.GetMember(0);
		}
	}
	return goal_node;
}