#include "SpritesManager.h"


CSpritesManager::~CSpritesManager(void)
{
	//��������д�������ͷ�������Դ
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


	CResourcesPool * rp = CResourcesPool::GetInstance();//�����Դ��
	ResDesc *pResDesc = rp->GetResource(sResourceName);//����Դ�ػ����Դ
	if (!pResDesc)
	{
		return false;//�������Դ���Ҳ������ͷ���ʧ��
	}

	nWidth = w;
	nHeight = h;

	*ppTexture =pResDesc->pTexture;
	if (w == 0 || h == 0)
	{//��ȡ����ͼƬ
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
	
	//���˴�������д����������������Ӿ���
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
	
	//���˴�������д����������������Ӷ�������
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
	//��������֪ͨÿ��������Ⱦ����
	for (list<CSprite*>::iterator ite = spriteList.begin(); ite != spriteList.end(); ite++)
	{
		(*ite)->Render();
	}
}

void CSpritesManager::Update(float fDeltaTime)
{
	//��������֪ͨÿ�������������
	for (list<CSprite*>::iterator ite = spriteList.begin(); ite != spriteList.end(); ite++)
	{
		(*ite)->Update(fDeltaTime);
	}
}

void CSpritesManager::Release()
{
	for(list<CSprite*>::iterator ite = spriteList.begin();ite != spriteList.end();ite++)
	{
		(*ite)->Release();//�������ָ��
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