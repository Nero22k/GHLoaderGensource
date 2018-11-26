#include "XEdit.h"

LRESULT CALLBACK EditCallback(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	CXEdit* pEdit = (CXEdit*)dwRefData;
	
	switch (msg)
	{
		case WM_KILLFOCUS:
		{
			if (pEdit->pKeyPressCallback)
				pEdit->pKeyPressCallback((void*)pEdit->GetText().c_str());
			break;
		}
		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case VK_TAB:
					//MessageBox(NULL, L"Pressed TAB", L"Test", MB_OK);
					return FALSE;
				case VK_ESCAPE:
					return TRUE;
			}
			//if (pEdit->pKeyPressCallback)
			//	pEdit->pKeyPressCallback((void*)pEdit->GetText().c_str());
			
			break;
		}
	}
	return DefSubclassProc(hWnd, msg, wParam, lParam);
}


CXEdit::CXEdit(CXWindow * pOwner, XID xID, int x, int y, int w, int h, tstring szText, CXFont * pFont)
	: CXControl(pOwner, xID, EDIT, x, y, w, h, szText, pFont)
{
	szClass = _T("EDIT");
	SetStyle(WS_XEDIT);
	this->bMultiLine = true;
}

CXEdit::~CXEdit()
{
}

bool CXEdit::Create()
{
	if (!bMultiLine && GetHeight() == 0)
	{
		TEXTMETRIC tm;
		GetTextMetrics(GetDC(hWnd), &tm);
		this->SetHeight(tm.tmHeight + 2);
	}
	if (!CreateXWindow())
		return false;

	SetWindowSubclass(hWnd, EditCallback, 2, (DWORD_PTR)this);

	if (pFont)
		SetFont(pFont);
	
	return true;
}

int CXEdit::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch (HIWORD(wParam))
	{
		case VK_LBUTTON:
				return TRUE;
		case VK_ESCAPE:
			return TRUE;			
	}
	return TRUE;
}

int CXEdit::OnKey(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
		case VK_LBUTTON:
			return TRUE;
		case VK_ESCAPE:
			return TRUE;
	}
	return FALSE;
}

tstring CXEdit::GetText()
{
	szText.clear();
	szText.resize(Edit_GetTextLength(hWnd) + 1);
	Edit_GetText(hWnd, &szText[0], szText.size());
	return szText;
}

void CXEdit::SetKeyPressCallback(std::function<int(void*)> pFunction)
{
	this->pKeyPressCallback = pFunction;
}
