// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// #pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")


// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <assert.h>
#include <vector>
#include <stack>
#include <string>
#include <map>
#include <set>
#include <list>
#include <d3dx9.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

extern HWND		g_hWnd;
extern float	g_fDeltaTime;


// ���� ����ü �� ��ũ��
#define EPSILON 0.0001f

#define SAFE_RELEASE(p) {if(p){(p)->Release(); (p) = NULL;}}
#define SAFE_ADD_REF(p) {if(p){(p)->AddRef();}}
#define SAFE_DELETE(p) {if(p){delete (p); (p) = NULL;}}

#define SAFE_DELETE_ARRAY(p) {if(p) { delete[](p); (p) = NULL;}}


#define SINGLETON(class_name) private:\
	class_name(void);\
public:\
	~class_name(void);\
	static class_name* GetInstance()\
{\
	static class_name instance;\
	return &instance;\
}

// ���� ����ü
#include "stdStruct.h"

struct ST_PC_VERTEX;
struct ST_PN_VERTEX;
struct ST_PNT_VERTEX;
struct ST_PT_VERTEX;
struct ST_RHWC_VERTEX;
struct ST_POS_SAMPLE;
struct ST_ROT_SAMPLE;
struct ST_SIZEF;
struct ST_RAY;
struct ST_PLANE;
struct ST_SPHERE;
struct ST_COLLISION_SPHERE;
struct ST_COLLISION_BOX_STICK;
struct ST_MISILE;


// ���� �Լ� �� ���� ��ƿ��Ƽ
#include "SKS_Utility.h"


// TODO: �������������߰� �� ����� �� ������. �����������
#include "soundManager.h"
#include "cDeviceManager.h"
#include "cCamera.h"
#include "cInputManager.h"
#include "cTextureManager.h"
#include "cTimeManager.h"
#include "cObjectManager.h"
#include "cUIManager.h"
#include "cSceneManager.h"
#include "cLIghtManager.h"
#include "cShaderManager.h"
#include "cIniData.h"

#include "cGameObject.h"
#include "cKeyManager.h"
#include "cSceneManager.h"
#include "cCollisionRender.h"
#include "cWorld.h"
#include "cEffectManager.h"

const string space = " ";
const string underbar = "_";
const string dash = "-";
const string sharp = "#";
const string enter = "\n";
const string plus = "+";


// Colors
const D3DCOLOR pastelPink = D3DCOLOR_XRGB(253, 198, 205);
const D3DCOLOR pastelPurple = D3DCOLOR_XRGB(223, 193, 253);
const D3DCOLOR pastelBlue = D3DCOLOR_XRGB(194, 220, 252);
const D3DCOLOR pastelMint = D3DCOLOR_XRGB(174, 251, 213);
const D3DCOLOR pastelYellow = D3DCOLOR_XRGB(248, 252, 173);
const D3DCOLOR pastelOrange = D3DCOLOR_XRGB(255, 205, 151);

const D3DCOLOR darkPink = D3DCOLOR_XRGB(247, 62, 80);
const D3DCOLOR darkPurple = D3DCOLOR_XRGB(101, 43, 208);
const D3DCOLOR darkBlue = D3DCOLOR_XRGB(53, 125, 198);
const D3DCOLOR darkMint = D3DCOLOR_XRGB(52, 175, 135);
const D3DCOLOR darkYellow = D3DCOLOR_XRGB(227, 205, 49);
const D3DCOLOR darkOrange = D3DCOLOR_XRGB(226, 123, 39);

const D3DCOLOR skinLight = D3DCOLOR_XRGB(254, 218, 188);
const D3DCOLOR cream = D3DCOLOR_XRGB(240, 231, 217);
const D3DCOLOR black = D3DCOLOR_XRGB(0, 0, 0);
const D3DCOLOR white = D3DCOLOR_XRGB(255, 255, 255);
const D3DCOLOR gray = D3DCOLOR_XRGB(107, 100, 95);
