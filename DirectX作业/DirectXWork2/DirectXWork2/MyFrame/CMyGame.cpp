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
	GetCMouse();//������λ��

	/*��ˢ*/
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
//	GetCursorPos(&CMouse);            // ��ȡ���ָ��λ�ã���Ļ���꣩
//	ScreenToClient(hwnd, &CMouse);    
//	x = CMouse.x;
//	y = CMouse.y;
//	isFirst = false;
//}
//IsLButtonPressed();
//x += pInput->getMouseX();
//y += pInput->getMouseY();



//	//��Ϣ���ർ�±�������֪��Ӧ����ô��
//	//if (IsLButtonPressed())
//	//{
//	//	CMouse.x = pInput->GetLClickX();
//	//	CMouse.y = pInput->GetLClickY();
//	//	pGameChapter->GetMClickPoint(CMouse.x, CMouse.y);
//	//}
//
//	//λ��ò����ƫ��
//	GetCursorPos(&CMouse);            // ��ȡ���ָ��λ�ã���Ļ���꣩
//	ScreenToClient(hwnd, &CMouse);    // �����ָ��λ��ת��Ϊ��������
//	pGameChapter->GetMClickPoint(CMouse.x, CMouse.y);
//
//}

void CMyGame::GetCMouse()
{
	//CMouse.x = LOWORD(lParam);
	//CMouse.y = HIWORD(lParam);
	//pGameChapter->GetMClickPoint(CMouse.x, CMouse.y);
	//pGameChapter->MouseClick();

	//λ�û�ȡ������
	//static bool isFirst = true;
	//if (isFirst)
	//{
	//	GetCursorPos(&CMouse);            // ��ȡ���ָ��λ�ã���Ļ���꣩
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
	GetCursorPos(&CMouse);            // ��ȡ���ָ��λ�ã���Ļ���꣩
	ScreenToClient(hWnd, &CMouse);
	pGameChapter->GetMClickPoint(CMouse.x, CMouse.y);
	pGameChapter->MouseClick();
}