#include"GameChapter.h"

GWaterManager *GWaterManager::instance = NULL;

GameChapter::GameChapter()
{
	CResourcesPool *pResPool = NULL;
	pResPool = CResourcesPool::GetInstance();
	CNSpritesManager *pSpritesManager = NULL;
	pSpritesManager = CNSpritesManager::GetInstance();

	/*����*/
	D2D1_SIZE_F Size = pResPool->GetResource(TEXT("Background"))->pTexture->GetSize();
	int w = Size.width/2, h = Size.height ;
	pBackground = pSpritesManager->CreateAnimationSprite(TEXT("Background"),2,2, D2D1::Point2F(0, 0), w, h);
	pBackground->SetTexPos(w, 0);
	/*ˮ������*/
	Size = pResPool->GetResource(TEXT("Number"))->pTexture->GetSize();
	w = Size.width / 10; h = Size.height;
	pWaterNumberWaH.x = w;
	pWaterNumberWaH.y = h;
	pWaterNumber[0] = pSpritesManager->CreateAnimationSprite(TEXT("Number"),10,2, D2D1::Point2F(480, 105), w, h);
	pWaterNumber[1] = pSpritesManager->CreateAnimationSprite(TEXT("Number"), 10, 2, D2D1::Point2F(526, 105), w, h);
	/*��ǰ�ؿ�*/
	Size = pResPool->GetResource(TEXT("Number"))->pTexture->GetSize();
	w = Size.width / 10; h = Size.height;
	pChapterNumberWaH.x = w;
	pChapterNumberWaH.y = h;
	pChapterNumber[0] = pSpritesManager->CreateAnimationSprite(TEXT("Number"), 10, 2, D2D1::Point2F(511, 312), w, h);
	pChapterNumber[1] = pSpritesManager->CreateAnimationSprite(TEXT("Number"), 10, 2, D2D1::Point2F(549, 312), w, h);
	pChapterNumber[0]->SetScaleFactor(0.8, 0.8);
	pChapterNumber[1]->SetScaleFactor(0.8, 0.8);
	/*��߹ؿ�*/
	Size = pResPool->GetResource(TEXT("Number"))->pTexture->GetSize();
	w = Size.width / 10; h = Size.height;
	pMaxChapterNumberWaH.x = w;
	pMaxChapterNumberWaH.y = h;
	pMaxChapterNumber[0] = pSpritesManager->CreateAnimationSprite(TEXT("Number"), 10, 2, D2D1::Point2F(553, 290), w, h);
	pMaxChapterNumber[1] = pSpritesManager->CreateAnimationSprite(TEXT("Number"), 10, 2, D2D1::Point2F(567, 290), w, h);
	pMaxChapterNumber[0]->SetScaleFactor(0.3, 0.3);
	pMaxChapterNumber[1]->SetScaleFactor(0.3, 0.3);
	/*ʤ��*/
	Size = pResPool->GetResource(TEXT("win"))->pTexture->GetSize();
	w = Size.width /3; h = Size.height;
	pWin = pSpritesManager->CreateAnimationSprite(TEXT("win"), 3, 2, D2D1::Point2F(0, 0), w, h);
	pWin->SetVisible(false);
	/*ʧ��*/
	Size = pResPool->GetResource(TEXT("fail"))->pTexture->GetSize();
	w = Size.width / 3; h = Size.height;
	pFail = pSpritesManager->CreateAnimationSprite(TEXT("fail"), 3, 2, D2D1::Point2F(0, 0), w, h);
	pFail->SetVisible(false);

	pGWaterManager = GWaterManager::GetInstance();

	/*������Ч*/
	pPassOrFailMusic = new XAudio2SoundPlayer();
	pPassOrFailMusic->LoadSound(TEXT("resource\\��.wav"));

	//��ʼ������	
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

	//��ȡ��Ϸ������Ϣ
	GameRead();

	//��ʼ��
	InitGame();
}

GameChapter::~GameChapter()
{
	GameKeep();//�������
}

void GameChapter::InitGame()
{
	pWin->SetVisible(false);
	pFail->SetVisible(false);
	pBackground->SetTexPos(pBackground->GetWidth(), 0);

	//ʹˮ�οɼ�
	pGWaterManager->SetWatersVisible(true);
	//��ʼ��ˮ��
	pGWaterManager->Init();
	//��ʼ��ˮ��״̬ 
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
	//�ж��Ƿ�����Ϸ����-��ûд
	if (MClickPoint.x < offset && GProgress == PGamePlaying)
	{
		pGWaterManager->MClick(MClickPoint);
	}

	if (GProgress == PGameOver)
	{
		//�ж��Ƿ���ѡ������Ϸ
		if (MClickPoint.x > SelectNewGame.left && MClickPoint.x<SelectNewGame.right
			&& MClickPoint.y>SelectNewGame.top && MClickPoint.y < SelectNewGame.bottom)
			IsSelectNewGame = true;
	}

	if (GProgress == PGameWin)
	{
		//�ж��Ƿ���ѡ����һ��
		if (MClickPoint.x > SelectNextGame.left && MClickPoint.x<SelectNextGame.right
			&& MClickPoint.y>SelectNextGame.top && MClickPoint.y < SelectNextGame.bottom)
			IsSelectNextGame = true;
	}
}

void GameChapter::GameSuccess()
{		
	if (IsSelectNextGame)
	{
		//����һ��ˮ��
		SetWaterNumber(1);

		//��ǰ�ؿ�����һ
		ChapterNumber += 1;

		//������߹ؿ�
		if (MaxChapterNumber <= ChapterNumber)
			MaxChapterNumber = ChapterNumber;

		//�޸��Ѷ�
		Changedifficulty();

		//��ʼ����Ϸ
		InitGame();

		IsSelectNextGame = false;

		//�ı���Ϸ״̬
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
	//ѡ������Ϸ
	if (IsSelectNewGame)
	{
		//��ʼ����ֵ
		ChapterNumber = 1;
		LitterNumber = EasyL;
		MiddleNumber1 = EasyM1;
		MiddleNumber2 = EasyM2;
		BigNumber = EasyB;
		WaterNumber = 10;

		//����Ϸ��ʼ��
		MClickPoint = { -1,-1 };
		IsSelectNewGame = false;
		
		//��ʼ����Ϸ
		InitGame();
		
		//״ֵ̬�ĸı�
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

	//��Ϸʧ�ܣ�����ؿ�������״̬�����ֹؿ���ˮ��	
	if (GProgress == PGameOver)
		WaterNumber = 10;//��ˮ�γ�ʼֵ

	DWORD readsize;
	sGameKeep sGK = { ChapterNumber, MaxChapterNumber, WaterNumber };
	WriteFile(pfile, &sGK, sizeof(sGameKeep), &readsize, NULL);
	////����ؿ�-��ǰ�ؿ�
	//WriteFile(pfile, &ChapterNumber, sizeof(int), &readsize, NULL);
	////����ؿ�-��߹ؿ�
	//WriteFile(pfile, &MaxChapterNumber, sizeof(int), &readsize, NULL);
	////����ˮ������
	//WriteFile(pfile, &WaterNumber, sizeof(int), &readsize, NULL);
}

void GameChapter::GameRead()
{
	HANDLE pfile;
	TCHAR filename[] = TEXT("GameInformation.txt");

	pfile = CreateFile(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	if (pfile == INVALID_HANDLE_VALUE)
	{
		//MessageBox(NULL, L"���ļ�ʧ��", L"Error", MB_OK);
		CloseHandle(pfile);        //һ��ע���ں����˳�֮ǰ�Ծ�������ͷš�
		return;
	}

	DWORD readsize;
	sGameKeep sGK ;
	ReadFile(pfile, &sGK, sizeof(sGameKeep), &readsize, NULL);
	ChapterNumber = sGK.sChapterNumber;
	MaxChapterNumber = sGK.sMaxChapterNumber;
	WaterNumber = sGK.sWaterNumber;
	////��ȡ�ؿ�-��ǰ�ؿ�
	//ReadFile(pfile, &ChapterNumber, sizeof(int), &readsize, NULL);
	////��ȡ�ؿ�-��߹ؿ�
	//ReadFile(pfile, &MaxChapterNumber, sizeof(int), &readsize, NULL);
	////��ȡˮ������
	//ReadFile(pfile, &WaterNumber, sizeof(int), &readsize, NULL);
	
	//�ƺ���
	CloseHandle(pfile);//�رվ����

	//�޸��Ѷ�
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

	//��Ϸʧ��״̬
	if (GProgress == PGameOver)
	{
		if (pFail->IsVisible() == false)
		{
			pFail->SetVisible(true);
			pFail->SetFrame(0);
			//������Ч
			pPassOrFailMusic->PlaySound(pPassOrFailMusic->GetSoundCount());
			pGWaterManager->SetWatersVisible(false);
			pBackground->SetTexPos(0, 0);
		}
		if (pFail->GetFrame() == 0)
		{
			fTime += 1;
			if (fTime >= 15)
			{
				//������Ч
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
				//������Ч
				pPassOrFailMusic->PlaySound(pPassOrFailMusic->GetSoundCount());
				fTime = 0;
				pFail->SetFrame(2);
				
			}
		}
	}

	//��Ϸʤ��״̬
	if (GProgress == PGameWin)
	{
		if (pWin->IsVisible() == false)
		{
			pWin->SetVisible(true);
			pWin->SetFrame(0);
			//������Ч
			pPassOrFailMusic->PlaySound(pPassOrFailMusic->GetSoundCount());
			pGWaterManager->SetWatersVisible(false);
			pBackground->SetTexPos(0, 0);
		}
		if (pWin->GetFrame() == 0 )
		{	
			fTime += 1;
			if (fTime >= 15)
			{
				//������Ч
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
				//������Ч
				pPassOrFailMusic->PlaySound(pPassOrFailMusic->GetSoundCount());
				fTime = 0;
				pWin->SetFrame(2);
			}
		}
	}

	/*������ʵ*/
	//ˮ��
	int ten = WaterNumber / 10;
	int ge = WaterNumber - ten * 10;
	pWaterNumber[0]->SetTexPos(pWaterNumberWaH.x*ten,0);
	pWaterNumber[1]->SetTexPos(pWaterNumberWaH.x*ge, 0);

	//�ؿ�
	ten = ChapterNumber / 10;
	ge = ChapterNumber - ten * 10;
	pChapterNumber[0]->SetTexPos(pChapterNumberWaH.x*ten, 0);
	pChapterNumber[1]->SetTexPos(pChapterNumberWaH.x*ge, 0);

	//��߼�¼
	ten = MaxChapterNumber / 10;
	ge = MaxChapterNumber - ten * 10;
	pMaxChapterNumber[0]->SetTexPos(pMaxChapterNumberWaH.x*ten, 0);
	pMaxChapterNumber[1]->SetTexPos(pMaxChapterNumberWaH.x*ge, 0);
}

GameProgress GameChapter::GetGProgress()
{
	return GProgress;
}
