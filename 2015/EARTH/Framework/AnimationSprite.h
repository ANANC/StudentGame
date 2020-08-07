#pragma once
#include "sprite.h"

class CAnimationSprite :
	public CSprite
{
public:
	CAnimationSprite(void);
	virtual ~CAnimationSprite(void);
	//带参构造函数
	CAnimationSprite(	HDC		tex,						//精灵图片DC
						int		nFrames,					//总帧数
						int		nFps,						//每秒多少帧（速度）
						int		x,							//初始的屏幕位置坐标x
						int		y,							//初始的屏幕位置坐标y
						int		w,							//精灵的宽度
						int		h,							//精灵的高度
						int		tx,							//从精灵图片的起始坐标
						int		ty,
						int		texWidth,					//精灵图片的宽度
						int		texHeight);					//精灵图片的高度

	int			GetTXpos(){ return tx; }			//得到精灵源目的上左上角x的位置
	int			GetTYpos(){ return ty; }			//得到精灵源目的上左上角y的位置

	int			GettexWidth(){ return texWidth; }//得到精灵图片的宽度
	int			GettexHeight(){ return texHeight; }//得到精灵图片的高度
	
	void		Play();										//播放动画精灵
	void		Stop() { bPlaying=false; }					//停止播放
	void		Resume() { bPlaying=true; }					//恢复播放
	bool		IsPlaying() const { return bPlaying; }		//是否在播放

	void		SetMode(int nMode) {this->nMode = nMode;}	//设置动画播放模式
	void		SetFps(int fps) { this->nFps = fps;fInterval=1.0f/fps; }	//设置帧速	
	void		SetFrame(int n);							//设置当前播放帧
	void		SetFrames(int n) { nFrames=n; }				//设置总帧数

	int			GetMode()  { return nMode; }			//得到当前动画模式
	int			GetFps() { return  nFps;}		//得到当前帧数
	int			GetFrame() { return nCurFrame; }		//返回当前帧
	int			GetFrames(){ return nFrames; }			//得到总帧数

	void		Update(float fDeltaTime);				//更新动画

	void        SetTextureStartPos(int tx,int ty);					//设置从精灵图片上开始切割的位置

	bool		CollideWith(CAnimationSprite & sprite);//矩形碰撞

private:

	int			texWidth;								//精灵图片的宽度
	int			texHeight;								//精灵图片的高度

	int         txStart;								//源x
	int         tyStart;								//源y

	bool		bPlaying;								//是否播放

	float		fInterval;									//速度
	float		fSinceLastFrame;						//从上一帧到现在经过了多少毫秒

	int			nMode;									//播放模式
	int			nDelta;									//每次更新多少帧
	int			nFrames;								//总帧数
	int			nFps;									//每秒多少帧
	int			nCurFrame;								//当前帧
};

