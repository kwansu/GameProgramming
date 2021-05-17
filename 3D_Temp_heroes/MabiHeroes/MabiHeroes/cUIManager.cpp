#include "stdafx.h"
#include "cUIManager.h"


cUIManager::cUIManager()
{
}


cUIManager::~cUIManager()
{
}

void cUIManager::Setup()
{
	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 16;
	fd.Width = 8;
	fd.Weight = FW_NORMAL;
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	//strcpy_s(fd.FaceName, "굴림체");	//글꼴 스타일
	//AddFontResource("umberto.ttf");
	strcpy_s(fd.FaceName, "궁서체");
	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFont);
}

void cUIManager::Update()
{
}

const char* szSulmung = " 카메라 날기 모드     : F \n 카메라 중심회전 모드 : G \n 캐릭터 회전          : V \n 애니메이션 변경  :  1 \n 마우스 숨김 on/off  :  Enter";

void cUIManager::Render()
{
	RECT rcBox = { 50, 20, 300, 200 };
	if (m_pFont)
		m_pFont->DrawTextA(NULL,
			szSulmung,
			strlen(szSulmung),
			&rcBox,
			DT_CENTER | DT_VCENTER,
			D3DCOLOR_XRGB(255, 255, 255));
}
