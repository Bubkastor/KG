#include "stdafx.h"
#include "MyApplication.h"
using namespace std;



void Dump3dsFile(const char *fileName);

// Выводим информацию о материалах
void DumpMaterials(Lib3dsFile const * pFile);

// Выводим информацию об источниках света 
void DumpLights(Lib3dsFile const *pFile);

// Выводим информацию о полигональных сетках 
void DumpMeshes(Lib3dsFile const * pFile);

std::string VectorToString(float const vec[3]);
std::string TextureCoordsToString(float const vec[2]);
std::string RgbToString(float const rgb[3]);



CMyApplication app("Rendering using Vertex Arrays", 800, 600);

int main()
{
	try
	{
		app.MainLoop();
	}
	catch (std::runtime_error const& e)
	{
		std::cout << e.what();
	}
	return 0;
}

//int main(int argc, char* argv [])
//{
//	if (argc == 1)
//	{   // Если программа запущена без аргументов командной строки,  
//		// выводим инструкцию по пользованию   
//		cout << "Usage:\n01_dump_3ds.exe <3ds file name>\n";
//		return 0;
//	}
//	else if (argc != 2)
//	{   // Если программа запущена с неверным числом аргументов,   
//		// сообщаем о некорректном использовании   
//		cout << "Invalid command line. Use the following syntax\n" << "01_dump_3ds.exe <3ds file name>\n";
//		return 1;
//	}
//	try
//	{
//		Dump3dsFile(argv[1]);
//	}
//	catch (std::runtime_error const& e)
//	{
//		cout << "Error: " << e.what();
//		return 2;
//	}
//	return 0;
//}


void DumpMaterials(Lib3dsFile const * pFile)
{
	const int materialsCount = pFile->nmaterials;

	std::cout << "===Materials===\n";

	for (int i = 0; i < materialsCount; ++i)
	{
		Lib3dsMaterial const * pMaterial = pFile->materials[i];

		// Выводим параметры материала, 
		cout << "\t" << "Material: '" << pMaterial->name << "'\n";
		cout << "\t\t" << "Ambient: " << RgbToString(pMaterial->ambient) << "\n";
		cout << "\t\t" << "Diffuse: " << RgbToString(pMaterial->diffuse) << "\n";
		cout << "\t\t" << "Specular: " << RgbToString(pMaterial->specular) << "\n";
		cout << "\t\t" << "Shininess: " << pMaterial->shininess << "\n";

		// а также имя текстуры, которая может быть привязана к материалу 
		Lib3dsTextureMap const & textureMap = pMaterial->texture1_map;
		// Проверяем задано ли имя файла текстуры для данного материала 
		if (textureMap.name[0] != '\0')
		{
			cout << "\t\t" << "Texture: " << textureMap.name << "\n";
		}
	}
}
void DumpLights(Lib3dsFile const *pFile)
{
	std::cout << "===Lights===\n";

	const int lightsCount = pFile->nlights;

	for (int i = 0; i < lightsCount; ++i)
	{
		Lib3dsLight const * pLight = pFile->lights[i];
		cout << "\t" << "Light: '" << pLight->name << "'\n";
		cout << "\t\t" << "Color: " << RgbToString(pLight->color) << "\n";
		cout << "\t\t" << "Position: " << VectorToString(pLight->position)
			<< "\n";
	}

}
void DumpMeshes(Lib3dsFile const * pFile)
{
	std::cout << "===Meshes==\n";
	const int meshCount = pFile->nmeshes;

	for (int i = 0; i <meshCount; ++i)
	{
		Lib3dsMesh const * pMesh = pFile->meshes[i];

		// Выводим имя полигональоной сетки 
		cout << "\t" << "Mesh: '" << pMesh->name << "'\n";

		// Выводим информацию о ее вершинах 
		{
			const int vertexCount = pMesh->nvertices;
			cout << "\t\t" << "Vertices: " << vertexCount << "\n";

			float const (*vertices)[3] = pMesh->vertices;
			float const (*textureCoords)[2] = pMesh->texcos;

			for (int i = 0; i < vertexCount; ++i)
			{
				cout << "\t\t\tVertex[" << i << "] " << VectorToString(vertices[i]);

				if (textureCoords != NULL)
				{
					// При наличии текстурных координат, выводим и их 
					cout << " Tex: " << TextureCoordsToString(textureCoords[i]);
				}
				cout << "\n";
			}
		}

		// Выводим информацию о гранях 
		{
			const int faceCount = pMesh->nfaces;
			cout << "\t\t" << "Faces: " << faceCount << "\n";

			for (int f = 0; f < faceCount; ++f)
			{
				Lib3dsFace const& face = pMesh->faces[f];
				const unsigned short * indices = face.index;
				cout << "\t\t\tFace[" << f << "] "
					<< "(" << indices[0] << ", " << indices[1] << ", "
					<< indices[2] << ")"
					<< " smooth: " << face.smoothing_group << " flags:" << face.flags
					<< " material: '" << face.material << "'\n";
			}
		}
	}
}
void Dump3dsFile(const char *fileName)
{
	// Открываем файл формата 3ds 
	Lib3dsFile * pFile = lib3ds_file_open(fileName);

	// В случае ошибки выбрасываем исключение 
	if (pFile == NULL)
	{
		throw std::runtime_error("Unable to read 3ds file");
	}

	// Сохраняем указатель на файл в обертке CFile3ds 
	CFile3ds file(pFile);

	// Выводим информацию о материалах, 
	DumpMaterials(pFile);
	
	// источниках света 
	DumpLights(pFile);

	// и полигональных сетках 
	DumpMeshes(pFile);
}

std::string VectorToString(float const vec[3])
{
	stringstream s;
	s << "(" << vec[0] << "; " << vec[1] << "; " << vec[2] << ")";
	return s.str();
}
std::string TextureCoordsToString(float const vec[2])
{
	stringstream s;
	s << "(" << vec[0] << "; " << vec[1] << ")";
	return s.str();
}
std::string RgbToString(float const rgb[3])
{
	stringstream s;
	s << "(" << rgb[0] << "; " << rgb[1] << "; " << rgb[2] << ")";
	return s.str();
}