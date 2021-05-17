#pragma once

#include "cSkinnedMesh.h"
struct stSwingEffectVec
{
	D3DXVECTOR3		m_vecEffect_Swing_Up, m_vecEffect_Swing_Down;
};
class cWearItem
{
private:
	cSkinnedMesh*	m_pMesh;
	D3DXMATRIXA16*	m_pmatParent;
	D3DXMATRIXA16	m_matR, m_matS, m_matT, m_matWrodl;

	string			m_FileName;
	stSwingEffectVec	m_SwingEffect;
public:
	cWearItem();
	~cWearItem();
	void Setup(string filePath, D3DXMATRIXA16* matParent);
	void Update();
	void Render();
	void Release();

	void SetParent(D3DXMATRIXA16* matParent);
	void SetPosition(int px, int py, int pz);
	stSwingEffectVec GetSwingEffectVec() { return m_SwingEffect; }
};

