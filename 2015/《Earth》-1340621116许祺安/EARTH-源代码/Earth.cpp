#include"Earth.h"
#include <ctime>

#define KEY_LEFT (GetKeyState(VK_LEFT) & 0x80)>0 ? true : false
#define KEY_RIGHT  (GetKeyState(VK_RIGHT) & 0x80)>0 ? true : false
#define KEY_SPACE  (GetKeyState(VK_SPACE) & 0x80)>0 ? true : false
#define KEY_SHIFT  (GetKeyState(VK_SHIFT) & 0x80)>0 ? true : false
#define KEY_CTRL  (GetKeyState(VK_ESCAPE) & 0x80)>0 ? true : false

/*׼������*/
Earth::Earth(HWND hwnd, int fps) : CGame(hwnd, fps)
{
	Init();
}
Earth::~Earth(void)
{
}

void Earth::Init()
{
	CGame::Init();

	/*׼������*/
	GetPicture();//����ͼƬ
	Mpoint = { 0, 0 };//����ƶ�λ��
	Cpoint = { 0, 0 };//�����λ��
	GameP = 1;//��Ϸ����
	IsGamePlay = false;//�Ƿ������Ϸ
	IsGameOver = false;//��Ϸ�Ƿ�ر�
	
	/*��ʼ����*/
	GetGameStart();//��ʼ����
	rGameStart = { 378, 120, 473, 145 };//��ʼ�Ŀ�
	IsSelectGameStart = false;//�Ƿ�Ӵ�

	/*ѡ�ؽ���*/
	GetGamePass();//ѡ�ؽ���
	for (int i = 1; i < 8; i++)
	{
		IsPassSelect[i] = false;//ѡ��״̬
		IsGamePass[i] = false;//ͨ��״̬
		GP[i] = false;//������
	}
	GP[0] = false;//������
	IsPassSelect[0] = true;//��һ�ؿ�ѡ	
	IsGamePass[0] = false;//ͨ��״̬-��һ��
	for (int i = 0; i < 8; i++)
		GameTime[i] = 0;//ͨ��ʱ��
	GameMunber = 0;//��ǰ�ؿ�
	Gp = -1;//�����ùؿ�


	/*��Ϸ����*/
	GetPlayScreen();//��Ϸ����
	FoodNumber = 0;//���ʳ�������
	for (int i = 0; i < 3; i++)
		IsGetFood[i] = { false };//�Ƿ�õ�ʳ��
	ss = { 237, 95, 616, 474 };//Բ�Ŀ�
	IsMoveRestart = false;//����Ƿ����������

	/*��������*/
	GetPeople();//��������
	RotationAngle = 0;//��ת�Ƕ�
	//��������һ��ʼ��λ��
	oldPos = { People->GetXPos() + PeoWidth / 2, People->GetYPos() };
	PeoHeight = People->GetHeight();//����ͼƬ�ĸ߶�
	PeoWidth = People->GetWidth();//����ͼƬ�Ŀ��
	bIsFly = false;//�ǷǷ�
	bIsDown = false;//�Ƿ�����
	fFlyDistance = 0;//���и߶�

	/*��ʱ��*/
	GameTime_min = 0;//��
	GameTime_sec = 0;//��
	GameTime_msec = 0;//����
	for (int i = 0; i < 8; i++)
		GameTime[i] = 0;//�ؿ�ʱ��
	Selecthf();//��ʼ������
	int  fD = 0;//��ʱ��

	/*�ϰ�*/
	GetHinder();//�ϰ�
	PlayWay = 1;//�����Ƿ�ߵ�
	IsStatic = false;//�����Ƿ�̶�
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < HinderNumber; j++)
			IsLeft[i][j] = 0;//�Ƿ����
	}
	rinSpeed = 1;//�꣬�ٶȸı�

}

void Earth::Erase()//������
{
	/*��ʼ����*/
	DeleteGameStart();

	/*ѡ�ؽ���*/
	DeleteGamePass();

	/*��Ϸ����*/
	DelectPlayScreen();
	DelectPeople();
	Delecthf();
	DelectHinder();
}

void Earth::GetPicture()
{
	/*����*/
	pResManager->LoadPictureFromFile(TEXT("people"), TEXT("image/����/people.bmp"));
	pResManager->LoadPictureFromFile(TEXT("����"), TEXT("image/����/����.bmp"));
	pResManager->LoadPictureFromFile(TEXT("��ȡ����"), TEXT("image/����/��ȡ����.bmp"));
	pResManager->LoadPictureFromFile(TEXT("����"), TEXT("image/����/����.bmp"));
	pResManager->LoadPictureFromFile(TEXT("ͨ��"), TEXT("image/����/ͨ��.bmp"));
	pResManager->LoadPictureFromFile(TEXT("����"), TEXT("image/����/����.bmp"));

	/*��ͼ*/
	pResManager->LoadPictureFromFile(TEXT("��ʼ"), TEXT("image/��ͼ/��ʼ.bmp"));
	pResManager->LoadPictureFromFile(TEXT("��צ��"), TEXT("image/��ͼ/��צ��.bmp"));
	pResManager->LoadPictureFromFile(TEXT("��צ���ϰ�"), TEXT("image/��ͼ/��צ���ϰ�.bmp"));
	pResManager->LoadPictureFromFile(TEXT("����"), TEXT("image/��ͼ/����.bmp"));
	pResManager->LoadPictureFromFile(TEXT("�ѹ�Ӣ"), TEXT("image/��ͼ/�ѹ�Ӣ.bmp"));
	pResManager->LoadPictureFromFile(TEXT("����"), TEXT("image/��ͼ/����.bmp"));
	pResManager->LoadPictureFromFile(TEXT("��"), TEXT("image/��ͼ/��.bmp"));
	pResManager->LoadPictureFromFile(TEXT("ˮ���ϰ�"), TEXT("image/��ͼ/ˮ���ϰ�.bmp"));
	pResManager->LoadPictureFromFile(TEXT("��"), TEXT("image/��ͼ/��.bmp"));
	pResManager->LoadPictureFromFile(TEXT("���ϰ�"), TEXT("image/��ͼ/���ϰ�.bmp"));
	pResManager->LoadPictureFromFile(TEXT("���ϰ�"), TEXT("image/��ͼ/���ϰ�.bmp"));

	pResManager->LoadPictureFromFile(TEXT("���ϰ�1"), TEXT("image/��ͼ/���ϰ�1.bmp"));
	pResManager->LoadPictureFromFile(TEXT("���ϰ�2"), TEXT("image/��ͼ/���ϰ�2.bmp"));

	/*�ؿ�*/
	pResManager->LoadPictureFromFile(TEXT("��צ��ؿ�"), TEXT("image/�ؿ�/��צ��.bmp"));
	pResManager->LoadPictureFromFile(TEXT("���ֹؿ�"), TEXT("image/�ؿ�/����.bmp"));
	pResManager->LoadPictureFromFile(TEXT("�ѹ�Ӣ�ؿ�"), TEXT("image/�ؿ�/�ѹ�Ӣ.bmp"));
	pResManager->LoadPictureFromFile(TEXT("����ؿ�"), TEXT("image/�ؿ�/����.bmp"));
	pResManager->LoadPictureFromFile(TEXT("���ؿ�"), TEXT("image/�ؿ�/��.bmp"));
	pResManager->LoadPictureFromFile(TEXT("ˮ�ιؿ�"), TEXT("image/�ؿ�/ˮ��.bmp"));
	pResManager->LoadPictureFromFile(TEXT("��ؿ�"), TEXT("image/�ؿ�/��.bmp"));
	pResManager->LoadPictureFromFile(TEXT("�ƹؿ�"), TEXT("image/�ؿ�/��.bmp"));

	/*����ӵı���*/
	pResManager->LoadPictureFromFile(TEXT("2_�"), TEXT("image/��ͼ/2-�.bmp"));
	pResManager->LoadPictureFromFile(TEXT("2_�����"), TEXT("image/��ͼ/2-�����.bmp"));
}

void Earth::Update(float fDeltaTime)
{
	if (IsGameOver)
		return;

	CGame::Update(fDeltaTime);

	//MouseMove();//����ƶ�-���Էŵ�main
	//MouseClick();//�����-���Էŵ�main

	if (GetGameP() == 1)
	{
		GameStart->Update(fDeltaTime);
		GameStartPlay();
	}
	

	/*��Ϸ����*/
	if (GetGameP() == 3)
	{
		PeoMove(fDeltaTime);//��������
		People->Update(fDeltaTime);
		GetPeopleXandY();

		for (int i = 0; i < HinderNum[1]; i++)
			Hinder[1][i]->Update(fDeltaTime);

		GameScreen->Update(fDeltaTime);

		TimerUpdate(fDeltaTime);//ʱ��ĸ���
		HinderMove();//�ϰ����ƶ�
		GetFood();//ʳ��
		HinderTouch(fDeltaTime);//�Ӵ��ϰ�

		IsRestart();//�����ݼ�
		IsGOver();//���ؿ�ݼ�
		Restart();
	}
	
}

void Earth::Render()
{
	//CGame::Render();
	FillRect(hdcMem, &rectClient, hBr);
	if (pSpriteManager)
	{
		pSpriteManager->Render(hdcMem);
	}
	if (t >= 1)
	{
		nCalcFps = nFrames / t;

		t = 0;
		nFrames = 0;
	}

	if (GetGameP() == 2)
		SetTip();

	if (GetGameP() == 3)
	{
		TimerShow();//ʱ���չʾ
		IsMoveInRestart();//�����ݼ�����ʾ
		IsMoveInReturn();//���ؿ�ݼ�����ʾ
	}

	BitBlt(hdc, 0, 0, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, hdcMem, 0, 0, SRCCOPY);
}

void Earth::MouseSide()//����ƶ�λ��
{
	GetCursorPos(&Mpoint);            // ��ȡ���ָ��λ�ã���Ļ���꣩
	ScreenToClient(hWnd, &Mpoint);    // �����ָ��λ��ת��Ϊ��������
}

void Earth::MouseCSide()//�����λ��
{
	GetCursorPos(&Cpoint);            // ��ȡ���ָ��λ�ã���Ļ���꣩
	ScreenToClient(hWnd, &Cpoint);    // �����ָ��λ��ת��Ϊ��������
}

void Earth::MouseMove()
{
	MouseSide();//�������ƶ�λ��-���Էŵ�main

	/*��ʼ����*/
	if (GetGameP() == 1)
		MoveGameStrat();

	/*ѡ�ؽ���*/
	if (GetGameP() == 2)
		MoveGamePass();
	
	/*��Ϸ����*/
	if (GetGameP() == 3)
	{
		MoveReturn();
		MoveRestart();
	}
}

void Earth::MouseClick()
{
	MouseCSide();//��������λ��-Ӧ�÷���main

	/*��ʼ����*/
	if (GetGameP() == 1)
		SelectGameStrat();

	/*ѡ�ؽ���*/
	if (GetGameP() == 2)
		SelectGamePass();

	/*��Ϸ����*/
	if (GetGameP() == 3)
	{
		Return();//����
		Restart();//����
	}
}

void Earth::GamePlaing(bool t)
{
	IsGamePlay = t;
}

void Earth::GameProgress(int i)
{
	GameP = i;
}

int Earth::GetGameP()
{
	return GameP;
}

void Earth::SetGameOver()
{
	IsGameOver = true;
}

void Earth::White()
{
	HANDLE han;	
	han = CreateFile(TEXT("gn.txt"), GENERIC_WRITE, FILE_SHARE_WRITE	, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL,	NULL);
	if (han == INVALID_HANDLE_VALUE)
		return;
	DWORD Written;
	BOOL bOK = WriteFile(han, TEXT("ASDDAJS"), strlen("ASDDAJS"), &Written, NULL);
	CloseHandle(han);
}

/*��ʼ����*/

void Earth::GetGameStart()
{
	GameStart = pSpriteManager->CreateAnimationSprite(TEXT("��ʼ"),3, 30, 0, 0,3,2);
	GameStart->SetPos(0, 0);
	GameStart->Play();
}

void Earth::DeleteGameStart()
{
	pSpriteManager->DeleteSprite(GameStart);
}

void Earth::SelectGameStrat()
{
	if (Cpoint.x >= rGameStart.left&&Cpoint.x <= rGameStart.right&&Cpoint.y >= rGameStart.top&&Cpoint.y <= rGameStart.bottom)
	{
		GameStart->SetVisible(false);
		GameStart->Stop();
		for (int i = 0; i < 8; i++)
		{
			GamePass[i]->SetVisible(true);
		}
		GameProgress(2);//������Ϸ״̬-����ѡ��״̬
	}
}

void Earth::MoveGameStrat()
{
	if (Mpoint.x >= rGameStart.left&&Mpoint.x <= rGameStart.right&&Mpoint.y >= rGameStart.top&&Mpoint.y <= rGameStart.bottom)
		IsSelectGameStart = true;
	else
		IsSelectGameStart = false;
}
void Earth::GameStartPlay()
{
	static bool k = false;
	if (IsSelectGameStart && !k)
	{
		int h = GameStart->GetHeight();
		GameStart->SetTextureStartPos(0, h);
		GameStart->Play();
		k = true;
	}
	else if (!IsSelectGameStart)
	{
		GameStart->SetTextureStartPos(0, 0);
		k = false;
	}
}

/*ѡ�ؽ���*/

void Earth::GetGamePass()
{
	int xxm = 40, yym = 90, ww, hh;
	GamePass[0] = pSpriteManager->CreateAnimationSprite(TEXT("���ֹؿ�"), 2, 1, xxm, yym, 2, 4);
	ww = GamePass[0]->GetDestWidth(); 
	hh = GamePass[0]->GetDestHeight();
	GamePass[1] = pSpriteManager->CreateAnimationSprite(TEXT("��ؿ�"), 2, 1, 2 * xxm + ww, yym, 2, 5);
	GamePass[2] = pSpriteManager->CreateAnimationSprite(TEXT("��צ��ؿ�"), 2, 1, 3 * xxm + 2 * ww, yym, 2, 5);
	GamePass[3] = pSpriteManager->CreateAnimationSprite(TEXT("���ؿ�"), 2, 1, 4 * xxm + 3 * ww, yym, 2, 5);
	GamePass[4] = pSpriteManager->CreateAnimationSprite(TEXT("�ѹ�Ӣ�ؿ�"), 2, 1, xxm, 20 + hh + yym, 2, 5);
	GamePass[5] = pSpriteManager->CreateAnimationSprite(TEXT("ˮ�ιؿ�"), 2, 1, 2 * xxm + ww, 20 + hh + yym, 2, 5);
	GamePass[6] = pSpriteManager->CreateAnimationSprite(TEXT("����ؿ�"), 2, 1, 3 * xxm + 2 * ww, 20 + hh + yym, 2, 5);
	GamePass[7] = pSpriteManager->CreateAnimationSprite(TEXT("�ƹؿ�"), 2, 1, 4 * xxm + 3 * ww, 20 + hh + yym, 2, 5);
	for (int i = 0; i < 8; i++)
	{
		GamePass[i]->SetVisible(false);
	}
}

void Earth::DeleteGamePass()
{
	for (int i = 0; i < 8;i++)
		pSpriteManager->DeleteSprite(GamePass[i]);
}

void Earth::ChangePass()
{
	if (GameTime[0])
	{
		if (GameTime[0] < 0.3 && GameTime[0] != 0)
			GamePass[0]->SetTexturePos(0, 183 * 3);

		if (GameTime[0]<1 && GameTime[0] >= 0.3)
			GamePass[0]->SetTexturePos(0, 182.222 * 2);

		if (GameTime[0]>1)
			GamePass[0]->SetTexturePos(0, 182.222);
	}
	for (int i = 1; i < 8; i++)
	{
		if (!IsGamePass[i] && IsGamePass[i - 1])
		{
			GamePass[i]->SetTexturePos(0, 182.5);
			IsPassSelect[i] = true;
		}

		if (GameTime[i]<0.3 && GameTime[i] != 0 && IsGamePass[i])
			GamePass[i]->SetTexturePos(0, 182.5 * 4);

		if (GameTime[i]<1 && GameTime[i] >= 0.3 && IsGamePass[i])
			GamePass[i]->SetTexturePos(0, 182.5 * 3);

		if (GameTime[i]>1 && IsGamePass[i])
			GamePass[i]->SetTexturePos(0, 182.5 * 2);
	}
}

void Earth::SelectGamePass()
{
	for (int i = 0; i < 8; i++)
	{
		if (!IsPassSelect[i])
			continue;

		if (GamePass[i]->IsSelected(Cpoint.x, Cpoint.y))
		{
			/*ѡ�ز��ɼ�*/
			for (int j = 0; j < 8; j++)
				GamePass[j]->SetVisible(false);

			/*������ߣ��ϰ��ɼ�*/
			GameScreen->SetVisible(true);//��ͼ
			GameScreen->Play();
			Again->SetVisible(true);//����
			Back->SetVisible(true);//����
			for (int j = 0; j < 3; j++)
				GFood[j]->SetVisible(true);//ʳ��
			People->SetVisible(true);//����
			People->Play();

			/*�޸���Ϸ״̬*/
			GameMunber = i;//���õ�ǰ�ؿ�
			GameProgress(3);//������Ϸ״̬
			GamePlaing(true);//������Ϸ

			/*������ߣ��ϰ�,��ʱ����ʼ��*/
			FoodFirst();//����
			PeoFirst();//����
			TimeFirst();//��ʱ��
			HinderCreate();//��̬�ϰ�
			HinderShow_static();//��̬�ϰ�

			/*���Ե��±���*/
			/*Two_F->SetVisible(true);
			Two_FF[0]->SetVisible(true);
			Two_FF[1]->SetVisible(true);*/

			return;
		}
	}
}

void Earth::MoveGamePass()
{
	for (int i = 0; i < 8; i++)
	{
		if (GamePass[i]->IsSelected(Mpoint.x, Mpoint.y))
		{
			int x = GamePass[i]->GetWidth();
			int y = GamePass[i]->GetTYpos();
			GamePass[i]->SetTexturePos(x, y);
			GP[i] = true;
			Gp = i;
		}
		else
		{
			if (GP[i] == false)
				continue;

			int y = GamePass[i]->GetTYpos();
			GamePass[i]->SetTexturePos(0, y);
			GP[i] = false;
			Gp = -1;
		}
	}
}

void Earth::SetGameTime(int p, int m, int s)
{
	GameTime[p] = m + s*0.01;
}

void Earth::SetGamePass(int i)
{
	IsGamePass[i] = true;
}

void Earth::SetTip()//w160 h182
{
	TCHAR szBuffer[15];
	switch (Gp)
	{
	case 0:
		if (IsPassSelect[0])
			TextOut(hdcMem, 50, 30 + 80 + 182, szBuffer, wsprintf(szBuffer, TEXT("��Ծ���߹������ľ���")));
		break;
	case 1:
		if (IsPassSelect[1])
			TextOut(hdcMem, 40 + 160 + 20, 30 + 80 + 182, szBuffer, wsprintf(szBuffer, TEXT("��Ⱥ��ӵ����ں��������ζ�")));
		break;
	case 2:
		if (IsPassSelect[2])
			TextOut(hdcMem, 40 + 160 * 2 + 60, 30 + 80 + 182, szBuffer, wsprintf(szBuffer, TEXT("�����İ�צ�����ǲ����������")));
		break;
	case 3:
		if (IsPassSelect[3])
			TextOut(hdcMem, 40 + 160 * 3 + 100, 30 + 80 + 182, szBuffer, wsprintf(szBuffer, TEXT("������յ�����;����ʧ����")));
		break;
	case 4:
		if (IsPassSelect[4])
			TextOut(hdcMem, 40-5, 30 + 80 + 182, szBuffer, wsprintf(szBuffer, TEXT("ɢ����ص��ѹ�ӢƮ�����")));
		break;
	case 5:
		if (IsPassSelect[5])
			TextOut(hdcMem, 40+160+45, 30+80+182, szBuffer, wsprintf(szBuffer, TEXT("·�˻�æ�����������")));
		break;
	case 6:
		if (IsPassSelect[6])
			TextOut(hdcMem, 40+160*2+90, 30+80+182, szBuffer, wsprintf(szBuffer, TEXT("����ʹ��ͣס�˽Ų�")));
		break;
	case 7:
		if (IsPassSelect[7])
			TextOut(hdcMem, 40+160*3+100, 30+80 + 182, szBuffer, wsprintf(szBuffer, TEXT("�ƶ���ס���䱦")));
		break;
	default:
		break;
	}
}

int Earth::GetGameMunber()
{
	return GameMunber;
}


/*��Ϸ����*/
void Earth::GetPlayScreen()
{
	/*��Ϸ����*/
	GameScreen = pSpriteManager->CreateAnimationSprite(TEXT("��"), 3, 20, 0, 0, 3, 4);//��ͼ
	GameScreen->SetPos(0, 0);
	GameScreen->SetVisible(false);
	GameScreen->Play();

	/*����*/
	Again = pSpriteManager->CreateAnimationSprite(TEXT("����"), 2, 1, 775, 20, 2, 1);
	Back = pSpriteManager->CreateAnimationSprite(TEXT("����"), 2, 1, 775 + Again->GetDestHeight() + 10, 20, 2, 1);
	Fail = pSpriteManager->CreateSprite(TEXT("����"));
	Fail->SetPos(690, 25);
	Success = pSpriteManager->CreateSprite(TEXT("ͨ��"));
	Success->SetPos(710, 25);
	for (int i = 0; i < 3; i++)
	{
		GFood[i] = pSpriteManager->CreateSprite(TEXT("��ȡ����"));
		GFood[i]->SetVisible(false);
		GFood[i]->SetSpriteRect(-3, -3);
	}
	Again->SetVisible(false);
	Back->SetVisible(false);
	Fail->SetVisible(false);
	Success->SetVisible(false);

	//for (int i = 0; i < 2; i++)
	//{
	//	Two_FF[i] = pSpriteManager->CreateAnimationSprite(TEXT("2_�����"), 2, 1, 0, 0, 2, 2);
	//	Two_FF[i]->SetVisible(false);
	//	Two_FF[i]->SetTransparent(true);
	//}
	//Two_FF[0]->SetPos(700, 270);
	//Two_FF[1]->SetTexturePos(0, Two_FF[1]->GetHeight());
	//Two_FF[1]->SetPos(-220, -200);

	//Two_F = pSpriteManager->CreateSprite(TEXT("2_�"));
	//Two_F->SetVisible(false);
	//Two_F->SetTransparent(true);

}

void Earth::DelectPlayScreen()
{
	pSpriteManager->DeleteSprite(GameScreen);
	pSpriteManager->DeleteSprite(Again);
	pSpriteManager->DeleteSprite(Back);
	pSpriteManager->DeleteSprite(Fail);
	pSpriteManager->DeleteSprite(Success);
	for (int i = 0; i < 3;i++)
		pSpriteManager->DeleteSprite(GFood[i]);
}

void Earth::Return()
{
	if (Back->IsSelected(Cpoint.x, Cpoint.y) || IsGOver())
	{
		/*ѡ�ؿɼ�*/
		for (int i = 0; i < 8; i++)
			GamePass[i]->SetVisible(true);

		/*����ϰ������߲��ɼ�*/
		GameScreen->SetVisible(false);//��ͼ
		GameScreen->Stop();
		Again->SetVisible(false);//����
		Back->SetVisible(false);//����
		Fail->SetVisible(false);//ʧ��
		Success->SetVisible(false);//�ɹ�
		for (int i = 0; i < 3;i++)
			GFood[i]->SetVisible(false);//ʳ��
		People->SetVisible(false);//����
		People->Stop();//���ﶯ��������
		HinderErase();//�ϰ�

		/*�޸���Ϸ״̬*/
		GameProgress(2);//������Ϸ״̬
		GamePlaing(false);//������Ϸ
		ChangePass();//�ı�ѡ��Ч��

		if (Again->IsSelected(Cpoint.x, Cpoint.y))
			Cpoint = { 0, 0 };
	}
}

void Earth::Restart()
{
	if (Again->IsSelected(Cpoint.x, Cpoint.y) || IsRestart())
	{
		/*���ߵĳ�ʼ��*/
		FoodFirst();
		for (int i = 0; i < 3; i++)
			GFood[i]->SetVisible(true);

		/*����ĳ�ʼ��*/
		PeoFirst();

		/*�ϰ��ĳ�ʼ��*/
		HinderErase();
		HinderShow_static();//��̬�ϰ�
		HinderCreate();//��̬�ϰ�

		/*��ʱ���ĳ�ʼ��*/
		TimeFirst();

		GamePlaing(true);
		Success->SetVisible(false);
		Fail->SetVisible(false);

		if (Again->IsSelected(Cpoint.x, Cpoint.y))
			Cpoint = { 0, 0 };
	}
}

bool Earth::IsRestart()
{
	if (KEY_SHIFT)
		return true;
}

bool Earth::IsGOver()
{
	if (KEY_CTRL)
		return true;
}

void Earth::MoveReturn()
{
	if (Back->IsSelected(Mpoint.x, Mpoint.y))
	{
		int x = Back->GettexWidth() / 2;
		Back->SetTexturePos(x, 0);
		//IsMoveReturn = true;
	}
	else
	{
		Back->SetTexturePos(0, 0);
		//IsMoveReturn = false;
	}
}

void Earth::MoveRestart()
{
	if (Again->IsSelected(Mpoint.x, Mpoint.y))
	{
		int x = Again->GettexWidth() / 2;
		Again->SetTexturePos(x, 0);
		IsMoveRestart = true;
	}
	else
	{
		Again->SetTexturePos(0, 0);
		IsMoveRestart = false;
	}

}

void Earth::IsMoveInRestart()
{
	if (IsMoveRestart)
	{
		TCHAR szBuffer[15];
		TextOut(hdcMem, 772, 50, szBuffer, wsprintf(szBuffer, TEXT("shift��")));
	}
}

void Earth::IsMoveInReturn()
{
	if (IsMoveReturn)
	{
		TCHAR szBuffer[15];
		TextOut(hdcMem, 792, 50, szBuffer, wsprintf(szBuffer, TEXT("control��")));
	}
}

void Earth::GameSuccess()
{
	Success->SetVisible(true);//�ɼ�
}

void Earth::GameOver()
{
	Fail->SetVisible(true);//�ɼ�
	GameScreen->SetTexturePos(0, 567 * 4);
	People->Stop();
	for (int i = 0; i < HinderNum[1]; i++)
		Hinder[1][i]->Stop();
	GamePlaing(false);//��Ϸ����
}

void Earth::GameSuccess(int i)
{
	/*����ͼƬ*/
	GameSuccess();

	/*���ùؿ�״̬*/
	GamePlaing(false);//��Ϸ����
	SetGamePass(i);//����ͨ�عؿ�

	/*��¼ʱ��*/
	SetGameTime(i, GameTime_min, GameTime_sec);

	People->Stop();
	for (int i = 0; i < HinderNum[1]; i++)
		Hinder[1][i]->Stop();


}

void Earth::SetFood()
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
	Vector2D vector(0.0f, -189.5f - 62);
	for (int i = 0; i < 3; i++)
	{
		vector.rotate(RR[i]);
		GFood[i]->SetPos(433 - 15 + vector.GetX(), 303 - 30 + vector.GetY());
	}
}

void Earth::GetFood()
{
	
	RECT rtIntersect;

	for (int i = 0; i < 3; i++)
	{
		if (IsGetFood[i])
			continue;
		if (IntersectRect(&rtIntersect, GFood[i]->GetSpriteRect(), People->GetSpriteRect()))
		{
			GFood[i]->SetVisible(false);
			IsGetFood[i] = true;
			FoodNumber += 1;
		}
	}
	if (FoodNumber)
		GameScreen->SetTextureStartPos(0, 567 * FoodNumber);

	if (FoodNumber == 3)//��Ϸʤ��
		GameSuccess(GetGameMunber());
		
	
}

void Earth::FoodFirst()
{
	/*���������͵�ͼ�ĳ�ʼ��*/
	for (int i = 0; i < 3;i++)
		IsGetFood[i] = { false };
	FoodNumber = 0;
	GameScreen->SetTextureStartPos(0, 567 * FoodNumber);

	//����ͼƬ
	SetFood();
}

/*��������*/
void Earth::GetPeople()
{
	People = pSpriteManager->CreateAnimationSprite(TEXT("people"), 4, 10, 0, 0, 4, 6);
	People->SetVisible(false);
	People->SetTransparent(true);

	int x = GameScreen->GetWidth() / 2 - People->GetWidth() / 2;
	People->SetPos(x, 70);
	People->SetSpriteRect(-4, -4);
	PeopleXaY = { 0, 0 };
}

void Earth::DelectPeople()
{
	pSpriteManager->DeleteSprite(People);
}

void Earth::PeoMove(float fDelataTime)
{
	static float fTime;
	Vector2D vector(0, 0);
	float Rota = 0.02;

	if (!IsGamePlay || IsStatic)
		return;

	bool IsMove;
	if (KEY_LEFT)
	{
		RotationAngle -= Rota * PlayWay * rinSpeed;
		People->SetTextureStartPos(0, 0);
		IsMove = true;
	}
	else if (KEY_RIGHT)
	{
		RotationAngle += Rota * PlayWay *rinSpeed;
		People->SetTextureStartPos(0, PeoHeight);
		IsMove = true;
	}
	else
		IsMove = false;

	if (RotationAngle > 180 || RotationAngle<-180)
		RotationAngle = 0;
	People->SetRotationAngle(RotationAngle);

	if (KEY_SPACE)
		bIsFly = true;


	fTime += fDelataTime;
	if (fTime >= 0.06 && bIsFly && !bIsDown)//��
	{
		fTime = 0;
		fFlyDistance += 5;
		if (fFlyDistance >= 45)
			bIsDown = true;
		People->SetTextureStartPos(0, PeoHeight * 2);
	}
	if (fTime >= 0.06 && bIsFly && bIsDown)//����
	{
		fTime = 0;
		fFlyDistance -= 7;
		if (fFlyDistance <= 0)
		{
			bIsDown = false;
			bIsFly = false;
		}
		People->SetTextureStartPos(0, PeoHeight * 4);
	}

	if (IsMove || bIsFly)
		People->Resume();
	else
		People->Stop();

	if (!bIsFly)
		vector.SetPos(0.0f, -189.5f - PeoHeight);
	else
		vector.SetPos(0.0f, -189.5f - PeoHeight - fFlyDistance);

	vector.rotate(RotationAngle);
	People->SetPos(433 - 8 + vector.GetX(), 303 - 20 + vector.GetY());
}

void Earth::PeoFirst()
{
	RotationAngle = 0;
	People->Play();
	People->SetTextureStartPos(0, 0);
	People->SetRotationAngle(RotationAngle);
	People->SetPos(oldPos.x, oldPos.y);
}

void Earth::GetPeopleXandY()
{
	PeopleXaY.x = People->GetXPos();
	PeopleXaY.y = People->GetYPos();
}

/*��ʱ��*/

void Earth::Selecthf()
{
	hf = (HFONT)GetStockObject(BLACK_PEN);
	SetTextColor(hdcMem, RGB(218, 218, 218));//�޸�������ɫ
	SetBkMode(hdcMem, TRANSPARENT);//͸������
	SelectObject(hdcMem, hf);
}

void Earth::Delecthf()
{
	DeleteObject(hf);
}

void Earth::TimerUpdate(float fDeltaTime)
{
	fD += fDeltaTime;

	if (!IsGamePlay)
		return;

	if (fD % 250 == 0)
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

void Earth::TimeFirst()
{
	GameTime_msec = 0;
	GameTime_sec = 0;
	GameTime_min = 0;
	fD = 0;
}

void Earth::TimerShow()
{
	int iLength;
	TCHAR szBuffer[15];
	if (IsGamePlay)
	{
		iLength = wsprintf(szBuffer, TEXT("ʱ�䣺%d.%d.%d"), GameTime_min, GameTime_sec, GameTime_msec);
		TextOut(hdcMem, 10, 5, szBuffer, iLength);
	}
	else
	{
		int m = (int)GameTime[GetGameMunber()];
		int s = (GameTime[GetGameMunber()] - m) * 100;
		iLength = wsprintf(szBuffer, TEXT("��ʱ��%d��%d��"), m, s);
		TextOut(hdcMem, 10, 5, szBuffer, iLength);
	}
}

/*�ϰ�*/
void Earth::GetHinder()
{
	for (int i = 0; i < HinderNumber; i++)
	{
		Hinder[0][i] = pSpriteManager->CreateAnimationSprite(TEXT("���ϰ�1"), 1, 1, 0, 0, 1, 1);
		//Hinder[0][i]->SetSpriteRect(-5, -12);

		Hinder[1][i] = pSpriteManager->CreateAnimationSprite(TEXT("��צ���ϰ�"), 4, 20, 0, 0, 4, 1);
		//Hinder[1][i]->SetSpriteRect(-20, -20);
		Hinder[1][i]->SetColorKey(Hinder[1][i]->GetPixelColor(5, 75));

		Hinder[2][i] = pSpriteManager->CreateAnimationSprite(TEXT("��"), 1, 1, 0, 0, 1, 1);
		//Hinder[2][i]->SetSpriteRect(-8, -8);

		Hinder[3][i] = pSpriteManager->CreateAnimationSprite(TEXT("�ѹ�Ӣ"), 1, 1, 0, 0, 1, 1);
		//Hinder[3][i]->SetSpriteRect(-2, -2);

		Hinder[4][i] = pSpriteManager->CreateAnimationSprite(TEXT("ˮ���ϰ�"), 1, 1, 0, 0, 1, 1);
		//Hinder[4][i]->SetSpriteRect(-1, -1);

		Hinder[5][i] = pSpriteManager->CreateAnimationSprite(TEXT("����"), 1, 1, 0, 0, 1, 1);
		//Hinder[5][i]->SetSpriteRect(-1, -1);

		Hinder[6][i] = pSpriteManager->CreateAnimationSprite(TEXT("���ϰ�"), 1, 1, 0, 0, 1, 1);
		//Hinder[6][i]->SetSpriteRect(-3, -3);

	}

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < HinderNumber; j++)
		{
			Hinder[i][j]->SetVisible(false);
			HinderSpeed[i][j] = 0;//�ٶ�
		}
		HinderNum[i] = 0;//����
		IsBSee[i] = 0;//״̬
	}
}

void Earth::DelectHinder()
{
	for (int i = 0; i <= 7; i++)
	{
		for (int j = 0; j < HinderNumber; j++)
		{
			pSpriteManager->DeleteSprite(Hinder[i][j]);//����
		}
	}
}

void Earth::HinderErase()
{
	for (int i = 0; i < GetGameMunber(); i++)
	{
		for (int j = 0; j < HinderNum[i]; j++)
		{
			Hinder[i][j]->SetVisible(false);
		}
		HinderNum[i] = 0;//����
	}
	PlayWay = 1;
	rinSpeed = 1;
}

void Earth::HinderCreate()
{

	srand((unsigned)time(NULL));
		/*��*/
		if (GetGameMunber() == 1 || GetGameMunber() > 1)
		{
			int Num;
			if (GetGameMunber()<5)
				Num = 10;
			else
				Num = 2 + GetGameMunber();
			for (int i = 0; i <= Num; i++)
			{
				int y = int(rand() % rectClient.bottom) + 1;
				if (i % 2 == 0)
					Hinder[0][HinderNum[0]++]->SetPos(rectClient.right, y);

				else
				{
					pSpriteManager->DeleteSprite(Hinder[0][HinderNum[0]++]);
					Hinder[0][HinderNum[0] - 1] = pSpriteManager->CreateAnimationSprite(TEXT("���ϰ�2"), 1, 1, 0, 0, 1, 1);

					Hinder[0][HinderNum[0]-1]->SetPos(rectClient.left, y);
					/*Hinder[0][HinderNum[0] - 1]->SetTexturePos(0, Hinder[0][HinderNum[0] - 1]->GetHeight());*/
					IsLeft[0][HinderNum[0] - 1] = 1;
				}
				HinderSpeed[0][HinderNum[0] - 1] = rand() % 13 + 1;
				//Hinder[0][HinderNum[0] - 1]->SetTransparent(true);
				Hinder[0][HinderNum[0] - 1]->SetVisible(true);
			}
			
		}

		/*��צ��*/
		if (GetGameMunber() == 2 || GetGameMunber() > 2)
		{
			int Num = GetGameMunber();
			if (GetGameMunber() < 4)
				Num = GetGameMunber();
			else
				Num = 3;
			int k = rand() % 2 + 1;
			for (int i = 0; i <= Num; i++)
			{
				int x = int(rand() % rectClient.right) + 1;
				Hinder[1][HinderNum[1]++]->SetPos(x, rectClient.bottom);
				Hinder[1][HinderNum[1] - 1]->Play();
				Hinder[1][HinderNum[1] - 1]->SetTransparent(true);
				HinderSpeed[1][HinderNum[1] - 1] = k++;
				Hinder[1][HinderNum[1] - 1]->SetVisible(true);
			}
		}

		/*ˮ��*/
		if (GetGameMunber() == 5 || GetGameMunber() > 5)
		{
			int Num = GetGameMunber()+4;
			for (int i = 0; i <= Num; i++)
			{
				int x = int(rand() % rectClient.right) + 1;
				Hinder[4][HinderNum[4]++]->SetPos(x,rectClient.top);
				Hinder[4][HinderNum[4] - 1]->SetTransparent(true);
				HinderSpeed[4][HinderNum[4] - 1] = rand() % 24 + 1;
				Hinder[4][HinderNum[4] - 1]->SetVisible(true);
			}
		}

		/*����*/
		if (GetGameMunber() == 6 || GetGameMunber() > 6)
		{
			int Num = GetGameMunber();
			for (int i = 0; i <= Num; i++)
			{
				int x = int(rand() % rectClient.right) + 1;
				Hinder[5][HinderNum[5]++]->SetPos(x,rectClient.top);
				Hinder[5][HinderNum[5] - 1]->SetTransparent(true);
				HinderSpeed[5][HinderNum[5] - 1] = rand() % 8 + 1;
				Hinder[5][HinderNum[5] - 1]->SetVisible(true);
			}
		}

		/*��*/
		if (GetGameMunber() == 7 || GetGameMunber() > 7)
		{
			int Num = GetGameMunber();
			for (int i = 0; i <= Num; i++)
			{
				int y = int(rand() % rectClient.bottom) + 1;
				if (i % 2 == 0)
					Hinder[6][HinderNum[6]++]->SetPos(rectClient.right, y);
				else
				{
					Hinder[6][HinderNum[6]++]->SetPos(rectClient.left, y);
					IsLeft[1][HinderNum[6] - 1] = 1;
				}
				Hinder[6][HinderNum[6] - 1]->SetTransparent(true);
				HinderSpeed[6][HinderNum[6] - 1] = rand() % 9+1;
				Hinder[6][HinderNum[6] - 1]->SetVisible(true);
			}
		}

}

void Earth::HinderShow_static()
{
	srand((unsigned)time(NULL));

	/*��*/
	if (GameMunber == 3 || GameMunber > 3)
	{
		int Num = GetGameMunber()-1;
		if (Num > 5)
			Num = 3;
		Vector2D vector(0, 0);
		float Ro = rand()%30 +1;

		for (int i = 0; i < Num; i++)
		{
			/*λ��*/
			if (Ro >= 180)
				Ro = 0;
			Ro += 10;
			vector.SetPos(0.0f, -185.0f - Hinder[2][0]->GetHeight());
			Hinder[2][i]->SetRotationAngle(Ro);
			vector.rotate(Ro);
			Hinder[2][i]->SetPos(433 - 8 + vector.GetX(), 303 - 19 + vector.GetY());

			///*����*/
			Hinder[2][i]->SetTransparent(true);

			/*�ɼ�*/
			Hinder[2][i]->SetVisible(true);

			HinderNum[2]++;//�ϰ�������
		}
	}

	/*�ѹ�Ӣ*/
	if (GameMunber == 4 || GameMunber > 4)
	{
		int Num = GetGameMunber()-2;
		if (Num > 5)
			Num = 4;
		Vector2D vector(0, 0);
		float Ro = rand()%10+1;

		for (int i = 0; i < Num; i++)
		{
			/*λ��*/
			if (Ro >= 180)
				Ro = 0;
			Ro += 8;
			vector.SetPos(0.0f, -189.5f - Hinder[3][0]->GetHeight());
			vector.rotate(Ro);
			Hinder[3][i]->SetRotationAngle(Ro);
			Hinder[3][i]->SetPos(433 - 7 + vector.GetX(), 303 - 19 + vector.GetY());

			/*����*/
			Hinder[3][i]->SetTransparent(true);

			/*�ɼ�*/
			Hinder[3][i]->SetVisible(true);

			HinderNum[3]++;//�ϰ�������
		}
	}
}

void Earth::HinderMove()
{
	if (!IsGamePlay)
		return;

	for (int i = 0; i <= GetGameMunber(); i++)
	{
		if (i == 2 || i == 3)//�̶�λ��
			continue;

		if (i == 0 || i == 6)//�����ƶ�
		{
			for (int j = 0; j < HinderNum[i]; j++)
			{
				/*�ƶ�*/
				int k = 0;
				if (i == 6)
					k = 1;
				if (IsLeft[k][j])
					Hinder[i][j]->SetPos(Hinder[i][j]->GetXPos() + HinderSpeed[i][j], Hinder[i][j]->GetYPos());
				else
					Hinder[i][j]->SetPos(Hinder[i][j]->GetXPos() - HinderSpeed[i][j], Hinder[i][j]->GetYPos());

				/*������Ļ*/
				if (Hinder[i][j]->GetXPos()>rectClient.right)//�����ұ�
					Hinder[i][j]->SetPos(0, Hinder[i][j]->GetYPos());
				if (Hinder[i][j]->GetXPos()<rectClient.left)//�������
					Hinder[i][j]->SetPos(rectClient.right, Hinder[i][j]->GetYPos());
			}
		}

		if (i == 4 || i == 5)// ���������ƶ�
		{
			for (int j = 0; j < HinderNum[i]; j++)
			{
				/*�ƶ�*/
				Hinder[i][j]->SetPos(Hinder[i][j]->GetXPos(), Hinder[i][j]->GetYPos() + HinderSpeed[i][j]);

				/*������Ļ*/
				if (Hinder[i][j]->GetYPos()>rectClient.bottom)
					Hinder[i][j]->SetPos(Hinder[i][j]->GetXPos(), 0);
			}
		}

		if (i == 1)//��צ��
		{
			static float RO = 0.0;
			for (int j = 0; j < HinderNum[i]; j++)
			{
				RO += 0.01;
				int h;
				if (j % 2 == 0)
					h = 13 * sin(RO);
				else
					h = 35 * cos(RO);
				Hinder[1][j]->SetPos(Hinder[i][j]->GetXPos() + h, Hinder[i][j]->GetYPos() - HinderSpeed[i][j]);

				/*������Ļ*/
				if (Hinder[1][j]->GetYPos()<rectClient.top)
					Hinder[1][j]->SetPos(Hinder[i][j]->GetXPos(), rectClient.bottom);
			}
		}

	}
}

void Earth::HinderTouch(float fDelataTime)
{
	switch (GetGameMunber())
	{
	case 1:
		TouchDie(0);
		break;

	case 2:
		TouchDie(0);
		TouchDie(1);
		break;

	case 3:
		TouchDie(0);
		TouchDie(1);
		Reverse(fDelataTime);
		break;

	case 4:
		TouchDie(0);
		TouchDie(1);
		Reverse(fDelataTime);
		ChangeSide();
		break;

	case 5:
		TouchDie(0);
		TouchDie(1);
		Reverse(fDelataTime);
		ChangeSide();
		rin();
		break;

	case 6:
		TouchDie(0);
		TouchDie(1);
		Reverse(fDelataTime);
		ChangeSide();
		rin();
		light(fDelataTime);
		break;

	case 7:
		TouchDie(0);
		TouchDie(1);
		Reverse(fDelataTime);
		ChangeSide();
		rin();
		light(fDelataTime);
		TouchNoSee();
		break;

	default:
		break;
	}

}

void Earth::TouchDie(int p)
{
	for (int i = 0; i < HinderNum[p]; i++)
	{
		if (Hinder[p][i]->CollideWith(*People))
			GameOver();
	}
}

void Earth::Reverse(float fDelataTime)
{
	static int k = 0,n = 0;
	static bool IsTouch = 0;
	static float ft = 0;
	//if (IsTouch)
	//{
	//	ft += fDelataTime;
	//	if (ft < 1)
	//		return;
	//	if (!Hinder[2][n]->CollideWith(*People))
	//	{
	//			IsTouch = 0;
	//			ft = 0;
	//	}
	//	else
	//		return;
	//}
		

	for (int i = 0; i < HinderNum[2]; i++)
	{
		if (Hinder[2][i]->CollideWith(*People))
		{
			if (++k % 2 == 0)
			{
				PlayWay = 1;			
				RotationAngle += 0.5;
			}

			else
			{
				PlayWay = -1;
				RotationAngle -= 0.5;
			}
			IsTouch = 1;
			n = i;
		}
	}

}

void Earth::ChangeSide()
{
	for (int i = 0; i < HinderNum[3]; i++)
	{
		if (Hinder[3][i]->CollideWith(*People))
		{
			srand(time(NULL));
			float R = rand() % 20+1;
			RotationAngle += R;
		}
	}
}

void Earth::rin()
{
	srand((unsigned)time(NULL));
	rinSpeed = int(rand() % 5) + 1;
}

void Earth::light(float fDelataTime)
{
	static float fT = 0;
	if (IsStatic)
	{
		fT += fDelataTime;
		if (fT > 1)
		{
			fT = 0;
			IsStatic = false;
		}
		return;
	}

	for (int i = 0; i < HinderNum[5]; i++)
	{
		if (Hinder[5][i]->CollideWith(*People))
		{
			IsStatic = true;
			break;
		}
	}
}

void Earth::TouchNoSee()
{
	static int f[3] = { 0 };
	for (int i = 0; i < HinderNum[6]; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (IsGetFood[j])
				continue;
			if (Hinder[6][i]->CSprite::CollideWith(*GFood[j]))
			{
				GFood[j]->SetVisible(false);
				f[j] = i;
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (f[i])
		{
			if (Hinder[6][f[i]]->CSprite::CollideWith(*GFood[i]) != true)
			{
				GFood[i]->SetVisible(true);
				f[i] = 0;
			}
		}
	}
}

