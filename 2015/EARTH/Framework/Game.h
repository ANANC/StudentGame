#pragma once
#include<windows.h>
#include <tchar.h>
#include "SpriteManager.h"
#include "ResourceManager.h"
#include "Vector2D.h"
class CGame
{

public:
	CGame(HWND hWnd,int fps=0);
	
	virtual ~CGame(void);
	
	void FrameFunc();

	virtual void Init() ;

	


protected:

	CSpriteManager		*pSpriteManager;									//����������ָ��	
	CResourceManager	*pResManager;										//��Դ�������ָ��	


	virtual void Update(float fDeltaTime){}	//״̬��Ϸ�޸�	
	virtual void Render();							//�������Ч��	


	HDC					hdcMem;												//�ڴ��豸����
	HBITMAP				hbMem;												//�ڴ�λͼ
	HDC					hdc;												//��ǰ�豸����
	RECT				rectClient;											//�ͻ�������

	int					nFps;						//ÿ�����֡
	int                 nFrames;					//��֡��
	int					nCalcFps;					//�����֡Ƶ
	DWORD				t0;                         //ǰһ֡��ʱ��
	float				t;							//�ۼ�����
	float				fFixedDeltaTime;			//�趨����֡���ʱ��������λ�Ǻ���
			
	HWND				hWnd;

	TCHAR               szBuf[255];		

	HPEN				hPen;
	HBRUSH				hBr;
};