#include "resource.h"
#include "MyListView.h"
#include "StaffForm.h"
#include "DBConnect.h" 
#include <WINDOWS.H>

/* 引入外部变量，以下变量定义在main.cpp */
extern HINSTANCE g_hinstance;
extern bool g_is_connect;
extern CDBConnect database;
WNDPROC old_list_processes;

LRESULT CALLBACK PersonnelList(HWND hwnd, UINT message,
                               WPARAM wParam, LPARAM lParam);
BOOL CALLBACK EditStaff(HWND hwnd, UINT message,
                             WPARAM wParam, LPARAM lParam);

/* Personnel Processes */
LRESULT CALLBACK PersonnelProcesses(HWND hwnd, UINT message,
                                  WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        {
            CMyListView list_view;
            RECT service_rect;
            GetWindowRect(hwnd, &service_rect);
            int width = service_rect.right - service_rect.left;
            int height = service_rect.bottom - service_rect.top;
            list_view.set_list_view_id(ID_PERSONNEL_INFO);
            list_view.set_list_view_height(height / 4 * 3 - 40);
            list_view.set_list_view_width(width - 40 );
            list_view.set_hinstance(g_hinstance);
            list_view.set_parent_hwnd(hwnd);
            POINT origin;
            origin.x = 20;
            origin.y = height / 4;
            list_view.set_origin_point(origin);
            list_view.set_process(PersonnelList);
            if (!list_view.CreateListView())
            {
                return 0;
            }
            old_list_processes = list_view.old_process();
            list_view.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
            if (!list_view.InsertColumn("员工编号", 0, width / 6) ||
                !list_view.InsertColumn("员工姓名", 1, width / 6) ||
                !list_view.InsertColumn("员工性别", 2, width / 6) ||
                !list_view.InsertColumn("员工年龄", 3, width / 6) ||
                !list_view.InsertColumn("员工工资", 4, width / 6) ||
                !list_view.InsertColumn("员工部门", 5, width / 6))
            {
                return 0;
            }
            list_view.SetSelectd(0);
            /* Get staff's information from Staff form in database. */
            StaffForm staff;
            staff.Initialize(database.hdbc());
            staff.GetRecordSet();
            staff.MoveFirst();
            int i = 0;
            while (!staff.IsEOF())
            {
                list_view.InsertItem(staff.id(), i);
                list_view.SetItem(staff.name(), i, 1);
                list_view.SetItem(staff.sex(), i, 2);
                list_view.SetItem(staff.age(), i, 3);
                list_view.SetItem(staff.salary(), i, 4);
                list_view.SetItem(staff.dept_num(), i, 5);
                staff.MoveNext();
                i++;
            }
            /* End get staff's information from Staff form in database. */
            return 0;
        }
    case WM_SETFOCUS:
        SetFocus(GetDlgItem(hwnd, ID_SERVICE_FOUNDING));
        return 0;
    case WM_LBUTTONDOWN:
        {
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
LRESULT CALLBACK PersonnelList(HWND hwnd, UINT message,
                               WPARAM wParam, LPARAM lParam)
{
    static HMENU menu;

    switch (message)
    {
    case WM_LBUTTONDOWN:
        {
            
            break;
        }
    case WM_RBUTTONDOWN:
        {
            menu = LoadMenu(g_hinstance, MAKEINTRESOURCE(IDR_PERSONNEL));
            menu = GetSubMenu(menu, 0);
            POINT point;
            point.x = LOWORD(lParam);
            point.y = HIWORD(lParam);
            ClientToScreen(hwnd, &point);
            TrackPopupMenu(menu, TPM_RIGHTBUTTON, point.x, point.y,
                           0, hwnd, NULL);
            break;
        }
    case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
            case IDR_ADD:
                /* TODO: send the list view content to dialog */
                DialogBox(g_hinstance, MAKEINTRESOURCE(IDD_STAFF_EDIT), hwnd,
                          (DLGPROC)EditStaff);
                break;
            case IDR_DELETE:
                MessageBox(hwnd, TEXT("You choiced delete staff"), TEXT("PERSONNEL"), MB_OK | MB_ICONINFORMATION);
                break;
            case IDR_MODIFY:
                MessageBox(hwnd, TEXT("You choiced modify staff"), TEXT("PERSONNEL"), MB_OK | MB_ICONINFORMATION);
                break;
            }
            return 0;
        }
    }
    return CallWindowProc(old_list_processes, hwnd, message, wParam, lParam);
}


BOOL CALLBACK EditStaff(HWND hwnd, UINT message,
                             WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
      case WM_INITDIALOG:
        {
            RECT login_rect;
            if (!GetWindowRect(hwnd, &login_rect))
            {
                MessageBox(hwnd, TEXT("Get dialog rect failed!"),
                    TEXT("ERROR"), MB_ICONINFORMATION | MB_OK);
                return FALSE;
            }
            int login_width = login_rect.right - login_rect.left;
            int login_height = login_rect.bottom - login_rect.top;
            int screen_width = GetSystemMetrics(SM_CXFULLSCREEN);
            int screen_height = GetSystemMetrics(SM_CYFULLSCREEN);
            MoveWindow(hwnd, (screen_width - login_width) / 2,
                      (screen_height - login_height) / 2, login_width,
                      login_height, TRUE);
//             HICON login_icon = LoadIcon(g_hinstance, MAKEINTRESOURCE(IDI_ICONLOGIN));
//             if (login_icon)
//             {
//                 SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)login_icon);
//                 SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)login_icon);
//             }
            return TRUE;
        }
    case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
            case ID_CANCEL_STAFF:
                EndDialog(hwnd,  LOWORD(wParam));
                break;
            }
            return TRUE;
        }
    case WM_CLOSE:
        EndDialog(hwnd, LOWORD(wParam));
        return TRUE;
    }
    return FALSE;
}