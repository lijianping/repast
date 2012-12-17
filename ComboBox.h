#ifndef REPAST_COMBOBOX_H_
#define REPAST_COMBOBOX_H_

#include <string>
#include <WINDOWS.H>
#include <COMMCTRL.H>
#pragma comment(lib, "comctl32.lib")

class CComboBox  
{
public:
	CComboBox();
	virtual ~CComboBox();
    bool Create(DWORD style, const RECT &rect,
                HWND parent_hwnd, UINT id);
    bool Initialization(HWND parent_hwnd, UINT id);
    bool AddString(const std::string item);
    bool DeleteString(int index);
    bool EnableWindow(BOOL enable = TRUE);
    bool GetComboBoxText(std::string &text);

private:
    UINT m_id_;
    HWND m_hwnd_;
};

#endif /* End #define REPAST_COMBOBOX_H_ */
