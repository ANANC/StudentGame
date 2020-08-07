#pragma once

#include <windows.h>
#include <d2d1.h>
#include<time.h>
#include <wincodec.h>   //创建WIC位图文件需要的
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

/*字体*/
IDWriteFactory	* pDWriteFactory = NULL;
IDWriteTextFormat	*pTextFormat = NULL;
ID2D1SolidColorBrush	*pBrush = NULL;


/*获得鼠标位置*/
void GetClickPoint();
POINT CMouse;//鼠标位置

/*初始化静态成员*/
CResourcesPool * CResourcesPool::pCResourcePool = NULL;
CSpritesManager *CSpritesManager::instance = NULL;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);



void Cleanup();									//释放资源的清理函数
HRESULT init();									//初始化D2D

HRESULT CreateDeviceIndependentResources();		//创建设备无关资源
HRESULT CreateDeviceResources();				//创建设备相关资源


/*框架*/
CGame *pGame = NULL;	//定义指针pGame
HRESULT init()
{
	GetClientRect(hWnd, &rc);
	//得到屏幕绘图区域矩形
	HRESULT hr = CreateDeviceIndependentResources();	//创建设备无关资源
	if (SUCCEEDED(hr))
	{
		hr = CreateDeviceResources();					//创建设备相关资源
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
			L"Comic Sans MS",//名字
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,//宽度
			DWRITE_FONT_STYLE_NORMAL,//风格
			DWRITE_FONT_STRETCH_NORMAL,
			20,//大小
			L"", //当地名称
			&pTextFormat
			);

		pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::White),//颜色
			&pBrush//笔刷
			);
	}

	return hr;
}


void GetClickPoint()
{
	GetCursorPos(&CMouse);            // 获取鼠标指针位置（屏幕坐标）
	ScreenToClient(hWnd, &CMouse);    // 将鼠标指针位置转换为窗口坐标
}

