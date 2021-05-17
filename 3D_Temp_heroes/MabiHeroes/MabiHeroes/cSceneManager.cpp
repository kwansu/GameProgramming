#include "stdafx.h"
#include "cSceneManager.h"
#include "cGameNode.h"

DWORD CALLBACK loadingThread(LPVOID prc)
{
	cSceneManager::g_pReadyScene->Setup();
	cSceneManager::g_pCurrentScene = cSceneManager::g_pReadyScene;

	cSceneManager::g_pLoadingScene->Release();
	cSceneManager::g_pLoadingScene = NULL;
	cSceneManager::g_pReadyScene = NULL;

	return 0;
}

cGameNode* cSceneManager::g_pCurrentScene = NULL;
cGameNode* cSceneManager::g_pLoadingScene = NULL;
cGameNode* cSceneManager::g_pReadyScene = NULL;

cSceneManager::cSceneManager()
{
}


cSceneManager::~cSceneManager()
{
}

HRESULT cSceneManager::Setup()
{
	g_pCurrentScene = NULL;
	g_pLoadingScene = NULL;
	g_pReadyScene = NULL;

	return S_OK;
}

void cSceneManager::Release()
{
	mapSceneIter mapIter = m_SceneDirectory.begin();

	for (; mapIter != m_SceneDirectory.end();)
	{
		if (mapIter->second != NULL)
		{
			if (mapIter->second == g_pCurrentScene) mapIter->second->Release();
			SAFE_DELETE(mapIter->second);
			mapIter = m_SceneDirectory.erase(mapIter);
		}
		else
		{
			++mapIter;
		}
	}
	m_SceneDirectory.clear();
}

void cSceneManager::Update()
{
	if (g_pCurrentScene) g_pCurrentScene->Update();
}

void cSceneManager::Render(void)
{
	if (g_pCurrentScene) g_pCurrentScene->Render();
}


cGameNode* cSceneManager::AddScene(string sceneName, cGameNode* scene)
{
	if (!scene) return NULL;

	m_SceneDirectory.insert(make_pair(sceneName, scene));

	return scene;
}

cGameNode* cSceneManager::AddLoadingScene(string loadingSceneName, cGameNode* scene)
{
	if (!scene) return NULL;

	m_SceneDirectory.insert(make_pair(loadingSceneName, scene));

	return scene;
}

HRESULT cSceneManager::ChangeScene(string sceneName)
{
	mapSceneIter mapIter = m_SceneDirectory.find(sceneName);

	//�ٲ��� ���ϸ� false 
	if (mapIter == m_SceneDirectory.end()) return E_FAIL;

	//�ٲ� ���� ������̸� �̻���� ����
	if (mapIter->second == g_pCurrentScene) return S_OK;

	//����Ǵ� ���� �ʱ�ȭ
	mapIter->second->Setup();
		//������ ���� ������ �� ���� �������ش�
	if (g_pCurrentScene) g_pCurrentScene->Release();
	g_pCurrentScene = mapIter->second;

	return S_OK;
}

HRESULT cSceneManager::ChangeScene(string sceneName, string loadingSceneName)
{
	//�ٲٷ��ϴ� ���� ã�´�
	mapSceneIter mapIter = m_SceneDirectory.find(sceneName);

	//�ٲ��� ���ϸ� false 
	if (mapIter == m_SceneDirectory.end()) return E_FAIL;

	//�ٲ� ���� ������̸� �̻���� ����
	if (mapIter->second == g_pCurrentScene) return S_OK;

	//�ٲٷ� �ϴ� ���� ã�´�
	mapSceneIter findLoading = m_SceneDirectory.find(loadingSceneName);

	//����Ǵ� ���� �ʱ�ȭ
	mapIter->second->Setup();

	//������ ���� ������ �� ���� �������ش�
	if (g_pCurrentScene) g_pCurrentScene->Release();

	//�ٲ�� �� �ε��� ������
	g_pLoadingScene = findLoading->second;

	//�ε� ���� �� ����� �� ����
	g_pReadyScene = mapIter->second;

	//�ε� ��(������ ȣ��)
	CloseHandle(CreateThread(NULL, 0, loadingThread, NULL, 0, &m_LoadThreadID));

	return S_OK;
}

void cSceneManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (g_pCurrentScene) g_pCurrentScene->WndProc(g_hWnd, message, wParam, lParam);
}