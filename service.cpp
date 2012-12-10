/*
 * 文件: service.cpp
 * 说明: 该文件是服务管理登录文件，对服务管理的操作在该文件中完成。
 **/

#include "resource.h"
#include "MyListView.h"
#include "StaffForm.h"
#include "DBConnect.h" 
#include "childwindowid.h"
#include <WINDOWS.H>

/* 引入外部变量，以下变量定义在main.cpp */
extern HINSTANCE g_hinstance;
extern bool g_is_connect;
extern CDBConnect database;
WNDPROC g_old_list_processes;

LRESULT CALLBACK ListProcesses(HWND hwnd, UINT message,
                               WPARAM wParam, LPARAM lParam);
/* Create list view */
bool CreateList(HINSTANCE hinstance, HWND hwnd, CMyListView &list_view);

LRESULT CALLBACK ServiceProcesses(HWND hwnd, UINT message,
                                  WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        {
            CMyListView list_view;
            CreateList(g_hinstance, hwnd, list_view);
            int count = list_view.column_count();
            char str[10];
 
            sprintf(str, "%d", count);
            if (g_is_connect)
            {
                MessageBox(hwnd, TEXT("connect to database"), TEXT("LISTVIEW"), MB_OK | MB_ICONINFORMATION);
            }
            MessageBox(hwnd, str, TEXT("LISTVIEW"), MB_OK | MB_ICONINFORMATION);
            
            return 0;
        }
    case WM_SETFOCUS:
        SetFocus(GetDlgItem(hwnd, ID_SERVICE_FOUNDING));
        return 0;
    case WM_LBUTTONDOWN:
        {
            CMyListView list_view;
            list_view.set_hwnd(GetDlgItem(hwnd, ID_SERVICE_FOUNDING));
            std::string name;
            std::string age, grade;
            list_view.GetItem(0, 0, name);
            list_view.GetItem(0, 1, age);
            list_view.GetItem(0, 2, grade);
            std::string data;
            data += name;
            data += age; 
            data += grade;
            MessageBox(hwnd, data.c_str(), TEXT("LISTVIEW"), MB_OK | MB_ICONINFORMATION);
            int count = list_view.GetItemCount();
            char str[10];
            sprintf(str, "%d", count);
            MessageBox(hwnd, str, TEXT("LISTVIEW"), MB_OK | MB_ICONINFORMATION);
            return 0;
        }
 
    case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

/*
 * 说明: list view处理函数。
 *       该函数不能处理所有的消息(如WM_CREATE消息)，只能处理
 *       部分的消息。
 **/
LRESULT CALLBACK ListProcesses(HWND hwnd, UINT message,
                               WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_LBUTTONDOWN:
        {
            
            break;
        }
    case WM_RBUTTONDOWN:
        {
            CMyListView list_view;
            list_view.set_hwnd(hwnd);
            int index = list_view.GetCursor();
            char str[10];
            sprintf(str, "%d", index);
            MessageBox(hwnd, str, TEXT("list"), MB_ICONINFORMATION | MB_OK);
            break;
        }
    case WM_COMMAND:
        {
            if (LOWORD(wParam) == ID_SERVICE_FOUNDING && HIWORD(wParam) == LBN_SELCHANGE)
            {
                CMyListView list_view;
                list_view.set_hwnd(hwnd);
                int index = list_view.GetCursor();
                char str[10];
                sprintf(str, "%d", index);
                MessageBox(hwnd, str, TEXT("list"), MB_ICONINFORMATION | MB_OK);
            }
            break;
        }
    }
    return CallWindowProc(g_old_list_processes, hwnd, message, wParam, lParam);
}

/*
 * 说明: 创建list view窗口
 * 参数:
 *       hinstance [in] 程序实例句柄
 *       hwnd [in] 窗口句柄
 *       list_view [out] CMyListView对象，保存创建好的listview的参数
 * 返回值: 若成功返回ture,否则返回false。
 **/
bool CreateList(HINSTANCE hinstance, HWND hwnd, CMyListView &list_view)
{
    RECT service_rect;
    GetWindowRect(hwnd, &service_rect);
    int width = service_rect.right - service_rect.left;
    int height = service_rect.bottom - service_rect.top;
    list_view.set_list_view_id(ID_SERVICE_FOUNDING);
    list_view.set_list_view_height(height / 2);
    list_view.set_list_view_width(width / 6);
    list_view.set_hinstance(hinstance);
    list_view.set_parent_hwnd(hwnd);
    POINT origin;
    origin.x = 20;
    origin.y = height / 6;
    list_view.set_origin_point(origin);
    list_view.set_process(ListProcesses);
    if (!list_view.CreateListView())
    {
        return false;
    }
    g_old_list_processes = list_view.old_process();
    list_view.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    if (!list_view.InsertColumn("台号", 0, width / 12) ||
        !list_view.InsertColumn("状态", 1, width / 12))
    {
       return false;
    }
    int i = 0; 
    double price = 20.5;
    while (i < 20)
    {
        list_view.InsertItem(i + 1, i);
        list_view.SetItem(price, i, 1);
        price++;
        i++;
    }
    
    list_view.SetSelectd(0);
    return true;
}
