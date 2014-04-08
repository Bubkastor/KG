#include "StdAfx.h"
#include "MyApplication.h"
#include "Vector3.h"

const float M_PI = 3.14159265358979323846f;
const double CMyApplication::FOV = 60;
const double CMyApplication::ZNEAR = 1;
const double CMyApplication::ZFAR = 100;
const float CMyApplication::ROTATION_SPEED = 20;
const double CMyApplication::DELTA = 0.1;


CMyApplication::CMyApplication(const char *title, int width, int height)
:CGLApplication(title, width, height)
, m_skyBox(
L"images/Galaxy_LT.png",
L"images/Galaxy_RT.png",
L"images/Galaxy_DN.png",
L"images/Galaxy_UP.png",
L"images/Galaxy_BK.png",
L"images/Galaxy_FT.png"
)
//,m_light(CVector3f(0, 10, 0))
, m_surface(100, 100, -16, 15, -16, 16)
, m_labyrinth(-16, 15, -16, 16,
L"images/brickTexture1.jpg",
L"images/brickTexture2.jpg",
L"images/brickTexture3.jpg",
L"images/brickTexture4.jpg",
L"images/brickTexture5.jpg",
L"images/rockTexture1.jpg")
, m_angle(0)
, m_polygonMode(GL_FILL)
{
	//m_light.SetDiffuseIntensity(1, 1, 1);
	//m_light.SetSpecularIntensity(1, 1, 1);

	m_eyex = -10;	m_eyey = -15;	m_eyez = 0;
	m_centerx = m_eyex + (DELTA * cos(0.0));
	m_centery = m_eyey + (DELTA * sin(0.0));
	m_centerz = 0;
}

CMyApplication::~CMyApplication(void)
{
}

void CMyApplication::OnInit()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(1, 1, 1, 1);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
}

void CMyApplication::OnIdle()
{
	// Если приложению нечем заняться - то обонвляем экран
	PostRedisplay();
}

void CMyApplication::SetupCamera()
{
	// Устанавливаем камеру
	glLoadIdentity();
	gluLookAt(
		m_eyex, m_eyey, m_eyez,
		m_centerx, m_centery, m_centerz,
		0, 0, 1);
}

void CMyApplication::OnDisplay(void)
{
	// Очищаем буфер цвета и буфер глубины
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetupCamera();

	glEnable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, m_polygonMode);
	DrawSkyBox();
	m_surface.Draw(-1, 122, 123, 115);
	glDisable(GL_TEXTURE_2D);

	m_labyrinth.DrawLabyrinth();
}

void CMyApplication::OnReshape(int width, int height)
{
	// Настраиваем порт просмотра
	glViewport(0, 0, width, height);

	double aspect = double(width) / double(height);
	// Делаем текущей матрицу проецирования и настраиваем ее параметры
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FOV, aspect, ZNEAR, ZFAR);
	// Делаем текущей матрицей матрицу моделирования-вида
	glMatrixMode(GL_MODELVIEW);
}

//void CMyApplication::OnSpecialHadler(int key, int x, int y)
void CMyApplication::OnKeyboard(unsigned char key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		m_angle += (DELTA_ANGLE * M_PI) / 180;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		m_angle -= (DELTA_ANGLE * M_PI) / 180;
	}
	else if (key == GLUT_KEY_UP)
	{
		GLdouble tempEyeX = m_eyex + (DELTA * cos(m_angle));
		GLdouble tempEyeY = m_eyey + (DELTA * sin(m_angle));
		if (!m_labyrinth.IsBarrier(tempEyeX, tempEyeY))
		{
			m_eyex = tempEyeX;
			m_eyey = tempEyeY;
		}
	}
	else if (key == GLUT_KEY_DOWN)
	{
		GLdouble tempEyeX = m_eyex - (DELTA * cos(m_angle));
		GLdouble tempEyeY = m_eyey - (DELTA * sin(m_angle));
		if (!m_labyrinth.IsBarrier(tempEyeX, tempEyeY))
		{
			m_eyex = tempEyeX;
			m_eyey = tempEyeY;
		}
	}

	m_centerx = m_eyex + (DELTA * cos(m_angle));
	m_centery = m_eyey + (DELTA * sin(m_angle));

	PostRedisplay();
}

void CMyApplication::DrawSkyBox()const
{
	glDisable(GL_LIGHTING);
	// Отключим режим отбраковки граней, т.к. 
	// мы находимся внутри куба и видим его нелицевую сторону
	glDisable(GL_CULL_FACE);
	m_skyBox.Draw();
}

