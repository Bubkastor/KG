#pragma once

template <class T>
class CVector3
{
public:
	T x, y, z;

	CVector3(void)
		:x(0), y(0), z(0)
	{
	}

	explicit CVector3(const T * p)
		:x(p[0]), y(p[1]), z(p[2])
	{
	}

	CVector3(T x0, T y0, T z0)
		:x(x0), y(y0), z(z0)
	{
	}

	operator T const*()const
	{
		return &x;
	}

	void operator = (const T * p)
	{
		x = p[0];
		y = p[1];
		z = p[2];
	}

	CVector3 & operator *= (T scale)
	{
		x *= scale;
		y *= scale;
		z *= scale;
		return *this;
	}


	CVector3 operator*(float num)
	{
		return CVector3(x*num, y*num, z*num);
	}

	CVector3 operator/(float num)
	{
		return CVector3(x / num, y / num, z / num);
	}

	CVector3  operator-(CVector3 const& v)const
	{
		return CVector3(x - v.x, y - v.y, z - v.z);
	}

	CVector3 operator+(CVector3 vVector)
	{
		// ���������� +����������� ������
		return CVector3(vVector.x + x, vVector.y + y, vVector.z + z);
	}

	float Magnitude(CVector3 vNormal)
	{
		return (float) sqrt((vNormal.x * vNormal.x) +
			(vNormal.y * vNormal.y) +
			(vNormal.z * vNormal.z));
	}


	T GetLength()const
	{
		return static_cast<T>(sqrt(x * x + y * y + z * z));
	}

	// �����������
	void Normalize()
	{
		float invLength = 1 / GetLength();
		x *= invLength;
		y *= invLength;
		z *= invLength;
	}

	CVector3 Cross(CVector3 vVector1, CVector3 vVector2)
	{
		CVector3 vNormal;

		// ���� � ��� ���� 2 ������� (������ ������� � ������������ ������), 
		// � ��� ���� ���������, �� ������� �� ����� ��������� ���� � 90 ��������.
		// ������� cross'a �����, �� ��� ������ ��������� � ������� ����. 
		// �������� X ��� ������� - (V1.y * V2.z) - (V1.z * V2.y)
		vNormal.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));

		// �������� Y - (V1.z * V2.x) - (V1.x * V2.z)
		vNormal.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));

		// �������� Z: (V1.x * V2.y) - (V1.y * V2.x)
		vNormal.z = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));

		// *�����* �� �� ������ ������ ���� �������, ����� ������ �� ����� ��������.
		// ������ ���� ������ ���, ��� �����. ������ ���������, ���� �� ����� �, �� ��
		// ����������� �������� X ���� ��������, � �� �� ����� ��� Y � Z. ��������,
		// �� ������������� �������� �� ���� ������ ����, � ������� �� ��� �� �����.

		// ����, ����� �� ���? ��� ����� ����� ���, ������ ������� ���������. �������� ������
		// ����� � ������ ������� - ������������ ��� ������ (0,1,0). 
		// �������� ������ ����� � ���� ����������, ��� ��� ��� ���������� ��� 
		// ���������� ����. ��������� ���� ����� �� �������� �������, ���� � ��� 
		// � ��� ���, ��� ��� ����������.

		// ������ ���������.
		return vNormal;
	}
};


// ��������� ��������� ������������ a � b
template <class T>
CVector3<T> const Cross(CVector3<T> const & a, CVector3<T> const & b)
{
	/*
	��������� ������������ �������� A � B ����� ������������ �������:
	|i  j  k |
	AxB = |Ax Ay Az|
	|Bx By Bz|
	*/
	return CVector3<T>(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x);

}




typedef CVector3<float> CVector3f;
typedef CVector3<double> CVector3d;
