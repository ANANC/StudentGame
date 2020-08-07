#pragma once
#include "Framework\SpriteManager.h"

class Begin 
{
private:
	CAnimationSprite *GameStart;//游戏开始界面
	RECT rGameStart;//开始的框

public:
	void GetGameStart();//得到图片
	void Delete();//清理工作

};

void Begin::GetGameStart()
{
	GameStart = pSpriteManager->
}