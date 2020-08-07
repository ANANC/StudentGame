#include"CMyGame.h"

GameChapter *GameChapter::instance = NULL;
GameResource *GameResource::instance = NULL;

CMyGame::CMyGame(HINSTANCE hInstance, HWND hWnd, int nFps) :CGame(hInstance,hWnd, nFps)
{
	InitGame();
}

CMyGame::~CMyGame()
{
	pXAudio2SoundPlayerp->~XAudio2SoundPlayer();
	delete pGameChapter->GetInstance();
}

void CMyGame::InitGame()
{
	GameResource *pGameResource = NULL;
	pGameResource = GameResource::GetInstance();

	CNSpritesManager *pSpritesManager = NULL;
	pSpritesManager = CNSpritesManager::GetInstance();

	pGameChapter = GameChapter::GetInstance();
	pGameChapter->InitGame();
	
	pCursor = pSpritesManager->CreateNSprite(TEXT("cursor"), D2D1::Point2F(0, 0));
	StartpCursor = { 0,0 };

	/*������Ч*/
	pXAudio2SoundPlayerp = new XAudio2SoundPlayer();
	pXAudio2SoundPlayerp->LoadSound(TEXT("resource\\A.wav"));
	pXAudio2SoundPlayerp->PlaySound(pXAudio2SoundPlayerp->GetSoundCount());

	//ShowCursor(false);
}

void CMyGame::Update(float fDeltaTime)
{
	//CGame::Update(fDeltaTime);
	CNSpritesManager::GetInstance()->Update(fDeltaTime);
	pGameChapter->UpdateGame();
	GetCMouse();//������λ��

	//��������
	PlayingSound();
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
		pGameChapter->RenderGame();
	}


	pRenderTarget->EndDraw();

}

void CMyGame::Cleanup()
{
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
	D2D1_POINT_2F p = pCursor->GetPos();
	p.x += /*StartpCursor.x + */pInput->GetMouseX();
	p.y +=/* StartpCursor.y +*/ pInput->GetMouseY();
	pCursor->SetPos(p);

	if (!IsLButtonPressed())
		return;
	pGameChapter->GetMClickPoint(p.x+20, p.y+10);
	pGameChapter->MouseClick();
	
	if (p.x>638|| p.x<0 ||p.y>518 || p.y<0)
		pInput->resetMouseCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	else
		pInput->resetMouseCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	
	//GetCursorPos(&CMouse);            // ��ȡ���ָ��λ�ã���Ļ���꣩
	//ScreenToClient(hWnd, &CMouse);
	//pGameChapter->GetMClickPoint(CMouse.x, CMouse.y);
	//pGameChapter->MouseClick();
}

void CMyGame::PlayingSound()
{
	if (pXAudio2SoundPlayerp->IsSoundPlaying(pXAudio2SoundPlayerp->GetSoundCount()) == false)
		pXAudio2SoundPlayerp->PlaySoundW(pXAudio2SoundPlayerp->GetSoundCount());
}