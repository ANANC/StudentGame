#include"GameResource.h"

CNSpritesManager *CNSpritesManager::instance = NULL;
CResourcesPool *CResourcesPool::instance = NULL;

GameResource::GameResource()
{
	CResourcesPool *pResPool = NULL;
	pResPool = CResourcesPool::GetInstance();
	ID2D1Bitmap *pBitmap = NULL;
	pResPool->AddTexture(TEXT("Water"), TEXT(".\\Ë®µÎ.png"), &pBitmap);
	pResPool->AddTexture(TEXT("Background"), TEXT(".\\±³¾°.jpg"), &pBitmap);
}

GameResource::~GameResource()
{
}