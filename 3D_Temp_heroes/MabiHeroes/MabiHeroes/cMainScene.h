#pragma once
#include "cGameNode.h"

class cCamera;
class cGrid;
class cSkinnedMesh;


class cMainScene : public cGameNode
{
private:
	cGrid*			m_pGrid;

public:
	cMainScene();
	~cMainScene();

	void Setup();
	void Render();
	void Update();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

