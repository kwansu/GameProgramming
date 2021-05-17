#pragma once
#include "stdObjects.h"
#include "cTerrain.h"

#define g_pObjectManager	cObjectManager::GetInstance()

class cObjectManager
{
	SINGLETON(cObjectManager);

private:
	// ���忡 �ִ� ��� ������Ʈ��
	vector<cGameObject*>	m_vecAllObject;

	// ���� ĳ���͸� �߽����� �����ȿ� ���ͼ� ���� ������Ʈ��
	vector<cGameObject*>	m_vecActiveObject;

	// ���� ��
	cTerrain*				m_pTerrain;

	D3DLIGHT9				m_lightDirection;

public:
	void Setup();
	void Update();
	void Render();
};

