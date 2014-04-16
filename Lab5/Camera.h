#pragma once 
#include "Vector3.h"
class CCamera 
{
public:
	CCamera();

	void PositionCamera(double positionX, double positionY, double positionZ,
		double viewX, double viewY, double viewZ,
		double upVectorX, double upVectorY, double upVectorZ);

	void MoveCamera(double speed);

	void Look();




	void RotateView(double angle, double x, double y, double z);

	CVector3d m_vPosition;	// Позиция камеры.
	CVector3d m_vView;	// Направление камеры.
	CVector3d m_vUpVector;	// Вертикальный вектор.

};