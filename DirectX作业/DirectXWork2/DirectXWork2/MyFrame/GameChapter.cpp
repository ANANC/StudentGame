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

	//��ʼ������	
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
	//��ʼ��ˮ��
	pGWaterManager->Init();
	//��ʼ��ˮ��״̬ 
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
	//�ж��Ƿ�����Ϸ����-��ûд
	if (MClickPoint.x<offset)
		pGWaterManager->MClick(MClickPoint);

	//�ж��Ƿ���ѡ������Ϸ
	if (MClickPoint.x > SelectNewGame.left && MClickPoint.x<SelectNewGame.right
		&& MClickPoint.y>SelectNewGame.top && MClickPoint.y < SelectNewGame.bottom)
		IsSelectNewGame = true;
}

void GameChapter::GameSuccess()
{
	//��Ϸʤ��
	IsGameWin = true;

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

	//�ı���Ϸ״̬
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
	//ѡ������Ϸ
	if (IsSelectNewGame)
	{
		//��ʼ����ֵ
		ChapterNumber = 1;
		LitterNumber = EasyL;
		MiddleNumber = EasyM;
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

void GameChapter::RenderGame(ID2D1HwndRenderTarget *pRenderTarget, IDWriteTextFormat *pTextFormat, ID2D1SolidColorBrush *pTextBrush, ID2D1SolidColorBrush *pBrush)
{
	TCHAR szBuffer[20                                                                                                                                                                                                                            ];
	int iLength;
	D2D1_RECT_F textRect;

	//��Ϸʧ��״̬
	if (GProgress == PGameOver)
	{
		iLength = wsprintf(szBuffer, TEXT("��Ϸʧ�ܣ�"));
		textRect = { offset, 420, offset + 150, 420 + 10 };
		pRenderTarget->DrawText(szBuffer, iLength, pTextFormat, textRect, pTextBrush);
		pRenderTarget->DrawRectangle(&D2D1::RectF(SelectNewGame.left, SelectNewGame.top, SelectNewGame.right, SelectNewGame.bottom), pBrush, 2);
		iLength = wsprintf(szBuffer, TEXT("��ʼ����Ϸ"));
		textRect = { SelectNewGame.right + 5, SelectNewGame.top + 5, SelectNewGame.right + 5+100, SelectNewGame.top + 5+10 };
		pRenderTarget->DrawText(szBuffer, iLength, pTextFormat, textRect, pTextBrush);

	}

	static float fTime = 0;
	//��Ϸʤ��״̬
	if (IsGameWin)
	{
		fTime += 0.1;
		iLength = wsprintf(szBuffer, TEXT("�ù�ʤ����ˮ��������һ��"));
		textRect = { offset, 420, offset + 150, 420 + 10 };
		pRenderTarget->DrawText(szBuffer, iLength, pTextFormat, textRect, pTextBrush);
	}
	if (fTime > 20)
	{
		fTime = 0;
		IsGameWin = false;
	}

	/*������ʵ*/
	//ˮ��
	iLength = wsprintf(szBuffer, TEXT("ˮ��������%d"), WaterNumber);
	textRect = { offset,20,offset+150,20+10 };
	pRenderTarget->DrawText(szBuffer, iLength, pTextFormat, textRect, pTextBrush);

	//�ؿ�
	iLength = wsprintf(szBuffer, TEXT("��ǰ�ؿ���%d"), ChapterNumber);
	textRect = { offset, 40, offset + 150, 40 + 10 };
	pRenderTarget->DrawText(szBuffer, iLength, pTextFormat, textRect, pTextBrush);

	//��߼�¼
	iLength = wsprintf(szBuffer, TEXT("��߼�¼��%d"), MaxChapterNumber);
	textRect = { offset, 60, offset + 150, 60 + 10 };
	pRenderTarget->DrawText(szBuffer, iLength, pTextFormat, textRect, pTextBrush);

}