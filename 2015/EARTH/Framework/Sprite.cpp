#include "Sprite.h"

CSprite::CSprite(void)
{
}

CSprite::~CSprite(void)
{
}
CSprite::CSprite(HDC hdcSprite,int x,int y,int w,int h)
{
	this->hdcSprite = hdcSprite;
	this->x = x;
	this->y = y;
	this->nDestWidth = this->width = w;
	this->nDestHeight = this->height = h;
	this->rectSprite.left = x;
	this->rectSprite.top = y;
	this->rectSprite.right = x + w;
	this->rectSprite.bottom = y + h;
	this->fRotationAngle = 0;

	tx = 0;
	ty = 0;
	ptHotSpot.x = 0;
	ptHotSpot.y = 0;
	dwColorKey = GetPixel(hdcSprite,0,0);

	bTransparent = false;
	bVisible = true;
	hdcDest = NULL;

	SpriteBox[0] = { x, y, x + w / 3, y + h / 3 };
	SpriteBox[1] = { x + w / 3, y + h / 3, (x + w / 3)*2, (y + h / 3)*2 };
	SpriteBox[2] = { (x + w / 3) * 2, (y + h / 3) * 2, w,h };
}

bool CSprite::CollideWith(RECT &rect)
{
	RECT rtIntersect;
	return IntersectRect(&rtIntersect,&this->rectSprite,&rect);
}
bool CSprite::CollideWith(CSprite &sprite) 
{
	RECT rtIntersect;
	return IntersectRect(&rtIntersect,&this->rectSprite,sprite.GetSpriteRect());
}


void CSprite::SetTransparent(bool val)
{
	bTransparent = val;
}
bool CSprite::GetTransparent()
{
	return bTransparent;
}
void CSprite::SetVisible(bool val)
{
	bVisible = val;
}
bool CSprite::GetVisible()
{
	return bVisible;
}

void CSprite::Draw()
{
	if (hdcDest == NULL)
	{
		return ;
	}
	if (hdcSprite == NULL )
	{
		return;
	}
	XFORM oldXForm ;								//提供旋转支持
	if (this->fRotationAngle != 0)
	{
		GetWorldTransform(hdcDest,&oldXForm);
		XFORM xForm; 
		SetGraphicsMode(hdcDest, GM_ADVANCED);


		xForm.eM11 = (float)cos(fRotationAngle); 
		xForm.eM12 = (float)sin(fRotationAngle);
		xForm.eM21 = (float)-sin(fRotationAngle); 
		xForm.eM22 = (float)cos(fRotationAngle);
		xForm.eDx  = (float)0.0; 
		xForm.eDy  = (float)0.0; 
	
		
		SetWorldTransform(hdcDest, &xForm); 
	}
	RECT rect = rectSprite;
	DPtoLP(hdcDest, (LPPOINT) &rect, 2); 

	if (bTransparent)
	{
		TransparentBlt(hdcDest,rect.left - ptHotSpot.x ,rect.top - ptHotSpot.y, nDestWidth,nDestHeight,hdcSprite,tx,ty,width,height,dwColorKey);
	}
	else
	{
		if (this->bStretchDraw)
		{
			StretchBlt(hdcDest,rect.left - ptHotSpot.x ,rect.top - ptHotSpot.y,nDestWidth,nDestHeight,hdcSprite,tx,ty,width,height,SRCCOPY);
		}
		else
		{
			BitBlt(hdcDest,rect.left - ptHotSpot.x ,rect.top - ptHotSpot.y,width,height,hdcSprite,tx,ty,SRCCOPY);
		}
	}

	if (this->fRotationAngle != 0)
	{
		SetWorldTransform(hdcDest, &oldXForm); 
	}


}
//void CSprite::Draw(bool bTransparent) 
//{
//
//	this->bTransparent = bTransparent;
//	Draw();
//	
//}
void CSprite::Draw(HDC hdcDest )
{
	this->hdcDest = hdcDest;
	
	Draw();
}
void CSprite::Draw(int x,int y)
{
	this->x = x;
	this->y = y;
	rectSprite.left = x;
	rectSprite.top = y;
	rectSprite.right = x + width;
	rectSprite.bottom = y + height;
	
	Draw();
}

void CSprite::Draw(HDC hdcDest,int x, int y)
{
	this->hdcDest = hdcDest;
	this->x = x;
	this->y = y;
	rectSprite.left = x;
	rectSprite.top = y;
	rectSprite.right = x + width;
	rectSprite.bottom = y + height;
	
	Draw();

}
void CSprite::StretchDraw(HDC hdcDest,int nDestX,int nDestY,int nDestWidth,int nDestHeight)
{
	bStretchDraw = true;
	this->nDestWidth = nDestWidth;
	this->nDestHeight = nDestHeight;
	Draw(hdcDest,nDestX,nDestY);

}
POINT CSprite::GetHotSpot() 
{
	return this->ptHotSpot;
}
DWORD CSprite::GetPixelColor(int x,int y)
{
	return GetPixel(hdcSprite,x,y);
}
const RECT *CSprite::GetSpriteRect()
{
	return &rectSprite;
}
int CSprite::GetZOrder() 
{
	return this->nZOrder;
}
void CSprite::SetColorKey(DWORD dwColorKey) 
{
	this->dwColorKey = dwColorKey;
}
void CSprite::SetDestDC(HDC hdcDest)
{
	this->hdcDest = hdcDest;
}
void CSprite::SetTexture(HDC hdcTexture)
{
	this->hdcSprite = hdcTexture;
}

void CSprite::SetHotSpot(POINT &pt)
{
	this->ptHotSpot = pt;
}
void CSprite::SetStretchDraw(bool bVal) 
{
	this->bStretchDraw = bVal;
	if (!bVal)
	{
		nDestWidth = width;
		nDestHeight = height;
	}
}
void CSprite::SetZOrder(int nZOrder) 
{
	this->nZOrder = nZOrder;
}
HDC CSprite::GetDC()
{
	return hdcSprite;
}
void CSprite::SetPos(float x,float y)
{
	this->x = x;
	this->y = y;
	rectSprite.left = x;
	rectSprite.top = y;
	rectSprite.right = x + width;
	rectSprite.bottom = y + height;
}
int CSprite::GetWidth()
{
	return width;
}
int CSprite::GetHeight()
{
	return height;
}
float CSprite::GetXPos()
{
	return x;
}
float CSprite::GetYPos()
{
	return y;
}
void CSprite::SetTexturePos(int x,int y)
{
	this->tx = x;
	this->ty = y;
}

void  CSprite::SetDestWidth(int nWidth)													//设置目的宽度
{
	this->nDestWidth = nWidth;
}

void  CSprite::SetDestHeight(int nHeight)												//设置目的高度
{
	this->nDestHeight = nHeight;
}



void CSprite::SetRotationAngle(float fAngle)											//设置旋转角度					
{
	this->fRotationAngle = fAngle;
}

float CSprite::GetRotationAngle()
{
	return fRotationAngle;
}

bool CSprite::IsSelected(int x, int y)
{
	if (x >= rectSprite.left && x <= rectSprite.right && y >= rectSprite.top && y <= rectSprite.bottom)
		return true;
	else
		return false;
}