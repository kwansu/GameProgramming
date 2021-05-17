#pragma once
#include "stdafx.h"
#include <bitset>

//������ �� �ִ� Ű ���� ���
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

	//Ű�� �ѹ� ������~
	bool IsOnceKeyDown(int key, BOOL isText = FALSE);

	//������ ����~
	bool IsOnceKeyUp(int key, BOOL isText = FALSE);

	//��� ������������~
	bool IsStayKeyDown(int key, BOOL isText = FALSE);

	//����������~
	bool IsToggleKey(int key, BOOL isText = FALSE);

	bool IsAnyKeyDown();

	bitset<KEYMAX> GetKeyUp() { return m_bsKeyUp; }
	bitset<KEYMAX> GetKeyDown() { return m_bsKeyDown; }

	void SetKeyDown(int key, bool state) { m_bsKeyDown.set(key, state); }
	void SetKeyUp(int key, bool state) { m_bsKeyUp.set(key, state); }
};

extern cKeyManager* g_pKeyManager;