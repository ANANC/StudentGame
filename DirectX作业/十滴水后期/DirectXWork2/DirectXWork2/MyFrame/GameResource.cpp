#include"GameResource.h"

CNSpritesManager *CNSpritesManager::instance = NULL;
CResourcesPool *CResourcesPool::instance = NULL;

GameResource::GameResource()
{
	CResourcesPool *pResPool = NULL;
	pResPool = CResourcesPool::GetInstance();
	ID2D1Bitmap *pBitmap = NULL;
	pResPool->AddTexture(TEXT("Water"), TEXT(".\\resource\\ˮ��״̬.png"), &pBitmap);
	pResPool->AddTexture(TEXT("Background"), TEXT(".\\resource\\����.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("Number"), TEXT(".\\resource\\������.png"), &pBitmap);
	pResPool->AddTexture(TEXT("fail"), TEXT(".\\resource\\fail.png"), &pBitmap);
	pResPool->AddTexture(TEXT("win"), TEXT(".\\resource\\win.png"), &pBitmap);
	pResPool->AddTexture(TEXT("cursor"), TEXT(".\\resource\\ָ��2.png"), &pBitmap);
}

GameResource::~GameResource()
{
}