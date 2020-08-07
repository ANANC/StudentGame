#pragma once
#include<Windows.h>
#include"..\OldFrame\ResourcesPool.h"
#include"NSpriteManager.h"

using namespace std;

enum WaterProgress /*ˮ��״̬*/
{
	little,
	middle1,
	middle2,
	big,
	NothingWithSmall,
	Nothing
};


class GameWater
{
public:
	GameWater();
	~GameWater();

private:
	CAnimationSprite *pWater;

	D2D1_POINT_2F Wpos;//����λ��-��
	
	BOOL Touch;//����
	WaterProgress GWProgress;//ˮ��״̬
	
	RECT WaterRect[4];//ˮ�εľ���
	
	int Col;//����
	int Row;//����

public:
	void SetWaterPos(D2D1_POINT_2F);//��������λ��
	D2D1_POINT_2F GetWaterPos();//����ˮ�ε�����λ��
	RECT GetWaterRect(WaterProgress);//ˮ�εľ���

	void SetClick();//���
	BOOL IsClick(POINT);//�Ƿ񱻵����

	void ChangeWaterProgress();//�ı�ˮ�ε�״̬
	WaterProgress GetGWProgress();//����ˮ��״̬
	void SetGWProgress(WaterProgress);//����ˮ��״̬

	void SetTouch(bool);//���ô���ˮ�εĺ���
	BOOL GetTouch();//���ش���ˮ�κ���
	BOOL IsTouch(RECT &);//�Ƿ�Ӵ�-����
	BOOL IsTouch(CNSprite );//�Ƿ�Ӵ�-����

	void SetCol(int);//��������
	int GetCol ();//��������
	void SetRow(int);//��������
	int GetRow();//��������
	
	void SetVisible(bool);//���ÿɼ���
};