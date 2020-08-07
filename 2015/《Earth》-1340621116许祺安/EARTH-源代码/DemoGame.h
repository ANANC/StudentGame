//DemoGame.h
#pragma once
#include "Framework\Game.h"
#define HinderNumber 30

class CDemoGame :public CGame
{
public:
	CDemoGame(HWND hWnd, int fps = 0);
	~CDemoGame(void);

public:
	void Init();
	void Update(float fDelataTime);
	void Render();

private:
	/*ͼƬ*/
	CAnimationSprite *GameStart;//��Ϸ��ʼ����
	CAnimationSprite *GamePass[8];//��Ϸѡ�ؽ���
	CAnimationSprite *GameScreen;//��Ϸ����
	CAnimationSprite *Hinder[8][HinderNumber];//�ϰ�
	int HinderSpeed[8][HinderNumber];//�ϰ����ٶ�
	int HinderNum[8];//�ϰ�������
	CSprite *GFood[3];//ʳ��
	CAnimationSprite *People;//����������
	CAnimationSprite *Again;//����
	CAnimationSprite *Back;//����
	CSprite *Fail;//ʧ��
	CSprite *Success;//ʤ��

	/*״̬*/
	int GameTime_min;//ʱ��ֲ���
	int GameTime_sec;//ʱ���벿��
	int GameTime_msec;//ʱ����벿��
	bool IsGameS;//��Ϸ״̬-true-ʤ��
	bool  IsGetHFood[3];//���ʳ��
	bool IsGamePass[8];//ͨ��״̬
	bool IsPassSelect[8];//ѡ��״̬
	float GameTime[8];//�ؿ�ʱ��
	int IsBSee[7];//�ϰ�״̬
	POINT Mpoint;//����ƶ�λ��
	POINT Cpoint;//�����λ��
	RECT rGameStart;
	int GameP;//��Ϸ����
	bool IsGamePlay;//������Ϸ
	float RotationAngle;//��ת�Ƕ�
	RECT ss;
	POINT oldPos;//����������һ��ʼ��λ��
	float PeoHeight;//�����ͼƬ�߶�
	float PeoWidth;//�����ͼƬ�߶�
	HFONT hf;//��ʱ���õĻ���
	bool bIsFly;  //�Ƿ��
	bool bIsDown; // �Ƿ�����
	float fFlyDistance; // ���и߶�
	int GameMunber;//��ǰ�⿨�Ĺ���
	int PlayWay;//�����Ƿ�ߵ�
	int IsStatic;//�����Ƿ�̶�
	int IsLeft[2][HinderNumber];//�����-�Ƿ����
	int rinSpeed;//��-�ٶȸı�

public:
	void GetPicture();//����ͼƬ
	void Erase();//������

	/*��ʼ����*/
	void MouseSide();//������λ��
	void MouseCSide(LPARAM lParam);//�����λ��
	void MouseMove();//������
	void MouseClick();//�����

	/*��Ϸѡ�ؽ���*/
	//void SelectPass();//�������ؿ�
	//void SelectNoPass();//���������ؿ�
	void ChangePass();//ͨ���Ĺؿ��Ĳ�ͬ״̬

	/*��Ϸ����*/

	void PeoMove(float fDelataTime);//��ɫ���ƶ�
	void TimerUpdate(float fDeltaTime);//��ʱ���ĸ���
	void TimerShow();//��ʱ������ʾ
	//void Restart();//����
	//void Return();//����
	void First_in();//��һ�ν�����Ϸ-��ûд
	void GameSuccess();//��Ϸʤ��-��ûд
	void GameOver();//��Ϸʧ��-��ûд
	void SetFood();//���õ���
	void GetFood();//��õ���

	/*�ϰ��ĳ���*/
	void HinderCreate(float fDeltaTime);//�����ϰ�-��
	void HinderShow_static();//�����ϰ�-�̶�
	void HinderFirst();//�ϰ���ʼ��
	void HinderVFail();//�ϰ�����
	void HinderMove();//�ϰ��ƶ�
	//void Crosswise();//�����ƶ�
	//void Lengthways();//�����ƶ�
	//void SLengthways();//�ر�������ƶ�

	/*�ϰ�����ʧ*/
	void HinderErase();//�ϰ���ʧ

	/*�����ϰ�*/
	void HinderTouch(float fDelataTime);//�Ӵ��ϰ�
	void TouchDie(int p);//��Ͱ�צ��-��
	void Reverse();//��-�ߵ�����
	void ChangeSide();//�ѹ�Ӣ-λ�øı�
	void rin();//��-�ٶȸı�
	void light(float fDelataTime);//����-�̶�2��
	void TouchNoSee();//��-������ʧ
};