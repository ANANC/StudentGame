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
	void InitGame();//创建资源

	virtual void Update(float fDeltaTime);//帧函数	
	virtual void Render();		//渲染	

	void Cleanup();//清理

	void GetCMouse();//得到点击位置
	//void HandleMouseDown(WPARAM wParam, LPARAM lParam);
};