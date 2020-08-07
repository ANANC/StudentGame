#pragma once
#include"GameScene.h"
#include"GameHinder.h"

using namespace std;

class CGamePeople
{
public:
	static CGamePeople *GetInstance()
	{
		if (!instance)
		{
			instance = new CGamePeople();
		}
		return instance;
	}


	~CGamePeople();

private:
	CGamePeople();
	static CGamePeople *instance;

	GameScene *pCGameScene;//场景类

	CAnimationSprite *People;//操作的人物
	float RotationAngle;//旋转角度
	POINT oldPos;//操作的人物一开始的位置
	float PeoHeight;//人物的图片高度
	float PeoWidth;//人物的图片高度
	bool bIsFly;  //是否飞
	bool bIsDown; // 是否下落
	float fFlyDistance; // 飞行高度
	POINT PeopleXaY;//人物的位置

	int PlayWay;//操作是否颠倒
	bool IsStatic;//人物是否固定
	int rinSpeed;//雨-速度改变

	/*人物旋转参数*/
	D2D1::Matrix3x2F Rotation;
	D2D1::Matrix3x2F Translation;
	D2D1::Matrix3x2F World;
	ID2D1Bitmap *pBitmap;

public:
	void PeoMove(float fDelataTime);//角色的移动
	void ShowPeoMove(ID2D1HwndRenderTarget *pRenderTarget);//渲染人物
	void PeoFirst();//角色的初始化
	void GetPeopleXandY();//得到人物的位置

	void SetRotationAngle(float p){ RotationAngle += p; }
};