#include "CMyGame.h"

POINT GameScene::Mpoint = { 0, 0 };
POINT GameScene::Cpoint = { 0, 0 };
GameScene *GameScene::instance = NULL;
CGamePeople *CGamePeople::instance = NULL;
CGameHinder *CGameHinder::instance = NULL;
CGameSelect *CGameSelect::instance = NULL;
CGamePlay *CGamePlay::instance = NULL;
CGameTime *CGameTime::instance = NULL;

CDemoGame::CDemoGame(HWND hWnd, int nFps) :CGame(hWnd, nFps)
{
	this->hWnd = hWnd;
	this->nFps = nFps;
}
CDemoGame::~CDemoGame(void)
{
	
}

void CDemoGame::InitGame()
{
	GameP = PGameStart;//游戏状态
	pCGameScene = GameScene::GetInstance();//场景类
	pCGameStart = new CGameStart();//开始场景
	pCGameSelect = CGameSelect::GetInstance();//选关界面
	pCGameHinder = CGameHinder::GetInstance();//阻碍
	pCGamePeople = CGamePeople::GetInstance();//人物
	pCGamePlay = CGamePlay::GetInstance();//游戏场景
	pCGameTime = CGameTime::GetInstance();//计时器
}

void CDemoGame::Update(float fDeltaTime)
{
	CGame::Update(fDeltaTime);
	GameP = pCGameScene->GetGameP();
	switch (GameP)
	{
	case PGameStart:
		pCGameStart->GameStartPlay();
		break;

	case PGameSelect:
		pCGameSelect->MoveChangeGamePass();
		break;

	case PGamePlaying:
		pCGamePeople->PeoMove(fDeltaTime);
		pCGameTime->TimerUpdate(fDeltaTime);
		pCGameHinder->HinderMove();
		pCGameHinder->HinderTouch(fDeltaTime);
		pCGamePlay->GetFood();
		/*pCGamePlay->IsRestart();
		pCGamePlay->IsGOver();*/
		//pCGamePlay->Restart();
		break;

	case PGamePlayWin:
		pCGameTime->TimerUpdate(fDeltaTime);
		pCGamePlay->Restart();
		pCGamePlay->Return();
		break;

	case PGamePlayFail:
		pCGameTime->TimerUpdate(fDeltaTime);
		pCGamePlay->Restart();
		pCGamePlay->Return();
		break;
	}
}

void CDemoGame::Render()
{
	if (NULL == pRenderTarget)
		return;

	pRenderTarget->BeginDraw();
	//CGame::Render();

	pRenderTarget->Clear(D2D1::ColorF(0x343131, 1.0f));//这里修改了背景颜色

	pSpritesManager = CSpritesManager::GetInstance();
	if (pSpritesManager)
	{
		pSpritesManager->Render();
	}
	Matrix3x2F World= D2D1::Matrix3x2F::Identity();
	if (t > 0)
	{
		switch (GameP)
			{
			case PGameStart:

				break;

			case PGameSelect:
				pCGameSelect->SetTip(pRenderTarget, pTextFormat, pTextBrush);
		
				break;

			case PGamePlaying:
				pCGamePeople->ShowPeoMove(pRenderTarget);

				pRenderTarget->SetTransform(World);

				pCGamePlay->IsMoveInRestart(pRenderTarget, pTextFormat, pTextBrush);
				pCGamePlay->IsMoveInReturn(pRenderTarget, pTextFormat, pTextBrush);
				pCGameTime->TimerShow(pRenderTarget, pTextFormat, pTextBrush);
				break;

			case PGamePlayWin:
				pRenderTarget->SetTransform(World);
				pCGameTime->TimerShow(pRenderTarget, pTextFormat, pTextBrush);
				break;

			case PGamePlayFail:
				pRenderTarget->SetTransform(World);
				pCGameTime->TimerShow(pRenderTarget, pTextFormat, pTextBrush);
				break;
			}
	}
	
	pRenderTarget->EndDraw();
}

void CDemoGame::MouseCSide()
{
	POINT Cpoint;
	GetCursorPos(&Cpoint);            // 获取鼠标指针位置（屏幕坐标）
	ScreenToClient(hWnd, &Cpoint);    // 将鼠标指针位置转换为窗口坐标
	GameScene::MouseCSide(Cpoint);


	switch (GameP)
	{
	case PGameStart:
		pCGameStart->SelectGameStrat();
		break;

	case PGameSelect:
		pCGameSelect->SelectGamePass();
		break;

	case PGamePlaying:
		pCGamePlay->Restart();
		pCGamePlay->Return();
		break;

	case PGamePlayWin:
		pCGamePlay->Restart();
		pCGamePlay->Return();
		break;

	case PGamePlayFail:
		pCGamePlay->Restart();
		pCGamePlay->Return();
		break;
	}
}

void CDemoGame::MouseSide()
{
	POINT Mpoint;
	GetCursorPos(&Mpoint);            // 获取鼠标指针位置（屏幕坐标）
	ScreenToClient(hWnd, &Mpoint);    // 将鼠标指针位置转换为窗口坐标
	GameScene::MouseSide(Mpoint);

	switch (GameP)
	{
	case PGameStart:
		pCGameStart->MoveGameStrat();
		break;

	case PGameSelect:
		pCGameSelect->MoveGamePass();
		break;

	case PGamePlaying:
		pCGamePlay->MoveReturn();
		pCGamePlay->MoveRestart();
		break;

	case PGamePlayWin:
		pCGamePlay->MoveReturn();
		pCGamePlay->MoveRestart();
		break;

	case PGamePlayFail:
		pCGamePlay->MoveReturn();
		pCGamePlay->MoveRestart();
		break;
	}
}