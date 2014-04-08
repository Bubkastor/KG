#pragma once

class CCube
{
public:
	CCube(float size, int i, int j, float dx, float dy,
		GLuint textureId);

	~CCube();

	void Draw()const;

	bool IsInsideTheCube(GLdouble x, GLdouble y) const;

private:
	GLfloat m_dx;
	GLfloat m_dy;

	GLdouble m_minX;
	GLdouble m_maxX;
	GLdouble m_minY;
	GLdouble m_maxY;

	int m_i;
	int m_j;

	float m_size;

	GLuint m_cubeTexture;
};
