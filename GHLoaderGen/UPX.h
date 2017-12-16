#pragma once
#include "XResource.h"

class CUPX
{
public:
	CUPX(tstring szFilepath);
	~CUPX();

private:
	tstring szFilepath;
	CResourceWriter resWriter;
};

