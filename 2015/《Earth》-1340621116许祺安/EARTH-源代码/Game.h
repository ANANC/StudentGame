#pragma once
#include<windows.h>
#include <math.h>

class CGame
{

	public:
		CGame(HWND hWnd,int fps=30)
		{
			hwnd=hWnd;
			nFps=fps;	
			Init();
		}

		~CGame()
		{
			DeleteDC(hdcMen);
			ReleaseDC(hwnd, hdc);
			DeleteObject(hbm);
			//DeleteObject(holdbm);
		}
		void FrameFunc();
		void Init();
		virtual void Render();	//�������Ч��	��˫����
		int ifdown();

	protected:
		virtual void Update(float fDeltaTime);			//״̬��Ϸ�޸�	
		int					nFps;						//ÿ�����֡
		unsigned int        nFrames;					//��֡��
		DWORD				t0;                         //ǰһ֡��ʱ��
		float t;										//�ۼ�����
		int					nFixedDeltaTime;			//�趨����֡���ʱ��������λ�Ǻ���
		
		RECT rt;
		HWND hwnd;
		HDC hdcMen;
		HDC hdc;
		HBITMAP hbm;
		//HBITMAP holdbm;
	
	private:
		int x;
		int y;
		int ifd;
		int iclicknum ;
	
};

class Sprite
{
public:
	Sprite(HWND hWnd)
	{

		Shwnd = hWnd;
		SInit();
	}

	~Sprite()
	{

	}

	void SFrameFunc();
	void SInit();
	virtual void SRender();

protected:
	RECT rt;
	HWND Shwnd;
	HDC hdcMen;
	HDC hdc;
	HBITMAP hbm;

	
private:



};
