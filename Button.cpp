// Button.cpp: implementation of the CButton class.
//
//////////////////////////////////////////////////////////////////////

#include "Button.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CButton::CButton()
: m_hwnd_(NULL)
{

}

CButton::~CButton()
{

}

/*
 * @ Description: This method creates the window button control.
 * @ Parameters:
 *      caption [in] Specifies the button control text.
 *      style [in] Specifies the button control style.
 *      rect [in] Specifies the button control size and position.
 *      parent_hwnd [in] Specifies the button control parent window.
 *      id [in] Specifies the button control identifier.
 * @ Return Value:
 *      Ture if it is successful; otherwise, it is false.
 **/
bool CButton::Create(std::string caption, DWORD style,
                     const RECT &rect, HWND parent_hwnd, UINT id)
{
   
    m_hwnd_ = CreateWindow(TEXT("button"), caption.c_str(),
                           WS_CHILD | WS_VISIBLE | style,
                           rect.left, rect.top, rect.right,
                           rect.bottom, parent_hwnd,
                           (HMENU)id,
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
 * @ Description: This method initialization the window button control
 *               which has been created before.
 * @ Parameters:
 *      parent_hwnd [in] Specifies the button control parent window.
 *      id [in] Specifies the button control identifier.
 * @ Return Value:
 *      Ture if it is successful; otherwise, it is false.
 **/
bool CButton::Initialization(HWND parent_hwnd, UINT id)
{
    /* Get the button control's handle */
    m_hwnd_ = GetDlgItem(parent_hwnd, id);
    if (NULL != m_hwnd_)
    {
        m_id_ = id;
        return true;
    }
    return false;
}

/*
 * @ Description: This method check the button is in checked state. 
 * @ Return Value:
 *       if it is in checked state, the return value is true;
 *       otherwise, the return value is false.
 **/
bool CButton::IsChecked()
{
    long ret = SendMessage(m_hwnd_, BM_GETCHECK, 0, 0);
    if (BST_CHECKED == ret)
    {
        return true;
    }
    return false;
}

/*
 * @ Description: This method sets the check state of a button control. 
 * @ Parameters:
 *      checked [in] Specifies the check state. True stands for checked.
 *                   FALSE stands for unchecked.
 * @ Return Value:
 *      This function always returns true.
 **/
bool CButton::SetChecked(const BOOL checked /* = FALSE */)
{
    BOOL checked_state;
    if (checked)
    {
        checked_state = BST_CHECKED;
    }
    else
    {
        checked_state = BST_UNCHECKED;
    }
    SendMessage(m_hwnd_, BM_SETCHECK, (WPARAM)checked_state, 0);
    return true;
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
 *      The return value is false if the window was previously enabled.
 **/
bool CButton::EnableWindow(const BOOL enable /* = TRUE */)
{
    BOOL ret = ::EnableWindow(m_hwnd_, enable);
    if (ret)
    {
        return true;
    }
    return false;
}
