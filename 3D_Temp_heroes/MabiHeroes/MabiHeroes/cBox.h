#pragma once
#include "cStructure.h"
class cBox :
	public cStructure
{
protected:
	LPD3DXMESH			m_pMesh;
	LPDIRECT3DTEXTURE9	m_pTexture;
	D3DMATERIAL9		m_mtl;

public:
	cBox();
	~cBox();

	void Setup()	override;
	void Update()	override;
	void Render()	override;
	void SaveData(OUT ofstream& outFile) override;
};

