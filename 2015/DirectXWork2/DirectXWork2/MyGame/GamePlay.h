#pragma once

#include <ctime>
#include"GameScene.h"
#include"People.h"
#include"GameHinder.h"
#include"GameSelect.h"
#include"GameTime.h"

using namespace std;

class CGamePlay
{
public:
	static CGamePlay *GetInstance()
	{
		if (!instance)
		{
			instance = new CGamePlay();
		}
		return instance;
	}

	virtual ~CGamePlay(void);

private:
	CGamePlay();
	static CGamePlay *instance;

	GameScene *pCGameScene;//场景类
	CGameSelect *pCGameSelect;//选关
	CGamePeople *pCGamePeople;//人物
	CGameHinder *pCGameHinder;//阻碍
	CGameTime *pCGameTime;//时间
	
	CAnimationSprite *Hinder[7][HinderNumber];//障碍
	CAnimationSprite *GamePass[8];//游戏选关界面
	CAnimationSprite *People;//操作的人物
	CAnimationSprite *GameScreen;//游戏界面
	CSprite *GFood[3];//食物
	CAnimationSprite *Again;//重来
	CAnimationSprite *Back;//返回
	CSprite *Fail;//失败
	CSprite *Success;//胜利

	POINT oldPos;//食物最开始的位置
	D2D1::Matrix3x2F World;//食物的位置参数
	
private:
	int  FoodNumber;//获得食物
	bool IsGetFood[3];//是否得到食物
	RECT ss;//圆的框
	bool IsMoveRestart;//鼠标是否放在重玩上
	bool IsMoveReturn;//鼠标是否放在返回上

	int HinderNum[7];//障碍的数量

public:
	void Restart();//重玩=初始化
	void Return();//返回
	void MoveReturn();//划过返回
	void MoveRestart();//划过重玩
	void SetFood();//放置道具
	void GetFood();//获得道具
	void FoodFirst();//道具初始化
	void First_in();//第一次进入游戏-还没写
	void GameOver();//放置游戏失败图片//游戏失败
	void GameSuccess(int);//游戏胜利
	bool IsRestart();//是否按重玩快捷键
	bool IsGOver();//是否按返回快捷键
	void IsMoveInRestart(ID2D1HwndRenderTarget *pRenderTarget, IDWriteTextFormat *pTextFormat, ID2D1SolidColorBrush *pTextBrush);
	//是否鼠标放到重玩上
	void IsMoveInReturn(ID2D1HwndRenderTarget *pRenderTarget, IDWriteTextFormat *pTextFormat, ID2D1SolidColorBrush *pTextBrush);
	//是否鼠标放到重玩上
	
	void GetIsGetFood(bool p[]){
		for (int i = 0; i < 3; i++)
			p[i] = IsGetFood[i];
	}
};