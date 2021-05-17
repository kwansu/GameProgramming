#pragma once

#define g_pDevice cDevice::GetInstance()->GetDevice()

class cDevice
{
	SINGLETONE(cDevice);

private:
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pDDevice;

public:
	LPDIRECT3DDEVICE9 GetDevice();
	void Release();
};

