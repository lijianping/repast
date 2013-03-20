#include "treectrl.h"

TreeCtrl::TreeCtrl() {
}


TreeCtrl::~TreeCtrl() {
}

TreeCtrl::TreeCtrl(HWND hwnd, UINT id) {
	hwnd_ = GetDlgItem(hwnd, id);
	assert(hwnd_ != NULL);
	id_ = id;
}

/*
 * @ brief: 初始化TreeCtrl控件
 * @ param: hwnd [in] 控件父窗口句柄
 * @ param: id [in] 控件id
 * @ return: 若初始化成功返回true，否则返回false
 **/
bool TreeCtrl::Initialization(HWND hwnd, UINT id) {
	hwnd_ = GetDlgItem(hwnd, id);
	if (hwnd_ != NULL) {
		id_ = id;
		return true;
	}
	return false;
}

/*
 * @ brief: 插入根节点
 * @ param: text [in] 文本
 * @ return: 若成功返回当前item的handle，否则返回NULL
 **/
HTREEITEM TreeCtrl::InsertRootItem(TCHAR *text) {
	TVINSERTSTRUCT tree_insert;
	tree_insert.hParent = NULL;
	tree_insert.hInsertAfter = TVI_ROOT;
	tree_insert.item.mask = TVIF_TEXT;
	tree_insert.item.pszText = text;
	return TreeView_InsertItem(hwnd_, &tree_insert);
}

/*
 * @ brief: 插入子节点
 * @ param: parent [in] 父节点handle
 * @ param: text [in] 文本
 * @ return: 若成功返回当前item的handle，否则返回NULL
 **/
HTREEITEM TreeCtrl::InsertChildItem(HTREEITEM parent, TCHAR *text) {
	HTREEITEM item = NULL;
	if (parent != NULL) {
		TVINSERTSTRUCT tree_insert;
		tree_insert.hParent = parent;
		tree_insert.hInsertAfter = TVI_LAST;
		tree_insert.item.mask = TVIF_TEXT;
		tree_insert.item.pszText = text;
		item = TreeView_InsertItem(hwnd_, &tree_insert);
	}
	return item;
}

/*
 * @ breif: 获取Tree控件中选中的item
 * @ return: 成功返回itme对应的句柄，失败返回NULL
 **/
HTREEITEM TreeCtrl::GetSelectedItem() {
	return TreeView_GetSelection(hwnd_);
}

/*
 * @ brief: 删除tree控件中指定的项，若指定的项为root项，
 *          则删除其下所有项
 * @ return: 若成功返回true，否则返回false
 **/
bool TreeCtrl::DeleteItem(HTREEITEM item) {
	BOOL is_ok = TreeView_DeleteItem(hwnd_, item);
	return (is_ok == TRUE);
}

/*
 * @ breif: 删除tree控件中所有的项
 * @ return: 若成功返回ture，否则返回false
 **/
bool TreeCtrl::DeleteAllItems() {
	BOOL is_ok =  TreeView_DeleteAllItems(hwnd_);
	return (is_ok == TRUE);
}

/*
 * @ brief: 获取tree控件中的item项文本内容
 * @ param: select [in] 选中的TreeCtrl中的item项
 * @ param: len [in] 数据缓冲区大小
 * @ param: text [out] 数据缓冲区指针
 * @ return: 若成功返回true，否则返回false
 **/
bool TreeCtrl::GetItem(int len, char *text) {
	HTREEITEM select = this->GetSelectedItem();
	if (select == NULL)
		return false;
	memset(text, '0', len); // 清空缓冲区
	TV_ITEM item;
	item.mask = TVIF_TEXT;
	item.pszText = (TCHAR *)text;
	item.cchTextMax = len;
	item.hItem = select;
	BOOL is_ok = SendDlgItemMessage(GetParent(hwnd_), id_, TVM_GETITEM, TVGN_CARET, (LPARAM)&item);
	return (is_ok == TRUE);
}

bool TreeCtrl::GetItem(HTREEITEM select, int len, char *text) {
	if (select == NULL) {
		return false;
	}
	memset(text, '0', len); // 清空缓冲区
	TV_ITEM item;
	item.mask = TVIF_TEXT;
	item.pszText = (TCHAR *)text;
	item.cchTextMax = len;
	item.hItem = select;
	BOOL is_ok = SendDlgItemMessage(GetParent(hwnd_), id_, TVM_GETITEM, TVGN_CARET, (LPARAM)&item);
	return (is_ok == TRUE);
}

bool TreeCtrl::SelectDropTarget(HTREEITEM item) {
	BOOL is_ok = TreeView_SelectDropTarget(hwnd_, item);
	return (is_ok == TRUE);
}

/*
 * @ brief: 设置tree控件中的item项可见
 * @ param: item [in] 指向item的指针
 * @ return: 若成功返回true，否则返回false
 **/
bool TreeCtrl::EnsureVisible(HTREEITEM item) {
	BOOL is_ok = TreeView_EnsureVisible(hwnd_, item);
	return (is_ok == TRUE);
}