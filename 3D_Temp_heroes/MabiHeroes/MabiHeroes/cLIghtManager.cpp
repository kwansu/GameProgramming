#include "stdafx.h"
#include "cLIghtManager.h"


cLIghtManager* g_pLightManager = cLIghtManager::GetInstance();

cLIghtManager::cLIghtManager()
{
}


cLIghtManager::~cLIghtManager()
{
}

void cLIghtManager::Setup()
{
	m_vecLightPos.push_back(D3DXVECTOR3(100, 20, 100));
	m_vecLightPos.push_back(D3DXVECTOR3(-100, 20, 100));
	m_vecLightPos.push_back(D3DXVECTOR3(-100, 20, -100));
}

void cLIghtManager::Updete(const D3DXVECTOR3 & vCenter)
{
	m_nActiveNum = 0;

	for each(const auto pos in m_vecLightPos)
	{
		if (D3DXVec3Dot(&vCenter, &pos) < fLIGHT_ACTIVE_DISTANCE_SQ)
		{
			arrActiveLightPos[m_nActiveNum++] = pos;
			if (m_nActiveNum >= 4)
				break;
		}
	}
}

float * cLIghtManager::GetActiveLightsPosArray()
{
	return &arrActiveLightPos[0].x;
}

int cLIghtManager::GetActiveLightNum()
{
	return m_nActiveNum;
}

