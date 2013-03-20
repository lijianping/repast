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
 * @ brief: 创建TabCtrl控件
 * @ param: hwnd [in] 父窗口句柄
 * @ param: id [in] 控件id
 * @ param: rect [in] 控件窗口大小
 * @ param: style [in] 控件风格
 * @ return: 创建成功返回true，否则返回false
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
 * @ brief: 初始化TabCtrl控件
 * @ param: hwnd [in] 控件父窗口句柄
 * @ param: id [in] 控件id
 * @ return: 若初始化成功返回true，否则返回false
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
 * @ brief: 插入TabCtrl页
 * @ param: index [in] 页索引号
 * @ param: text [in] 页内容
 * @ return: 若成功返回true，否则返回false
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
 * @ brief: 获取当前选中的tab，以0开始
 * @ return: 失败返回-1，否则返回选中的tab号
 **/
int TabCtrl::GetCurSel() {
	return TabCtrl_GetCurSel(hwnd_);
}

/*
 * @ brief: 设置tab控件中当前选中的item
 * @ param: index [in] item索引号
 * @ return: 成功返回之前选择的选中的item索引，否则返回-1
 **/
int TabCtrl::SetCurSel(int index) {
	return TabCtrl_SetCurSel(hwnd_, index);
}

/*
 * @ brief: 设置具有焦点的tab页
 * @ param: index [in] 页索引号
 **/
void TabCtrl::SetCurFocus(int index) {
	TabCtrl_SetCurFocus(hwnd_, index);
}

/*
 * @ brief: 获取具有焦点的tab页
 * @ return: 页索引号
 **/
int TabCtrl::GetCurFocus() {
	return TabCtrl_GetCurFocus(hwnd_);
}

/*
 * @ brief: 获取tab页的大小
 * @ param: rect [out] 页的大小
 * @ return: 若成功返回TRUE，否则返回FALSE
 **/
BOOL TabCtrl::GetClientRect(RECT *rect) {
	return ::GetClientRect(hwnd_, rect);
}

/*
 * @ brief: 高亮选中项
 * @ param: index [in] 索引项
 * @ param: highlight [in] 是否高亮
 * @ return: 成功返回true，否则返回false
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
 * @ brief: 高亮tab控件中的item项，并将其他项设置为非高亮
 * @ param: index [in] 待高亮的item索引
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
 * @ brief: 获取tab控件中item的个数
 * @ return: 成功返回tab控件中item个数，否则返回0
 **/
int TabCtrl::GetItemCount() {
	return TabCtrl_GetItemCount(hwnd_);
}

/*
 * @ brief: 删除TabCtrl控件上的item
 * @ param: index [in] TabCtrl控件item索引
 * @ return: 若成功返回true，否则返回false
 **/
bool TabCtrl::DeleteItem(int index) {
	BOOL is_ok = TabCtrl_DeleteItem(hwnd_, index);
	return (is_ok == TRUE);
}

/*
 * @ brief: 获取TabCtrl控件item标题
 * @ param: index [in] TabCtrl控件item索引
 * @ param: len [in] 数据缓冲区大小
 * @ param: text [out] 数据缓冲区指针
 * @ return: 若成功返回true，否则返回false
 **/
bool TabCtrl::GetItem(int index, int len, char *text) {
	BOOL is_ok = FALSE;
	memset(text, '0', len);   // 清空缓冲区
	TCITEM item;
	item.mask = TCIF_TEXT;
	item.pszText = (TCHAR *)text;
	item.cchTextMax = len;
	is_ok = TabCtrl_GetItem(hwnd_, index, &item);
	return (is_ok == TRUE);

}