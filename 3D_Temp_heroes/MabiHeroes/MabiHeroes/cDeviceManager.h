#pragma once

#define g_pDeviceManager cDeviceManager::GetInstance()

class cDeviceManager
{
	SINGLETON(cDeviceManager);

private:
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pD3DDevice;

public:
	LPDIRECT3DDEVICE9 GetDevice();
};

extern LPDIRECT3DDEVICE9 g_pD3DDevice;