#pragma once

#include"GWater.h"
#include"GWaterSmall.h"
#include<vector>
#include<list>
#include<time.h>

#define row 5//行
#define col 5//列

class GWaterManager 
{
public:
	static GWaterManager *GetInstance()
	{
		if (!instance)
		{
			instance = new GWaterManager();
		}
		return instance;
	}

	virtual ~GWaterManager(void);
private:
	GWaterManager();
	static GWaterManager *instance;

	GameWater *pGameWater[row*col];//大水滴数组
	list<GameWaterSmall *> pGameWaterSmall;//小水滴链表
	list<GameWaterSmall *>::iterator Iterator;//小水滴链表的迭代器

	RECT rClient;
	vector<int> TNumber;//接触的数组
	int AddWNumber;//是否增加水滴容量

public:
	void Init();//初始化
	void MClick(POINT p);//点击
	void GetTouchNumber(GameWaterSmall *, int);//获得要检测接触的下标
	void WaterTouch();//接触
	void InitWprocession(int,int,int);//初始化水滴的状态
	int GetAddWNumber();//获得是否增加水滴容量的值
	void SetAddWNumber(int = 0);//设置是否增加水滴容量的值
	BOOL IsTouch(GameWater **, GameWaterSmall *, int);//是否触碰-精灵
	BOOL IsAllNothing();//是否所有的水滴都是被点爆了
};