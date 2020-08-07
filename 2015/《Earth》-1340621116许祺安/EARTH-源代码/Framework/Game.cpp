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
CGame::~CGame(void)												//在析构函数中释放资源
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
	hdc = GetDC(hWnd);												//得到设备环境
	GetClientRect(hWnd,&rectClient);								//得到客户区矩形
	//下面创建后备缓冲
	hdcMem = CreateCompatibleDC(hdc);
	hbMem = CreateCompatibleBitmap(hdc,rectClient.right-rectClient.left,rectClient.bottom-rectClient.top);
	SelectObject(hdcMem,hbMem);

	pResManager =  new CResourceManager(hWnd);						//创建资源管理对象
	pSpriteManager = new CSpriteManager(pResManager);				//创建精灵管理对象	
	
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
			//帧函数，根据系统流逝的时间更新精灵状态，可以在子类重写游戏规则

	DWORD dt = 0;
	
	do 
	{ 
		dt=GetTickCount() - t0; 
	} while(dt < 1);									//保证最小间隔时间大于等于1毫秒
	if (dt >= fFixedDeltaTime)							//如果大于固定的间隔时间
	{
		t0 = GetTickCount();								//记录本帧调用的时刻
		Update(dt / 1000.0);							//调用帧函数更新
		t += dt / 1000.0;
		Render();										//渲染
		
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