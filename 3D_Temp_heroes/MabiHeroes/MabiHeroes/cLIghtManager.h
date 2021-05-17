#pragma once

#define	fLIGHT_ACTIVE_DISTANCE_SQ	1000000

class cLIghtManager
{
	SINGLETON(cLIghtManager);

private:
	vector<D3DXVECTOR3>	m_vecLightPos;
	D3DXVECTOR3			arrActiveLightPos[4];
	int					m_nActiveNum;

public:
	void Setup();
	void Updete(const D3DXVECTOR3& vCenter);
	
	float* GetActiveLightsPosArray();
	int	GetActiveLightNum();
};

extern cLIghtManager* g_pLightManager;

