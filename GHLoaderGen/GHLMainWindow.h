#pragma once
#include "XGui\XMainWindow.h"

//form properties
#define SZWND_TITLE _T("GH-Loader Generator")
#define GHL_WND_W 500
#define GHL_WND_H 350
#define GHL_WND_BGCLR RGB(25,25,25)

//control id's
#define IDBTN_PROCSELECT	0x8001
#define IDBTN_DLLSELECT		0x8002

#define IDGRP_PROCESS		0x7000

class GHLMainWindow : public CXMainWindow
{
public:
	GHLMainWindow(HINSTANCE hInstance, int x, int y);
	~GHLMainWindow();

private:
	int CreateControls();
};

