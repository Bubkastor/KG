#include "StdAfx.h"
#include "Utils.h"

GLuint CUtils::LoadTexture(std::wstring const & fileName)
{
	// ��������� ����������� ��� ������ GDI+
	Gdiplus::Bitmap bmp(fileName.c_str());
	if (bmp.GetLastStatus() != Gdiplus::Ok)
	{
		//std::cerr << "Error open texture file" << std::endl;
		throw std::runtime_error("Error loading texture file");
	}

	// ���������� ������ �������� ��� ������������� 
	// � ������� Bitmap::Lock � �������� gluBuild2DMipmaps
	Gdiplus::PixelFormat pixelFormat = 0;
	GLint textureFormat = 0;
	GLint colorComponents = 0;
	GLint internalFormat = 0;

	// ���� �� � ����������� �����-�����?
	if ((bmp.GetPixelFormat() & PixelFormatAlpha) != 0)
	{
		colorComponents = 4;
		pixelFormat = PixelFormat32bppARGB;
		textureFormat = GL_BGRA_EXT;
		internalFormat = GL_RGBA;
	}
	else
	{
		colorComponents = 3;
		pixelFormat = PixelFormat24bppRGB;
		textureFormat = GL_BGR_EXT;
		internalFormat = GL_RGB;
	}

	// ������� � ��������� ������������� ������� �����������, 
	// ������ � ������ ������� �� ����� ��������
	Gdiplus::Rect lockRect(0, 0, bmp.GetWidth(), bmp.GetHeight());

	// �������� ������ ������ ��� ������ � ������ ���������� �����������
	Gdiplus::BitmapData bitmapData;
	bmp.LockBits(&lockRect, Gdiplus::ImageLockModeRead,
		pixelFormat, &bitmapData);

	GLuint textureName = 0;
	// ���������� ���� ���������� ������������� ����������� �������
	glGenTextures(1, &textureName);

	// ������ �������� ���������� ������ � ������ ���������������
	// (� ��� ��� ���� �� ������� ������� �����������)
	glBindTexture(GL_TEXTURE_2D, textureName);

	// ������ ��������� ���-������� ��� ������������ �����������
	// � ����������� �� � ���������� ����������� �������
	// ������ ���������� ����������� ��� 0 ������ �����������
	glTexImage2D(
		GL_TEXTURE_2D,
		0,		// ������� �����������
		internalFormat,
		bitmapData.Width,
		bitmapData.Height,
		0,		// ������ ����� �������� (0 - ��� �����, 1 - ����� � 1 �������)
		textureFormat,
		GL_UNSIGNED_BYTE,
		bitmapData.Scan0
		);
	// ������ ��������� ���������� �������� ��� ���������� � ��� ����������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// ��������� ������ � ������� ������
	bmp.UnlockBits(&bitmapData);

	// ���������� ������������� ���������� �����������
	return textureName;
}
