#include "StdAfx.h"
#include "MyApplication.h"
#include "Vector3.h"

#define kSpeed  5.0

const float M_PI = 3.14159265358979323846f;
const double CMyApplication::FOV = 60;    //���� ������ ������
const double CMyApplication::ZNEAR = 0.1; // ��������� �� �� �����
const double CMyApplication::ZFAR = 100;  // ��������� �� ����� �� �������� ������� �����������
const int CMyApplication::ROTATION_SPEED = 2;
const double CMyApplication::DELTA = 0.1;

CMyApplication::CMyApplication(const char *title, int width, int height)
:CGLApplication(title, width, height)
, m_skyBox(
L"images/lf.bmp",
L"images/rt.bmp",
L"images/dn.bmp",
L"images/up.bmp",
L"images/bk.bmp",
L"images/ft.bmp"
)

, m_light(CVector3f(0, 10, 0))
, m_surface(250, 250, -16, 15, -16, 16)
, m_labyrinth(-16, 15, -16, 16,
L"images/brickTexture1.jpg",
L"images/brickTexture1.jpg",
L"images/brickTexture1.jpg",
L"images/brickTexture1.jpg",
L"images/brickTexture1.jpg",
L"images/brickTexture1.jpg")
, m_angle(0)
, m_polygonMode(GL_FILL)
, m_anglez(0)
, m_FPS(0)
, m_FrameInterval(0)
{
	m_fog = false;
	m_skyBoxb = false;
	m_mouse = true;
	

	m_camera.m_vPosition.x = 0;	m_camera.m_vPosition.y = 0;	m_camera.m_vPosition.z = 0;
	//gluLookAt(
	//	x, y + height, z,
	//	x - sin(angleX / 180 * PI), y + height + (tan(angleY / 180 * PI)), z - cos(angleX / 180 * PI)
	//	, 0, 1, 0);
	//m_camera.m_vView.x = m_camera.m_vPosition.x + (DELTA * cos(0.0));
	m_camera.m_vView.x = m_camera.m_vPosition.x - sin(DELTA / 180 * M_PI) ;
	//m_camera.m_vView.y = m_camera.m_vPosition.y + (DELTA * sin(0.0));
	m_camera.m_vView.y = m_camera.m_vPosition.y -cos(DELTA /180 *M_PI);
	m_camera.m_vView.z = m_camera.m_vPosition.z + (tan(DELTA / 180 * M_PI));

	m_camera.PositionCamera(
		m_camera.m_vPosition.x, m_camera.m_vPosition.y, m_camera.m_vPosition.z ,
		m_camera.m_vView.x, m_camera.m_vView.y, m_camera.m_vView.z,
		0, 0, 1);
}

CMyApplication::~CMyApplication(void)
{
} 

void CMyApplication::CalculateFrameRate()
{
	//���� �� �������� ��������� ��������� ����������, �.�. �����, ����� ��� ��������� ���
	//�������� ����� ���������� ������ �-��. �� ����� �� ������� �� �����������, �� ��� �����
	//��������.

	static float framesPerSecond = 0.0f;    //���� ���
	static float lastTime = 0.0f;           //��� �������� �����, ��������� � ���������� �����
	static char strFrameRate[50] = { 0 };     //������ ��� ������

	//��� �� �������� ������� tick count � �������� ��� �� 0.001 ��� ����������� �� ����������� � �������.
	float currentTime = timeGetTime() * 0.001f;

	//����������� ������� ������
	++framesPerSecond;

	//������ ������ �� �������� ������� ��������� ����������� �����. ���� ��������� ������ �������,
	//��� ������, ��� ������� ������ � ����� ������� ����� FPS.
	if (currentTime - lastTime > 1.0f)
	{
		//������������� lastTime � ������� �����. ������ ��� ����� ������������� ��� ���������� �����
		//��� ����. �������.
		lastTime = currentTime;

		// ��������� FPS ��� ������:
		m_FPS = framesPerSecond;

		//������� FPS
		framesPerSecond = 0;
	}
}

void CMyApplication::GetFrameTime()
{
	static float frameTime = 0.0f;  // ����� ���������� �����

	float currentTime = timeGetTime() * 0.001f;

	// �������� �������, ���������� � �������� �����
	m_FrameInterval = currentTime - frameTime;

	frameTime = currentTime;
}

void CMyApplication::OnInit()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	ShowCursor(false);
}


void CMyApplication::OnIdle()
{
	// ���� ���������� ����� �������� - �� ��������� �����
	PostRedisplay();
}

void CMyApplication::SetupLight()
{
	glEnable(GL_LIGHT1);
	GLfloat light3_diffuse[] = { 1, 1, 1 };
	GLfloat light3_ambel[] = { 1, 1, 1 };
	GLfloat light3_specular[] = { 1, 1, 1 };
	GLfloat light3_position[] = { m_camera.m_vPosition.x, m_camera.m_vPosition.y, m_camera.m_vPosition.z, 1 }; //(x, y, z, w) ����������� ��������� ������������� �����
	GLfloat light3_spot_direction[] = { m_camera.m_vView.x, m_camera.m_vView.y, m_camera.m_vView.z }; //(x, y, z) - ����������� ���������� (��� ��������������� ������)

	glLightfv(GL_LIGHT1, GL_SPECULAR, light3_specular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light3_ambel);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light3_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light3_position);
	//glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light3_spot_direction);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30); //���� ����� ���� � �������� ������ (�� �� �������� ���� ��� �������)
}

void CMyApplication::OnDisplay(void)
{
	// ������� ����� ����� � ����� �������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	CalculateFrameRate();
	GetFrameTime();
	std::cout << m_FPS<< '\n';
	m_light.SetPosition(m_camera.m_vPosition);

	if (m_fog)
	{
		glEnable(GL_FOG);
	}
	else
	{
		glDisable(GL_FOG);
	}

	 //������ ����� ������
	glFogi(GL_FOG_MODE, GL_EXP2);

	 //������ ���� ������
	float fogColor[4] = { 0, 0, 0, 0 };
	glFogfv(GL_FOG_COLOR, fogColor);

	// � ��� ���������
	glFogf(GL_FOG_DENSITY, 0.2);

	m_camera.Look();
	if (m_mouse)
	{
		glutWarpPointer(m_width / 2, m_height / 2);

	}

	glEnable(GL_LIGHTING);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_NORMALIZE);

	
	SetupLight();
	
		
	glEnable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, m_polygonMode);
	if (m_skyBoxb)
		DrawSkyBox();
	m_surface.Draw(-1, 122, 123, 115);
	m_surface.Draw(1, 122, 123, 115);
	
	glDisable(GL_TEXTURE_2D);
		
	m_labyrinth.DrawLabyrinth();
}
	
void CMyApplication::OnReshape(int width, int height)
{
	// ����������� ���� ���������
	glViewport(0, 0, width, height);
	double aspect = double(width) / double(height);
	m_width = width;
	m_height = height;

	// ������ ������� ������� ������������� � ����������� �� ���������
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FOV, aspect, ZNEAR, ZFAR);
	// ������ ������� �������� ������� �������������-����
	glMatrixMode(GL_MODELVIEW);
}

void CMyApplication::OnKeyboard(unsigned char key, int x, int y)
{
	float speed = kSpeed * m_FrameInterval;
	if (GetKeyState(VK_LEFT) & 0x80 || GetKeyState('A') & 0x80) //((key == 'a') || (key == 'A'))//left
	{
		GLdouble tempEyeX = m_camera.m_vPosition.x + (DELTA * cos(m_angle + M_PI / 2));
		GLdouble tempEyeY = m_camera.m_vPosition.y + (DELTA * sin(m_angle + M_PI / 2));
		if (!m_labyrinth.IsBarrier(tempEyeX, tempEyeY))
		{
			m_camera.m_vPosition.x = tempEyeX;
			m_camera.m_vPosition.y = tempEyeY;
		}
	}
	
	if (GetKeyState(VK_RIGHT) & 0x80 || GetKeyState('D') & 0x80)
	{
		GLdouble tempEyeX = m_camera.m_vPosition.x - (DELTA * cos(m_angle + M_PI / 2));
		GLdouble tempEyeY = m_camera.m_vPosition.y - (DELTA * sin(m_angle + M_PI / 2));
		if (!m_labyrinth.IsBarrier(tempEyeX, tempEyeY))
		{
			m_camera.m_vPosition.x = tempEyeX;
			m_camera.m_vPosition.y = tempEyeY;
		}
	}
	if (GetKeyState(VK_UP) & 0x80 || GetKeyState('W') & 0x80)  
	{
		GLdouble tempEyeX = m_camera.m_vPosition.x + (DELTA * cos(m_angle));
		GLdouble tempEyeY = m_camera.m_vPosition.y + (DELTA * sin(m_angle));
		if (!m_labyrinth.IsBarrier(tempEyeX, tempEyeY))
		{
			m_camera.m_vPosition.x = tempEyeX;
			m_camera.m_vPosition.y = tempEyeY;
		}
	}
	if (GetKeyState(VK_DOWN) & 0x80 || GetKeyState('S') & 0x80)
	{
		GLdouble tempEyeX = m_camera.m_vPosition.x - (DELTA * cos(m_angle));
		GLdouble tempEyeY = m_camera.m_vPosition.y - (DELTA * sin(m_angle));
		if (!m_labyrinth.IsBarrier(tempEyeX, tempEyeY))
		{
			m_camera.m_vPosition.x = tempEyeX;
			m_camera.m_vPosition.y = tempEyeY;
		}

	}

	m_camera.m_vView.x = m_camera.m_vPosition.x + (speed * cos(m_angle));
	m_camera.m_vView.y = m_camera.m_vPosition.y + (speed * sin(m_angle));

	if (key == VK_ESCAPE)
		exit(1);
	if (key == '1')
	{
		m_skyBoxb = !m_skyBoxb;
		if (m_skyBoxb)
		{
			std::cout << "SkyBox: " << "true\n";
		}
		else
		{
			std::cout << "SkyBox: " << "false\n";
		}
	}
	if (key == '2')
	{
		m_fog = !m_fog;
		if (m_fog)
		{
			std::cout << "fog: " << "true\n";
		}
		else
		{
			std::cout << "fog: " << "false\n";
		}
	}
		
	if (key == '3')
	{
		m_mouse = !m_mouse;
		if (m_mouse)
		{
			std::cout << "mouse: " << "true\n";
		}
		else
		{
			std::cout << "mouse: " << "false\n";
		}
		ShowCursor(!m_mouse);
	}
	
	PostRedisplay();
}

void CMyApplication::OnMouse(int button, int state, int x, int y)
{

}

void CMyApplication::OnPassiveMotion(int x, int y)
{
	if (x < (m_width / 2))
	{
		m_angle += (ROTATION_SPEED/2 * M_PI) / 180;
	}
	if (x >(m_width / 2))
	{
		m_angle -= (ROTATION_SPEED/2 * M_PI) / 180;
	}
	if (y < (m_height / 2))
	{
		m_anglez += (ROTATION_SPEED / 2 * M_PI) / 180;
	}

	if (y > (m_height / 2))
	{
		m_anglez -= (ROTATION_SPEED / 2 * M_PI) / 180;
	}
	if (m_anglez<-1.5){ m_anglez = -1.5; }
	if (m_anglez>1.5){ m_anglez = 1.5; }

	m_camera.m_vView.x = m_camera.m_vPosition.x + (DELTA * cos(m_angle));
	m_camera.m_vView.y = m_camera.m_vPosition.y + (DELTA * sin(m_angle));
	m_camera.m_vView.z = m_camera.m_vPosition.z + (DELTA * tan(m_anglez));
	
	PostRedisplay();
}

void CMyApplication::DrawSkyBox()const
{
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	m_skyBox.Draw();
	//glEnable(GL_LIGHTING);
}	  