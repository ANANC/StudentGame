#pragma  once

#include"..\OldFrame\AnimationSprite.h"

class CNAnimationSprite : public CAnimationSprite
{
public:
	CNAnimationSprite(ID2D1HwndRenderTarget	*pRenderTarget,  //带参构造函数
		ID2D1Bitmap				*pTexture,
		D2D1_POINT_2F			&vPos,
		int						nFrames,
		int						nFps,
		int						width,
		int						height,
		int						tx = 0,
		int						ty = 0,
		D2D1_POINT_2F			vHotSpot = D2D1::Point2F(0, 0),
		wstring					wsName = TEXT("")
		);


	virtual ~CNAnimationSprite();

	friend class CSpritesManager;
};