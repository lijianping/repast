#ifndef REPAST_BUTTON_H_
#define REPAST_BUTTON_H_

#include <string>
#include <WINDOWS.H>
#include <COMMCTRL.H>
#pragma comment(lib, "comctl32.lib")

class CButton  
{
public:
	CButton();
	virtual ~CButton();
    bool Create(std::string caption, DWORD style,
                const RECT &rect, HWND parent_hwnd, UINT id);
    bool Initialization(HWND parent_hwnd, UINT id);
    bool IsChecked();
    bool SetChecked(const BOOL checked = FALSE);
    bool EnableWindow(const BOOL enable = TRUE);
    inline void set_id(CONST UINT id);
    inline UINT id() const;
private:
    UINT m_id_;
    HWND m_hwnd_;
};

/*
 * @ Description: This method used to set the button control's id.
 * @ Parameters:
 *      id [in] Specifies the button control identifier.
 **/
void CButton::set_id(CONST UINT id)
{
    m_id_ = id;
}

/*
 * @ Description: This method used to get the button control's id.
 * @ Return value:
 *      This method return the button control's id.
 **/
UINT CButton::id() const
{
    return m_id_;
}

#endif /* #define REPAST_BUTTON_H_ */
