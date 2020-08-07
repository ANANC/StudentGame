#pragma once

#include"GameScene.h"


using namespace std;
class CGameStart
{
public:
	CGameStart();
	~CGameStart();

private:
	GameScene *pCGameScene;//场景类
	CAnimationSprite *GameStart;//游戏开始界面
	CAnimationSprite *GamePass[8];//游戏选关界面

private:
	RECT rGameStart;//开始的框
	bool IsSelectGameStart;//是否接触着
public:
	void SelectGameStrat();//点击开始
	void MoveGameStrat();//划过开始
	void GameStartPlay();//播放开始动画
};