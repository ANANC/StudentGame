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
	

	
	
	
	//�Ӵ�������λͼ	
	HBITMAP hBitmap=(HBITMAP)LoadImage(
		NULL,//����λͼʵ���handle��
		pszFile,//λͼ��Դ·�����ļ���
		IMAGE_BITMAP,//����λͼ������
		0,0,//λͼ��Ҫ��ʾ�Ŀ��
		LR_LOADFROMFILE//���ر�־��
	);
	if (!hBitmap)
	{
		//ReleaseDC(hWnd,hdc);
		return;
	}

	ResDesc *pResDesc = new ResDesc;
	wcscpy_s(pResDesc->szName,pszName);
	HDC hdc=GetDC(hWnd);//��õ�ǰ���ڵ�DC
	 //���ڴ��д���һ���͵�ǰ���ڼ��ݵĻ�ͼ���
	HDC hdcBmp=CreateCompatibleDC(hdc);

	//��Bitmapѡ���ڴ��д����õ�dc
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



