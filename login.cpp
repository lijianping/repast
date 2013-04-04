/*
 * 文件: login.cpp
 * 说明: 该文件是关于登录模块的设计。
 **/
#include "resource.h"
#include "LoginForm.h"
#include "Edit.h"
std::string g_login_name;  // 登陆用户名
static WNDPROC g_button_proc = NULL;

// 子类化button控件
LRESULT CALLBACK ButtonProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK LoginProcesses(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HINSTANCE hinstance = (HINSTANCE)lParam;  /* The program handle */
  
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
            HICON login_icon = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_ICONLOGIN));
            if (login_icon)
            {
                SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)login_icon);
                SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)login_icon);
            }
			CEdit edit(hwnd, IDC_USERNAME);    // 设置文本垂直居中
			edit.SetV(3);
			HWND ok_hwnd = GetDlgItem(hwnd, IDOK);
			g_button_proc = (WNDPROC)SetWindowLong(ok_hwnd, GWL_WNDPROC, (LONG)ButtonProc);
            return TRUE;
        }
	case WM_CTLCOLORSTATIC:   //设置静态文本框字体颜色
		{
			HWND child_hwnd = (HWND)lParam;
			HDC hdc = (HDC)wParam;
			SetTextColor(hdc, RGB(254, 251, 232));
			SetBkMode(hdc, TRANSPARENT);
			return (BOOL)((HBRUSH)GetStockObject(NULL_BRUSH));
			return TRUE;
		}
	case WM_CTLCOLORDLG:   // 设置对话框背景
		{
			HBRUSH g_hbrBackground = CreateSolidBrush(RGB(66, 66, 65));
			return (LONG)g_hbrBackground;
		}
	case WM_CTLCOLOREDIT:  // 设置编辑框背景
		{
			SetBkMode((HDC)wParam, TRANSPARENT);
			SetTextColor((HDC)wParam, RGB(147, 88, 66));
			return  (LONG)CreateSolidBrush(RGB(34, 62, 76));
		}
	case WM_CTLCOLORBTN:
		{
			HWND child_hwnd = (HWND)lParam;
			HDC hdc = (HDC)wParam;
			TCHAR button_text[64];
			GetWindowText(child_hwnd, button_text, 64);
			RECT rect;
			GetClientRect(child_hwnd, &rect);
			SetTextColor(hdc, RGB(255, 255, 255)); //设置按钮上文本的颜色
			SetBkMode(hdc, TRANSPARENT);
			DrawText(hdc, button_text, strlen(button_text), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		    return  (INT_PTR)CreateSolidBrush(RGB(35, 35, 35));//返回画刷设置按钮的背景色
		}
    case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
            case IDOK:
                {  
					long return_value = 0;
                    TCHAR user_name[256];
                    TCHAR user_password[128];
                    memset(user_name, 0, sizeof(user_name));
                    memset(user_password, 0, sizeof(user_password));
                    UINT name_return = GetDlgItemText(hwnd, IDC_USERNAME, user_name, 256);
                    UINT password_return = GetDlgItemText(hwnd, IDC_PASSWORD, user_password, 128);
                    if ((0 == name_return) || (0 == password_return))
                    {
                        MessageBox(hwnd, TEXT("用户名或密码为空！"),
                                   TEXT("登录"), MB_OK | MB_ICONINFORMATION);
                        return FALSE;
				    } else {
                        /* get permission from database */
						std::string error_information;
						std::string name(user_name);
						std::string password(user_password);
						try {
							CLoginForm login; 
							login.CheckInputRight(user_name,user_password);
							std::string pw = login.Encrypt(password.c_str(), password.length()/2, password.length());
							return_value = login.GetUserPermission(name, pw,error_information);
							login.Disconnect();
						} catch (Err &err) {
							MessageBox(hwnd, err.what(), TEXT("LOGIN ERROR"), MB_ICONERROR);
							return FALSE;
						}
                        if (-1 == return_value) {
                            MessageBox(hwnd, error_information.c_str(), TEXT("LOGIN"), MB_OK | MB_ICONINFORMATION);
                            return FALSE;
                        }
						g_login_name = name;	// 保存用户登录名
                    }
                    EndDialog(hwnd, return_value);
                    break;
                }
            case IDCANCEL:
                {
					wParam = 0;
                    EndDialog(hwnd, LOWORD(wParam));
                    break;
                }
            }
            return TRUE;
        }
    }
   return FALSE;
}

LRESULT CALLBACK ButtonProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_MOUSEMOVE:
		{
			
			SetTextColor((HDC)wParam, RGB(255,0,0));
			break;
		}
	}
	return CallWindowProc(g_button_proc, hwnd, message, wParam, lParam);
}