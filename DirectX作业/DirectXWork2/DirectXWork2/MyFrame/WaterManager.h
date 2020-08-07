#pragma once

#include"GWater.h"
#include"GWaterSmall.h"
#include<vector>
#include<list>
#include<time.h>

#define row 5//��
#define col 5//��

class GWaterManager 
{
public:
	static GWaterManager *GetInstance()
	{
		if (!instance)
		{
			instance = new GWaterManager();
		}
		return instance;
	}

	virtual ~GWaterManager(void);
private:
	GWaterManager();
	static GWaterManager *instance;

	GameWater *pGameWater[row*col];//��ˮ������
	list<GameWaterSmall *> pGameWaterSmall;//Сˮ������
	list<GameWaterSmall *>::iterator Iterator;//Сˮ������ĵ�����

	RECT rClient;
	vector<int> TNumber;//�Ӵ�������
	int AddWNumber;//�Ƿ�����ˮ������

public:
	void Init();//��ʼ��
	void MClick(POINT p);//���
	void GetTouchNumber(GameWaterSmall *, int);//���Ҫ���Ӵ����±�
	void WaterTouch();//�Ӵ�
	void InitWprocession(int,int,int);//��ʼ��ˮ�ε�״̬
	int GetAddWNumber();//����Ƿ�����ˮ��������ֵ
	void SetAddWNumber(int = 0);//�����Ƿ�����ˮ��������ֵ
	BOOL IsTouch(GameWater **, GameWaterSmall *, int);//�Ƿ���-����
	BOOL IsAllNothing();//�Ƿ����е�ˮ�ζ��Ǳ��㱬��
};