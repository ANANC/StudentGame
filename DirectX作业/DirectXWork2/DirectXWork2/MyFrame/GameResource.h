#pragma once

#include"..\OldFrame\ResourcesPool.h"
#include"NSpriteManager.h"

class GameResource
{
public:
	static GameResource *GetInstance()
	{
		if (!instance)
		{
			instance = new GameResource();
		}
		return instance;
	}

	virtual ~GameResource(void);
private:
	GameResource();
	static GameResource *instance;
};

