#pragma  once

#include"../OldFrame/Sprite.h"

class CNSprite :public CSprite
{
public:
	CNSprite(ID2D1HwndRenderTarget 		*pRenderTarget,													//RenderTarget										
		ID2D1Bitmap					*pTexture,														//����
		D2D1_POINT_2F				&vPos, 															//λ������
		int							w,																//������
		int							h,																//����߶�
		int							tx = 0,															//����x
		int							ty = 0,															//����y
		D2D1_POINT_2F				vHotSpot = Point2F(0.0f, 0.0f),										//�ȵ�
		wstring						wsName = TEXT("")
		);
	virtual ~CNSprite(void);				//����

	friend class CSpritesManager;
private:
	RECT BoxDeviant;//��Χ�е�ƫ��ֵ
public:
	void SetBoxDeviant(RECT);//���ð�Χ�е�ƫ��ֵ
	RECT GetBoxDeviant();//���ذ�Χ�е�ƫ��ֵ
	void ComputerBoundingBox();
};