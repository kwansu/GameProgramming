#pragma once
#include "cUI.h"

class cQuickSlot : public cUI
{
private:
	LPDIRECT3DTEXTURE9 m_pTexQuickSlot;

public:
	cQuickSlot();
	~cQuickSlot();

	void Setup();
	void Update();
	void Render(int xLeft, int yTop/*, D3DXMATRIXA16* matW*/);
};

