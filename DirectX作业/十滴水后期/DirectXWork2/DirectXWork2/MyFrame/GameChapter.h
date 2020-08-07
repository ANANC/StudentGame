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
	
	CAnimationSprite *pWaterNumber[2];//水滴总量精灵
	CAnimationSprite *pChapterNumber[2];//当前光卡数精灵
	CAnimationSprite *pMaxChapterNumber[2];//最高关卡精灵
	CAnimationSprite *pWin;//胜利精灵
	CAnimationSprite *pFail;//失败精灵
	CAnimationSprite *pBackground;//背景

	POINT pWaterNumberWaH;//水滴总量精灵-宽和高
	POINT pChapterNumberWaH;//当前光卡数精灵-宽和高
	POINT pMaxChapterNumberWaH;//最高关卡精灵-宽和高

	GWaterManager *pGWaterManager;//水滴管理类

	int ChapterNumber;//当前光卡数
	int LitterNumber;//水滴-小状态的数量
	int MiddleNumber1;//水滴-中1状态的数量
	int MiddleNumber2;//水滴-中2状态的数量
	int BigNumber;//水滴-大状态的数量
	int WaterNumber;//水滴总量
	int MaxChapterNumber;//最高关卡

	GameProgress GProgress;//游戏状态

	POINT MClickPoint;//鼠标点击位置

	RECT SelectNewGame;//选择新游戏
	BOOL IsSelectNewGame;//是否选择新游戏
	RECT SelectNextGame;//选择下一关
	BOOL IsSelectNextGame;//是否选择下一关

	int offset;//基础状态输出位置的偏移量

	XAudio2SoundPlayer *pPassOrFailMusic;//场景音效

public:
	void InitGame();//初始化游戏
	void UpdateGame();//更新游戏状态
	void RenderGame();//显示一些游戏画面
	void SetWaterNumber(int i = 0);//设置水滴容量
	void Changedifficulty();//修改难度
	void MouseClick();//鼠标点击
	void IsChangeGameProgress();//是否改变游戏状态-检测是否游戏胜利或者失败
	void GameSuccess();//游戏胜利
	void GameOver();//游戏结束
	void GameKeep();//游戏保存
	void GameRead();//读取进度
	void GetMClickPoint(int,int);//获得鼠标点击位置
	GameProgress GetGProgress();//获得游戏状态
};