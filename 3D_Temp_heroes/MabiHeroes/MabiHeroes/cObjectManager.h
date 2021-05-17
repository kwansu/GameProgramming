#pragma once
#include "stdObjects.h"
#include "cTerrain.h"

#define g_pObjectManager	cObjectManager::GetInstance()

class cObjectManager
{
	SINGLETON(cObjectManager);

private:
	// 월드에 있는 모든 오브젝트들
	vector<cGameObject*>	m_vecAllObject;

	// 현재 캐릭터를 중심으로 범위안에 들어와서 계산될 오브젝트들
	vector<cGameObject*>	m_vecActiveObject;

	// 게임 맵
	cTerrain*				m_pTerrain;

	D3DLIGHT9				m_lightDirection;

public:
	void Setup();
	void Update();
	void Render();
};

