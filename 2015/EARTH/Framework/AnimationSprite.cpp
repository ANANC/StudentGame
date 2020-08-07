#include "AnimationSprite.h"

CAnimationSprite::CAnimationSprite(void)
{
}

CAnimationSprite::~CAnimationSprite(void)
{
}
CAnimationSprite::CAnimationSprite(HDC tex, int nFrames, int nFps, int x, int y, int w, int h,int tx,int ty,int texWidth,int texHeight)
	:CSprite(tex,x,y,w,h)
{
	this->nFrames = nFrames;
	this->nFps = nFps;
	this->texWidth = texWidth;
	this->texHeight = texHeight;
	this->tx = tx;
	this->ty = ty;
	bPlaying = false;
	this->fInterval = 1.0f/nFps;
}

//根据播放模式设置动画播放的初始条件
void CAnimationSprite::Play() 
{
	bPlaying=true;
	fSinceLastFrame=0.0f;
	nDelta = 1;
	SetFrame(0);
}
//根据系统流逝的时间来更新动画
void CAnimationSprite::Update(float fDeltaTime)
{
	if(!bPlaying) 
	{
		return;
	}

	
	fSinceLastFrame += fDeltaTime;
	

	if (fSinceLastFrame >= fInterval)
	{
		fSinceLastFrame = 0.0f;

		SetFrame(nCurFrame+nDelta);
	}
}
//设置当前帧应该取哪幅图片
void CAnimationSprite::SetFrame(int n)
{
	int tx1, ty1;
	
	int ncols = texWidth / width;


	n = n % nFrames;
	

	if(n < 0) n = nFrames + n;
	nCurFrame = n;

	// calculate texture coords for frame n
	ty1 = tyStart;
	tx1 = txStart + n*width;

	if(tx1 > texWidth - width)
	{
		n -= (texWidth -tx) / width;
		tx1 = width * (n%ncols);
		ty1 += height * (1 + n/ncols);
	}

	SetTexturePos(tx1,ty1);
}
void CAnimationSprite::SetTextureStartPos(int tx,int ty)
{
	this->txStart = tx;
	this->tyStart = ty;
}

bool CAnimationSprite::CollideWith(CAnimationSprite &sprite)
{
	RECT rtIntersect;
	return IntersectRect(&rtIntersect, &this->rectSprite, sprite.GetSpriteRect());
}