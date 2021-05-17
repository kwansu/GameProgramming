#pragma once
#include "stdafx.h"
#include "cMainScene.h"
#include "cSkinnedMesh.h"

cMainScene::cMainScene()
{
}


cMainScene::~cMainScene()
{
	// 나머지 모두 해체
	SafeDelete(m_pGrid);
}

void cMainScene::Setup()
{
	m_pGrid = new cGrid;
	m_pGrid->Setup(100, 1);

	// 각종 매니저 및 전역 객체 초기화
	g_pWorld->Setup();
	g_pWorld->LoadMap();
	g_pUIManager->Setup();

	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
}
void cMainScene::Update()
{
	g_pTimeManager->Update();
	g_pCamera->Update();
	g_pWorld->Update();
	g_pInput->Update();
}

void cMainScene::Render()
{

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);

	// ↓↓↓↓↓↓↓↓↓↓ 랜더 추가 ↓↓↓↓↓↓↓↓↓↓
	m_pGrid->Render();
	g_pWorld->Render();

	g_pUIManager->Render();

	//////////////////////////////////////////////////////


}


void cMainScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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