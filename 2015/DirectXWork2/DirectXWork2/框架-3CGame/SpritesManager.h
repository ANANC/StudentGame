#pragma once

/***************************************************************************
	精灵节点管理类，将精灵用链表串起来
***************************************************************************/
#include "sprite.h"
#include "ResourcesPool.h"
#include "AnimationSprite.h"
#include <list>
#include <vector>
#include <string>
using namespace std;

class CSpritesManager
{
private:
	CSpritesManager()
	{
		pRenderTarget = NULL;//为什么要为空
	}
	CSpritesManager(const CSpritesManager&){}
	CSpritesManager &operator = (const CSpritesManager&){}
	static CSpritesManager *instance;//使用单例模式

public:
	static CSpritesManager *GetInstance()
	{
		if (!instance)
		{
			instance = new CSpritesManager();
		}
		return instance;
	}
	virtual ~CSpritesManager(void);
	
	
public:
	void SetRenderTarget(ID2D1HwndRenderTarget *pRenderTarget);

	/*创建精灵*/
	CSprite * CreateSprite	(	const wstring		sResourceName,//精灵纹理图片名字
								//ResourceType		rt,//图片类型
								D2D1_POINT_2F		&vPos,//精灵位置
								int					w=0,//宽度
								int					h=0,//高度
								int					tx = 0,//纹理的x坐标
								int					ty = 0,//纹理的y坐标
								D2D1_POINT_2F		vHotSpot=D2D1::Point2F(0,0)//热点
								);		//创建精灵节点

	/*创建动画精灵*/
	CAnimationSprite * CreateAnimationSprite   (	const wstring   sResourceName,//精灵纹理图片名字
													//ResourceType	rt,//图片类型
													int				nFrames,///动画帧数
													float			nFps,//动画帧频
													D2D1_POINT_2F	&vPos,//精灵位置
													int				w,//宽度
													int				h,//高度
													int				tx = 0,//纹理的x坐标
													int				ty = 0,//纹理的y坐标
													D2D1_POINT_2F   vHotSpot=D2D1::Point2F(0,0)//热点
													);//创建动画精灵节点
	void DeleteSprite(CSprite *pSprite);	//删除精灵节点				
	void Render();									//渲染	
	void Release();							//清理指针
	void Update(float fDeltaTime);
	
	/*克隆*/
	CSprite *Clone(CSprite *pSprite);
	CAnimationSprite *Clone(CAnimationSprite *pAniSprite);
protected:
	bool GetTextureFromResource(const wstring		sResourceName,
								//ResourceType		rt,
								ID2D1Bitmap			**ppTexture,
								int					w,
								int					h,
								int					&nWidth,
								int					&nHeight);

		
	ID2D1HwndRenderTarget       *pRenderTarget; 
	list<CSprite*>				spriteList;
	vector<CSprite*>			toBeDeleted;
	
};


