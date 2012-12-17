#ifndef REPAST_EDIT_H_
#define REPAST_EDIT_H_

#include <string>
#include <WINDOWS.H>
#include <COMMCTRL.H>
#pragma comment(lib, "comctl32.lib")

class CEdit  
{
public:
	CEdit();
	virtual ~CEdit();
    bool Create(DWORD style, const RECT &rect,
                HWND parent_hwnd, UINT id);
    bool Initialization(HWND parent_hwnd, UINT id);
    bool GetEditText(std::string &text);
    bool SetEditText(const std::string text);
    bool EnableWindow(BOOL enable = TRUE);

private:
    UINT m_id_;
    HWND m_hwnd_;
};

#endif /* End #define REPAST_EDIT_H_ */
