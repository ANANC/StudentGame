#pragma once
#include <math.h>

class Vector2D
{
private:
	double x, y;
public:
	Vector2D(float X = 0, float Y = 0)
	{
		x = X;y = Y;
	}
	~Vector2D() {} 	

	Vector2D operator*(float scalar) const
	{
		return Vector2D(x * scalar, y * scalar);
	}
	Vector2D operator+(const Vector2D &vect) const
	 {
		 return Vector2D(x + vect.x, y + vect.y);
	}
	Vector2D operator-(const Vector2D &vect) const
	  {
		  return Vector2D(x - vect.x, y - vect.y);
	}
	//��ת����
	void rotate(float angle)
	{
		float xt = (x * cosf(angle)) - (y * sinf(angle));
		float yt = (y * cosf(angle)) + (x * sinf(angle));
		x = xt;
		y = yt;
	}
		
	//ȡ�ô�ֱ����
	Vector2D getNormal()
	{
		return Vector2D(-y,x);
	}
	//ȡģ,�õ������Ĵ�С
	float magnitude()
	{
		return sqrtf(x * x +y * y);
	}
	//��λ������
	void normalise()
	{
		double mag = sqrtf(x* x + y * y);
		this->x = x / mag;
		this->y = y / mag;
	}
	//������
	double dotproduct(const Vector2D &vect) const
	{
		return (x * vect.x) + (y * vect.y);
	}
	//������
	float crossproduct(const Vector2D &vect2) const
	{
		return (this->x * vect2.y) - (this->y * vect2.x);
	}
	double GetX(){ return x; }
	double GetY(){ return y; }
	//���λ��
	void SetPos(const int x, const int y)
	{
		this->x = x;
		this->y = y;
	}
};
