#pragma once

#include <windows.h>
#include"MyFrame\CMyGame.h"

using namespace std;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

CMyGame *pCGame;

HWND hWnd;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT ("Demo") ;
	MSG			msg ;
	WNDCLASS	wc ;
	wc.style			= CS_HREDRAW | CS_VREDRAW ;
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
	hWnd = CreateWindow(szAppName,	// window class name
		TEXT("The Demo Game"),	// window caption
		WS_OVERLAPPEDWINDOW,	// window style
		//WS_POPUP | WS_VISIBLE,
		CW_USEDEFAULT,	// initial x position
		CW_USEDEFAULT,	// initial y position
		638,	// initial x size
		518,	// initial y size
		NULL,			// parent window handle
		NULL,	        // window menu handle
		hInstance,	    // program instance handle
		NULL) ; 	    // creation parameters


	ShowWindow (hWnd, SW_SHOW/*MAXIMIZED*/) ;
	UpdateWindow (hWnd) ;

	pCGame = new CMyGame(hInstance, hWnd);
	
	if (SUCCEEDED(CoInitialize(NULL)))				//�����ʼ��Com����ɹ�
	{
			BOOL  bMessage;
			PeekMessage(&msg, NULL, 0, 0,PM_NOREMOVE);
			while(msg.message != WM_QUIT)			//������Ϣѭ��
			{
				bMessage = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
				if(bMessage)
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				pCGame->GameFunc();							//��Ⱦ
			} 
	}						
	delete pCGame;	//�ͷ���Դ
	CoUninitialize();		//�ͷ�Com���
	
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
		pCGame->HandleMouseDown(wParam, lParam);
		return 0;

		
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}


