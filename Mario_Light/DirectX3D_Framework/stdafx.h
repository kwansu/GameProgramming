// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include <d3dx9.h>
#include <assert.h>
#include <vector>
#include "Resource.h"
using namespace std;

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")


// ��ũ��:
#define SAFE_RELEASE(p)		{if(p) (p)->Release(); (p) = NULL;}
#define SAFE_DELETE(p)		{if(p) delete (p); (p) = NULL;}
#define SINGLETONE(class_name) private:\
	class_name(void);\
public:\
	~class_name(void);\
	static class_name* GetInstance()\
{\
	static class_name instance;\
	return &instance;\
}
#define MAX(r, l)	(((r) > (l)) ? r : l)
#define MIN(r, l)	(((r) < (l)) ? r : l)

// ��� �� ������:
#define pDevice			LPDIRECT3DDEVICE9
#define cMatrixA		D3DXMATRIXA16
#define cVec3			D3DXVECTOR3
#define cVec2			D3DXVECTOR2
#define xColor			D3DCOLOR
#define pTexture		LPDIRECT3DTEXTURE9
#define stMaterial		D3DMATERIAL9
#define stLight			D3DLIGHT9
#define	pTexture		LPDIRECT3DTEXTURE9


// ���� �߰� ���:
#include "stVertex.h"
#include "cDevice.h"
#include "cGraphics.h"
#include "cInput.h"
#include "cTime.h"


// �ܺ� ���� ����:
extern HWND					g_hWnd;
extern HINSTANCE			g_hInsg;
extern HWND					g_hDlg;
