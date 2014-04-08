#pragma once

#include "Cube.h"

class CLabyrinthMap
{
public:
	CLabyrinthMap(float minX, float maxX, float minY, float maxY,
		std::wstring const& fileName1,
		std::wstring const& fileName2,
		std::wstring const& fileName3,
		std::wstring const& fileName4,
		std::wstring const& fileName5,
		std::wstring const& fileName6);
	~CLabyrinthMap();
	void DrawLabyrinth() const;
	bool IsBarrier(GLdouble x, GLdouble y) const;
private:
	std::vector<CCube> m_cubes;
	float m_minX;
	float m_maxX;
	float m_minY;
	float m_maxY;
	static const char M_MAP[16][16];
	static const float SIZE;

	std::wstring m_fileName1;
	std::wstring m_fileName2;
	std::wstring m_fileName3;
	std::wstring m_fileName4;
	std::wstring m_fileName5;
	std::wstring m_fileName6;

	std::vector<GLuint> m_textureIds;
};
