//DemoGame.h
#pragma once
#include "Framework\Game.h"
#define HinderNumber 30

class CDemoGame :public CGame
{
public:
	CDemoGame(HWND hWnd, int fps = 0);
	~CDemoGame(void);

public:
	void Init();
	void Update(float fDelataTime);
	void Render();

private:
	/*图片*/
	CAnimationSprite *GameStart;//游戏开始界面
	CAnimationSprite *GamePass[8];//游戏选关界面
	CAnimationSprite *GameScreen;//游戏界面
	CAnimationSprite *Hinder[8][HinderNumber];//障碍
	int HinderSpeed[8][HinderNumber];//障碍的速度
	int HinderNum[8];//障碍的数量
	CSprite *GFood[3];//食物
	CAnimationSprite *People;//操作的人物
	CAnimationSprite *Again;//重来
	CAnimationSprite *Back;//返回
	CSprite *Fail;//失败
	CSprite *Success;//胜利

	/*状态*/
	int GameTime_min;//时间分部分
	int GameTime_sec;//时间秒部分
	int GameTime_msec;//时间毫秒部分
	bool IsGameS;//游戏状态-true-胜利
	bool  IsGetHFood[3];//获得食物
	bool IsGamePass[8];//通关状态
	bool IsPassSelect[8];//选关状态
	float GameTime[8];//关卡时间
	int IsBSee[7];//障碍状态
	POINT Mpoint;//鼠标移动位置
	POINT Cpoint;//鼠标点击位置
	RECT rGameStart;
	int GameP;//游戏进程
	bool IsGamePlay;//进行游戏
	float RotationAngle;//旋转角度
	RECT ss;
	POINT oldPos;//操作的人物一开始的位置
	float PeoHeight;//人物的图片高度
	float PeoWidth;//人物的图片高度
	HFONT hf;//计时器用的画笔
	bool bIsFly;  //是否飞
	bool bIsDown; // 是否下落
	float fFlyDistance; // 飞行高度
	int GameMunber;//当前光卡的关数
	int PlayWay;//操作是否颠倒
	int IsStatic;//人物是否固定
	int IsLeft[2][HinderNumber];//鱼和云-是否左边
	int rinSpeed;//雨-速度改变

public:
	void GetPicture();//载入图片
	void Erase();//清理工作

	/*开始界面*/
	void MouseSide();//鼠标放置位置
	void MouseCSide(LPARAM lParam);//鼠标点击位置
	void MouseMove();//鼠标放置
	void MouseClick();//鼠标点击

	/*游戏选关界面*/
	//void SelectPass();//点击可玩关卡
	//void SelectNoPass();//点击不可玩关卡
	void ChangePass();//通过的关卡的不同状态

	/*游戏界面*/

	void PeoMove(float fDelataTime);//角色的移动
	void TimerUpdate(float fDeltaTime);//计时器的更新
	void TimerShow();//计时器的显示
	//void Restart();//重玩
	//void Return();//返回
	void First_in();//第一次进入游戏-还没写
	void GameSuccess();//游戏胜利-还没写
	void GameOver();//游戏失败-还没写
	void SetFood();//放置道具
	void GetFood();//获得道具

	/*障碍的出现*/
	void HinderCreate(float fDeltaTime);//创建障碍-动
	void HinderShow_static();//创建障碍-固定
	void HinderFirst();//障碍初始化
	void HinderVFail();//障碍清理
	void HinderMove();//障碍移动
	//void Crosswise();//横向移动
	//void Lengthways();//纵向移动
	//void SLengthways();//特别的纵向移动

	/*障碍的消失*/
	void HinderErase();//障碍消失

	/*触碰障碍*/
	void HinderTouch(float fDelataTime);//接触障碍
	void TouchDie(int p);//鱼和八爪鱼-死
	void Reverse();//树-颠倒操作
	void ChangeSide();//蒲公英-位置改变
	void rin();//雨-速度改变
	void light(float fDelataTime);//闪电-固定2秒
	void TouchNoSee();//云-触碰消失
};