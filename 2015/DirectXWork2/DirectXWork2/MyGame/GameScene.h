#pragma once

//#include<Windows.h>
//#include<dwrite.h>
#include"..\框架-3CGame\SpritesManager.h"
#include"..\框架-3CGame\ResourcesPool.h"

#define HinderNumber 20

using namespace std;

enum GameProgress /*游戏状态*/
{
	PGameStart,
	PGameSelect,
	PGamePlaying,
	PGamePlayWin,
	PGamePlayFail
};

class GameScene
{
public:
	static GameScene *GetInstance()
	{
		if (!instance)
		{
			instance = new GameScene();
		}
		return instance;
	}

	virtual ~GameScene(void);

private:
	GameScene();
	static GameScene *instance;

	static POINT Mpoint;//鼠标移动位置
	static POINT Cpoint;//鼠标点击位置
	GameProgress GameP;//游戏进程-开始还是选关还是进行游戏中

	CAnimationSprite *GameStart;//游戏开始界面
	CAnimationSprite *GamePass[8];//游戏选关界面
	CAnimationSprite *GameScreen;//游戏界面
	//static CSprite *Two_F;//鱼背景
	//static CAnimationSprite *Two_FF[2];//深海大鱼
	CSprite *GFood[3];//食物
	CAnimationSprite *Again;//重来
	CAnimationSprite *Back;//返回
	CSprite *Fail;//失败
	CSprite *Success;//胜利
	CAnimationSprite *People;//操作的人物
	CAnimationSprite *Hinder[7][HinderNumber];//障碍

/*图片相关函数*/
	void InitPicture();//载入图片
	void InitpPicture();//载入精灵

public:
	static void MouseSide(POINT MS);//鼠标放置位置
	static void MouseCSide(POINT MC);//鼠标点击位置

	inline void SetGameP(GameProgress);//设置游戏进程
	GameProgress GetGameP(){return GameP;}//得到游戏进度
	inline POINT GetMpoint(){ return Mpoint; }//得到鼠标移动位置
	inline POINT GetCpoint(){ return Cpoint; }//得到鼠标移动位置

public:
	void GetGameStart(CAnimationSprite **p){
		*p = GameStart;}

	void GetGamePass(CAnimationSprite *p[]){
		for (int i = 0; i < 8; i++)
		{
			p[i] = GamePass[i];
		}
	}

	void GetGameScreen(CAnimationSprite **p){
	*p = GameScreen;}

	void GetAgain(CAnimationSprite **p){
		*p = Again; }

	void GetBack(CAnimationSprite **p){
		*p = Back; }

	void GetPeople(CAnimationSprite **p){
		*p = People; }

	void GetHinder(CAnimationSprite *p[][HinderNumber]){
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < HinderNumber;j++)
				p[i][j] = Hinder[i][j];
		}
	}

	void GetGFood(CSprite *p[]){ 
		for (int i = 0; i < 3; i++)
		{
			p[i] = GFood[i];
		}
	}

	void GetFail(CSprite **p){ 
		*p = Fail; }

	void GetSuccess(CSprite **p){ 
		*p = Success; }
};