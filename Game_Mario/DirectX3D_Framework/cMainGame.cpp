#include "stdafx.h"
#include "cMainGame.h"


cMainGame::cMainGame()
{
}


cMainGame::~cMainGame()
{
}


void cMainGame::Initialize()
{
	m_pCamera = g_pCamera;
	m_pGrid = new cGrid;
	m_pMario = new cObject_Mario;

	m_pGrid->SetInterval(5);
	
	// 바닥 맵 생성 및 초기화 :
	cObject_Plane* pPlane = new cObject_Plane;
	pPlane->Setup(5, 5, 60, D3DCOLOR_XRGB(40, 0, 10));
	pPlane->SetPosition(0, -5, 0);
	m_apPlanes.push_back(pPlane);

	pPlane = new cObject_Plane;
	pPlane->Setup(5, 5, 20, D3DCOLOR_XRGB(0, 30, -40));
	pPlane->SetPosition(0, 20, 100);
	pPlane->SetMovePlane(10, 0.2f);
	m_apPlanes.push_back(pPlane);

	pPlane = new cObject_Plane;
	pPlane->Setup(5, 5, 20, D3DCOLOR_XRGB(0, 30, -40));
	pPlane->SetPosition(0, 40, 160);
	pPlane->SetMovePlane(10, 0.4f);
	m_apPlanes.push_back(pPlane);

	for (int i = 0; i < 10; ++i)
	{
		pPlane = new cObject_Plane;
		pPlane->Setup(5, 5, 10, D3DCOLOR_XRGB(30, -40, 0));
		pPlane->SetPosition(0, 40 + i*10, 200 + i*10);
		m_apPlanes.push_back(pPlane);
	}


	m_pCamera->Setup();
	m_pCamera->SetTarget(m_pMario->GetPosition());
	m_pGrid->Setup();
	m_pMario->Setup(&m_apPlanes);
}


void cMainGame::Release()
{
	SAFE_DELETE(m_pGrid);
	
	int size = m_apPlanes.size();
	for (int i = 0; i < size; ++i)
		SAFE_DELETE(m_apPlanes[i]);

	SAFE_DELETE(m_pMario);

	cDevice::GetInstance()->Release(); //디바이스 해체 마지막에.
}


void cMainGame::Run()
{
	g_pTime->AdjustTime();

	Update();
	Render();
}


void cMainGame::Update()
{
	g_pInput->Update();
	m_pCamera->Update();
	int size = m_apPlanes.size();
	for (int i = 0; i < size; ++i)
		m_apPlanes[i]->Update();
	m_pMario->Update();
}


void cMainGame::Render()
{
	g_pDevice->Clear(NULL, NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(185, 185, 185),
		1.0f, 0);
	g_pDevice->BeginScene();

	// render:
	m_pGrid->Render();
	m_pMario->Render();

	int size = m_apPlanes.size();
	for (int i = 0; i < size; ++i)
		m_apPlanes[i]->Render();

	// end
	g_pDevice->EndScene();
	g_pDevice->Present(NULL, NULL, NULL, NULL);
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


void cMainGame::DialogHandler(HWND hDlg, UINT iMsg, WPARAM wp, LPARAM lp)
{
	cObject_Plane*	pPlane;
	cVec3			vTmp;

	switch (iMsg)
	{
	case WM_COMMAND:
		switch (wp)
		{
		case IDC_BUTTON_CREATE:
			pPlane = new cObject_Plane;
			pPlane->Setup(1, 1, 1);
			m_apPlanes.push_back(pPlane);
			//SendDlgItemMessage(hDlg, IDC_LIST1,
			//	LB_ADDSTRING, 2, (LPARAM)(m_apPlanes.size()-1));
			vTmp = *pPlane->GetPosition();
			SetDlgItemInt(hDlg, IDC_POSITIONX, vTmp.x, TRUE);
			SetDlgItemInt(hDlg, IDC_POSITIONY, vTmp.x, TRUE);
			SetDlgItemInt(hDlg, IDC_POSITIONZ, vTmp.x, TRUE);
			break;
		case IDC_BUTTON_SETPOS:
			vTmp.x = GetDlgItemInt(hDlg, IDC_POSITIONX, NULL, TRUE);
			vTmp.y = GetDlgItemInt(hDlg, IDC_POSITIONY, NULL, TRUE);
			vTmp.z = GetDlgItemInt(hDlg, IDC_POSITIONZ, NULL, TRUE);
			m_apPlanes.back()->SetPosition(&vTmp);
			m_apPlanes.back()->UpdateWorld();
			break;
		case IDC_BUTTON_SETSIZE:
			vTmp.x = GetDlgItemInt(hDlg, IDC_SCALEX, NULL, TRUE);
			vTmp.y = GetDlgItemInt(hDlg, IDC_SCALEY, NULL, TRUE);
			vTmp.z = GetDlgItemInt(hDlg, IDC_SCALEZ, NULL, TRUE);
			m_apPlanes.back()->SetScale(vTmp.x, vTmp.y, vTmp.z);
			m_apPlanes.back()->UpdateWorld();
			break;
		case IDC_BUTTON_SETColor:
			vTmp.x = GetDlgItemInt(hDlg, IDC_COLORR, NULL, TRUE);
			vTmp.y = GetDlgItemInt(hDlg, IDC_COLORG, NULL, TRUE);
			vTmp.z = GetDlgItemInt(hDlg, IDC_COLORB, NULL, TRUE);
			m_apPlanes.back()->SetColor(D3DCOLOR_XRGB((int)vTmp.x, (int)vTmp.y, (int)vTmp.z));
			m_apPlanes.back()->UpdateWorld();
			break;
		}
		return;
	case WM_CLOSE:
		DestroyWindow(g_hDlg);
		g_hDlg = NULL;
		return;
	}
}
