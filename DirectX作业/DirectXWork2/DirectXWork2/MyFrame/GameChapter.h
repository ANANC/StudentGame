#pragma once

#include"WaterManager.h"
#include"..\OldFrame\ResourcesPool.h"
#include"NSpriteManager.h"
#include"NSprite.h"

#define DifficultL	 16
#define DifficultM	 5
#define DifficultB   1
#define EasyL		 12
#define EasyM		 8
#define EasyB		 3

enum GameProgress
{
	PGamePlaying,
	PGameWin,
	PGameOver
};

struct sGameKeep
{
	int sChapterNumber;
	int sMaxChapterNumber;
	int sWaterNumber;
};

class GameChapter
{
public:
	static GameChapter *GetInstance()
	{
		if (!instance)
		{
			instance = new GameChapter();
		}
		return instance;
	}

	virtual ~GameChapter(void);
private:
	GameChapter();
	static GameChapter *instance;
	
	CNSprite *pBackground;//����
	GWaterManager *pGWaterManager;//ˮ�ι�����

	int ChapterNumber;//��ǰ�⿨��
	int LitterNumber;//ˮ��-С״̬������
	int MiddleNumber;//ˮ��-��״̬������
	int BigNumber;//ˮ��-��״̬������
	int WaterNumber;//ˮ������
	int MaxChapterNumber;//��߹ؿ�

	GameProgress GProgress;//��Ϸ״̬

	POINT MClickPoint;//�����λ��

	RECT SelectNewGame;//ѡ������Ϸ
	BOOL IsSelectNewGame;//�Ƿ�ѡ������Ϸ
	BOOL IsGameWin;//��Ϸ�Ƿ�ʤ��

	int offset;//����״̬���λ�õ�ƫ����

public:
	void InitGame();//��ʼ����Ϸ
	void UpdateGame();//������Ϸ״̬
	void RenderGame(ID2D1HwndRenderTarget *pRenderTarget, IDWriteTextFormat *pTextFormat, ID2D1SolidColorBrush *pTextBrush, ID2D1SolidColorBrush *pBrush);
	//��ʾһЩ��Ϸ����
	void SetWaterNumber(int i = 0);//����ˮ������
	void Changedifficulty();//�޸��Ѷ�
	void MouseClick();//�����
	void IsChangeGameProgress();//�Ƿ�ı���Ϸ״̬-����Ƿ���Ϸʤ������ʧ��
	void GameSuccess();//��Ϸʤ��
	void GameOver();//��Ϸ����
	void GameKeep();//��Ϸ����
	void GameRead();//��ȡ����
	void GetMClickPoint(int,int);//��������λ��
};