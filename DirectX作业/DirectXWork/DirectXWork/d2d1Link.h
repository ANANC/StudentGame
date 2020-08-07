#include <wincodec.h>   //创建WIC位图文件需要的
#include<dwrite.h>
#include<d2d1.h>

using namespace std;
using namespace D2D1;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

template<class Interface>
inline void SafeRelease(Interface **ppInterfaceToRelease){
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = NULL;
	}
}

HRESULT LoadBitmapFromFile(						//从文件中读取位图
	ID2D1RenderTarget *pRenderTarget,
	IWICImagingFactory *pIWICFactory,
	PCWSTR uri,
	UINT destinationWidth,
	UINT destinationHeight,
	ID2D1Bitmap **ppBitmap
	);

HWND hwnd;
ID2D1Factory *pD2DFactory = NULL;
ID2D1HwndRenderTarget* pRenderTarget = NULL;
IWICImagingFactory		*pWICFactory = NULL;
RECT rc;
HRESULT hr;
ID2D1SolidColorBrush	*pBrush = NULL;

/*字体*/
IDWriteFactory	* pDWriteFactory = NULL;
IDWriteTextFormat	*pTextFormat = NULL;
ID2D1SolidColorBrush	*pBrushWrite = NULL;

/*位图*/
#define  BitmapCount  5//图片的数量
ID2D1Bitmap				*pBitmapPuzzle[BitmapCount] = { NULL };
ID2D1Bitmap				*pJumap = NULL;
ID2D1BitmapBrush		*pJumapBrush = NULL;


HRESULT CreateDeviceIndependentResources();		//创建设备无关资源
HRESULT CreateDeviceResources();				//创建设备相关资源
HRESULT Init();
void ClearUp();
void Render();

/*鼠标位置*/
POINT ClickP;
void GetClickPoint();

HRESULT Init()
{
	GetClientRect(hwnd, &rc);							//得到屏幕绘图区域矩形
	HRESULT hr = CreateDeviceIndependentResources();	//创建设备无关资源
	if (SUCCEEDED(hr))
	{
		hr = CreateDeviceResources();					//创建设备相关资源
	}
	return hr;
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
	hr = !S_OK;

	if (!pRenderTarget)
	{

		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top
			);

		// Create a Direct2D render target.
		hr = pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hwnd, size),
			&pRenderTarget
			);


		if (SUCCEEDED(hr))
		{
			// Create a bitmap by loading it from a file.
			hr = LoadBitmapFromFile(
				pRenderTarget,
				pWICFactory,
				L".\\1.jpg",
				0,
				0,
				&pBitmapPuzzle[0]
				);
		}

		if (SUCCEEDED(hr))
		{
			// Create a bitmap by loading it from a file.
			hr = LoadBitmapFromFile(
				pRenderTarget,
				pWICFactory,
				L".\\2.jpg",
				0,
				0,
				&pBitmapPuzzle[1]
				);
		}

		if (SUCCEEDED(hr))
		{
			// Create a bitmap by loading it from a file.
			hr = LoadBitmapFromFile(
				pRenderTarget,
				pWICFactory,
				L".\\3.jpg",
				0,
				0,
				&pBitmapPuzzle[2]
				);
		}

		if (SUCCEEDED(hr))
		{
			// Create a bitmap by loading it from a file.
			hr = LoadBitmapFromFile(
				pRenderTarget,
				pWICFactory,
				L".\\4.jpg",
				0,
				0,
				&pBitmapPuzzle[3]
				);
		}

		if (SUCCEEDED(hr))
		{
			// Create a bitmap by loading it from a file.
			hr = LoadBitmapFromFile(
				pRenderTarget,
				pWICFactory,
				L".\\5.jpg",
				0,
				0,
				&pBitmapPuzzle[4]
				);
		}

		/*笔刷*/
		hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White, 1.0f),&pBrush);


		hr = pDWriteFactory->CreateTextFormat(
			L"Comic Sans MS",//名字
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,//宽度
			DWRITE_FONT_STYLE_NORMAL,//风格
			DWRITE_FONT_STRETCH_NORMAL,
			13,//大小
			L"", //当地名称
			&pTextFormat
			);

		pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::White),//颜色
			&pBrushWrite//笔刷
			);
		
		/*位图*/
		D2D1_SIZE_F j = pBitmapPuzzle[0]->GetSize();
		pRenderTarget->CreateBitmap(D2D1::SizeU(j.width, j.height), D2D1::BitmapProperties(pBitmapPuzzle[0]->GetPixelFormat()), &pJumap);

		/*位图笔刷*/
		hr = pRenderTarget->CreateBitmapBrush(pJumap,&pJumapBrush);

	}
	return hr;
}

void ClearUp()
{
	SafeRelease(&pBrush);
	SafeRelease(&pJumapBrush);
	SafeRelease(&pTextFormat);
	SafeRelease(&pDWriteFactory);
	for (int i = 0; i < 3; i++)
		SafeRelease(&pBitmapPuzzle[i]);
	SafeRelease(&pWICFactory);
	SafeRelease(&pJumap);
	SafeRelease(&pRenderTarget);
	SafeRelease(&pD2DFactory);

}

void GetClickPoint()
{
	GetCursorPos(&ClickP);            // 获取鼠标指针位置（屏幕坐标）
	ScreenToClient(hwnd, &ClickP);    // 将鼠标指针位置转换为窗口坐标
}


//
// Creates a Direct2D bitmap from a resource in the
// application resource file.
//
HRESULT LoadResourceBitmap(
	ID2D1RenderTarget *pRenderTarget,
	IWICImagingFactory *pIWICFactory,
	PCWSTR resourceName,
	PCWSTR resourceType,
	UINT destinationWidth,
	UINT destinationHeight,
	ID2D1Bitmap **ppBitmap
	)
{
	IWICBitmapDecoder *pDecoder = NULL;
	IWICBitmapFrameDecode *pSource = NULL;
	IWICStream *pStream = NULL;
	IWICFormatConverter *pConverter = NULL;
	IWICBitmapScaler *pScaler = NULL;

	HRSRC imageResHandle = NULL;
	HGLOBAL imageResDataHandle = NULL;
	void *pImageFile = NULL;
	DWORD imageFileSize = 0;

	// Locate the resource.
	imageResHandle = FindResourceW(NULL, resourceName, resourceType);
	HRESULT hr = imageResHandle ? S_OK : E_FAIL;
	if (SUCCEEDED(hr))
	{
		// Load the resource.
		imageResDataHandle = LoadResource(NULL, imageResHandle);

		hr = imageResDataHandle ? S_OK : E_FAIL;
	}
	if (SUCCEEDED(hr))
	{
		// Lock it to get a system memory pointer.
		pImageFile = LockResource(imageResDataHandle);

		hr = pImageFile ? S_OK : E_FAIL;
	}
	if (SUCCEEDED(hr))
	{
		// Calculate the size.
		imageFileSize = SizeofResource(NULL, imageResHandle);

		hr = imageFileSize ? S_OK : E_FAIL;

	}
	if (SUCCEEDED(hr))
	{
		// Create a WIC stream to map onto the memory.
		hr = pIWICFactory->CreateStream(&pStream);
	}
	if (SUCCEEDED(hr))
	{
		// Initialize the stream with the memory pointer and size.
		hr = pStream->InitializeFromMemory(
			reinterpret_cast<BYTE*>(pImageFile),
			imageFileSize
			);
	}
	if (SUCCEEDED(hr))
	{
		// Create a decoder for the stream.
		hr = pIWICFactory->CreateDecoderFromStream(
			pStream,
			NULL,
			WICDecodeMetadataCacheOnLoad,
			&pDecoder
			);
	}
	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}
	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pIWICFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr))
	{
		// If a new width or height was specified, create an
		// IWICBitmapScaler and use it to resize the image.
		if (destinationWidth != 0 || destinationHeight != 0)
		{
			UINT originalWidth, originalHeight;
			hr = pSource->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr))
			{
				if (destinationWidth == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
					destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
				}
				else if (destinationHeight == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
					destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
				}

				hr = pIWICFactory->CreateBitmapScaler(&pScaler);
				if (SUCCEEDED(hr))
				{
					hr = pScaler->Initialize(
						pSource,
						destinationWidth,
						destinationHeight,
						WICBitmapInterpolationModeCubic
						);
					if (SUCCEEDED(hr))
					{
						hr = pConverter->Initialize(
							pScaler,
							GUID_WICPixelFormat32bppPBGRA,
							WICBitmapDitherTypeNone,
							NULL,
							0.f,
							WICBitmapPaletteTypeMedianCut
							);
					}
				}
			}
		}
		else
		{

			hr = pConverter->Initialize(
				pSource,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.f,
				WICBitmapPaletteTypeMedianCut
				);
		}
	}
	if (SUCCEEDED(hr))
	{
		//create a Direct2D bitmap from the WIC bitmap.
		hr = pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
			);

	}

	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);

	return hr;
}

//
// Creates a Direct2D bitmap from the specified
// file name.
//
HRESULT LoadBitmapFromFile(
	ID2D1RenderTarget *pRenderTarget,
	IWICImagingFactory *pIWICFactory,
	PCWSTR uri,
	UINT destinationWidth,
	UINT destinationHeight,
	ID2D1Bitmap **ppBitmap
	)
{
	IWICBitmapDecoder *pDecoder = NULL;
	IWICBitmapFrameDecode *pSource = NULL;
	IWICStream *pStream = NULL;
	IWICFormatConverter *pConverter = NULL;
	IWICBitmapScaler *pScaler = NULL;

	HRESULT hr = pIWICFactory->CreateDecoderFromFilename(
		uri,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
		);

	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}
	if (SUCCEEDED(hr))
	{

		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pIWICFactory->CreateFormatConverter(&pConverter);

	}


	if (SUCCEEDED(hr))
	{
		// If a new width or height was specified, create an
		// IWICBitmapScaler and use it to resize the image.
		if (destinationWidth != 0 || destinationHeight != 0)
		{
			UINT originalWidth, originalHeight;
			hr = pSource->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr))
			{
				if (destinationWidth == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
					destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
				}
				else if (destinationHeight == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
					destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
				}

				hr = pIWICFactory->CreateBitmapScaler(&pScaler);
				if (SUCCEEDED(hr))
				{
					hr = pScaler->Initialize(
						pSource,
						destinationWidth,
						destinationHeight,
						WICBitmapInterpolationModeCubic
						);
				}
				if (SUCCEEDED(hr))
				{
					hr = pConverter->Initialize(
						pScaler,
						GUID_WICPixelFormat32bppPBGRA,
						WICBitmapDitherTypeNone,
						NULL,
						0.f,
						WICBitmapPaletteTypeMedianCut
						);
				}
			}
		}
		else // Don't scale the image.
		{
			hr = pConverter->Initialize(
				pSource,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.f,
				WICBitmapPaletteTypeMedianCut
				);
		}
	}
	if (SUCCEEDED(hr))
	{

		// Create a Direct2D bitmap from the WIC bitmap.
		hr = pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
			);
	}

	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);

	return hr;
}
