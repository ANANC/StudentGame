#include"NSpriteManager.h"

CNSprite *CNSpritesManager::CreateNSprite(const wstring		sResourceName,
	//ResourceType		rt,
	D2D1_POINT_2F		&vPos,
	int					w ,
	int					h ,
	int					tx ,
	int					ty ,
	D2D1_POINT_2F		vHotSpot
	)
{
	ID2D1Bitmap *pTexture;
	int nWidth;
	int nHeight;
	GetTextureFromResource(sResourceName, &pTexture, w, h, nWidth, nHeight);
	CNSprite *pNSprite = new CNSprite(pRenderTarget, pTexture, vPos, nWidth, nHeight, tx, ty, vHotSpot);
	spriteList.push_back(pNSprite);
	return pNSprite;
}

CNSpritesManager::~CNSpritesManager()
{
}