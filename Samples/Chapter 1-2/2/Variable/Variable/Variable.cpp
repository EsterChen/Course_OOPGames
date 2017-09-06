// Variable.cpp : Defines the entry point for the application.
//
/************************************************************************/
/*	����Ŀ�ģ�C���Ը��ֱ�����ʹ��
	�����ܣ�����ĸ��Ϸ�������3����������Ļ���ϳ����������ĸҪ����Ҿ�����ȷ���롣
		���������ȷ����1�֣������һ��������������Ϊ0ʱ��������Ϸ��������ҵ�ƽ�������ٶȡ�
	�����߸Ľ�:�޸�������ֵĴ�С����Ҫ���û��ڹ涨ʱ�������ÿ����ĸ�����룬�����������
	��д�ߣ������ף�hanhonglei@sina.com��*/
/************************************************************************/

#include "stdafx.h"
#include "Variable.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
// ȫ�ֱ���
COLORREF color = RGB(255, 0, 0);				// ������ɫΪ��ɫ
int health = 3;									// �����������
int score = 0;									// ��ҵ÷�
unsigned long times = 0;						// ��Ϸ����ʱ��
char c;											// ���������ĸ
WCHAR str[64];									// ����ַ�����ʹ����չ���ַ��洢��ʽ���������ڹ��ʻ����ִ洢��
char hit;										// ��ǰ�û��İ�����ĸ

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	c = 'A'+rand()%26;			// �������һ���µĴ�������ĸ
	times = GetTickCount();		// �õ���������ʱ��ʱ�䣨���룩

	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_VARIABLE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VARIABLE));
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VARIABLE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_VARIABLE);
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
	case WM_LBUTTONDOWN:					// ������������Ϣ
		color = RGB(255, 0, 0);				// ��������ɫ�任Ϊ��ɫ
		InvalidateRect(hWnd, NULL, TRUE);	// �����ػ���Ϣ
		break; 
	case WM_RBUTTONDOWN:					// ����Ҽ�������Ϣ
		color = RGB(0, 0, 255);				// ��������ɫ�任Ϊ��ɫ
		InvalidateRect(hWnd, NULL, TRUE);	// �����ػ���Ϣ
		break; 
	case WM_KEYDOWN:						// ���̰�����Ϣ
		if (health <= 0)					// ���������ľ�,�򲻴��������Ϣ
			break;
		 hit = wParam;						// �õ���ǰ�û��İ���
		 if (hit == c)						// �������ȷ�İ���
		 {
			 c = 'A'+ rand()%26;			// �������һ���µĴ�������ĸ
			 score = score + 1;				// �÷ּ�1
		 }
		 else								// ����,����������
		 {
			health = health - 1;
			if (health <= 0)				// ���������ľ�,������ܺ�ʱ
				times = GetTickCount() - times;
		 }
		 InvalidateRect(hWnd, NULL, TRUE);	// �ػ���Ļ
		break; 
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		SetTextColor(hdc, color);			// �趨������ɫ
		TextOut(hdc, 0, 0, L"��������ȷ����ĸ!", 9);
		swprintf(str, L"��������%d", health);	// �����������Ϣ��ʽ���洢���ַ�����
		TextOut(hdc, 200, 0, str, wcslen(str));	// �����Ϸ��Ϣ

		swprintf(str, L"�÷֣�%d", score);	// �����������Ϣ��ʽ���洢���ַ�����
		TextOut(hdc, 400, 0, str, wcslen(str));	// �����Ϸ��Ϣ

		if (health <= 0)					// ��Ϸ������Ϣ
		{
			swprintf(str, L"��Ϸ����,�����ٶ�: %.2f ��ÿ��", float(score*1000)/times);
		}
		else
			swprintf(str, L"%c", c);		// ��ǰ��������ַ�
		TextOut(hdc, 20, 40, str, wcslen(str));

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
