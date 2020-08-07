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
	
	CNSprite *pBackground;//背景
	GWaterManager *pGWaterManager;//水滴管理类

	int ChapterNumber;//当前光卡数
	int LitterNumber;//水滴-小状态的数量
	int MiddleNumber;//水滴-中状态的数量
	int BigNumber;//水滴-大状态的数量
	int WaterNumber;//水滴总量
	int MaxChapterNumber;//最高关卡

	GameProgress GProgress;//游戏状态

	POINT MClickPoint;//鼠标点击位置

	RECT SelectNewGame;//选择新游戏
	BOOL IsSelectNewGame;//是否选择新游戏
	BOOL IsGameWin;//游戏是否胜利

	int offset;//基础状态输出位置的偏移量

public:
	void InitGame();//初始化游戏
	void UpdateGame();//更新游戏状态
	void RenderGame(ID2D1HwndRenderTarget *pRenderTarget, IDWriteTextFormat *pTextFormat, ID2D1SolidColorBrush *pTextBrush, ID2D1SolidColorBrush *pBrush);
	//显示一些游戏画面
	void SetWaterNumber(int i = 0);//设置水滴容量
	void Changedifficulty();//修改难度
	void MouseClick();//鼠标点击
	void IsChangeGameProgress();//是否改变游戏状态-检测是否游戏胜利或者失败
	void GameSuccess();//游戏胜利
	void GameOver();//游戏结束
	void GameKeep();//游戏保存
	void GameRead();//读取进度
	void GetMClickPoint(int,int);//获得鼠标点击位置
};