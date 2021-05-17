#include "StdAfx.h"
#include "cTextureManager.h"


cTextureManager::cTextureManager(void)
{
}


cTextureManager::~cTextureManager(void)
{
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture( char* szFilename )
{
	return GetTexture(std::string(szFilename));
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture( std::string sFilename )
{
	if (m_mapTexture.find(sFilename) == m_mapTexture.end())
	{
		D3DXCreateTextureFromFile(g_pD3DDevice,
			sFilename.c_str(),
			&m_mapTexture[sFilename]);
	}

	LPDIRECT3DTEXTURE9 t = m_mapTexture[sFilename];
	return m_mapTexture[sFilename];
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture( char* szFilename, D3DXIMAGE_INFO* pII )
{
	return GetTexture(std::string(szFilename), pII);
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture( std::string sFilename, D3DXIMAGE_INFO* pII )
{
	if (m_mapTexture.find(sFilename) == m_mapTexture.end() ||
		m_mapImageInfo.find(sFilename) == m_mapImageInfo.end())
	{
		SAFE_RELEASE( m_mapTexture[sFilename]);

		D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			sFilename.c_str(), 
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN, 
			D3DPOOL_MANAGED, 
			D3DX_FILTER_NONE, 
			D3DX_DEFAULT, 
			0,//D3DCOLOR_XRGB(255, 255, 255),
			&m_mapImageInfo[sFilename],
			NULL,
			&m_mapTexture[sFilename] );
	}

	if(pII)
		*pII = m_mapImageInfo[sFilename];

	return m_mapTexture[sFilename];
}

void cTextureManager::Destroy()
{
	for each(auto it in m_mapTexture)
	{
		it.second->Release(); 
	}
}
