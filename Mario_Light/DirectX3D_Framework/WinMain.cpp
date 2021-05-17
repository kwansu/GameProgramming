// DirectX3D_Framework.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "cMainGame.h"

#define MAX_LOADSTRING 100

// 전역 변수:
cMainGame*		g_pGame;
HWND			g_hWnd;
HINSTANCE		g_hInst;
HWND			g_hDlg = NULL;
TCHAR			szTitle[MAX_LOADSTRING];
TCHAR			szWindowClass[MAX_LOADSTRING];


ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL	CALLBACK	DlgProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	MSG msg;

	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DIRECTX3D_FRAMEWORK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance (hInstance, nCmdShow))
		return FALSE;

	// 전역 객체 생성 및 초기화.
	g_pGame = new cMainGame;
	g_pGame->Initialize();

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		g_pGame->Run();
	}

	// 전역 객체 소멸 및 메모리해체.
	g_pGame->Release();
	delete g_pGame;

	return (int) msg.wParam;
}



ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DIRECTX3D_FRAMEWORK));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_DIRECTX3D_FRAMEWORK);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   g_hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	if (g_pGame)
		g_pGame->MessageHandler(message, wParam, lParam);

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		if (wmId == IDM_ABOUT)
		{
			if (!g_hDlg)
			{
				g_hDlg = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_MAPTOOL)
					, g_hWnd, DlgProc);
				ShowWindow(g_hDlg, SW_SHOW);
			}
		}
		return 0;
	case WVR_REDRAW:
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	
	return DefWindowProc(hWnd, message, wParam, lParam);
}


BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wp, LPARAM lp)
{
	g_pGame->DialogHandler(hDlg, iMsg, wp, lp);
	DefWindowProc(hDlg, iMsg, wp, lp);
	return true;
}

