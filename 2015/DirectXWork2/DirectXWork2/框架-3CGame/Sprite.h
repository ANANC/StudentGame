#pragma  once


/*******************************************************************************
	建立精灵类,用于管理精灵自身的行为,包括将图片渲染到指定的地方,
	渲染时可以拉伸渲染，并且能检查是否与其它精灵碰撞。

********************************************************************************/

#include <windows.h>
#include <math.h>
#include <d2d1.h>
#include <assert.h>
#include <string>
#include "Helper.h"
//#include "Resources.h"
//#include "SafeRelease.h"


using namespace D2D1;
using namespace std;


class CSprite
{
	
public:

	CSprite(ID2D1HwndRenderTarget 		*pRenderTarget,													//RenderTarget										
			ID2D1Bitmap					*pTexture,														//纹理
			D2D1_POINT_2F				&vPos, 															//位置向量
			int							w,																//精灵宽度
			int							h,																//精灵高度
			int							tx = 0,															//纹理x
			int							ty = 0,															//纹理y
			D2D1_POINT_2F				vHotSpot=Point2F(0.0f,0.0f),										//热点
			wstring						wsName = TEXT("")
			);														
	virtual ~CSprite(void);				//析构
	
	friend class CSpritesManager;
protected:
	wstring						wsName;
	ID2D1HwndRenderTarget 		*pRenderTarget;															
	ID2D1Bitmap					*pTexture;
	ID2D1BitmapBrush			*pSpriteBrush;
	ID2D1Bitmap					*pSpriteBitmap;
	ID2D1SolidColorBrush		*pBoundingBoxBrush;
	D2D1_RECT_F					rtBoundingBox;															//精灵矩形 
	D2D1_POINT_2F				vPos;																	//位置向量
	int							tx;																		//纹理图x
	int							ty;																		//纹理图y									
	

	int							width;																	//精灵宽度
	int							height;																	//精灵高度			
	int							nTexWidth;
	int							nTexHeight;
																
	bool						bVisible;																//可见性
	bool						bEnabled;																//使能
	bool						bDrawBoundingBox;														//是否需要画包围盒
	bool						bTexPosChanged;															//纹理是否发生了改变
	bool						bStretch;																//是否拉伸填充


	D2D1_COLOR_F				color;
	D2D1_POINT_2F	            vHotSpot;																//热点

	
																										//下面是4个变换矩阵
	Matrix3x2F			        matWorld;											
	Matrix3x2F					matScale;
	Matrix3x2F					matRotation;
	Matrix3x2F					matTranslation;

	float						fRotationAngle;															//旋转角度
	float                       fsx;																	//x方向的缩放系数
	float                       fsy;																	//y方向的缩放系数

	D2D1_RECT_F					destRect;																//目标矩形
	D2D1_POINT_2F				ptBoundingBox[4];														//包围盒矩形


	void                        ComputerBoundingBox();													//计算包围盒矩形

	
	virtual CSprite *Clone();																			//克隆精灵

	void Release();																						//释放资源
	
public:

	
	
	bool IsSelected(int x,int y);																//是否选中
	bool CollideWith(CSprite &sprite);															//是否碰撞
	bool CollideWith(RECT &rect);																//是否和某个矩形碰撞

	void SetTexture(ID2D1Bitmap *tex);															//设置精灵的纹理
	const ID2D1Bitmap *GetTexture();

	const ID2D1Bitmap *GetBitmap();																//得到精灵渲染的位图


	void SetScaleFactor(float sx,float sy);														//设置缩放系数 

	void SetDestRect(float x1,float y1,float w,float h,bool bStretch = true);					//设置渲染的目的矩形

	void SetTransform(Matrix3x2F &matTrans);													//设置变换矩阵 
	const Matrix3x2F *GetTransform();
	
	void SetTexPos(int x,int y);																//设置精灵在纹理上截取的左上角坐标	

	void SetPos(D2D1_POINT_2F &vPos);															//设置精灵的位置
	D2D1_POINT_2F	&GetPos();	


	void SetHotSpot(D2D1_POINT_2F &vHotSpot);													//设置热点			
	D2D1_POINT_2F &GetHotSpot();																//得到热点

	void SetRotationAngle(float fAngle);														//设置旋转角度			
	float GetRotationAngle();

	void SetVisible(bool bVal);																	//设置精灵可见性 
	bool IsVisible();	

	void SetEnabled(bool bVal);																	//设置精灵“使能”
	bool IsEnabled();

	int GetWidth();																				//得到精灵宽度
	int GetHeight();																			//得到精灵高度



	const wstring &GetSpriteName();
	const D2D1_RECT_F* GetBoundingBox();																//得到精灵矩形范围		


	virtual void Update(float fDeltaTime){}	//更新
	virtual void Render();																		//根据设定的变换矩阵进行渲染
	virtual void Render(D2D1_POINT_2F &vPos);													//渲染到指定位置
	virtual void Render(D2D1_RECT_F &destRect,													//渲染到指定的目标矩形，根据给定的参数决定是拉伸渲染还是平铺渲染			
						bool bStretch=true,
						D2D1_EXTEND_MODE extendModeX=D2D1_EXTEND_MODE_WRAP, 
						D2D1_EXTEND_MODE extendModeY=D2D1_EXTEND_MODE_WRAP);
	
};





