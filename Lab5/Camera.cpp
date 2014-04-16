#include "Camera.h"
#include "stdafx.h"

CCamera::CCamera()
{
	//Инициализируем вектор нашей позиции в нулевые координаты
	CVector3d vZero = CVector3d(0.0, 0.0, 0.0);
	CVector3d vView = CVector3d(0.0, 1.0, 0.5);     // Иниц. вектор взгляда
	CVector3d vUp = CVector3d(0.0, 0.0, 1.0);       // Вертикальный вектор
	m_vPosition = vZero;
	m_vView = vView;
	m_vUpVector = vUp;
}


void CCamera::PositionCamera(double positionX, double positionY, double positionZ,
	double viewX, double viewY, double viewZ,
	double upVectorX, double upVectorY, double upVectorZ)
{
	CVector3d vPosition = CVector3d(positionX, positionY, positionZ);
	CVector3d vView = CVector3d(viewX, viewY, viewZ);
	CVector3d vUpVector = CVector3d(upVectorX, upVectorY, upVectorZ);

	//Обширный код просто делает легче назначение переменных.
	//Можно просто сразу присвоить переменным класса переданные функции значения.

	m_vPosition = vPosition;
	m_vView = vView;
	m_vUpVector = vUpVector;
}
void CCamera::MoveCamera(double speed)
{
	//CVector3d vVector = { 0,0,0 };     //Иниц. вектор направления взгляда

	//// Получаем вектор направления. Чтобы получить вектор из 2х 
	//// точек, мы вычитаем первую точку из второй.
	//// Это дает нам направление, куда мы смотрим. 
	//// Позже мы напишем ф-ю, вычисляющую направление
	//// по-другому.

	////Получаем направление взгляда (напр-е, куда мы повернуты "лицом")
	//vVector.x = m_vView.x - m_vPosition.x;      //Направление по X
	//vVector.y = m_vView.y - m_vPosition.y;      //Направление по Y
	//vVector.z = m_vView.z - m_vPosition.z;      //Направление по Z

	//// Следующий код двигает камеру вперед или назад.
	//// Мы прибавляем к текущему положению направление взгляда, помноженное на скорость.
	//// Может быть, вы думаете, что проще было бы просто прибавить к позиции скорость. Да,
	//// сейчас это сработает - вы смотрите прямо по оси Х. Но как только начнется вращение, код
	//// перестанет действовать. Поверьте мне.
	//// Итак, если мы смотрим в направлении 45 градусов, мы и пойдем в этом направлении.
	//// Если движемся назад - просто передаём в ф-ю отрицательную скорость.

	//m_vPosition.x += vVector.x * speed;
	//m_vPosition.z += vVector.z * speed;
	//m_vView.x += vVector.x * speed;
	//m_vView.y += vVector.z * speed;

	CVector3d vVector = m_vView - m_vPosition;

	m_vPosition.x += vVector.x * speed;
	m_vPosition.z += vVector.z * speed;
	m_vView.x += vVector.x * speed;
	m_vView.z += vVector.z * speed;

}

void CCamera::RotateView(double angle, double x, double y, double z)
{
	CVector3d vNewView;
	CVector3d vView;

	// Получим наш вектор взгляда (направление, куда мы смотрим)
	vView.x = m_vView.x - m_vPosition.x;    //направление по X
	vView.y = m_vView.y - m_vPosition.y;    //направление по Y
	vView.z = m_vView.z - m_vPosition.z;    //направление по Z

	// Теперь, имея вектор взгляда, хранящийся в CVector3 "vView", мы можем вращать его.
	// Эта ф-я будет вызыватся, когда нужно повернутся налево-направо.
	// Итак, нам нужно вращаться вокруг нашей позиции. Представьте это примерно так:
	// скажем, мы стоим на месте, смотря вперед. Мы смотрим в какую-то точку, верно?
	// Теперь, если мы повернем голову налево или направо, направление взгляда изменится.
	// Соответственно переместится точка, на которую мы смотрим (вектор взгляда).
	// Вот почему мы изменяем m_vView - потому что это и есть вектор 
	// взгляда. Мы будем вращать m_vView вокруг m_vPosition
	// по кругу, чтобы реализовать всё это.
	// Чтобы вращать что-то, используем синус и косинус. Для использования sin() & cos() мы
	// ранее подключили math.h.
	//
	// Чтобы реализовать вращение камеры, мы будем использовать axis-angle вращение.
	// Я должен предупредить, что формулы для рассчета вращения не очень просты, но
	// занимают не много кода. Axis-angle вращение позволяет нам вращать точку в пространстве
	// вокруг нужной оси. Это значит, что мы можем взять нашу точку взгляда (m_vView) и
	// вращать вокруг нашей позиции.
	// Чтобы лучше понять следующие рассчеты, советую вам посмотреть детальное
	// описание: http://astronomy.swin.edu.au/~pbourke/geometry/rotate/

	// Рассчитаем 1 раз синус и косинус переданного угла
	double cosTheta =  cos(angle);
	double sinTheta =  sin(angle);

	// Найдем новую позицию X для вращаемой точки
	vNewView.x = (cosTheta + (1 - cosTheta) * x * x)   * vView.x;
	vNewView.x += ((1 - cosTheta) * x * y - z * sinTheta)   * vView.y;
	vNewView.x += ((1 - cosTheta) * x * z + y * sinTheta)   * vView.z;

	// Найдем позицию Y
	vNewView.y = ((1 - cosTheta) * x * y + z * sinTheta)   * vView.x;
	vNewView.y += (cosTheta + (1 - cosTheta) * y * y)   * vView.y;
	vNewView.y += ((1 - cosTheta) * y * z - x * sinTheta)   * vView.z;

	// И позицию Z
	vNewView.z = ((1 - cosTheta) * x * z - y * sinTheta)   * vView.x;
	vNewView.z += ((1 - cosTheta) * y * z + x * sinTheta)   * vView.y;
	vNewView.z += (cosTheta + (1 - cosTheta) * z * z)   * vView.z;

	// Теперь просто добавим новый вектор вращения к нашей позиции, чтобы
	// установить новый взгляд камеры.
	m_vView.x = m_vPosition.x + vNewView.x;
	m_vView.y = m_vPosition.y + vNewView.y;
	m_vView.z = m_vPosition.z + vNewView.z;
}
void CCamera::Look()
{
	glLoadIdentity();
	gluLookAt(
		m_vPosition.x, m_vPosition.y, m_vPosition.z,
		m_vView.x, m_vView.y, m_vView.z,
		m_vUpVector.x, m_vUpVector.y, m_vUpVector.z);
}
