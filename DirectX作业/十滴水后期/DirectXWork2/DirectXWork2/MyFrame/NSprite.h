#pragma  once

#include"../OldFrame/Sprite.h"

class CNSprite :public CSprite
{
public:
	CNSprite(ID2D1HwndRenderTarget 		*pRenderTarget,													//RenderTarget										
		ID2D1Bitmap					*pTexture,														//纹理
		D2D1_POINT_2F				&vPos, 															//位置向量
		int							w,																//精灵宽度
		int							h,																//精灵高度
		int							tx = 0,															//纹理x
		int							ty = 0,															//纹理y
		D2D1_POINT_2F				vHotSpot = Point2F(0.0f, 0.0f),										//热点
		wstring						wsName = TEXT("")
		);
	virtual ~CNSprite(void);				//析构

	friend class CSpritesManager;
private:
	RECT BoxDeviant;//包围盒的偏移值
public:
	void SetBoxDeviant(RECT);//设置包围盒的偏移值
	RECT GetBoxDeviant();//返回包围盒的偏移值
	void ComputerBoundingBox();
};