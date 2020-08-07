#pragma once

#include"GameScene.h"
//#include"GameSelect.h"

using namespace std;
class CGameSelect;
class CGameTime
{
public:
	static CGameTime *GetInstance()
	{
		if (!instance)
		{
			instance = new CGameTime();
		}
		return instance;
	}

	~CGameTime();

private:
	CGameTime();
	static CGameTime *instance;

	GameScene *pCGameScene;
	CGameSelect *pCGameSelect;

	int GameTime_min;//时间分部分
	int GameTime_sec;//时间秒部分
	int GameTime_msec;//时间毫秒部分
	HFONT hf;//计时器用的画笔
	int fD;//计时器的累加

public:
	void TimerUpdate(float fDeltaTime);//计时器的更新
	void TimerShow(ID2D1HwndRenderTarget *pRenderTarget, IDWriteTextFormat *pTextFormat, ID2D1SolidColorBrush *pTextBrush);
	//计时器的显示
	void TimeFirst();//计时器初始化

};