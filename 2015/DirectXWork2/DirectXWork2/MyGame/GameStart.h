#pragma once

#include"GameScene.h"


using namespace std;
class CGameStart
{
public:
	CGameStart();
	~CGameStart();

private:
	GameScene *pCGameScene;//������
	CAnimationSprite *GameStart;//��Ϸ��ʼ����
	CAnimationSprite *GamePass[8];//��Ϸѡ�ؽ���

private:
	RECT rGameStart;//��ʼ�Ŀ�
	bool IsSelectGameStart;//�Ƿ�Ӵ���
public:
	void SelectGameStrat();//�����ʼ
	void MoveGameStrat();//������ʼ
	void GameStartPlay();//���ſ�ʼ����
};