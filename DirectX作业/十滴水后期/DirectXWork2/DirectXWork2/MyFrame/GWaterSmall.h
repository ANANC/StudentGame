#pragma once
#include<Windows.h>
#include"..\OldFrame\ResourcesPool.h"
#include"NSpriteManager.h"

using namespace std;

class GameWaterSmall
{
public:
	GameWaterSmall();
	~GameWaterSmall();

private:
	CAnimationSprite *pWaterSmall[4];

	D2D1_POINT_2F WSpos[4];//坐标位置-小
	RECT WaterSamllRect[4];//小水滴的矩形
	int SmallOverNumber;//小水滴的脱离状态

	int Col;
	int Row;

public:
	void SetWaterSPos(int, D2D1_POINT_2F);//设置小水滴的坐标位置
	D2D1_POINT_2F GetWatersHotPos(int);//返回小水滴的热点偏移量
	D2D1_POINT_2F GetWaterSPos(int);//返回小水滴的坐标位置
	const D2D1_RECT_F *GetWatersBoundingBox(int);//返回小水滴的包围盒
	const CAnimationSprite GetWatersAnimationSprite(int);//返回小水滴

	void SetSmallOverNumber(int i=-1);//设置小水滴的脱离状态
	int GetSmallOverNumber();//得到小水滴的脱离状态
	void SetWaterSamllVisible(int,BOOL);//设置小水滴的可见性
	BOOL GetWaterSamllVisible(int);//得到小水滴的可见性

	void SetCol(int);//设置列数
	int GetCol();//返回列数
	void SetRow(int);//设置行数
	int GetRow();//返回行数
};