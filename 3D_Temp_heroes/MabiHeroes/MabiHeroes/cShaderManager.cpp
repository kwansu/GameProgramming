#include "stdafx.h"
#include "cShaderManager.h"


LPD3DXEFFECT g_pNormalEffect = NULL;
LPD3DXEFFECT g_pDiffuseEffect = NULL;

cShaderManager::cShaderManager()
{
}


cShaderManager::~cShaderManager()
{
}

void cShaderManager::Setup()
{
	m_pEffectDiffuse = LoadEffect("DiffuseTexture.fx");
	m_pEffectNormal = LoadEffect("MultiLight.hpp");
}

LPD3DXEFFECT cShaderManager::GetNormalEffect()
{
	return m_pEffectNormal;
}

LPD3DXEFFECT cShaderManager::GetDiffuseEffect()
{
	return m_pEffectDiffuse;
}

LPD3DXEFFECT cShaderManager::LoadEffect(const char * szFileName)
{
	LPD3DXEFFECT pEffect = NULL;

	D3DXMACRO mac[2] =
	{
		{ "MATRIX_PALETTE_SIZE_DEFAULT", "35" },
		{ NULL,                          NULL }
	};

	D3DCAPS9 caps;
	D3DXMACRO *pmac = NULL;
	g_pD3DDevice->GetDeviceCaps(&caps);
	if (caps.VertexShaderVersion > D3DVS_VERSION(1, 1))
		pmac = mac;

	DWORD dwShaderFlags = 0;

#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DXSHADER_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

#ifdef DEBUG_VS
	dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
#endif
#ifdef DEBUG_PS
	dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
#endif

	ID3DXBuffer* pBuffer = NULL;
	if (FAILED(D3DXCreateEffectFromFile(g_pD3DDevice,
		szFileName,
		pmac,
		NULL,
		dwShaderFlags,
		NULL,
		&pEffect,
		&pBuffer)))
	{
		// if creation fails, and debug information has been returned, output debug info
		if (pBuffer)
		{
			OutputDebugStringA((char*)pBuffer->GetBufferPointer());
			SAFE_RELEASE(pBuffer);
			assert(false, "effect load failed");
		}

		return NULL;
	}

	return pEffect;
}
