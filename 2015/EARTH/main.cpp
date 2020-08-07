
#include<Windows.h>
#include<tchar.h>
#include "Framework/Game.h"
#include "Earth.h"
//#include"resource.h"

//�����ص�����
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
///////////////
Earth *pGame;
//���������ʹ��ڱ���
const TCHAR szWindowClass[] = L"��һ������";
const TCHAR szWindowTitle[] = L"EARTH";

//WinMain��������ڵ�
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//ע�ᴰ����
	WNDCLASSEX wcex = { 0 };//������ṹ��
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.hInstance = hInstance;
	//wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));//ʹ��ϵͳĬ�ϵ�ͼ��
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);//ʹ��ϵͳĬ�ϵ�ͼ��
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);//ʹ��ϵͳĬ�ϵĹ��
	wcex.hbrBackground = NULL; //(HBRUSH)GetStockObject(WHITE_BRUSH);//��ɫ��ˢ      
	wcex.lpszClassName = szWindowClass;
	RegisterClassEx(&wcex);
	//��������
	HWND hWnd = CreateWindow(
		szWindowClass,             //��������
		szWindowTitle,             //���ڱ���
		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX/*���*/ & ~WS_THICKFRAME/*���ϱ߿�*/,      
		//���ڷ��
//		100, 200, 500, 500,           //���Ͻ������Լ���ȣ��߶�
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		866,606,
        HWND_DESKTOP,
		NULL,
		hInstance,
		NULL
		);

	if (!hWnd) return FALSE;//������ڴ���ʧ�����˳�
	/////////////////////////
	pGame = new Earth(hWnd, 60);
	//pGame->Init();
	//��ʾ�����´���
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);



	//�޸ĺ����Ϣѭ��
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


//���ں�����������Ϣ����
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
		//pGame->MouseCSide();//��������λ��-Ӧ�÷���main
		return 0;

	}

	return DefWindowProc(hWnd, msg, wParam, lParam);


}