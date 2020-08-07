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
	bool IsPassSelect[8];//ѡ��״̬
	bool IsGamePass[8];//ͨ��״̬
	bool GP[8];//������
	int Gp;//�����ùؿ�
	float GameTime[8];//�ؿ�ʱ��
	int GameMunber;//��ǰ�ؿ�

private:
	GameScene *pCGameScene;
	CGamePlay *pCGamePlay;//��Ϸ����
	CGamePeople *pCGamePeople;//����
	CGameHinder *pCGameHinder;//�谭
	CGameTime *pCGameTime;//��ʱ��

	CAnimationSprite *GamePass[8];//��Ϸѡ�ؽ���
	CAnimationSprite *GameScreen;//��Ϸ����
	CSprite *GFood[3];//ʳ��
	CAnimationSprite *Again;//����
	CAnimationSprite *Back;//����
	CAnimationSprite *People;//����������

public:
	void ChangePass();//�ı�ͨ���Ĺؿ��Ĳ�ͬ״̬
	void MoveChangeGamePass();//����Ч��
	void SelectGamePass();//����ؿ�
	void MoveGamePass();//�����ؿ�
	void SetGamePass(int i);//����ͨ��״̬
	void SetTip(ID2D1HwndRenderTarget *pRenderTarget, IDWriteTextFormat *pTextFormat, ID2D1SolidColorBrush *pTextBrush);//������ʾ
	int GetGameMunber();//�õ���ǰ�ؿ�

	void SetGameTime(int i,float p)
	{
		GameTime[i] = p;
	}
};

