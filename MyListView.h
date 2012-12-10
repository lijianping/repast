/*
 * �ļ�: MyListView.h
 * ˵��: ���ļ��ǹ���CMyListView��Ķ��壬�ڴ���CMyListView����ʱ��
 *       �����ͨ��set_ϵ�к�����list view���б�Ҫ�ĳ�ʼ��������
 *       ����set_list_view_id�������Ҫ���е��õģ��ú���������list
 *       view��Ψһ��ʶid��SetListViewInfo�������ó�set_list_view_id
 *       �������������ֵ���ú�����set_ϵ�к������ҽ���һ����Ч��Խ����
 *       ���ã�����ֵ��Ϊ��ֵ��ͨ�����������ã�����Ҫ����CreateListView
 *       ��������list view���ڡ�
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
    int GetCursor();
 
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
 * @����: �ƽ
 * @˵��: ���ó���ʵ�����
 */
 void CMyListView::set_hinstance(const HINSTANCE hinstance)
 {
 	m_hinstance_ = hinstance;
 }

/*
 * @����: �ƽ
 * @˵��: ���� list view �����ھ��
 */
void CMyListView::set_parent_hwnd(const HWND hwnd)
{
	m_parent_hwnd_ = hwnd;
}

/*
 * @����: �ƽ
 * @˵��: ���� list view �������
 */
 void CMyListView::set_origin_point(const POINT origin)
 {
 	m_origin_point_ = origin;
 }

/*
 * @����: �ƽ
 * @˵��: ���� list view ���ڿ��
 */
 void CMyListView::set_list_view_width(const int width)
 {
 	m_list_view_width_ = width;
 }

 /*
 * @����: �ƽ
 * @˵��: ���� list view ���ڸ߶�
 */
 void CMyListView::set_list_view_height(const int height)
 {
 	m_list_view_height_ = height;
 }

 /*
  * @����: �ƽ
  * @˵��: ����list view���ھ��
  *        �ú������ڴ����е�list view�ؼ�
  *        ����CMyListView����
  **/
 void CMyListView::set_hwnd(const HWND hwnd)
 {
     m_hwnd_ = hwnd;
 }
/*
 * @����: �ƽ
 * @˵��: ��ȡ list view ���ھ��
 */
 HWND CMyListView::hwnd() const
 {
 	return m_hwnd_;
 }

 /*
 * @����: �ƽ
 * @˵��: ���� list view ���� id ֵ
 *        �˺�������Ҫ��ʾ����
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
  * ˵��: ����list view���ڴ�����
  *       Ҫ�޸Ĵ��ڴ���������Ҫ��CreateListView����֮ǰ
  *       ���á�������set_processes����֮�󣬵���old_processes
  *       ����
  * ����: 
  *       processes [in] ���봰�ڴ�����
  **/
 void CMyListView::set_process(WNDPROC process)
 {
     if (process != NULL)
     {
         m_process_ = process;
     }
 }

  /*
  * ˵��: ��ȡlist view����Ĭ�ϴ����������������list view�Ĵ��ڴ�������
  *       ���ڵ�����CreateListView����Ҫ���ô˺�������ԭ�еĴ��ڴ�����̺�
  *       �����Ա����µĴ�������ʹ�á�
  * ����ֵ: list view����Ĭ�ϴ�����
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
