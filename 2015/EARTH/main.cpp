
#include<Windows.h>
#include<tchar.h>
#include "Framework/Game.h"
#include "Earth.h"
//#include"resource.h"

//声明回调函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
///////////////
Earth *pGame;
//窗口类名和窗口标题
const TCHAR szWindowClass[] = L"第一个窗口";
const TCHAR szWindowTitle[] = L"EARTH";

//WinMain函数，入口点
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//注册窗口类
	WNDCLASSEX wcex = { 0 };//窗口类结构体
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.hInstance = hInstance;
	//wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));//使用系统默认的图标
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);//使用系统默认的图标
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);//使用系统默认的光标
	wcex.hbrBackground = NULL; //(HBRUSH)GetStockObject(WHITE_BRUSH);//白色面刷      
	wcex.lpszClassName = szWindowClass;
	RegisterClassEx(&wcex);
	//创建窗口
	HWND hWnd = CreateWindow(
		szWindowClass,             //窗口类名
		szWindowTitle,             //窗口标题
		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX/*最大化*/ & ~WS_THICKFRAME/*加上边框*/,      
		//窗口风格
//		100, 200, 500, 500,           //左上角坐标以及宽度，高度
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		866,606,
        HWND_DESKTOP,
		NULL,
		hInstance,
		NULL
		);

	if (!hWnd) return FALSE;//如果窗口创建失败则退出
	/////////////////////////
	pGame = new Earth(hWnd, 60);
	//pGame->Init();
	//显示并更新窗口
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);



	//修改后的消息循环
	BOOL bMessage;
	MSG msg;
	PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE);
	while (msg.message != WM_QUIT)
	{
		bMessage = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		if (bMessage)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		/////////////
		pGame->FrameFunc();
	}
	////////////
	if (pGame)
		delete pGame;
	return (int)msg.wParam;
}


//窗口函数，用于消息处理
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		pGame->White();
		pGame->SetGameOver();
		pGame->Erase();
		PostQuitMessage(0);
		return 0;

	case WM_MOUSEMOVE:
		pGame->MouseMove();
		return 0;

	case WM_LBUTTONDOWN:
		pGame->MouseClick();
		//pGame->MouseCSide();//获得鼠标点击位置-应该放在main
		return 0;

	}

	return DefWindowProc(hWnd, msg, wParam, lParam);


}