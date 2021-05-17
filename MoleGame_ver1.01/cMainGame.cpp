#include "stdafx.h"
#include "cMainGame.h"


cMainGame::cMainGame()
	: m_tNextTime(0), m_fFPS(60), m_nFrame(0)
	, m_pCamera(NULL), m_pGrid(NULL)
	, m_pHammer(NULL), m_pMachine(NULL)
{
}


cMainGame::~cMainGame()
{
	g_pGraphics->Release();
	g_pDeviceManager->Destroy();
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pMachine);
}


void cMainGame::Initialize()
{
	m_fFPS = 60;
	m_tFrameTime = 1000 / m_fFPS;

	g_pDDevice->SetRenderState(D3DRS_LIGHTING, false);

	// 오브젝트 생성 및 초기화
	m_pCamera = new cObject_Camera;
	m_pGrid = new cObject_Grid;
	m_pMachine = new cObject_MoleMachine;
	m_pHammer = new cObject_Hammer;

	m_pCamera->Setup();
	m_pCamera->UpdateProjection();
	m_pGrid->Setup();
	m_pMachine->Setup();
	m_pHammer->Setup();

	m_pHammer->SetArrayCube(&m_pMachine->m_aMole);
}


void cMainGame::Release()
{
}


void cMainGame::Run()
{
	g_tCurrentTime = GetTickCount();

	if (g_tCurrentTime < m_tNextTime)
		Sleep(m_tNextTime - g_tCurrentTime);

	Update();
	Render();
}


void cMainGame::Update()
{
	g_pInput->Update();
	m_pCamera->Update();
	//m_pGrid->Update();
	m_pMachine->Update();
	m_pHammer->Update();

	++m_nFrame;

	if (m_nFrame >= 600)
	{
		m_nFrame = -g_nStage * 300;
		++g_nStage;
	}
}


void cMainGame::Render()
{
	g_pDDevice->Clear(NULL, NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(210, 210, 210), 1.0f, 0);

	g_pDDevice->BeginScene();

	// 나중에 버텍스 구조체로 정의한뒤, 객채별 랜더안에서 설정.
	g_pDDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);

	// Render:
	//m_pGrid->Render();
	m_pMachine->Render();
	m_pHammer->Render();


	// Release
	g_pDDevice->EndScene();
	g_pDDevice->Present(NULL, NULL, NULL, NULL);
}


void cMainGame::MessageHandler(UINT iMsg, WPARAM wp, LPARAM lp)
{
	switch (iMsg)
	{
	case WM_KEYDOWN:
		g_pInput->KeyDown(wp);
		break;
	case WM_KEYUP:
		g_pInput->KeyUp(wp);
		break;
	case WM_MOUSEMOVE:
		g_pInput->SetMouse(LOWORD(lp), HIWORD(lp));
		break;
	case WM_LBUTTONDOWN:
		g_pInput->KeyDown(VK_LBUTTON);
		break;
	case WM_LBUTTONUP:
		g_pInput->KeyUp(VK_LBUTTON);
		break;
	case WM_RBUTTONDOWN:
		g_pInput->KeyDown(VK_RBUTTON);
		break;
	case WM_RBUTTONUP:
		g_pInput->KeyUp(VK_RBUTTON);
		break;
	case WM_MOUSEWHEEL:
		g_pInput->AddWheel(HIWORD(wp));
		break;
	}
}
