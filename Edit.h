#ifndef REPAST_EDIT_H_
#define REPAST_EDIT_H_

#include <string>
#include <ASSERT.H>
#include <WINDOWS.H>
#include <COMMCTRL.H>
#pragma comment(lib, "comctl32.lib")

class CEdit  
{
public:
	CEdit();
	CEdit(HWND parent, UINT id);
	virtual ~CEdit();
    bool Create(DWORD style, const RECT &rect,
                HWND parent_hwnd, UINT id);
    bool Initialization(HWND parent_hwnd, UINT id);
    bool GetEditText(std::string &text);
    bool SetEditText(const std::string text);
    bool EnableWindow(BOOL enable = TRUE);
	int CanUndo();
	void EmptyUndoBuffer();
	void Empty();
	bool SetReadOnly(bool read_only = true);

private:
    UINT m_id_;
    HWND m_hwnd_;
};

#endif /* End #define REPAST_EDIT_H_ */
