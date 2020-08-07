#include"GameChapter.h"

GWaterManager *GWaterManager::instance = NULL;

GameChapter::GameChapter()
{
	CResourcesPool *pResPool = NULL;
	pResPool = CResourcesPool::GetInstance();
	CNSpritesManager *pSpritesManager = NULL;
	pSpritesManager = CNSpritesManager::GetInstance();

	/*背景*/
	D2D1_SIZE_F Size = pResPool->GetResource(TEXT("Background"))->pTexture->GetSize();
	int w = Size.width/2, h = Size.height ;
	pBackground = pSpritesManager->CreateAnimationSprite(TEXT("Background"),2,2, D2D1::Point2F(0, 0), w, h);
	pBackground->SetTexPos(w, 0);
	/*水滴总量*/
	Size = pResPool->GetResource(TEXT("Number"))->pTexture->GetSize();
	w = Size.width / 10; h = Size.height;
	pWaterNumberWaH.x = w;
	pWaterNumberWaH.y = h;
	pWaterNumber[0] = pSpritesManager->CreateAnimationSprite(TEXT("Number"),10,2, D2D1::Point2F(480, 105), w, h);
	pWaterNumber[1] = pSpritesManager->CreateAnimationSprite(TEXT("Number"), 10, 2, D2D1::Point2F(526, 105), w, h);
	/*当前关卡*/
	Size = pResPool->GetResource(TEXT("Number"))->pTexture->GetSize();
	w = Size.width / 10; h = Size.height;
	pChapterNumberWaH.x = w;
	pChapterNumberWaH.y = h;
	pChapterNumber[0] = pSpritesManager->CreateAnimationSprite(TEXT("Number"), 10, 2, D2D1::Point2F(511, 312), w, h);
	pChapterNumber[1] = pSpritesManager->CreateAnimationSprite(TEXT("Number"), 10, 2, D2D1::Point2F(549, 312), w, h);
	pChapterNumber[0]->SetScaleFactor(0.8, 0.8);
	pChapterNumber[1]->SetScaleFactor(0.8, 0.8);
	/*最高关卡*/
	Size = pResPool->GetResource(TEXT("Number"))->pTexture->GetSize();
	w = Size.width / 10; h = Size.height;
	pMaxChapterNumberWaH.x = w;
	pMaxChapterNumberWaH.y = h;
	pMaxChapterNumber[0] = pSpritesManager->CreateAnimationSprite(TEXT("Number"), 10, 2, D2D1::Point2F(553, 290), w, h);
	pMaxChapterNumber[1] = pSpritesManager->CreateAnimationSprite(TEXT("Number"), 10, 2, D2D1::Point2F(567, 290), w, h);
	pMaxChapterNumber[0]->SetScaleFactor(0.3, 0.3);
	pMaxChapterNumber[1]->SetScaleFactor(0.3, 0.3);
	/*胜利*/
	Size = pResPool->GetResource(TEXT("win"))->pTexture->GetSize();
	w = Size.width /3; h = Size.height;
	pWin = pSpritesManager->CreateAnimationSprite(TEXT("win"), 3, 2, D2D1::Point2F(0, 0), w, h);
	pWin->SetVisible(false);
	/*失败*/
	Size = pResPool->GetResource(TEXT("fail"))->pTexture->GetSize();
	w = Size.width / 3; h = Size.height;
	pFail = pSpritesManager->CreateAnimationSprite(TEXT("fail"), 3, 2, D2D1::Point2F(0, 0), w, h);
	pFail->SetVisible(false);

	pGWaterManager = GWaterManager::GetInstance();

	/*场景音效*/
	pPassOrFailMusic = new XAudio2SoundPlayer();
	pPassOrFailMusic->LoadSound(TEXT("resource\\过.wav"));

	//初始化数据	
	ChapterNumber = 1;
	MaxChapterNumber = 1;
	LitterNumber = EasyL;
	MiddleNumber1 = EasyM1;
	MiddleNumber2 = EasyM2;
	BigNumber = EasyB;
	WaterNumber = 10;
	GProgress = PGamePlaying;

	MClickPoint = { -1, -1 };

	offset = 472;
	SelectNewGame = { 311,54,498,264};
	IsSelectNewGame = false;
	SelectNextGame = { 415,32, 462,207};
	IsSelectNextGame = false;

	//读取游戏保存信息
	GameRead();

	//初始化
	InitGame();
}

GameChapter::~GameChapter()
{
	GameKeep();//保存进度
}

void GameChapter::InitGame()
{
	pWin->SetVisible(false);
	pFail->SetVisible(false);
	pBackground->SetTexPos(pBackground->GetWidth(), 0);

	//使水滴可见
	pGWaterManager->SetWatersVisible(true);
	//初始化水滴
	pGWaterManager->Init();
	//初始化水滴状态 
	pGWaterManager->InitWprocession(LitterNumber, MiddleNumber1, MiddleNumber2, BigNumber);

}

void GameChapter::UpdateGame()
{
	switch (GProgress)
	{
	case PGamePlaying:
		SetWaterNumber();
		pGWaterManager->WaterTouch();
		IsChangeGameProgress();
		break;

	case PGameWin:
		GameSuccess();
		break;

	case PGameOver:
		GameOver();
		break;
	}
}

void GameChapter::SetWaterNumber(int i)
{
	WaterNumber += pGWaterManager->GetAddWNumber();
	pGWaterManager->SetAddWNumber(0);

	if (i != 0)
	{
		WaterNumber += i;
	}
}

void GameChapter::MouseClick()
{
	//判断是否在游戏盘上-还没写
	if (MClickPoint.x < offset && GProgress == PGamePlaying)
	{
		pGWaterManager->MClick(MClickPoint);
	}

	if (GProgress == PGameOver)
	{
		//判断是否点击选择新游戏
		if (MClickPoint.x > SelectNewGame.left && MClickPoint.x<SelectNewGame.right
			&& MClickPoint.y>SelectNewGame.top && MClickPoint.y < SelectNewGame.bottom)
			IsSelectNewGame = true;
	}

	if (GProgress == PGameWin)
	{
		//判断是否点击选择下一关
		if (MClickPoint.x > SelectNextGame.left && MClickPoint.x<SelectNextGame.right
			&& MClickPoint.y>SelectNextGame.top && MClickPoint.y < SelectNextGame.bottom)
			IsSelectNextGame = true;
	}
}

void GameChapter::GameSuccess()
{		
	if (IsSelectNextGame)
	{
		//增加一滴水滴
		SetWaterNumber(1);

		//当前关卡数加一
		ChapterNumber += 1;

		//更新最高关卡
		if (MaxChapterNumber <= ChapterNumber)
			MaxChapterNumber = ChapterNumber;

		//修改难度
		Changedifficulty();

		//初始化游戏
		InitGame();

		IsSelectNextGame = false;

		//改变游戏状态
		GProgress = PGamePlaying;
	}
	
}

void GameChapter::IsChangeGameProgress()
{
	if (WaterNumber <= 0 && pGWaterManager->IsHaveSmallWaters() == false)
	{
		GProgress = PGameOver;
		return;
	}
	
	if (pGWaterManager->IsAllNothing())
		GProgress = PGameWin;
}

void GameChapter::GameOver()
{
	//选择新游戏
	if (IsSelectNewGame)
	{
		//初始化数值
		ChapterNumber = 1;
		LitterNumber = EasyL;
		MiddleNumber1 = EasyM1;
		MiddleNumber2 = EasyM2;
		BigNumber = EasyB;
		WaterNumber = 10;

		//新游戏初始化
		MClickPoint = { -1,-1 };
		IsSelectNewGame = false;
		
		//初始化游戏
		InitGame();
		
		//状态值的改变
		GProgress = PGamePlaying;
	}
}

void GameChapter::Changedifficulty()
{
	int k = ChapterNumber /5;
	while (k > 1)
	{
		if (DifficultL > LitterNumber)
			LitterNumber++;
		if (DifficultM1 > MiddleNumber1)
			MiddleNumber1++;
		if (DifficultM2 > MiddleNumber2)
			MiddleNumber2++;
		if (BigNumber> DifficultB)
			BigNumber--;
		k -= 1;
	}
}

void GameChapter::GameKeep()
{
	HANDLE pfile;
	TCHAR filename[] = TEXT("GameInformation.txt");

	pfile = CreateFile(filename,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

	//游戏失败：保存关卡，其他状态：保持关卡和水滴	
	if (GProgress == PGameOver)
		WaterNumber = 10;//把水滴初始值

	DWORD readsize;
	sGameKeep sGK = { ChapterNumber, MaxChapterNumber, WaterNumber };
	WriteFile(pfile, &sGK, sizeof(sGameKeep), &readsize, NULL);
	////保存关卡-当前关卡
	//WriteFile(pfile, &ChapterNumber, sizeof(int), &readsize, NULL);
	////保存关卡-最高关卡
	//WriteFile(pfile, &MaxChapterNumber, sizeof(int), &readsize, NULL);
	////保存水滴容量
	//WriteFile(pfile, &WaterNumber, sizeof(int), &readsize, NULL);
}

void GameChapter::GameRead()
{
	HANDLE pfile;
	TCHAR filename[] = TEXT("GameInformation.txt");

	pfile = CreateFile(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	if (pfile == INVALID_HANDLE_VALUE)
	{
		//MessageBox(NULL, L"打开文件失败", L"Error", MB_OK);
		CloseHandle(pfile);        //一定注意在函数退出之前对句柄进行释放。
		return;
	}

	DWORD readsize;
	sGameKeep sGK ;
	ReadFile(pfile, &sGK, sizeof(sGameKeep), &readsize, NULL);
	ChapterNumber = sGK.sChapterNumber;
	MaxChapterNumber = sGK.sMaxChapterNumber;
	WaterNumber = sGK.sWaterNumber;
	////读取关卡-当前关卡
	//ReadFile(pfile, &ChapterNumber, sizeof(int), &readsize, NULL);
	////读取关卡-最高关卡
	//ReadFile(pfile, &MaxChapterNumber, sizeof(int), &readsize, NULL);
	////读取水滴容量
	//ReadFile(pfile, &WaterNumber, sizeof(int), &readsize, NULL);
	
	//善后工作
	CloseHandle(pfile);//关闭句柄。

	//修改难度
	Changedifficulty();
}

void GameChapter::GetMClickPoint(int x, int y)
{
	MClickPoint.x = x;
	MClickPoint.y = y;
}

void GameChapter::RenderGame()
{
	static float fTime = 0;

	//游戏失败状态
	if (GProgress == PGameOver)
	{
		if (pFail->IsVisible() == false)
		{
			pFail->SetVisible(true);
			pFail->SetFrame(0);
			//场景音效
			pPassOrFailMusic->PlaySound(pPassOrFailMusic->GetSoundCount());
			pGWaterManager->SetWatersVisible(false);
			pBackground->SetTexPos(0, 0);
		}
		if (pFail->GetFrame() == 0)
		{
			fTime += 1;
			if (fTime >= 15)
			{
				//场景音效
				pPassOrFailMusic->PlaySound(pPassOrFailMusic->GetSoundCount());
				fTime = 0;
				pFail->SetFrame(1);
			}
		}
		if (pFail->GetFrame() == 1)
		{
			fTime += 1;
			if (fTime >= 15)
			{
				//场景音效
				pPassOrFailMusic->PlaySound(pPassOrFailMusic->GetSoundCount());
				fTime = 0;
				pFail->SetFrame(2);
				
			}
		}
	}

	//游戏胜利状态
	if (GProgress == PGameWin)
	{
		if (pWin->IsVisible() == false)
		{
			pWin->SetVisible(true);
			pWin->SetFrame(0);
			//场景音效
			pPassOrFailMusic->PlaySound(pPassOrFailMusic->GetSoundCount());
			pGWaterManager->SetWatersVisible(false);
			pBackground->SetTexPos(0, 0);
		}
		if (pWin->GetFrame() == 0 )
		{	
			fTime += 1;
			if (fTime >= 15)
			{
				//场景音效
				pPassOrFailMusic->PlaySound(pPassOrFailMusic->GetSoundCount());
				fTime = 0;
				pWin->SetFrame(1);
			}
		}
		if (pWin->GetFrame() == 1 )
		{
			fTime += 1;
			if (fTime >= 15)
			{
				//场景音效
				pPassOrFailMusic->PlaySound(pPassOrFailMusic->GetSoundCount());
				fTime = 0;
				pWin->SetFrame(2);
			}
		}
	}

	/*基础现实*/
	//水滴
	int ten = WaterNumber / 10;
	int ge = WaterNumber - ten * 10;
	pWaterNumber[0]->SetTexPos(pWaterNumberWaH.x*ten,0);
	pWaterNumber[1]->SetTexPos(pWaterNumberWaH.x*ge, 0);

	//关卡
	ten = ChapterNumber / 10;
	ge = ChapterNumber - ten * 10;
	pChapterNumber[0]->SetTexPos(pChapterNumberWaH.x*ten, 0);
	pChapterNumber[1]->SetTexPos(pChapterNumberWaH.x*ge, 0);

	//最高记录
	ten = MaxChapterNumber / 10;
	ge = MaxChapterNumber - ten * 10;
	pMaxChapterNumber[0]->SetTexPos(pMaxChapterNumberWaH.x*ten, 0);
	pMaxChapterNumber[1]->SetTexPos(pMaxChapterNumberWaH.x*ge, 0);
}

GameProgress GameChapter::GetGProgress()
{
	return GProgress;
}
