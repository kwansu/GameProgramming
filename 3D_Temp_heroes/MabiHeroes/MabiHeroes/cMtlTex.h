#pragma once
class cMtlTex
{
protected:
	//SYNTHESIZE(D3DMATERIAL9, m_stMtl, Mtl);
	LPDIRECT3DTEXTURE9	m_pTexture;
	int					m_nMtlRef;

public:
	D3DMATERIAL9 m_stMtl;

public:
	cMtlTex(void);
	~cMtlTex(void);
	void SetTexture(LPDIRECT3DTEXTURE9 txture) { m_pTexture = txture; }
	LPDIRECT3DTEXTURE9 GetTexture() { return m_pTexture; }

	void SetMtlRef(int n) { m_nMtlRef = n; }
	int GetMtlRef() { return m_nMtlRef; }


};

