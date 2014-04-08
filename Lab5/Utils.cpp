#include "StdAfx.h"
#include "Utils.h"

GLuint CUtils::LoadTexture(std::wstring const & fileName)
{
	// Загружаем изображение при помощи GDI+
	Gdiplus::Bitmap bmp(fileName.c_str());
	if (bmp.GetLastStatus() != Gdiplus::Ok)
	{
		//std::cerr << "Error open texture file" << std::endl;
		throw std::runtime_error("Error loading texture file");
	}

	// Определяем формат пикселей для использования 
	// с методом Bitmap::Lock и функцией gluBuild2DMipmaps
	Gdiplus::PixelFormat pixelFormat = 0;
	GLint textureFormat = 0;
	GLint colorComponents = 0;
	GLint internalFormat = 0;

	// Есть ли в изображении альфа-канал?
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

	// Размеры и положение прямоугольной области изображения, 
	// доступ к данным которой мы хотим получить
	Gdiplus::Rect lockRect(0, 0, bmp.GetWidth(), bmp.GetHeight());

	// Получаем прямой доступ для чтения к данным растрового изображения
	Gdiplus::BitmapData bitmapData;
	bmp.LockBits(&lockRect, Gdiplus::ImageLockModeRead,
		pixelFormat, &bitmapData);

	GLuint textureName = 0;
	// генерируем один уникальный идентификатор текстурного объекта
	glGenTextures(1, &textureName);

	// делаем активным текстурный объект с данным идентификатором
	// (с ним еще пока не связано никакое изображение)
	glBindTexture(GL_TEXTURE_2D, textureName);

	// Строим семейство мип-уровней для загруженного изображения
	// и присоединям их к выбранному текстурному объекту
	// Задаем текстурное изображение для 0 уровня детализации
	glTexImage2D(
		GL_TEXTURE_2D,
		0,		// уровень детализации
		internalFormat,
		bitmapData.Width,
		bitmapData.Height,
		0,		// ширина рамки текстуры (0 - нет рамки, 1 - рамка в 1 пиксель)
		textureFormat,
		GL_UNSIGNED_BYTE,
		bitmapData.Scan0
		);
	// Задаем параметры фильтрации текстуры при уменьшении и при увеличении
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Завершаем работу с данными растра
	bmp.UnlockBits(&bitmapData);

	// Возвращаем идентификатор созданного изображения
	return textureName;
}
