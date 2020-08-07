#pragma once
#include"GameScene.h"
#include"GameHinder.h"

using namespace std;

class CGamePeople
{
public:
	static CGamePeople *GetInstance()
	{
		if (!instance)
		{
			instance = new CGamePeople();
		}
		return instance;
	}


	~CGamePeople();

private:
	CGamePeople();
	static CGamePeople *instance;

	GameScene *pCGameScene;//������

	CAnimationSprite *People;//����������
	float RotationAngle;//��ת�Ƕ�
	POINT oldPos;//����������һ��ʼ��λ��
	float PeoHeight;//�����ͼƬ�߶�
	float PeoWidth;//�����ͼƬ�߶�
	bool bIsFly;  //�Ƿ��
	bool bIsDown; // �Ƿ�����
	float fFlyDistance; // ���и߶�
	POINT PeopleXaY;//�����λ��

	int PlayWay;//�����Ƿ�ߵ�
	bool IsStatic;//�����Ƿ�̶�
	int rinSpeed;//��-�ٶȸı�

	/*������ת����*/
	D2D1::Matrix3x2F Rotation;
	D2D1::Matrix3x2F Translation;
	D2D1::Matrix3x2F World;
	ID2D1Bitmap *pBitmap;

public:
	void PeoMove(float fDelataTime);//��ɫ���ƶ�
	void ShowPeoMove(ID2D1HwndRenderTarget *pRenderTarget);//��Ⱦ����
	void PeoFirst();//��ɫ�ĳ�ʼ��
	void GetPeopleXandY();//�õ������λ��

	void SetRotationAngle(float p){ RotationAngle += p; }
};