// Bricks.cpp : Defines the entry point for the application.
//
/************************************************************************/
/*	����Ŀ�ģ�C�����еĺ���
	�����ܣ���ש�顣��ҿ���һ��ש������Ļ���ƶ�,ϵͳ�����λ�����ɲ�ͬ��ɫ��ש��
		Ҫ����ҿ��Ƶ�ש�龡���ƶ���ϵͳ���ɵ�ש�鴦,�÷�.
	�����߸Ľ�:�޸�Ϊ̰ʳ�ߵĲ���ģʽ
	��д�ߣ������ף�hanhonglei@sina.com��*/
/************************************************************************/

#include "stdafx.h"
#include "Bricks.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name


// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

//////////////////////////////////////////////////////////////////////////
// �û��Զ���ĺ���
// �ڴ��ڷ�Χ���������һ��λ��
int RandPos()
{
	return rand()%501;
}
// ��ָ��λ�û���һ������
// @hdc �����豸���
// @x y ����λ��
// @s �����С
// @bPlayer ����Ƿ�����ҷ���
void DrawBrick(HDC hdc, int x, int y, int s, int bPlayer)
{
	HBRUSH brush;
	brush=bPlayer?CreateSolidBrush(RGB(255,0,0)):CreateSolidBrush(RGB(0,255,0));
	//SelectObject(hdc, brush);
	//Rectangle(hdc,x-size/2,y-size/2,x+size/2,y+size/2);
	RECT rc;
	rc.top = y-s/2;
	rc.left = x-s/2;
	rc.bottom = y+s/2;
	rc.right = x+s/2;
	FillRect(hdc, &rc, brush);

	DeleteObject(brush);
}
// �ж�����ͬ����С�ķ����Ƿ��ڿռ������ص�
// @�����ֱ������������λ���Լ���С
int IsCollider(int x1, int y1, int x2, int y2, int s)
{
	if (x1+s < x2 || x1-s > x2)
		return 0;
	if (y1+s < y2 || y1-s > y2)
		return 0;
	return 1;
}
//////////////////////////////////////////////////////////////////////////
// ȫ�ֱ���
int xP=RandPos(), yP=RandPos(), xE=RandPos(), yE=RandPos();	// �������λ�ú���,���������Һ͵��˵�λ��
const int size = 20;				// ש���С
int score = 0;						// ��¼��ҵ÷�

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_BRICKS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BRICKS));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BRICKS));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_BRICKS);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_KEYDOWN:
		InvalidateRect(hWnd, NULL, TRUE);	// �ô��ڱ�Ϊ��Ч,�Ӷ������ػ���Ϣ
		switch(wParam)						// �û��������ǽ������������ƶ�
		{
		case VK_LEFT:						
			xP -= xP<0?0:10;
			break;
		case VK_RIGHT:
			xP += xP>500?0:10;
			break;
		case VK_UP:
			yP -= yP<0?0:10;
			break;
		case VK_DOWN:
			yP += yP>500?0:10;
			break;
		}
		if (IsCollider(xP, yP, xE, yE, size))	// ������Ǻ͵���λ�ó�ͻ,��÷�,�����·������λ��
		{
			score++;
			xE = RandPos(), yE = RandPos();
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		WCHAR str[16];
		swprintf(str, L"��ĵ÷֣�%d", score);	// ��Ļ����÷�
		TextOut(hdc, 0, 0, str, wcslen(str));
		DrawBrick(hdc, xE, yE, size, 0);		// ���Ƶ��˺���ҽ�ɫ
		DrawBrick(hdc, xP, yP, size, 1);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
