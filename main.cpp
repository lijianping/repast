#include "Wind.h"
#include "resource.h"
#include "service.h"
#include "childwindowid.h"
#include "basic_info.h"
#include "manager.h"
#include <SkinPPWTL.h>


bool CreateSysManagement(TabCtrl *tab, HWND tab_hwnd, RECT tab_rect);
BOOL CALLBACK ChangePasswdProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

/* 登陆对话框处理过程函数 */
BOOL CALLBACK LoginProcesses(HWND hwnd, UINT message,
                                WPARAM wParam, LPARAM lParam);

static HINSTANCE g_hinstance;
static int g_user_permission = 0;  /* The user permission flag */
static PageCtrl h_server ,h_personnel, h_finance,  h_passwd, h_user, h_basic_info, h_help;
extern std::string g_login_name;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine, int nShowCmd)
{
	skinppLoadSkin(TEXT("skin/Royale.ssk"));  // 加载皮肤
	g_hinstance = hInstance;
    std::string information;

    g_user_permission = DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_LOGIN), NULL,
                                     (DLGPROC)LoginProcesses, (long)&hInstance);

	if ( 0 < g_user_permission && g_user_permission < 5)
	{
		DialogBox(hInstance, MAKEINTRESOURCE(IDD_SYS_MANAGEMENT), NULL, (DLGPROC)ManagerProcesses);
	}
	skinppExitSkin();  // 退出
    return 0;
}


BOOL CALLBACK ManagerProcesses(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static RECT tab_rect;
   
	switch (msg)
	{
	case WM_INITDIALOG:
		{
			InitCommonControls();
			TabCtrl tab;
			HWND tab_hwnd = GetDlgItem(hwnd, IDC_TAB_MAIN);
			tab.Initialization(hwnd, IDC_TAB_MAIN);
			tab.GetClientRect(&tab_rect);
			tab_rect.top += 25;
			tab_rect.bottom -= 20;
			tab_rect.left += 1;
			tab_rect.right -= 2;
			CreateSysManagement(&tab, tab_hwnd, tab_rect);/*系统管理*/
			return TRUE;
		}
	case WM_NOTIFY:
		{
			switch(((LPNMHDR)lParam)->code)
			{
			case TCN_SELCHANGE:
				{
					h_server.ShowWindow(SW_HIDE);
					h_basic_info.ShowWindow(SW_HIDE);
					h_personnel.ShowWindow(SW_HIDE);
					h_finance.ShowWindow(SW_HIDE);
					h_user.ShowWindow(SW_HIDE);
					h_passwd.ShowWindow(SW_HIDE);
					h_help.ShowWindow(SW_HIDE);
					
					TabCtrl tab;
					tab.Initialization(hwnd, IDC_TAB_MAIN);
					int selected = tab.GetCurSel();
					tab.Highlight(selected);
					char tab_title[256];
					tab.GetItem(selected, 256, tab_title);
					if (0 == strcmp(tab_title, "前台管理")) {
						h_server.ShowWindow(SW_NORMAL);
						
					} else if (0 == strcmp(tab_title, "基础信息管理")) {
						h_basic_info.ShowWindow(SW_NORMAL);
						
					} else if (0 == strcmp(tab_title, "人事管理")) {
						h_personnel.ShowWindow(SW_NORMAL);
					} else if (0 == strcmp(tab_title, "财政管理")) {
						h_finance.ShowWindow(SW_NORMAL);
					} else if (0 == strcmp(tab_title, "用户管理")) {
						h_user.ShowWindow(SW_NORMAL);
					} else if (0 == strcmp(tab_title, "数据库备份")) {
						MessageBox(hwnd, TEXT("尚未添加，敬请期待！"), TEXT("提示"), MB_ICONINFORMATION);
					} else if (0 == strcmp(tab_title, "数据库还原")) {
						MessageBox(hwnd, TEXT("尚未添加，敬请期待！"), TEXT("提示"), MB_ICONINFORMATION);
					} else if (0 == strcmp(tab_title, "使用帮助")) {
						MessageBox(hwnd, TEXT("尚未添加，敬请期待！"), TEXT("提示"), MB_ICONINFORMATION);
					} else if (0 == strcmp(tab_title, "密码管理")) {
						h_passwd.ShowWindow(SW_NORMAL);
						HWND passwd_hwnd = h_passwd.hwnd();
						CEdit old_passwd(passwd_hwnd, IDC_OLD_PASSWD);   // 在切换tab时清空编辑框内容
						CEdit new_passwd(passwd_hwnd, IDC_NEW_PASSWD);
						CEdit confirm(passwd_hwnd, IDC_CONFIRM);
						old_passwd.Empty();
						new_passwd.Empty();
						confirm.Empty();
					}
				}
			}
			return TRUE;
		}
	case WM_CLOSE:
		{
			if (IDYES == MessageBox(hwnd, TEXT("是否退出系统？"), TEXT("提示"), MB_YESNOCANCEL | MB_ICONINFORMATION)) {
				EndDialog(hwnd, HIWORD(wParam));
			}
			return TRUE;
		}
	}
	return FALSE;
}

bool CreateSysManagement(TabCtrl *tab, HWND tab_hwnd, RECT tab_rect)
{
	h_server.CreatePage(g_hinstance, tab_hwnd, IDD_TAB_SERVER, (DLGPROC)ServiceProcesses);
	h_basic_info.CreatePage(g_hinstance, tab_hwnd, IDD_TAB_BASIC_INFO, (DLGPROC)BasicInfoProc);
	h_personnel.CreatePage(g_hinstance, tab_hwnd, IDD_TAB_PERSONNEL, (DLGPROC)PersonnelProc);
	h_finance.CreatePage(g_hinstance, tab_hwnd, IDD_TAB_FINANCE, (DLGPROC)FinanceProc);
	h_user.CreatePage(g_hinstance, tab_hwnd, IDD_TAB_USER, (DLGPROC)UserManagementProc);
	h_passwd.CreatePage(g_hinstance, tab_hwnd, IDD_TAB_PASSWD, (DLGPROC)ChangePasswdProc);
	h_server.MoveWindow(tab_rect);
	h_basic_info.MoveWindow(tab_rect);
	h_personnel.MoveWindow(tab_rect);
	h_finance.MoveWindow(tab_rect);
	h_user.MoveWindow(tab_rect);
	h_passwd.MoveWindow(tab_rect);
	
	h_server.ShowWindow(SW_HIDE);
	h_basic_info.ShowWindow(SW_HIDE);
	h_personnel.ShowWindow(SW_HIDE);
	h_finance.ShowWindow(SW_HIDE);
	h_user.ShowWindow(SW_HIDE);
	if (1== g_user_permission) {
		tab->InsertItem(0, "前台管理");
		tab->InsertItem(1, "密码管理");
		tab->InsertItem(2, "使用帮助");
		h_server.ShowWindow(SW_NORMAL);

	} else if (2 == g_user_permission) {
		tab->InsertItem(0, "基础信息管理");
		tab->InsertItem(1, "密码管理");
		tab->InsertItem(2, "使用帮助");
		h_basic_info.ShowWindow(SW_NORMAL);

	} else if (3 == g_user_permission) {
		tab->InsertItem(0, "人事管理");
		tab->InsertItem(1, "密码管理");
		tab->InsertItem(2, "使用帮助");
		h_personnel.ShowWindow(SW_NORMAL);
	} else {
		tab->InsertItem(0, "前台管理");
		tab->InsertItem(1, "基础信息管理");
		tab->InsertItem(2, "人事管理");
		tab->InsertItem(3, "财政管理");
		tab->InsertItem(4, "用户管理");
		tab->InsertItem(5, "数据库备份");
		tab->InsertItem(6, "数据库还原");
		tab->InsertItem(7, "使用帮助");
		h_server.ShowWindow(SW_NORMAL);
	} 
	tab->SetCurSel(0);
	tab->Highlight(0);
	return true;
}

BOOL CALLBACK ChangePasswdProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		{
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDOK:
				{
					TCHAR new_passwd[64] = "\0", confirm[64] = "\0";
					int ret = GetDlgItemText(hwnd, IDC_NEW_PASSWD, new_passwd, 64);
					int ret1 = GetDlgItemText(hwnd, IDC_CONFIRM, confirm, 64);
					std::string password1(new_passwd), password2(confirm);
					if (password1 != password2) {
						MessageBox(hwnd, TEXT("两次密码输入不一致！"), TEXT("提示"), MB_OK | MB_ICONINFORMATION);
						return FALSE;
					} 
					if (!ret || !ret1) {
						MessageBox(hwnd, TEXT("密码不能为空！"), TEXT("提示"), MB_OK | MB_ICONINFORMATION);
						return FALSE;
					}
					TCHAR old_passwd[64] = "\0";
					GetDlgItemText(hwnd, IDC_OLD_PASSWD, old_passwd, 64);
					std::string password(old_passwd), error;
					CLoginForm modify_passwd;
					std::string pw = modify_passwd.Encrypt(password.c_str(), password.length() / 2, password.length());
					std::string pw1 = modify_passwd.Encrypt(password1.c_str(), password1.length() / 2, password1.length());
					// 判断用户密码是否正确
					if (-1 == modify_passwd.GetUserPermission(g_login_name, pw, error)) {
						MessageBox(hwnd, TEXT("用户密码错误！"), TEXT("提示"), MB_OK | MB_ICONINFORMATION);
						return FALSE;
					}
					if (!modify_passwd.ModifyPasswd(g_login_name, pw1))
					{
						MessageBox(hwnd, TEXT("修改用户密码失败！"), TEXT("提示"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					MessageBox(hwnd, TEXT("密码修改成功！"), TEXT("提示"), MB_OK);
				}
			case IDCANCEL:
				{
					CEdit old, new_passwd, confirm;
					old.Initialization(hwnd, IDC_OLD_PASSWD);
					new_passwd.Initialization(hwnd, IDC_NEW_PASSWD);
					confirm.Initialization(hwnd, IDC_CONFIRM);
					old.Empty();
					new_passwd.Empty();
					confirm.Empty();
				}
			}
			return TRUE;
		}
	}
	return FALSE;
}
