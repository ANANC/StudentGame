#pragma once

#include"GameScene.h"


class CGamePlay;
class CGamePeople;
class CGameSelect;

class CGameHinder
{
private:
	GameScene *pCGameScene;//场景类
	CGamePlay *pCGamePlay;//游戏场景
	CGamePeople *pCGamePeople;//人物
	CGameSelect *pCGameSelect;//选关场景

	static CGameHinder *instance;
	CGameHinder();

	
public:
	static CGameHinder* GetInstance()
	{
		if (!instance)
		{
			instance = new CGameHinder();
		}
		return instance;
	}
	
	virtual ~CGameHinder(void);

private:
	

	CSprite *GFood[3];//食物
	CAnimationSprite *People;//操作的人物
	CAnimationSprite *Hinder[7][HinderNumber];//障碍
	int HinderSpeed[7][HinderNumber];//障碍的速度
	int HinderNum[7];//障碍的数量
	int IsBSee[7];//障碍状态
	int PlayWay;//操作是否颠倒
	bool IsStatic;//人物是否固定
	int IsLeft[2][HinderNumber];//鱼和云-是否左边
	int rinSpeed;//雨-速度改变
	
	POINT oldPos_2;//静态障碍的初始化位置-树
	POINT oldPos_3;//静态障碍的初始化位置-蒲公英

	int GameNumber;//当前光卡关数
	RECT rectClient;
	D2D1::Matrix3x2F World;//食物的位置参数

public:
	void HinderCreate(/*float fDeltaTime*/);//创建障碍-动
	void HinderShow_static();//创建障碍-固定
	void HinderErase();//障碍消失
	void GetHinder();//创建障碍指针
	void HinderMove();//障碍移动

	void HinderTouch(float fDelataTime);//接触障碍
	void TouchDie(int p);//鱼和八爪鱼-死
	void Reverse(float fDelataTime);//树-颠倒操作
	void ChangeSide();//蒲公英-位置改变
	void rin();//雨-速度改变
	void light(float fDelataTime);//闪电-固定2秒
	void TouchNoSee();//云-触碰消失

	void GetPlayWay(int &p){ p = PlayWay; }
	void GetIsStatic(bool &p){ p = IsStatic; }
	void GetrinSpeed(int &p){ p = rinSpeed; }
	void GetHinderNum(int p[]){
		for (int i = 0; i < 7; i++)
			p[i] = HinderNum[i];
	}
};