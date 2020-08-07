#pragma once
#include<windows.h>
#include <math.h>

class CGame
{

	public:
		CGame(HWND hWnd,int fps=30)
		{
			hwnd=hWnd;
			nFps=fps;	
			Init();
		}

		~CGame()
		{
			DeleteDC(hdcMen);
			ReleaseDC(hwnd, hdc);
			DeleteObject(hbm);
			//DeleteObject(holdbm);
		}
		void FrameFunc();
		void Init();
		virtual void Render();	//输出画面效果	有双缓冲
		int ifdown();

	protected:
		virtual void Update(float fDeltaTime);			//状态游戏修改	
		int					nFps;						//每秒多少帧
		unsigned int        nFrames;					//总帧数
		DWORD				t0;                         //前一帧的时刻
		float t;										//累计秒数
		int					nFixedDeltaTime;			//设定的两帧间的时间间隔，单位是毫秒
		
		RECT rt;
		HWND hwnd;
		HDC hdcMen;
		HDC hdc;
		HBITMAP hbm;
		//HBITMAP holdbm;
	
	private:
		int x;
		int y;
		int ifd;
		int iclicknum ;
	
};

class Sprite
{
public:
	Sprite(HWND hWnd)
	{

		Shwnd = hWnd;
		SInit();
	}

	~Sprite()
	{

	}

	void SFrameFunc();
	void SInit();
	virtual void SRender();

protected:
	RECT rt;
	HWND Shwnd;
	HDC hdcMen;
	HDC hdc;
	HBITMAP hbm;

	
private:



};
