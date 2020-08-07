#pragma once

/*******************************************************************************
Ŀ�꣺	����������,���ڹ������������Ϊ,������ͼƬ��Ⱦ��ָ����DC��ָ���ط�,
	��Ⱦʱ���Խ��������͸����Ⱦ�������ܼ���Ƿ�������������ײ
���ߣ�
����ʱ�䣺
�汾��

�޸��ߣ�

********************************************************************************/
#include <windows.h>
#include <math.h>
//#include "Resources.h"
#define PI 3.1415926
class CSprite
{
public:
	CSprite(void);																	//���캯��
	CSprite(HDC hdcSprite,int x,int y,int w,int h);									//���ι���
	
	virtual ~CSprite(void);																	//����
protected:
	
	HDC		hdcSprite;																//������ָ���ͼƬ��Դ
	HDC     hdcDest;																//Ŀ��DC
	RECT    rectSprite;																//������� 
	float   x;																		//Ŀ��x
	float   y;																		//Ŀ��y
	int     tx;																		//Դͼx
	int     ty;																		//Դͼy
	int     width;																	//������
	int     height;																	//����߶�			
	int     nDestWidth;																//Ŀ�Ŀ��
	int     nDestHeight;															//Ŀ�ĸ߶�
	DWORD   dwColorKey;																//�ؼ�ɫ
	POINT   ptHotSpot;																//�ȵ�
	int     nZOrder;																//Z-Order
	bool	bStretchDraw;		//�Ƿ�������Ⱦ

	bool    bTransparent;
	bool	bVisible;

	float   fRotationAngle;		//��ת�Ƕ�

	RECT SpriteBox[3];//�����Χ��
public:
	void Draw();
	//void Draw(bool bTransparent = false);											//��Ⱦ				
	void Draw(HDC hdcDest);								//�������õ�x,y��Ⱦ��Ŀ��	
	void Draw(int x,int y);								//��Ⱦ��Ŀ��x,y
	void Draw(HDC hdcDest,int x,int y);					//��Ⱦ��ָ��DC��ָ���ط�
	void StretchDraw(HDC hdcDest,int nDestX,int nDestY,int nDestWidth,int nDestHeight);//������Ⱦ
	void SetStretchDraw(bool bVal);													//�����Ƿ�����		
	bool CollideWith(CSprite & sprite);												//�Ƿ���ײ
	bool CollideWith(RECT &rect);													//�Ƿ��ĳ��������ײ
	bool IsSelected(int x, int y);													//����Ƿ�ѡ��

	void SetColorKey(DWORD dwColorKey);												//���ùؼ�ɫ
	void SetZOrder(int nZOrder);													//����Z��Order
	int GetZOrder();																//�õ� Z-Order
	HDC GetDC();																	//�õ������λͼDC
	void SetDestDC(HDC hdcDest);													//���þ�����Ⱦ��Ŀ��DC
	void SetTexture(HDC hdcTexture);												//���þ����λͼ
	void SetPos(float x,float y);													//���þ��������
	void SetTexturePos(int x,int y);												//���þ���Դ�����Ͻ�����	
	float GetXPos();																//�õ�������Ŀ��DC�����Ͻ�x����	
	float GetYPos();																//�õ�������Ŀ��DC�����Ͻ�y����
	int GetWidth();																	//�õ�������
	int GetHeight();																//�õ�����߶�
	void SetHotSpot(POINT &pt);														//�����ȵ�			
	POINT GetHotSpot();																//�õ��ȵ�

	const RECT* GetSpriteRect();													//�õ��������		
	void SetSpriteRect(int x,int y)//���þ������
	{
		//rectSprite.left += x;
		//rectSprite.top += y;
		rectSprite.right += x;
		rectSprite.bottom += y;
	}

	DWORD GetPixelColor(int x,int y);												//�õ�ָ�������ɫ

	void  SetDestWidth(int nWidth);													//����Ŀ�Ŀ��
	

	void  SetDestHeight(int nHeight);												//����Ŀ�ĸ߶�
	
	
	virtual void Update(float fDeltaTime){}											//����
	
	void SetRotationAngle(float fAngle)	;											//������ת�Ƕ�					
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
