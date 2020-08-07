#include"Earth.h"
#include <ctime>

#define KEY_LEFT (GetKeyState(VK_LEFT) & 0x80)>0 ? true : false
#define KEY_RIGHT  (GetKeyState(VK_RIGHT) & 0x80)>0 ? true : false
#define KEY_SPACE  (GetKeyState(VK_SPACE) & 0x80)>0 ? true : false
#define KEY_SHIFT  (GetKeyState(VK_SHIFT) & 0x80)>0 ? true : false
#define KEY_CTRL  (GetKeyState(VK_ESCAPE) & 0x80)>0 ? true : false

/*准备工作*/
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

	/*准备工作*/
	GetPicture();//载入图片
	Mpoint = { 0, 0 };//鼠标移动位置
	Cpoint = { 0, 0 };//鼠标点击位置
	GameP = 1;//游戏进程
	IsGamePlay = false;//是否进行游戏
	IsGameOver = false;//游戏是否关闭
	
	/*开始界面*/
	GetGameStart();//开始界面
	rGameStart = { 378, 120, 473, 145 };//开始的框
	IsSelectGameStart = false;//是否接触

	/*选关界面*/
	GetGamePass();//选关界面
	for (int i = 1; i < 8; i++)
	{
		IsPassSelect[i] = false;//选关状态
		IsGamePass[i] = false;//通关状态
		GP[i] = false;//鼠标放置
	}
	GP[0] = false;//鼠标放置
	IsPassSelect[0] = true;//第一关可选	
	IsGamePass[0] = false;//通关状态-第一关
	for (int i = 0; i < 8; i++)
		GameTime[i] = 0;//通关时间
	GameMunber = 0;//当前关卡
	Gp = -1;//鼠标放置关卡


	/*游戏界面*/
	GetPlayScreen();//游戏界面
	FoodNumber = 0;//获得食物的数量
	for (int i = 0; i < 3; i++)
		IsGetFood[i] = { false };//是否得到食物
	ss = { 237, 95, 616, 474 };//圆的框
	IsMoveRestart = false;//鼠标是否放在重玩上

	/*操作人物*/
	GetPeople();//操作人物
	RotationAngle = 0;//旋转角度
	//操作人物一开始的位置
	oldPos = { People->GetXPos() + PeoWidth / 2, People->GetYPos() };
	PeoHeight = People->GetHeight();//人物图片的高度
	PeoWidth = People->GetWidth();//人物图片的宽度
	bIsFly = false;//是非飞
	bIsDown = false;//是否下落
	fFlyDistance = 0;//飞行高度

	/*计时器*/
	GameTime_min = 0;//分
	GameTime_sec = 0;//秒
	GameTime_msec = 0;//毫秒
	for (int i = 0; i < 8; i++)
		GameTime[i] = 0;//关卡时间
	Selecthf();//初始化画笔
	int  fD = 0;//计时器

	/*障碍*/
	GetHinder();//障碍
	PlayWay = 1;//操作是否颠倒
	IsStatic = false;//人物是否固定
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < HinderNumber; j++)
			IsLeft[i][j] = 0;//是否左边
	}
	rinSpeed = 1;//雨，速度改变

}

void Earth::Erase()//清理工作
{
	/*开始界面*/
	DeleteGameStart();

	/*选关界面*/
	DeleteGamePass();

	/*游戏界面*/
	DelectPlayScreen();
	DelectPeople();
	Delecthf();
	DelectHinder();
}

void Earth::GetPicture()
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

	pResManager->LoadPictureFromFile(TEXT("鱼障碍1"), TEXT("image/地图/鱼障碍1.bmp"));
	pResManager->LoadPictureFromFile(TEXT("鱼障碍2"), TEXT("image/地图/鱼障碍2.bmp"));

	/*关卡*/
	pResManager->LoadPictureFromFile(TEXT("八爪鱼关卡"), TEXT("image/关卡/八爪鱼.bmp"));
	pResManager->LoadPictureFromFile(TEXT("练手关卡"), TEXT("image/关卡/练手.bmp"));
	pResManager->LoadPictureFromFile(TEXT("蒲公英关卡"), TEXT("image/关卡/蒲公英.bmp"));
	pResManager->LoadPictureFromFile(TEXT("闪电关卡"), TEXT("image/关卡/闪电.bmp"));
	pResManager->LoadPictureFromFile(TEXT("树关卡"), TEXT("image/关卡/树.bmp"));
	pResManager->LoadPictureFromFile(TEXT("水滴关卡"), TEXT("image/关卡/水滴.bmp"));
	pResManager->LoadPictureFromFile(TEXT("鱼关卡"), TEXT("image/关卡/鱼.bmp"));
	pResManager->LoadPictureFromFile(TEXT("云关卡"), TEXT("image/关卡/云.bmp"));

	/*新添加的背景*/
	pResManager->LoadPictureFromFile(TEXT("2_深海"), TEXT("image/地图/2-深海.bmp"));
	pResManager->LoadPictureFromFile(TEXT("2_深海大鱼"), TEXT("image/地图/2-深海大鱼.bmp"));
}

void Earth::Update(float fDeltaTime)
{
	if (IsGameOver)
		return;

	CGame::Update(fDeltaTime);

	//MouseMove();//鼠标移动-可以放到main
	//MouseClick();//鼠标点击-可以放到main

	if (GetGameP() == 1)
	{
		GameStart->Update(fDeltaTime);
		GameStartPlay();
	}
	

	/*游戏界面*/
	if (GetGameP() == 3)
	{
		PeoMove(fDeltaTime);//操作人物
		People->Update(fDeltaTime);
		GetPeopleXandY();

		for (int i = 0; i < HinderNum[1]; i++)
			Hinder[1][i]->Update(fDeltaTime);

		GameScreen->Update(fDeltaTime);

		TimerUpdate(fDeltaTime);//时间的更新
		HinderMove();//障碍的移动
		GetFood();//食物
		HinderTouch(fDeltaTime);//接触障碍

		IsRestart();//重玩快捷键
		IsGOver();//返回快捷键
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
		TimerShow();//时间的展示
		IsMoveInRestart();//重玩快捷键的提示
		IsMoveInReturn();//返回快捷键的提示
	}

	BitBlt(hdc, 0, 0, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, hdcMem, 0, 0, SRCCOPY);
}

void Earth::MouseSide()//鼠标移动位置
{
	GetCursorPos(&Mpoint);            // 获取鼠标指针位置（屏幕坐标）
	ScreenToClient(hWnd, &Mpoint);    // 将鼠标指针位置转换为窗口坐标
}

void Earth::MouseCSide()//鼠标点击位置
{
	GetCursorPos(&Cpoint);            // 获取鼠标指针位置（屏幕坐标）
	ScreenToClient(hWnd, &Cpoint);    // 将鼠标指针位置转换为窗口坐标
}

void Earth::MouseMove()
{
	MouseSide();//获得鼠标移动位置-可以放到main

	/*开始界面*/
	if (GetGameP() == 1)
		MoveGameStrat();

	/*选关界面*/
	if (GetGameP() == 2)
		MoveGamePass();
	
	/*游戏界面*/
	if (GetGameP() == 3)
	{
		MoveReturn();
		MoveRestart();
	}
}

void Earth::MouseClick()
{
	MouseCSide();//获得鼠标点击位置-应该放在main

	/*开始界面*/
	if (GetGameP() == 1)
		SelectGameStrat();

	/*选关界面*/
	if (GetGameP() == 2)
		SelectGamePass();

	/*游戏界面*/
	if (GetGameP() == 3)
	{
		Return();//返回
		Restart();//重玩
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

/*开始界面*/

void Earth::GetGameStart()
{
	GameStart = pSpriteManager->CreateAnimationSprite(TEXT("开始"),3, 30, 0, 0,3,2);
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
		GameProgress(2);//更改游戏状态-进入选关状态
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

/*选关界面*/

void Earth::GetGamePass()
{
	int xxm = 40, yym = 90, ww, hh;
	GamePass[0] = pSpriteManager->CreateAnimationSprite(TEXT("练手关卡"), 2, 1, xxm, yym, 2, 4);
	ww = GamePass[0]->GetDestWidth(); 
	hh = GamePass[0]->GetDestHeight();
	GamePass[1] = pSpriteManager->CreateAnimationSprite(TEXT("鱼关卡"), 2, 1, 2 * xxm + ww, yym, 2, 5);
	GamePass[2] = pSpriteManager->CreateAnimationSprite(TEXT("八爪鱼关卡"), 2, 1, 3 * xxm + 2 * ww, yym, 2, 5);
	GamePass[3] = pSpriteManager->CreateAnimationSprite(TEXT("树关卡"), 2, 1, 4 * xxm + 3 * ww, yym, 2, 5);
	GamePass[4] = pSpriteManager->CreateAnimationSprite(TEXT("蒲公英关卡"), 2, 1, xxm, 20 + hh + yym, 2, 5);
	GamePass[5] = pSpriteManager->CreateAnimationSprite(TEXT("水滴关卡"), 2, 1, 2 * xxm + ww, 20 + hh + yym, 2, 5);
	GamePass[6] = pSpriteManager->CreateAnimationSprite(TEXT("闪电关卡"), 2, 1, 3 * xxm + 2 * ww, 20 + hh + yym, 2, 5);
	GamePass[7] = pSpriteManager->CreateAnimationSprite(TEXT("云关卡"), 2, 1, 4 * xxm + 3 * ww, 20 + hh + yym, 2, 5);
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
			/*选关不可见*/
			for (int j = 0; j < 8; j++)
				GamePass[j]->SetVisible(false);

			/*人物，道具，障碍可见*/
			GameScreen->SetVisible(true);//地图
			GameScreen->Play();
			Again->SetVisible(true);//重玩
			Back->SetVisible(true);//返回
			for (int j = 0; j < 3; j++)
				GFood[j]->SetVisible(true);//食物
			People->SetVisible(true);//人物
			People->Play();

			/*修改游戏状态*/
			GameMunber = i;//设置当前关卡
			GameProgress(3);//进入游戏状态
			GamePlaing(true);//进行游戏

			/*人物，道具，障碍,计时器初始化*/
			FoodFirst();//道具
			PeoFirst();//人物
			TimeFirst();//计时器
			HinderCreate();//动态障碍
			HinderShow_static();//静态障碍

			/*测试的新背景*/
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
			TextOut(hdcMem, 50, 30 + 80 + 182, szBuffer, wsprintf(szBuffer, TEXT("跳跃能走过更长的距离")));
		break;
	case 1:
		if (IsPassSelect[1])
			TextOut(hdcMem, 40 + 160 + 20, 30 + 80 + 182, szBuffer, wsprintf(szBuffer, TEXT("成群结队的鱼在海洋幽幽游动")));
		break;
	case 2:
		if (IsPassSelect[2])
			TextOut(hdcMem, 40 + 160 * 2 + 60, 30 + 80 + 182, szBuffer, wsprintf(szBuffer, TEXT("爱动的八爪鱼总是不按常规出现")));
		break;
	case 3:
		if (IsPassSelect[3])
			TextOut(hdcMem, 40 + 160 * 3 + 100, 30 + 80 + 182, szBuffer, wsprintf(szBuffer, TEXT("遮天蔽日的树让途人迷失方向")));
		break;
	case 4:
		if (IsPassSelect[4])
			TextOut(hdcMem, 40-5, 30 + 80 + 182, szBuffer, wsprintf(szBuffer, TEXT("散落各地的蒲公英飘向天际")));
		break;
	case 5:
		if (IsPassSelect[5])
			TextOut(hdcMem, 40+160+45, 30+80+182, szBuffer, wsprintf(szBuffer, TEXT("路人慌忙躲避这绵绵雨")));
		break;
	case 6:
		if (IsPassSelect[6])
			TextOut(hdcMem, 40+160*2+90, 30+80+182, szBuffer, wsprintf(szBuffer, TEXT("闪电使人停住了脚步")));
		break;
	case 7:
		if (IsPassSelect[7])
			TextOut(hdcMem, 40+160*3+100, 30+80 + 182, szBuffer, wsprintf(szBuffer, TEXT("云朵遮住了珍宝")));
		break;
	default:
		break;
	}
}

int Earth::GetGameMunber()
{
	return GameMunber;
}


/*游戏界面*/
void Earth::GetPlayScreen()
{
	/*游戏界面*/
	GameScreen = pSpriteManager->CreateAnimationSprite(TEXT("鱼"), 3, 20, 0, 0, 3, 4);//地图
	GameScreen->SetPos(0, 0);
	GameScreen->SetVisible(false);
	GameScreen->Play();

	/*道具*/
	Again = pSpriteManager->CreateAnimationSprite(TEXT("重来"), 2, 1, 775, 20, 2, 1);
	Back = pSpriteManager->CreateAnimationSprite(TEXT("返回"), 2, 1, 775 + Again->GetDestHeight() + 10, 20, 2, 1);
	Fail = pSpriteManager->CreateSprite(TEXT("死亡"));
	Fail->SetPos(690, 25);
	Success = pSpriteManager->CreateSprite(TEXT("通关"));
	Success->SetPos(710, 25);
	for (int i = 0; i < 3; i++)
	{
		GFood[i] = pSpriteManager->CreateSprite(TEXT("获取道具"));
		GFood[i]->SetVisible(false);
		GFood[i]->SetSpriteRect(-3, -3);
	}
	Again->SetVisible(false);
	Back->SetVisible(false);
	Fail->SetVisible(false);
	Success->SetVisible(false);

	//for (int i = 0; i < 2; i++)
	//{
	//	Two_FF[i] = pSpriteManager->CreateAnimationSprite(TEXT("2_深海大鱼"), 2, 1, 0, 0, 2, 2);
	//	Two_FF[i]->SetVisible(false);
	//	Two_FF[i]->SetTransparent(true);
	//}
	//Two_FF[0]->SetPos(700, 270);
	//Two_FF[1]->SetTexturePos(0, Two_FF[1]->GetHeight());
	//Two_FF[1]->SetPos(-220, -200);

	//Two_F = pSpriteManager->CreateSprite(TEXT("2_深海"));
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
		for (int i = 0; i < 3;i++)
			GFood[i]->SetVisible(false);//食物
		People->SetVisible(false);//人物
		People->Stop();//人物动画不播放
		HinderErase();//障碍

		/*修改游戏状态*/
		GameProgress(2);//进入游戏状态
		GamePlaing(false);//进行游戏
		ChangePass();//改变选关效果

		if (Again->IsSelected(Cpoint.x, Cpoint.y))
			Cpoint = { 0, 0 };
	}
}

void Earth::Restart()
{
	if (Again->IsSelected(Cpoint.x, Cpoint.y) || IsRestart())
	{
		/*道具的初始化*/
		FoodFirst();
		for (int i = 0; i < 3; i++)
			GFood[i]->SetVisible(true);

		/*人物的初始化*/
		PeoFirst();

		/*障碍的初始化*/
		HinderErase();
		HinderShow_static();//静态障碍
		HinderCreate();//动态障碍

		/*计时器的初始化*/
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
		TextOut(hdcMem, 772, 50, szBuffer, wsprintf(szBuffer, TEXT("shift键")));
	}
}

void Earth::IsMoveInReturn()
{
	if (IsMoveReturn)
	{
		TCHAR szBuffer[15];
		TextOut(hdcMem, 792, 50, szBuffer, wsprintf(szBuffer, TEXT("control键")));
	}
}

void Earth::GameSuccess()
{
	Success->SetVisible(true);//可见
}

void Earth::GameOver()
{
	Fail->SetVisible(true);//可见
	GameScreen->SetTexturePos(0, 567 * 4);
	People->Stop();
	for (int i = 0; i < HinderNum[1]; i++)
		Hinder[1][i]->Stop();
	GamePlaing(false);//游戏结束
}

void Earth::GameSuccess(int i)
{
	/*放置图片*/
	GameSuccess();

	/*设置关卡状态*/
	GamePlaing(false);//游戏结束
	SetGamePass(i);//设置通关关卡

	/*记录时间*/
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

	if (FoodNumber == 3)//游戏胜利
		GameSuccess(GetGameMunber());
		
	
}

void Earth::FoodFirst()
{
	/*设置数量和地图的初始化*/
	for (int i = 0; i < 3;i++)
		IsGetFood[i] = { false };
	FoodNumber = 0;
	GameScreen->SetTextureStartPos(0, 567 * FoodNumber);

	//放置图片
	SetFood();
}

/*操作人物*/
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

/*计时器*/

void Earth::Selecthf()
{
	hf = (HFONT)GetStockObject(BLACK_PEN);
	SetTextColor(hdcMem, RGB(218, 218, 218));//修改字体颜色
	SetBkMode(hdcMem, TRANSPARENT);//透明背景
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
		iLength = wsprintf(szBuffer, TEXT("时间：%d.%d.%d"), GameTime_min, GameTime_sec, GameTime_msec);
		TextOut(hdcMem, 10, 5, szBuffer, iLength);
	}
	else
	{
		int m = (int)GameTime[GetGameMunber()];
		int s = (GameTime[GetGameMunber()] - m) * 100;
		iLength = wsprintf(szBuffer, TEXT("用时：%d分%d秒"), m, s);
		TextOut(hdcMem, 10, 5, szBuffer, iLength);
	}
}

/*障碍*/
void Earth::GetHinder()
{
	for (int i = 0; i < HinderNumber; i++)
	{
		Hinder[0][i] = pSpriteManager->CreateAnimationSprite(TEXT("鱼障碍1"), 1, 1, 0, 0, 1, 1);
		//Hinder[0][i]->SetSpriteRect(-5, -12);

		Hinder[1][i] = pSpriteManager->CreateAnimationSprite(TEXT("八爪鱼障碍"), 4, 20, 0, 0, 4, 1);
		//Hinder[1][i]->SetSpriteRect(-20, -20);
		Hinder[1][i]->SetColorKey(Hinder[1][i]->GetPixelColor(5, 75));

		Hinder[2][i] = pSpriteManager->CreateAnimationSprite(TEXT("树"), 1, 1, 0, 0, 1, 1);
		//Hinder[2][i]->SetSpriteRect(-8, -8);

		Hinder[3][i] = pSpriteManager->CreateAnimationSprite(TEXT("蒲公英"), 1, 1, 0, 0, 1, 1);
		//Hinder[3][i]->SetSpriteRect(-2, -2);

		Hinder[4][i] = pSpriteManager->CreateAnimationSprite(TEXT("水滴障碍"), 1, 1, 0, 0, 1, 1);
		//Hinder[4][i]->SetSpriteRect(-1, -1);

		Hinder[5][i] = pSpriteManager->CreateAnimationSprite(TEXT("闪电"), 1, 1, 0, 0, 1, 1);
		//Hinder[5][i]->SetSpriteRect(-1, -1);

		Hinder[6][i] = pSpriteManager->CreateAnimationSprite(TEXT("云障碍"), 1, 1, 0, 0, 1, 1);
		//Hinder[6][i]->SetSpriteRect(-3, -3);

	}

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < HinderNumber; j++)
		{
			Hinder[i][j]->SetVisible(false);
			HinderSpeed[i][j] = 0;//速度
		}
		HinderNum[i] = 0;//数量
		IsBSee[i] = 0;//状态
	}
}

void Earth::DelectHinder()
{
	for (int i = 0; i <= 7; i++)
	{
		for (int j = 0; j < HinderNumber; j++)
		{
			pSpriteManager->DeleteSprite(Hinder[i][j]);//清理
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
		HinderNum[i] = 0;//数量
	}
	PlayWay = 1;
	rinSpeed = 1;
}

void Earth::HinderCreate()
{

	srand((unsigned)time(NULL));
		/*鱼*/
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
					Hinder[0][HinderNum[0] - 1] = pSpriteManager->CreateAnimationSprite(TEXT("鱼障碍2"), 1, 1, 0, 0, 1, 1);

					Hinder[0][HinderNum[0]-1]->SetPos(rectClient.left, y);
					/*Hinder[0][HinderNum[0] - 1]->SetTexturePos(0, Hinder[0][HinderNum[0] - 1]->GetHeight());*/
					IsLeft[0][HinderNum[0] - 1] = 1;
				}
				HinderSpeed[0][HinderNum[0] - 1] = rand() % 13 + 1;
				//Hinder[0][HinderNum[0] - 1]->SetTransparent(true);
				Hinder[0][HinderNum[0] - 1]->SetVisible(true);
			}
			
		}

		/*八爪鱼*/
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

		/*水滴*/
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

		/*闪电*/
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

		/*云*/
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

	/*树*/
	if (GameMunber == 3 || GameMunber > 3)
	{
		int Num = GetGameMunber()-1;
		if (Num > 5)
			Num = 3;
		Vector2D vector(0, 0);
		float Ro = rand()%30 +1;

		for (int i = 0; i < Num; i++)
		{
			/*位置*/
			if (Ro >= 180)
				Ro = 0;
			Ro += 10;
			vector.SetPos(0.0f, -185.0f - Hinder[2][0]->GetHeight());
			Hinder[2][i]->SetRotationAngle(Ro);
			vector.rotate(Ro);
			Hinder[2][i]->SetPos(433 - 8 + vector.GetX(), 303 - 19 + vector.GetY());

			///*背景*/
			Hinder[2][i]->SetTransparent(true);

			/*可见*/
			Hinder[2][i]->SetVisible(true);

			HinderNum[2]++;//障碍的数量
		}
	}

	/*蒲公英*/
	if (GameMunber == 4 || GameMunber > 4)
	{
		int Num = GetGameMunber()-2;
		if (Num > 5)
			Num = 4;
		Vector2D vector(0, 0);
		float Ro = rand()%10+1;

		for (int i = 0; i < Num; i++)
		{
			/*位置*/
			if (Ro >= 180)
				Ro = 0;
			Ro += 8;
			vector.SetPos(0.0f, -189.5f - Hinder[3][0]->GetHeight());
			vector.rotate(Ro);
			Hinder[3][i]->SetRotationAngle(Ro);
			Hinder[3][i]->SetPos(433 - 7 + vector.GetX(), 303 - 19 + vector.GetY());

			/*背景*/
			Hinder[3][i]->SetTransparent(true);

			/*可见*/
			Hinder[3][i]->SetVisible(true);

			HinderNum[3]++;//障碍的数量
		}
	}
}

void Earth::HinderMove()
{
	if (!IsGamePlay)
		return;

	for (int i = 0; i <= GetGameMunber(); i++)
	{
		if (i == 2 || i == 3)//固定位置
			continue;

		if (i == 0 || i == 6)//横向移动
		{
			for (int j = 0; j < HinderNum[i]; j++)
			{
				/*移动*/
				int k = 0;
				if (i == 6)
					k = 1;
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

		if (i == 4 || i == 5)// 竖向向下移动
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

		if (i == 1)//八爪鱼
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

				/*超出屏幕*/
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

