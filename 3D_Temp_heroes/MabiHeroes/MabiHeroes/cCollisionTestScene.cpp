#include "stdafx.h"
#include "cCollisionTestScene.h"


cCollisionTestScene::cCollisionTestScene()
{
}


cCollisionTestScene::~cCollisionTestScene()
{
}

void cCollisionTestScene::Setup()
{
	g_pWorld->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup(100, 1);
}

void cCollisionTestScene::Release()
{
	SafeDelete(m_pGrid);
}

void cCollisionTestScene::Update()
{
	g_pTimeManager->Update();
	g_pWorld->Update();
	g_pCamera->Update();
	g_pInput->Update();
}

void cCollisionTestScene::Render()
{
	m_pGrid->Render();
	g_pWorld->Render();
}

void cCollisionTestScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
