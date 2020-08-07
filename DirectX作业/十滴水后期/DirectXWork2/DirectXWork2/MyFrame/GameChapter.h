#pragma once

#include"WaterManager.h"
#include"..\OldFrame\ResourcesPool.h"
#include"NSpriteManager.h"
#include"NSprite.h"
#include"..\OldFrame\XAudio2SoundPlayer.h"

#define DifficultL	 12
#define DifficultM2	 8
#define DifficultM1	 4
#define DifficultB   3

#define EasyL		 7
#define EasyM2		 4
#define EasyM1		 8
#define EasyB		 7

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
	
	CAnimationSprite *pWaterNumber[2];//ˮ����������
	CAnimationSprite *pChapterNumber[2];//��ǰ�⿨������
	CAnimationSprite *pMaxChapterNumber[2];//��߹ؿ�����
	CAnimationSprite *pWin;//ʤ������
	CAnimationSprite *pFail;//ʧ�ܾ���
	CAnimationSprite *pBackground;//����

	POINT pWaterNumberWaH;//ˮ����������-��͸�
	POINT pChapterNumberWaH;//��ǰ�⿨������-��͸�
	POINT pMaxChapterNumberWaH;//��߹ؿ�����-��͸�

	GWaterManager *pGWaterManager;//ˮ�ι�����

	int ChapterNumber;//��ǰ�⿨��
	int LitterNumber;//ˮ��-С״̬������
	int MiddleNumber1;//ˮ��-��1״̬������
	int MiddleNumber2;//ˮ��-��2״̬������
	int BigNumber;//ˮ��-��״̬������
	int WaterNumber;//ˮ������
	int MaxChapterNumber;//��߹ؿ�

	GameProgress GProgress;//��Ϸ״̬

	POINT MClickPoint;//�����λ��

	RECT SelectNewGame;//ѡ������Ϸ
	BOOL IsSelectNewGame;//�Ƿ�ѡ������Ϸ
	RECT SelectNextGame;//ѡ����һ��
	BOOL IsSelectNextGame;//�Ƿ�ѡ����һ��

	int offset;//����״̬���λ�õ�ƫ����

	XAudio2SoundPlayer *pPassOrFailMusic;//������Ч

public:
	void InitGame();//��ʼ����Ϸ
	void UpdateGame();//������Ϸ״̬
	void RenderGame();//��ʾһЩ��Ϸ����
	void SetWaterNumber(int i = 0);//����ˮ������
	void Changedifficulty();//�޸��Ѷ�
	void MouseClick();//�����
	void IsChangeGameProgress();//�Ƿ�ı���Ϸ״̬-����Ƿ���Ϸʤ������ʧ��
	void GameSuccess();//��Ϸʤ��
	void GameOver();//��Ϸ����
	void GameKeep();//��Ϸ����
	void GameRead();//��ȡ����
	void GetMClickPoint(int,int);//��������λ��
	GameProgress GetGProgress();//�����Ϸ״̬
};