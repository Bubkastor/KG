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
		// Возвращаем +добавленный вектор
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

	// Нормализуем
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

		// Если у нас есть 2 вектора (вектор взгляда и вертикальный вектор), 
		// у нас есть плоскость, от которой мы можем вычислить угол в 90 градусов.
		// Рассчет cross'a прост, но его сложно запомнить с первого раза. 
		// Значение X для вектора - (V1.y * V2.z) - (V1.z * V2.y)
		vNormal.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));

		// Значение Y - (V1.z * V2.x) - (V1.x * V2.z)
		vNormal.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));

		// Значение Z: (V1.x * V2.y) - (V1.y * V2.x)
		vNormal.z = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));

		// *ВАЖНО* Вы не можете менять этот порядок, иначе ничего не будет работать.
		// Должно быть именно так, как здесь. Просто запомните, если вы ищите Х, вы не
		// используете значение X двух векторов, и то же самое для Y и Z. Заметьте,
		// вы рассчитываете значение из двух других осей, и никогда из той же самой.

		// Итак, зачем всё это? Нам нужно найти ось, вокруг которой вращаться. Вращение камеры
		// влево и вправо простое - вертикальная ось всегда (0,1,0). 
		// Вращение камеры вверх и вниз отличается, так как оно происходит вне 
		// глобальных осей. Достаньте себе книгу по линейной алгебре, если у вас 
		// её ещё нет, она вам пригодится.

		// вернем результат.
		return vNormal;
	}
};


// Вычисляем векторное произведение a и b
template <class T>
CVector3<T> const Cross(CVector3<T> const & a, CVector3<T> const & b)
{
	/*
	Векторное произведение векторов A и B равно определителю матрицы:
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
