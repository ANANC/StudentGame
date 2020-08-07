#pragma once

/***************************************************************************
	����ڵ�����࣬����������������
***************************************************************************/
#include "sprite.h"
#include "ResourcesPool.h"
#include "AnimationSprite.h"
#include <list>
#include <vector>
#include <string>
using namespace std;

class CSpritesManager
{
private:
	CSpritesManager()
	{
		pRenderTarget = NULL;//ΪʲôҪΪ��
	}
	CSpritesManager(const CSpritesManager&){}
	CSpritesManager &operator = (const CSpritesManager&){}
	static CSpritesManager *instance;//ʹ�õ���ģʽ

public:
	static CSpritesManager *GetInstance()
	{
		if (!instance)
		{
			instance = new CSpritesManager();
		}
		return instance;
	}
	virtual ~CSpritesManager(void);
	
	
public:
	void SetRenderTarget(ID2D1HwndRenderTarget *pRenderTarget);

	/*��������*/
	CSprite * CreateSprite	(	const wstring		sResourceName,//��������ͼƬ����
								//ResourceType		rt,//ͼƬ����
								D2D1_POINT_2F		&vPos,//����λ��
								int					w=0,//���
								int					h=0,//�߶�
								int					tx = 0,//�����x����
								int					ty = 0,//�����y����
								D2D1_POINT_2F		vHotSpot=D2D1::Point2F(0,0)//�ȵ�
								);		//��������ڵ�

	/*������������*/
	CAnimationSprite * CreateAnimationSprite   (	const wstring   sResourceName,//��������ͼƬ����
													//ResourceType	rt,//ͼƬ����
													int				nFrames,///����֡��
													float			nFps,//����֡Ƶ
													D2D1_POINT_2F	&vPos,//����λ��
													int				w,//���
													int				h,//�߶�
													int				tx = 0,//�����x����
													int				ty = 0,//�����y����
													D2D1_POINT_2F   vHotSpot=D2D1::Point2F(0,0)//�ȵ�
													);//������������ڵ�
	void DeleteSprite(CSprite *pSprite);	//ɾ������ڵ�				
	void Render();									//��Ⱦ	
	void Release();							//����ָ��
	void Update(float fDeltaTime);
	
	/*��¡*/
	CSprite *Clone(CSprite *pSprite);
	CAnimationSprite *Clone(CAnimationSprite *pAniSprite);
protected:
	bool GetTextureFromResource(const wstring		sResourceName,
								//ResourceType		rt,
								ID2D1Bitmap			**ppTexture,
								int					w,
								int					h,
								int					&nWidth,
								int					&nHeight);

		
	ID2D1HwndRenderTarget       *pRenderTarget; 
	list<CSprite*>				spriteList;
	vector<CSprite*>			toBeDeleted;
	
};


