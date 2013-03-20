#include "tabctrl.h"


TabCtrl::TabCtrl() {
}


TabCtrl::~TabCtrl() {
}

TabCtrl::TabCtrl(HWND hwnd, UINT id) {
	hwnd_ = GetDlgItem(hwnd, id);
	assert(hwnd_ != NULL);
	id_ = id;
}

/*
 * @ brief: ����TabCtrl�ؼ�
 * @ param: hwnd [in] �����ھ��
 * @ param: id [in] �ؼ�id
 * @ param: rect [in] �ؼ����ڴ�С
 * @ param: style [in] �ؼ����
 * @ return: �����ɹ�����true�����򷵻�false
 **/
bool TabCtrl::CreateTab(HWND hwnd, UINT id, const RECT rect, const DWORD style) {
	hwnd_ = CreateWindow(TEXT("tab"), NULL, TCS_TABS | TCS_FIXEDWIDTH | \
		                 WS_CHILD | WS_VISIBLE | WS_BORDER | style, \
		                 rect.left, rect.top, rect.right, rect.bottom, \
		                 hwnd, (HMENU)id, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), \
						 NULL);
	if (NULL != hwnd_)
	{
		id_ = id;
		return true;
	}
	return false;
}

/*
 * @ brief: ��ʼ��TabCtrl�ؼ�
 * @ param: hwnd [in] �ؼ������ھ��
 * @ param: id [in] �ؼ�id
 * @ return: ����ʼ���ɹ�����true�����򷵻�false
 **/
bool TabCtrl::Initialization(HWND hwnd, UINT id) {
	hwnd_ = GetDlgItem(hwnd, id);
	if (hwnd_ != NULL) {
		id_ = id;
		return true;
	}
	return false;
}

/*
 * @ brief: ����TabCtrlҳ
 * @ param: index [in] ҳ������
 * @ param: text [in] ҳ����
 * @ return: ���ɹ�����true�����򷵻�false
 **/
bool TabCtrl::InsertItem(int index, TCHAR *text) {
	TCITEM tab_item;
	tab_item.mask = TCIF_TEXT;
	tab_item.pszText = text;
	if (-1 == TabCtrl_InsertItem(hwnd_, index, &tab_item)) {
		return false;
	}
	return true;
}

/*
 * @ brief: ��ȡ��ǰѡ�е�tab����0��ʼ
 * @ return: ʧ�ܷ���-1�����򷵻�ѡ�е�tab��
 **/
int TabCtrl::GetCurSel() {
	return TabCtrl_GetCurSel(hwnd_);
}

/*
 * @ brief: ����tab�ؼ��е�ǰѡ�е�item
 * @ param: index [in] item������
 * @ return: �ɹ�����֮ǰѡ���ѡ�е�item���������򷵻�-1
 **/
int TabCtrl::SetCurSel(int index) {
	return TabCtrl_SetCurSel(hwnd_, index);
}

/*
 * @ brief: ���þ��н����tabҳ
 * @ param: index [in] ҳ������
 **/
void TabCtrl::SetCurFocus(int index) {
	TabCtrl_SetCurFocus(hwnd_, index);
}

/*
 * @ brief: ��ȡ���н����tabҳ
 * @ return: ҳ������
 **/
int TabCtrl::GetCurFocus() {
	return TabCtrl_GetCurFocus(hwnd_);
}

/*
 * @ brief: ��ȡtabҳ�Ĵ�С
 * @ param: rect [out] ҳ�Ĵ�С
 * @ return: ���ɹ�����TRUE�����򷵻�FALSE
 **/
BOOL TabCtrl::GetClientRect(RECT *rect) {
	return ::GetClientRect(hwnd_, rect);
}

/*
 * @ brief: ����ѡ����
 * @ param: index [in] ������
 * @ param: highlight [in] �Ƿ����
 * @ return: �ɹ�����true�����򷵻�false
 **/
bool TabCtrl::HighlightItem(int index, bool highlight /* = true */) {
	BOOL is_ok;
	if (highlight) {
		is_ok = TabCtrl_HighlightItem(hwnd_, index, 255);
	} else {
		is_ok = TabCtrl_HighlightItem(hwnd_, index, 0);
	}
	return (is_ok == TRUE);
}

/*
 * @ brief: ����tab�ؼ��е�item���������������Ϊ�Ǹ���
 * @ param: index [in] ��������item����
 **/
void TabCtrl::Highlight(int index) {
	int all_item = this->GetItemCount();
	for (int i = 0; i < all_item; ++i) {
		if (i == index) {
			this->HighlightItem(i, true);
		} else {
			this->HighlightItem(i, false);
		}
	}
}

/*
 * @ brief: ��ȡtab�ؼ���item�ĸ���
 * @ return: �ɹ�����tab�ؼ���item���������򷵻�0
 **/
int TabCtrl::GetItemCount() {
	return TabCtrl_GetItemCount(hwnd_);
}

/*
 * @ brief: ɾ��TabCtrl�ؼ��ϵ�item
 * @ param: index [in] TabCtrl�ؼ�item����
 * @ return: ���ɹ�����true�����򷵻�false
 **/
bool TabCtrl::DeleteItem(int index) {
	BOOL is_ok = TabCtrl_DeleteItem(hwnd_, index);
	return (is_ok == TRUE);
}

/*
 * @ brief: ��ȡTabCtrl�ؼ�item����
 * @ param: index [in] TabCtrl�ؼ�item����
 * @ param: len [in] ���ݻ�������С
 * @ param: text [out] ���ݻ�����ָ��
 * @ return: ���ɹ�����true�����򷵻�false
 **/
bool TabCtrl::GetItem(int index, int len, char *text) {
	BOOL is_ok = FALSE;
	memset(text, '0', len);   // ��ջ�����
	TCITEM item;
	item.mask = TCIF_TEXT;
	item.pszText = (TCHAR *)text;
	item.cchTextMax = len;
	is_ok = TabCtrl_GetItem(hwnd_, index, &item);
	return (is_ok == TRUE);

}