#include"NSprite.h"

CNSprite::CNSprite(ID2D1HwndRenderTarget 		*pRenderTarget,													//RenderTarget										
	ID2D1Bitmap					*pTexture,														//纹理
	D2D1_POINT_2F				&vPos, 															//位置向量
	int							w,																//精灵宽度
	int							h,																//精灵高度
	int							tx ,															//纹理x
	int							ty ,															//纹理y
	D2D1_POINT_2F				vHotSpot,										//热点
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

	//增加了包围盒的偏移量
	rtBoundingBox.left = fMinX + BoxDeviant.left;
	rtBoundingBox.top = fMinY + BoxDeviant.top;
	rtBoundingBox.right = fMaxX-(width - BoxDeviant.right);
	rtBoundingBox.bottom = fMaxY - (height -BoxDeviant.bottom);
}