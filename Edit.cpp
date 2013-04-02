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

CEdit::CEdit(HWND parent, UINT id) {
	m_hwnd_ = GetDlgItem(parent, id);
	assert(m_hwnd_ != NULL);
	m_id_ = id;
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
    TCHAR temp[1024] = "\0";
    int ret = GetWindowText(m_hwnd_, temp, 1024);
    if (0 != ret)
    {
        std::string text_temp(temp);
        text = text_temp;
        return true;
    }
    return false;
}

/*
 * @ brief: 获取编辑框中的数字型数据
 * @ param: data [out] 获取的值
 * @ param: is_signed [in] 是否为有符号数 若为true则表示是
 * @ return: 若成功返回true
 **/
bool CEdit::GetEidtInt(int &data, bool is_signed /* = true */) {
	BOOL is_ok;
	int temp = ::GetDlgItemInt(m_hwnd_, m_id_, &is_ok, is_signed);
	if (is_ok == TRUE) {
		data = temp;
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

int CEdit::CanUndo() {
	return ::SendMessage(this->m_hwnd_, EM_CANUNDO, (WPARAM)0, (LPARAM)0);
}

void CEdit::EmptyUndoBuffer() {
	::SendMessage(this->m_hwnd_, EM_EMPTYUNDOBUFFER, (WPARAM)0, (LPARAM)0);
}

void CEdit::Empty() {
	::SetWindowText(m_hwnd_, "");
}

/*
 * @ brief: 设置编辑框为只读模式
 * @ param: read_only [in] 若为true则表示为只读模式，否则为去掉只读模式
 * @ return: 若成功返回true，否则返回false
 **/
bool CEdit::SetReadOnly(bool read_only /* = true */) {
	int ret = ::SendMessage(m_hwnd_, EM_SETREADONLY, (WPARAM)&read_only, 0);
	return (ret != 0);
}

bool CEdit::SetV(int x /* = 5*/) {
	RECT rect;
	GetClientRect(m_hwnd_, &rect);
	::OffsetRect(&rect,0, x); 
	::SendMessage(m_hwnd_,EM_SETRECT,0,(LPARAM)&rect);
	return true;
}