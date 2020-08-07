#pragma once

#include "..\框架-3CGame\Game.h"
#include"GameStart.h"
#include"GameSelect.h"
#include"GamePlay.h"
#include"People.h"
#include"GameHinder.h"
#include"GameTime.h"
using namespace std;

class CDemoGame :public CGame
{
private:
	CDemoGame(HWND hWnd, int nFps = 0);
	static CDemoGame *instance;
	static HWND hWnd;
	static int nFps;

public:
	static CDemoGame *GetInstance(HWND hWnd, int nFps = 0)
	{
		if (!instance)
		{
			instance = new CDemoGame(hWnd,nFps);
		}
		return instance;
	}

	virtual ~CDemoGame(void);

	void InitGame();
	virtual void Update(float fDeltaTime);//帧函数	
	virtual void Render();//渲染	

	/*鼠标*/
	void MouseSide();//鼠标放置位置
	void MouseCSide();//鼠标点击位置

private:
	GameProgress GameP;//游戏状态

	/*场景*/
	GameScene *pCGameScene;//场景类
	CGameStart *pCGameStart;//开始场景
	CGameSelect *pCGameSelect;//选关场景
	CGamePlay *pCGamePlay;//游戏场景
	CGamePeople *pCGamePeople;//人物
	CGameHinder *pCGameHinder;//阻碍
	CGameTime *pCGameTime;//计时器
};
