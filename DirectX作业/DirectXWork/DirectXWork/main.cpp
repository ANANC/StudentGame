#include"����.h"
#include<time.h>
#include"d2d1Link.h"


/*��ͼ��ˢ*/
#define MaxHang 12
#define MaxLei  12
#define MixHang  2
#define MixLei   2
int Hang = 2;
int Lei = 2;
int ScreenWidth = 400;
int ScreenHeight = 400;
int BitmapNumber = 0;//λͼ����
int ClickN = 0;//�������
Ju *FRect = NULL;//��һ�ε���ľ���
Ju *SRect = NULL;//�ڶ��ε���ľ���
Ju *AllJu[MaxHang*MaxLei] = { NULL };//ȫ���ľ���ָ��
bool IsGameOver = false;
int Strong = 0;//��Ϸ�Ѷ�
int GameTime_s = 0;//��Ϸʱ��
int GameTime_f = 0;//��Ϸʱ��
bool IsChangeHL = false;//�Ƿ�ı��к���
bool IsTips = false;//�Ƿ��ṩTips
int InitX = ScreenWidth + 22;//�ұ߲˵����ĳ�ʼ����xλ��



/*�任*/
Matrix3x2F			        matWorld;
Matrix3x2F					matScale;
Matrix3x2F					matRotation;
Matrix3x2F					matTranslation;

/*����*/
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
	TCHAR lpszTitle[] = TEXT("ƴͼ��Ϸ");

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
		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX/*���*/ & ~WS_THICKFRAME/*���ϱ߿�*/,
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

	if (SUCCEEDED(CoInitialize(NULL)))				//�����ʼ��Com����ɹ�
	{
		if (SUCCEEDED(Init()))						//��ʼ��
		{
			BOOL  bMessage;
			PeekMessage(&Msg, NULL, 0, 0, PM_NOREMOVE);
			while (Msg.message != WM_QUIT)			//������Ϣѭ��
			{
				bMessage = PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE);
				if (bMessage)
				{
					TranslateMessage(&Msg);
					DispatchMessage(&Msg);
				}
				Render();							//��Ⱦ
			}
		}
		ClearUp();									//�ͷ���Դ
		CoUninitialize();							//�ͷ�Com���

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
			iLength = wsprintf(szBuffer, TEXT("���������ѳ̶�"));
		if (Hang == MixHang || Lei == MixLei)
			iLength = wsprintf(szBuffer, TEXT("������򵥳̶�"));
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

	/*��Ϸʱ��*/
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
	int iLength = wsprintf(szBuffer, TEXT("��ʱʱ�䣺%d.%d"), GameTime_f, GameTime_s);
	pRenderTarget->DrawText(szBuffer, iLength, pTextFormat, textRect, pBrushWrite);

	/*��Ϸ�ѶȾ���*/
	
	TCHAR szBuffer1[8];
	int iLength1 = wsprintf(szBuffer1, TEXT("��Ϸ�Ѷȣ�"));
	pRenderTarget->DrawText(szBuffer1, iLength1, pTextFormat, D2D1::RectF(InitX, 40, InitX + 100, 40 + 10), pBrushWrite);

	pRenderTarget->DrawRectangle(&D2D1::RectF(InitX, 65, InitX + 20, 65 + 20), pBrush, 2);
	pRenderTarget->DrawRectangle(&D2D1::RectF(InitX + 53, 65, InitX + 53+20, 65 + 20), pBrush, 2);

	TCHAR szBuffer2[4];
	int iLength2 = wsprintf(szBuffer2, TEXT("��ǿ"));
	pRenderTarget->DrawText(szBuffer2, iLength2, pTextFormat, D2D1::RectF(InitX + 30, 60, InitX + 30 + 20, 60 + 20), pBrushWrite);
	TCHAR szBuffer3[4];
	int iLength3 = wsprintf(szBuffer3, TEXT("����"));
	pRenderTarget->DrawText(szBuffer3, iLength3, pTextFormat, D2D1::RectF(InitX + 83, 60, InitX + 83 + 20, 60 + 20), pBrushWrite);

	/*��λͼ*/
	TCHAR szBuffer4[8];
	int iLength4 = wsprintf(szBuffer4, TEXT("��ϷͼƬ��"));
	pRenderTarget->DrawText(szBuffer4, iLength4, pTextFormat, D2D1::RectF(InitX, 100, InitX + 100, 100 + 10), pBrushWrite);

	pRenderTarget->DrawRectangle(&D2D1::RectF(InitX, 135, InitX + 20, 135 + 20), pBrush, 2);
	pRenderTarget->DrawRectangle(&D2D1::RectF(InitX + 53, 135, InitX + 53 + 20, 135 + 20), pBrush, 2);

	TCHAR szBuffer5[4];
	int iLength5 = wsprintf(szBuffer5, TEXT("��һ��"));
	pRenderTarget->DrawText(szBuffer5, iLength5, pTextFormat, D2D1::RectF(InitX + 30, 120, InitX + 30 + 20, 120 + 20), pBrushWrite);
	TCHAR szBuffer6[4];
	int iLength6 = wsprintf(szBuffer6, TEXT("��һ��"));
	pRenderTarget->DrawText(szBuffer6, iLength6, pTextFormat, D2D1::RectF(InitX + 83, 120, InitX + 83 + 20, 120 + 20), pBrushWrite);

	D2D1_SIZE_F BitmapSize  = pBitmapPuzzle[BitmapNumber]->GetSize();
	matTranslation = Matrix3x2F::Translation(InitX, 200);
	matScale = D2D1::Matrix3x2F::Scale(float(100/BitmapSize.width ), float(150/BitmapSize.height ), D2D1::Point2F(0, 0));
	matWorld = matScale * matTranslation;
	pRenderTarget->SetTransform(matWorld);
	pRenderTarget->DrawBitmap(pBitmapPuzzle[BitmapNumber]);

	pRenderTarget->EndDraw();
}

/*�������*/
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

/*�������*/
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

/*��ʼ��*/
void RectangleInit()
{
	if (AllJu[0] != NULL)
		DelectJu();//�������

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

	//��ʼ����Ϸʱ��
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



	/*�����ͬ�ľ���*/
	if (ClickP.x > InitX&& ClickP.y>65)
	{
		/*�����Ѷ�*/
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

		/*�����Ѷ�*/
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



		/*��λͼ*/
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

/*��Ϸ���*/
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

/*�ı�λͼ*/
void ChangeMap(int n)
{
	BitmapNumber+=n;
	if (BitmapNumber > (BitmapCount-1))
		BitmapNumber = 0;
	if (BitmapNumber < 0)
		BitmapNumber = BitmapCount - 1;
}

/*�޸�λ��*/
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