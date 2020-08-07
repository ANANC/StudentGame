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

TCHAR typeText[3][10] = { _T("ֱ��"), _T("����"), _T("��Բ") };
HINSTANCE g_hInst;
SCRAWL temp;

TCHAR filename[256] = _T("");
TCHAR strDefExt[] = _T("pat");
OPENFILENAME of = { sizeof (OPENFILENAME) };
HANDLE hFile;
DWORD bytesToWrite = 0;

//���ں�������
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void DrawGraphics(HDC hdc, POINTS begin, POINTS end, COLORREF penColor, SCRAWLTYPE type);
//��ں��� WinMain()
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	static TCHAR szAppName[] = TEXT("Hello windows");
	WNDCLASS wndclass;        //���崰����ṹ����
	HWND hwnd;                //���崰�ھ��
	MSG msg;                  //������Ϣ�ṹ����

	/********���崰���������*******/
	wndclass.style = CS_HREDRAW | CS_VREDRAW;       //�ı䴰�ڴ�С���ػ�
	wndclass.lpfnWndProc = WndProc;               //���ں���Ϊ  WndProc
	wndclass.cbClsExtra = 0;                      //����������չ
	wndclass.cbWndExtra = 0;                      //����ʵ������չ
	wndclass.hInstance = hInstance;               //ע�ᴰ�����ʵ�����
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //������Ĭ��ͼ��
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);   //�����ü�ͷ���
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //����Ϊ��ɫ
	wndclass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);                 //����Ĭ���޲˵�
	wndclass.lpszClassName = szAppName;


	if (!RegisterClass(&wndclass)) {
		MessageBox(NULL, TEXT("ע��ʧ�ܣ�"), szAppName, MB_ICONERROR);
		return -1;
	}
	
	HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));

	//��������
	/****�ӵ�һ��������ʼ����Chap1Exa1,ΪChap1Exa1,,���Ͻ���Ļ����,
	��Ⱥ͸߶�,,,�������ڵ�ʵ�����,�˴����޴�������****/
	hwnd = CreateWindow(szAppName,//��������
		szAppName,//������
		WS_OVERLAPPEDWINDOW,//�ص�ʽ���ڷ��
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,//ϵͳȱʡ������Ϳ�ȸ߶�
		NULL,//�����޸�����
		hMenu,//���������˵�
		hInstance,//ʵ�����
		NULL//�޴�������
		);
	g_hInst = hInstance;
	ShowWindow(hwnd, nCmdShow);              //��ʾ����
	UpdateWindow(hwnd);                     //���´��ڵĿͻ���

	//������Ϣѭ��
	while (GetMessage(&msg, NULL, 0, 0))        //��ȡ��Ϣ����WM_QUIT�˳�ѭ��
	{
		TranslateMessage(&msg);             //������Ϣת��
		DispatchMessage(&msg);              //������Ϣ�����ں���
	}
	return msg.wParam;

}

//���ں���
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;                     //�����豸��������
	PAINTSTRUCT ps;              //�����ͼ��Ϣ�ṹ����
	static std::vector<SCRAWL> save;
	static POINTS begin = { 0, 0 };
	static SCRAWLTYPE type = SCRAWLLINE;
	static COLORREF penColor = RGB(0, 0, 0);
	static TCHAR str[100] = _T("��ǰ���Ƶ���ֱ��(ֱ�߰�7�����ΰ�8����Բ��9����ɫR����ɫG����ɫB����ɫK)");
	static bool mousestate = false;
	HBRUSH oldBrush;
	static POINTS end = { 0, 0 };
	switch (message)                  //������Ϣֵת��Ӧ����Ϣ����
	{

	case WM_PAINT:                   //�ػ����ڿͻ�����Ϣ
		hdc = BeginPaint(hwnd, &ps);  //��ȡ���ػ����ڵ��豸��������
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
		EndPaint(hwnd, &ps);          //����Ҫ�ػ��Ĵ���

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
		wsprintf(str, _T("��ǰ���Ƶ���%s(ֱ�߰�7�����ΰ�8����Բ��9����ɫR����ɫG����ɫB����ɫK)"), typeText[type]);
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
	case  WM_DESTROY:                //����������Ϣ
		PostQuitMessage(0);          //�����˳�������ϢWM_QUIT
		return 0;

	case WM_COMMAND :
		switch (LOWORD(wParam))
		{
		case ID_HELP_ABOUT :
			MessageBox(NULL, TEXT("��ͼС����"), _T("˵����Ϣ"), MB_OK);
			break;

		case ID_FILE_SAVE :
			of.hwndOwner = hwnd;
			of.hInstance = g_hInst;
			of.lpstrFilter = _T("Ϳѻ�ļ�(*.pat)\0*.pat\0");
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
			of.lpstrFilter = _T("Ϳѻ�ļ�(*.pat)\0*.pat\0");
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
		wsprintf(str, _T("��ǰ���Ƶ���%s(ֱ�߰�7�����ΰ�8����Բ��9����ɫR����ɫG����ɫB����ɫK)"), typeText[type]);
		SetTextColor(hdc, penColor);
		TextOut(hdc, 0, 0, str, _tcslen(str));
		ReleaseDC(hwnd, hdc);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);//����תĬ�ϴ��ں���
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