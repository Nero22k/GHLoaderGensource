#include "UPX.h"



CUPX::CUPX(tstring szFilepath)
	: resWriter(GetModuleHandle(0))
{
	this->szFilepath = szFilepath;
}


CUPX::~CUPX()
{
}
