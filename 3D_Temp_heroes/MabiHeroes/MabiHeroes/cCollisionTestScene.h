#pragma once
#include "cGameNode.h"
#include "cWorld.h"

class cCollisionTestScene :
	public cGameNode
{
private:
	cGrid*			m_pGrid;

public:
	cCollisionTestScene();
	~cCollisionTestScene();

	// GameNode override
	void Setup()	override;
	void Release()	override;
	void Update()	override;
	void Render()	override;
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

