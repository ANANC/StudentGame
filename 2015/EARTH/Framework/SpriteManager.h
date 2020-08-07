#pragma once
/***************************************************************************
	精灵节点管理类，将精灵用数据容器串起来
***************************************************************************/
#define MAX_SPRITES	1000
#include "Sprite.h"
#include "AnimationSprite.h"
#include "ResourceManager.h"
class CSpriteManager
{
public:
	CSpriteManager(void);
	CSpriteManager(CResourceManager *pResManager);					//传入一个ResourceManager对象的指针来构造SpriteManager
	virtual ~CSpriteManager(void);
public:
	//CSprite* CreateSprite(HDC hdcSprite,HBITMAP texture,int x = 0,int y = 0);		//创建精灵节点
	CSprite* CreateSprite(const TCHAR *pszResourceName,int x = 0,int y = 0,ResourceType rt = RES_BMP);		//创建精灵节点
//	CAnimationSprite* CreateAnimationSprite(HDC hdcSprite,HBITMAP texture,int nFrames,float nFps,int x,int y,int w,int h,int tx=0,int ty=0);//创建动画精灵节点

	CAnimationSprite* CreateAnimationSprite(const TCHAR *pszResourceName,int nFrames,float nFps,int x,int y,int ws = 1,int hs = 1,int tx = 0,int ty = 0,ResourceType rt = RES_BMP);//创建动画精灵节点


	void DeleteSprite(CSprite *pSprite);								//删除精灵节点				
	void ReZOrder(CSprite *pSprite);										//根据Z-Order重排次节点
	void Render(HDC hdcDest);														//渲染

	void Update(float fDeltaTime);
protected:
	CResourceManager *pResManager;													//资源管理对象			
	void InsertSprite(CSprite *pSprite);								//插入节点到链表
	CSprite	*pSprites[MAX_SPRITES];
	int nZOrder;	//Z-Order
	int nSize;
};

