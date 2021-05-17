#include "stdafx.h"
#include "cKeyManager.h"


cKeyManager* g_pKeyManager = cKeyManager::GetInstance();

cKeyManager::cKeyManager(void)
:AnyKeyDown(false)
{
}


cKeyManager::~cKeyManager(void)
{
}

void cKeyManager::Setup(void)
{
	for (int i = 0; i < KEYMAX; i++)
	{
		this->GetKeyUp().set(i, false);
		this->GetKeyUp().set(i, false);
	}
}

void cKeyManager::Destroy(void)
{

}

//Ű�� �ѹ� ��������?
bool cKeyManager::IsOnceKeyDown(int key, BOOL isText)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!this->GetKeyDown()[key])
		{
			this->SetKeyDown(key, true);
			return true;
			AnyKeyDown = true;
		}
	}
	else this->SetKeyDown(key, false);

	return false;
}

//Ű�� �� �ѹ��� (���������¿���) �翩������ �˻�
bool cKeyManager::IsOnceKeyUp(int key, BOOL isText)
{
	if (GetAsyncKeyState(key) & 0x8000) this->SetKeyUp(key, true);
	else
	{
		if (this->GetKeyUp()[key])
		{
			this->SetKeyUp(key, false);
			return true;
			AnyKeyDown = false;
		}
	}
	return false;
}

bool cKeyManager::IsStayKeyDown(int key, BOOL isText)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}

bool cKeyManager::IsToggleKey(int key, BOOL isText)
{
	if (GetKeyState(key) & 0x0001) return true;
	return false;
}

bool cKeyManager::IsAnyKeyDown()
{
	return AnyKeyDown;
}