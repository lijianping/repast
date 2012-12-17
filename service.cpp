/*
 * �ļ�: service.cpp
 * ˵��: ���ļ��Ƿ�������¼�ļ����Է������Ĳ����ڸ��ļ�����ɡ�
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
 * ˵��: list view��������
 *       �ú������ܴ������е���Ϣ(��WM_CREATE��Ϣ)��ֻ�ܴ���
 *       ���ֵ���Ϣ��
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
 * ˵��: ����list view����
 * ����:
 *       hinstance [in] ����ʵ�����
 *       hwnd [in] ���ھ��
 *       list_view [out] CMyListView���󣬱��洴���õ�listview�Ĳ���
 * ����ֵ: ���ɹ�����ture,���򷵻�false��
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
//     if (!list_view.InsertColumn("̨��", 0, width / 12) ||
//         !list_view.InsertColumn("״̬", 1, width / 12) ||
//         !list_view.InsertColumn("��̨ʱ��", 2, width / 12))
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
//     start_hwnd = CreateWindow(TEXT("button"), TEXT("��̨"), WS_CHILD | WS_VISIBLE |
//                               WS_TABSTOP | BS_PUSHBUTTON, 600, 20, )
    return false;
}
