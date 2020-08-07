#include"矩形.h"
#include<time.h>
#include"d2d1Link.h"


/*画图笔刷*/
#define MaxHang 12
#define MaxLei  12
#define MixHang  2
#define MixLei   2
int Hang = 2;
int Lei = 2;
int ScreenWidth = 400;
int ScreenHeight = 400;
int BitmapNumber = 0;//位图号码
int ClickN = 0;//点击次数
Ju *FRect = NULL;//第一次点击的矩形
Ju *SRect = NULL;//第二次点击的矩形
Ju *AllJu[MaxHang*MaxLei] = { NULL };//全部的矩形指针
bool IsGameOver = false;
int Strong = 0;//游戏难度
int GameTime_s = 0;//游戏时间
int GameTime_f = 0;//游戏时间
bool IsChangeHL = false;//是否改变行和列
bool IsTips = false;//是否提供Tips
int InitX = ScreenWidth + 22;//右边菜单栏的初始化的x位置



/*变换*/
Matrix3x2F			        matWorld;
Matrix3x2F					matScale;
Matrix3x2F					matRotation;
Matrix3x2F					matTranslation;

/*函数*/
void Click();
void RectangleInit();
void DelectJu();
void RectangleRand();
void RandAB(int &i, int &b);
BOOL CheakGame();
void ChangeHL();
void ChangeMap(int n);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	MSG Msg;
	WNDCLASS wndclass;
	TCHAR lpszTitle[] = TEXT("拼图游戏");

	wndclass.style = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszMenuName = NULL;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = TEXT("MyClass");

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("RegisterClass fail!"), TEXT("error"), MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(
		TEXT("MyClass"),
		lpszTitle,
		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX/*最大化*/ & ~WS_THICKFRAME/*加上边框*/,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		550,
		460,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hwnd)
	{
		MessageBox(NULL, TEXT("createwindow fail!"), TEXT("error"), MB_ICONERROR);
		return 0;
	}
	Init();
	RectangleInit();

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	if (SUCCEEDED(CoInitialize(NULL)))				//如果初始化Com组件成功
	{
		if (SUCCEEDED(Init()))						//初始化
		{
			BOOL  bMessage;
			PeekMessage(&Msg, NULL, 0, 0, PM_NOREMOVE);
			while (Msg.message != WM_QUIT)			//进入消息循环
			{
				bMessage = PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE);
				if (bMessage)
				{
					TranslateMessage(&Msg);
					DispatchMessage(&Msg);
				}
				Render();							//渲染
			}
		}
		ClearUp();									//释放资源
		CoUninitialize();							//释放Com组件

	}
	DelectJu();
	return 0;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN:
		if (!IsGameOver)
		{
			GetClickPoint();
			Click();
		}
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}



void Render()
{
	pRenderTarget->BeginDraw();
	pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

	matWorld = D2D1::Matrix3x2F::Identity();
	pRenderTarget->SetTransform(matWorld);

	if (IsGameOver || IsChangeHL)
	{
		static float k = 1,fTime = 20;
		fTime += 0.1;
		if (fTime>1)
		{
			fTime = 0;
			k -= 0.2;
		}
		for (int i = 0; i < Hang*Lei; i++)
		{
			pJumap->CopyFromBitmap(&D2D1::Point2U(0, 0), pBitmapPuzzle[BitmapNumber], &D2D1::RectU(AllJu[i]->GetTexRc().left, AllJu[i]->GetTexRc().top, AllJu[i]->GetTexRc().right, AllJu[i]->GetTexRc().bottom));
			pJumapBrush->GetBitmap(&pJumap);
			pJumapBrush->SetOpacity(k);
			matTranslation = Matrix3x2F::Translation(AllJu[i]->GetPos().x, AllJu[i]->GetPos().y);
			pRenderTarget->SetTransform(matTranslation);
			pRenderTarget->FillRectangle(&D2D1::RectF(0, 0, AllJu[i]->GetTexRc().right, AllJu[i]->GetTexRc().bottom), pJumapBrush);
		}
		if (k < 0)
		{
			k = 1;
			if (IsChangeHL)
			{
				ChangeHL();
				IsChangeHL = false;
			}
			if (IsGameOver)
			{
				IsGameOver = false;
				ChangeMap(1);
			}
			RectangleInit();
		}

		pRenderTarget->EndDraw();
		return;
	}

	if (IsTips)
	{
		static float fTime = 20;
		fTime += 0.1;

		matWorld = D2D1::Matrix3x2F::Identity();
		pRenderTarget->SetTransform(matWorld);

		D2D1_RECT_F textRect = D2D1::RectF(InitX, 480, InitX + 120, 480 + 10);
		TCHAR szBuffer[12];
		int iLength;
		if (Hang == MaxHang ||Lei == MaxLei)
			iLength = wsprintf(szBuffer, TEXT("已是最困难程度"));
		if (Hang == MixHang || Lei == MixLei)
			iLength = wsprintf(szBuffer, TEXT("已是最简单程度"));
 		pRenderTarget->DrawText(szBuffer, iLength, pTextFormat, textRect, pBrushWrite);

		if (fTime>20)
		{
			fTime = 0;
			IsTips = false;
		}
	}

	if (ClickN ==1)
	{			
		matTranslation = Matrix3x2F::Translation(FRect->GetPos().x, FRect->GetPos().y);
		matScale = D2D1::Matrix3x2F::Scale(0.8f, 0.8f, D2D1::Point2F(FRect->GetWidth() / 2, FRect->GetHeight() / 2));


		pJumap->CopyFromBitmap(&D2D1::Point2U(0, 0), pBitmapPuzzle[BitmapNumber], &D2D1::RectU(FRect->GetTexRc().left, FRect->GetTexRc().top, FRect->GetTexRc().right, FRect->GetTexRc().bottom));
		
		matWorld = matScale * matTranslation;
		pRenderTarget->SetTransform(matWorld);
		pRenderTarget->DrawBitmap(pJumap);
	}

	for (int i = 0; i < Hang*Lei; i++)
	{
		if (ClickN == 1)
		{
			if (AllJu[i] == FRect)
				continue;
		}

		pJumap->CopyFromBitmap(&D2D1::Point2U(0, 0), pBitmapPuzzle[BitmapNumber], &D2D1::RectU(AllJu[i]->GetTexRc().left, AllJu[i]->GetTexRc().top, AllJu[i]->GetTexRc().right, AllJu[i]->GetTexRc().bottom));
		
		matTranslation = Matrix3x2F::Translation(AllJu[i]->GetPos().x, AllJu[i]->GetPos().y);
		pRenderTarget->SetTransform(matTranslation);
		pRenderTarget->DrawBitmap(pJumap);
	}

	/*游戏时间*/
	matWorld = D2D1::Matrix3x2F::Identity();
	pRenderTarget->SetTransform(matWorld);

	GameTime_s += 1;
	if (GameTime_s > 60)
	{
		GameTime_s = 0;
		GameTime_f += 1;
	}
	D2D1_RECT_F textRect = D2D1::RectF(InitX, 10, InitX + 120, 10 + 10);
	TCHAR szBuffer[12];
	int iLength = wsprintf(szBuffer, TEXT("用时时间：%d.%d"), GameTime_f, GameTime_s);
	pRenderTarget->DrawText(szBuffer, iLength, pTextFormat, textRect, pBrushWrite);

	/*游戏难度矩形*/
	
	TCHAR szBuffer1[8];
	int iLength1 = wsprintf(szBuffer1, TEXT("游戏难度："));
	pRenderTarget->DrawText(szBuffer1, iLength1, pTextFormat, D2D1::RectF(InitX, 40, InitX + 100, 40 + 10), pBrushWrite);

	pRenderTarget->DrawRectangle(&D2D1::RectF(InitX, 65, InitX + 20, 65 + 20), pBrush, 2);
	pRenderTarget->DrawRectangle(&D2D1::RectF(InitX + 53, 65, InitX + 53+20, 65 + 20), pBrush, 2);

	TCHAR szBuffer2[4];
	int iLength2 = wsprintf(szBuffer2, TEXT("增强"));
	pRenderTarget->DrawText(szBuffer2, iLength2, pTextFormat, D2D1::RectF(InitX + 30, 60, InitX + 30 + 20, 60 + 20), pBrushWrite);
	TCHAR szBuffer3[4];
	int iLength3 = wsprintf(szBuffer3, TEXT("减弱"));
	pRenderTarget->DrawText(szBuffer3, iLength3, pTextFormat, D2D1::RectF(InitX + 83, 60, InitX + 83 + 20, 60 + 20), pBrushWrite);

	/*换位图*/
	TCHAR szBuffer4[8];
	int iLength4 = wsprintf(szBuffer4, TEXT("游戏图片："));
	pRenderTarget->DrawText(szBuffer4, iLength4, pTextFormat, D2D1::RectF(InitX, 100, InitX + 100, 100 + 10), pBrushWrite);

	pRenderTarget->DrawRectangle(&D2D1::RectF(InitX, 135, InitX + 20, 135 + 20), pBrush, 2);
	pRenderTarget->DrawRectangle(&D2D1::RectF(InitX + 53, 135, InitX + 53 + 20, 135 + 20), pBrush, 2);

	TCHAR szBuffer5[4];
	int iLength5 = wsprintf(szBuffer5, TEXT("上一张"));
	pRenderTarget->DrawText(szBuffer5, iLength5, pTextFormat, D2D1::RectF(InitX + 30, 120, InitX + 30 + 20, 120 + 20), pBrushWrite);
	TCHAR szBuffer6[4];
	int iLength6 = wsprintf(szBuffer6, TEXT("下一张"));
	pRenderTarget->DrawText(szBuffer6, iLength6, pTextFormat, D2D1::RectF(InitX + 83, 120, InitX + 83 + 20, 120 + 20), pBrushWrite);

	D2D1_SIZE_F BitmapSize  = pBitmapPuzzle[BitmapNumber]->GetSize();
	matTranslation = Matrix3x2F::Translation(InitX, 200);
	matScale = D2D1::Matrix3x2F::Scale(float(100/BitmapSize.width ), float(150/BitmapSize.height ), D2D1::Point2F(0, 0));
	matWorld = matScale * matTranslation;
	pRenderTarget->SetTransform(matWorld);
	pRenderTarget->DrawBitmap(pBitmapPuzzle[BitmapNumber]);

	pRenderTarget->EndDraw();
}

/*清理矩形*/
void DelectJu()
{
	for (int i = 0; i < Hang*Lei; i++)
	{
		delete AllJu[i];
		AllJu[i] = NULL;
	}
}

void RandAB(int &i, int &b)
{
	i = rand() % (Hang*Lei);
	b = rand() % (Hang*Lei);

	if (i < 0 || b < 0 || i == b)
		RandAB(i,b);
	else
		return;
}

/*随机矩形*/
void RectangleRand()
{
	int i1, i2;
	POINT j1, j2;
	for (int i = 0; i < 60 + Hang+Lei; i++)
	{
		RandAB(i1, i2);
		j1 = AllJu[i1]->GetPos();
		j2 = AllJu[i2]->GetPos();
		AllJu[i1]->SetPos(j2);
		AllJu[i2]->SetPos(j1);
	}
}

/*初始化*/
void RectangleInit()
{
	if (AllJu[0] != NULL)
		DelectJu();//清理矩形

	if (pJumap)
	{
		pRenderTarget->CreateBitmap(D2D1::SizeU(ScreenWidth / Lei, ScreenHeight / Hang), D2D1::BitmapProperties(pBitmapPuzzle[0]->GetPixelFormat()), &pJumap);
	}
	if (pJumapBrush)
	{
		pRenderTarget->CreateBitmapBrush(pJumap, &pJumapBrush);
	}

	int k = 0;
	POINT pos = { 10, 10 }, TexPos = {0,0};
	int w = ScreenWidth / Lei, h = ScreenHeight / Hang;
	for (int i = 0; i < Hang; i++)
	{
		for (int j = 0; j < Lei; j++)
		{
			pos = { 10 + j*w, 10 + i*h };
			TexPos = { 0 + j*w, 0 + i*h };
			AllJu[k++] = new Ju(pos, TexPos, w, h,10);
		}
	}

	//初始化游戏时间
	GameTime_s = 0;
	GameTime_f = 0;

	RectangleRand();
}

void Click()
{
	if (ClickN == 0)
	{
		for (int i = 0; i < Hang*Lei; i++)
		{
			if (AllJu[i]->IsClick(ClickP))
			{
				FRect = AllJu[i];
				ClickN = 1;
				return;
			}
		}
	}
	if (ClickN == 1)
	{
		for (int i = 0; i < Hang*Lei; i++)
		{
			if (AllJu[i]->IsClick(ClickP))
			{
				SRect = AllJu[i];
			}
		}
		POINT j1, j2;
		j1 = FRect->GetPos();
		j2 = SRect->GetPos();
		FRect->SetPos(j2);
		SRect->SetPos(j1);
		ClickN = 0;
		CheakGame();
		return;
	}



	/*点击不同的矩形*/
	if (ClickP.x > InitX&& ClickP.y>65)
	{
		/*增加难度*/
		if (ClickP.x > InitX && ClickP.x<InitX + 20 && ClickP.y>65 && ClickP.y<85)
		{
			if (Hang == MaxHang)
			{
				IsTips = true;
				return;
			}
			if (Lei == MaxLei)
			{
				IsTips = true;
				return;
			}


			Strong = 1;
			IsChangeHL = true;
		}

		/*减弱难度*/
		else if (ClickP.x>InitX + 53 && ClickP.x < InitX + 53 + 20 && ClickP.y > 65 && ClickP.y < 85)
		{
			if (Hang == MixHang)
			{
				IsTips = true;
				return;
			}
			if (Lei == MixLei)
			{
				IsTips = true;
				return;
			}
			
			Strong = -1;
			IsChangeHL = true;
		}



		/*换位图*/
		if (ClickP.x > InitX && ClickP.x<InitX + 20 && ClickP.y>135 && ClickP.y < 155)
		{
			ChangeMap(-1);
		}
		if (ClickP.x > InitX + 53 && ClickP.x<InitX + 53 + 20 && ClickP.y>135 && ClickP.y < 155)
		{
			ChangeMap(1);
		}
	}
}

/*游戏检查*/
BOOL CheakGame()
{
	for (int i = 0; i < Hang*Lei; i++)
	{
		if (!AllJu[i]->IsEquality())
			return false;
	}
	IsGameOver = true;
	return true;
}

/*改变位图*/
void ChangeMap(int n)
{
	BitmapNumber+=n;
	if (BitmapNumber > (BitmapCount-1))
		BitmapNumber = 0;
	if (BitmapNumber < 0)
		BitmapNumber = BitmapCount - 1;
}

/*修改位置*/
void ChangeHL()
{
	DelectJu();

	Hang += Strong * 2;
	Lei += Strong * 2;

	if (Hang > MaxHang)
	{
		Hang = MaxHang;
		return;
	}
	if (Hang < MixHang)
	{
		Hang = MixHang;
		return;
	}
	if (Lei > MaxLei)
	{
		Lei = MaxLei;
		return;
	}
	if (Lei < MixLei)
	{
		Lei = MixLei;
		return;
	}

}