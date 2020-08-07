#pragma once

#include "..\���-3CGame\Game.h"
#include"GameStart.h"
#include"GameSelect.h"
#include"GamePlay.h"
#include"People.h"
#include"GameHinder.h"
#include"GameTime.h"
using namespace std;

class CDemoGame :public CGame
{
private:
	CDemoGame(HWND hWnd, int nFps = 0);
	static CDemoGame *instance;
	static HWND hWnd;
	static int nFps;

public:
	static CDemoGame *GetInstance(HWND hWnd, int nFps = 0)
	{
		if (!instance)
		{
			instance = new CDemoGame(hWnd,nFps);
		}
		return instance;
	}

	virtual ~CDemoGame(void);

	void InitGame();
	virtual void Update(float fDeltaTime);//֡����	
	virtual void Render();//��Ⱦ	

	/*���*/
	void MouseSide();//������λ��
	void MouseCSide();//�����λ��

private:
	GameProgress GameP;//��Ϸ״̬

	/*����*/
	GameScene *pCGameScene;//������
	CGameStart *pCGameStart;//��ʼ����
	CGameSelect *pCGameSelect;//ѡ�س���
	CGamePlay *pCGamePlay;//��Ϸ����
	CGamePeople *pCGamePeople;//����
	CGameHinder *pCGameHinder;//�谭
	CGameTime *pCGameTime;//��ʱ��
};
