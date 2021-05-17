#pragma once

#include "StdAfx.h"
#include "cMonsterTestScene.h"
#include "cGrid.h"
#include "cCamera.h"
#include "cObjectManager.h"
#include "cSkinnedMesh.h"
#include "cSkelArcher.h"
#include "cObj_Fiona.h"

cMonsterTestScene::cMonsterTestScene(void)
	: m_pGrid(NULL)
{
}

cMonsterTestScene::~cMonsterTestScene(void)
{
	SAFE_DELETE(m_pGrid);
	//SAFE_DELETE(m_pCamera);


	g_pTextureManager->Destroy();
	//g_pDeviceManager->Destroy();
	//g_pObjectManager->Destroy();
}

void cMonsterTestScene::Setup()
{
	m_pGrid = new cGrid;
	m_pGrid->Setup(15, 1.0f);

	g_pCamera->Setup();
	g_pCamera->SetTarget(NULL);

	m_pSkelArcher = new cSkelArcher;
	m_pSkelArcher->Setup();
	m_pSkelArcher->SetupCreature();

	//m_pFiona = new cObj_Fiona;
	//m_pFiona->Setup();
	//m_pFiona->SetupCreature();
}

void cMonsterTestScene::Update()
{
	g_pTimeManager->Update();


	g_pCamera->Update();

	m_pSkelArcher->Update();
	m_pSkelArcher->UpdateCreature();

	//m_pFiona->Update();
	//m_pFiona->UpdateCreature();

	g_pInput->Update();
}

void cMonsterTestScene::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		pastelBlue,
		1.0f, 0);
	g_pD3DDevice->BeginScene();

	// ↓↓↓↓↓↓↓↓↓↓ 랜더 추가 ↓↓↓↓↓↓↓↓↓↓
	if (m_pGrid)
		m_pGrid->Render();

	m_pSkelArcher->Render();
	m_pSkelArcher->RenderCreature();

	//m_pFiona->Render();
	//m_pFiona->RenderCreature();

	////////////////////////////////////////////////////////////////



}

void cMonsterTestScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		g_pInput->KeyDown(wParam);
		break;
	case WM_KEYUP:
		g_pInput->KeyUp(wParam);
		break;
	case WM_LBUTTONDOWN:
		g_pInput->KeyDown(VK_LBUTTON);
		//SetCapture(g_hWnd);
		break;
	case WM_LBUTTONUP:
		g_pInput->KeyUp(VK_LBUTTON);
		ReleaseCapture();
		break;
	case WM_RBUTTONDOWN:
		g_pInput->KeyDown(VK_RBUTTON);
		//SetCapture(g_hWnd);
		break;
	case WM_RBUTTONUP:
		g_pInput->KeyUp(VK_RBUTTON);
		ReleaseCapture();
		break;
	case WM_MOUSEWHEEL:
		g_pInput->AddWheel(HIWORD(wParam));
		break;
	}
}

void cMonsterTestScene::SetLight()
{
	D3DXCOLOR c = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = stLight.Diffuse = stLight.Specular = c;
	D3DXVECTOR3 d(1, -1, 1);
	D3DXVec3Normalize(&d, &d);
	stLight.Direction = d;
	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
}