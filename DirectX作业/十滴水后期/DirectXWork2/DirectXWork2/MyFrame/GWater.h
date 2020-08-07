#pragma once
#include<Windows.h>
#include"..\OldFrame\ResourcesPool.h"
#include"NSpriteManager.h"

using namespace std;

enum WaterProgress /*水滴状态*/
{
	little,
	middle1,
	middle2,
	big,
	NothingWithSmall,
	Nothing
};


class GameWater
{
public:
	GameWater();
	~GameWater();

private:
	CAnimationSprite *pWater;

	D2D1_POINT_2F Wpos;//坐标位置-大
	
	BOOL Touch;//触碰
	WaterProgress GWProgress;//水滴状态
	
	RECT WaterRect[4];//水滴的矩形
	
	int Col;//列数
	int Row;//行数

public:
	void SetWaterPos(D2D1_POINT_2F);//设置坐标位置
	D2D1_POINT_2F GetWaterPos();//返回水滴的坐标位置
	RECT GetWaterRect(WaterProgress);//水滴的矩形

	void SetClick();//点击
	BOOL IsClick(POINT);//是否被点击了

	void ChangeWaterProgress();//改变水滴的状态
	WaterProgress GetGWProgress();//返回水滴状态
	void SetGWProgress(WaterProgress);//设置水滴状态

	void SetTouch(bool);//设置触碰水滴的号码
	BOOL GetTouch();//返回触碰水滴号码
	BOOL IsTouch(RECT &);//是否接触-矩形
	BOOL IsTouch(CNSprite );//是否接触-精灵

	void SetCol(int);//设置列数
	int GetCol ();//返回列数
	void SetRow(int);//设置行数
	int GetRow();//返回行数
	
	void SetVisible(bool);//设置可见性
};