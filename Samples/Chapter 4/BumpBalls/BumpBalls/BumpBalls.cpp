// BumpBalls.cpp : Defines the entry point for the application.
//
/************************************************************************/
/*	����Ŀ�ģ�C�����е�ָ�������
	�����ܣ����������ͨ���ո�����Ļ�����������������ٶȵ�С�����ɵ�С����ڴ��ڷ�Χ�ڷ�����ײ
		ʹ�ö�ʱ����ʽ���õ�����Ч����ÿ��һ��ʱ�䴥��һ�ζ�ʱ��������Ȼ�������Ϸ�е�����״̬���Դ˲�������Ч��
	�����߸Ľ�:����ײ������ײ��Ӧ��ʹ�ø����ȶ��Ĳ��ԣ����С��֮��ճ��������
	��д�ߣ������ף�hanhonglei@sina.com��*/
/************************************************************************/

#include "stdafx.h"
#include "BumpBalls.h"
#include <math.h>
#include <time.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

#define BALLS_NUM 64							// ����С������
#define MAX_V 4									// С�������ٶ�
int ballsX[BALLS_NUM], ballsY[BALLS_NUM];		// ���飬����ÿ��С���λ��
int ballsVX[BALLS_NUM], ballsVY[BALLS_NUM];		// ���飬����ÿ��С����ٶ�
COLORREF ballsC[BALLS_NUM];						// ���飬����ÿ��С�����ɫ
int nBalls = 0;									// ��ǰ��С������
int radius = 20;								// С��뾶
int timeStep = 50;								// ��ʱ��ʱ����
int wndWidth = 0;								// ���ڳߴ�
int wndHeight = 0;  
 

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

// �ڴ��������������һ��С��ĺ���
// @n ��ǰС�������,����ָ�뷽ʽ���ݲ���,�����ڿ��Զ�ָ��ָ��ı��������޸�
int GenerateBall(int *n)
{
	if (*n >= BALLS_NUM)			// С���������࣬������							
		return 0;
	ballsX[*n] = wndWidth / 2;		// ����λ��
	ballsY[*n] = wndHeight / 2;
	ballsVX[*n] = MAX_V - 2*(rand() % (MAX_V+1));		// ����ٶ�
	ballsVY[*n] = MAX_V - 2*(rand() % (MAX_V+1));
	ballsC[*n] = RGB(rand()%256, rand()%256,rand()%256);// �����ɫ
	(*n)++;							// �޸Ĳ���ֵ,С��������1
	return 1;
}
// ����С��ĺ���
// @hdc �����豸���
// @n ��ǰ��С������
// @r С��뾶
// @X Y С���λ������
// @C С�����ɫ����
void DrawBalls(HDC hdc, int n, int r, int X[], int Y[],COLORREF C[])
{
	HBRUSH brush;	
	for (int i = 0; i < n; i++)
	{
		brush = CreateSolidBrush(C[i]);		// ʹ�õ�ǰ��ɫ�ı�ˢ����С��
		SelectObject(hdc, brush);			
		Ellipse(hdc, X[i]-r, Y[i]-r, X[i]+r, Y[i]+r);
		DeleteObject(brush);
	}
}
// ������С������ײ��ķ�Ӧ,������ײ����ٶ�
// @v1 v2 �����������С����ٶ�
// @u ����С�����������
int Response(int v1[2], int v2[2], int u[2])
{     
	if (u[0] * u[0] + u[1] * u[1] == 0)					// �����ص��Ļ�����ʱ��������ײ
		return 0;
	int tmp, v11[2], v12[2], v21[2], v22[2];			// �������������Ϻʹ�ֱ�����ߵ��ٶȷ���
	v11[0] = (v1[0] * u[0] + v1[1] * u[1]) * u[0] / (u[0] * u[0] + u[1] * u[1]);
	v11[1] = (v1[0] * u[0] + v1[1] * u[1]) * u[1] / (u[0] * u[0] + u[1] * u[1]);
	v12[0] = v1[0] - v11[0];
	v12[1] = v1[1] - v11[1];
	v21[0] = (v2[0] * u[0] + v2[1] * u[1]) * u[0] / (u[0] * u[0] + u[1] * u[1]);
	v21[1] = (v2[0] * u[0] + v2[1] * u[1]) * u[1] / (u[0] * u[0] + u[1] * u[1]);
	v22[0] = v2[0] - v21[0];
	v22[1] = v2[1] - v21[1];
	// �������������ٶȽ���
	tmp	   = v11[0];
	v11[0] = v21[0];
	v21[0] = tmp;
	tmp	   = v11[1];
	v11[1] = v21[1];
	v21[1] = tmp;
	// �õ��µ��ٶ�
	v1[0]  = v11[0] + v12[0];
	v1[1]  = v11[1] + v12[1];
	v2[0]  = v21[0] + v22[0];
	v2[1]  = v21[1] + v22[1];
	return 1;
}
// ÿһ֡������С����������ײ״̬�޸�С���ٶȣ�������С��λ��
// @n С������
// @r С��뾶
// @X Y С��ǰλ������
// @VX VY С��ǰ�ٶ�����
// @elapseTime ��֮֡���ʱ����
void UpdateBalls(int n, int r, int X[], int Y[], int VX[], int VY[], int elapseTime)
{
	if(n > BALLS_NUM)
		return;
	for (int i = 0; i < n; i++)
	{
		for (int j = i+1; j < n; j++)
		{
			int v1xy[2], v2xy[2], u[2];			// ����С��ĳ��ٶȺ���ײ��������
			// 1 С���Ƿ����໥��ײ
			// Ŀǰ����ײ���ͷ�Ӧ��ֻ����򵥵ļ��㷽��,��������µ�����:
			// a.С��֮����ܳ���ճ��
			// b.С���ٶȹ���ʱ,���ܼ����ײʱ�Ѿ������
			int dist2 = (X[i] - X[j]) * (X[i] - X[j]) + (Y[i] - Y[j]) * (Y[i] - Y[j]);
			if(dist2 <= 4*r*r)	
			{
				u[0]  = X[j] - X[i];		
				u[1]  = Y[j] - Y[i];
				v1xy[0] = VX[i];
				v1xy[1] = VY[i];
				v2xy[0] = VX[j];
				v2xy[1] = VY[j];
				// ���С�����������޸�С����ٶ�
				if(Response(v1xy, v2xy, u))
				{
					VX[i] = v1xy[0];			// ��ײ����С����ٶȵĸı�
					VY[i] = v1xy[1];
					VX[j] = v2xy[0];
					VY[j] = v2xy[1];
				}
			}
		}
	}
	// 2 ����С�����Ļ�߽����ײ
	for (int i = 0; i < n; i++)
	{
		if((X[i] - r) <= 0)					// ��߽�
			VX[i] = abs(VX[i]);
		else if((X[i] + r) >= wndWidth)		// �ұ߽�
			VX[i] = -abs(VX[i]);
		if ((Y[i] + r) >= wndHeight)		// �±߽�
			VY[i] = -abs(VY[i]);
		else if ((Y[i] - r) <= 0)			// �ϱ߽�
			VY[i] = abs(VY[i]);
	}
	// �����ٶȸ���С���λ��,�Ա��������
	for (int i = 0; i < n; i++)
	{
		X[i] += VX[i] * elapseTime;
		Y[i] += VY[i] * elapseTime;
	}
}

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
	LoadString(hInstance, IDC_BUMPBALLS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BUMPBALLS));

	srand(time((NULL)));	// �������
	GenerateBall(&nBalls);	// �������һ��С��

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BUMPBALLS));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_BUMPBALLS);
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
	case WM_CREATE:			// ����������
		SetTimer(hWnd,1,timeStep,NULL);	// ��ʼ����һ��IDΪ1�Ķ�ʱ��,ÿtimeStep���봥��һ����ʱ����Ϣ
		break;
	case WM_TIMER:			// ��ʱ����Ӧ��Ϣ
		if (wParam == 1)	// ����Ǹ���Ȥ�Ķ�ʱ��(IDΪ1),�������Ϸ����
		{
			UpdateBalls(nBalls, radius, ballsX, ballsY, ballsVX, ballsVY, timeStep/10);
			InvalidateRect(hWnd, NULL, TRUE);	// �ô��ڱ�Ϊ��Ч,�Ӷ������ػ���Ϣ
		}
		break;
	case WM_SIZE:			// ��ȡ���ڵĳߴ�
		wndWidth = LOWORD(lParam);
		wndHeight = HIWORD(lParam);
		break;
	case WM_KEYDOWN:
		if (wParam == ' ')	// ���¿ո�
		{
			GenerateBall(&nBalls);				// ����һ��С��
			InvalidateRect(hWnd, NULL, TRUE);	// �ô��ڱ�Ϊ��Ч,�Ӷ������ػ���Ϣ
		}
		break;
	case WM_ERASEBKGND:		// �ػ����������Ϣ,����������,������˸
		break;
	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			// ���µĲ�����Ϊ�˱��������Ļ��˸,���������Ȼ��Ƶ��ڴ���,Ȼ��һ���Կ�������Ļ��
			// �����ڴ�HDC
			HDC memHDC = CreateCompatibleDC(hdc);

			//��ȡ�ͻ�����С
			RECT rectClient;
			GetClientRect(hWnd, &rectClient);

			//����λͼ
			HBITMAP bmpBuff = CreateCompatibleBitmap(hdc,wndWidth,wndHeight);
			HBITMAP pOldBMP = (HBITMAP)SelectObject(memHDC, bmpBuff);
			PatBlt(memHDC,0,0,wndWidth,wndHeight,WHITENESS);	// ���ñ���Ϊ��ɫ

			// ���������Ļ���
			DrawBalls(memHDC, nBalls, radius, ballsX, ballsY, ballsC);

			//�����ڴ�HDC���ݵ�ʵ��HDC
			BOOL tt = BitBlt(hdc, rectClient.left, rectClient.top, wndWidth,
				wndHeight, memHDC, rectClient.left, rectClient.top, SRCCOPY);

			//�ڴ����
			SelectObject(memHDC, pOldBMP);
			DeleteObject(bmpBuff);
			DeleteDC(memHDC);

			EndPaint(hWnd, &ps);
			break;
		}
	case WM_DESTROY:
		KillTimer(hWnd,1);			// �����˳�ʱ������ʱ��ɾ��
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
