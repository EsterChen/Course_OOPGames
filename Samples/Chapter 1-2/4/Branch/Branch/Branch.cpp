// Branch.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Branch.h"
#include <time.h>
/************************************************************************/
/*	����Ŀ�ģ�C�����еķ�֧�ṹ
	�����ܣ������֡�������������4�����ظ������֣�����Ҳ²⣬�������²����ʾ������Ա�����ҽ�һ���²⡣
		From: http://zh.wikipedia.org/wiki/%E7%8C%9C%E6%95%B0%E5%AD%97
		��Ϸ����
		ͨ�����������棬һ�������֣�һ���¡������ֵ���Ҫ���һ��û���ظ����ֵ�4λ���������òµ���֪�����µ��˾Ϳ��Կ�ʼ�¡�ÿ��һ�����֣�
		�����߾�Ҫ����������ָ�����A��B������Aǰ������ֱ�ʾλ����ȷ�����ĸ�������Bǰ�����ֱ�ʾ������ȷ��λ�ò��Ե����ĸ�����
		����ȷ��Ϊ 5234�����µ��˲� 5346������ 1A2B��������һ��5��λ�ö��ˣ���Ϊ1A����3��4���������ֶ��ˣ���λ��û�ԣ���˼�Ϊ 2B������������ 1A2B��
		���Ųµ����ٸ��ݳ����ߵļ�A��B�����£�ֱ�����У��� 4A0B��Ϊֹ��
		��������Ϸ��һ�ֱ��������ظ������롣���ֹ������Ϸ����Ϊ Mastermind����������Ϊ��
		��������Ĺ����⣬����г����ظ������֣����ظ�������ÿ��Ҳֻ����һ�Σ��������ŵĽ��Ϊ׼�����磬����ȷ��Ϊ5543���µ��˲�5255��
		�������ﲻ����Ϊ�²�ĵ�һ��5����ȷ�𰸵ڶ������������Ž��Ϊ׼��ԭ���ÿ������ֻ����һ�εĹ��������ȽϺ�Ӧ��Ϊ1A1B����һ��5λ����ȷ��
		��Ϊ1A���²������еĵ�����5����ĸ�5�ʹ𰸵ĵڶ���5ƥ�䣬ֻ�ܼ�Ϊ1B����Ȼ������в�5267�еĵ�һ��5��������еĵڶ���5ƥ�䣬���ֻ�ܼ���1A0B��
	�����߸Ľ�:�޸�Ϊ֧���ظ����ֵ�ģʽ
	��д�ߣ������ף�hanhonglei@sina.com��*/
/************************************************************************/

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

char num[4];				// ����������ɵĴ��²�����
char guess[4];				// ��Ҳ²��4������
int nGuess = 0;				// ����Ѿ���������ָ���
WCHAR str[16];				// ��������ַ���
int x = 0, y = 0;			// ���ֺ�λ�ö���ȷ�ĸ���,�Լ�������ȷ��λ�ò���ȷ�ĸ���

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
	LoadString(hInstance, IDC_BRANCH, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BRANCH));

	srand(time(NULL));				// �������
	for (int i = 0; i < 4; i++)		// �������4�����ظ�����
	{
		num [i] = '0' + rand()%10;
		for (int j = 0; j < i; j++)
		{
			if (num[i] == num[j])	// ��֤�������ظ�Ԫ��
			{
				i--;
				break;
			}
		}
	}

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BRANCH));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_BRANCH);
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
		InvalidateRect(hWnd, NULL, TRUE);	// �ػ���Ļ��Ϣ
		if(wParam < '0' || wParam > '9')	// ����������Ĳ�������,�򲻼�¼
		{
			if (wParam == VK_RETURN)		// ����������س���,���ʾ���²²�
			{
				nGuess = 0;
				x = y = 0;
			}
			else if (wParam == ' ')			// ����������ո��,������������ɴ��²������
			{
				for (int i = 0; i < 4; i++)
				{
					num [i] = '0' + rand()%10;
					for (int j = 0; j < i; j++)
					{
						if (num[i] == num[j])	// ��֤�������ظ�Ԫ��
						{
							i--;
							break;
						}
					}
				}
				nGuess = 0;
				x = y = 0;
			}
			break;
		}
		if (nGuess < 4)						// �������²������
		{
			guess[nGuess++] = wParam;
		}
		if (nGuess == 4)					// ����Ѿ�������4������,��ʾ�²���ϣ��жϽ��
		{
			x = y = 0;
			for(int i = 0;i < 4; i++)
				for(int j = 0; j < 4; j++){
					if(num[i] == guess[i]){
						x++;
						break;
					}
					if(guess[j] == num[i])
						y++;
				}
		}

		break; 
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		TextOut(hdc, 0, 0, L"���4������", 6);
		for (int i = 0; i < nGuess; i++)	// �������Ѿ��²������
		{
			swprintf(str, L"%c", guess[i]);
			TextOut(hdc, i*20, 20, str, wcslen(str));
		}
		if(nGuess == 4)						// �������Ѿ��������,������²���
		{
			if(x==4){				
				TextOut(hdc, 0, 20, L"�¶��ˣ�", 4);
				break;
			}
			else{
				swprintf(str, L"�����%dA%dB", x, y);
				TextOut(hdc, 80, 20, str, wcslen(str));
			}
		}
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
