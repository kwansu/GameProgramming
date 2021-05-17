#pragma once
#include "cCamera.h"
#include "cGrid.h"

class cGameNode
{
private:
	HDC		_hdc;

public:
	cGameNode();
	virtual ~cGameNode();

	virtual void Setup();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

