
#include"DemoGame.h"
#include <ctime>
#define KEY_LEFT(key)  (GetKeyState(key) & 0x80)>0 ? true : false
#define KEY_RIGHT(key)  (GetKeyState(key) & 0x80)>0 ? true : false
#define KEY_SPACE(key)  (GetKeyState(key) & 0x80)>0 ? true : false

CDemoGame::CDemoGame(HWND hwnd, int fps):CGame(hwnd, fps)
{
	Init(); 
}
CDemoGame::~CDemoGame(void)
{
}

void CDemoGame::Init()
{
	CGame::Init();

	GetPicture();

	/*��Ϸ��ʼ����*/
	GameStart = pSpriteManager->CreateAnimationSprite(TEXT("��ʼ"),2,1,0,0);
	GameStart->SetPos(0, 0);
	//GameStart->SetVisible(false);
	
	/*��Ϸѡ�ؽ���*/
	int xxm = 40, yym = 90,ww,hh;
	GamePass[0] = pSpriteManager->CreateAnimationSprite(TEXT("���ֹؿ�"),2,1,xxm,yym,2,4);
	ww = GamePass[0]->GetDestWidth(); hh = GamePass[0]->GetDestHeight();
	GamePass[1] = pSpriteManager->CreateAnimationSprite(TEXT("��ؿ�"), 2, 1, 2*xxm+ww, yym,2,5);
	GamePass[2] = pSpriteManager->CreateAnimationSprite(TEXT("��צ��ؿ�"), 2, 1, 3*xxm+2*ww, yym,2,5);
	GamePass[3] = pSpriteManager->CreateAnimationSprite(TEXT("���ؿ�"), 2, 1, 4*xxm+3*ww, yym,2,5);
	GamePass[4] = pSpriteManager->CreateAnimationSprite(TEXT("�ѹ�Ӣ�ؿ�"), 2, 1, xxm, 20+hh+yym,2,5);
	GamePass[5] = pSpriteManager->CreateAnimationSprite(TEXT("ˮ�ιؿ�"), 2, 1, 2 * xxm + ww, 20 + hh + yym, 2, 5);
	GamePass[6] = pSpriteManager->CreateAnimationSprite(TEXT("����ؿ�"), 2, 1, 3 * xxm + 2 * ww, 20 + hh + yym, 2, 5);
	GamePass[7] = pSpriteManager->CreateAnimationSprite(TEXT("�ƹؿ�"), 2, 1, 4 * xxm + 3 * ww, 20 + hh + yym, 2, 5);
	for (int i = 0; i < 8; i++)
	{
		GamePass[i]->SetVisible(false);
	}

	/*��Ϸ����*/
	GameScreen = pSpriteManager->CreateAnimationSprite(TEXT("��"),1,1,0,0,1,4);//��ͼ
	GameScreen->SetPos(0, 0);
	GameScreen->SetVisible(false);


	/*�ϰ�*/
	HinderFirst();
	for (int i = 0; i < 8; i++)
	{
		HinderNum[i] = 0;
		for (int j = 0; j < HinderNumber; j++)
		{
			HinderSpeed[i][j] = 0;
		}
			
	}

	
	/*����*/
	int hk;
	
	Again = pSpriteManager->CreateAnimationSprite(TEXT("����"),2,1,775,20,2,1);
	hk = Again->GetDestHeight();
	Back = pSpriteManager->CreateAnimationSprite(TEXT("����"),2,1,775+hk+10,20,2,1);
	Fail = pSpriteManager->CreateSprite(TEXT("����"));
	Fail->SetPos(690, 25);
	Success = pSpriteManager->CreateSprite(TEXT("ͨ��"));
	Success->SetPos(710, 25);
	for (int i = 0; i < 3;i++)
		GFood[i] = pSpriteManager->CreateSprite(TEXT("��ȡ����"));
	for (int i = 0; i < 3;i++)
		GFood[i]->SetVisible(false);
	Again->SetVisible(false);
	Back->SetVisible(false);
	Fail->SetVisible(false);
	Success->SetVisible(false);


	People = pSpriteManager->CreateAnimationSprite(TEXT("people"), 4, 10,0, 0,4,6);
	People->SetVisible(false);

	People->SetTransparent(true);
	People->SetColorKey(People->GetPixelColor(0, 0));

	int x = GameScreen->GetWidth() / 2 - People->GetWidth() / 2;
	People->SetPos(x, 70);

	/*POINT PP = {433,303};
	People->SetHotSpot(PP);*/
	//People->Play();

	GameTime_min = 0;//ʱ��ֲ���
	GameTime_sec = 0;//ʱ���벿��
	GameTime_msec = 0;//ʱ����벿��
	IsGameS = false;//�Ƿ�ͨ��
	for (int i = 0; i < 3; i++)//���ʳ��
	{
		IsGetHFood[i] = false;
	}
	
	//ͨ��״̬
	for (int i = 0; i < 8; i++)
	{
		IsGamePass[i] = false; GameTime[i] = 0; IsPassSelect[i] = true;
	}
	IsPassSelect[0] = true;
		
	//�ϰ�״̬
	for (int i = 0; i < 7; i++)
		IsBSee[i] = 0;
	Mpoint = { 0, 0 };
	Cpoint = { 0, 0 };
	GameP = 1;
	RotationAngle = 0;

	rGameStart = { 378, 120, 473,145 };
	ss = { 237, 95, 616, 474 };
	PeoHeight = People->GetHeight();
	PeoWidth = People->GetWidth();
	oldPos = { People->GetXPos() + PeoWidth / 2, People->GetYPos() };

	
	hf = (HFONT)GetStockObject(BLACK_PEN);
	SetTextColor(hdcMem, RGB(218, 218, 218));//�޸�������ɫ
	SetBkMode(hdcMem, TRANSPARENT);//͸������
	//SetBkColor(hdcMem, RGB(52, 49, 49));
	DeleteObject(hf);

	bIsFly = false;
	bIsDown = false;
	fFlyDistance = 0;
	GameMunber = 0;
	PlayWay = 1;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < HinderNumber; j++)
			IsLeft[i][j] = 0;
	}
	rinSpeed = 1;
}

void CDemoGame::GetPicture()
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

	/*�ؿ�*/
	pResManager->LoadPictureFromFile(TEXT("��צ��ؿ�"), TEXT("image/�ؿ�/��צ��.bmp"));
	pResManager->LoadPictureFromFile(TEXT("���ֹؿ�"), TEXT("image/�ؿ�/����.bmp"));
	pResManager->LoadPictureFromFile(TEXT("�ѹ�Ӣ�ؿ�"), TEXT("image/�ؿ�/�ѹ�Ӣ.bmp"));
	pResManager->LoadPictureFromFile(TEXT("����ؿ�"), TEXT("image/�ؿ�/����.bmp"));
	pResManager->LoadPictureFromFile(TEXT("���ؿ�"), TEXT("image/�ؿ�/��.bmp"));
	pResManager->LoadPictureFromFile(TEXT("ˮ�ιؿ�"), TEXT("image/�ؿ�/ˮ��.bmp"));
	pResManager->LoadPictureFromFile(TEXT("��ؿ�"), TEXT("image/�ؿ�/��.bmp"));
	pResManager->LoadPictureFromFile(TEXT("�ƹؿ�"), TEXT("image/�ؿ�/��.bmp"));
}

void CDemoGame::Update(float fDeltaTime)
{
	CGame::Update(fDeltaTime);
	//static float fTime = 0;
	//fTime += fDeltaTime;


	if (IsGamePlay)
	{
		People->Update(fDeltaTime);
		HinderCreate(fDeltaTime);
		HinderMove();
		//HinderTouch(fDeltaTime);
	}	

	PeoMove(fDeltaTime);
	GetFood();
	TimerUpdate(fDeltaTime);
	MouseMove();
	MouseClick();
}

void CDemoGame::Render()
{
	CGame::Render();
	/*if (IsGamePlay)
	{
		Rectangle(hdcMem,ss.left,ss.top,ss.right,ss.bottom);
		BitBlt(hdc, 0, 0, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, hdcMem, 0, 0, SRCCOPY);
	}*/
	TimerShow();
	BitBlt(hdc, 0, 0, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, hdcMem, 0, 0, SRCCOPY);
	
}

void CDemoGame::PeoMove(float fDelataTime)//��1��2����3����4����5����6
{
	static float fTime;
	Vector2D vector(0, 0);
	float Rota = 0.01;
	
	if (!IsGamePlay && GameP==2)
	{
		RotationAngle = 0;
		People->SetTextureStartPos(0, 0);
		People->SetRotationAngle(RotationAngle);
		vector.SetPos(0.0f, -189.5f - PeoHeight);
		vector.rotate(RotationAngle);
		People->SetPos(433 - 8 + vector.GetX(), 303 - 20 + vector.GetY());
		return;
	}

	if (!IsGamePlay &&GameP == 3)
		return;

	if (IsStatic)
		return;

	bool IsMove;
	if (KEY_LEFT(VK_LEFT))
	{
		RotationAngle -= Rota * PlayWay * rinSpeed;
		People->SetTextureStartPos(0, 0);
		IsMove = true;
	}
	else if (KEY_RIGHT(VK_RIGHT))
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

	if (KEY_SPACE(VK_SPACE))
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

void CDemoGame::MouseSide()
{
	GetCursorPos(&Mpoint);            // ��ȡ���ָ��λ�ã���Ļ���꣩
	ScreenToClient(hWnd, &Mpoint);    // �����ָ��λ��ת��Ϊ��������
}

void CDemoGame::MouseCSide(LPARAM lParam)
{
	Cpoint.x = LOWORD(lParam);
	Cpoint.y = HIWORD(lParam);
}

void CDemoGame::MouseMove()
{
	/*��ʼ����*/
	if(GameP == 1)
	{
		if (Mpoint.x >= rGameStart.left&&Mpoint.x <= rGameStart.right&&Mpoint.y >= rGameStart.top&&Mpoint.y <= rGameStart.bottom)
		{
			int h = GameStart->GettexHeight() / 2;
			GameStart->SetTexturePos(0, h);
		}
		else
		{
			GameStart->SetTexturePos(0, 0);
		}
	}
	

	/*��Ϸѡ�ؽ���*/
	static bool GP[8] = { false };
	if(GameP == 2)
	{
		for (int i = 0; i < 8; i++)
		{
			if (GamePass[i]->IsSelected(Mpoint.x, Mpoint.y))
			{
				if (GP[i])//��������ʹ����žͲ��ü��
					continue;

				int x = GamePass[i]->GettexWidth()/2;
				int y = GamePass[i]->GetTYpos();
				GamePass[i]->SetTexturePos(x,y);
				GP[i] = true;
			}
			else
			{
				if (GP[i] == false)
					continue;

				int y = GamePass[i]->GetTYpos();
				GamePass[i]->SetTexturePos(0, y);
				GP[i] = false;
			}
		}
	}
	
	/*��Ϸ����*/
	if (GameP == 3)
	{
		if (Back->IsSelected(Mpoint.x, Mpoint.y))//����
		{
			int x = Back->GettexWidth() / 2;
			Back->SetTexturePos(x, 0);
		}
		else
			Back->SetTexturePos(0, 0);

		if (Again->IsSelected(Mpoint.x, Mpoint.y))//����
		{
			int x = Again->GettexWidth() / 2;
			Again->SetTexturePos(x, 0);
		}
		else
			Again->SetTexturePos(0, 0);
	}
	
}

void CDemoGame::MouseClick()
{
	/*��ʼ����-ѡ��*/
	if (GameP==1 && Cpoint.x >= rGameStart.left&&Cpoint.x <= rGameStart.right&&Cpoint.y >= rGameStart.top&&Cpoint.y <= rGameStart.bottom)
	//if (x >= rGameStart.left && x <= rGameStart.right && y >= rGameStart.top && y <= rGameStart.bottom)
	{
		GameStart->SetVisible(false);
		for (int i = 0; i < 8; i++)
		{
			GamePass[i]->SetVisible(true);
		}
		GameP = 2;//������Ϸ״̬
	}

	/*��Ϸѡ�ؽ���-��Ϸ����*/
	if (GameP == 2)
	{
		for (int i = 0; i < 8; i++)
		{
			if (GamePass[i]->IsSelected(Cpoint.x, Cpoint.y))
			{
				if (!IsPassSelect[i])
						continue;

				for (int i = 0; i < 8; i++)
				{
					GamePass[i]->SetVisible(false);
				}
				GameScreen->SetVisible(true);//��ͼ
				People->SetVisible(true);//����������
				Again->SetVisible(true);//����
				Back->SetVisible(true);//����
				for (int i = 0; i < 3; i++)
					GFood[i]->SetVisible(true);//ʳ��

				People->Play();
				People->Stop();

				IsGamePlay = true;//��Ϸ��ʼ
				GameP = 3;

				SetFood();//����ʳ���λ��
				GameScreen->SetTexturePos(0, 0);

				GameMunber = i;//��ǰ�ؿ�����

				HinderShow_static();//��̬�ϰ��ĳ���
			}
		}
	}

	if (Back->IsSelected(Cpoint.x, Cpoint.y))
	{
		for (int i = 0; i < 8; i++)
		{
			GamePass[i]->SetVisible(true);
		}
		ChangePass();

		GameScreen->SetVisible(false);//��ͼ
		People->SetVisible(false);//����������
		Again->SetVisible(false);//����
		Back->SetVisible(false);//����
		GameP = 2;
		IsGamePlay = false;//��Ϸ����
		for (int i = 0; i < 3; i++)
			GFood[i]->SetVisible(false);//ʳ��

		HinderErase();
	}
		
	
}

void CDemoGame::TimerUpdate(float fDeltaTime)
{
	static int  fD = 0;
	if (!IsGamePlay)
	{
		if (GameTime_min|| GameTime_sec||GameTime_msec)
			GameTime[GameMunber] = GameTime_min + GameTime_sec*0.01;
		fD = 0;
		GameTime_msec = 0;
		GameTime_sec = 0;
		GameTime_min = 0;
		return;
	}
	
	fD += fDeltaTime;

	if (fD % 360 == 0)
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
	}
}

void CDemoGame::TimerShow()
{
	if (GameP != 3)
		return;

	int iLength;
	TCHAR szBuffer[15];
	if (IsGamePlay)
	{
		iLength = wsprintf(szBuffer, TEXT("ʱ�䣺%d.%d.%d"), GameTime_min, GameTime_sec, GameTime_msec);
		TextOut(hdcMem, 10, 5, szBuffer, iLength);
	}
	else
	{
		int m = (int)GameTime[GameMunber];
		int s = (GameTime[GameMunber] - m) * 100;
		iLength = wsprintf(szBuffer, TEXT("��ʱ��%d��%d��"),m, s);
		TextOut(hdcMem, 10, 5, szBuffer, iLength);
	}

}

void CDemoGame::SetFood()//9,12,19,3,4,6,0,21
{
	srand((unsigned)time(NULL));
	int RR[3], k;
	RR[2] = rand() % 23;
	if (RR[2] == 3 || RR[2] == 4 || RR[2] == 6)
		RR[2] += 4;
	if (RR[2]==0 || RR[2] == 9 || RR[2] == 12 || RR[2] == 19 || RR[2]==21)
		RR[2] += 2;
	for (int i = 1; i >= 0; i--)
	{
		RR[i] = RR[i+1] - 50;
	}
	Vector2D vector(0.0f, -189.5f - 26);
	for (int i = 0; i < 3; i++)
	{
		vector.rotate(RR[i]);
		GFood[i]->SetPos(433 -24 + vector.GetX(), 303 - 25 + vector.GetY());
	}
}

void CDemoGame::GetFood()
{
	static int FoodM = 0;

	if (!IsGamePlay && GameP == 2)
	{
		FoodM = 0;
		GameScreen->SetTexturePos(0, 567 * FoodM); 
		for (int i = 0; i < 3; i++)
			IsGetHFood[i] = false;
		return;
	}

	RECT rtIntersect;
	
	for (int i = 0; i < 3; i++)
	{
		if (IsGetHFood[i])
			continue;
		if (IntersectRect(&rtIntersect, GFood[i]->GetSpriteRect(), People->GetSpriteRect()))
		{
			GFood[i]->SetVisible(false);
			IsGetHFood[i] = true;
			FoodM += 1;
		}
	}
	if (FoodM)
		GameScreen->SetTexturePos(0, 567*FoodM);
	
	if (FoodM == 3)//��Ϸʤ��
	{
		IsGameS = true;
		FoodM = 0;
		IsGamePlay = false;
		IsGamePass[GameMunber] = true;
	}
		
}

void CDemoGame::ChangePass()
{
	int PassNumber = 0;
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
		if (!IsGamePass[i] && IsGamePass[i-1])
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

void CDemoGame::HinderCreate(float fDeltaTime)
{
	static float fTime = 0;
	fTime += fDeltaTime;
	srand((unsigned)time(NULL));

	if (fTime > 60)//ÿ����³���
	{
		fTime = 0;

		/*��*/
		if (GameMunber > 1 || GameMunber == 1)
		{
			int Num = int(rand()%15)+1;
			if (HinderNumber > HinderNum[1] + Num)
			{
				for (int i = 0; i <= Num; i++)
				{
					int y = rand() % rectClient.bottom+1;
					if (i % 2 == 0)
						Hinder[1][HinderNum[1]++]->SetPos(rectClient.right, y);
		
					else
					{
						Hinder[1][HinderNum[1]++]->SetPos(rectClient.left, y);
						Hinder[1][HinderNum[1] - 1]->SetTexturePos(0, Hinder[1][HinderNum[1] - 1]->GetHeight());
						IsLeft[0][HinderNum[1] - 1] = 1;
					}
					HinderSpeed[1][HinderNum[1] - 1] = rand() % 20 + 1;
					Hinder[1][HinderNum[1] - 1]->SetTransparent(true);
					Hinder[1][HinderNum[1] - 1]->SetVisible(true);
				}
			}
		}

		/*��צ��*/
		if (GameMunber > 2 || GameMunber == 2)
		{
			int Num = int(rand() %10)+1;
			if (HinderNumber > HinderNum[2] + Num)
			{
				for (int i = 0; i <= Num; i++)
				{
					int x = rand() % rectClient.right+1;
					Hinder[2][HinderNum[2]++]->SetPos(x, rectClient.bottom);
					Hinder[2][HinderNum[2]-1]->Play();			
					Hinder[2][HinderNum[2]- 1]->SetTransparent(true);
					HinderSpeed[2][HinderNum[2] - 1] = rand() % 8+1;	
					Hinder[2][HinderNum[2] - 1]->SetVisible(true);
				}
			}
		}

		/*ˮ��*/
		if (GameMunber > 5 || GameMunber == 5)
		{
			int Num = int(rand() % 26)+1;
			if (HinderNumber > HinderNum[5] + Num)
			{
				for (int i = 0; i <= Num; i++)
				{
					int y = rand() % rectClient.bottom+1;
					Hinder[5][HinderNum[5]++]->SetPos(rectClient.left, y);
					Hinder[5][HinderNum[5] - 1]->SetTransparent(true);
					HinderSpeed[5][HinderNum[5]-1] = rand() % 24+1;
					Hinder[5][HinderNum[5] - 1]->SetVisible(true);
				}
			}
		}

		/*����*/
		if (GameMunber > 6 || GameMunber == 6)
		{
			int Num = int(rand() % 15)+1;
			if (HinderNumber > HinderNum[6] + Num)
			{
				for (int i = 0; i <= Num; i++)
				{
					int y = rand() % rectClient.bottom+1;
					Hinder[6][HinderNum[6]++]->SetPos(rectClient.left, y);
					Hinder[6][HinderNum[6] - 1]->SetTransparent(true);
					HinderSpeed[6][HinderNum[6]+1] = rand() % 24+1;
					Hinder[6][HinderNum[6] - 1]->SetVisible(true);
				}

			}
		}

		/*��*/
		if (GameMunber > 7 || GameMunber == 7)
		{
			int Num = int(rand() % 10)+1;
			if (HinderNumber > HinderNum[7] + Num)
			{
				for (int i = 0; i <= Num; i++)
				{
					int y = rand() % rectClient.bottom+1;
					if (i % 2 == 0)
						Hinder[7][HinderNum[7]++]->SetPos(rectClient.right, y);
					else
					{
						Hinder[7][HinderNum[7]++]->SetPos(rectClient.left, y);
						IsLeft[1][HinderNum[7] - 1] = 1;
					}
					Hinder[7][HinderNum[7] - 1]->SetTransparent(true);
					HinderSpeed[7][HinderNum[7] - 1] = rand() % 15;
					Hinder[7][HinderNum[7] - 1]->SetVisible(true);
				}
			}
		}


	}
	
}

void CDemoGame::HinderShow_static()
{
	srand((unsigned)time(NULL));

	/*��*/
	if (GameMunber > 3 || GameMunber == 3)
	{
		int Num = rand() % 9+1;
		Vector2D vector(0, 0);
		float Ro = 30.0;
	
		for (int i = 0; i < Num; i++)
		{
			/*λ��*/
			if (Ro > 180)
				Ro = 0;
			Ro += rand() % 15;	
			vector.SetPos(0.0f, -185.0f - Hinder[3][0]->GetHeight());
			Hinder[3][i]->SetRotationAngle(Ro);
			vector.rotate(Ro);
			Hinder[3][i]->SetPos(433 - 8 + vector.GetX(), 303 - 19 + vector.GetY());

			/*����*/
			Hinder[3][i]->SetTransparent(true);

			/*�ɼ�*/
			Hinder[3][i]->SetVisible(true);

			HinderNum[3]++;//�ϰ�������
		}
	}
	
	/*�ѹ�Ӣ*/
	if (GameMunber > 4 || GameMunber == 4)
	{
		int Num = rand() % 5+1;
		Vector2D vector(0, 0);
		float Ro = 20.0;
		
		for (int i = 0; i < Num; i++)
		{
			/*λ��*/
			if (Ro > 180)
				Ro= 0;
			Ro += rand() % 20;
			vector.SetPos(0.0f, -189.5f  -Hinder[4][0]->GetHeight());
			vector.rotate(Ro);
			Hinder[4][i]->SetRotationAngle(Ro);
			Hinder[4][i]->SetPos(433 -7 + vector.GetX(), 303 - 19 + vector.GetY());

			/*����*/
			Hinder[4][i]->SetTransparent(true);

			/*�ɼ�*/
			Hinder[4][i]->SetVisible(true);

			HinderNum[4]++;//�ϰ�������
		}
	}
}

void CDemoGame::HinderFirst()
{
	for (int i = 0; i < HinderNumber; i++)
	{
		Hinder[1][i] = pSpriteManager->CreateAnimationSprite(TEXT("���ϰ�"), 1, 1, 0, 0, 1, 2);
		Hinder[2][i] = pSpriteManager->CreateAnimationSprite(TEXT("��צ���ϰ�"), 4, 10, 0, 0, 4, 1);
		Hinder[3][i] = pSpriteManager->CreateAnimationSprite(TEXT("��"), 1, 1, 0, 0, 1, 1);
		Hinder[4][i] = pSpriteManager->CreateAnimationSprite(TEXT("�ѹ�Ӣ"), 1, 1, 0, 0, 1, 1);
		Hinder[5][i] = pSpriteManager->CreateAnimationSprite(TEXT("ˮ���ϰ�"), 1, 1, 0, 0, 1, 1);
		Hinder[6][i] = pSpriteManager->CreateAnimationSprite(TEXT("����"), 1, 1, 0, 0, 1, 1);
		Hinder[7][i] = pSpriteManager->CreateAnimationSprite(TEXT("���ϰ�"), 1, 1, 0, 0, 1, 1);
	}
	for (int i = 1; i <= 7; i++)
	{
		for (int j = 0; j < HinderNumber; j++)
		{
			Hinder[i][j]->SetVisible(false);
		}
	}

}

void CDemoGame::HinderVFail()
{
	for (int i = 1; i <= GameMunber; i++)
	{
		for (int j = 0; j < HinderNum[i]; j++)
		{
			pSpriteManager->DeleteSprite(Hinder[i][j]);//����
		}
	}
	
}

void CDemoGame::HinderErase()
{
	for (int i = 0; i < GameMunber; i++)
	{
		for (int j = 0; j < HinderNum[i]; j++)
		{
			Hinder[i][j]->SetVisible(false);
		}
		HinderNum[i] = 0;//����
	}
}

void CDemoGame::HinderMove()
{
	for (int i = 1; i <= GameMunber; i++)
	{
		if (i == 3 || i == 4)//�̶�λ��
			continue;

		if (i == 1 || i == 7)//�����ƶ�
		{
			for (int j = 0; j < HinderNum[i]; j++)
			{
				/*�ƶ�*/
				int k=1;
				if (i == 1)
					k = 0;
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

		if (i == 5 || i == 6)// ���������ƶ�
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

		if (i == 2)//��צ��
		{
			static float RO = 0.0;
			for (int j = 0; j < HinderNum[i]; j++)
			{
				RO += 0.01;
				int h;
				if (j % 2 == 0)
					h = 40 * sin(RO);
				else
					h = 40 * cos(RO);
				Hinder[2][j]->SetPos(Hinder[i][j]->GetXPos()+h , Hinder[i][j]->GetYPos()- HinderSpeed[i][j]);
			
				/*������Ļ*/
				if (Hinder[2][j]->GetYPos()<rectClient.top)
					Hinder[2][j]->SetPos(Hinder[i][j]->GetXPos(), rectClient.bottom);
			}
		}
	
	}
}

void CDemoGame::HinderTouch(float fDelataTime)
{
	if (GameMunber >= 1)
			TouchDie(1);

	if (GameMunber >= 2)
		TouchDie(2);

	if (GameMunber >= 3)
			Reverse();

	if (GameMunber >= 4)
			ChangeSide();

	if (GameMunber >= 5)
			rin();

	if (GameMunber >= 6)
		light(fDelataTime);

	if (GameMunber >= 7)
			TouchNoSee();
	
}

void CDemoGame::TouchDie(int p)
{
	for (int i = 0; i < HinderNum[p]; i++)
	{
		if (Hinder[p][i]->IsSelected(People->GetXPos(), People->GetYPos()))
		{
			IsGamePlay = false;
			IsGameS = false;
		}
	}
}

void CDemoGame::Reverse()
{
	static int k = 0;
	for (int i = 0; i < HinderNum[3]; i++)
	{
		if (Hinder[3][i]->IsSelected(People->GetXPos(), People->GetYPos()))
		{
			if (k++ % 2 == 0)
				PlayWay = 1;
			else
				PlayWay = -1;
		}
	}
	
}

void CDemoGame::ChangeSide()
{
	for (int i = 0; i < HinderNum[4]; i++)
	{
		if (Hinder[4][i]->IsSelected(People->GetXPos(), People->GetYPos()))
		{
			srand(time(NULL));
			float R = rand() % 50;
			RotationAngle += R;
		}
	}
}

void CDemoGame::rin()
{
	srand((unsigned)time(NULL));
	rinSpeed = int(rand() % 3) + 1;
}

void CDemoGame::light(float fDelataTime)
{
	if (IsStatic)
	{
		static float fT = 0;
		fT += fDelataTime;
		if (fT > 360)
		{
			fT = 0;
			IsStatic = false;
		}
		return;
	}

	for (int i = 0; i < HinderNum[6]; i++)
	{
		if (Hinder[6][i]->IsSelected(People->GetXPos(), People->GetYPos()))
		{
			IsStatic = true;
			break;
		}
	}
}

void CDemoGame::TouchNoSee()
{
	static int f[3] = { 0 };
	for (int i = 0; i < HinderNum[7]; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (Hinder[7][i]->IsSelected(GFood[j]->GetXPos(), GFood[j]->GetYPos()))
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
			if (!Hinder[7][i]->IsSelected(GFood[i]->GetXPos(), GFood[i]->GetYPos()))
				GFood[i]->SetVisible(true);
			f[i] = 0;
		}
	}
}

void CDemoGame::Erase()
{
	DeleteObject(hf);
	HinderVFail();//�ϰ�������
}