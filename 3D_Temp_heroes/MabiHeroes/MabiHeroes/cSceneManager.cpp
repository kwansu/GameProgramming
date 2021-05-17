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

	//바꾸지 못하면 false 
	if (mapIter == m_SceneDirectory.end()) return E_FAIL;

	//바꿀 신이 현재씬이면 이상없음 리턴
	if (mapIter->second == g_pCurrentScene) return S_OK;

	//변경되는 씬을 초기화
	mapIter->second->Setup();
		//기존의 씬이 있으면 그 씬을 해제해준다
	if (g_pCurrentScene) g_pCurrentScene->Release();
	g_pCurrentScene = mapIter->second;

	return S_OK;
}

HRESULT cSceneManager::ChangeScene(string sceneName, string loadingSceneName)
{
	//바꾸려하는 씬을 찾는다
	mapSceneIter mapIter = m_SceneDirectory.find(sceneName);

	//바꾸지 못하면 false 
	if (mapIter == m_SceneDirectory.end()) return E_FAIL;

	//바꿀 신이 현재씬이면 이상없음 리턴
	if (mapIter->second == g_pCurrentScene) return S_OK;

	//바꾸려 하는 씬을 찾는다
	mapSceneIter findLoading = m_SceneDirectory.find(loadingSceneName);

	//변경되는 씬을 초기화
	mapIter->second->Setup();

	//기존의 씬이 있으면 그 씬을 해제해준다
	if (g_pCurrentScene) g_pCurrentScene->Release();

	//바뀌기 전 로딩씬 보여줌
	g_pLoadingScene = findLoading->second;

	//로딩 끝난 후 변경될 씬 셋팅
	g_pReadyScene = mapIter->second;

	//로딩 씬(쓰레드 호출)
	CloseHandle(CreateThread(NULL, 0, loadingThread, NULL, 0, &m_LoadThreadID));

	return S_OK;
}

void cSceneManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (g_pCurrentScene) g_pCurrentScene->WndProc(g_hWnd, message, wParam, lParam);
}