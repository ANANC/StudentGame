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

	CNSprite *pCursor;//���
	POINT StartpCursor;//����ʼλ��
	XAudio2SoundPlayer *pXAudio2SoundPlayerp;//������Դ��-��������

public:
	void InitGame();//������Դ
	inline void PlayingSound();//ѭ������
	virtual void Update(float fDeltaTime);//֡����	
	virtual void Render();		//��Ⱦ	

	void Cleanup();//����

	void GetCMouse();//�õ����λ��
	//void HandleMouseDown(WPARAM wParam, LPARAM lParam);
};