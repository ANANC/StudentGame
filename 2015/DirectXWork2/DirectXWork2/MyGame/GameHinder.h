#pragma once

#include"GameScene.h"


class CGamePlay;
class CGamePeople;
class CGameSelect;

class CGameHinder
{
private:
	GameScene *pCGameScene;//������
	CGamePlay *pCGamePlay;//��Ϸ����
	CGamePeople *pCGamePeople;//����
	CGameSelect *pCGameSelect;//ѡ�س���

	static CGameHinder *instance;
	CGameHinder();

	
public:
	static CGameHinder* GetInstance()
	{
		if (!instance)
		{
			instance = new CGameHinder();
		}
		return instance;
	}
	
	virtual ~CGameHinder(void);

private:
	

	CSprite *GFood[3];//ʳ��
	CAnimationSprite *People;//����������
	CAnimationSprite *Hinder[7][HinderNumber];//�ϰ�
	int HinderSpeed[7][HinderNumber];//�ϰ����ٶ�
	int HinderNum[7];//�ϰ�������
	int IsBSee[7];//�ϰ�״̬
	int PlayWay;//�����Ƿ�ߵ�
	bool IsStatic;//�����Ƿ�̶�
	int IsLeft[2][HinderNumber];//�����-�Ƿ����
	int rinSpeed;//��-�ٶȸı�
	
	POINT oldPos_2;//��̬�ϰ��ĳ�ʼ��λ��-��
	POINT oldPos_3;//��̬�ϰ��ĳ�ʼ��λ��-�ѹ�Ӣ

	int GameNumber;//��ǰ�⿨����
	RECT rectClient;
	D2D1::Matrix3x2F World;//ʳ���λ�ò���

public:
	void HinderCreate(/*float fDeltaTime*/);//�����ϰ�-��
	void HinderShow_static();//�����ϰ�-�̶�
	void HinderErase();//�ϰ���ʧ
	void GetHinder();//�����ϰ�ָ��
	void HinderMove();//�ϰ��ƶ�

	void HinderTouch(float fDelataTime);//�Ӵ��ϰ�
	void TouchDie(int p);//��Ͱ�צ��-��
	void Reverse(float fDelataTime);//��-�ߵ�����
	void ChangeSide();//�ѹ�Ӣ-λ�øı�
	void rin();//��-�ٶȸı�
	void light(float fDelataTime);//����-�̶�2��
	void TouchNoSee();//��-������ʧ

	void GetPlayWay(int &p){ p = PlayWay; }
	void GetIsStatic(bool &p){ p = IsStatic; }
	void GetrinSpeed(int &p){ p = rinSpeed; }
	void GetHinderNum(int p[]){
		for (int i = 0; i < 7; i++)
			p[i] = HinderNum[i];
	}
};