#pragma once

#include <windows.h>
#include <d2d1.h>
#include<time.h>
#include <wincodec.h>   //����WICλͼ�ļ���Ҫ��
#include<dwrite.h>

//#include"ResourcesPool.h"
//#include"SpritesManager.h"
//#include"AnimationSprite.h"
#include"..\MyGame\CMyGame.h"

using namespace std;
using namespace D2D1;

HWND		hWnd;

ID2D1Factory			*pD2DFactory = NULL;	 // Direct2D factory
ID2D1HwndRenderTarget	*pRenderTarget = NULL;
IWICImagingFactory		*pWICFactory = NULL;
//ID2D1Bitmap				*pBitmap = NULL;
RECT rc;										// Render area

/*����*/
IDWriteFactory	* pDWriteFactory = NULL;
IDWriteTextFormat	*pTextFormat = NULL;
ID2D1SolidColorBrush	*pBrush = NULL;


/*������λ��*/
void GetClickPoint();
POINT CMouse;//���λ��

/*��ʼ����̬��Ա*/
CResourcesPool * CResourcesPool::pCResourcePool = NULL;
CSpritesManager *CSpritesManager::instance = NULL;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);



void Cleanup();									//�ͷ���Դ��������
HRESULT init();									//��ʼ��D2D

HRESULT CreateDeviceIndependentResources();		//�����豸�޹���Դ
HRESULT CreateDeviceResources();				//�����豸�����Դ


/*���*/
CGame *pGame = NULL;	//����ָ��pGame
HRESULT init()
{
	GetClientRect(hWnd, &rc);
	//�õ���Ļ��ͼ�������
	HRESULT hr = CreateDeviceIndependentResources();	//�����豸�޹���Դ
	if (SUCCEEDED(hr))
	{
		hr = CreateDeviceResources();					//�����豸�����Դ
	}

	return hr;
}

void Cleanup()
{
	SafeRelease(&pBrush);
	SafeRelease(&pTextFormat);
	SafeRelease(&pDWriteFactory);
	SafeRelease(&pWICFactory);
	SafeRelease(&pRenderTarget);
	SafeRelease(&pD2DFactory);
}
HRESULT CreateDeviceIndependentResources()
{

	// Create a Direct2D factory.

	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);

	if (SUCCEEDED(hr))
	{
		// Create WIC factory.
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&pWICFactory)
			);
	}

	if (SUCCEEDED(hr))
	{
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&pDWriteFactory)
			);
	}


	return hr;
}


HRESULT CreateDeviceResources()
{
	HRESULT hr = !S_OK;

	if (!pRenderTarget)
	{

		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top
			);

		// Create a Direct2D render target.
		hr = pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, size),
			&pRenderTarget
			);


		hr = pDWriteFactory->CreateTextFormat(
			L"Comic Sans MS",//����
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,//���
			DWRITE_FONT_STYLE_NORMAL,//���
			DWRITE_FONT_STRETCH_NORMAL,
			20,//��С
			L"", //��������
			&pTextFormat
			);

		pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::White),//��ɫ
			&pBrush//��ˢ
			);
	}

	return hr;
}


void GetClickPoint()
{
	GetCursorPos(&CMouse);            // ��ȡ���ָ��λ�ã���Ļ���꣩
	ScreenToClient(hWnd, &CMouse);    // �����ָ��λ��ת��Ϊ��������
}

