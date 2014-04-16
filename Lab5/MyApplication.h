#pragma once
#include "glapplication.h"
#include "Surface.h"
#include "LabyrinthMap.h"
#include "OmniLight.h"
#include "SkyBox.h"
#include "Light.h"
#include "Camera.h"

class CMyApplication :
	public CGLApplication
{
public:
	CMyApplication(const char *title, int width, int height);
	~CMyApplication(void);
protected:
	// Перегружаем необходимые виртуальные методы родительского класса
	virtual void OnInit();
	virtual void OnIdle();
	virtual void OnDisplay(void);
	virtual void OnReshape(int width, int height);
	virtual void OnKeyboard(unsigned char key, int x, int y);
	virtual void OnMouse(int button, int state, int x, int y);
	virtual void OnPassiveMotion(int x, int y);


private:

	void CalculateFrameRate();
	void GetFrameTime();
	void SetupLight();
	void DrawSkyBox()const;

	CSurface m_surface;
	CLabyrinthMap m_labyrinth;
	COmniLight m_light;
	CCamera m_camera;

	float m_FPS;
	float m_angle;
	float m_anglez;
	float m_FrameInterval;
	static const double DELTA;

	GLdouble m_eyex;
	GLdouble m_eyey;  
	GLdouble m_eyez;

	GLdouble m_centerx;
	GLdouble m_centery;
	GLdouble m_centerz;

	GLenum m_polygonMode;

	CSkyBox m_skyBox;

	static const int ROTATION_SPEED;
	static const double FOV;
	static const double ZNEAR;
	static const double ZFAR;
	int m_width;
	int m_height;
	bool m_fog;
	bool m_skyBoxb;
	bool m_mouse;
	int light_sample;
};
