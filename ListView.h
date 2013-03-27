#ifndef REPAST_LISTVIEW_H_
#define REPAST_LISTVIEW_H_

#include <string>
#include <WINDOWS.H>
#include <COMMCTRL.H>
#include <ASSERT.H>
#pragma comment(lib, "comctl32.lib")

class CListView  
{
public:
	CListView();
	CListView(HWND hwnd, UINT id);
	virtual ~CListView();
    inline void set_new_process(WNDPROC process);
    inline WNDPROC old_process();
	inline HWND hwnd();
    inline bool is_set_process() const;
    bool Create(DWORD style, const RECT &rect,
                HWND parent_hwnd, UINT id);
    bool Initialization(HWND parent_hwnd, UINT id);
    int InsertColumn(int column, int width, std::string column_head);
    int InsertItem(int item, std::string item_text);
	int InsertItem(int item, int item_values);
    bool SetItem(int item, int subitem, std::string item_text);
	bool SetItem(int item, int subitem, int item_text);
	bool SetItem(int item, int subitem, double item_text);
	std::string GetItem(int item, int subitem);
    int GetItemCount();
    int GetColumnCount();
	int GetSelectedCount();
    int GetSelectionMark();
    int SetSelectionMark(int index);
    bool SetItemState(int item, UINT state, UINT mask);
    bool DeleteItem(int item);
    bool DeleteAllItems();
    void SetSelectAndGrid(DWORD style);
	void SetEditLabel(const int item);
	WNDPROC SetListProc(const WNDPROC proc);
	void SetExtendStyle(DWORD style);
	int FindItem(std::string item);
	int FindItem(int index, std::string item);

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
	m_old_process_ = (WNDPROC) SetWindowLong(m_hwnd_, GWL_WNDPROC, (LONG)process);
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
HWND CListView::hwnd()
{
	return m_hwnd_;
}

#endif // !defined(AFX_LISTVIEW_H__77342954_5258_41DF_87F6_267D6A706457__INCLUDED_)
