#pragma once
#include<Windows.h>
#include"..\OldFrame\ResourcesPool.h"
#include"NSpriteManager.h"

using namespace std;

class GameWaterSmall
{
public:
	GameWaterSmall();
	~GameWaterSmall();

private:
	CAnimationSprite *pWaterSmall[4];

	D2D1_POINT_2F WSpos[4];//����λ��-С
	RECT WaterSamllRect[4];//Сˮ�εľ���
	int SmallOverNumber;//Сˮ�ε�����״̬

	int Col;
	int Row;

public:
	void SetWaterSPos(int, D2D1_POINT_2F);//����Сˮ�ε�����λ��
	D2D1_POINT_2F GetWatersHotPos(int);//����Сˮ�ε��ȵ�ƫ����
	D2D1_POINT_2F GetWaterSPos(int);//����Сˮ�ε�����λ��
	const D2D1_RECT_F *GetWatersBoundingBox(int);//����Сˮ�εİ�Χ��
	const CAnimationSprite GetWatersAnimationSprite(int);//����Сˮ��

	void SetSmallOverNumber(int i=-1);//����Сˮ�ε�����״̬
	int GetSmallOverNumber();//�õ�Сˮ�ε�����״̬
	void SetWaterSamllVisible(int,BOOL);//����Сˮ�εĿɼ���
	BOOL GetWaterSamllVisible(int);//�õ�Сˮ�εĿɼ���

	void SetCol(int);//��������
	int GetCol();//��������
	void SetRow(int);//��������
	int GetRow();//��������
};