#include "stdafx.h"
#include "cGameNode.h"


cGameNode::cGameNode()
{
}


cGameNode::~cGameNode()
{
}

void cGameNode::Setup()
{
	g_pSoundManager->init();
}

void cGameNode::Release()
{
	//DC�������ش�
	ReleaseDC(g_hWnd, _hdc);
}
void cGameNode::Update()
{
}
void cGameNode::Render()
{
}

void cGameNode::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_CLOSE)
		PostQuitMessage(0);
}

