#include"GameResource.h"

CNSpritesManager *CNSpritesManager::instance = NULL;
CResourcesPool *CResourcesPool::instance = NULL;

GameResource::GameResource()
{
	CResourcesPool *pResPool = NULL;
	pResPool = CResourcesPool::GetInstance();
	ID2D1Bitmap *pBitmap = NULL;
	pResPool->AddTexture(TEXT("Water"), TEXT(".\\resource\\ÀÆµŒ◊¥Ã¨.png"), &pBitmap);
	pResPool->AddTexture(TEXT("Background"), TEXT(".\\resource\\±≥æ∞.bmp"), &pBitmap);
	pResPool->AddTexture(TEXT("Number"), TEXT(".\\resource\\¥Û ˝◊÷.png"), &pBitmap);
	pResPool->AddTexture(TEXT("fail"), TEXT(".\\resource\\fail.png"), &pBitmap);
	pResPool->AddTexture(TEXT("win"), TEXT(".\\resource\\win.png"), &pBitmap);
	pResPool->AddTexture(TEXT("cursor"), TEXT(".\\resource\\÷∏’Î2.png"), &pBitmap);
}

GameResource::~GameResource()
{
}