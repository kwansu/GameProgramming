// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "Resource.h"
#include <assert.h>
#include <d3dx9.h>
#include <vector>
#include <math.h>
using namespace std;

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")


// 매크로:
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


// 상수 및 재정의:
#define pDDevice		LPDIRECT3DDEVICE9
#define cMatrixA		D3DXMATRIXA16
#define cVec3			D3DXVECTOR3
#define cVec2			D3DXVECTOR2
#define xColor			D3DCOLOR
#define pTexture		LPDIRECT3DTEXTURE9


// 후입 추가 헤더:
#include "cDeviceManager.h"
#include "cInput.h"
#include "cGraphics.h"


// 외부 전역 변수:
extern int					g_nStage;
extern bool					g_bCollision;
extern HWND					g_hWnd;
extern HINSTANCE			g_hInsg;
extern cInput*				g_pInput;
extern DWORD				g_tCurrentTime;
extern LPDIRECT3DDEVICE9	g_pDDevice;

