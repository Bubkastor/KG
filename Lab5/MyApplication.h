#pragma once
#include "glapplication.h"
#include "Surface.h"
#include "LabyrinthMap.h"
//#include "OmniLight.h"
#include "SkyBox.h"

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
	virtual void OnSpecialHadler(int key, int x, int y);
	virtual void OnKeyboard(unsigned char key, int x, int y);


private:
	void SetupCamera();
	void DrawSkyBox()const;

	CSurface m_surface;
	CLabyrinthMap m_labyrinth;
	//COmniLight m_light;

	float m_angle;

	static const int DELTA_ANGLE = 1;
	static const double DELTA;

	GLdouble m_eyex;
	GLdouble m_eyey;
	GLdouble m_eyez;

	GLdouble m_centerx;
	GLdouble m_centery;
	GLdouble m_centerz;

	GLenum m_polygonMode;

	CSkyBox m_skyBox;

	static const float ROTATION_SPEED;
	static const double FOV;
	static const double ZNEAR;
	static const double ZFAR;
};
