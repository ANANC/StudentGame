#include "Game.h"
#include "Helper.h"
CGame::CGame(HWND hWnd,int nFps)
{
	pRenderTarget = NULL;
	pWICFactory = NULL;
	this->nFps = nFps;
	this->hWnd = hWnd;
	if (nFps > 0)
	{
		nFixedDeltaTime = 1000 / nFps;
	}
	else
	{
		nFixedDeltaTime = 0;
	}

	
	
	
	
	Init(hWnd);
	//this->hInstance = hInst;
	
	//HMODULE handle = GetModuleHandle(NULL);
	//pInput->CreateInput(hInstance,hWnd);

	t=0;
	nFrames = 0;
	
	t0 = timeGetTime();
	

}

CGame::~CGame(void)												//�������������ͷ���Դ
{
	
	Cleanup();

}


HRESULT CGame::CreateDeviceIndependentResources()
{
	static const WCHAR msc_fontName[] = L"Comic Sans MS";
	static const FLOAT msc_fontSize = 18;

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

		// Create a DirectWrite factory.
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(pDWriteFactory),
			reinterpret_cast<IUnknown **>(&pDWriteFactory)
			);
	}
	if (SUCCEEDED(hr))
	{
		// Create a DirectWrite text format object.
		hr = pDWriteFactory->CreateTextFormat(
			L"Comic Sans MS",
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			13,
			L"", //locale
			&pTextFormat
			);
	}
	if (SUCCEEDED(hr))
	{
		// Center the text horizontally and vertically.
		pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

		pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	}

	return hr;
}

HRESULT CGame::CreateDeviceResources()
{
	HRESULT hr = !S_OK;

	if (!pRenderTarget)
	{

		D2D1_SIZE_U size = D2D1::SizeU(
			rectClient.right - rectClient.left,
			rectClient.bottom - rectClient.top
			);

		// Create a Direct2D render target.
		hr = pD2DFactory->CreateHwndRenderTarget(			
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, size),
			&pRenderTarget
			);
		if (FAILED(hr))
		{
			return hr;
		}
		hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0xdadada), &pTextBrush);
		
	
	}
	return hr;
}
HRESULT CGame::Init(HWND hWnd)
{
	
    GetClientRect(hWnd,&rectClient);					//�õ���Ļ��ͼ�������
	HRESULT hr = CreateDeviceIndependentResources();	//�����豸�޹���Դ
	if (SUCCEEDED(hr))
	{
		hr = CreateDeviceResources();					//�����豸�����Դ
	}
	CResourcesPool::GetInstance()->init(pWICFactory,pRenderTarget);
	CSpritesManager::GetInstance()->SetRenderTarget(pRenderTarget);
	return hr;
	
   
}

//void CGame::CreateSpritesManager()
//{
//	pSpriteManager =  new CSpritesManager();
//}
//void CGame::CreateResourcesPool( )
//{
//	pResPool = new CResourcesPool();
//}


//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
void CGame::Cleanup()
{
	SafeRelease(&pWICFactory);
	SafeRelease(&pTextBrush);
 	SafeRelease(&pTextFormat);
	SafeRelease(&pDWriteFactory);          
	SafeRelease(&pRenderTarget);
	SafeRelease(&pD2DFactory);

}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
void CGame::Render()
{
    if( NULL == pRenderTarget )
        return;


	

    // Begin the scene
	//pRenderTarget->BeginDraw();
	pRenderTarget->Clear(D2D1::ColorF(0x343131, 1.0f));//�����޸��˱�����ɫ
        // Rendering of scene objects can happen here
	
		pSpritesManager = CSpritesManager::GetInstance();
		if (pSpritesManager)
		{
			pSpritesManager->Render();
		}
		if (t > 0)
		{
			//int nfps =  nFrames / t;
			//wsprintf(szBuf,TEXT("֡Ƶ��%d"),nfps);
			//D2D1_RECT_F rect = {0,0,50,20};
			//pRenderTarget->DrawText(
			//		 szBuf,           // Text to render
			//		 wcslen(szBuf),       // Text length
			//		 pTextFormat,     // Text format
			//		 rect,    // The region of the window where the text will be rendered
			//		 pTextBrush      // The brush used to draw the text
			//);
			
		}
    
        // End the scene
	//pRenderTarget->EndDraw();

   
}
void CGame::GameFunc()
{
	DWORD dt = 0;
	
	do 
	{ 
		dt=timeGetTime() - t0; 
	} while(dt < 1);									//��֤��С���ʱ����ڵ���1����
	if (dt >= nFixedDeltaTime)							//������ڹ̶��ļ��ʱ��
	{
		
		t0 = timeGetTime();								//��¼��֡���õ�ʱ��
	
	

		Update(dt / 1000.0);							//����֡��������
		t += dt / 1000.0;
		Render();										//��Ⱦ
		if (t > 1)
		{
			t = 0;
			nFrames = 0;
		}
		nFrames++;
	}
	else
	{
		Sleep(1);										//��������1����
	}

	
}
void CGame::Update(float fDeltaTime)
{
	
	CSpritesManager::GetInstance()->Update(fDeltaTime);		//���º���������ϵͳ���ŵ�ʱ�����������ľ��飬�������������أ�д��Ϸ����
	
}
