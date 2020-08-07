#include"GamePlay.h"
#define KEY_SHIFT  (GetKeyState(VK_SHIFT) & 0x80)>0 ? true : false
#define KEY_CTRL  (GetKeyState(VK_ESCAPE) & 0x80)>0 ? true : false

CGamePlay::~CGamePlay()
{
}

CGamePlay::CGamePlay()
{
	pCGameScene = GameScene::GetInstance();
	
	pCGameScene->GetHinder(Hinder);
	pCGameScene->GetGamePass(GamePass);
	pCGameScene->GetPeople(&People);
	pCGameScene->GetGameScreen(&GameScreen);
	pCGameScene->GetGFood(GFood);
	pCGameScene->GetAgain(&Again);
	pCGameScene->GetBack(&Back);
	pCGameScene->GetFail(&Fail);
	pCGameScene->GetSuccess(&Success);

	/*游戏界面*/
	GameScreen->SetPos(D2D1::Point2F(0, 0));
	GameScreen->SetVisible(false);

	/*道具*/
	Fail->SetPos(D2D1::Point2F(690, 25));
	Success->SetPos(D2D1::Point2F(710, 25));
	for (int i = 0; i < 3; i++)
	{
		GFood[i]->SetVisible(false);
	}
	Again->SetPos(D2D1::Point2F(775,20));
	Back->SetPos(D2D1::Point2F(775 + Again->GetWidth() + 10, 20));

	Again->SetVisible(false);
	Back->SetVisible(false);
	Fail->SetVisible(false);
	Success->SetVisible(false);

	

	oldPos = { People->GetPos().x + People->GetWidth() / 2-50, People->GetPos().y-50 };
	World = D2D1::Matrix3x2F::Identity();
}

void CGamePlay::Restart()
{
	pCGamePeople = CGamePeople::GetInstance();
	pCGameHinder = CGameHinder::GetInstance();//阻碍
	pCGameTime = CGameTime::GetInstance();

	if (Again->IsSelected(pCGameScene->GetCpoint().x, pCGameScene->GetCpoint().y) || IsRestart())
	{
		/*道具的初始化*/
		FoodFirst();
		for (int i = 0; i < 3; i++)
			GFood[i]->SetVisible(true);

		/*人物的初始化*/
		pCGamePeople->PeoFirst();

		/*障碍的初始化*/
		pCGameHinder->HinderErase();
		pCGameHinder->HinderShow_static();//静态障碍
		pCGameHinder->HinderCreate();//动态障碍

		/*计时器的初始化*/
		pCGameTime->TimeFirst();

		pCGameScene->SetGameP(PGamePlaying);
		Success->SetVisible(false);
		Fail->SetVisible(false);

		if (Again->IsSelected(pCGameScene->GetCpoint().x, pCGameScene->GetCpoint().x))
			pCGameScene->MouseCSide({ 0, 0 });
	}
}

void CGamePlay::Return()
{
	if (Back->IsSelected(pCGameScene->GetCpoint().x, pCGameScene->GetCpoint().y) || IsGOver())
	{
		/*选关可见*/
		for (int i = 0; i < 8; i++)
			GamePass[i]->SetVisible(true);

		/*人物，障碍，道具不可见*/
		GameScreen->SetVisible(false);//地图
		GameScreen->Stop();
		Again->SetVisible(false);//重玩
		Back->SetVisible(false);//返回
		Fail->SetVisible(false);//失败
		Success->SetVisible(false);//成功
		for (int i = 0; i < 3; i++)
			GFood[i]->SetVisible(false);//食物
		People->SetVisible(false);//人物
		People->Stop();//人物动画不播放
		pCGameHinder->HinderErase();//障碍

		/*修改游戏状态*/		
		pCGameScene->SetGameP(PGameSelect);//进入游戏选关状态
		pCGameSelect->ChangePass();//改变选关效果


		if (Again->IsSelected(pCGameScene->GetCpoint().x, pCGameScene->GetCpoint().y))
			pCGameScene->MouseCSide({ 0, 0 });
	}
}

void CGamePlay::MoveReturn()
{
	if (Back->IsSelected(pCGameScene->GetMpoint().x, pCGameScene->GetMpoint().y))
	{
		int x = Back->GetWidth();
		Back->SetTexturePos(x, 0);
		IsMoveReturn = true;
	}
	else
	{
		Back->SetTexturePos(0, 0);
		IsMoveReturn = false;
	}
}

void CGamePlay::MoveRestart()
{
	if (Again->IsSelected(pCGameScene->GetMpoint().x, pCGameScene->GetMpoint().y))
	{
		int x = Again->GetWidth();
		Again->SetTexturePos(x, 0);
		IsMoveRestart = true;
	}
	else
	{
		Again->SetTexturePos(0, 0);
		IsMoveRestart = false;
	}
}

void CGamePlay::IsMoveInRestart(ID2D1HwndRenderTarget *pRenderTarget, IDWriteTextFormat *pTextFormat, ID2D1SolidColorBrush *pTextBrush)
{
	TCHAR szBuffer[15];
	int iLength;
	D2D1_RECT_F textRect;
	if (IsMoveRestart)
	{
		iLength = wsprintf(szBuffer, TEXT("shift"));
		textRect = { 745, 50, 745+100, 50+15 };
	}
	else
	{
		iLength = wsprintf(szBuffer, TEXT(""));
		textRect = { 745, 50, 745 + 100, 50 + 15 };
	}
	pRenderTarget->DrawText(szBuffer, iLength, pTextFormat, textRect, pTextBrush);
}

void CGamePlay::IsMoveInReturn(ID2D1HwndRenderTarget *pRenderTarget, IDWriteTextFormat *pTextFormat, ID2D1SolidColorBrush *pTextBrush)
{
	TCHAR szBuffer[15];
	int iLength;
	D2D1_RECT_F textRect;
	if (IsMoveReturn)
	{
		iLength = wsprintf(szBuffer, TEXT("control"));
		textRect = { 782, 50, 782+100, 50+15 };
	}
	else
	{
		iLength = wsprintf(szBuffer, TEXT(""));
		textRect = { 782, 50, 782 + 100, 50 + 15 };
	}
	pRenderTarget->DrawText(szBuffer, iLength, pTextFormat, textRect, pTextBrush);

}



void CGamePlay::GameOver()
{
	Fail->SetVisible(true);//可见
	GameScreen->SetTexturePos(0, 567 * 4);
	People->Stop();
	for (int i = 0; i < HinderNum[1]; i++)
		Hinder[1][i]->Stop();

	pCGameScene->SetGameP(PGamePlayFail);;//游戏结束
}

void CGamePlay::GameSuccess(int i)
{
	/*放置图片*/
	Success->SetVisible(true);//可见

	/*设置关卡状态*/
	pCGameSelect->SetGamePass(i);//设置通关关卡

	/*记录时间*/
	//pCGameTime->SetGameTime();

	People->Stop();
	for (int i = 0; i < HinderNum[1]; i++)
		Hinder[1][i]->Stop();

	pCGameScene->SetGameP(PGamePlayWin);//游戏结束//改变状态
}

void CGamePlay::SetFood()
{
	srand((unsigned)time(NULL));
	int RR[3];
	RR[2] = rand() % 23;
	if (RR[2] == 3 || RR[2] == 4 || RR[2] == 6)
		RR[2] += 4;
	if (RR[2] == 0 || RR[2] == 9 || RR[2] == 12 || RR[2] == 19 || RR[2] == 21)
		RR[2] += 2;
	for (int i = 1; i >= 0; i--)
	{
		RR[i] = RR[i + 1] - 50;
	}

	for (int i = 0; i < 3; i++)
	{
		World = D2D1::Matrix3x2F::Identity();
		World = World * D2D1::Matrix3x2F::Translation(oldPos.x, oldPos.y);
		World = World * D2D1::Matrix3x2F::Rotation(RR[i], D2D1::Point2F(425.5f, 284));
		D2D1_POINT_2F wp = { 0, 0 };
		wp = World.TransformPoint(wp);
		GFood[i]->SetPos(wp);
		GFood[i]->SetRotationAngle(RR[i]);
	}
	
}

void CGamePlay::GetFood()
{
	RECT *rtIntersect= (RECT *)People->GetBoundingBox();
	for (int i = 0; i < 3; i++)
	{
		if (IsGetFood[i])
			continue;

		if (GFood[i]->CSprite::CollideWith(*rtIntersect))
		{
			GFood[i]->SetVisible(false);
			IsGetFood[i] = true;
			FoodNumber += 1;
		}
	}
	if (FoodNumber)
		GameScreen->SetTexturePos(0, 567 * FoodNumber);

	if (FoodNumber == 3)//游戏胜利
		GameSuccess(pCGameSelect->GetGameMunber());


}

void CGamePlay::FoodFirst()
{
	/*设置数量和地图的初始化*/
	for (int i = 0; i < 3; i++)
		IsGetFood[i] = { false };
	FoodNumber = 0;
	GameScreen->SetTexturePos(0, 567 * FoodNumber);

	//放置图片
	SetFood();

	pCGameSelect = CGameSelect::GetInstance();//选关界面
}

bool CGamePlay::IsRestart()
{
	if (KEY_SHIFT)
		return true;
}

bool CGamePlay::IsGOver()
{
	if (KEY_CTRL)
		return true;
}