// Word.cpp : Defines the entry point for the application.
//
/************************************************************************/
/*	����Ŀ�ģ��ַ���
	�����ܣ�����Ӣ�ۡ����涥�˻᲻�����¸��ֵ���,Ҫ������ڵ������ǰ������ȷ�ĵ���
		���һ���������,��������1,����Ϊ0,����Ϸ����.��ȷ����һ������,�÷ּ�1
		�÷�Խ�ߵ��������ٶ�Խ��,��ÿ10�ֻ������ٶ�Ϊ��ʼ״̬
	�����߸Ľ�:���Ӳ���ƥ���ʶ��ȣ����粿��ƥ�����ĸ�ø�����ʾ
	��д�ߣ������ף�hanhonglei@sina.com��*/
/************************************************************************/

#include "stdafx.h"
#include "Word.h"
#include <string.h>
#include <stdio.h>
#include <time.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

#define ALL_WORDS 18
#define SCR_WORDS 4
#define MAX_LEN_WORD 16

// �ַ�������,�������п��ܵ��ַ���,ÿ���ַ�����һ��Ӣ�ĵ���
char *candWords[ALL_WORDS] = {"noun","adjective","dverb","pronoun","conjunction","preposition","number","interjection","phrasal"
	,"contain","embrace","vibrate","innovate","extract","entilate","deprive","whitewash","contrary"};
// ��ǰ��Ļ����ʾ����Ҫ��Ҽ���ĵ�����candWords�е��±�
int scrWords[SCR_WORDS];
// ÿ����Ļ���ʵ�λ��
int posXWords[SCR_WORDS], posYWords[SCR_WORDS];
// ��ҵ�����
char inputs[MAX_LEN_WORD];	int nInput = 0;
// ��ʱ��ʱ����
int timeStep = 200;
// ���ڳߴ�
int wndWidth = 0;	int wndHeight = 0;  
// �����ƶ��ٶ�
int v = 1;
// ��ҵ÷ֺ�����
int nScore = 0;	int nLife = 3;
// ��ǰ��Ҳ������еĵ���,ʹ��λ�������м���
unsigned short tmpHits;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

// ���������Ļ��ָ���±�id�ĵ���
void GenerateWord(int id)
{
	int done = 0;
	while(!done)			// ��֤���ɵĵ��ʺ���Ļ�����е��ʲ��ظ�
	{
		done = 1;
		int candID = scrWords[id]= rand() % (ALL_WORDS);
		for (int i = 0; i < SCR_WORDS; i++)
		{
			if (i == id)
				continue;
			if (scrWords[i] == candID)
			{
				done = 0;
				break;
			}
		}
	}
	// ���õ��ʵ�λ�úͲ������б�־
	posYWords[id] = 0;
	tmpHits ^= tmpHits & (1<<id);
}
// ��ʼ�����ֲ���
void Init()
{
	memset(scrWords, -1, SCR_WORDS*sizeof(int));	// ��Ļ�ϵ��ʵ��±�
	memset(posYWords, 0, SCR_WORDS*sizeof(int));	// ��Ļ�ϵ��ʵ�������
	memset(inputs, '\0', SCR_WORDS*sizeof(char));	// ��ǰ����Ĳ����ַ�
	tmpHits = 0;									// û�����е���
	for(int i = 0; i < SCR_WORDS; i++)				// Ϊ��Ļ�ϵĵ��ʸ��������
	{
		posXWords[i] = i*wndWidth / SCR_WORDS;
		GenerateWord(i);
	}
	nLife = 3;										// ���������ʼΪ3,�÷�Ϊ0
	nScore = 0;
}
// ��������������ĸ,�����ǲ�������,����ȫ������,ȫ������Ҫ�÷�,�����������еĵ���
// @c ��ǰ�������ĸ
// @n ��ǰ�Ѿ�������ɵ���ĸ��,ʹ��ָ�뷽ʽ,�ں����ڶ��ⲿ���������޸�
// @ips ��������������ĸ����
// @����ֵ ���еĵ����±�
int InputChar(char c, int *n, char ips[])
{
	ips[*n] = c;
	int done = 0;
	int hitID = -1;
	unsigned short th = 0;
	for (int i = 0; i < SCR_WORDS; i++)	// ������Ļ�ϵ����е��ʶ����бȽ�
	{
		if(strnicmp(ips, candWords[scrWords[i]], strlen(ips)) == 0)	// �������ƥ��Ļ�,���ƥ��ĵ����±�(ʹ��λ����)
		{
			done = 1;
			th |= (1<<i);
			if(stricmp(ips, candWords[scrWords[i]]) == 0)			// ���ȫ��ƥ��,��������ʱ�����,�÷�
			{
				nScore++;
				hitID = i;
				v++;
				v = (nScore%10==0)?1:v;								// ÿ��10��,�����õ����ٶ�
				break;
			}
		}
	}
	if (!done)
		ips[*n] = '\0';
	else
	{
		(*n)++;
		tmpHits = th;
	}
	return hitID;
}
// �������������ַ���
void ResetInputs()
{
	nInput = 0;
	memset(inputs, '\0', MAX_LEN_WORD*sizeof(char));
	tmpHits = 0;
}
// ÿ֡���и���,�����ٶȸ��µ���λ��
// @ts ��֮֡��ʱ����
void Update(int ts)
{
	for(int i = 0; i < SCR_WORDS; i++)
	{
		if (posYWords[i] >= wndHeight)	// ��������Ѿ����,���������,��������һ�����ظ��ĵ���
		{
			nLife--;
			GenerateWord(i);
			int bReset = 1;
			for (int i = 0; i < SCR_WORDS; i++)
			{
				if (tmpHits & (1<<i))
				{
					bReset = 0;
					break;
				}
			}
			if (bReset)
				ResetInputs();

		}
		else
			posYWords[i] += v * ts;		// ������Ļ����λ��
	}
}
// ��ӡ,���������Ϣ�Լ�������������Ϣ
void PrintWords(HDC hdc)
{
	HFONT hf;
	WCHAR str[MAX_LEN_WORD];
	// 1 �ú�ɫ����,����Ļ���Ĵ�ӡ�����Ϣ,����������Ϊ0,���ӡ������Ϣ
	SetTextColor(hdc, RGB(255, 0, 0));
	hf =						//�����߼�����
		CreateFont(  
		56,						//����߶�(��ת���������)=56    
		20,						//������(��ת�������߶�)=20  
		0,						//������ʾ�Ƕ�=0��  
		0,						//nOrientation=0  
		10,						//�������=10 
		FALSE,					//��б��
		FALSE,					//���»���
		FALSE,					//��ɾ����
		DEFAULT_CHARSET,         //ʹ��ȱʡ�ַ���
		OUT_DEFAULT_PRECIS,		//ȱʡ�������
		CLIP_DEFAULT_PRECIS,	//ȱʡ�ü�����
		DEFAULT_QUALITY,		//nQuality=ȱʡֵ
		DEFAULT_PITCH,			//nPitchAndFamily=ȱʡֵ
		L"@system");			//������=@system 
	HFONT hfOld = (HFONT)SelectObject(hdc, hf);
	if (nLife > 0)
	{
		MultiByteToWideChar(CP_THREAD_ACP,MB_USEGLYPHCHARS,inputs,strlen(inputs)+1,str,MAX_LEN_WORD);   // ���û������븴�Ƶ��ַ�����
		TextOut(hdc, wndWidth/2-100, wndHeight/2,str,wcslen(str));

		wsprintf(str, L"Life:%d Score:%d", nLife, nScore);	
		TextOut(hdc, wndWidth/2-100, wndHeight/2-40,str,wcslen(str));
	}
	else
	{
		TextOut(hdc, wndWidth/2-100, wndHeight/2-40,L"Game Over",9);
		SelectObject(hdc, hfOld);
		return;
	}	

	// 2 ������һ�������ӡ��Ļ�ϴ�����ĵ���
	long lfHeight;
	lfHeight = -MulDiv(50, GetDeviceCaps(hdc, LOGPIXELSY), 72);
	DeleteObject(hf);
	hf = CreateFont(lfHeight, 0, 0, 0, 0, TRUE, 0, 0, 0, 0, 0, 0, 0, L"Times New Roman");

	SelectObject(hdc, hf);
	for(int i = 0; i < SCR_WORDS; i++)
	{
		if (tmpHits & (1<<i))		// �����ǰ���ʲ�������,����������ɫ��ʾ
			SetTextColor(hdc, RGB(0, 125, 125));
		else
			SetTextColor(hdc, RGB(0, 0, 0));
		MultiByteToWideChar(CP_THREAD_ACP,MB_USEGLYPHCHARS,candWords[scrWords[i]],strlen(candWords[scrWords[i]])+1,str,MAX_LEN_WORD);   // ���û������븴�Ƶ��ַ�����
		TextOut(hdc, posXWords[i], posYWords[i],str,wcslen(str));
	}
	SelectObject(hdc, hfOld);		// �ָ�Ĭ������
	DeleteObject(hf);
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
	LoadString(hInstance, IDC_WORD, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WORD));

	srand(time(NULL));	// �������
	Init();				// ��ʼ�����ֲ���

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WORD));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WORD);
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
	case WM_CREATE:			// ����������,��ʼ����һ����ʱ��
		SetTimer(hWnd,1,timeStep,NULL);
		break;
	case WM_TIMER:			// ��ʱ����Ӧ
		if (wParam == 1)
		{
			Update(timeStep/100);				// ������Ϸ����
			InvalidateRect(hWnd, NULL, TRUE);	// �ô��ڱ�Ϊ��Ч,�Ӷ������ػ���Ϣ
		}
		break;
	case WM_SIZE:			// ����������Ϣ����ȡ���ڵĳߴ�
		wndWidth = LOWORD(lParam);
		wndHeight = HIWORD(lParam);
		break;
	case WM_CHAR: 
		{
			InvalidateRect(hWnd, NULL, TRUE);		// �ػ���Ļ
			if ((wParam >= 'A' && wParam <= 'Z')||	// ������������ĸ,������ҵ�����			
				(wParam >= 'a' && wParam <= 'z'))
			{
				int hit = InputChar(wParam, &nInput, inputs);	
				if(hit != -1)						// ����е��ʻ���,�����������µĵ���
				{
					GenerateWord(hit);
					ResetInputs();
				}
			}
			else if (wParam == ' ')					// �������ո�,�����õ�ǰ����
				ResetInputs();
			break;
		}
	case WM_ERASEBKGND:		// ����������,������˸
		break;
	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			// ���µĲ�����Ϊ�˱��������Ļ��˸,��������Ƶ��ڴ���,һ���Կ�������Ļ��
			//�����ڴ�HDC
			HDC memHDC = CreateCompatibleDC(hdc);

			//��ȡ�ͻ�����С
			RECT rectClient;
			GetClientRect(hWnd, &rectClient);

			//����λͼ
			HBITMAP bmpBuff = CreateCompatibleBitmap(hdc,wndWidth,wndHeight);
			HBITMAP pOldBMP = (HBITMAP)SelectObject(memHDC, bmpBuff);
			PatBlt(memHDC,0,0,wndWidth,wndHeight,WHITENESS);	// ���ñ���Ϊ��ɫ

			// ���������Ļ���
			PrintWords(memHDC);

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
		KillTimer(hWnd,1);		// �����˳�ʱ������ʱ��ɾ��
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
