#include"CMyGame.h"

GameChapter *GameChapter::instance = NULL;
GameResource *GameResource::instance = NULL;

CMyGame::CMyGame(HINSTANCE hInstance, HWND hWnd, int nFps) :CGame(hInstance,hWnd, nFps)
{
	InitGame();
}

CMyGame::~CMyGame()
{
	delete pGameChapter->GetInstance();
}

void CMyGame::InitGame()
{
	GameResource *pGameResource = NULL;
	pGameResource = GameResource::GetInstance();

	pGameChapter = GameChapter::GetInstance();
	pGameChapter->InitGame();
}

void CMyGame::Update(float fDeltaTime)
{
	//CGame::Update(fDeltaTime);
	CNSpritesManager::GetInstance()->Update(fDeltaTime);
	pGameChapter->UpdateGame();
	GetCMouse();//获得鼠标位置

	/*笔刷*/
	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White, 1.0f), &pBrush);
}

void CMyGame::Render()
{
	if (NULL == pRenderTarget)
		return;


	pRenderTarget->BeginDraw();
	pRenderTarget->Clear(D2D1::ColorF(0x0, 1.0f));

	pSpritesManager = CNSpritesManager::GetInstance();
	if (pSpritesManager)
	{
		pSpritesManager->Render();
	}
	if (t > 0)
	{
		pGameChapter->RenderGame(pRenderTarget, pTextFormat, pTextBrush,pBrush);
	}


	pRenderTarget->EndDraw();

}

void CMyGame::Cleanup()
{
	SafeRelease(&pBrush);
	CGame::Cleanup();
}

//void CMyGame::GetCMouse(HWND hwnd)
//{

//static int x = 0;
//static int y = 0;
//
//static bool isFirst = true;
//if (isFirst){
//	GetCursorPos(&CMouse);            // 获取鼠标指针位置（屏幕坐标）
//	ScreenToClient(hwnd, &CMouse);    
//	x = CMouse.x;
//	y = CMouse.y;
//	isFirst = false;
//}
//IsLButtonPressed();
//x += pInput->getMouseX();
//y += pInput->getMouseY();



//	//消息过多导致崩溃，不知道应该怎么改
//	//if (IsLButtonPressed())
//	//{
//	//	CMouse.x = pInput->GetLClickX();
//	//	CMouse.y = pInput->GetLClickY();
//	//	pGameChapter->GetMClickPoint(CMouse.x, CMouse.y);
//	//}
//
//	//位置貌似有偏差
//	GetCursorPos(&CMouse);            // 获取鼠标指针位置（屏幕坐标）
//	ScreenToClient(hwnd, &CMouse);    // 将鼠标指针位置转换为窗口坐标
//	pGameChapter->GetMClickPoint(CMouse.x, CMouse.y);
//
//}

void CMyGame::GetCMouse()
{
	//CMouse.x = LOWORD(lParam);
	//CMouse.y = HIWORD(lParam);
	//pGameChapter->GetMClickPoint(CMouse.x, CMouse.y);
	//pGameChapter->MouseClick();

	//位置获取有问题
	//static bool isFirst = true;
	//if (isFirst)
	//{
	//	GetCursorPos(&CMouse);            // 获取鼠标指针位置（屏幕坐标）
	//	ScreenToClient(hWnd, &CMouse);
	//	isFirst = false;
	//}
	//if (IsLButtonPressed())
	//{
	//	CMouse.x += pInput->GetMouseX();
	//	CMouse.y += pInput->GetMouseY();
	//	pGameChapter->GetMClickPoint(CMouse.x, CMouse.y);
	//	pGameChapter->MouseClick();
	//}


	if (!IsLButtonPressed())
		return;
	GetCursorPos(&CMouse);            // 获取鼠标指针位置（屏幕坐标）
	ScreenToClient(hWnd, &CMouse);
	pGameChapter->GetMClickPoint(CMouse.x, CMouse.y);
	pGameChapter->MouseClick();
}