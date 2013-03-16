#include "manager.h"
#include "Button.h"

BOOL CALLBACK ManagerProcesses(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static RECT tab_rect;
	static HWND page1, page2;
    static HINSTANCE hinstance = (HINSTANCE)lParam;
	switch (msg)
	{
	case WM_INITDIALOG:
		{
			InitCommonControls();
			CTab tab;
			tab.Initialization(hwnd, IDC_TAB1);
			tab.InsertItem(0, "用户管理");
			tab.InsertItem(1, "财务管理");
			tab.InsertItem(2, "数据库备份");
			tab.InsertItem(3, "数据库还原");
			tab.SetCurFocus(0);
			tab.GetClientRect(&tab_rect);
			tab_rect.top += 25;
			tab_rect.bottom -= 20;
			tab_rect.left += 1;
			tab_rect.right -= 2;
			HWND tab_hwnd = GetDlgItem(hwnd, IDC_TAB1);
			page1 = CreateDialog(hinstance, MAKEINTRESOURCE(IDD_TAB_CHILD1), tab_hwnd, (DLGPROC)SysManagementProc);
			page2 = CreateDialog(hinstance, MAKEINTRESOURCE(IDD_TAB_FINANCE), tab_hwnd, (DLGPROC)FinanceProc);
			
			MoveWindow(page1, tab_rect.left, tab_rect.top, \
				       tab_rect.right - tab_rect.left, tab_rect.bottom - tab_rect.top, TRUE);
			MoveWindow(page2, tab_rect.left, tab_rect.top, \
				       tab_rect.right - tab_rect.left, tab_rect.bottom - tab_rect.top, TRUE);
			ShowWindow(page1, SW_NORMAL);
			return TRUE;
		}
	case WM_NOTIFY:
		{
			switch(((LPNMHDR)lParam)->code)
			{
			case TCN_SELCHANGE:
				ShowWindow(page1, SW_HIDE);
				ShowWindow(page2, SW_HIDE);
				CTab tab;
				tab.Initialization(hwnd, IDC_TAB1);
				int selected = tab.GetCurSel();
				if (0 == selected) {
					ShowWindow(page1, SW_NORMAL);
				}
				else{
					ShowWindow(page2, SW_NORMAL);
				}
				break;
			}
		
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam)) 
			{
			case IDC_ADD_USER:
				{
					CTab tab;
					tab.Initialization(hwnd, IDC_TAB1);
					int selected = tab.GetCurFocus();
					char sel[32];
					sprintf(sel, "you choose the %d", selected);
					MessageBox(hwnd, sel, TEXT("tab"), MB_ICONINFORMATION);
					return TRUE;			
				}
			case IDOK:
				return TRUE;
			}
		}
	case WM_CLOSE:
		{
			EndDialog(hwnd, HIWORD(wParam));
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CALLBACK SysManagementProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HINSTANCE hinstance = (HINSTANCE)GetWindowLong(GetParent(hwnd), GWL_HINSTANCE);
	switch (msg) {
	case WM_INITDIALOG:
		{
			CListView user;
			user.Initialization(hwnd, IDC_USER_LIST);
			user.InsertColumn(0, 100, "用户名");
			user.InsertColumn(1, 100, " 权限");
			user.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			CLoginForm login_user;
			login_user.GetRecordSet();
			login_user.MoveFirst();
			int i=0;
			while(!login_user.IsEOF())
			{
				user.InsertItem(i, login_user.name());
				user.SetItem(i, 1, login_user.permission_name());
				login_user.MoveNext();
				i++;
			}
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam)) {
			case IDC_ADD_USER:
				{
				DialogBoxParam(hinstance,  MAKEINTRESOURCE(IDD_EDIT_USER), \
						hwnd, (DLGPROC)EditUserProc,(LONG)&hinstance);
				}
				break;
			case IDC_MODIFY_USER:
				{
				/*TODO: 获取用户信息*/
					
					CListView list;
					LoginUser login_user;
					list.Initialization(hwnd, IDC_USER_LIST);
					int select_row = list.GetSelectionMark();
					if (-1 == select_row) {
						MessageBox(hwnd, TEXT("请先选择用户！"), TEXT("系统管理"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					login_user.menu_id = IDC_MODIFY_USER;
					login_user.user_old_name = list.GetItem(select_row, 0);
					login_user.user_permission_name = list.GetItem(select_row, 1);
				DialogBoxParam(hinstance,  MAKEINTRESOURCE(IDD_EDIT_USER), \
						hwnd, (DLGPROC)EditUserProc,(LONG)&login_user);
				}
				break;
			}
		}
	}
	return FALSE;
}


BOOL CALLBACK FinanceProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HINSTANCE hinstance = (HINSTANCE)GetWindowLong(GetParent(hwnd), GWL_HINSTANCE);	
	switch (msg) {
	case WM_INITDIALOG:
		{
			CListView user;
			user.Initialization(hwnd, IDC_CONSUMPTION);
			user.InsertColumn(0, 100, "消费者编号");
			user.InsertColumn(1, 100, "消费金额");
			user.InsertColumn(2, 100, "消费日期");
			user.InsertColumn(3, 100, "营业员");
			user.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_CONSUMPTION_DETAIL:
				{
					DialogBoxParam(hinstance,  MAKEINTRESOURCE(IDD_CONSUMPTION_DETAIL), \
						hwnd, (DLGPROC)ConsumeDetailProc,(LONG)&hinstance);
				}
				break;
			}
		}
	}
	return FALSE;
}

BOOL CALLBACK ConsumeDetailProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_INITDIALOG:
			{
				return TRUE;
			}
		case WM_COMMAND:
			{
				
				return TRUE;
			}
		case WM_CLOSE:
			{
				EndDialog(hwnd, HIWORD(wParam));
				return TRUE;
			}
	}
	return FALSE;
}


BOOL CALLBACK EditUserProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static LoginUser *login_user;
	switch (msg)
	{
	case WM_INITDIALOG:
		{
			login_user = (LoginUser *)lParam;
			CButton button;
			if (login_user->menu_id == IDC_MODIFY_USER) {
				if (login_user->user_permission_name == "前台管理") {
					button.Initialization(hwnd, IDC_DESK_MANAGEMENT);
					button.SetChecked(TRUE);
				} else if (login_user->user_permission_name == "库存管理") {
					button.Initialization(hwnd, IDC_STOCK_MANAGEMENT);
					button.SetChecked(TRUE);
				} else if (login_user->user_permission_name == "人事管理") {
					button.Initialization(hwnd, IDC_PERSONNEL_MANAGEMENT);
					button.SetChecked(TRUE);
				} else {
					button.Initialization(hwnd, IDC_SYS_MANAGEMENT);
					button.SetChecked(TRUE);
				}
			}
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case IDC_E_ADD_USER:
				{
					char name[20];
					GetDlgItemText(hwnd, IDC_E_USER_NAME, name, 32);
					char passwd1[30], passwd2[30];
					GetDlgItemText(hwnd, IDC_E_USER_PASSWD, passwd1, 30);
					GetDlgItemText(hwnd, IDC_E_CONFROM_PASSWD, passwd2, 30);
					if (0 != strcmp(passwd1, passwd2)) {
						MessageBox(hwnd, TEXT("两次密码不一致！"), TEXT("系统管理"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					std::string permission_name = GetPermissionName(hwnd);
					if (permission_name == "") {
						MessageBox(hwnd, TEXT("请选择用户权限！"), TEXT("系统管理"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					LoginUser user;
					user.user_name = std::string(name);
					user.user_permission_name = permission_name;
					user.user_passwd = std::string(passwd1);
					break;
				}
			case IDC_E_MODIFY_USER:
				{
					char name[20];
					GetDlgItemText(hwnd, IDC_E_USER_NAME, name, 32);
					char passwd1[30], passwd2[30];
					GetDlgItemText(hwnd, IDC_E_USER_PASSWD, passwd1, 30);
					GetDlgItemText(hwnd, IDC_E_CONFROM_PASSWD, passwd2, 30);
					if (0 != strcmp(passwd1, passwd2)) {
						MessageBox(hwnd, TEXT("两次密码不一致！"), TEXT("系统管理"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					std::string permission_name = GetPermissionName(hwnd);
					if (permission_name == "") {
						MessageBox(hwnd, TEXT("请选择用户权限！"), TEXT("系统管理"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					LoginUser user;
					user.user_name = std::string(name);
					user.user_permission_name = permission_name;
					user.user_passwd = std::string(passwd1);
					break;
				}
			case IDC_E_CANCEL:
				EndDialog(hwnd, TRUE);
				break;
			}
			
			return TRUE;
		}
	case WM_CLOSE:
		{
			EndDialog(hwnd, HIWORD(wParam));
			return TRUE;
		}
	}
	return FALSE;
}

std::string GetPermissionName(HWND hwnd) {
	CButton desk, stock, personnel, sys;
	desk.Initialization(hwnd, IDC_DESK_MANAGEMENT);
	stock.Initialization(hwnd, IDC_STOCK_MANAGEMENT);
	personnel.Initialization(hwnd, IDC_PERSONNEL_MANAGEMENT);
	sys.Initialization(hwnd, IDC_SYS_MANAGEMENT);
	std::string data;
	if (desk.IsChecked()) {
		data = "前台管理";
	} else if (stock.IsChecked()) {
		data = "库存管理";
	} else if (personnel.IsChecked()) {
		data = "人事管理";
	} else if (sys.IsChecked()) {
		data = "系统管理";
	} else {
			data = "";
	}
	return data;
}