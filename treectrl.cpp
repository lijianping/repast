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
 * @ brief: ��ʼ��TreeCtrl�ؼ�
 * @ param: hwnd [in] �ؼ������ھ��
 * @ param: id [in] �ؼ�id
 * @ return: ����ʼ���ɹ�����true�����򷵻�false
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
 * @ brief: ������ڵ�
 * @ param: text [in] �ı�
 * @ return: ���ɹ����ص�ǰitem��handle�����򷵻�NULL
 **/
HTREEITEM TreeCtrl::InsertRootItem(const char *text) {
	TVINSERTSTRUCT tree_insert;
	tree_insert.hParent = NULL;
	tree_insert.hInsertAfter = TVI_ROOT;
	tree_insert.item.mask = TVIF_TEXT;
	tree_insert.item.pszText = (char *)text;
	return TreeView_InsertItem(hwnd_, &tree_insert);
}

/*
 * @ brief: �����ӽڵ�
 * @ param: parent [in] ���ڵ�handle
 * @ param: text [in] �ı�
 * @ return: ���ɹ����ص�ǰitem��handle�����򷵻�NULL
 **/
HTREEITEM TreeCtrl::InsertChildItem(HTREEITEM parent, const char *text) {
	HTREEITEM item = NULL;
	if (parent != NULL) {
		TVINSERTSTRUCT tree_insert;
		tree_insert.hParent = parent;
		tree_insert.hInsertAfter = TVI_LAST;
		tree_insert.item.mask = TVIF_TEXT;
		tree_insert.item.pszText = (char *)text;
		item = TreeView_InsertItem(hwnd_, &tree_insert);
	}
	return item;
}

/*
 * @ breif: ��ȡTree�ؼ���ѡ�е�item
 * @ return: �ɹ�����itme��Ӧ�ľ����ʧ�ܷ���NULL
 **/
HTREEITEM TreeCtrl::GetSelectedItem() {
	return TreeView_GetSelection(hwnd_);
}

/*
 * @ brief: ɾ��tree�ؼ���ָ�������ָ������Ϊroot�
 *          ��ɾ������������
 * @ return: ���ɹ�����true�����򷵻�false
 **/
bool TreeCtrl::DeleteItem(HTREEITEM item) {
	BOOL is_ok = TreeView_DeleteItem(hwnd_, item);
	return (is_ok == TRUE);
}

/*
 * @ breif: ɾ��tree�ؼ������е���
 * @ return: ���ɹ�����ture�����򷵻�false
 **/
bool TreeCtrl::DeleteAllItems() {
	BOOL is_ok =  TreeView_DeleteAllItems(hwnd_);
	return (is_ok == TRUE);
}

/*
 * @ brief: ��ȡtree�ؼ��е�item���ı�����
 * @ param: select [in] ѡ�е�TreeCtrl�е�item��
 * @ param: len [in] ���ݻ�������С
 * @ param: text [out] ���ݻ�����ָ��
 * @ return: ���ɹ�����true�����򷵻�false
 **/
bool TreeCtrl::GetItem(int len, char *text) {
	HTREEITEM select = this->GetSelectedItem();
	if (select == NULL)
		return false;
	memset(text, '0', len); // ��ջ�����
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
	memset(text, '0', len); // ��ջ�����
	TV_ITEM item;
	item.mask = TVIF_TEXT;
	item.pszText = text;
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
 * @ brief: ����tree�ؼ��е�item��ɼ�
 * @ param: item [in] ָ��item��ָ��
 * @ return: ���ɹ�����true�����򷵻�false
 **/
bool TreeCtrl::EnsureVisible(HTREEITEM item) {
	BOOL is_ok = TreeView_EnsureVisible(hwnd_, item);
	return (is_ok == TRUE);
}

/*
 * @ brief: ��ȡ���ڵ�
 * @ return: �ɹ�����item��������򷵻�NULL
 **/
HTREEITEM TreeCtrl::GetRoot() {
	return TreeView_GetRoot(hwnd_);
}

HTREEITEM TreeCtrl::GetChild(HTREEITEM parent) {
	return TreeView_GetChild(hwnd_, parent);
}
/*
 * @ brief: ��ȡitem�ڵ���ֵܽڵ�
 * @ return: �ɹ�����item��������򷵻�NULL
 **/
HTREEITEM TreeCtrl::GetNextSibling(HTREEITEM item) {
	return TreeView_GetNextSibling(hwnd_, item);
}

HTREEITEM TreeCtrl::FindItem(HTREEITEM item, const char *text) {
	HTREEITEM find_item = NULL;
	if (item == NULL) {   // ������ڵ�Ϊ�գ�ֱ�ӷ���
		return find_item;
	}
	char item_text[512];
	while (item != NULL) {
		memset(item_text, 0, sizeof(item_text));
		GetItem(item, 512, item_text); // ��ȡ��ǰ�ڵ��ı�
		if (strcmp(item_text, text) == 0) {  // ����ȣ��򷵻�
			find_item = item;
			return find_item;
		} 
		// ����ȣ��ݹ��ѯ
		HTREEITEM child = GetChild(item); // ��ȡ�ӽڵ�
		if (child != NULL) { // �ӽڵ㲻Ϊ�ղ���
			find_item = FindItem(child, text); // �ݹ�����ӽڵ�
			if (find_item != NULL) {  // ����Ϊ�ձ�ʾ�Ѳ��ҵ�������
				return find_item;
			}
		} else {  // ���ӽڵ�Ϊ�գ������ֵܽڵ�
			item = GetNextSibling(item);  // �����ֵܽڵ�
		}
	}
	return find_item;
}