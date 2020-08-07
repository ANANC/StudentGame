#pragma once

#include"GameScene.h"
//#include"GameSelect.h"

using namespace std;
class CGameSelect;
class CGameTime
{
public:
	static CGameTime *GetInstance()
	{
		if (!instance)
		{
			instance = new CGameTime();
		}
		return instance;
	}

	~CGameTime();

private:
	CGameTime();
	static CGameTime *instance;

	GameScene *pCGameScene;
	CGameSelect *pCGameSelect;

	int GameTime_min;//ʱ��ֲ���
	int GameTime_sec;//ʱ���벿��
	int GameTime_msec;//ʱ����벿��
	HFONT hf;//��ʱ���õĻ���
	int fD;//��ʱ�����ۼ�

public:
	void TimerUpdate(float fDeltaTime);//��ʱ���ĸ���
	void TimerShow(ID2D1HwndRenderTarget *pRenderTarget, IDWriteTextFormat *pTextFormat, ID2D1SolidColorBrush *pTextBrush);
	//��ʱ������ʾ
	void TimeFirst();//��ʱ����ʼ��

};