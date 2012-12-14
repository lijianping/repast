/*
 * 文件: MyListView.h
 * 说明: 该文件是关于CMyListView类的定义，在创建CMyListView对象时，
 *       你可以通过set_系列函数对list view进行必要的初始化操作，
 *       其中set_list_view_id是你必须要进行调用的，该函数设置了list
 *       view的唯一标识id。SetListViewInfo可以设置除set_list_view_id
 *       以外的其他属性值，该函数与set_系列函数有且仅有一个有效，越靠后
 *       调用，属性值便为该值。通过上述的设置，你需要调用CreateListView
 *       函数创建list view窗口。
 */

#ifndef REPAST_MYLISTVIEW_H_
#define REPAST_MYLISTVIEW_H_
#include <string>
#include <WINDOWS.H>
#include <COMMCTRL.H>
#pragma comment(lib, "comctl32.lib")

class CMyListView  
{
public:
	CMyListView();
    CMyListView(int id, HINSTANCE hinstance, HWND parent_hwnd);
	virtual ~CMyListView();
	inline void set_hinstance(const HINSTANCE hinstance);
	inline void set_parent_hwnd(const HWND parent_hwnd);
	inline void set_origin_point(const POINT origin);
	inline void set_list_view_width(const int width);
	inline void set_list_view_height(const int height);
    inline void set_list_view_id(const int id);
    inline void set_hwnd(const HWND hwnd);
    inline void set_process(WNDPROC process);
    inline WNDPROC old_process();
	inline HWND hwnd() const;
    inline int column_count() const;
    void SetListViewInfo(HINSTANCE hinstance, HWND parent_hwnd,
                        int origin_x = 0, int origin_y = 0,
		                int listview_width = 40, int listview_height = 30,
                        DWORD style = LVS_REPORT);
    bool CreateListView();
    bool InsertColumn(std::string title, int column, int width);
    bool InsertItem(std::string text, int row);
    bool InsertItem(int text, int row);
    bool SetItem(std::string text, int row, int column);
    bool SetItem(double text, int row, int cloumn);
    bool SetItem(int text, int row, int column);
    void SetSelectAndGrid(const DWORD style);
    int GetItem(int row, int column, std::string &text);
    int GetItemCount();
    void SetSelectd(const int index);
    int GetCurSel() const;
 
private:
    int m_list_view_id_;         /* list view's id */
    HINSTANCE m_hinstance_;      /* program's handle */
    HWND m_parent_hwnd_;         /* parent window's handle */
    HWND m_hwnd_;               /* list view's handle */
    POINT m_origin_point_;       /* list view start point */
    int m_list_view_width_;      /* list view's width */
    int m_list_view_height_;     /* list view's height */
    DWORD m_list_view_style_;    /* list view's style */
    int m_column_count_;         /* the number of column */
    WNDPROC m_process_;          /* the new list view's processes */
    WNDPROC m_old_process_;      /* the default list view's processes */
};

/*
 * @作者: 李建平
 * @说明: 设置程序实例句柄
 */
 void CMyListView::set_hinstance(const HINSTANCE hinstance)
 {
 	m_hinstance_ = hinstance;
 }

/*
 * @作者: 李建平
 * @说明: 设置 list view 父窗口句柄
 */
void CMyListView::set_parent_hwnd(const HWND hwnd)
{
	m_parent_hwnd_ = hwnd;
}

/*
 * @作者: 李建平
 * @说明: 设置 list view 窗口起点
 */
 void CMyListView::set_origin_point(const POINT origin)
 {
 	m_origin_point_ = origin;
 }

/*
 * @作者: 李建平
 * @说明: 设置 list view 窗口宽度
 */
 void CMyListView::set_list_view_width(const int width)
 {
 	m_list_view_width_ = width;
 }

 /*
 * @作者: 李建平
 * @说明: 设置 list view 窗口高度
 */
 void CMyListView::set_list_view_height(const int height)
 {
 	m_list_view_height_ = height;
 }

 /*
  * @作者: 李建平
  * @说明: 设置list view窗口句柄
  *        该函数用于从已有的list view控件
  *        创建CMyListView对象
  **/
 void CMyListView::set_hwnd(const HWND hwnd)
 {
     m_hwnd_ = hwnd;
 }
/*
 * @作者: 李建平
 * @说明: 获取 list view 窗口句柄
 */
 HWND CMyListView::hwnd() const
 {
 	return m_hwnd_;
 }

 /*
 * @作者: 李建平
 * @说明: 设置 list view 窗口 id 值
 *        此函数必须要显示调用
 */
 void CMyListView::set_list_view_id(const int id)
 {
     m_list_view_id_ = id;
 }

 int CMyListView::column_count() const
 {
     return m_column_count_;
 }

  /*
  * 说明: 设置list view窗口处理函数
  *       要修改窗口处理函数，需要在CreateListView函数之前
  *       调用。调用了set_processes函数之后，调用old_processes
  *       保存
  * 参数: 
  *       processes [in] 传入窗口处理函数
  **/
 void CMyListView::set_process(WNDPROC process)
 {
     if (process != NULL)
     {
         m_process_ = process;
     }
 }

  /*
  * 说明: 获取list view窗口默认处理函数，如果设置了list view的窗口处理函数，
  *       则在调用了CreateListView后，需要调用此函数保存原有的窗口处理过程函
  *       数，以便在新的处理函数中使用。
  * 返回值: list view窗口默认处理函数
  **/
 WNDPROC CMyListView::old_process()
 {
     if (m_old_process_ != NULL)
     {
         return m_old_process_;
     }
     return NULL;
 }

#endif  /* end #define REPAST_MYLISTVIEW_H_ */
