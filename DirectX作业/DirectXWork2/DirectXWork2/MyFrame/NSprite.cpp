#include"NSprite.h"

CNSprite::CNSprite(ID2D1HwndRenderTarget 		*pRenderTarget,													//RenderTarget										
	ID2D1Bitmap					*pTexture,														//����
	D2D1_POINT_2F				&vPos, 															//λ������
	int							w,																//������
	int							h,																//����߶�
	int							tx ,															//����x
	int							ty ,															//����y
	D2D1_POINT_2F				vHotSpot,										//�ȵ�
	wstring						wsName
	) :CSprite(pRenderTarget, pTexture, vPos, w, h, tx, ty, vHotSpot, wsName)
{
	BoxDeviant = {0};
}

CNSprite::~CNSprite()
{
}

void CNSprite::SetBoxDeviant(RECT p)
{
	BoxDeviant = p;
	ComputerBoundingBox();
}

RECT CNSprite::GetBoxDeviant()
{
	return BoxDeviant;
}

void CNSprite::ComputerBoundingBox()
{
	D2D1_POINT_2F	ptTmp[4];
	for (int i = 0; i<4; ++i)
	{
		ptTmp[i] = matWorld.TransformPoint(ptBoundingBox[i]);
	}
	float fMinX = ptTmp[0].x;
	float fMaxX = ptTmp[0].x;
	float fMinY = ptTmp[0].y;
	float fMaxY = ptTmp[0].y;
	for (int i = 1; i<4; ++i)
	{
		if (fMinX > ptTmp[i].x)
		{
			fMinX = ptTmp[i].x;
		}
		if (fMaxX < ptTmp[i].x)
		{
			fMaxX = ptTmp[i].x;
		}

		if (fMinY > ptTmp[i].y)
		{
			fMinY = ptTmp[i].y;
		}
		if (fMaxY < ptTmp[i].y)
		{
			fMaxY = ptTmp[i].y;
		}

	}

	//�����˰�Χ�е�ƫ����
	rtBoundingBox.left = fMinX + BoxDeviant.left;
	rtBoundingBox.top = fMinY + BoxDeviant.top;
	rtBoundingBox.right = fMaxX-(width - BoxDeviant.right);
	rtBoundingBox.bottom = fMaxY - (height -BoxDeviant.bottom);
}