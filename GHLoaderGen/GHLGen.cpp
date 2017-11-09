#include "GHLGen.h"



GHLGen::GHLGen(HINSTANCE hInstance)
{
	this->hInstance = hInstance;
	RECT rc;
	GetWindowRect(GetDesktopWindow(), &rc);
	int x = rc.right - ((rc.right - rc.left) / 2) - (GHL_WND_W / 2);
	int y = (rc.bottom / 2) - GHL_WND_H / 2;
	pWnd = new GHLMainWindow(hInstance, x, y);
	vWindows.push_back(pWnd);
}


GHLGen::~GHLGen()
{
}

bool GHLGen::IsDlgMessage(MSG * pMsg)
{
	bool bIsDlgMsg = false;
	for (auto p : vWindows)
		bIsDlgMsg = bIsDlgMsg || IsDialogMessage(p->GetHandle(), pMsg);
	return bIsDlgMsg;
}
