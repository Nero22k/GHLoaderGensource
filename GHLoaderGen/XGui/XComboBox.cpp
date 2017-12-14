#include "XComboBox.h"

CXComboBox::CXComboBox(CXWindow * pOwner, XID xID, int x, int y, int w, int h, tstring szText, CXFont * pFont)
	: CXControl(pOwner, xID, COMBOBOX, x, y, w, h, szText, pFont)
{
	szClass = WC_COMBOBOX;
	SetStyle(WS_XCOMBOBOXDROPLIST); // can't change this after creation :'( //would probably need to re-create the window which would prolly flicka	
}

CXComboBox::~CXComboBox()
{
}

bool CXComboBox::Create()
{
	bool bRet = CXControl::Create();
	AddString(szText);
	ComboBox_SetCurSel(hWnd, 0);
	return bRet;
}

void CXComboBox::AddString(tstring szText)
{
	this->szText = szText;
	ComboBox_AddString(hWnd, szText.c_str());
}

int CXComboBox::GetSelectedIndex()
{
	return ComboBox_GetCurSel(hWnd);
}
