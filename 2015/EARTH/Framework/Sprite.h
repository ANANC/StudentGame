#pragma once

/*******************************************************************************
目标：	建立精灵类,用于管理精灵自身的行为,包括将图片渲染到指定的DC的指定地方,
	渲染时可以进行拉伸和透明渲染。并且能检查是否与其它精灵碰撞
作者：
创建时间：
版本：

修改者：

********************************************************************************/
#include <windows.h>
#include <math.h>
//#include "Resources.h"
#define PI 3.1415926
class CSprite
{
public:
	CSprite(void);																	//构造函数
	CSprite(HDC hdcSprite,int x,int y,int w,int h);									//带参构造
	
	virtual ~CSprite(void);																	//析构
protected:
	
	HDC		hdcSprite;																//精灵所指向的图片资源
	HDC     hdcDest;																//目的DC
	RECT    rectSprite;																//精灵矩形 
	float   x;																		//目的x
	float   y;																		//目的y
	int     tx;																		//源图x
	int     ty;																		//源图y
	int     width;																	//精灵宽度
	int     height;																	//精灵高度			
	int     nDestWidth;																//目的宽度
	int     nDestHeight;															//目的高度
	DWORD   dwColorKey;																//关键色
	POINT   ptHotSpot;																//热点
	int     nZOrder;																//Z-Order
	bool	bStretchDraw;		//是否拉伸渲染

	bool    bTransparent;
	bool	bVisible;

	float   fRotationAngle;		//旋转角度

	RECT SpriteBox[3];//精灵包围盒
public:
	void Draw();
	//void Draw(bool bTransparent = false);											//渲染				
	void Draw(HDC hdcDest);								//根据设置的x,y渲染到目的	
	void Draw(int x,int y);								//渲染到目的x,y
	void Draw(HDC hdcDest,int x,int y);					//渲染到指定DC的指定地方
	void StretchDraw(HDC hdcDest,int nDestX,int nDestY,int nDestWidth,int nDestHeight);//拉伸渲染
	void SetStretchDraw(bool bVal);													//设置是否拉伸		
	bool CollideWith(CSprite & sprite);												//是否碰撞
	bool CollideWith(RECT &rect);													//是否和某个矩形碰撞
	bool IsSelected(int x, int y);													//鼠标是否选中

	void SetColorKey(DWORD dwColorKey);												//设置关键色
	void SetZOrder(int nZOrder);													//设置Z—Order
	int GetZOrder();																//得到 Z-Order
	HDC GetDC();																	//得到精灵的位图DC
	void SetDestDC(HDC hdcDest);													//设置精灵渲染的目的DC
	void SetTexture(HDC hdcTexture);												//设置精灵的位图
	void SetPos(float x,float y);													//设置精灵的坐标
	void SetTexturePos(int x,int y);												//设置精灵源的左上角坐标	
	float GetXPos();																//得到精灵在目的DC的左上角x坐标	
	float GetYPos();																//得到精灵在目的DC的左上角y坐标
	int GetWidth();																	//得到精灵宽度
	int GetHeight();																//得到精灵高度
	void SetHotSpot(POINT &pt);														//设置热点			
	POINT GetHotSpot();																//得到热点

	const RECT* GetSpriteRect();													//得到精灵矩形		
	void SetSpriteRect(int x,int y)//设置精灵矩形
	{
		//rectSprite.left += x;
		//rectSprite.top += y;
		rectSprite.right += x;
		rectSprite.bottom += y;
	}

	DWORD GetPixelColor(int x,int y);												//得到指定点的颜色

	void  SetDestWidth(int nWidth);													//设置目的宽度
	

	void  SetDestHeight(int nHeight);												//设置目的高度
	
	
	virtual void Update(float fDeltaTime){}											//更新
	
	void SetRotationAngle(float fAngle)	;											//设置旋转角度					
	float GetRotationAngle();

	void SetTransparent(bool val);
	bool GetTransparent();
	void SetVisible(bool val);
	bool GetVisible();

	int GetDestWidth(){ return nDestWidth; }
	int GetDestHeight(){ return nDestHeight; }

	void SetSpriteBox(RECT r1, RECT r2, RECT r3)
	{
		SpriteBox[0] = r1;
		SpriteBox[1] = r2;
		SpriteBox[2] = r3;
	}
	const RECT* GetSpriteBox1(){ return &SpriteBox[0]; }
	const RECT* GetSpriteBox2(){ return &SpriteBox[1]; }
	const RECT* GetSpriteBox3(){ return &SpriteBox[2]; }
};
