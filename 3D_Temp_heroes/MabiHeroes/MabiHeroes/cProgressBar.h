#pragma once
#include "cUI.h"
//#include "cUIText.h"

class cProgressBar : public cUI
{
private:
	//cUIText*				m_pUIText;

	RECT					m_stRc;
	LPDIRECT3DTEXTURE9		m_pTexHp;
	LPDIRECT3DTEXTURE9		m_pTexHpBack;

	LPDIRECT3DTEXTURE9		m_pTexStm;
	LPDIRECT3DTEXTURE9		m_pTexStmBack;

public:
	cProgressBar();
	~cProgressBar();

	void Setup();
	void Update();
	void Render(int xLeft, int yTop/*, D3DXMATRIXA16* matW*/);
};