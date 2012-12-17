#ifndef REPAST_LISTVIEW_H_
#define REPAST_LISTVIEW_H_

#include <string>
#include <WINDOWS.H>
#include <COMMCTRL.H>
#pragma comment(lib, "comctl32.lib")

class CListView  
{
public:
	CListView();
	virtual ~CListView();
    inline void set_new_process(WNDPROC process);
    inline WNDPROC old_process();
    inline bool is_set_process() const;
    bool Create(DWORD style, const RECT &rect,
                HWND parent_hwnd, UINT id);
    bool Initialization(HWND parent_hwnd, UINT id);
    int InsertColumn(int column, int width, std::string column_head);
    int InsertItem(int item, std::string item_text);
    bool SetItem(int item, int subitem, std::string item_text);
	bool SetItem(int item, int subitem, int item_text);
	bool SetItem(int item, int subitem, double item_text);
    int GetItemCount();
    int GetColumnCount();
    int GetSelectionMark();
    int SetSelectionMark(int index);
    bool SetItemState(int item, UINT state, UINT mask);
    bool DeleteItem(int item);
    bool DeleteAllItems();
    void SetSelectAndGrid(DWORD style);

private:
    UINT m_id_;
    HWND m_hwnd_;
    bool m_is_set_process_;
    WNDPROC m_new_process_;
    WNDPROC m_old_process_;
};

/*
 * @Description: This method set the list view control's processes.
 * @Parameters:
 *      process [in] The processes that set to the list view.
 **/
void CListView::set_new_process(WNDPROC process)
{
    m_new_process_ = process;
}

/*
 * @Description: This method get the list view's window processes.
 * @Return Value:
 *      The return value is the list view's default window processes.
 **/
WNDPROC CListView::old_process()
{
    return m_old_process_;
}

bool CListView::is_set_process() const
{
    return m_is_set_process_;
}

#endif // !defined(AFX_LISTVIEW_H__77342954_5258_41DF_87F6_267D6A706457__INCLUDED_)
