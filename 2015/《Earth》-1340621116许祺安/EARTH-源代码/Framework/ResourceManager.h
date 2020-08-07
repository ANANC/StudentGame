#pragma once

#include <windows.h>
#define MAXRESCHARS	255
#define MAX_RESOURCES	1000
enum ResourceType		//��Դ����
{
	RES_BMP
};
typedef struct tagResDesc				//��Դ�ڵ�
{	
	TCHAR		szName[MAXRESCHARS];	//��Դ��
	int			nResgroup;				//��Դ��
	DWORD		dwHandle1;				//��Դ���1
	DWORD		dwHandle2;				//��Դ���2
	ResourceType resourceType;			//��Դ����
	
}ResDesc,*PResDesc;


/************************************************
	��Դ��������������������е���Դ
	Ŀǰֻ����λͼ
************************************************/

class CResourceManager
{
public:
	CResourceManager(HWND hWnd);
	virtual ~CResourceManager(void);
public:	


	void LoadPictureFromFile(const TCHAR * pszName,const TCHAR *pszFile);					//����λͼ��Դ
	
	const PResDesc GetResource(ResourceType resType,const TCHAR *pszResName);		//������Դ���ͺ���Դ���õ���Դ�ڵ�
	void SetHWnd(HWND hWnd);
private:
	ResDesc *res[MAX_RESOURCES];															
	int		nSize;
	HWND	hWnd;															//���ھ��

	

};
