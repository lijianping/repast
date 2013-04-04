// ListView.cpp: implementation of the CListView class.
//
//////////////////////////////////////////////////////////////////////

#include "ListView.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListView::CListView()
: m_hwnd_(NULL),
  m_new_process_(NULL),
  m_old_process_(NULL),
  m_is_set_process_(false)
{
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC  = ICC_TREEVIEW_CLASSES;
    InitCommonControlsEx(&icex);
}

CListView::CListView(HWND hwnd, UINT id)
: m_hwnd_(NULL),
m_new_process_(NULL),
m_old_process_(NULL),
m_is_set_process_(false)
{
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC  = ICC_TREEVIEW_CLASSES;
    InitCommonControlsEx(&icex);
	m_hwnd_ = GetDlgItem(hwnd, id);
	assert(m_hwnd_ != NULL);
	m_id_ = id;
}

CListView::~CListView()
{

}

/*
 * @ Description: This method creates the window combo box control.
 * @ Parameters:
 *      style [in] Specifies the combo box control style.
 *      rect [in] Specifies the combo box control size and position.
 *      parent_hwnd [in] Specifies the combo box control parent window.
 *      id [in] Specifies the combo box control identifier.
 * @ Return Value:
 *      Ture if it is successful; otherwise, it is false.
 **/
bool CListView::Create(DWORD style, const RECT &rect,
                       HWND parent_hwnd, UINT id)
{
    m_hwnd_ = CreateWindowEx(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES,
                             WC_LISTVIEW, NULL,
                             WS_CHILD | WS_VISIBLE | style,
                             rect.left, rect.top, rect.right, rect.bottom,
                             parent_hwnd, (HMENU)id,
                             (HINSTANCE)GetWindowLong(parent_hwnd, GWL_HINSTANCE),
                             NULL);
    if (NULL != m_new_process_)
    {
        m_is_set_process_ = true;
        m_old_process_ = (WNDPROC)SetWindowLong(m_hwnd_,
                                                GWL_WNDPROC,
                                                (LONG)m_new_process_);
    }
    if (NULL != m_hwnd_)
    {
        m_id_ = id;
        return true;
    }
    return false;
}

/*
 * @ Description: This method initialization the window list view
 *               control which has been created before.
 * @ Parameters:
 *      parent_hwnd [in] Specifies the list view control parent window.
 *      id [in] Specifies the list view control identifier.
 * @ Return Value:
 *      Ture if it is successful; otherwise, it is false.
 **/
bool CListView::Initialization(HWND parent_hwnd, UINT id)
{
    /* Get the list view control's handle */
    m_hwnd_ = GetDlgItem(parent_hwnd, id);
    if (NULL != m_hwnd_)
    {
        m_id_ = id;
        return true;
    }
    return false;
}

/*
 * @ Description: This method Inserts a new column in a list view control.
 * @ Parameters:
 *      column [in] The index of the new column.
 *      width [in] The new column's width.
 *      column_data [in] The column's heading text.
 * @ Return Value:
 *      The index of the new column indicates success. 
 *      -1 indicates failure.
 **/
int CListView::InsertColumn(int column, int width, std::string column_head)
{
    LVCOLUMN column_data;
    column_data.mask = LVCF_TEXT | LVCF_WIDTH;
    column_data.cx = width;
    column_data.pszText = const_cast<char *>(column_head.c_str());
    return SendMessage(m_hwnd_, LVM_INSERTCOLUMN,
                       column, (WPARAM)&column_data);
}

/*
 * @ Description: This method Inserts a new item in a list view control.
 * @ Parameters:
 *      item [in] Index of the item to be inserted.
 *      item_text [in] The item's text.
 * @ Return Value:
 *      The index of the new item indicates success. 
 *      -1 indicates failure.
 **/
int CListView::InsertItem(int item, std::string item_text)
{
    LVITEM item_data;
    item_data.mask = LVIF_TEXT;
    item_data.iItem = item;
    item_data.iSubItem = 0;
    item_data.pszText = const_cast<char *>(item_text.c_str());
    return SendMessage(m_hwnd_, LVM_INSERTITEM, 0, (WPARAM)&item_data);
}

int CListView::InsertItem(int item, int item_values)
{
	char item_text[32]={0};
	LVITEM item_data;
    item_data.mask = LVIF_TEXT;
    item_data.iItem = item;
    item_data.iSubItem = 0;
	itoa(item_values, item_text, 10);
    item_data.pszText = item_text;
	return SendMessage(m_hwnd_, LVM_INSERTITEM, 0, (WPARAM)&item_data);
}
/*
 * @ Description: This method Sets some or all of a list 
 *               view item's attributes.
 * @ Parameters:
 *      item [in] Index of the item whose attributes are to be set.
 *      subitem [in] Index of the subitem whose attributes ate to be set.
 *      item_text [in] The item's text.
 * @ Return Value:
 *      True if it is successful, otherwise, it is false.
 **/
bool CListView::SetItem(int item, int subitem, std::string item_text)
{
    LVITEM item_data;
    item_data.mask = LVIF_TEXT;
    item_data.iItem = item;
    item_data.iSubItem = subitem;
    item_data.pszText = const_cast<char *>(item_text.c_str());
    BOOL ret = SendMessage(m_hwnd_, LVM_SETITEM, 0, (WPARAM)&item_data);
    if (TRUE == ret)
    {
        return true;
    }
    return false;
}

/*
 * @ Description: This method Sets some or all of a list 
 *               view item's attributes.
 * @ Parameters:
 *      item [in] Index of the item whose attributes are to be set.
 *      subitem [in] Index of the subitem whose attributes ate to be set.
 *      item_text [in] The item's text.
 * @ Return Value:
 *      True if it is successful, otherwise, it is false.
 **/
bool CListView::SetItem(int item, int subitem, int item_text)
{
	LVITEM item_data;
	char temp[10] = "\0";
	sprintf(temp, "%d", item_text);
    item_data.mask = LVIF_TEXT;
    item_data.iItem = item;
    item_data.iSubItem = subitem;
	item_data.pszText = temp;
	BOOL ret = SendMessage(m_hwnd_, LVM_SETITEM, 0, (WPARAM)&item_data);
    if (TRUE == ret)
    {
        return true;
    }
    return false;
}

/*
 * @ Description: This method Sets some or all of a list 
 *               view item's attributes.
 * @ Parameters:
 *      item [in] Index of the item whose attributes are to be set.
 *      subitem [in] Index of the subitem whose attributes ate to be set.
 *      item_text [in] The item's text.
 * @ Return Value:
 *      True if it is successful, otherwise, it is false.
 **/
bool CListView::SetItem(int item, int subitem, double item_text)
{
	LVITEM item_data;
	char temp[10] = "\0";
	sprintf(temp, "%.2f", item_text);
    item_data.mask = LVIF_TEXT;
    item_data.iItem = item;
    item_data.iSubItem = subitem;
	item_data.pszText = temp;
	BOOL ret = SendMessage(m_hwnd_, LVM_SETITEM, 0, (WPARAM)&item_data);
    if (TRUE == ret)
    {
        return true;
    }
    return false;
}

std::string CListView::GetItem(int item, int subitem)
{
	char data[1024];
	memset(data, 0, sizeof(data));
	ListView_GetItemText(m_hwnd_, item, subitem, data, 1024);
	return std::string(data);
}

int CListView::GetNextSelected(int index) {
	return ListView_GetNextItem(m_hwnd_, index, LVNI_SELECTED);
}
/*
 * @Description: Get the number of items in a list view control.
 * @Return Value:
 *      The number of items in the list view control.
 **/
int CListView::GetItemCount()
{	
    return SendMessage(m_hwnd_, LVM_GETITEMCOUNT, 0, 0);
}

/*
 * @ Description: Get the number of columns in a list view control.
 * @ Return Value:
 *      The number of columns in the list view control.
 * @ Hit: Maybe this function has something wrong.
 **/
int CListView::GetColumnCount()
{
    int count(0);
    TCHAR data[128] = "\0";
    LVCOLUMN col;
    col.mask = LVIF_TEXT | LVCF_WIDTH;
    col.cchTextMax = 128;
    col.pszText = data;
    while (TRUE == SendMessage(m_hwnd_, LVM_GETCOLUMN, count, (WPARAM)&col))
    {
        count++;
    }
    return count;
}

/*
 **/
int CListView::GetSelectedCount()
{
	return ListView_GetSelectedCount(m_hwnd_);
}

/*
 * @ Description: Retrieves the selection mark of a list view control.
 * @ Return Value:
 *      The zero-based selection mark, or -1 if there is no selection.
 **/
int CListView::GetSelectionMark()
{
    /*return SendMessage(m_hwnd_, LVM_GETSELECTIONMARK, 0, 0);*/
	return ListView_GetSelectionMark(m_hwnd_);
}

/*
 * @ Description: Sets the selection mark of a list view control.
 * @ parameters:
 *      index [in] The zero-based index of first item in a multiple selection.
 * @ Return Value:
 *      The previous selection mark, or -1 if there was no selection mark.
 **/
int CListView::SetSelectionMark(int index)
{
    return SendMessage(m_hwnd_, LVM_SETSELECTIONMARK, 0, index);
}

/*
 * @ Description: Changes the state of an item in a list view control.
 * @ parameters:
 *      item [in] Index of the item whose state is to be set.
 *      state [in] New values for the state bits.
 *      mask [in] Mask specifying which state bits to change.
 * @ Return Value:
 *      If it is success, the return value is true; otherwise,
 *      the return value is false.
 **/
bool CListView::SetItemState(int item, UINT state, UINT mask)
{
    LVITEM item_state;
    item_state.mask = LVIF_STATE;
    item_state.stateMask = mask;
    item_state.state = state;
    if (TRUE == SendMessage(m_hwnd_, LVM_SETITEMSTATE,
                            item, (LPARAM)&item_state))
    {
        return true;
    }

    return false;
}

/*
 * @ Description: Deletes an item from the list view control.
 * @ parameters:
 *      index [in] Specifies the index of the item to be deleted.
 * @ Return Value:
 *      If it is success, return value is true; otherwise return false.
 **/
bool CListView::DeleteItem(int item)
{
   if (TRUE == SendMessage(m_hwnd_, LVM_DELETEITEM, item, 0))
   {
       return true;
   }
   return false;
}

/*
 * @ Description: Deletes an item from the list view control.
 * @ Return Value:
 *      If it is success, return value is true; otherwise return false.
 **/
bool CListView::DeleteAllItems()
{
    if (TRUE == SendMessage(m_hwnd_, LVM_DELETEALLITEMS, 0, 0))
    {
        return true;
    }
    return false;
}

void CListView::SetSelectAndGrid(DWORD style)
{
    ListView_SetExtendedListViewStyle(m_hwnd_, style | LVS_EX_INFOTIP); 
}

void CListView::SetEditLabel(const int item)
{
	ListView_EditLabel(m_hwnd_, item);
}

/*
 * @ 说明: 设置list的窗口处理过程函数
 * @ 参数:
 *         proc [in] 待设置的窗口处理过程
 * @ 返回值:
 *           返回之前的窗口处理过程函数
 **/
WNDPROC CListView::SetListProc(const WNDPROC proc)
{
	return (WNDPROC)SetWindowLong(m_hwnd_, GWL_WNDPROC, (LONG)proc);
}

void CListView::SetExtendStyle(DWORD style) {
	ListView_SetExtendedListViewStyle(m_hwnd_, style);
}

/*
 * @ brief: find the item
 * @ param: index [in] 查找的列，第一列可忽略
 * @ param: item [in] 查找的item项
 * @ return: 返回查找项的行号，失败返回-1
 **/
int CListView::FindItem(std::string item) {
	LVFINDINFO find_info;
	find_info.flags = LVFI_PARTIAL | LVFI_STRING;
	find_info.psz = item.c_str();
	// ListView_FindItem(m_hwnd_, -1, &find_info);
	return SendMessage(m_hwnd_, LVM_FINDITEM, -1, (LPARAM)&find_info);
}

int CListView::FindItem(int index, std::string item) {
	int row = GetItemCount();
	for (int i = 0; i < row; ++i) {
		std::string text = GetItem(i, index);
		if (item == text) {
			return i;
		}
	}
	return -1;
}