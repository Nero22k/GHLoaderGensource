#pragma once
#include "XGui\XDialog.h"
#include "ProcManager.h"

#define IDLIST1				0x8000
#define IDBUTTON1			0x8001

class CGHLProcPicker : public CXDialog
{
public:
	CGHLProcPicker(CXWindow* pMainWindow);
	~CGHLProcPicker();
	void Show();
	void FillList();
	void Init();

private:
	ProcManager procManager;
};

