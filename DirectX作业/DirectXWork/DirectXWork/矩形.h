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
	RECT TexRc;//�������
	RECT PosRc;//λ�þ���
	POINT Pos;//λ��
	POINT TexPos;//����λ��
	int Width;//��
	int Height;//��
	int PosMove;//λ�õı�����

public:
	//�����������λ��
	void  SetTexRc();

	//����������λ��
	POINT GetTex();

	//��������λ��
	void SetTexPos(POINT p);
	
	//�õ��������
	RECT GetTexRc(){ return TexRc; }

	//����λ��
	void SetPos(POINT p);

	//�޸�λ�þ���
	void SetPosRc();

	//�õ�λ�þ���
	RECT GetPosRc(){ return PosRc; }

	//���λ�þ���
	POINT GetPos();

	//�޸Ŀ�͸�
	void SetWidthOrHeight(int w, int h);

	//�õ���
	int GetWidth(){ return Width; }

	//�õ���
	int GetHeight(){ return Height; }

	//�Ƿ������
	BOOL IsClick(POINT pt);

	//���������κ�λ�þ����Ƿ����
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
