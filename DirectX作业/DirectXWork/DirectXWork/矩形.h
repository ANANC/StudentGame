#include <windows.h>
using namespace std;

class Ju
{
public:
	Ju(POINT p, POINT tp, int w, int h,int M = 0)
	{
		Pos= p;
		TexPos = tp;
		Width = w;
		Height = h;
		PosMove = M;
		SetTexRc();
		SetPosRc();
	}

private:
	RECT TexRc;//纹理矩形
	RECT PosRc;//位置矩形
	POINT Pos;//位置
	POINT TexPos;//纹理位置
	int Width;//宽
	int Height;//高
	int PosMove;//位置的便宜量

public:
	//计算纹理矩形位置
	void  SetTexRc();

	//输出纹理矩形位置
	POINT GetTex();

	//设置纹理位置
	void SetTexPos(POINT p);
	
	//得到纹理矩形
	RECT GetTexRc(){ return TexRc; }

	//设置位置
	void SetPos(POINT p);

	//修改位置矩形
	void SetPosRc();

	//得到位置矩形
	RECT GetPosRc(){ return PosRc; }

	//输出位置矩形
	POINT GetPos();

	//修改宽和高
	void SetWidthOrHeight(int w, int h);

	//得到宽
	int GetWidth(){ return Width; }

	//得到高
	int GetHeight(){ return Height; }

	//是否鼠标点击
	BOOL IsClick(POINT pt);

	//检测纹理矩形和位置矩形是否相等
	BOOL IsEquality();

};

void Ju::SetTexRc()
{
	TexRc.left = TexPos.x;
	TexRc.top = TexPos.y;
	TexRc.right = TexRc.left + Width;
	TexRc.bottom = TexRc.top + Height;
}

POINT Ju::GetTex()
{
	return TexPos;
}

void Ju::SetTexPos(POINT p)
{
	TexPos = p;
	SetTexRc();
}

void Ju::SetPos(POINT p)
{
	Pos = p;
	SetPosRc();
}

void Ju::SetPosRc()
{
	PosRc.left = Pos.x;
	PosRc.top = Pos.y;
	PosRc.right = PosRc.left + Width;
	PosRc.bottom = PosRc.top + Height;
}

POINT Ju::GetPos()
{
	return Pos;
}

void Ju::SetWidthOrHeight(int w, int h)
{
	if (w == 0)
		Height = h;
	else if(h == 0)
		Width = w;
	else
	{
		Width = w; Height = h;
	}
	SetTexRc();
	SetPosRc();
}

BOOL Ju::IsClick(POINT pt)
{
	if (pt.x >= PosRc.left && pt.x <= PosRc.right)
	{
		if (pt.y >= PosRc.top && pt.y <= PosRc.bottom)
		{
			return true;
		}
	}
	return false;
}

BOOL Ju::IsEquality()
{
	if (Pos.x - PosMove == TexPos.x && Pos.y - PosMove == TexPos.y)
		return true;
	else
		return false;
}
