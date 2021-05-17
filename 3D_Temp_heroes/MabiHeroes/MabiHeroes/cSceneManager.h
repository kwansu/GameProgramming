#pragma once

#define g_pSceneManager cSceneManager::GetInstance()

class cGameNode;

class cSceneManager
{
	SINGLETON(cSceneManager);

public:
	typedef map<string, cGameNode*> mapSceneList;
	typedef map<string, cGameNode*>::iterator mapSceneIter;

private:
	static cGameNode* g_pCurrentScene;
	static cGameNode* g_pLoadingScene;
	static cGameNode* g_pReadyScene;

	mapSceneList m_SceneDirectory;
	mapSceneList m_LoadingSceneDirectory;

	DWORD m_LoadThreadID;

public:

	HRESULT Setup();
	void Release();
	void Update();
	void Render();

	cGameNode* AddScene(string sceneName, cGameNode* scene);
	cGameNode* AddLoadingScene(string loadingSceneName, cGameNode* scene);
	HRESULT ChangeScene(string scenename);
	HRESULT ChangeScene(string scenename, string loadingSceneName);

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	friend DWORD CALLBACK loadingThread(LPVOID prc);
};

