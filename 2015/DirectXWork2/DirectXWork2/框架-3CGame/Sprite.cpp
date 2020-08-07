
#include "Sprite.h"



CSprite::~CSprite(void)
{
	Release();
}
CSprite::CSprite(ID2D1HwndRenderTarget 	*pRenderTarget,													//RenderTarget													
	ID2D1Bitmap					*pTexture,																//纹理
	D2D1_POINT_2F				&vPos, 																	//位置向量
	int							w,																		//精灵宽度
	int							h,																		//精灵高度
	int							tx,																		//纹理x
	int							ty,																		//纹理y
	D2D1_POINT_2F				vHotSpot,																//热点
	wstring						wsName
	)
{
	assert(pRenderTarget != NULL);
	assert(pTexture != NULL);
	this->wsName = wsName;
	this->pTexture = pTexture;
	this->pRenderTarget = pRenderTarget;
	this->width = w;
	this->height = h;
	this->bStretch = true;

	D2D1_SIZE_F size=pTexture->GetSize();

	this->nTexWidth =  size.width;
	this->nTexHeight  = size.height;

	ptBoundingBox[0].x = 0;
	ptBoundingBox[0].y = 0;
	ptBoundingBox[1].x = 0;
	ptBoundingBox[1].y = h;
	ptBoundingBox[2].x = w;
	ptBoundingBox[2].y = 0;
	ptBoundingBox[3].x = w;
	ptBoundingBox[3].y = h;


	this->fRotationAngle = 0;
	this->vPos = vPos;
	this->tx = tx;
	this->ty = ty;
	this->vHotSpot = vHotSpot;
	this->bVisible = true;
	this->bEnabled = true;
	this->bTexPosChanged = false;

	pRenderTarget->CreateBitmap(D2D1::SizeU(width,height),D2D1::BitmapProperties(pTexture->GetPixelFormat()),&pSpriteBitmap);
	assert(pSpriteBitmap != NULL);
	pSpriteBitmap->CopyFromBitmap(&D2D1::Point2U(0,0),pTexture,&D2D1::RectU(tx,ty,tx + width,ty + height));
	pRenderTarget->CreateBitmapBrush(pSpriteBitmap,&pSpriteBrush);

	matWorld = Matrix3x2F::Identity();
	matScale = Matrix3x2F::Identity();
	matRotation = Matrix3x2F::Identity();
	matTranslation = Matrix3x2F::Translation(vPos.x - vHotSpot.x ,vPos.y - vHotSpot.y);
	matWorld = matScale * matRotation * matTranslation;
	this->ComputerBoundingBox();
	color = D2D1::ColorF(0xff,1.0f);
	pRenderTarget->CreateSolidColorBrush(color,&pBoundingBoxBrush);
	bDrawBoundingBox = false;//是否画包围盒

	rtBoundingBox.left = vPos.x;
	rtBoundingBox.top = vPos.y;
	rtBoundingBox.right = vPos.x + width;
	rtBoundingBox.bottom = vPos.y + height;

}

void CSprite::Render()
{
	if (!pRenderTarget)
	{
		return;
	}

	if (!bVisible)//可见性
		return;

	if (bStretch)
	{
		//此处代码填写完整
		matWorld = matScale * matRotation * matTranslation;
		pRenderTarget->SetTransform(matWorld);
		pRenderTarget->DrawBitmap(pSpriteBitmap);
		if (bDrawBoundingBox)
		{
			pRenderTarget->SetTransform(Matrix3x2F::Identity());
			pRenderTarget->DrawRectangle(rtBoundingBox,pBoundingBoxBrush,2.0f);
		}
	}
	else
	{
		Render(destRect,bStretch);
	}
}

void CSprite::Render(D2D1_POINT_2F &vPos)
{
	if (!pRenderTarget)
	{
		return;
	}

	if (!bVisible)//可见性
		return;

	this->vPos = vPos;
	matTranslation = Matrix3x2F::Translation(vPos.x - vHotSpot.x ,vPos.y - vHotSpot.y );
	matWorld =  matScale * matRotation * matTranslation;
	this->ComputerBoundingBox();
	Render();
}
void CSprite::Render(D2D1_RECT_F &destRect,bool bStretch,D2D1_EXTEND_MODE extendModeX, D2D1_EXTEND_MODE extendModeY)
{
	if (!pRenderTarget)
	{
		return;
	}
	
	if (!bVisible)//可见性
		return;

	if (bStretch)
	{
		fsx = (destRect.right - destRect.left) / static_cast<float>(width);
		fsy = (destRect.bottom - destRect.top ) / static_cast<float>(height);
		vPos.x = destRect.left;
		vPos.y = destRect.top;
		matTranslation = Matrix3x2F::Translation(vPos.x - vHotSpot.x ,vPos.y - vHotSpot.y );
		matScale = D2D1::Matrix3x2F::Scale(fsx,fsy,D2D1::Point2F(vHotSpot.x,vHotSpot.y));
		matWorld =  matScale * matRotation * matTranslation;
		this->ComputerBoundingBox();
		Render();
	}
	else
	{
		HRESULT hr = S_OK;
		

		if (this->bTexPosChanged)
		{
			SafeRelease(&pSpriteBrush);
			hr = pRenderTarget->CreateBitmapBrush(pSpriteBitmap,&pSpriteBrush);
			this->bTexPosChanged = false;
		}
		pSpriteBrush->SetExtendModeX(extendModeX);
		pSpriteBrush->SetExtendModeY(extendModeY);
		if (SUCCEEDED(hr))
		{
			matWorld = D2D1::Matrix3x2F::Identity();
			pRenderTarget->SetTransform(matWorld);//D2D1::Matrix3x2F::Identity());
			pRenderTarget->FillRectangle(&destRect,pSpriteBrush);
			if (bDrawBoundingBox)
			{
				pRenderTarget->SetTransform(Matrix3x2F::Identity());
				pRenderTarget->DrawRectangle(rtBoundingBox,pBoundingBoxBrush,2.0f);
			}		
		}
	}


}
bool CSprite::CollideWith(RECT &rect)
{
	RECT rtIntersect;
	RECT *rtSprite = reinterpret_cast<RECT*>(&rtBoundingBox);
	return IntersectRect(&rtIntersect,rtSprite,&rect);
}
bool CSprite::CollideWith(CSprite &sprite) 
{
	RECT rtIntersect;

	const RECT *rtSprite = reinterpret_cast<const RECT*>(sprite.GetBoundingBox());
	//return IntersectRect(&rtIntersect,rtSprite,&rtIntersect);//两个rtIntersect
	RECT *rtSpriteNew = reinterpret_cast<RECT*>(&rtBoundingBox);
	return IntersectRect(&rtIntersect, rtSprite, rtSpriteNew);
}

D2D1_POINT_2F &CSprite::GetHotSpot() 
{
	return this->vHotSpot;
}

const D2D1_RECT_F* CSprite::GetBoundingBox()
{
	return &rtBoundingBox;																	;
}																	

void CSprite::SetTexture(ID2D1Bitmap *tex)
{
	this->pTexture = tex;

}
const ID2D1Bitmap *CSprite::GetTexture()
{
	return pTexture;
}
const ID2D1Bitmap *CSprite::GetBitmap()
{
	return pSpriteBitmap;
}
void CSprite::SetHotSpot(D2D1_POINT_2F &vHotSpot)
{
	//请将此处代码填写完整
	this->vHotSpot.x = vHotSpot.x;
	this->vHotSpot.y = vHotSpot.y;
	matTranslation = Matrix3x2F::Translation(vPos.x - vHotSpot.x, vPos.y - vHotSpot.y);
	this->ComputerBoundingBox();

}

void CSprite::SetTransform(Matrix3x2F &matTrans)
{
	this->matWorld = matTrans;
	this->ComputerBoundingBox();

}
const Matrix3x2F *CSprite::GetTransform()
{
	return &matWorld;
}

int CSprite::GetWidth()
{
	return width;
}
int CSprite::GetHeight()
{
	return height;
}

void CSprite::SetPos(D2D1_POINT_2F &vPos)
{
	//请将此处代码填写完整
	this->vPos.x = vPos.x;
	this->vPos.y = vPos.y;
	matTranslation = Matrix3x2F::Translation(vPos.x - vHotSpot.x, vPos.y - vHotSpot.y);
	this->ComputerBoundingBox();
}
D2D1_POINT_2F &CSprite::GetPos()
{
	return vPos;
}
void CSprite::SetDestRect(float x1,float y1,float w,float h,bool bStretch) 
{

	fsx = (float)w / (float)width;
	fsy = (float)h / (float)height;
	vPos.x = x1  ;
	vPos.y = y1 ;
	matTranslation = Matrix3x2F::Translation(vPos.x - vHotSpot.x ,vPos.y - vHotSpot.y );
	SetScaleFactor(fsx,fsy);
	this->bStretch = bStretch;
	destRect.left = x1;
	destRect.top = y1;
	destRect.right = x1+w;
	destRect.bottom = y1 + h;
	if(!bStretch)
	{
		rtBoundingBox  = destRect;
	}

}
void CSprite::SetTexPos(int x,int y)
{
	assert(pSpriteBitmap != NULL);
	//请将此处代码填写完整
	D2D1_SIZE_F size = pTexture->GetSize();
	if (x >= size.width || x < 0 || y >= size.height || y < 0)
		return;
	pSpriteBitmap->CopyFromBitmap(&D2D1::Point2U(0, 0), pTexture, &D2D1::RectU(x, y, x + width, y + height));
	this->tx = x;
	this->ty = y;
}
void CSprite::Release()
{
	SafeRelease(&pSpriteBitmap);
	SafeRelease(&pSpriteBrush);
	SafeRelease(&pBoundingBoxBrush);
}



void CSprite::SetVisible(bool bVal)
{
	this->bVisible = bVal;
}
bool CSprite::IsVisible()
{
	return bVisible;
}

void CSprite::SetRotationAngle(float fAngle)															//设置旋转角度					
{
	//请将此处代码填写完整
	this->fRotationAngle = fAngle;
	matRotation = D2D1::Matrix3x2F::Rotation(fRotationAngle, D2D1::Point2F(vHotSpot.x,vHotSpot.y));
	ComputerBoundingBox();
}
float CSprite::GetRotationAngle()
{
	return fRotationAngle;
}
void CSprite::SetScaleFactor(float sx,float sy)
{
	//请将此处代码填写完整
	this->fsx = sx;
	this->fsy = sy;
	matScale = D2D1::Matrix3x2F::Scale(fsx, fsy, D2D1::Point2F(vHotSpot.x, vHotSpot.y));
	ComputerBoundingBox();
}

const wstring &CSprite::GetSpriteName()
{
	return wsName;
}

void CSprite::ComputerBoundingBox()
{
	
	//请将此处代码填写完整
	matWorld = matScale * matRotation * matTranslation;
	ptBoundingBox[0].x = 0;
	ptBoundingBox[0].y = 0;
	ptBoundingBox[1].x = 0;
	ptBoundingBox[1].y = height;
	ptBoundingBox[2].x = width;
	ptBoundingBox[2].y = 0;
	ptBoundingBox[3].x = width;
	ptBoundingBox[3].y = height;

	/*包围盒矩形*/
	for (int i = 0; i < 4; i++)
		ptBoundingBox[i] = matWorld.TransformPoint(ptBoundingBox[i]);


	/*精灵矩形*/
	int MaxX = ptBoundingBox[2].x, MaxY = ptBoundingBox[3].y;
	int MixX = ptBoundingBox[0].x, MixY = ptBoundingBox[1].y;
	for (int i = 0; i<4; i++)
	{
		if (ptBoundingBox[i].x >MaxX)
			MaxX = ptBoundingBox[i].x;
		if (ptBoundingBox[i].y >MaxY)
			MaxY = ptBoundingBox[i].y;
		if (ptBoundingBox[i].x <MixX)
			MixX = ptBoundingBox[i].x;
		if (ptBoundingBox[i].y <MixY)
			MixY = ptBoundingBox[i].y;
	}

	rtBoundingBox.left = MixX;
	rtBoundingBox.top = MixY;
	rtBoundingBox.right = MaxX;
	rtBoundingBox.bottom = MaxY;
}

bool CSprite::IsSelected(int x,int y)
{
	bool bRet = false;
	if (x>=rtBoundingBox.left && x <= rtBoundingBox.right  && y >= rtBoundingBox.top && y <= rtBoundingBox.bottom)
	{
		return true;
	}
	return bRet;

}

CSprite *CSprite::Clone()
{
	CSprite *pSprite = new CSprite(pRenderTarget,pTexture,vPos,width,height,tx,ty,vHotSpot,wsName);
	return pSprite;
}
void CSprite::SetEnabled(bool bVal)
{
	this->bEnabled = bVal;

}
bool CSprite::IsEnabled()
{
	return bEnabled;
}


