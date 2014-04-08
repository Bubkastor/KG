// labyrinth.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MyApplication.h"

class CGdiplusInitializer
{
public:
	CGdiplusInitializer()
	{
		Gdiplus::GdiplusStartupInput input;
		Gdiplus::GdiplusStartupOutput output;

		if (Gdiplus::GdiplusStartup(&m_token, &input, &output) != Gdiplus::Ok)
		{
			// Не удалось инициализировать GDI+
			throw std::runtime_error("Failed to initialize GDI+");
		}
	}

	~CGdiplusInitializer()
	{
		Gdiplus::GdiplusShutdown(m_token);
	}
private:
	ULONG_PTR m_token;
};

CGdiplusInitializer gdiplusInitializer;
CMyApplication g_app("Labyrinth", 800, 600);


int main(int argc, _TCHAR* argv[])
{
	g_app.MainLoop();
	return 0;
}

