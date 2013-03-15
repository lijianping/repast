#ifndef REPAST_TAB_H_
#define REPAST_TAB_H_

#include <string>
#include <WINDOWS.H>
#include <COMMCTRL.H>
#pragma comment(lib, "comctl32.lib")

class CTab  
{
public:
	CTab();
	virtual ~CTab();
	bool Create(DWORD style, const RECT &rect,
                HWND parent_hwnd, UINT id);
	bool Initialization(HWND parent_hwnd, UINT id);
	bool InsertItem(const int index, std::string text);
	int GetCurSel();
	void SetCurFocus(const int index);
	int GetCurFocus();
	BOOL GetClientRect(RECT *rc);
private:
	HWND m_hwnd_;
	UINT m_id_;
};

#endif 
