#pragma once

#include"GameScene.h"
#include"GamePlay.h"
#include"People.h"
#include"GameHinder.h"
#include"GameTime.h"
using namespace std;

class CGameSelect
{
private:
	CGameSelect();
	static CGameSelect *instance;

public:
	static CGameSelect *GetInstance()
	{
		if (!instance)
		{
			instance = new CGameSelect();
		}
		return instance;
	}
	
	virtual ~CGameSelect();

private:
	bool IsPassSelect[8];//选关状态
	bool IsGamePass[8];//通关状态
	bool GP[8];//鼠标放置
	int Gp;//鼠标放置关卡
	float GameTime[8];//关卡时间
	int GameMunber;//当前关卡

private:
	GameScene *pCGameScene;
	CGamePlay *pCGamePlay;//游戏场景
	CGamePeople *pCGamePeople;//人物
	CGameHinder *pCGameHinder;//阻碍
	CGameTime *pCGameTime;//计时器

	CAnimationSprite *GamePass[8];//游戏选关界面
	CAnimationSprite *GameScreen;//游戏界面
	CSprite *GFood[3];//食物
	CAnimationSprite *Again;//重来
	CAnimationSprite *Back;//返回
	CAnimationSprite *People;//操作的人物

public:
	void ChangePass();//改变通过的关卡的不同状态
	void MoveChangeGamePass();//划过效果
	void SelectGamePass();//点击关卡
	void MoveGamePass();//划过关卡
	void SetGamePass(int i);//设置通关状态
	void SetTip(ID2D1HwndRenderTarget *pRenderTarget, IDWriteTextFormat *pTextFormat, ID2D1SolidColorBrush *pTextBrush);//设置提示
	int GetGameMunber();//得到当前关卡

	void SetGameTime(int i,float p)
	{
		GameTime[i] = p;
	}
};

