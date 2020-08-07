#include "Game.h"

CGame::CGame(HWND hWnd, int fps)
{
	this->hWnd=hWnd;
	nFps=fps;
	if (fps <= 0)
	{
		fFixedDeltaTime = 0;
	}
	else
	{
		fFixedDeltaTime = 1000.0f / fps;
	}
	

}
CGame::~CGame(void)												//�������������ͷ���Դ
{
	if (pSpriteManager)
	{
		delete pSpriteManager;
	}
	if (pResManager)
	{
		delete pResManager;
	}
	if (hWnd && hdc)
	{
		ReleaseDC(hWnd,hdc);
	}
	if (hdcMem)
	{
		DeleteDC(hdcMem);
	}
	if (hbMem)
	{
		DeleteObject(hbMem);
	}
	

}

void CGame::Init()
{
	hdc = GetDC(hWnd);												//�õ��豸����
	GetClientRect(hWnd,&rectClient);								//�õ��ͻ�������
	//���洴���󱸻���
	hdcMem = CreateCompatibleDC(hdc);
	hbMem = CreateCompatibleBitmap(hdc,rectClient.right-rectClient.left,rectClient.bottom-rectClient.top);
	SelectObject(hdcMem,hbMem);

	pResManager =  new CResourceManager(hWnd);						//������Դ�������
	pSpriteManager = new CSpriteManager(pResManager);				//��������������	
	
	t0 = GetTickCount();
	t = 0;
	nFrames = 0;
	nCalcFps = 0;
	//nFps = 0;
	
	hPen = CreatePen(PS_SOLID, 1, RGB(218, 218, 218));
	hBr = CreateSolidBrush(RGB(52, 49, 49));

	SelectObject(hdcMem, hPen);
	SelectObject(hdcMem, hBr);

}



void CGame::FrameFunc()
{
			//֡����������ϵͳ���ŵ�ʱ����¾���״̬��������������д��Ϸ����

	DWORD dt = 0;
	
	do 
	{ 
		dt=GetTickCount() - t0; 
	} while(dt < 1);									//��֤��С���ʱ����ڵ���1����
	if (dt >= fFixedDeltaTime)							//������ڹ̶��ļ��ʱ��
	{
		t0 = GetTickCount();								//��¼��֡���õ�ʱ��
		Update(dt / 1000.0);							//����֡��������
		t += dt / 1000.0;
		Render();										//��Ⱦ
		
		nFrames++;
	}
}

void CGame::Render()
{
	FillRect(hdcMem,&rectClient,hBr);
	if (pSpriteManager)
	{
		pSpriteManager->Render(hdcMem);
	}
	if (t >= 1)
	{
		nCalcFps  =  nFrames / t;
		
		t = 0;
		nFrames = 0;
	}
	BitBlt(hdc,0,0,rectClient.right - rectClient.left,rectClient.bottom - rectClient.top,hdcMem,0,0,SRCCOPY);

}