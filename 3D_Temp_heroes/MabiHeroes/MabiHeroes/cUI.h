#pragma once
#include "cTransform.h"

#define MAX_HP			2850
#define MAX_STAMINA		780

class cUI : public cTransform
{
private:

protected:
	//D3DXMATRIXA16		m_matT;
	//D3DXMATRIXA16		m_matR;
	//D3DXMATRIXA16		m_matWorld

	//D3DXVECTOR3		m_vPos;\

	D3DXMATRIXA16		m_mScale;
	
	D3DXIMAGE_INFO		m_stII;\

	D3DXVECTOR3			m_vecScale;

	LPD3DXSPRITE		m_pD3DSprite;

	int*				m_pHp;
	int*				m_pStamina;

public:
	cUI();
	~cUI();

	virtual void Setup(char* szFile) {}
	virtual void Update() {}
	virtual void Render(int xLeft, int yTop/*, D3DXMATRIXA16* matW*/) {}

	void SetHp(int* pHp) { m_pHp = pHp; }
	void SetStamina(int* pStamina) { m_pStamina = pStamina; }
};

