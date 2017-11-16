#include "GHLProcPicker.h"
#include "XGui\XControls.h"

CGHLProcPicker::CGHLProcPicker(CXWindow* pMainWindow)
	: CXDialog(pMainWindow, 1, pMainWindow->GetRect().right, pMainWindow->GetRect().top, 600,350, _T("Proc'Picker"))
{
}


CGHLProcPicker::~CGHLProcPicker()
{
}

void CGHLProcPicker::Show()
{
	if (!hWnd)
		Init();
	ShowWindow(hWnd, SW_SHOW);
	//CXDialog::Show();
	auto xLV = xControls->GetControl<CXListView>(IDLIST1);
	ListView_DeleteAllItems(xLV->GetHandle());
	FillList();
	bShown = true;
}

void CGHLProcPicker::FillList()
{
	//to do
	// enumerate open processes, should probably spawn processes to do this
	// load binary icon from resource, also implement reading resource from binary in resmanager class
	// list sorting, by arch, name (A-Z || Z-A), pid, process start time or duration running might be nice too


	//CXListViewItem listItem = CXListViewItem(0, 0, L"TEST");
	//listItem.AddSubItem(0, 1, L"FUCK");		
	//auto xLV = xControls->GetControl<CXListView>(IDLIST1);
	//xLV->AddItem(listItem);

	//RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
	procManager.LoadProcs();
	int x = 0;
	tstring pid(22, 0);
	ProcVec pv = procManager.GetProcs();
	for (auto p : pv)
	{
		CXListViewItem listItem = CXListViewItem(x, 0, L"");
		listItem.AddSubItem(x, 1, L"IDK");		
		listItem.AddSubItem(x, 2, p->GetProcName());
		_itow_s(p->GetPID(), &pid[0], 22, 10);
		listItem.AddSubItem(x, 3, pid);
		listItem.AddSubItem(x, 4, p->GetProcPath());
		auto xLV = xControls->GetControl<CXListView>(IDLIST1);
		xLV->AddItem(listItem);
		x++;
	}
}

void CGHLProcPicker::Init()
{
	Create();
	GetRect();
	xControls = new CXControls(this);
	xControls->AddControl<CXListView>(IDLIST1, 15, 15, 550, rcRect.bottom - 35, _T(" "));
	CXListView* list = xControls->GetControl<CXListView>(IDLIST1);
	list->SetColumnWidth(0, 32);
	list->InsertColumn(_T("Arch"), 48, LVCFMT_CENTER);
	list->InsertColumn(_T("Process Name"), 100, LVCFMT_LEFT);
	list->InsertColumn(_T("PID"), 48, LVCFMT_CENTER);
	list->InsertColumn(_T("Path"), uWidth/2);

	RECT rc = list->GetRect();
	xControls->AddControl<CXButton>(IDBUTTON1, 15, rcRect.bottom - 5, rc.right - rc.left, 25, _T("Select Process"));

	procManager.LoadProcs();
}
