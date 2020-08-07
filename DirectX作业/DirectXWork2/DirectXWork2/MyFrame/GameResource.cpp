#include"GameResource.h"

CNSpritesManager *CNSpritesManager::instance = NULL;
CResourcesPool *CResourcesPool::instance = NULL;

GameResource::GameResource()
{
	CResourcesPool *pResPool = NULL;
	pResPool = CResourcesPool::GetInstance();
	ID2D1Bitmap *pBitmap = NULL;
	pResPool->AddTexture(TEXT("Water"), TEXT(".\\ˮ��.png"), &pBitmap);
	pResPool->AddTexture(TEXT("Background"), TEXT(".\\����.jpg"), &pBitmap);
}

GameResource::~GameResource()
{
}