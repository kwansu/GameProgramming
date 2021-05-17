#pragma once

class cPyramid
{
private:
	
	D3DXVECTOR3					m_vDirection;
	D3DXVECTOR3					m_vPosition;
	D3DXMATRIXA16				m_matWorld;
	D3DMATERIAL9				m_stMtl;
	D3DMATERIAL9				m_stMtl2;
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	int							m_nNumTri;
	bool						m_isPicked;
public:
	cPyramid(void);
	~cPyramid(void);
	
	void Setup(D3DXCOLOR c, D3DXMATRIXA16* pmat = NULL);

	// cGameObject override
	void Update();
	void Render();
	void Render(const D3DXMATRIXA16* pmatWorld);

	bool IsPick(const ST_RAY& rayMouse);
};

