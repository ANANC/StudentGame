#pragma once
#include "Framework\SpriteManager.h"

class Begin 
{
private:
	CAnimationSprite *GameStart;//��Ϸ��ʼ����
	RECT rGameStart;//��ʼ�Ŀ�

public:
	void GetGameStart();//�õ�ͼƬ
	void Delete();//������

};

void Begin::GetGameStart()
{
	GameStart = pSpriteManager->
}