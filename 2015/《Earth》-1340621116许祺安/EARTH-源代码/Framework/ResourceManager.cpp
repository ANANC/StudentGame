#include "ResourceManager.h"

CResourceManager::CResourceManager(HWND hWnd)
{
	this->hWnd = hWnd;
	nSize = 0;
}

CResourceManager::~CResourceManager(void)
{
	for(int i=0;i<nSize;++i)
	{
		PResDesc pResDesc = res[i];
		DeleteDC((HDC)pResDesc->dwHandle1);
		DeleteObject((HBITMAP)pResDesc->dwHandle2);
		delete res[i];
	}
	
}
const PResDesc CResourceManager::GetResource(ResourceType resType,const TCHAR *pszResName)
{
	for(int i=0;i<nSize;++i)
	{
		if (res[i]->resourceType == resType)
		{
			if (wcscmp(res[i]->szName,pszResName) == 0)
			{
				return res[i];
			}
		}
	}
	return NULL;
}



void CResourceManager::LoadPictureFromFile(const TCHAR *pszName,const TCHAR *pszFile)
{
	

	
	
	
	//从磁盘载入位图	
	HBITMAP hBitmap=(HBITMAP)LoadImage(
		NULL,//包含位图实体的handle，
		pszFile,//位图的源路径与文件名
		IMAGE_BITMAP,//加载位图的类型
		0,0,//位图索要显示的宽高
		LR_LOADFROMFILE//加载标志，
	);
	if (!hBitmap)
	{
		//ReleaseDC(hWnd,hdc);
		return;
	}

	ResDesc *pResDesc = new ResDesc;
	wcscpy_s(pResDesc->szName,pszName);
	HDC hdc=GetDC(hWnd);//获得当前窗口的DC
	 //在内存中创建一个和当前窗口兼容的绘图句柄
	HDC hdcBmp=CreateCompatibleDC(hdc);

	//将Bitmap选入内存中创建好的dc
	SelectObject(hdcBmp,hBitmap);
	ReleaseDC(hWnd,hdc);
	pResDesc->dwHandle1 = (DWORD)hdcBmp;
	pResDesc->dwHandle2 = (DWORD)hBitmap;
	pResDesc->resourceType = RES_BMP;

	res[nSize++] = pResDesc;
	
	//++nSize;
}
void CResourceManager::SetHWnd(HWND hWnd)
{
	this->hWnd = hWnd;
}



