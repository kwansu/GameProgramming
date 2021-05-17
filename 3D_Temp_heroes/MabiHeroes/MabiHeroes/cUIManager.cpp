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
	//strcpy_s(fd.FaceName, "����ü");	//�۲� ��Ÿ��
	//AddFontResource("umberto.ttf");
	strcpy_s(fd.FaceName, "�ü�ü");
	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFont);
}

void cUIManager::Update()
{
}

const char* szSulmung = " ī�޶� ���� ���     : F \n ī�޶� �߽�ȸ�� ��� : G \n ĳ���� ȸ��          : V \n �ִϸ��̼� ����  :  1 \n ���콺 ���� on/off  :  Enter";

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
