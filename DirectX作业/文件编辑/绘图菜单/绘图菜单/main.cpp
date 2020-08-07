#include<windows.h>
#include <tchar.h>
#include <vector>
#include <string>
#include "resource.h"
enum SCRAWLTYPE
{
	SCRAWLLINE,
	SCRAWLRECTANGLE,
	SCRAWLELLIPSE,
};

struct SCRAWL
{
	POINTS begin;
	POINTS end;
	COLORREF color;
	SCRAWLTYPE type;
};

TCHAR typeText[3][10] = { _T("直线"), _T("矩形"), _T("椭圆") };
HINSTANCE g_hInst;
SCRAWL temp;

TCHAR filename[256] = _T("");
TCHAR strDefExt[] = _T("pat");
OPENFILENAME of = { sizeof (OPENFILENAME) };
HANDLE hFile;
DWORD bytesToWrite = 0;

//窗口函数声明
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void DrawGraphics(HDC hdc, POINTS begin, POINTS end, COLORREF penColor, SCRAWLTYPE type);
//入口函数 WinMain()
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	static TCHAR szAppName[] = TEXT("Hello windows");
	WNDCLASS wndclass;        //定义窗口类结构变量
	HWND hwnd;                //定义窗口句柄
	MSG msg;                  //定义消息结构变量

	/********定义窗口类各属性*******/
	wndclass.style = CS_HREDRAW | CS_VREDRAW;       //改变窗口大小则重画
	wndclass.lpfnWndProc = WndProc;               //窗口函数为  WndProc
	wndclass.cbClsExtra = 0;                      //窗口类无扩展
	wndclass.cbWndExtra = 0;                      //窗口实例无扩展
	wndclass.hInstance = hInstance;               //注册窗口类的实例句柄
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //窗口用默认图标
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);   //窗口用箭头光标
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景为白色
	wndclass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);                 //窗口默认无菜单
	wndclass.lpszClassName = szAppName;


	if (!RegisterClass(&wndclass)) {
		MessageBox(NULL, TEXT("注册失败！"), szAppName, MB_ICONERROR);
		return -1;
	}
	
	HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));

	//创建窗口
	/****从第一个参数开始代表Chap1Exa1,为Chap1Exa1,,左上角屏幕坐标,
	宽度和高度,,,创建窗口的实例句柄,此窗口无创建参数****/
	hwnd = CreateWindow(szAppName,//窗口类名
		szAppName,//窗口名
		WS_OVERLAPPEDWINDOW,//重叠式窗口风格
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,//系统缺省的坐标和宽度高度
		NULL,//窗口无父窗口
		hMenu,//窗口无主菜单
		hInstance,//实例句柄
		NULL//无创建参数
		);
	g_hInst = hInstance;
	ShowWindow(hwnd, nCmdShow);              //显示窗口
	UpdateWindow(hwnd);                     //更新窗口的客户区

	//以下消息循环
	while (GetMessage(&msg, NULL, 0, 0))        //获取消息，遇WM_QUIT退出循环
	{
		TranslateMessage(&msg);             //键盘消息转换
		DispatchMessage(&msg);              //派送消息给窗口函数
	}
	return msg.wParam;

}

//窗口函数
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;                     //定义设备描述表句柄
	PAINTSTRUCT ps;              //定义绘图信息结构变量
	static std::vector<SCRAWL> save;
	static POINTS begin = { 0, 0 };
	static SCRAWLTYPE type = SCRAWLLINE;
	static COLORREF penColor = RGB(0, 0, 0);
	static TCHAR str[100] = _T("当前绘制的是直线(直线按7，矩形按8，椭圆按9，红色R，绿色G，蓝色B，黑色K)");
	static bool mousestate = false;
	HBRUSH oldBrush;
	static POINTS end = { 0, 0 };
	switch (message)                  //根据消息值转相应的消息处理
	{

	case WM_PAINT:                   //重画窗口客户区消息
		hdc = BeginPaint(hwnd, &ps);  //获取需重画窗口的设备描述表句柄
		oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
		SetTextColor(hdc, penColor); 
		TextOut(hdc, 0, 0, str, _tcslen(str));
		for (std::vector<SCRAWL>::const_iterator i = save.cbegin(); i != save.cend(); i++)
		{
			DrawGraphics(hdc, i->begin, i->end, i->color, i->type);
		}
		SelectObject(hdc, oldBrush);
		if (mousestate == true)
		{
			oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
			DrawGraphics(hdc, begin, end, penColor, type);
			SelectObject(hdc, oldBrush);

		}
		EndPaint(hwnd, &ps);          //结束要重画的窗口

		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case 55:
			type = SCRAWLLINE;
			break;

		case 56:
			type = SCRAWLRECTANGLE;
			break;

		case 57:
			type = SCRAWLELLIPSE;
			break;

		case 0x52:
			penColor = RGB(255, 0, 0);
			break;

		case 0x47:
			penColor = RGB(0, 255, 0);
			break;

		case 0x42:
			penColor = RGB(0, 0, 255);
			break;

		case 0x4B:
			penColor = RGB(0, 0, 0);
			break;
		}

		hdc = GetDC(hwnd);
		wsprintf(str, _T("当前绘制的是%s(直线按7，矩形按8，椭圆按9，红色R，绿色G，蓝色B，黑色K)"), typeText[type]);
		SetTextColor(hdc, penColor);
		TextOut(hdc, 0, 0, str, _tcslen(str));
		ReleaseDC(hwnd, hdc);

		return 0;
	case WM_LBUTTONDOWN:
		mousestate = true;
		begin = MAKEPOINTS(lParam);
		return 0;

	case WM_LBUTTONUP:
		mousestate = false;
		end = MAKEPOINTS(lParam);

		SCRAWL s;
		s.begin = begin;
		s.end = end;
		s.color = penColor;
		s.type = type;
		save.push_back(s);
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;

	case WM_MOUSEMOVE:
		if (mousestate == true)
		{
			end = MAKEPOINTS(lParam);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		return 0;
	case  WM_DESTROY:                //撤消窗口消息
		PostQuitMessage(0);          //产生退出程序消息WM_QUIT
		return 0;

	case WM_COMMAND :
		switch (LOWORD(wParam))
		{
		case ID_HELP_ABOUT :
			MessageBox(NULL, TEXT("绘图小程序！"), _T("说明信息"), MB_OK);
			break;

		case ID_FILE_SAVE :
			of.hwndOwner = hwnd;
			of.hInstance = g_hInst;
			of.lpstrFilter = _T("涂鸦文件(*.pat)\0*.pat\0");
			of.nFilterIndex = 1;
			of.lpstrFile = filename;
			of.nMaxFile = MAX_PATH;
			of.lpstrDefExt = strDefExt;
			of.Flags = OFN_EXPLORER;

			if (GetSaveFileName(&of) == true)
			{
				hFile = CreateFile(
					filename,
					GENERIC_WRITE,
					0,
					NULL,
					CREATE_ALWAYS,
					FILE_ATTRIBUTE_NORMAL,
					NULL);
			}
			for (std::vector<SCRAWL>::const_iterator i = save.cbegin(); i != save.cend(); i++)
			{
				WriteFile(hFile, &(*i), sizeof(SCRAWL),&bytesToWrite, NULL);
			}
			CloseHandle(hFile);
			break;

		case ID_FILE_OPEN :
			of.hwndOwner = hwnd;
			of.hInstance = g_hInst;
			of.lpstrFilter = _T("涂鸦文件(*.pat)\0*.pat\0");
			of.nFilterIndex = 1;
			of.lpstrFile = filename;
			of.nMaxFile = MAX_PATH;
			of.lpstrDefExt = strDefExt;
			of.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER | OFN_HIDEREADONLY;

			if (GetOpenFileName(&of) == true)
			{
				save.empty();
				hFile = CreateFile(
					filename,
					GENERIC_READ,
					0,
					NULL,
					OPEN_EXISTING,
					FILE_ATTRIBUTE_NORMAL,
					NULL
					);
				while (true)
				{
					ReadFile(hFile, &temp, sizeof(SCRAWL), &bytesToWrite, NULL);
					if (bytesToWrite == 0)
						break;
					save.push_back(temp);
				}
				CloseHandle(hFile);
				InvalidateRect(hwnd, NULL, true);

			}
			break;

		case ID_FILE_EXIT :
			DestroyWindow(hwnd);
			break;
			
		case  ID_STYLE_LINE :
			type = SCRAWLLINE;
			break;

		case ID_STYLE_ELLIPSE :
			type = SCRAWLELLIPSE;
			break;

		case ID_STYLE_RECTANGLE :
			type = SCRAWLRECTANGLE;
			break;

		case ID_COLOR_RED :
			penColor = RGB(255, 0, 0);
			break;

		case ID_COLOR_GREEN :
			penColor = RGB(0, 255, 0);
			break;
			
		case ID_COLOR_BLUE :
			penColor = RGB(0, 0, 255);
			break;

		case ID_COLOR_BLACK :
			penColor = RGB(0, 0, 0);
			break;
		}
		hdc = GetDC(hwnd);
		wsprintf(str, _T("当前绘制的是%s(直线按7，矩形按8，椭圆按9，红色R，绿色G，蓝色B，黑色K)"), typeText[type]);
		SetTextColor(hdc, penColor);
		TextOut(hdc, 0, 0, str, _tcslen(str));
		ReleaseDC(hwnd, hdc);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);//其它转默认窗口函数
}

void DrawGraphics(HDC hdc, POINTS begin, POINTS end, COLORREF penColor, SCRAWLTYPE type)
{
	HPEN pen = CreatePen(PS_SOLID, 1, penColor);
	HPEN oldpen = static_cast<HPEN>(SelectObject(hdc, pen));

	switch (type)
	{
	case SCRAWLLINE:
		MoveToEx(hdc, begin.x, begin.y, NULL);
		LineTo(hdc, end.x, end.y);
		break;

	case SCRAWLRECTANGLE:
		Rectangle(hdc, begin.x, begin.y, end.x, end.y);
		break;

	case SCRAWLELLIPSE:
		Ellipse(hdc, begin.x, begin.y, end.x, end.y);
		break;
	}

	SelectObject(hdc, oldpen);
}