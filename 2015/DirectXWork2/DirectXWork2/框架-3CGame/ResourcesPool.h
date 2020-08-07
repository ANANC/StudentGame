#pragma once

#include <windows.h>
#include <map>
#include <string>
#include <D2D1.h>
#include <wincodec.h>   //����WICλͼ�ļ���Ҫ��
#include "Helper.h"
#define MAXRESCHARS	255
using namespace std;
using namespace D2D1;

enum ResourceType		//��Դ����
{
	RES_TEX
};
struct tagResDesc				//��Դ�ڵ�
{	
	tagResDesc()
	{
		wsName = TEXT("");//��Դ��
		wsPath = TEXT("");//��Դ·��
		//nResGroup = 0;//��Դ��

		pTexture = NULL;//��Դ����ָ��
		resourceType = RES_TEX;//��Դ����
	}
	wstring		wsName;					//��Դ��
	wstring		wsPath;					//��Դ·��
//	int			nResGroup;				//��Դ��
	ID2D1Bitmap	*pTexture;				//��Դ����ָ��
	ResourceType resourceType;			//��Դ����
};
typedef tagResDesc ResDesc,*PResDesc;

/************************************************
	��Դ����������map�������е���Դ
	Ŀǰֻ����λͼ
************************************************/

class CResourcesPool
{

private:
	CResourcesPool(){}
	static CResourcesPool *pCResourcePool;

public:
	static CResourcesPool *GetInstance()
	{
		if (pCResourcePool == NULL)
			pCResourcePool = new CResourcesPool();

		return pCResourcePool;
	}

	~CResourcesPool(void);


public:	//��Щ��������Ϊʲô�����ǹ��У����������ܱ����������
	void init(IWICImagingFactory *pWICImagingFactory,ID2D1HwndRenderTarget *pRenderTarget);		
	HRESULT AddTexture(const wstring wsName,const wstring  wsFile,ID2D1Bitmap **ppTexture = NULL);//�����ļ���װ��ͼƬ��Դ
	const PResDesc GetResource(const wstring sResName);		//������Դ���õ���Դ�ڵ�

	void ClearResourcesPool();

protected:
	typedef map<wstring,PResDesc> ResMap;
	ResMap					resMap;
	ID2D1HwndRenderTarget	*pRenderTarget;
	IWICImagingFactory		*pWICImagingFactory;
	void Release();

	HRESULT LoadBitmapFromFile(						//���ļ��ж�ȡλͼ
		const wstring		sName,
		const wstring		sFile,
		ID2D1Bitmap			**ppTexture,
		int					destinationWidth = 0,
		int					destinationHeight =0
		
	);
};






