#pragma once

#include <windows.h>
#define MAXRESCHARS	255
#define MAX_RESOURCES	1000
enum ResourceType		//资源类型
{
	RES_BMP
};
typedef struct tagResDesc				//资源节点
{	
	TCHAR		szName[MAXRESCHARS];	//资源名
	int			nResgroup;				//资源组
	DWORD		dwHandle1;				//资源句柄1
	DWORD		dwHandle2;				//资源句柄2
	ResourceType resourceType;			//资源类型
	
}ResDesc,*PResDesc;


/************************************************
	资源管理器，用数组管理所有的资源
	目前只管理位图
************************************************/

class CResourceManager
{
public:
	CResourceManager(HWND hWnd);
	virtual ~CResourceManager(void);
public:	


	void LoadPictureFromFile(const TCHAR * pszName,const TCHAR *pszFile);					//载入位图资源
	
	const PResDesc GetResource(ResourceType resType,const TCHAR *pszResName);		//根据资源类型和资源名得到资源节点
	void SetHWnd(HWND hWnd);
private:
	ResDesc *res[MAX_RESOURCES];															
	int		nSize;
	HWND	hWnd;															//窗口句柄

	

};
