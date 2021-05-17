#include "stdafx.h"
#include "cBattleRoomScene.h"


cBattleRoomScene::cBattleRoomScene()
{
}


cBattleRoomScene::~cBattleRoomScene()
{
}

void cBattleRoomScene::Setup()
{
	m_vecWorldGrid.resize(36);

	int i = 0;
	// ¹Ù´Ú
	m_vecWorldGrid[i].p = D3DXVECTOR3( 200,   0, 200); m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3( 200,   0,-200); m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 1);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200,   0, 200); m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200,   0, 200); m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3( 200,   0,-200); m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 1);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200,   0,-200); m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 1);

	// µÚ
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 400, -200);	 m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 400, -200);	 m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 1);
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 0, -200);	 m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 0, -200);	 m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 400, -200);	 m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 1);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 0, -200); 	 m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 1);
			
	// ¾Õ
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 400, 200);	   m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 0, 200);		   m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 1);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 400, 200);	   m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 400, 200);	   m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 0, 200);		   m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 1);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 0, 200);	   m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 1);

	// ¿À¸¥ÂÊ
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 400, -200);	 m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 0, -200);	 m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 1);
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 400, 200);	 m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 400, 200);	 m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 0, -200);	 m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 1);
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 0, 200);	 m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 1);
					
	// ¿ÞÂÊ
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 400, -200);	  m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 400, 200);	  m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 1);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 0, -200);	  m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 0, -200);	  m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 400, 200);	  m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 1);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 0, 200);	  m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 1);
				
	// À§
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 400, 200);  m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 400, 200); m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 1);
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 400, -200); m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 400, 200); m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 400, -200); m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 1);
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 400, -200); m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 1);

	m_pTexture = g_pTextureManager->GetTexture("./MapData/grid.jpg");

	g_pWorld->Setup();

	ST_COLLISION_BOX_STICK stBox;

	stBox.vHalfSize = D3DXVECTOR3(200, 0, 200);
	g_pWorld->CreateCollisionBox(stBox);

	stBox.vHalfSize = D3DXVECTOR3(200, 200, 0);
	D3DXMatrixTranslation(&stBox.matOffset, 0, 200, 200);
	g_pWorld->CreateCollisionBox(stBox);

	stBox.vHalfSize = D3DXVECTOR3(200, 200, 0);
	D3DXMatrixTranslation(&stBox.matOffset, 0, 200,-200);
	g_pWorld->CreateCollisionBox(stBox);

	stBox.vHalfSize = D3DXVECTOR3(0, 200, 200);
	D3DXMatrixTranslation(&stBox.matOffset, 200, 200, 0);
	g_pWorld->CreateCollisionBox(stBox);

	stBox.vHalfSize = D3DXVECTOR3(0, 200, 200);
	D3DXMatrixTranslation(&stBox.matOffset, -200, 200, 0);
	g_pWorld->CreateCollisionBox(stBox);
}

void cBattleRoomScene::Release()
{
}

void cBattleRoomScene::Update()
{
	g_pTimeManager->Update();
	g_pCamera->Update();
	g_pWorld->Update();
	g_pInput->Update();
}

void cBattleRoomScene::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	

	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, &m_vecWorldGrid[0], sizeof(ST_PT_VERTEX));
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	g_pWorld->Render();
}

void cBattleRoomScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
