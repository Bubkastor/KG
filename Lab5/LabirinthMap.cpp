#include "StdAfx.h"
#include "LabyrinthMap.h"
#include "Utils.h"

const char CLabyrinthMap::M_MAP[16][16] =
{
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1 },
	{ 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1 },
	{ 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1 },
	{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
	{ 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
	{ 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },

	/*
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	//*/
};

const float CLabyrinthMap::SIZE = 2;


CLabyrinthMap::CLabyrinthMap(float minX, float maxX, float minY, float maxY,
	std::wstring const& fileName1,
	std::wstring const& fileName2,
	std::wstring const& fileName3,
	std::wstring const& fileName4,
	std::wstring const& fileName5,
	std::wstring const& fileName6)
	:m_minX(minX)
	, m_maxX(maxX)
	, m_minY(minY)
	, m_maxY(maxY)
	, m_fileName1(fileName1)
	, m_fileName2(fileName2)
	, m_fileName3(fileName3)
	, m_fileName4(fileName4)
	, m_fileName5(fileName5)
	, m_fileName6(fileName6)
{
	m_textureIds.push_back(CUtils::LoadTexture(m_fileName1));
	m_textureIds.push_back(CUtils::LoadTexture(m_fileName2));
	m_textureIds.push_back(CUtils::LoadTexture(m_fileName3));
	m_textureIds.push_back(CUtils::LoadTexture(m_fileName4));
	m_textureIds.push_back(CUtils::LoadTexture(m_fileName5));
	m_textureIds.push_back(CUtils::LoadTexture(m_fileName6));

	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 16; ++j)
		{
			if (M_MAP[i][j] == 1)
			{
				float dx, dy;

				dx = (m_minX + (j * 2)) + (SIZE * 0.5);
				dy = (m_maxY - (i * 2)) - (SIZE * 0.5);

				GLuint textureId = 0;
				if (j == 0)
					textureId = m_textureIds[0];
				else if (i == 0)
					textureId = m_textureIds[1];
				else if (j == 15)
					textureId = m_textureIds[2];
				else if (i == 15)
					textureId = m_textureIds[3];
				else if (i < 8)
					textureId = m_textureIds[4];
				else
					textureId = m_textureIds[5];

				CCube cube(SIZE, i, j, dx, dy, textureId);
				m_cubes.push_back(cube);
			}
		}
	}
}

CLabyrinthMap::~CLabyrinthMap()
{
	for (int i = 0; i < static_cast<int>(m_textureIds.size()); ++i)
	{
		if (m_textureIds[i])
		{
			glDeleteTextures(1, &m_textureIds[i]);
		}
	}
}

void CLabyrinthMap::DrawLabyrinth() const
{
	for (int i = 0; i < static_cast<int>(m_cubes.size()); ++i)
	{
		m_cubes[i].Draw();
	}
}

bool CLabyrinthMap::IsBarrier(GLdouble x, GLdouble y) const
{
	bool result = false;
	for (int i = 0; i < static_cast<int>(m_cubes.size()); ++i)
	{
		result = m_cubes[i].IsInsideTheCube(x, y);
		if (result)
			break;
	}
	return result;
}

