#pragma once

#include"..\OldFrame\Game.h"
#include"GameChapter.h"
#include"GameResource.h"
#include"NSpriteManager.h"

class CMyGame : public CGame
{
public:
	CMyGame(HINSTANCE hInstance, HWND hWnd, int nFps = 0);
	~CMyGame();

private:
	ID2D1SolidColorBrush *pBrush;
	GameChapter *pGameChapter;
	POINT CMouse;
public:
	void InitGame();//������Դ

	virtual void Update(float fDeltaTime);//֡����	
	virtual void Render();		//��Ⱦ	

	void Cleanup();//����

	void GetCMouse();//�õ����λ��
	//void HandleMouseDown(WPARAM wParam, LPARAM lParam);
};