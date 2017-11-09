#pragma once
#include "GHLMainWindow.h"

class GHLGen
{
public:
	GHLGen(HINSTANCE hInstance);
	~GHLGen();
	bool IsDlgMessage(MSG * pMsg);

private:
	std::vector<CXWindow*> vWindows;
	HINSTANCE hInstance = NULL;
	GHLMainWindow * pWnd = nullptr;
};

