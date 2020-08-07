#include "SpriteManager.h"

CSpriteManager::CSpriteManager(void)
{
	nZOrder = 0;
	nSize = 0;

}

CSpriteManager::~CSpriteManager(void)
{
	for(int i=0;i<nSize;++i)
	{
		delete pSprites[i];
	}
}
CSpriteManager::CSpriteManager(CResourceManager *pResManager)
{
	nZOrder = 0;
	nSize = 0;
	this->pResManager = pResManager;
}
CSprite *CSpriteManager::CreateSprite(const TCHAR *pszResourceName,int x,int y,ResourceType rt)
{

	int nWidth;
	int nHeight;

	PResDesc pResDesc = pResManager->GetResource(rt,pszResourceName);

	BITMAP bm;
	//GetObject(texture,sizeof(bm),&bm); 
	

	GetObject((HBITMAP)pResDesc->dwHandle2,sizeof(bm),&bm); 


	nWidth = bm.bmWidth;
	nHeight = bm.bmHeight; 
	//CSprite *pSprite = new CSprite(hdcSprite,x,y,nWidth,nHeight);
	CSprite *pSprite = new CSprite((HDC)pResDesc->dwHandle1,x,y,nWidth,nHeight);

	//pSprite->SetPos(x,y);




	pSprite->SetZOrder(nZOrder++);
	InsertSprite(pSprite);

	return pSprite;
}

CAnimationSprite* CSpriteManager::CreateAnimationSprite(const TCHAR *pszResourceName,int nFrames,float nFps,int x,int y,int ws,int hs,int tx,int ty,ResourceType rt)
{


	BITMAP bm;
	//GetObject(texture,sizeof(bm),&bm); 
	PResDesc pResDesc = pResManager->GetResource(rt,pszResourceName);

	GetObject((HBITMAP)pResDesc->dwHandle2,sizeof(bm),&bm); 

	//CAnimationSprite *pAnimationSprite = new CAnimationSprite(hdcSprite,nFrames,nFps,x,y,w,h,tx,ty,bm.bmWidth,bm.bmHeight);
	
	int w = bm.bmWidth / ws;
	int h = bm.bmHeight / hs;

	CAnimationSprite *pAnimationSprite = new CAnimationSprite((HDC)pResDesc->dwHandle1, nFrames, nFps, x, y, w, h, tx, ty, bm.bmWidth, bm.bmHeight);


	//pAnimationSprite->SetPos(x,y);
	pAnimationSprite->SetZOrder(nZOrder++);
	InsertSprite(pAnimationSprite);

	return pAnimationSprite;
}

void CSpriteManager::DeleteSprite(CSprite *pSprite)
{
	int pos = -1;
	for(int i=0;i<nSize;++i)
	{
		if (pSprites[i] == pSprite)
		{
			pos = i;
			break;
		}
	}
	if (pos <0)
	{
		return;
	}
	delete pSprites[pos];
	for(int j=pos;j<nSize - 1;++j)
	{
		pSprites[j] = pSprites[j+1];
	}
	--nSize;
}
void CSpriteManager::InsertSprite(CSprite *pInsert)
{
	if (pInsert == NULL)
	{
		return;
	}
	int pos = nSize;
	for(int i=0;i<nSize;++i)
	{
		if (pSprites[i]->GetZOrder() > pInsert->GetZOrder())
		{
			pos = i;
			break;
		}
	}

	if (pos >= 0)
	{
		for(int j=nSize;j>pos;--j)
		{
			pSprites[j] = pSprites[j-1];
		}
		pSprites[pos] = pInsert;
		++nSize;
	}

}
void CSpriteManager::Render(HDC hdcDest)
{
	for(int i=0;i<nSize;++i)
	{
		if (pSprites[i]->GetVisible())
		{
			pSprites[i]->Draw(hdcDest);
		}
	}

}
void CSpriteManager::ReZOrder(CSprite *pSprite)
{

}


void CSpriteManager::Update(float fDeltaTime)
{
	for(int i=0;i<nSize;++i)
	{
		pSprites[i]->Update(fDeltaTime);
	}
}