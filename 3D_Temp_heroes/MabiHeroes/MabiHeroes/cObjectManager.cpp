#include "stdafx.h"
#include "cObjectManager.h"

cObjectManager::cObjectManager()
{
	ZeroMemory(&m_lightDirection, sizeof(m_lightDirection));
}


cObjectManager::~cObjectManager()
{
}

void cObjectManager::Setup()
{
	m_pTerrain = new cTerrain;
	m_pTerrain->Setup();

	cObj_Fiona* pObject = new cObj_Fiona;
	pObject->Setup();
	g_pCamera->SetTarget(&pObject->GetPosition());

	m_vecAllObject.push_back(pObject);
	m_vecActiveObject.push_back(pObject);

	//////////////////////////////////// 몬스터 생성 ///////////////////////////////////////////////////
	cNoll* pEnemyNoll = new cNoll;
	pEnemyNoll->Setup();
	pEnemyNoll->SetTarget(&pObject->GetPosition());
	pEnemyNoll->SetTargetObj(pObject);
	D3DXMATRIXA16 tempMat, matS;
	D3DXMatrixIdentity(&tempMat);
	D3DXMatrixIdentity(&matS);
	tempMat._41 = 0;
	tempMat._43 = 0;
	D3DXMatrixScaling(&matS, 0.2f, 0.2f, 0.2f);
	pEnemyNoll->SetOriginMatrix(matS * tempMat);

	m_vecAllObject.push_back(pEnemyNoll);
	m_vecActiveObject.push_back(pEnemyNoll);
	//////////////////////////////////////////////////////////////////////////////////////////////////////

	// 임시 라이트 생성
	//m_lightDirection.Type = D3DLIGHT_DIRECTIONAL;
	//m_lightDirection.Diffuse = m_lightDirection.Ambient = D3DXCOLOR(1, 1, 1, 1);
	//m_lightDirection.Direction = D3DXVECTOR3(1, -1, 1);

	//g_pD3DDevice->SetLight(0, &m_lightDirection);
	//g_pD3DDevice->LightEnable(0, true);
	//g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
}

void cObjectManager::Update()
{
	for each(const auto &pObject in m_vecActiveObject)
	{
		pObject->Update();
	}

}

void cObjectManager::Render()
{
	m_pTerrain->Render();

	for each(const auto &pObject in m_vecActiveObject)
	{
		pObject->Render();
	}
}
