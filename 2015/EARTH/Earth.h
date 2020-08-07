#pragma once
#include "Framework\Game.h"
#define HinderNumber 20


class Earth :public CGame
{
public:
	Earth(HWND hWnd, int fps = 0);
	~Earth(void);

public:
	void Init();
	void Update(float fDelataTime);
	void Render();

/*准备工作*/
private:
	POINT Mpoint;//鼠标移动位置
	POINT Cpoint;//鼠标点击位置
	int GameP;//游戏进程-开始还是选关还是进行游戏中
	bool IsGamePlay;//进行游戏
	bool IsGameOver;//游戏是否关闭
public:
	void GetPicture();//载入图片
	void Erase();//清理工作
	void MouseSide();//鼠标放置位置
	void MouseCSide();//鼠标点击位置
	void MouseMove();//鼠标放置
	void MouseClick();//鼠标点击
	void GamePlaing(bool);//游戏是否进行中
	void GameProgress(int);//设置游戏进程
	inline int GetGameP();//得到游戏进度
	void SetGameOver();//设置关闭游戏
	void White();//记录数据
	void Read();//读取数据
	

/*开始界面*/
private:
	CAnimationSprite *GameStart;//游戏开始界面
	RECT rGameStart;//开始的框
	bool IsSelectGameStart;//是否接触着
public:
	void GetGameStart();//得到图片
	void DeleteGameStart();//清理工作
	void SelectGameStrat();//点击开始
	void MoveGameStrat();//划过开始
	void GameStartPlay();//播放图画

/*选关界面*/
private:
	CAnimationSprite *GamePass[8];//游戏选关界面
	bool IsPassSelect[8];//选关状态
	bool IsGamePass[8];//通关状态
	bool GP[8];//鼠标放置
	int Gp;//鼠标放置关卡
	float GameTime[8];//关卡时间
	int GameMunber;//当前关卡
public:
	void ChangePass();//通过的关卡的不同状态
	void GetGamePass();//得到图片
	void DeleteGamePass();//清理工作
	void SelectGamePass();//点击关卡
	void MoveGamePass();//划过关卡
	void SetGameTime(int p,int m,int s);//设置通关时间
	void SetGamePass(int i);//设置通关状态
	void SetTip();//设置提示
	inline int GetGameMunber();//得到当前关卡

/*游戏界面*/
private:
	CAnimationSprite *GameScreen;//游戏界面
	CSprite *GFood[3];//食物
	CAnimationSprite *Again;//重来
	CAnimationSprite *Back;//返回
	CSprite *Fail;//失败
	CSprite *Success;//胜利
	int  FoodNumber;//获得食物
	bool IsGetFood[3];//是否得到食物
	RECT ss;//圆的框
	bool IsMoveRestart;//鼠标是否放在重玩上
	bool IsMoveReturn;//鼠标是否放在返回上
public:
	void GetPlayScreen();//得到游戏界面的图片
	void DelectPlayScreen();//清理图片
	void Restart();//重玩=初始化
	void Return();//返回
	void MoveReturn();//划过返回
	void MoveRestart();//划过重玩
	void SetFood();//放置道具
	void GetFood();//获得道具
	void FoodFirst();//道具初始化
	void First_in();//第一次进入游戏-还没写
	void GameSuccess();//放置游戏胜利图片
	void GameOver();//放置游戏失败图片
	void GameSuccess(int);//游戏胜利
	inline bool IsRestart();//是否按重玩快捷键
	inline bool IsGOver();//是否按返回快捷键
	void IsMoveInRestart();//是否鼠标放到重玩上
	void IsMoveInReturn();//是否鼠标放到重玩上

/*操作人物*/
private:
	CAnimationSprite *People;//操作的人物
	float RotationAngle;//旋转角度
	POINT oldPos;//操作的人物一开始的位置
	float PeoHeight;//人物的图片高度
	float PeoWidth;//人物的图片高度
	bool bIsFly;  //是否飞
	bool bIsDown; // 是否下落
	float fFlyDistance; // 飞行高度
	POINT PeopleXaY;//人物的位置
public:
	void GetPeople();//得到图片
	void DelectPeople();//清理图片
	void PeoMove(float fDelataTime);//角色的移动
	void PeoFirst();//角色的初始化
	void GetPeopleXandY();//得到人物的位置

/*计时器*/
private:
	int GameTime_min;//时间分部分
	int GameTime_sec;//时间秒部分
	int GameTime_msec;//时间毫秒部分
	HFONT hf;//计时器用的画笔
	int fD;//计时器的累加
public:
	void TimerUpdate(float fDeltaTime);//计时器的更新
	void TimerShow();//计时器的显示
	void Selecthf();//选入画笔
	void Delecthf();//删除画笔
	void TimeFirst();//计时器初始化


/*障碍*/
private:
	CAnimationSprite *Hinder[7][HinderNumber];//障碍
	int HinderSpeed[7][HinderNumber];//障碍的速度
	int HinderNum[7];//障碍的数量
	int IsBSee[7];//障碍状态
	int PlayWay;//操作是否颠倒
	bool IsStatic;//人物是否固定
	int IsLeft[2][HinderNumber];//鱼和云-是否左边
	int rinSpeed;//雨-速度改变
public:
	void HinderCreate(/*float fDeltaTime*/);//创建障碍-动
	void HinderShow_static();//创建障碍-固定
	void HinderErase();//障碍消失
	void GetHinder();//创建障碍指针
	void DelectHinder();//障碍清理
	void HinderMove();//障碍移动
	void HinderTouch(float fDelataTime);//接触障碍
	void TouchDie(int p);//鱼和八爪鱼-死
	void Reverse(float fDelataTime);//树-颠倒操作
	void ChangeSide();//蒲公英-位置改变
	void rin();//雨-速度改变
	void light(float fDelataTime);//闪电-固定2秒
	void TouchNoSee();//云-触碰消失
	
};