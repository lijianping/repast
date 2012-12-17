/*
 * 文件: service.cpp
 * 说明: 该文件是服务管理登录文件，对服务管理的操作在该文件中完成。
 **/


#include "service.h"


WNDPROC g_old_list_processes;

LRESULT CALLBACK ServiceProcesses(HWND hwnd, UINT message,
                                  WPARAM wParam, LPARAM lParam)
{
    HINSTANCE hinstance;
    switch (message)
    {
    case WM_CREATE:
        {
            hinstance = ((LPCREATESTRUCT)lParam)->hInstance;
//             CMyListView list_view;
//             CreateList(hinstance, hwnd, list_view); /* Create list view */
            return 0;
        }
    case WM_SETFOCUS:
        {
            SetFocus(GetDlgItem(hwnd, ID_SERVICE_LIST));
            return 0;
        }
    case WM_LBUTTONDOWN:
        {
            return 0;
        }
 
    case WM_COMMAND:
        {
            if (LOWORD (wParam) == ID_SERVICE_LIST && HIWORD (wParam) == LBN_SELCHANGE)
            {
                HWND list_hwnd = GetDlgItem(hwnd, ID_SERVICE_LIST);
                int index = SendMessage(list_hwnd, LB_GETCURSEL, 0, 0);
                TCHAR select[20];
                sprintf(select, TEXT("You choiced %d!"), index);
                MessageBox(hwnd, select, TEXT("SERVICE"), MB_ICONINFORMATION | MB_OK);
            }
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
    case WM_LBUTTONDBLCLK:
        {
//             CMyListView list_view;
//             list_view.set_hwnd(hwnd);
//             int index = list_view.GetCurSel();
//             char str[20];
//             sprintf(str, "You choiced %d", index);
//             MessageBox(hwnd, str, TEXT("list"), MB_ICONINFORMATION | MB_OK);
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
// bool CreateList(HINSTANCE hinstance, HWND hwnd, CMyListView &list_view)
// {
//     RECT service_rect;
//     GetWindowRect(hwnd, &service_rect);
//     int width = service_rect.right - service_rect.left;
//     int height = service_rect.bottom - service_rect.top;
//     list_view.set_list_view_id(ID_SERVICE_LIST);
//     list_view.set_list_view_height(height / 2);
//     list_view.set_list_view_width(width / 6);
//     list_view.set_hinstance(hinstance);
//     list_view.set_parent_hwnd(hwnd);
//     POINT origin;
//     origin.x = 20;
//     origin.y = height / 6;
//     list_view.set_origin_point(origin);
//     list_view.set_process(ListProcesses);
//     if (!list_view.CreateListView())
//     {
//         return false;
//     }
//     g_old_list_processes = list_view.old_process();
//     list_view.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
//     if (!list_view.InsertColumn("台号", 0, width / 12) ||
//         !list_view.InsertColumn("状态", 1, width / 12) ||
//         !list_view.InsertColumn("开台时间", 2, width / 12))
//     {
//        return false;
//     }
//     int i = 0; 
//     double price = 20.5;
//     while (i < 20)
//     {
//         list_view.InsertItem(i + 1, i);
//         list_view.SetItem(price, i, 1);
//         price++;
//         i++;
//     }
//     
//     list_view.SetSelectd(0);
//     return true;
// }

bool CreateStartButton(HINSTANCE hinstance, HWND hwnd, std::string error_info)
{
    HWND start_hwnd(NULL);
//     start_hwnd = CreateWindow(TEXT("button"), TEXT("开台"), WS_CHILD | WS_VISIBLE |
//                               WS_TABSTOP | BS_PUSHBUTTON, 600, 20, )
    return false;
}
