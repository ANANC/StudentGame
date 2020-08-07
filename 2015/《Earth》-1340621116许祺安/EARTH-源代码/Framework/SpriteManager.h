#pragma once
/***************************************************************************
	����ڵ�����࣬����������������������
***************************************************************************/
#define MAX_SPRITES	1000
#include "Sprite.h"
#include "AnimationSprite.h"
#include "ResourceManager.h"
class CSpriteManager
{
public:
	CSpriteManager(void);
	CSpriteManager(CResourceManager *pResManager);					//����һ��ResourceManager�����ָ��������SpriteManager
	virtual ~CSpriteManager(void);
public:
	//CSprite* CreateSprite(HDC hdcSprite,HBITMAP texture,int x = 0,int y = 0);		//��������ڵ�
	CSprite* CreateSprite(const TCHAR *pszResourceName,int x = 0,int y = 0,ResourceType rt = RES_BMP);		//��������ڵ�
//	CAnimationSprite* CreateAnimationSprite(HDC hdcSprite,HBITMAP texture,int nFrames,float nFps,int x,int y,int w,int h,int tx=0,int ty=0);//������������ڵ�

	CAnimationSprite* CreateAnimationSprite(const TCHAR *pszResourceName,int nFrames,float nFps,int x,int y,int ws = 1,int hs = 1,int tx = 0,int ty = 0,ResourceType rt = RES_BMP);//������������ڵ�


	void DeleteSprite(CSprite *pSprite);								//ɾ������ڵ�				
	void ReZOrder(CSprite *pSprite);										//����Z-Order���Ŵνڵ�
	void Render(HDC hdcDest);														//��Ⱦ

	void Update(float fDeltaTime);
protected:
	CResourceManager *pResManager;													//��Դ�������			
	void InsertSprite(CSprite *pSprite);								//����ڵ㵽����
	CSprite	*pSprites[MAX_SPRITES];
	int nZOrder;	//Z-Order
	int nSize;
};

