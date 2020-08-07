#pragma  once


/*******************************************************************************
	����������,���ڹ������������Ϊ,������ͼƬ��Ⱦ��ָ���ĵط�,
	��Ⱦʱ����������Ⱦ�������ܼ���Ƿ�������������ײ��

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
			ID2D1Bitmap					*pTexture,														//����
			D2D1_POINT_2F				&vPos, 															//λ������
			int							w,																//������
			int							h,																//����߶�
			int							tx = 0,															//����x
			int							ty = 0,															//����y
			D2D1_POINT_2F				vHotSpot=Point2F(0.0f,0.0f),										//�ȵ�
			wstring						wsName = TEXT("")
			);														
	virtual ~CSprite(void);				//����
	
	friend class CSpritesManager;
protected:
	wstring						wsName;
	ID2D1HwndRenderTarget 		*pRenderTarget;															
	ID2D1Bitmap					*pTexture;
	ID2D1BitmapBrush			*pSpriteBrush;
	ID2D1Bitmap					*pSpriteBitmap;
	ID2D1SolidColorBrush		*pBoundingBoxBrush;
	D2D1_RECT_F					rtBoundingBox;															//������� 
	D2D1_POINT_2F				vPos;																	//λ������
	int							tx;																		//����ͼx
	int							ty;																		//����ͼy									
	

	int							width;																	//������
	int							height;																	//����߶�			
	int							nTexWidth;
	int							nTexHeight;
																
	bool						bVisible;																//�ɼ���
	bool						bEnabled;																//ʹ��
	bool						bDrawBoundingBox;														//�Ƿ���Ҫ����Χ��
	bool						bTexPosChanged;															//�����Ƿ����˸ı�
	bool						bStretch;																//�Ƿ��������


	D2D1_COLOR_F				color;
	D2D1_POINT_2F	            vHotSpot;																//�ȵ�

	
																										//������4���任����
	Matrix3x2F			        matWorld;											
	Matrix3x2F					matScale;
	Matrix3x2F					matRotation;
	Matrix3x2F					matTranslation;

	float						fRotationAngle;															//��ת�Ƕ�
	float                       fsx;																	//x���������ϵ��
	float                       fsy;																	//y���������ϵ��

	D2D1_RECT_F					destRect;																//Ŀ�����
	D2D1_POINT_2F				ptBoundingBox[4];														//��Χ�о���


	void                        ComputerBoundingBox();													//�����Χ�о���

	
	virtual CSprite *Clone();																			//��¡����

	void Release();																						//�ͷ���Դ
	
public:

	
	
	bool IsSelected(int x,int y);																//�Ƿ�ѡ��
	bool CollideWith(CSprite &sprite);															//�Ƿ���ײ
	bool CollideWith(RECT &rect);																//�Ƿ��ĳ��������ײ

	void SetTexture(ID2D1Bitmap *tex);															//���þ��������
	const ID2D1Bitmap *GetTexture();

	const ID2D1Bitmap *GetBitmap();																//�õ�������Ⱦ��λͼ


	void SetScaleFactor(float sx,float sy);														//��������ϵ�� 

	void SetDestRect(float x1,float y1,float w,float h,bool bStretch = true);					//������Ⱦ��Ŀ�ľ���

	void SetTransform(Matrix3x2F &matTrans);													//���ñ任���� 
	const Matrix3x2F *GetTransform();
	
	void SetTexPos(int x,int y);																//���þ����������Ͻ�ȡ�����Ͻ�����	

	void SetPos(D2D1_POINT_2F &vPos);															//���þ����λ��
	D2D1_POINT_2F	&GetPos();	


	void SetHotSpot(D2D1_POINT_2F &vHotSpot);													//�����ȵ�			
	D2D1_POINT_2F &GetHotSpot();																//�õ��ȵ�

	void SetRotationAngle(float fAngle);														//������ת�Ƕ�			
	float GetRotationAngle();

	void SetVisible(bool bVal);																	//���þ���ɼ��� 
	bool IsVisible();	

	void SetEnabled(bool bVal);																	//���þ��顰ʹ�ܡ�
	bool IsEnabled();

	int GetWidth();																				//�õ�������
	int GetHeight();																			//�õ�����߶�



	const wstring &GetSpriteName();
	const D2D1_RECT_F* GetBoundingBox();																//�õ�������η�Χ		


	virtual void Update(float fDeltaTime){}	//����
	virtual void Render();																		//�����趨�ı任���������Ⱦ
	virtual void Render(D2D1_POINT_2F &vPos);													//��Ⱦ��ָ��λ��
	virtual void Render(D2D1_RECT_F &destRect,													//��Ⱦ��ָ����Ŀ����Σ����ݸ����Ĳ���������������Ⱦ����ƽ����Ⱦ			
						bool bStretch=true,
						D2D1_EXTEND_MODE extendModeX=D2D1_EXTEND_MODE_WRAP, 
						D2D1_EXTEND_MODE extendModeY=D2D1_EXTEND_MODE_WRAP);
	
};





