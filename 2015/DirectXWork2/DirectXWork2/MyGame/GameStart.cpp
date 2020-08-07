#include"GameStart.h"


CGameStart::~CGameStart()
{
}


CGameStart::CGameStart() 
{
	pCGameScene = GameScene::GetInstance();
	pCGameScene->GetGameStart(&GameStart);
	pCGameScene->GetGamePass(GamePass);

	GameStart->SetPos(D2D1::Point2F(0, 0));
	GameStart->Play();

	rGameStart = { 378, 120, 473, 145 };//开始的框
	IsSelectGameStart = false;//是否接触
}

void CGameStart::SelectGameStrat()
{
	if (pCGameScene->GetCpoint().x >= rGameStart.left&&pCGameScene->GetCpoint().x <= rGameStart.right&&
		pCGameScene->GetCpoint().y >= rGameStart.top&&pCGameScene->GetCpoint().y <= rGameStart.bottom)
	{
		GameStart->SetVisible(false);
		GameStart->Stop();
		for (int i = 0; i < 8; i++)
		{
			GamePass[i]->SetVisible(true);
		}
		pCGameScene->SetGameP(PGameSelect);//更改游戏状态-进入选关状态
	}
}

void CGameStart::MoveGameStrat()
{
	if (pCGameScene->GetMpoint().x >= rGameStart.left&&pCGameScene->GetMpoint().x <= rGameStart.right&&
		pCGameScene->GetMpoint().y >= rGameStart.top&&pCGameScene->GetMpoint().y <= rGameStart.bottom)
		IsSelectGameStart = true;
	else
		IsSelectGameStart = false;
}

void CGameStart::GameStartPlay()
{
	static bool IsSelectRect = false;
	if (IsSelectGameStart && !IsSelectRect)
	{
		int h = GameStart->GetHeight();
		GameStart->SetTexturePos(0, h);
		GameStart->Play();
		IsSelectRect = true;
	}
	else if (!IsSelectGameStart)
	{
		GameStart->SetTexturePos(0, 0);
		IsSelectRect = false;
	}
}