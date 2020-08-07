#pragma once

#include"..\OldFrame\SpritesManager.h"
#include"NSprite.h"

class CNSpritesManager :public CSpritesManager
{
private:
	CNSpritesManager() :CSpritesManager()
	{
		pRenderTarget = NULL;
	}
	CNSpritesManager(const CNSpritesManager&) :CSpritesManager(){}
	CNSpritesManager &operator =(const CNSpritesManager&){}
	static CNSpritesManager *instance;

public:
	static CNSpritesManager *GetInstance()
	{
		if (!instance)
		{
			instance = new CNSpritesManager();
		}
		return instance;
	}
	virtual ~CNSpritesManager(void);

public:
	CNSprite * CreateNSprite(const wstring		sResourceName,
		//ResourceType		rt,
		D2D1_POINT_2F		&vPos,
		int					w = 0,
		int					h = 0,
		int					tx = 0,
		int					ty = 0,
		D2D1_POINT_2F		vHotSpot = D2D1::Point2F(0, 0)
		);
};