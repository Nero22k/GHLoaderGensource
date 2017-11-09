#include "GHLMainWindow.h"

GHLMainWindow::GHLMainWindow(HINSTANCE hInstance, int x, int y)
	: CXMainWindow(hInstance, SZWND_TITLE, XMAINWNDCLS, x, y, GHL_WND_W, GHL_WND_H)
{
	g_pMainWindow = this;
	SetBgColor(GHL_WND_BGCLR);
	SetStyle(WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX);
	if (!Create())
	{
		//error ;P
		exit(-1);
	}
	CreateControls();
}


GHLMainWindow::~GHLMainWindow()
{
}

int GHLMainWindow::CreateControls()
{
	//CXButton * pButton = pControls->AddControl<CXButton>(IDBTN_PROCSELECT, rcRect.left + 5, rcRect.top + 5, 120, 25, _T("Select Process"));
	//RECT rc = pButton->GetRect();
	//pControls->AddControl<CXButton>(IDBTN_DLLSELECT, rcRect.left + 5, pButton->GetPos().x + pButton->GetHeight() + 5, 120, 25, _T("Select DLL"));

	CXGroupBox * pGb = pControls->AddControl<CXGroupBox>(IDGRP_PROCESS, 10, 10, 200, 200, L"Process");
	pGb->SetTxtColor(RGB(200, 200, 200));
	return 0;
}
