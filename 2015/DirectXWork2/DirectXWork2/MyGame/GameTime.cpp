#include"GameTime.h"

#include "GameSelect.h"
CGameTime::~CGameTime()
{
}

CGameTime::CGameTime()
{
	pCGameScene = GameScene::GetInstance();

	GameTime_min = 0;//分
	GameTime_sec = 0;//秒
	GameTime_msec = 0;//毫秒
	int  fD = 0;//计时器
	/*失败*/
}

void CGameTime::TimerUpdate(float fDeltaTime)
{
	fD += fDeltaTime;


	if (pCGameScene->GetGameP() == PGamePlayWin)
	{
		//pCGameSelect->SetGameTime(pCGameSelect->GetGameMunber(), GameTime_min, GameTime_sec);
		pCGameSelect->SetGameTime(pCGameSelect->GetGameMunber(), GameTime_min + GameTime_sec *0.01);
		return;
	}

	//if (pCGameScene->GetGameP() == PGamePlayFail)
	//{
	//	return;
	//}

	if (pCGameScene->GetGameP() == PGamePlaying)
	{
		if (fD % 60 == 0)
		{
			GameTime_msec++;
			if (GameTime_msec == 60)
			{
				GameTime_sec++;
				GameTime_msec = 0;
			}
			if (GameTime_sec == 60)
			{
				GameTime_min++;
				GameTime_sec = 0;
			}
			fD = 0;
		}
	}

}

void CGameTime::TimeFirst()
{
	GameTime_msec = 0;
	GameTime_sec = 0;
	GameTime_min = 0;
	fD = 0;


	pCGameSelect = CGameSelect::GetInstance();
}

void CGameTime::TimerShow(ID2D1HwndRenderTarget *pRenderTarget, IDWriteTextFormat *pTextFormat, ID2D1SolidColorBrush *pTextBrush)
{
	TCHAR szBuffer[15];
	int iLength;
	D2D1_RECT_F textRect;
	if (pCGameScene->GetGameP() == PGamePlaying)
	{
		iLength = wsprintf(szBuffer, TEXT("时间：%d.%d.%d"), GameTime_min, GameTime_sec, GameTime_msec);
	}
	else
	{
			int m = GameTime_min;
			int s = GameTime_sec ;
			iLength = wsprintf(szBuffer, TEXT("用时：%d分%d秒"), m, s);
	}
	textRect = { 10, 15, 10 + 100, 15 + 15 };
	pRenderTarget->DrawText(szBuffer, iLength, pTextFormat, textRect, pTextBrush);
}