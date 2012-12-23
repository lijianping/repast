// ComboBox.cpp: implementation of the CComboBox class.
//
//////////////////////////////////////////////////////////////////////

#include "ComboBox.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComboBox::CComboBox()
: m_hwnd_(NULL)
{

}

CComboBox::~CComboBox()
{

}

/*
 * @ Description: This method creates the window combo box control.
 * @ Parameters:
 *       style [in] Specifies the combo box control style.
 *       rect [in] Specifies the combo box control size and position.
 *       parent_hwnd [in] Specifies the combo box control parent window.
 *       id [in] Specifies the combo box control identifier.
 * @ Return Value:
 *       Ture if it is successful; otherwise, it is false.
 **/
bool CComboBox::Create(DWORD style, const RECT &rect,
                       HWND parent_hwnd, UINT id)
{
    m_hwnd_ = CreateWindow(TEXT("combobox"), NULL,
                           WS_CHILD | WS_VISIBLE | style,
                           rect.left, rect.top, rect.right, rect.bottom,
                           parent_hwnd, (HMENU)id,
                           (HINSTANCE)GetWindowLong(parent_hwnd, GWL_HINSTANCE),
                           NULL);
    if (NULL != m_hwnd_)
    {
        m_id_ = id;
        return true;
    }
    return false;
}

/*
 * @ Description: This method initialization the window combo box
 *                control which has been created before.
 * @ Parameters:
 *       parent_hwnd [in] Specifies the combo box control parent window.
 *       id [in] Specifies the combo box control identifier.
 * @ Return Value:
 *       Ture if it is successful; otherwise, it is false.
 **/
bool CComboBox::Initialization(HWND parent_hwnd, UINT id)
{
    /* Get the combo box control's handle */
    m_hwnd_ = GetDlgItem(parent_hwnd, id);
    if (NULL != m_hwnd_)
    {
        m_id_ = id;
        return true;
    }
    return false;
}

/*
 * @ Description: This method adds a string to the end of list
 *                in the list box of combo box.
 * @ Parameters:
 *       item [in] Specifies the string that is to be added.
 * @ Return Value:
 *       Ture if it is successful; otherwise, it is false.
 **/
bool CComboBox::AddString(const std::string item)
{
    int ret = SendMessage(m_hwnd_, CB_ADDSTRING, 0, (LPARAM)item.c_str());
    if (CB_ERR != ret && CB_ERRSPACE != ret)
    {
        return true;
    }
    return false;
}

/*
 * @ Description: This method adds a string to the end of list
 *                in the list box of combo box.
 * @ Parameters:
 *		 index [in] Specifies the zero-based index of the position at which to insert the string.
 *       item [in] Specifies the string that is to be added.
 * @ Return Value:
 *       Ture if it is successful; otherwise, it is false.
 **/
bool CComboBox::InsertString(const int index, const std::string item)
{
	int ret = SendMessage(m_hwnd_, CB_INSERTSTRING, index, (LPARAM)item.c_str());
	if (CB_ERR != ret && CB_ERRSPACE != ret)
	{
		return true;
	}
	return false;
}
/*
 * @ Description: This method deletes a string in the list
 *                box of combo box.
 * @ Parameters:
 *       index [in] Specifies the zero-based index of the 
 *                 string to delete.
 * @ Return Value:
 *       Ture if it is successful; otherwise, it is false.
 **/
bool CComboBox::DeleteString(int index)
{
    int ret = SendMessage(m_hwnd_, CB_DELETESTRING, index, 0);
    if (CB_ERR != ret)
    {
        return true;
    }
    return false;
}

/*
 * @ Description: This method enables or disables mouse and keyboard
 *                input. When input is disabled, input such as mouse
 *                clicks and keystrokes is ignored. When input is 
 *                enabled, the window processes all input.
 * @ Parameters:
 *       enable [in] Specifies whether the given window is to be enabled
 *                   or disabled. If this parameter is TRUE, the window
 *                   will be enabled. If this parameter is FALSE, the
 *                   window will be disabled.
 * @ Return Value:
 *       Indicates the state before the EnableWindow method was called.
 *       The return value is true if the window was previously disabled.
 *       The return value is false if the window was previously enabled.
 **/
bool CComboBox::EnableWindow(const BOOL enable /* = TRUE */)
{
    BOOL ret = ::EnableWindow(m_hwnd_, enable);
    if (ret)
    {
        return true;
    }
    return false;
}

/*
 * @ Description: This method gets the text which is in the edit
 *                box of combo control.
 * @ Parameters:
 *       text [out] The string that gets from combo control's edit box.
 * @ Return Value:
 *       Ture if it is successful; otherwise, it is false.
 **/
bool CComboBox::GetComboBoxText(std::string &text)
{
    int index = SendMessage(m_hwnd_, CB_GETCURSEL, 0, 0);
    TCHAR data[128] = "\0";
    int ret = SendMessage(m_hwnd_, CB_GETLBTEXT, index, (LPARAM)data);
    if (CB_ERR != ret)
    {
        std::string temp(data);
        text = temp;
        return true;
    }
    return false;
}

/*
 * @ Description: This method set the selected item.
 * @ Parameters:
 *       index [in] Specifies the zero-based index of the string to select.
 * @ Return Value:
 *       Ture if it is successful; otherwise, it is false.
 **/
bool CComboBox::SetCurSel(const int index)
{
	int ret = SendMessage(m_hwnd_, CB_SETCURSEL, index, 0);
	if (ret != CB_ERR)
	{
		return true;
	}
	return false;
}