#pragma once
#include <stdafx.h>

std::wstring MBS2WCS(std::string szString);
std::string WCS2MBS(std::wstring szString);
bool ReadFileIntoVec(tstring szFilepath, size_t szSize, std::vector<byte> & vData);