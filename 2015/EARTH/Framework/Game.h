#pragma once
#include<windows.h>
#include <tchar.h>
#include "SpriteManager.h"
#include "ResourceManager.h"
#include "Vector2D.h"
class CGame
{

public:
	CGame(HWND hWnd,int fps=0);
	
	virtual ~CGame(void);
	
	void FrameFunc();

	virtual void Init() ;

	


protected:

	CSpriteManager		*pSpriteManager;									//精灵管理对象指针	
	CResourceManager	*pResManager;										//资源管理对象指针	


	virtual void Update(float fDeltaTime){}	//状态游戏修改	
	virtual void Render();							//输出画面效果	


	HDC					hdcMem;												//内存设备环境
	HBITMAP				hbMem;												//内存位图
	HDC					hdc;												//当前设备环境
	RECT				rectClient;											//客户区矩形

	int					nFps;						//每秒多少帧
	int                 nFrames;					//总帧数
	int					nCalcFps;					//计算的帧频
	DWORD				t0;                         //前一帧的时刻
	float				t;							//累计秒数
	float				fFixedDeltaTime;			//设定的两帧间的时间间隔，单位是毫秒
			
	HWND				hWnd;

	TCHAR               szBuf[255];		

	HPEN				hPen;
	HBRUSH				hBr;
};