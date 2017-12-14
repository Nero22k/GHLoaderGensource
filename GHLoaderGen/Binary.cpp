#include "Binary.h"
#include <DbgHelp.h>
#pragma comment(lib, "Dbghelp.lib")



CBinary::CBinary(tstring & szPath)
{
	this->szPath = szPath;
}

CBinary::~CBinary()
{
}

bool CBinary::Is64BitImage()
{
	ReadPEHeader();
	PIMAGE_NT_HEADERS pNT = ImageNtHeader(&vHeader[0]);
	if (pNT->FileHeader.Machine == IMAGE_FILE_MACHINE_I386)
		return false;

	return true;
}

bool CBinary::Exists()
{
	bool exists = false;
	HANDLE hFile = OpenFile(szPath.c_str());
	if (hFile != INVALID_HANDLE_VALUE)
		exists = true;
	CloseHandle(hFile);
	return exists;
}

tstring CBinary::GetPath()
{
	return szPath;
}

std::vector<byte>* CBinary::Read()
{
	if (Exists())
	{
		//GetFileSize()
	}
	return nullptr;
}


void CBinary::ReadPEHeader()
{
	//HANDLE hFile = CreateFile(szPath.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE hFile = OpenFile(szPath.c_str());

	vHeader.resize(0x1000, 0);
	BOOL bRead = ReadFile(hFile, &vHeader[0], 0x1000, NULL, NULL);
	if (!bRead)
		ErrorMsgBox(_T("Invalid PE file..."));
	CloseHandle(hFile);
}
