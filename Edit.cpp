// Edit.cpp: implementation of the CEdit class.
//
//////////////////////////////////////////////////////////////////////

#include "Edit.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEdit::CEdit()
: m_hwnd_(NULL)
{

}

CEdit::~CEdit()
{

}

/*
 * @ Description: This method creates the window edit control.
 * @ Parameters:
 *       style [in] Specifies the edit control style.
 *       rect [in] Specifies the edit control size and position.
 *       parent_hwnd [in] Specifies the edit control parent window.
 *       id [in] Specifies the edit control identifier.
 * @ Return Value:
 *       Ture if it is successful; otherwise, it is false.
 **/
bool CEdit::Create(DWORD style, const RECT &rect,
                   HWND parent_hwnd, UINT id)
{
    m_hwnd_ = CreateWindow(TEXT("edit"), NULL,
                           WS_CHILD | WS_VISIBLE | WS_BORDER | style,
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
 * @ Description: This method initialization the window edit control
 *                which has been created before.
 * @ Parameters:
 *       parent_hwnd [in] Specifies the edit control parent window.
 *       id [in] Specifies the edit control identifier.
 * @ Return Value:
 *       Ture if it is successful; otherwise, it is false.
 **/
bool CEdit::Initialization(HWND parent_hwnd, UINT id)
{
    /* Get the edit control's handle */
    m_hwnd_ = GetDlgItem(parent_hwnd, id);
    if (NULL != m_hwnd_)
    {
        m_id_ = id;
        return true;
    }
    return false;
}

/*
 * @ Description: This method used to get the text of edit control.
 * @ Parameters:
 *       text [out] Specifies the buffer that contain the text in edit control.
 * @ Return Value:
 *       Ture if it is successful; otherwise, it is false.
 **/
bool CEdit::GetEditText(std::string &text)
{
    TCHAR temp[128] = "\0";
    int ret = GetWindowText(m_hwnd_, temp, 128);
    if (0 != ret)
    {
        std::string text_temp(temp);
        text = text_temp;
        return true;
    }
    return false;
}

/*
 * @ Description: This method used to set the text of edit control.
 * @ Parameters:
 *       text [in] Specifies the text that used as new edit text.
 * @ Return Value:
 *       Ture if it is successful; otherwise, it is false.
 **/
bool CEdit::SetEditText(const std::string text)
{
    if (SetWindowText(m_hwnd_, text.c_str()))
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
 *      The return value is true if the window was previously disabled.
 *      The return value is false if the window was previously enabled.
 **/
bool CEdit::EnableWindow(const BOOL enable /* = TRUE */)
{
    BOOL ret = ::EnableWindow(m_hwnd_, enable);
    if (ret)
    {
        return true;
    }
    return false;
}

