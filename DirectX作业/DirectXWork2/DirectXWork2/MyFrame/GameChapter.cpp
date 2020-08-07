#include"GameChapter.h"

GWaterManager *GWaterManager::instance = NULL;

GameChapter::GameChapter()
{
	CResourcesPool *pResPool = NULL;
	pResPool = CResourcesPool::GetInstance();
	CNSpritesManager *pSpritesManager = NULL;
	pSpritesManager = CNSpritesManager::GetInstance();

	D2D1_SIZE_F Size = pResPool->GetResource(TEXT("Background"))->pTexture->GetSize();
	int w = Size.width, h = Size.height ;
	pBackground = pSpritesManager->CreateNSprite(TEXT("Background"), D2D1::Point2F(0, 0), w, h);

	pGWaterManager = GWaterManager::GetInstance();

	//初始化数据	
	ChapterNumber = 1;
	MaxChapterNumber = 1;
	LitterNumber = EasyL;
	MiddleNumber = EasyM;
	BigNumber = EasyB;
	WaterNumber = 10;
	GProgress = PGamePlaying;

	MClickPoint = { -1, -1 };

	offset = 522;
	SelectNewGame = { offset, 440, offset +20,440+20};
	IsSelectNewGame = false;
	IsGameWin = false;

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
	//初始化水滴
	pGWaterManager->Init();
	//初始化水滴状态 
	pGWaterManager->InitWprocession(LitterNumber, MiddleNumber, BigNumber);

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
	if (MClickPoint.x<offset)
		pGWaterManager->MClick(MClickPoint);

	//判断是否点击选择新游戏
	if (MClickPoint.x > SelectNewGame.left && MClickPoint.x<SelectNewGame.right
		&& MClickPoint.y>SelectNewGame.top && MClickPoint.y < SelectNewGame.bottom)
		IsSelectNewGame = true;
}

void GameChapter::GameSuccess()
{
	//游戏胜利
	IsGameWin = true;

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

	//改变游戏状态
	GProgress = PGamePlaying;
	
}

void GameChapter::IsChangeGameProgress()
{
	if (WaterNumber == 0)
		GProgress = PGameOver;
	
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
		MiddleNumber = EasyM;
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
		if (DifficultM > MiddleNumber)
			MiddleNumber++;
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

void GameChapter::RenderGame(ID2D1HwndRenderTarget *pRenderTarget, IDWriteTextFormat *pTextFormat, ID2D1SolidColorBrush *pTextBrush, ID2D1SolidColorBrush *pBrush)
{
	TCHAR szBuffer[20                                                                                                                                                                                                                            ];
	int iLength;
	D2D1_RECT_F textRect;

	//游戏失败状态
	if (GProgress == PGameOver)
	{
		iLength = wsprintf(szBuffer, TEXT("游戏失败！"));
		textRect = { offset, 420, offset + 150, 420 + 10 };
		pRenderTarget->DrawText(szBuffer, iLength, pTextFormat, textRect, pTextBrush);
		pRenderTarget->DrawRectangle(&D2D1::RectF(SelectNewGame.left, SelectNewGame.top, SelectNewGame.right, SelectNewGame.bottom), pBrush, 2);
		iLength = wsprintf(szBuffer, TEXT("开始新游戏"));
		textRect = { SelectNewGame.right + 5, SelectNewGame.top + 5, SelectNewGame.right + 5+100, SelectNewGame.top + 5+10 };
		pRenderTarget->DrawText(szBuffer, iLength, pTextFormat, textRect, pTextBrush);

	}

	static float fTime = 0;
	//游戏胜利状态
	if (IsGameWin)
	{
		fTime += 0.1;
		iLength = wsprintf(szBuffer, TEXT("该关胜利，水滴总量加一！"));
		textRect = { offset, 420, offset + 150, 420 + 10 };
		pRenderTarget->DrawText(szBuffer, iLength, pTextFormat, textRect, pTextBrush);
	}
	if (fTime > 20)
	{
		fTime = 0;
		IsGameWin = false;
	}

	/*基础现实*/
	//水滴
	iLength = wsprintf(szBuffer, TEXT("水滴总量：%d"), WaterNumber);
	textRect = { offset,20,offset+150,20+10 };
	pRenderTarget->DrawText(szBuffer, iLength, pTextFormat, textRect, pTextBrush);

	//关卡
	iLength = wsprintf(szBuffer, TEXT("当前关卡：%d"), ChapterNumber);
	textRect = { offset, 40, offset + 150, 40 + 10 };
	pRenderTarget->DrawText(szBuffer, iLength, pTextFormat, textRect, pTextBrush);

	//最高记录
	iLength = wsprintf(szBuffer, TEXT("最高记录：%d"), MaxChapterNumber);
	textRect = { offset, 60, offset + 150, 60 + 10 };
	pRenderTarget->DrawText(szBuffer, iLength, pTextFormat, textRect, pTextBrush);

}