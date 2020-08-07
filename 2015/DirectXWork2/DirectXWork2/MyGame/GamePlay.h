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

	GameScene *pCGameScene;//������
	CGameSelect *pCGameSelect;//ѡ��
	CGamePeople *pCGamePeople;//����
	CGameHinder *pCGameHinder;//�谭
	CGameTime *pCGameTime;//ʱ��
	
	CAnimationSprite *Hinder[7][HinderNumber];//�ϰ�
	CAnimationSprite *GamePass[8];//��Ϸѡ�ؽ���
	CAnimationSprite *People;//����������
	CAnimationSprite *GameScreen;//��Ϸ����
	CSprite *GFood[3];//ʳ��
	CAnimationSprite *Again;//����
	CAnimationSprite *Back;//����
	CSprite *Fail;//ʧ��
	CSprite *Success;//ʤ��

	POINT oldPos;//ʳ���ʼ��λ��
	D2D1::Matrix3x2F World;//ʳ���λ�ò���
	
private:
	int  FoodNumber;//���ʳ��
	bool IsGetFood[3];//�Ƿ�õ�ʳ��
	RECT ss;//Բ�Ŀ�
	bool IsMoveRestart;//����Ƿ����������
	bool IsMoveReturn;//����Ƿ���ڷ�����

	int HinderNum[7];//�ϰ�������

public:
	void Restart();//����=��ʼ��
	void Return();//����
	void MoveReturn();//��������
	void MoveRestart();//��������
	void SetFood();//���õ���
	void GetFood();//��õ���
	void FoodFirst();//���߳�ʼ��
	void First_in();//��һ�ν�����Ϸ-��ûд
	void GameOver();//������Ϸʧ��ͼƬ//��Ϸʧ��
	void GameSuccess(int);//��Ϸʤ��
	bool IsRestart();//�Ƿ������ݼ�
	bool IsGOver();//�Ƿ񰴷��ؿ�ݼ�
	void IsMoveInRestart(ID2D1HwndRenderTarget *pRenderTarget, IDWriteTextFormat *pTextFormat, ID2D1SolidColorBrush *pTextBrush);
	//�Ƿ����ŵ�������
	void IsMoveInReturn(ID2D1HwndRenderTarget *pRenderTarget, IDWriteTextFormat *pTextFormat, ID2D1SolidColorBrush *pTextBrush);
	//�Ƿ����ŵ�������
	
	void GetIsGetFood(bool p[]){
		for (int i = 0; i < 3; i++)
			p[i] = IsGetFood[i];
	}
};