#pragma once

#define g_pTextureManager cTextureManager::GetInstance()

class cTextureManager
{
private:
	SINGLETON(cTextureManager);

private:
	std::map<std::string, LPDIRECT3DTEXTURE9>	m_mapTexture;
	std::map<std::string, D3DXIMAGE_INFO>		m_mapImageInfo;

public:
	LPDIRECT3DTEXTURE9 GetTexture(char* szFilename);
	LPDIRECT3DTEXTURE9 GetTexture(std::string sFilename);
	LPDIRECT3DTEXTURE9 GetTexture(char* szFilename, D3DXIMAGE_INFO* pII);
	LPDIRECT3DTEXTURE9 GetTexture(std::string sFilename, D3DXIMAGE_INFO* pII);
	void Destroy();
};

