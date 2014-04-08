#include "StdAfx.h"
#include "Cube.h"
#include "Vector3.h"
#include "Utils.h"
#include "Texture.h"

CCube::CCube(float size, int i, int j, float dx, float dy,
	GLuint textureId)
	:m_size(size)
	, m_i(i)
	, m_j(j)
	, m_dx(dx)
	, m_dy(dy)
	, m_cubeTexture(textureId)
{
	m_minX = dx - (size * 0.5);
	m_maxX = dx + (size * 0.5);
	m_minY = dy - (size * 0.5);
	m_maxY = dy + (size * 0.5);

	//m_cubeTexture = CUtils::LoadTexture(m_fileName);
}

CCube::~CCube()
{
	/*if (m_cubeTexture)
	{
	glDeleteTextures(1, &m_cubeTexture);
	}*/
}

void CCube::Draw()const
{
	/*

	Y
	|
	|
	|
	+---X
	/
	/
	Z
	3----2
	/    /|
	/    / |
	7----6  |
	|  0 |  1
	|    | /
	|    |/
	4----5
	*/
	// ������ ��������� ������
	static const float vertices[8][3] =
	{
		{ -1, -1, -1 },	// 0
		{ +1, -1, -1 },	// 1
		{ +1, +1, -1 },	// 2
		{ -1, +1, -1 },	// 3
		{ -1, -1, +1 },	// 4
		{ +1, -1, +1 },	// 5
		{ +1, +1, +1 },	// 6
		{ -1, +1, +1 },	// 7
	};

	// ������ ��������� ������ (� �������, ����������� � 
	// �������� ���������� �� � ������� ������)
	// ������� ������ ������ ������������� � ������� �� ������
	// ������ ������� ������� (���� �������� �� ����� �������)
	static const unsigned char faces[6][4] =
	{
		{ 7, 3, 0, 4 },	// ����� x<0
		{ 5, 1, 2, 6 },	// ����� x>0
		{ 4, 0, 1, 5 },	// ����� y<0
		{ 6, 2, 3, 7 },	// ����� y>0
		{ 0, 3, 2, 1 },	// ����� z<0
		{ 4, 5, 6, 7 },	// ����� z>0
	};
	static size_t const faceCount = sizeof(faces) / sizeof(*faces);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_cubeTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glPushMatrix();
	{
		CVector3f p0;
		CVector3f p1;
		CVector3f p2;
		CVector3f p3;

		glTranslated(m_dx, m_dy, 0);

		glBegin(GL_QUADS);
		{
			for (size_t face = 0; face < faceCount; ++face)
			{
				// ������������� ���� �����
				const unsigned char * facePoints = faces[face];

				// �������� ������� ��������� ����� ����
				p0 = vertices[facePoints[0]];
				p1 = vertices[facePoints[1]];
				p2 = vertices[facePoints[2]];
				p3 = vertices[facePoints[3]];
				// ��������� ���������� ������ ���� � ������ ��� �������
				p0 *= m_size * 0.5f;
				p1 *= m_size * 0.5f;
				p2 *= m_size * 0.5f;
				p3 *= m_size * 0.5f;

				// ��������� ������� � ����� ���� �����
				// ��������� ������������ ��� ������� ������
				CVector3f v01 = p1 - p0;
				CVector3f v02 = p2 - p0;
				CVector3f normal = Cross(v01, v02);
				normal.Normalize();

				glNormal3fv(normal);

				// � ������ CVector3f ���������� �������� ���������� � ���� cosnt float*
				// ������� ���������� ��������� ������ ������������
				// glVertex3fv(&p0.x);
				glTexCoord2f(0, 0);
				glVertex3fv(p0);

				glTexCoord2f(0, 1);
				glVertex3fv(p1);

				glTexCoord2f(1, 1);
				glVertex3fv(p2);

				glTexCoord2f(1, 0);
				glVertex3fv(p3);

			}
		}
		glEnd();
	}
	glPopMatrix();
}

bool CCube::IsInsideTheCube(GLdouble x, GLdouble y) const
{
	//if ((x > m_minX) && (x < m_maxX) && (y > m_minY) && (y < m_maxY))

	if ((x >= m_minX - 0.11) && (x <= m_maxX + 0.11) && (y >= m_minY - 0.11) && (y <= m_maxY + 0.11))
		return true;
	return false;
}
