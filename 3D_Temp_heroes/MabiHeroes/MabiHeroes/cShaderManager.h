#pragma once

class cShaderManager
{
	SINGLETON(cShaderManager);

private:
	LPD3DXEFFECT	m_pEffectNormal;
	LPD3DXEFFECT	m_pEffectDiffuse;

public:
	void Setup();
	LPD3DXEFFECT GetNormalEffect();
	LPD3DXEFFECT GetDiffuseEffect();
	
private:
	LPD3DXEFFECT LoadEffect(const char* szFileName);
};

extern LPD3DXEFFECT g_pNormalEffect;
extern LPD3DXEFFECT g_pDiffuseEffect;

