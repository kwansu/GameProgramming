#include "stdafx.h"
#include "cEffectFactoryScene.h"


cEffectFactoryScene::cEffectFactoryScene()
{
}


cEffectFactoryScene::~cEffectFactoryScene()
{
}

void cEffectFactoryScene::Setup()
{
	m_vecWorldGrid.resize(36);

	m_pGrid = new cGrid;
	m_pGrid->Setup(10, 1);

	int i = 0;
	// 바닥
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 0, 200); m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 0, -200); m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 1);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 0, 200); m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 0, 200); m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 0, -200); m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 1);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 0, -200); m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 1);

	// 뒤
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 400, -200);	 m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 400, -200);	 m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 1);
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 0, -200);	 m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 0, -200);	 m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 400, -200);	 m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 1);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 0, -200); 	 m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 1);

	// 앞
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 400, 200);	   m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 0, 200);		   m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 1);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 400, 200);	   m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 400, 200);	   m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 0, 200);		   m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 1);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 0, 200);	   m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 1);

	// 오른쪽
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 400, -200);	 m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 0, -200);	 m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 1);
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 400, 200);	 m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 400, 200);	 m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 0, -200);	 m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 1);
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 0, 200);	 m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 1);

	// 왼쪽
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 400, -200);	  m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 400, 200);	  m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 1);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 0, -200);	  m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 0, -200);	  m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 400, 200);	  m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 1);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 0, 200);	  m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 1);

	// 위
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 400, 200);  m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 400, 200); m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 1);
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 400, -200); m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 400, 200); m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 0);
	m_vecWorldGrid[i].p = D3DXVECTOR3(-200, 400, -200); m_vecWorldGrid[i++].t = D3DXVECTOR2(1, 1);
	m_vecWorldGrid[i].p = D3DXVECTOR3(200, 400, -200); m_vecWorldGrid[i++].t = D3DXVECTOR2(0, 1);

	m_pTexture = g_pTextureManager->GetTexture("./MapData/grid2.jpg");

	g_pEffectManager->Setup();


	// 임시 라이트 생성
	m_lightDirection.Type = D3DLIGHT_DIRECTIONAL;
	m_lightDirection.Diffuse = m_lightDirection.Ambient = D3DXCOLOR(1, 1, 1, 1);
	m_lightDirection.Direction = D3DXVECTOR3(-1, -1, -1);

	g_pD3DDevice->SetLight(1, &m_lightDirection);
	g_pD3DDevice->LightEnable(1, true);
	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
}

void cEffectFactoryScene::Release()
{
}

void cEffectFactoryScene::Update()
{
	g_pTimeManager->Update();

	g_pCamera->Update();
	g_pInput->Update();
	g_pEffectManager->Update();
}

void cEffectFactoryScene::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	m_pGrid->Render();

	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, &m_vecWorldGrid[0], sizeof(ST_PT_VERTEX));
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	g_pEffectManager->Render();


}

void cEffectFactoryScene::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
