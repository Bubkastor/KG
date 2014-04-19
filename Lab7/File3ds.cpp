#include "File3ds.h"

CFile3ds::CFile3ds(Lib3dsFile * pFile)
:m_pFile(pFile)
{
}

CFile3ds::~CFile3ds()
{
	if (m_pFile)
	{
		lib3ds_file_free(m_pFile);
	}
}