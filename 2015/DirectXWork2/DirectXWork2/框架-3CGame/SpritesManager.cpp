#include "SpritesManager.h"


CSpritesManager::~CSpritesManager(void)
{
	//这里请填写完整，释放所有资源
	Release();
	vector<CSprite *>::const_iterator pos;
	for (pos = toBeDeleted.begin(); pos != toBeDeleted.end(); ++pos)
	{
		delete *pos;
	}
}

void CSpritesManager::SetRenderTarget(ID2D1HwndRenderTarget *pRenderTarget)
{
	this->pRenderTarget = pRenderTarget;
}

bool CSpritesManager::GetTextureFromResource(const wstring		sResourceName,
											//ResourceType		rt,
											ID2D1Bitmap			**ppTexture,
											int					w,
											int					h,
											int					&nWidth,
											int					&nHeight)
{	


	CResourcesPool * rp = CResourcesPool::GetInstance();//获得资源池
	ResDesc *pResDesc = rp->GetResource(sResourceName);//从资源池获得资源
	if (!pResDesc)
	{
		return false;//如果在资源池找不到，就返回失败
	}

	nWidth = w;
	nHeight = h;

	*ppTexture =pResDesc->pTexture;
	if (w == 0 || h == 0)
	{//获取整张图片
		D2D1_SIZE_F  size = (*ppTexture)->GetSize();

		nWidth = size.width;
		nHeight = size.height;
	}
	
	return true;
}
CSprite * CSpritesManager::CreateSprite(	const wstring		sResourceName,
											//	ResourceType		rt,
											D2D1_POINT_2F		&vPos,
											int					w,
											int					h,
											int					tx,
											int					ty,
											D2D1_POINT_2F		vHotSpot
								)
{
	
	//将此处代码填写完整，向容器里添加精灵
	ID2D1Bitmap *pBitmap;
	GetTextureFromResource(sResourceName, &pBitmap, 0, 0, w, h);
	CSprite *pSprite = new CSprite(pRenderTarget, pBitmap, vPos, w, h, tx, ty, vHotSpot);
	spriteList.push_back(pSprite);
	return pSprite;
	
}

CAnimationSprite * CSpritesManager::CreateAnimationSprite  (	const wstring		sResourceName,
																//ResourceType		rt,
																int					nFrames,
																float				nFps,
																D2D1_POINT_2F		&vPos,
																int					w,
																int					h,
																int					tx,
																int					ty,
																D2D1_POINT_2F		vHotSpot)
{
	
	//将此处代码填写完整，向容器里添加动画精灵
	ID2D1Bitmap *pBitmap;
	int TexWidth,TexHeight;
	GetTextureFromResource(sResourceName, &pBitmap, w, h,TexWidth,TexHeight);
	CAnimationSprite *pAnimationSprite = new CAnimationSprite(pRenderTarget, pBitmap, vPos, nFrames, nFps, TexWidth, TexHeight, tx, ty, vHotSpot);
	spriteList.push_back(pAnimationSprite);
	
	return pAnimationSprite;
}

void CSpritesManager::DeleteSprite(CSprite *pSprite)
{
	//delete pSprite;
	//spriteList.remove(pSprite);
	pSprite->bEnabled=pSprite->bVisible = false;
	toBeDeleted.push_back(pSprite);
}

void CSpritesManager::Render()
{
	//遍历链表，通知每个精灵渲染自身
	for (list<CSprite*>::iterator ite = spriteList.begin(); ite != spriteList.end(); ite++)
	{
		(*ite)->Render();
	}
}

void CSpritesManager::Update(float fDeltaTime)
{
	//遍历链表，通知每个精灵更新自身
	for (list<CSprite*>::iterator ite = spriteList.begin(); ite != spriteList.end(); ite++)
	{
		(*ite)->Update(fDeltaTime);
	}
}

void CSpritesManager::Release()
{
	for(list<CSprite*>::iterator ite = spriteList.begin();ite != spriteList.end();ite++)
	{
		(*ite)->Release();//清理精灵的指针
	}
}

CSprite *CSpritesManager::Clone(CSprite *pSprite)
{
	CSprite *pSpr = pSprite->Clone();
	spriteList.push_back(pSpr);
	return pSpr;
}
CAnimationSprite *CSpritesManager::Clone(CAnimationSprite *pAniSprite)
{
	CAnimationSprite *pAniSpr = pAniSprite->Clone();
	spriteList.push_back(pAniSpr);
	return pAniSpr;
}