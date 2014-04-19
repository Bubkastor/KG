#pragma once
#include "stdaf.h"
class CFile3ds
{
public:
	CFile3ds(Lib3dsFile * pFile);
	~CFile3ds();
private:
	CFile3ds(CFile3ds const&);
	CFile3ds& operator=(CFile3ds const&);
	Lib3dsFile * m_pFile;
};
