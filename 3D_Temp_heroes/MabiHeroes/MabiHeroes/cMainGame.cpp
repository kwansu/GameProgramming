#include "StdAfx.h"
#include "cMainGame.h"
#include "cEffectFactoryScene.h"


cMainGame::cMainGame(void)
{


}

cMainGame::~cMainGame(void)
{
}

void cMainGame::Setup()
{
	
	
	// 전역 객체 초기화
	g_pD3DDevice = cDeviceManager::GetInstance()->GetDevice();
	g_pCamera = cCamera::GetInstance();
	g_pCamera->Setup();
	g_pWorld = cWorld::GetInstance();
	g_pCollisionRender->Setup();

	cShaderManager* pSM = cShaderManager::GetInstance();
	pSM->Setup();
	g_pNormalEffect = pSM->GetNormalEffect();
	g_pDiffuseEffect = pSM->GetNormalEffect();
	
	cGameNode::Setup();

	// 헤더와 여기에 씬만 추가하고
	g_pSceneManager->AddScene("sceneMonsterTest", m_pSceneMonsterTest = new cMonsterTestScene);
	g_pSceneManager->AddScene("sceneMain", m_pSceneMain = new cMainScene);
	g_pSceneManager->AddScene("sceneCollisionTest", m_pSceneMain = new cCollisionTestScene);
	g_pSceneManager->AddScene("sceneEditMode", m_pSceneMain = new cEditScene);
	g_pSceneManager->AddScene("sceneBattleRoom", m_pSceneMain = new cBattleRoomScene);
	g_pSceneManager->AddScene("sceneEffectFactory", m_pSceneMain = new cEffectFactoryScene);
	
	// 여기서 씬 바꾸시면 돼겠습니다~
	g_pSceneManager->ChangeScene("sceneMain");

	g_pSoundManager->addSound("한숨", "./3dObject/Sound/LEE HI_한숨.mp3", true, true);

	// 임시 라이트 생성
	m_lightDirection.Type = D3DLIGHT_DIRECTIONAL;
	m_lightDirection.Diffuse = m_lightDirection.Ambient = D3DXCOLOR(1, 1, 1, 1);
	m_lightDirection.Direction = D3DXVECTOR3(-1, -1, -1);

	g_pD3DDevice->SetLight(1, &m_lightDirection);
	g_pD3DDevice->LightEnable(1, true);
	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);

	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
}

void cMainGame::Release()
{
	cGameNode::Release();
}

void cMainGame::Update()
{
	cGameNode::Update();
	g_pSceneManager->Update();

	if (g_pKeyManager->IsStayKeyDown(VK_CONTROL))
	{
		if (g_pKeyManager->IsOnceKeyDown('O'))
			g_pSceneManager->ChangeScene("sceneMonsterTest");

		if (g_pKeyManager->IsOnceKeyDown('P'))
			g_pSceneManager->ChangeScene("sceneMain");

		if (g_pKeyManager->IsOnceKeyDown('C'))
			g_pSceneManager->ChangeScene("sceneCollisionTest");

		if (g_pKeyManager->IsOnceKeyDown('V'))
			g_pSceneManager->ChangeScene("sceneBattleRoom");

		if (g_pKeyManager->IsOnceKeyDown('X'))
			g_pSceneManager->ChangeScene("sceneEditMode");

		if (g_pKeyManager->IsOnceKeyDown('M'))
			g_pSceneManager->ChangeScene("sceneEffectFactory");
	}

	if (g_pKeyManager->IsOnceKeyDown('P'))
		g_pSoundManager->play("한숨", 0.5f);
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(128, 128, 128),
		1.0f, 0);
	g_pD3DDevice->BeginScene();

	g_pSceneManager->Render();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	g_pSceneManager->WndProc(hWnd, message, wParam, lParam);
}