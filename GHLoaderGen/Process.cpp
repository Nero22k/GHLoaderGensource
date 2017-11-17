#include "Process.h"
#include "XResource.h"
#include <ShlObj.h>
#define _WIN32_WINNT

CProcess::CProcess()
{
}

CProcess::CProcess(PROCESSENTRY32 pe32)
{
	this->pe32 = pe32;
	this->dwPID = pe32.th32ProcessID;
	this->szExe = pe32.szExeFile;
	Start();
}

CProcess::CProcess(DWORD dwPID, tstring szExe)
{
	this->dwPID = dwPID;
	this->szExe = szExe;
	Start();
}


CProcess::~CProcess()
{
	if (hHandle)
	{
		CloseHandle(hHandle);
	}
}

HANDLE CProcess::Open()
{
	return Open(PROCESS_QUERY_INFORMATION);
}

HANDLE CProcess::Open(DWORD dwAccess)
{
	hHandle = OpenProcess(dwAccess, FALSE, dwPID);
	if (!hHandle)
	{
		//GetLastError();
		return 0;
	}
	return hHandle;
}

tstring CProcess::GetProcName()
{
	return szExe;
}

tstring CProcess::GetProcPath()
{
	return szPath;
}

DWORD CProcess::GetPID()
{
	return dwPID;
}

HICON CProcess::GetIcon()
{	
	return hIcon;
}

typedef BOOL(WINAPI * _IsWow64Process)(HANDLE, PBOOL);
_IsWow64Process  _IsWow64;
bool CProcess::Is64Bit()
{
	if (!_IsWow64)
	{
		HMODULE hMod = GetModuleHandle(_T("kernel32"));
		_IsWow64 = (_IsWow64Process)GetProcAddress(hMod, "IsWow64Process");
	}

	BOOL b64;
	if (_IsWow64)
	{
		if (Open())
		{
			_IsWow64(hHandle, &b64);
			return !b64;
		}
		return true;
	}
	return false;
}

void CProcess::Start()
{
	Open();
	FindProcPath();
	FindIcon();
}

void CProcess::FindProcPath()
{
	if (szPath.empty())
	{
		if (!hHandle)
			Open();

		if (hHandle)
		{
			szPath.resize(MAX_PATH);
			GetModuleFileNameEx(hHandle, NULL, &szPath[0], MAX_PATH);
		}
		else
			szPath = L"";
	}
}

void CProcess::FindIcon()
{
	HRSRC hRes;
	GetProcPath();
	if (!hIcon && !szPath.empty())
	{
		if (!hHandle)
			Open();
		if (!hHandle)
			return;


		hIcon = NULL;
	}
}