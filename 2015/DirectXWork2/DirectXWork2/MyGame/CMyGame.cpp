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
	GameP = PGameStart;//��Ϸ״̬
	pCGameScene = GameScene::GetInstance();//������
	pCGameStart = new CGameStart();//��ʼ����
	pCGameSelect = CGameSelect::GetInstance();//ѡ�ؽ���
	pCGameHinder = CGameHinder::GetInstance();//�谭
	pCGamePeople = CGamePeople::GetInstance();//����
	pCGamePlay = CGamePlay::GetInstance();//��Ϸ����
	pCGameTime = CGameTime::GetInstance();//��ʱ��
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

	pRenderTarget->Clear(D2D1::ColorF(0x343131, 1.0f));//�����޸��˱�����ɫ

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
	GetCursorPos(&Cpoint);            // ��ȡ���ָ��λ�ã���Ļ���꣩
	ScreenToClient(hWnd, &Cpoint);    // �����ָ��λ��ת��Ϊ��������
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
	GetCursorPos(&Mpoint);            // ��ȡ���ָ��λ�ã���Ļ���꣩
	ScreenToClient(hWnd, &Mpoint);    // �����ָ��λ��ת��Ϊ��������
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