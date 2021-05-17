#ifndef __GET_DIRECTION_H__
#define __GET_DIRECTION_H__

#include "Location.h"
#include "Map.h"
#include "Base.h"

class Node : public Location
{
	int cost;
	int remain;
	bool active;
	bool pass;
	Node* parents;
public:
	Node() : cost(0), remain(0), active(false), pass(true) {}
	void SetCost(int _value);
	void SetRemain(int _value);
	void SetParents(Node* _parents);
	void SetActivation(bool _bool);
	void SetPassing(bool _bool);
	int GetCost() const;
	int GetRemain() const;
	bool GetActive() const;
	bool GetPass() const;
	Node* GetParents() const;
	DIRECTION& GetDir();
};

template <class T>
class List
{
	T** arr;
	int len;
public:
	List() : arr(NULL), len(0) {}
	List(const List& copy)
	{
		len = copy.len;
		arr = new T*[len];
		for (int n = 0; n < len; n++)
			arr[n] = copy.arr[n];
	}
	void Initialization()
	{
		arr = NULL;
		len = 0;
	}
	void AddMember(T* member)
	{
		if (arr == NULL)
		{
			len = 1;
			arr = new T*[len];
			arr[0] = member;
			return;
		}
		T** tem = new T*[len];
		for (int n = 0; n < len; n++)
			tem[n] = arr[n];

		delete[] arr;
		len++;
		arr = new T*[len];
		for (int n = 0; n < len - 1; n++)
			arr[n] = tem[n];

		delete[] tem;
		arr[len - 1] = member;
	}
	void operator=(T* member)
	{
		AddMember(member);
	}
	void RemoveMember(int index)
	{
		if (index < 0 || index >= len)
		{
			cout << "error~List.RemoveMember(" << index << ")~?->cancle!" << endl;
			return;
		}
		for (int n = index; n < len; n++)
			arr[n] = arr[n + 1];

		len--;
		T** tem = new T*[len];
		for (int n = 0; n < len; n++)
			tem[n] = arr[n];

		delete[] arr;
		arr = new T*[len];
		for (int n = 0; n < len; n++)
			arr[n] = tem[n];

		delete[] tem;
	}
	void RemoveMember(T* member)
	{
		for (int n = 0; n < len; n++)
			if (arr[n] == member)
				RemoveMember(n);
	}
	T* GetMember(int index)
	{
		if (index < 0 || index >= len)
		{
			cout << "error~List.GetMember(" << index << ")?->arr[0]!" << endl;
			return arr[0];
		}
		return arr[index];
	}
	int GetLen() const
	{
		return len;
	}
	int Sort(int(T::*GetInt)(void)const)
	{
		for (int i = len; i > 0; i--)
		{
			for (int n = 0; n < i; n++)
			{
				if ((arr[n]->*GetInt)() - (arr[n + 1]->*GetInt)() > 0)
				{
					T* tem = arr[n];
					arr[n] = arr[n + 1];
					arr[n + 1] = tem;
				}
			}
		}
		return len;
	}
};

class A_Star
{
	Node node[MAX_X][MAX_Y];
	Node* start_node;
	Node* goal_node;
	List<Node> open_list;
	List<Node> close_list;
	bool find;
public:
	A_Star();
	int Abs(int _value);
	bool CheckPassing(int x, int y);
	bool SetStartNode(Ship* ship, Map* _map);
	bool SetGoalNode(int x, int y);
	bool AddOpenListNode(int x, int y, Node* parents, LAYOUT size, DIRECTION dir);
	void GetMapData(Map* _map);
	void NodeInitialization();
	void ListExpansion(LAYOUT size);
	Node* GetDirection(LAYOUT size);
};

#endif