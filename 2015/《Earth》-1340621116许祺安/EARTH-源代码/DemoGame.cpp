
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

	/*游戏开始界面*/
	GameStart = pSpriteManager->CreateAnimationSprite(TEXT("开始"),2,1,0,0);
	GameStart->SetPos(0, 0);
	//GameStart->SetVisible(false);
	
	/*游戏选关界面*/
	int xxm = 40, yym = 90,ww,hh;
	GamePass[0] = pSpriteManager->CreateAnimationSprite(TEXT("练手关卡"),2,1,xxm,yym,2,4);
	ww = GamePass[0]->GetDestWidth(); hh = GamePass[0]->GetDestHeight();
	GamePass[1] = pSpriteManager->CreateAnimationSprite(TEXT("鱼关卡"), 2, 1, 2*xxm+ww, yym,2,5);
	GamePass[2] = pSpriteManager->CreateAnimationSprite(TEXT("八爪鱼关卡"), 2, 1, 3*xxm+2*ww, yym,2,5);
	GamePass[3] = pSpriteManager->CreateAnimationSprite(TEXT("树关卡"), 2, 1, 4*xxm+3*ww, yym,2,5);
	GamePass[4] = pSpriteManager->CreateAnimationSprite(TEXT("蒲公英关卡"), 2, 1, xxm, 20+hh+yym,2,5);
	GamePass[5] = pSpriteManager->CreateAnimationSprite(TEXT("水滴关卡"), 2, 1, 2 * xxm + ww, 20 + hh + yym, 2, 5);
	GamePass[6] = pSpriteManager->CreateAnimationSprite(TEXT("闪电关卡"), 2, 1, 3 * xxm + 2 * ww, 20 + hh + yym, 2, 5);
	GamePass[7] = pSpriteManager->CreateAnimationSprite(TEXT("云关卡"), 2, 1, 4 * xxm + 3 * ww, 20 + hh + yym, 2, 5);
	for (int i = 0; i < 8; i++)
	{
		GamePass[i]->SetVisible(false);
	}

	/*游戏界面*/
	GameScreen = pSpriteManager->CreateAnimationSprite(TEXT("鱼"),1,1,0,0,1,4);//地图
	GameScreen->SetPos(0, 0);
	GameScreen->SetVisible(false);


	/*障碍*/
	HinderFirst();
	for (int i = 0; i < 8; i++)
	{
		HinderNum[i] = 0;
		for (int j = 0; j < HinderNumber; j++)
		{
			HinderSpeed[i][j] = 0;
		}
			
	}

	
	/*道具*/
	int hk;
	
	Again = pSpriteManager->CreateAnimationSprite(TEXT("重来"),2,1,775,20,2,1);
	hk = Again->GetDestHeight();
	Back = pSpriteManager->CreateAnimationSprite(TEXT("返回"),2,1,775+hk+10,20,2,1);
	Fail = pSpriteManager->CreateSprite(TEXT("死亡"));
	Fail->SetPos(690, 25);
	Success = pSpriteManager->CreateSprite(TEXT("通关"));
	Success->SetPos(710, 25);
	for (int i = 0; i < 3;i++)
		GFood[i] = pSpriteManager->CreateSprite(TEXT("获取道具"));
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

	GameTime_min = 0;//时间分部分
	GameTime_sec = 0;//时间秒部分
	GameTime_msec = 0;//时间毫秒部分
	IsGameS = false;//是否通关
	for (int i = 0; i < 3; i++)//获得食物
	{
		IsGetHFood[i] = false;
	}
	
	//通关状态
	for (int i = 0; i < 8; i++)
	{
		IsGamePass[i] = false; GameTime[i] = 0; IsPassSelect[i] = true;
	}
	IsPassSelect[0] = true;
		
	//障碍状态
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
	SetTextColor(hdcMem, RGB(218, 218, 218));//修改字体颜色
	SetBkMode(hdcMem, TRANSPARENT);//透明背景
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
	/*道具*/
	pResManager->LoadPictureFromFile(TEXT("people"), TEXT("image/道具/people.bmp"));
	pResManager->LoadPictureFromFile(TEXT("返回"), TEXT("image/道具/返回.bmp"));
	pResManager->LoadPictureFromFile(TEXT("获取道具"), TEXT("image/道具/获取道具.bmp"));
	pResManager->LoadPictureFromFile(TEXT("死亡"), TEXT("image/道具/死亡.bmp"));
	pResManager->LoadPictureFromFile(TEXT("通关"), TEXT("image/道具/通关.bmp"));
	pResManager->LoadPictureFromFile(TEXT("重来"), TEXT("image/道具/重来.bmp"));

	/*地图*/
	pResManager->LoadPictureFromFile(TEXT("开始"), TEXT("image/地图/开始.bmp"));
	pResManager->LoadPictureFromFile(TEXT("八爪鱼"), TEXT("image/地图/八爪鱼.bmp"));
	pResManager->LoadPictureFromFile(TEXT("八爪鱼障碍"), TEXT("image/地图/八爪鱼障碍.bmp"));
	pResManager->LoadPictureFromFile(TEXT("练手"), TEXT("image/地图/练手.bmp"));
	pResManager->LoadPictureFromFile(TEXT("蒲公英"), TEXT("image/地图/蒲公英.bmp"));
	pResManager->LoadPictureFromFile(TEXT("闪电"), TEXT("image/地图/闪电.bmp"));
	pResManager->LoadPictureFromFile(TEXT("树"), TEXT("image/地图/树.bmp"));
	pResManager->LoadPictureFromFile(TEXT("水滴障碍"), TEXT("image/地图/水滴障碍.bmp"));
	pResManager->LoadPictureFromFile(TEXT("鱼"), TEXT("image/地图/鱼.bmp"));
	pResManager->LoadPictureFromFile(TEXT("鱼障碍"), TEXT("image/地图/鱼障碍.bmp"));
	pResManager->LoadPictureFromFile(TEXT("云障碍"), TEXT("image/地图/云障碍.bmp"));

	/*关卡*/
	pResManager->LoadPictureFromFile(TEXT("八爪鱼关卡"), TEXT("image/关卡/八爪鱼.bmp"));
	pResManager->LoadPictureFromFile(TEXT("练手关卡"), TEXT("image/关卡/练手.bmp"));
	pResManager->LoadPictureFromFile(TEXT("蒲公英关卡"), TEXT("image/关卡/蒲公英.bmp"));
	pResManager->LoadPictureFromFile(TEXT("闪电关卡"), TEXT("image/关卡/闪电.bmp"));
	pResManager->LoadPictureFromFile(TEXT("树关卡"), TEXT("image/关卡/树.bmp"));
	pResManager->LoadPictureFromFile(TEXT("水滴关卡"), TEXT("image/关卡/水滴.bmp"));
	pResManager->LoadPictureFromFile(TEXT("鱼关卡"), TEXT("image/关卡/鱼.bmp"));
	pResManager->LoadPictureFromFile(TEXT("云关卡"), TEXT("image/关卡/云.bmp"));
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

void CDemoGame::PeoMove(float fDelataTime)//左1右2跳左3跳右4下左5下右6
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
	if (fTime >= 0.06 && bIsFly && !bIsDown)//飞
	{
		fTime = 0;
		fFlyDistance += 5;
		if (fFlyDistance >= 45)
			bIsDown = true;
		People->SetTextureStartPos(0, PeoHeight * 2);
	}
	if (fTime >= 0.06 && bIsFly && bIsDown)//下落
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
	GetCursorPos(&Mpoint);            // 获取鼠标指针位置（屏幕坐标）
	ScreenToClient(hWnd, &Mpoint);    // 将鼠标指针位置转换为窗口坐标
}

void CDemoGame::MouseCSide(LPARAM lParam)
{
	Cpoint.x = LOWORD(lParam);
	Cpoint.y = HIWORD(lParam);
}

void CDemoGame::MouseMove()
{
	/*开始界面*/
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
	

	/*游戏选关界面*/
	static bool GP[8] = { false };
	if(GameP == 2)
	{
		for (int i = 0; i < 8; i++)
		{
			if (GamePass[i]->IsSelected(Mpoint.x, Mpoint.y))
			{
				if (GP[i])//如果本来就触碰着就不用检测
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
	
	/*游戏界面*/
	if (GameP == 3)
	{
		if (Back->IsSelected(Mpoint.x, Mpoint.y))//返回
		{
			int x = Back->GettexWidth() / 2;
			Back->SetTexturePos(x, 0);
		}
		else
			Back->SetTexturePos(0, 0);

		if (Again->IsSelected(Mpoint.x, Mpoint.y))//重玩
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
	/*开始界面-选关*/
	if (GameP==1 && Cpoint.x >= rGameStart.left&&Cpoint.x <= rGameStart.right&&Cpoint.y >= rGameStart.top&&Cpoint.y <= rGameStart.bottom)
	//if (x >= rGameStart.left && x <= rGameStart.right && y >= rGameStart.top && y <= rGameStart.bottom)
	{
		GameStart->SetVisible(false);
		for (int i = 0; i < 8; i++)
		{
			GamePass[i]->SetVisible(true);
		}
		GameP = 2;//更改游戏状态
	}

	/*游戏选关界面-游戏界面*/
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
				GameScreen->SetVisible(true);//地图
				People->SetVisible(true);//操作的人物
				Again->SetVisible(true);//重来
				Back->SetVisible(true);//返回
				for (int i = 0; i < 3; i++)
					GFood[i]->SetVisible(true);//食物

				People->Play();
				People->Stop();

				IsGamePlay = true;//游戏开始
				GameP = 3;

				SetFood();//设置食物的位置
				GameScreen->SetTexturePos(0, 0);

				GameMunber = i;//当前关卡关数

				HinderShow_static();//静态障碍的出现
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

		GameScreen->SetVisible(false);//地图
		People->SetVisible(false);//操作的人物
		Again->SetVisible(false);//重来
		Back->SetVisible(false);//返回
		GameP = 2;
		IsGamePlay = false;//游戏结束
		for (int i = 0; i < 3; i++)
			GFood[i]->SetVisible(false);//食物

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
		iLength = wsprintf(szBuffer, TEXT("时间：%d.%d.%d"), GameTime_min, GameTime_sec, GameTime_msec);
		TextOut(hdcMem, 10, 5, szBuffer, iLength);
	}
	else
	{
		int m = (int)GameTime[GameMunber];
		int s = (GameTime[GameMunber] - m) * 100;
		iLength = wsprintf(szBuffer, TEXT("用时：%d分%d秒"),m, s);
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
	
	if (FoodM == 3)//游戏胜利
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

	if (fTime > 60)//每秒更新出现
	{
		fTime = 0;

		/*鱼*/
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

		/*八爪鱼*/
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

		/*水滴*/
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

		/*闪电*/
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

		/*云*/
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

	/*树*/
	if (GameMunber > 3 || GameMunber == 3)
	{
		int Num = rand() % 9+1;
		Vector2D vector(0, 0);
		float Ro = 30.0;
	
		for (int i = 0; i < Num; i++)
		{
			/*位置*/
			if (Ro > 180)
				Ro = 0;
			Ro += rand() % 15;	
			vector.SetPos(0.0f, -185.0f - Hinder[3][0]->GetHeight());
			Hinder[3][i]->SetRotationAngle(Ro);
			vector.rotate(Ro);
			Hinder[3][i]->SetPos(433 - 8 + vector.GetX(), 303 - 19 + vector.GetY());

			/*背景*/
			Hinder[3][i]->SetTransparent(true);

			/*可见*/
			Hinder[3][i]->SetVisible(true);

			HinderNum[3]++;//障碍的数量
		}
	}
	
	/*蒲公英*/
	if (GameMunber > 4 || GameMunber == 4)
	{
		int Num = rand() % 5+1;
		Vector2D vector(0, 0);
		float Ro = 20.0;
		
		for (int i = 0; i < Num; i++)
		{
			/*位置*/
			if (Ro > 180)
				Ro= 0;
			Ro += rand() % 20;
			vector.SetPos(0.0f, -189.5f  -Hinder[4][0]->GetHeight());
			vector.rotate(Ro);
			Hinder[4][i]->SetRotationAngle(Ro);
			Hinder[4][i]->SetPos(433 -7 + vector.GetX(), 303 - 19 + vector.GetY());

			/*背景*/
			Hinder[4][i]->SetTransparent(true);

			/*可见*/
			Hinder[4][i]->SetVisible(true);

			HinderNum[4]++;//障碍的数量
		}
	}
}

void CDemoGame::HinderFirst()
{
	for (int i = 0; i < HinderNumber; i++)
	{
		Hinder[1][i] = pSpriteManager->CreateAnimationSprite(TEXT("鱼障碍"), 1, 1, 0, 0, 1, 2);
		Hinder[2][i] = pSpriteManager->CreateAnimationSprite(TEXT("八爪鱼障碍"), 4, 10, 0, 0, 4, 1);
		Hinder[3][i] = pSpriteManager->CreateAnimationSprite(TEXT("树"), 1, 1, 0, 0, 1, 1);
		Hinder[4][i] = pSpriteManager->CreateAnimationSprite(TEXT("蒲公英"), 1, 1, 0, 0, 1, 1);
		Hinder[5][i] = pSpriteManager->CreateAnimationSprite(TEXT("水滴障碍"), 1, 1, 0, 0, 1, 1);
		Hinder[6][i] = pSpriteManager->CreateAnimationSprite(TEXT("闪电"), 1, 1, 0, 0, 1, 1);
		Hinder[7][i] = pSpriteManager->CreateAnimationSprite(TEXT("云障碍"), 1, 1, 0, 0, 1, 1);
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
			pSpriteManager->DeleteSprite(Hinder[i][j]);//清理
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
		HinderNum[i] = 0;//数量
	}
}

void CDemoGame::HinderMove()
{
	for (int i = 1; i <= GameMunber; i++)
	{
		if (i == 3 || i == 4)//固定位置
			continue;

		if (i == 1 || i == 7)//横向移动
		{
			for (int j = 0; j < HinderNum[i]; j++)
			{
				/*移动*/
				int k=1;
				if (i == 1)
					k = 0;
				if (IsLeft[k][j])
					Hinder[i][j]->SetPos(Hinder[i][j]->GetXPos() + HinderSpeed[i][j], Hinder[i][j]->GetYPos());
				else
					Hinder[i][j]->SetPos(Hinder[i][j]->GetXPos() - HinderSpeed[i][j], Hinder[i][j]->GetYPos());

				/*超出屏幕*/
				if (Hinder[i][j]->GetXPos()>rectClient.right)//超过右边
					Hinder[i][j]->SetPos(0, Hinder[i][j]->GetYPos());
				if (Hinder[i][j]->GetXPos()<rectClient.left)//超过左边
					Hinder[i][j]->SetPos(rectClient.right, Hinder[i][j]->GetYPos());
			}
		}

		if (i == 5 || i == 6)// 竖向向下移动
		{
			for (int j = 0; j < HinderNum[i]; j++)
			{
				/*移动*/
				Hinder[i][j]->SetPos(Hinder[i][j]->GetXPos(), Hinder[i][j]->GetYPos() + HinderSpeed[i][j]);
				
				/*超出屏幕*/
				if (Hinder[i][j]->GetYPos()>rectClient.bottom)
					Hinder[i][j]->SetPos(Hinder[i][j]->GetXPos(), 0);
			}
		}

		if (i == 2)//八爪鱼
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
			
				/*超出屏幕*/
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
	HinderVFail();//障碍的清理
}