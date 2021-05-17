#pragma once
#include "cCreature.h"

class cObj_Sendbag :
	public cStructure
{
	D3DXCOLOR	m_color;

public:
	cObj_Sendbag();
	~cObj_Sendbag();

	void Setup();
	void Update();
	void Render();

	virtual void Damaged(float fDamege, cGameObject* pAttacker, bool isSmash);
};

