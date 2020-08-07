//#include"框架-3CGame\D2D1link.h"
#include <windows.h>
#include"MyGame\CMyGame.h"

using namespace std;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HWND		hWnd;
using namespace std;

/*初始化静态成员*/
CResourcesPool * CResourcesPool::pCResourcePool = NULL;
CSpritesManager *CSpritesManager::instance = NULL;
CDemoGame *CDemoGame::instance = NULL;

/*框架*/
CDemoGame *pGame = NULL;	//定义指针pGame
HWND CDemoGame::hWnd = NULL;
INT CDemoGame::nFps = 0;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT ("Demo") ;
	MSG			msg ;
	WNDCLASS	wc ;
	wc.style			= CS_OWNDC/*CS_HREDRAW | CS_VREDRAW */;
	wc.lpfnWndProc		= WndProc ;
	wc.cbClsExtra		= 0 ;
	wc.cbWndExtra		= 0 ;
	wc.hInstance		= hInstance ;
	wc.hIcon			= LoadIcon (NULL, IDI_APPLICATION) ;
	wc.hCursor			= LoadCursor (NULL, IDC_ARROW) ;
	wc.hbrBackground	= (HBRUSH) GetStockObject (WHITE_BRUSH) ;
	wc.lpszMenuName		= NULL ;
	wc.lpszClassName	= szAppName ;

	if (!RegisterClass (&wc))
	{
		MessageBox (	NULL, TEXT ("This program requires Windows NT!"), 
			szAppName, MB_ICONERROR) ;
		return 0 ;
	}

	hWnd = CreateWindow
		(szAppName,	// window class name
		TEXT("EARTH"),	// window caption
		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,	// window style
		//WS_POPUP | WS_VISIBLE,
		CW_USEDEFAULT,	// initial x position
		CW_USEDEFAULT,	// initial y position
		866,	// initial x size
		606,	// initial y size
		HWND_DESKTOP,			// parent window handle
		NULL,	        // window menu handle
		hInstance,	    // program instance handle
		NULL) ; 	    // creation parameters

	ShowWindow(hWnd, iCmdShow/*SW_SHOWMAXIMIZED*/);
	UpdateWindow (hWnd) ;

	//进入消息循环之前，创建CDemoGame对象
	::CoInitialize(NULL);
	pGame = CDemoGame::GetInstance(hWnd,60);
	pGame->InitGame();

	
	BOOL  bMessage;
	PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE);
	while (msg.message != WM_QUIT)
	{
		bMessage = PeekMessage(&msg, NULL, 0,
			0, PM_REMOVE);
		if (bMessage) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		pGame->GameFunc();		//帧函数
	}


	if (pGame)	//程序结束前，释放资源
		delete pGame;
	::CoUninitialize(); 
	return 0 ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYUP:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0) ;
		}	
		return 0;
	
	case WM_DESTROY:
		PostQuitMessage(0) ;
		return 0 ;

	case WM_LBUTTONDOWN:
		pGame->MouseCSide();
		return 0;

	case WM_MOUSEMOVE:
		pGame->MouseSide();
		return 0;
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}

