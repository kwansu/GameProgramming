#pragma once
#include "stdafx.h"
#include <bitset>

//눌러질 수 있는 키 전부 등록
#define KEYMAX 256


class cKeyManager
{
	SINGLETON(cKeyManager);

private:
	bitset<KEYMAX> m_bsKeyUp;
	bitset<KEYMAX> m_bsKeyDown;

	bool AnyKeyDown;

public:
	void Setup();
	void Destroy();

	//키를 한번 누르면~
	bool IsOnceKeyDown(int key, BOOL isText = FALSE);

	//눌렀다 떼면~
	bool IsOnceKeyUp(int key, BOOL isText = FALSE);

	//계속 누르고있으면~
	bool IsStayKeyDown(int key, BOOL isText = FALSE);

	//켜져있으면~
	bool IsToggleKey(int key, BOOL isText = FALSE);

	bool IsAnyKeyDown();

	bitset<KEYMAX> GetKeyUp() { return m_bsKeyUp; }
	bitset<KEYMAX> GetKeyDown() { return m_bsKeyDown; }

	void SetKeyDown(int key, bool state) { m_bsKeyDown.set(key, state); }
	void SetKeyUp(int key, bool state) { m_bsKeyUp.set(key, state); }
};

extern cKeyManager* g_pKeyManager;