// Static.cpp: implementation of the CStatic class.
//
//////////////////////////////////////////////////////////////////////

#include "Static.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStatic::CStatic()
: m_hwnd_(NULL)
{

}

CStatic::~CStatic()
{

}

/*
 * @ Description: This method creates the window static control.
 * @ Parameters:
 *      text [in] Specifies the text to place in the control.
 *      style [in] Specifies the static control style.
 *      rect [in] Specifies the static control size and position.
 *      parent_hwnd [in] Specifies the static control parent window.
 *      id [in] Specifies the static control identifier.
 * @ Return Value:
 *      Ture if it is successful; otherwise, it is false.
 **/
bool CStatic::Create(std::string text, DWORD style,
                     const RECT &rect, HWND parent_hwnd,
                     UINT id /* = 0xFFFF */)
{
    m_hwnd_ = CreateWindow(TEXT("static"), text.c_str(),
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
