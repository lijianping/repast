// MyListView.cpp: implementation of the CMyListView class.
//
//////////////////////////////////////////////////////////////////////

#include "MyListView.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyListView::CMyListView()
    : m_list_view_width_(40),
      m_list_view_height_(30),
      m_list_view_style_(LVS_REPORT),
      m_column_count_(0)
{
    m_origin_point_.x = 0;
    m_origin_point_.y = 0;
}

CMyListView::CMyListView(int id, HINSTANCE hinstance, HWND parent_hwnd) 
    : m_hinstance_(hinstance),
      m_parent_hwnd_(parent_hwnd),
      m_list_view_id_(id),
      m_list_view_width_(40),
      m_list_view_height_(30),
      m_list_view_style_(LVS_REPORT),
      m_column_count_(0)
{
    m_origin_point_.x = 0;
    m_origin_point_.y = 0;
}

CMyListView::~CMyListView()
{

}
/*
 * ����: �ƽ
 * ˵��: ���� list view ��������
 */
void CMyListView::SetListViewInfo(HINSTANCE hinstance,
                                  HWND parent_hwnd,
                                  int origin_x /* = 0 */,
                                  int origin_y /* = 0 */,
                                  int listview_width /* = 40 */,
                                  int listview_height /* = 30 */,
                                  DWORD style /* = LVS_REPORT */)
{
    m_hinstance_ = hinstance;
    m_parent_hwnd_ = parent_hwnd;
    m_origin_point_.x = origin_x;
    m_origin_point_.y = origin_y;
    m_list_view_width_ = listview_width;
    m_list_view_height_ = listview_height;
    m_list_view_style_ = style;
}

/*
 * ����: �ƽ
 * ˵��: ���� list view ����
 *       �ڵ��ô˺���֮ǰ����Ҫ�ȵ���set_list_view_id����
 *       ����list view��id
 * ����ֵ: ���ɹ����ⷵ��true�����򷵻�false��
 */
bool CMyListView::CreateListView()
{
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC  = ICC_TREEVIEW_CLASSES;
    InitCommonControlsEx(&icex);
    m_hwnd_ = CreateWindowEx(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES,
                             WC_LISTVIEW, NULL,
                             WS_CHILD | WS_VISIBLE | LVS_SHOWSELALWAYS | m_list_view_style_,
                             m_origin_point_.x, m_origin_point_.y,
                             m_list_view_width_, m_list_view_height_,
                             m_parent_hwnd_, (HMENU)m_list_view_id_, m_hinstance_, NULL);

    if (m_process_ != NULL)
    {
        m_old_process_ = (WNDPROC)SetWindowLong(m_hwnd_, GWL_WNDPROC, (LONG)m_process_);
    }
    if (m_hwnd_)
    {
        return true;
    }
    return false;
}

/*
 * ˵��: ����list view��ͷ
 * ����:
 *        title [in] ��������
 *       column [in] �кţ���0��ʼ
 *        width [in] �п�
 * ����ֵ: ���ɹ����򷵻�true�����򷵻�false��
 */
bool CMyListView::InsertColumn(std::string title, int column, int width)
{
    LVCOLUMN column_clause;
    column_clause.mask = LVCF_TEXT | LVCF_WIDTH;
    column_clause.pszText = (char *)title.c_str();
    column_clause.cx = width;
	int ret = SendMessage(m_hwnd_, LVM_INSERTCOLUMN, column, (LPARAM)&column_clause);
    if (ret != -1)
    {
        m_column_count_++;
        return true;
    }
    return false;
}

/*
 * ˵��: �������ÿ�еĵ�һ��
 * ����:
 *       text [in] ���õ��ı���ʾ����
 *        row [in] �кţ���0��ʼ
 * ����ֵ: ���ɹ����򷵻�true�����򷵻�false��
 */
bool CMyListView::InsertItem(std::string text, int row)
{
	LVITEM item;
	item.mask = LVIF_TEXT;
	item.iItem = row;
	item.iSubItem = 0;
	item.pszText = (char *)text.c_str();
	int ret = SendMessage(m_hwnd_, LVM_INSERTITEM, 0, (LPARAM)&item);
    return ret != -1;
}

/*
 * ˵��: �������ÿ�еĵ�һ��
 * ����:
 *       text [in] ���õ��ı���ʾ����
 *        row [in] �кţ���0��ʼ
 * ����ֵ: ���ɹ����򷵻�true�����򷵻�false��
 */
bool CMyListView::InsertItem(int text, int row)
{
    LVITEM item;
    char data[10];
    sprintf(data, "%d", text);
    item.mask = LVIF_TEXT;
    item.iItem = row;
    item.iSubItem = 0;
    item.pszText = data;
    int ret = SendMessage(m_hwnd_, LVM_INSERTITEM, 0, (LPARAM)&item);
    return ret != -1;
}

/*
 * ˵��: ������е�ÿ�еĳ���һ��ĺ�������ô˺���֮ǰ��
 *       ��ȷ�����ѵ���InsertItem����������ͷ��
 * ����:
 *       text [in] ���õ��ı���ʾ����
 *        row [in] �кţ���0��ʼ
 *     column [in] �кţ���1��ʼ
 * ����ֵ: ���ɹ����򷵻�true�����򷵻�false��
 */
bool CMyListView::SetItem(std::string text, int row, int column)
{
	LVITEM item;
	item.mask = LVIF_TEXT;
	item.iItem = row;
	item.iSubItem = column;
	item.pszText = (char *)text.c_str();
	int ret = SendMessage(m_hwnd_, LVM_SETITEM, 0, (LPARAM)&item);
    return ret != -1;
}

/*
 * ˵��: ������е�ÿ�еĳ���һ��ĺ�������ô˺���֮ǰ��
 *       ��ȷ�����ѵ���InsertItem����������ͷ��
 * ����:
 *       text [in] ���õ��ı���ʾ����
 *        row [in] �кţ���0��ʼ
 *     column [in] �кţ���1��ʼ
 * ����ֵ: ���ɹ����򷵻�true�����򷵻�false��
 */
bool CMyListView::SetItem(double text, int row, int column)
{
    char data[10];
    sprintf(data, "%.2f", text);
    LVITEM item;
    item.mask = LVIF_TEXT;
    item.iItem = row;
    item.iSubItem = column;
    item.pszText = data;
    int ret = SendMessage(m_hwnd_, LVM_SETITEM, 0, (LPARAM)&item);
    return ret != -1;
}

/*
 * ˵��: ������е�ÿ�еĳ���һ��ĺ�������ô˺���֮ǰ��
 *       ��ȷ�����ѵ���InsertItem����������ͷ��
 * ����:
 *       text [in] ���õ��ı���ʾ����
 *        row [in] �кţ���0��ʼ
 *     column [in] �кţ���1��ʼ
 * ����ֵ: ���ɹ����򷵻�true�����򷵻�false��
 */
bool CMyListView::SetItem(int text, int row, int column)
{
    char data[10];
    sprintf(data, "%d", text);
    LVITEM item;
    item.mask = LVIF_TEXT;
    item.iItem = row;
    item.iSubItem = column;
    item.pszText = data;
    int ret = SendMessage(m_hwnd_, LVM_SETITEM, 0, (LPARAM)&item);
    return ret != -1;
}

/*
 * ˵��: ����ȫ��ѡ�к�������
 * ����:
 *       style [in] �����õķ�� LVS_EX_CHECKBOXES��LVS_EX_GRIDLINES��LVS_EX_FULLROWSELECT
 */
void CMyListView::SetSelectAndGrid(DWORD style)
{
	ListView_SetExtendedListViewStyle(m_hwnd_, style); 
}

/*
 * ����: �ƽ
 * ˵��: ��ȡlist view��һ��item������
 * ����:
 *          row [in]  �кţ���0��ʼ
 *       column [in]  �кţ���0��ʼ
 *         text [out] ����
 * ����ֵ: ���ػ�ȡ�����ݳ���
 **/
int CMyListView::GetItem(int row, int column, std::string &text)
{
    char data[512] = {0};
    LVITEM item;
    item.mask = LVIF_PARAM | LVIF_TEXT;
    item.cchTextMax = 512;
    item.iSubItem = column;
    item.pszText = data;
    SendMessage(m_hwnd_, LVM_GETITEMTEXT, (WPARAM)row, (LPARAM)&item);
    std::string text_temp(item.pszText);
    text = text_temp;
    return text.length();
}

/*
 * ����: �ƽ
 * ˵��: ��ȡlist view����
 * ����ֵ: list view������
 **/
int CMyListView::GetItemCount()
{
    return SendMessage(m_hwnd_, LVM_GETITEMCOUNT, 0, 0);
}

void CMyListView::SetSelectd(const int index)
{
    ListView_SetItemState(m_hwnd_, index, LVIS_SELECTED, LVIS_SELECTED);
}

/*
 * ˵��: ��ȡlist view�й���е��к�
 * ����ֵ: ��������ȡ���кţ���0��ʼ
 * **/
int CMyListView::GetCurSel() const
{
    return ListView_GetSelectionMark(m_hwnd_);
}


