#include "GHLMainWindow.h"

GHLMainWindow * g_pMain = nullptr;

void BtnCallback(uintptr_t iCommand)
{
	switch (iCommand)
	{
		case SELECT_PROCESS:
			g_pMain->SelectProcess();
			break;
		case SELECT_DLL:
			g_pMain->SelectDll();
			break;
		case SELECT_README:
			g_pMain->SelectReadme();
			break;
		case SELECT_GH:
			g_pMain->LaunchGH();
			break;
	}
}

GHLMainWindow::GHLMainWindow(HINSTANCE hInstance, int x, int y)
	: CXMainWindow(hInstance, SZWND_TITLE, XMAINWNDCLS, x, y, GHL_WND_W, GHL_WND_H)
{
	g_pMainWindow = this;
	g_pMain = this;
	SetBgColor(GHL_WND_BGCLR);
	SetStyle(WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX);

	this->hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	this->hIconSm = hIcon;

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

void GHLMainWindow::SelectProcess()
{
	pProcPicker->Show();
}

void GHLMainWindow::ProcessSelected()
{
	targetProc = this->pProcPicker->GetSelectedProcess();

	CXControls* pC = pControls->GetControl<CXGroupBox>(IDGRP_PROCESS)->pControls;

	pC->GetControl<CXEdit>(IDEDT_PROCNAME)->SetText(targetProc->GetProcName());
	CXLabel * pL = pC->GetControl<CXLabel>(IDLBL_PID);
	tstring buf(22, 0);
	_itot_s(targetProc->GetPID(), &buf[0], 22, 10);
	tstring pid = _T("PID: ");
	pid += buf;
	pid.resize(lstrlen(pid.c_str()));
	pL->SetText(pid);
	bool b64 = targetProc->Is64Bit();
	pL = pC->GetControl<CXLabel>(IDLBL_ARCH);
	tstring arch = pL->GetText();
	arch += (b64) ? _T("x64") : _T("x86");
	pL->SetText(arch);
	RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
}

void GHLMainWindow::SelectDll()
{
	CXFileDialogFilterEntry fe(L"Dll file | (*.dll)", L"*.dll");
	CXFileDialog fd(this, OPEN, &fe);
	tstring szPath;
	if (fd.Show(szPath))
		pControls->GetControl<CXEdit>(IDEDT_DLLPATH)->SetText(szPath);
}

void GHLMainWindow::SelectReadme()
{
	CXFileDialogFilterEntry fe(L"Text file | (*.txt)", L"*.txt");
	CXFileDialog fd(this, OPEN, &fe);
	tstring szPath;
	if (fd.Show(szPath))
		pControls->GetControl<CXEdit>(IDEDT_README)->SetText(szPath);
}

void GHLMainWindow::LaunchGH()
{
	MessageBox(hWnd, _T("Thanks for using the official GuidedHacking loader!\n-GH Team"), _T("Heyo!"), MB_ICONINFORMATION | MB_OK);
	ShellExecute(hWnd, L"open", _T("http://guidedhacking.com"), NULL, NULL, SW_SHOW);
}

void GHLMainWindow::GenerateLoader()
{
	//first we need to check if everything is good to go
	//check if 
	//then we need to generate our resources
	//write appropriate binary to disk
	//write resources into binary
}

int GHLMainWindow::CreateControls()
{
	CXControls* pC;
	CXControl* pCtrl;
	CXGroupBox * pGb;
	CXButton * pBtn;
	std::function<void(uintptr_t)> bc = BtnCallback;

	// ============================================= LOADER SETTINGS =============================================
	pGb = pControls->AddControl<CXGroupBox>(IDGRP_LOADSET, 10, 5, 270, 115, L"Loader Settings");
	pGb->SetTxtColor(RGB(200, 200, 200));
	pGb->SetControlManager(new CXControls(pGb));
	pC = pGb->pControls;
	
	pC->AddControl<CXLabel>(IDLBL_FORMNAME, 10, 23, 80, 25, L"Window Title:");
	pC->AddControl<CXEdit>(IDEDT_FORMNAME, 110, 20, 150, 25, L"SupaDupaHax");
	pC->AddControl<CXLabel>(IDLBL_GAMENAME, 10, 53, 80, 25, L"Game Title:");
	pC->AddControl<CXEdit>(IDEDT_GAMENAME, 110, 50, 150, 25, L"AssaultCube");
	pC->AddControl<CXLabel>(IDLBL_AUTHOR, 10, 83, 80, 25, L"Author:");
	pC->AddControl<CXEdit>(IDEDT_AUTHOR, 110, 80, 150, 25, L"Traxin");

	pControls->AddControl<CXEdit>(IDEDT_DLLPATH, 290, 45, 275, 25, L"C:\\hax.dll");
	pBtn = pControls->AddControl<CXButton>(IDBTN_DLLSELECT, 290, 10, 125, 25, L"Select DLL");
	pBtn->SetAction(bc);
	pBtn->SetCommandArgs(SELECT_DLL);
		
	pControls->AddControl<CXEdit>(IDEDT_README, 290, 80, 275, 25, L"C:\\readme.txt");
	pBtn = pControls->AddControl<CXButton>(IDBTN_README, 440, 10, 125, 25, L"Select Readme");
	pBtn->SetAction(bc);
	pBtn->SetCommandArgs(SELECT_README);
	
#define DIV 115

	// ============================================= PROCESS =============================================
	pGb = pControls->AddControl<CXGroupBox>(IDGRP_PROCESS, 10, DIV+10, 200, 115, L"Process");
	pGb->SetTxtColor(RGB(200, 200, 200));
	RECT rc = pGb->GetAdjustedRect();
	pGb->SetControlManager(new CXControls(pGb));

	pC = pGb->pControls;
	pCtrl = pC->AddControl<CXLabel>(IDLBL_PROCNAME, 10, 23, 40, 25, L"Name:");


	//pC->AddGroup(IDGRP_PROCESS);
	//pC->AddControlToGroup<CXLabel>(IDGRP_PROCESS, IDLBL_PROCNAME, 10, 23, 40, 25, L"Name:");
	pC->AddControl<CXEdit>(IDEDT_PROCNAME, 65, 20, 120, 25, L"ac_client.exe");
	pCtrl = pC->AddControl<CXLabel>(IDLBL_PID, 10, 55, 60, 25, L"PID: ");
	pCtrl = pC->AddControl<CXLabel>(IDLBL_ARCH, 10, 85, 60, 25, L"Arch: ");

	pBtn = pControls->AddControl<CXButton>(IDBTN_PROCSELECT, 14, DIV + 130, 190, 25, L"Select Process");
	pProcPicker = new CGHLProcPicker(this, targetProc);
	std::function<void()> ppc = ProcPickerCallback;
	pProcPicker->SetProcPickerCallback(ppc);
	pBtn->SetAction(bc);
	pBtn->SetCommandArgs(SELECT_PROCESS);

	// ============================================= INJECTOR SETTINGS =============================================
	pGb = pControls->AddControl<CXGroupBox>(IDGRP_INJSET, 220, DIV + 10, 350, 190, L"Injection Settings");
	pGb->SetTxtColor(RGB(200, 200, 200));
	pGb->SetControlManager(new CXControls(pGb));
	pC = pGb->pControls;
	pC->AddGroup(IDGRP_INJSET);
	pC->AddControlToGroup<CXRadioButton>(IDGRP_INJSET, IDRDO_LOADLIB, 10, 20, 125, 25, L"LoadLibrary");
	pC->vGroups[IDGRP_INJSET]->GetControl<CXRadioButton>(IDRDO_LOADLIB)->SetCheck(true);
	//pC->GetControl<CXRadioButton>(IDRDO_LOADLIB)->SetCheck(true);
	pC->AddControlToGroup<CXRadioButton>(IDGRP_INJSET, IDRDO_LDRLOAD, 125, 20, 125, 25, L"LdrLoadDll");
	pC->AddControlToGroup<CXRadioButton>(IDGRP_INJSET, IDRDO_MANMAP, 235, 20, 125, 25, L"Manual Map");
	pC->AddControlToGroup<CXCheckBox>(IDGRP_INJSET, IDCHK_THIJACK, 10, 50, 150, 25, L"Thread Hijacking");

	pC->AddGroup(IDGRP_INJPOST);
	pC->AddControlToGroup<CXRadioButton>(IDGRP_INJPOST, IDRDO_KEEPPEH, 10, 90, 125, 25, L"Keep PEH");
	pC->vGroups[IDGRP_INJPOST]->GetControl<CXRadioButton>(IDRDO_KEEPPEH)->SetCheck(true);
	pC->AddControlToGroup<CXRadioButton>(IDGRP_INJPOST, IDRDO_ERASEPEH, 125, 90, 125, 25, L"Erase PEH");
	pC->AddControlToGroup<CXRadioButton>(IDGRP_INJPOST, IDRDO_FAKEPEH, 235, 90, 125, 25, L"Fake PEH");
	pC->AddControlToGroup<CXCheckBox>(IDGRP_INJPOST, IDCHK_ULNKPEB, 10, 115, 150, 25, L"Unlink from PEB");
	pCtrl = pC->AddControl<CXLabel>(IDLBL_DELAY, 50, 148, 100, 25, L"Delay: ");
	pCtrl->SetTxtColor(RGB(200, 200, 200));
	pCtrl = pC->AddControl<CXEdit>(IDEDT_DELAY, 120, 145, 200, 25, L"0");
	pCtrl->SetStyle(pCtrl->GetStyle() | ES_NUMBER);

	// ============================================= FINALE =============================================
	pControls->AddControl<CXCheckBox>(IDCHK_RANDNAMES, 10, DIV + 160, 180, 25, L"Randomize File Names");
	pControls->AddControl<CXCheckBox>(IDCHK_UPXFILES, 10, DIV + 180, 180, 25, L"UPX Everything");

	pControls->AddControl<CXButton>(IDBTN_BUILD, 10, DIV + 210, 510, 25, L"Generate Loader!");
	pBtn = pControls->AddControl<CXButton>(IDBTN_GH, 530, DIV + 210, 40, 25, L"");	
	pBtn->SetIcon(hIcon);
	pBtn->SetAction(bc);
	pBtn->SetCommandArgs(SELECT_GH);

	RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);

	return 0;
}

void ProcPickerCallback()
{
	g_pMain->ProcessSelected();
}
