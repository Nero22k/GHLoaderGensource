#pragma once
#include "XControl.h"

#define BS_XOWNERDRAW (WS_VISIBLE | WS_CHILD | BS_OWNERDRAW)
#define BS_XOWNERDRAWTS (WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_OWNERDRAW)

LRESULT CALLBACK OwnerDrawProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

class CXOwnerDrawControl :	public CXControl
{
public:
	CXOwnerDrawControl(CXWindow * pOwner, XID xID, ECXControl ControlType, int x, int y, int w, int h, tstring szText, CXFont * pFont = nullptr);
	~CXOwnerDrawControl();

	virtual bool Create();
	virtual int OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void SetText(tstring szText);
	virtual LRESULT OnDrawItem(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnCtlColor(WPARAM wParam, LPARAM lParam);
	virtual void Draw(HTHEME hTheme, LPDRAWITEMSTRUCT lpDI);

	virtual void RedrawCheck();
	virtual void SetCheck(bool bCheck);
	virtual bool GetCheck();
	virtual void ToggleCheck();
	virtual void SetHot(bool isHot);
	virtual void SetFocus(bool isFocused);
	virtual bool GetFocused();
	virtual void ToggleFocusRect();
	virtual void Disable(bool bDisable);
	virtual bool IsDisabled();
	virtual void SetClicked();
	virtual void LostFocus();
private:
	void DetermineTypeAndState(int & iButtonPart, DWORD & dwState);

protected:
	DWORD dwDTFlags = DT_LEFT | DT_SINGLELINE;
	bool bChecked = false;
	bool bHot = false;
	bool bDisabled = false;
	bool bFocused = false;
	// lol omg
	bool bToggleFocusRect = false;
	bool bClicked = false;
	bool bLostFocus = false;
	bool bFocusDrawn = false;
};

extern std::map<XID, CXOwnerDrawControl*> mODControls;