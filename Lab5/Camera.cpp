#include "Camera.h"
#include "stdafx.h"

CCamera::CCamera()
{
	//�������������� ������ ����� ������� � ������� ����������
	CVector3d vZero = CVector3d(0.0, 0.0, 0.0);
	CVector3d vView = CVector3d(0.0, 1.0, 0.5);     // ����. ������ �������
	CVector3d vUp = CVector3d(0.0, 0.0, 1.0);       // ������������ ������
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

	//�������� ��� ������ ������ ����� ���������� ����������.
	//����� ������ ����� ��������� ���������� ������ ���������� ������� ��������.

	m_vPosition = vPosition;
	m_vView = vView;
	m_vUpVector = vUpVector;
}
void CCamera::MoveCamera(double speed)
{
	//CVector3d vVector = { 0,0,0 };     //����. ������ ����������� �������

	//// �������� ������ �����������. ����� �������� ������ �� 2� 
	//// �����, �� �������� ������ ����� �� ������.
	//// ��� ���� ��� �����������, ���� �� �������. 
	//// ����� �� ������� �-�, ����������� �����������
	//// ��-�������.

	////�������� ����������� ������� (����-�, ���� �� ��������� "�����")
	//vVector.x = m_vView.x - m_vPosition.x;      //����������� �� X
	//vVector.y = m_vView.y - m_vPosition.y;      //����������� �� Y
	//vVector.z = m_vView.z - m_vPosition.z;      //����������� �� Z

	//// ��������� ��� ������� ������ ������ ��� �����.
	//// �� ���������� � �������� ��������� ����������� �������, ����������� �� ��������.
	//// ����� ����, �� �������, ��� ����� ���� �� ������ ��������� � ������� ��������. ��,
	//// ������ ��� ��������� - �� �������� ����� �� ��� �. �� ��� ������ �������� ��������, ���
	//// ���������� �����������. �������� ���.
	//// ����, ���� �� ������� � ����������� 45 ��������, �� � ������ � ���� �����������.
	//// ���� �������� ����� - ������ ������� � �-� ������������� ��������.

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

	// ������� ��� ������ ������� (�����������, ���� �� �������)
	vView.x = m_vView.x - m_vPosition.x;    //����������� �� X
	vView.y = m_vView.y - m_vPosition.y;    //����������� �� Y
	vView.z = m_vView.z - m_vPosition.z;    //����������� �� Z

	// ������, ���� ������ �������, ���������� � CVector3 "vView", �� ����� ������� ���.
	// ��� �-� ����� ���������, ����� ����� ���������� ������-�������.
	// ����, ��� ����� ��������� ������ ����� �������. ����������� ��� �������� ���:
	// ������, �� ����� �� �����, ������ ������. �� ������� � �����-�� �����, �����?
	// ������, ���� �� �������� ������ ������ ��� �������, ����������� ������� ���������.
	// �������������� ������������ �����, �� ������� �� ������� (������ �������).
	// ��� ������ �� �������� m_vView - ������ ��� ��� � ���� ������ 
	// �������. �� ����� ������� m_vView ������ m_vPosition
	// �� �����, ����� ����������� �� ���.
	// ����� ������� ���-��, ���������� ����� � �������. ��� ������������� sin() & cos() ��
	// ����� ���������� math.h.
	//
	// ����� ����������� �������� ������, �� ����� ������������ axis-angle ��������.
	// � ������ ������������, ��� ������� ��� �������� �������� �� ����� ������, ��
	// �������� �� ����� ����. Axis-angle �������� ��������� ��� ������� ����� � ������������
	// ������ ������ ���. ��� ������, ��� �� ����� ����� ���� ����� ������� (m_vView) �
	// ������� ������ ����� �������.
	// ����� ����� ������ ��������� ��������, ������� ��� ���������� ���������
	// ��������: http://astronomy.swin.edu.au/~pbourke/geometry/rotate/

	// ���������� 1 ��� ����� � ������� ����������� ����
	double cosTheta =  cos(angle);
	double sinTheta =  sin(angle);

	// ������ ����� ������� X ��� ��������� �����
	vNewView.x = (cosTheta + (1 - cosTheta) * x * x)   * vView.x;
	vNewView.x += ((1 - cosTheta) * x * y - z * sinTheta)   * vView.y;
	vNewView.x += ((1 - cosTheta) * x * z + y * sinTheta)   * vView.z;

	// ������ ������� Y
	vNewView.y = ((1 - cosTheta) * x * y + z * sinTheta)   * vView.x;
	vNewView.y += (cosTheta + (1 - cosTheta) * y * y)   * vView.y;
	vNewView.y += ((1 - cosTheta) * y * z - x * sinTheta)   * vView.z;

	// � ������� Z
	vNewView.z = ((1 - cosTheta) * x * z - y * sinTheta)   * vView.x;
	vNewView.z += ((1 - cosTheta) * y * z + x * sinTheta)   * vView.y;
	vNewView.z += (cosTheta + (1 - cosTheta) * z * z)   * vView.z;

	// ������ ������ ������� ����� ������ �������� � ����� �������, �����
	// ���������� ����� ������ ������.
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
