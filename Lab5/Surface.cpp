#include "StdAfx.h"
#include "Surface.h"

CSurface::CSurface(int columns, int rows, float xMin, float xMax, float yMin, float yMax)
:m_rows(rows)
, m_columns(columns)
, m_xMin(xMin)
, m_xMax(xMax)
, m_yMin(yMin)
, m_yMax(yMax)
, m_displayList(0)
{
}

void CSurface::Draw(double z, GLubyte r, GLubyte g, GLubyte b)const
{

	glColor3ub(r, g, b);
	// вычисляем шаг узлов сетки
	const float dy = (m_yMax - m_yMin) / (m_rows - 1);
	const float dx = (m_xMax - m_xMin) / (m_columns - 1);

	float y = m_yMin;

	for (int row = 0; row < m_rows - 1; ++row, y += dy)
	{
		glBegin(GL_QUAD_STRIP);//GL_TRIANGLE_STRIP
		float x = m_xMin;

		for (int column = 0; column <= m_columns; ++column, x += dx)
		{
			glNormal3f(0, 0, ((z < 0) ? 1 : -1));
			glVertex3f(x, y + dy, z);

			glNormal3f(0, 0, ((z < 0) ? 1 : -1));
			glVertex3f(x, y, z);
		}
		glEnd();
	}
}

Vertex CSurface::CalculateVertex(double x, double y, double z)const
{
	Vertex result =
	{
		float(x), float(y), float(z),
		0, 0, (z < 0) ? 1 : -1
	};
	return result;
}

// Не забыли удалить дисплейный список при разрушении экземпляра класса
CSurface::~CSurface(void)
{
	if (m_displayList != 0)
	{
		glDeleteLists(m_displayList, 1);
	}
}
