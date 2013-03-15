// Tab.cpp: implementation of the CTab class.


#include "Tab.h"

CTab::CTab()
{

}

CTab::~CTab()
{

}

bool CTab::Create(DWORD style, const RECT &rect, HWND parent_hwnd, UINT id) {
	m_hwnd_ = CreateWindow(TEXT("tab"), NULL, TCS_TABS | TCS_FIXEDWIDTH |
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

bool CTab::Initialization(HWND parent_hwnd, UINT id)
{
    /* Get the table control's handle */
    m_hwnd_ = GetDlgItem(parent_hwnd, id);
    if (NULL != m_hwnd_)
    {
        m_id_ = id;
        return true;
    }
    return false;
}

bool CTab::InsertItem(const int index, std::string text) {
	TCITEM tab_item;
	tab_item.mask = TCIF_TEXT;
	tab_item.pszText = (char *)text.c_str();
	if (-1 == TabCtrl_InsertItem(m_hwnd_, index, &tab_item)) {
		return false;
	}
	return true;
}

/*
 * @ brief: 获取当前选中的tab，以0开始
 * @ return: 失败返回-1，否则返回选中的tab号
 **/
int CTab::GetCurSel() {
	return TabCtrl_GetCurSel(m_hwnd_);
}

void CTab::SetCurFocus(const int index) {
	TabCtrl_SetCurFocus(m_hwnd_, index);
}

int CTab::GetCurFocus() {
	return TabCtrl_GetCurFocus(m_hwnd_);
}

BOOL CTab::GetClientRect(RECT *rc) {
	return ::GetClientRect(m_hwnd_, rc);
}