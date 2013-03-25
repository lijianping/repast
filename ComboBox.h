#ifndef REPAST_COMBOBOX_H_
#define REPAST_COMBOBOX_H_

#include <string>
#include <WINDOWS.H>
#include <COMMCTRL.H>
#include <ASSERT.H>
#pragma comment(lib, "comctl32.lib")

class CComboBox  
{
public:
	CComboBox();
	CComboBox(HWND hwnd, UINT id);
	virtual ~CComboBox();
    bool Create(DWORD style, const RECT &rect,
                HWND parent_hwnd, UINT id);
    bool Initialization(HWND parent_hwnd, UINT id);
    bool AddString(const std::string item);
	bool InsertString(const int index, const std::string item);
    bool DeleteString(int index);
    bool EnableWindow(BOOL enable = TRUE);
    bool GetComboBoxText(std::string &text);
	bool SetCurSel(const int index);
	int FindString(const char *text);
private:
    UINT m_id_;
    HWND m_hwnd_;
};

#endif /* End #define REPAST_COMBOBOX_H_ */
