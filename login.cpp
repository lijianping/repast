/*
 * �ļ�: login.cpp
 * ˵��: ���ļ��ǹ��ڵ�¼ģ�����ơ�
 **/
#include "resource.h"
#include "LoginForm.h"
#include "Edit.h"
std::string g_login_name;  // ��½�û���
static WNDPROC g_button_proc = NULL;
extern HINSTANCE g_hinstance;

// ���໯button�ؼ�
LRESULT CALLBACK ButtonProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK LoginProcesses(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HINSTANCE hinstance;  /* The program handle */
  
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
			hinstance = (HINSTANCE)lParam;
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
			CEdit edit(hwnd, IDC_USERNAME);    // �����ı���ֱ����
			edit.SetV(3);
			HWND ok_hwnd = GetDlgItem(hwnd, IDOK);
			g_button_proc = (WNDPROC)SetWindowLong(ok_hwnd, GWL_WNDPROC, (LONG)ButtonProc);
            return TRUE;
        }
	case WM_CTLCOLORSTATIC:   //���þ�̬�ı���������ɫ
		{
			HWND child_hwnd = (HWND)lParam;
			HDC hdc = (HDC)wParam;
			SetTextColor(hdc, RGB(254, 251, 232));
			SetBkMode(hdc, TRANSPARENT);
			return (BOOL)((HBRUSH)GetStockObject(NULL_BRUSH));
			return TRUE;
		}
	case WM_CTLCOLORDLG:   // ���öԻ��򱳾�
		{
			HBRUSH g_hbrBackground = CreateSolidBrush(RGB(66, 66, 65));
			return (LONG)g_hbrBackground;
		}
	case WM_CTLCOLOREDIT:  // ���ñ༭�򱳾�
		{
			SetBkMode((HDC)wParam, TRANSPARENT);
			SetTextColor((HDC)wParam, RGB(147, 88, 66));
			return  (LONG)CreateSolidBrush(RGB(34, 62, 76));
		}
	case WM_CTLCOLORBTN:
		{
			HWND child_hwnd = (HWND)lParam;
			HDC hdc = (HDC)wParam;
			if (child_hwnd == GetDlgItem(hwnd, IDC_B_CLOSE)) {
				RECT rect;
				GetClientRect(child_hwnd, &rect);
				SetBkMode(hdc, TRANSPARENT);
				return (LONG)CreateSolidBrush(RGB(158,27,27));
			} else if (child_hwnd == GetDlgItem(hwnd, IDOK)) {
				TCHAR button_text[64];
			    GetWindowText(child_hwnd, button_text, 64);
			    RECT rect;
			    GetClientRect(child_hwnd, &rect);
			    SetTextColor(hdc, RGB(255, 255, 255)); //���ð�ť���ı�����ɫ
			    SetBkMode(hdc, TRANSPARENT);
			    DrawText(hdc, button_text, strlen(button_text), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			} else if (child_hwnd == GetDlgItem(hwnd, IDCANCEL)) {
				TCHAR button_text[64];
				GetWindowText(child_hwnd, button_text, 64);
				RECT rect;
				GetClientRect(child_hwnd, &rect);
				SetTextColor(hdc, RGB(255, 255, 255)); //���ð�ť���ı�����ɫ
				SetBkMode(hdc, TRANSPARENT);
				DrawText(hdc, button_text, strlen(button_text), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
		    return  (INT_PTR)CreateSolidBrush(RGB(35, 35, 35));//���ػ�ˢ���ð�ť�ı���ɫ
		}
	case WM_DRAWITEM:
		{
			LPDRAWITEMSTRUCT draw_item = (LPDRAWITEMSTRUCT)lParam;
			switch (draw_item->CtlID) {
			case IDC_B_CLOSE:
				{
					HBITMAP hbitmap = LoadBitmap(g_hinstance, MAKEINTRESOURCE(IDB_BITMAP1));
					HWND child_hwnd = GetDlgItem(hwnd, draw_item->CtlID);
					HDC hdc = GetWindowDC(child_hwnd);
					RECT rect;
					GetClientRect(child_hwnd, &rect);
					HDC hdc_mem = CreateCompatibleDC(hdc);
					SelectObject(hdc_mem, hbitmap);
					BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, hdc_mem, 0, 0, SRCCOPY);
					DeleteDC(hdc_mem);
					SetBkMode(hdc, TRANSPARENT);
					ReleaseDC(child_hwnd, hdc);
					break;
				}
			}
			return TRUE;
		}
	case WM_LBUTTONDOWN:
		{
			UpdateWindow(hwnd);
			ReleaseCapture();
			SendMessage(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
			return TRUE;
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
                        MessageBox(hwnd, TEXT("�û���������Ϊ�գ�"),
                                   TEXT("��¼"), MB_OK | MB_ICONINFORMATION);
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
						g_login_name = name;	// �����û���¼��
                    }
                    EndDialog(hwnd, return_value);
                    break;
                }
			case IDC_B_CLOSE:
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