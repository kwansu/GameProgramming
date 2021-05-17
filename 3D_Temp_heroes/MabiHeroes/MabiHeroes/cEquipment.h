#pragma once
#include "cUI.h"

class cObj_Fiona;

struct stItemRc
{
	RECT				rc;
	bool				isClick;
};

class cEquipment : public cUI
{
private:
	cObj_Fiona*			m_pFiona;


	LPDIRECT3DTEXTURE9	m_pTexEquip;
	LPDIRECT3DTEXTURE9	m_pTexEquipCheck;

	LPD3DXMESH			m_pMesh;

	stItemRc			m_stRc[5];

	bool				m_isSwitch;
	bool				m_isOpen;
public:
	cEquipment();
	~cEquipment();

	void Setup();
	void Update();
	void Render(int xLeft, int yTop/*, D3DXMATRIXA16* matW*/);

	void SetFiona(cObj_Fiona*	fiona);

	stItemRc GetStRc() { return m_stRc[5]; }
};

