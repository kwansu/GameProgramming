#include "stdafx.h"
#include "cDevice.h"


cDevice::cDevice()
	: m_pD3D(NULL), m_pDDevice(NULL)
{
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9	stCaps;
	int			nVertexProcessing;
	m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &stCaps);

	if (stCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		nVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		nVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS	stD3DPP;
	ZeroMemory(&stD3DPP, sizeof(D3DPRESENT_PARAMETERS));
	stD3DPP.AutoDepthStencilFormat = D3DFMT_D16;
	stD3DPP.BackBufferFormat = D3DFMT_UNKNOWN;
	stD3DPP.EnableAutoDepthStencil = TRUE;
	stD3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	stD3DPP.Windowed = TRUE;

	m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		g_hWnd, nVertexProcessing, &stD3DPP, &m_pDDevice);

	//g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
}


cDevice::~cDevice()
{
}


LPDIRECT3DDEVICE9 cDevice::GetDevice()
{
	return m_pDDevice;
}


void cDevice::Release()
{
	SAFE_RELEASE(m_pD3D);
	ULONG ul = m_pDDevice->Release();
	assert(ul == 0 && "디바이스를 이용하여 생성된 객채 중 해제되지 않은 자원이 있습니다.");
}
