/*
 * �ļ�: login.cpp
 * ˵��: ���ļ��ǹ��ڵ�¼ģ�����ơ�
 **/
#include "resource.h"
#include "LoginForm.h"
#include "DBConnect.h"


/* �����ⲿ���������±���������main.cpp */
extern int g_user_permission;
extern HINSTANCE g_hinstance;
extern CDBConnect database;

BOOL CALLBACK LoginProcesses(HWND hwnd, UINT message,
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
            HICON login_icon = LoadIcon(g_hinstance, MAKEINTRESOURCE(IDI_ICONLOGIN));
            if (login_icon)
            {
                SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)login_icon);
                SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)login_icon);
            }
            return TRUE;
        }
    case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
            case IDOK:
                {
                    TCHAR user_name[256];
                    TCHAR user_password[128];
                    memset(user_name, 0, sizeof(user_name));
                    memset(user_password, 0, sizeof(user_password));
                    UINT name_return = GetDlgItemText(hwnd, IDC_USERNAME,
                                                      user_name, 256);
                    UINT password_return = GetDlgItemText(hwnd, IDC_PASSWORD,
                                                          user_password, 128);
                    if ((0 == name_return) || (0 == password_return))
                    {
                        MessageBox(hwnd, TEXT("�û���������Ϊ�գ�"),
                                   TEXT("��¼"), MB_OK | MB_ICONINFORMATION);
                        return FALSE;
				    }
                    else
                    {
                        /* get permission from database */
                        CLoginForm login;
                        login.Initialize(database.hdbc());
                        std::string name(user_name);
                        std::string password(user_password);
                        std::string error_information;
                        g_user_permission = login.GetUserPermission(name, password, error_information);
                        if (0 == g_user_permission)
                        {
                            MessageBox(hwnd, error_information.c_str(),
                                       TEXT("LOGIN"), MB_OK | MB_ICONINFORMATION);
                            return FALSE;
                        }
                    }
                    EndDialog(hwnd, LOWORD(wParam));
                    break;
                }
            case IDCANCEL:
                {
                    EndDialog(hwnd, LOWORD(wParam));
                    break;
                }
            }
            return TRUE;
        }
    }
   return FALSE;
}