#pragma once

#include"..\OldFrame\Game.h"
#include"GameChapter.h"
#include"GameResource.h"
#include"NSpriteManager.h"
#include"..\OldFrame\XAudio2SoundPlayer.h"
#include"..\MyFrame\NSprite.h"

class CMyGame : public CGame
{
public:
	CMyGame(HINSTANCE hInstance, HWND hWnd, int nFps = 0);
	~CMyGame();

private:
	GameChapter *pGameChapter;
	POINT CMouse;

	CNSprite *pCursor;//鼠标
	POINT StartpCursor;//鼠标初始位置
	XAudio2SoundPlayer *pXAudio2SoundPlayerp;//声音资源类-背景音乐

public:
	void InitGame();//创建资源
	inline void PlayingSound();//循环音乐
	virtual void Update(float fDeltaTime);//帧函数	
	virtual void Render();		//渲染	

	void Cleanup();//清理

	void GetCMouse();//得到点击位置
	//void HandleMouseDown(WPARAM wParam, LPARAM lParam);
};