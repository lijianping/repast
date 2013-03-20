#include "manager.h"
#include "Button.h"



BOOL CALLBACK UserManagementProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HINSTANCE hinstance = (HINSTANCE)GetWindowLong(GetParent(hwnd), GWL_HINSTANCE);
	switch (msg) {
	case WM_INITDIALOG:
		{
			CListView user;
			user.Initialization(hwnd, IDC_USER_LIST);
			user.InsertColumn(0, 200, "�û���");
			user.InsertColumn(1, 200, " Ȩ��");
			user.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	        ShowLoginUser(hwnd);
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam)) {
			case IDC_ADD_USER:
				{
				DialogBoxParam(hinstance,  MAKEINTRESOURCE(IDD_EDIT_USER), \
						hwnd, (DLGPROC)EditUserProc,(LONG)&hinstance);
				ShowLoginUser(hwnd);
				}
				break;
			case IDC_MODIFY_USER:
				{
					CListView list;
					LoginUser login_user;
					list.Initialization(hwnd, IDC_USER_LIST);
					int select_row = list.GetSelectionMark();
					if (-1 == select_row) {
						MessageBox(hwnd, TEXT("����ѡ���û���"), TEXT("ϵͳ����"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					login_user.menu_id = IDC_MODIFY_USER;
					login_user.user_old_name = list.GetItem(select_row, 0);
					login_user.user_permission_name = list.GetItem(select_row, 1);
				DialogBoxParam(hinstance,  MAKEINTRESOURCE(IDD_EDIT_USER), \
						hwnd, (DLGPROC)EditUserProc,(LONG)&login_user);
				 ShowLoginUser(hwnd);
				}
				break;
			case  IDC_DELETE_USER:
				{
					CListView list;
					list.Initialization(hwnd, IDC_USER_LIST);
					int select_row = list.GetSelectionMark();
					if (-1 == select_row) {
						MessageBox(hwnd, TEXT("����ѡ���û���"), TEXT("ϵͳ����"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					if (IDNO ==MessageBox(hwnd, TEXT("ȷ��ɾ�����û���"), \
						TEXT("ɾ���û�"), MB_YESNO))
					{
						break;
					}
					CLoginForm login_form;
					std::string error;
					if (!login_form.DeleteInfo(list.GetItem(select_row, 0), error))
					{
						MessageBox(hwnd, error.c_str(), TEXT("ɾ���û�"), MB_OK);
						break;
					}
					MessageBox(hwnd, TEXT("ɾ���û��ɹ���"), TEXT("ɾ���û�"), MB_OK);
					ShowLoginUser(hwnd);
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
			user.InsertColumn(0, 100, "�����߱��");
			user.InsertColumn(1, 100, "���ѽ��");
			user.InsertColumn(2, 100, "��������");
			user.InsertColumn(3, 100, "ӪҵԱ");
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
				ShowWindow(GetDlgItem(hwnd, IDC_E_ADD_USER), SW_HIDE);
				SetDlgItemText(hwnd, IDC_E_USER_NAME, login_user->user_old_name.c_str());
				if (login_user->user_permission_name == "ǰ̨����") {
					button.Initialization(hwnd, IDC_DESK_MANAGEMENT);
					button.SetChecked(TRUE);
				} else if (login_user->user_permission_name == "������") {
					button.Initialization(hwnd, IDC_STOCK_MANAGEMENT);
					button.SetChecked(TRUE);
				} else if (login_user->user_permission_name == "���¹���") {
					button.Initialization(hwnd, IDC_PERSONNEL_MANAGEMENT);
					button.SetChecked(TRUE);
				} else {
					button.Initialization(hwnd, IDC_SYS_MANAGEMENT);
					button.SetChecked(TRUE);
				}
			}
			else
			{
				ShowWindow(GetDlgItem(hwnd, IDC_E_MODIFY_USER), SW_HIDE);
			}
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case IDC_E_ADD_USER:
				{
					CLoginForm login_form;
					std::string error;
					char name[20];
					GetDlgItemText(hwnd, IDC_E_USER_NAME, name, 32);
					char passwd1[30], passwd2[30];
					//passwd1 = new char[30];
					//passwd2 = new char[30];
					memset(passwd1, 0, sizeof(passwd1));
					memset(passwd2, 0, sizeof(passwd2));
					std::string p1, p2;
					GetDlgItemText(hwnd, IDC_E_USER_PASSWD, passwd1, 30);
					p1 = login_form.Encrypt(passwd1, strlen(passwd1)/2, strlen(passwd1));
				//	delete [] passwd1;
					GetDlgItemText(hwnd, IDC_E_CONFROM_PASSWD, passwd2, 30);
					p2 = login_form.Encrypt(passwd2, strlen(passwd2)/2, strlen(passwd2));
				//	delete [] passwd1;
					if (p1 != p2) {
						MessageBox(hwnd, TEXT("�������벻һ�£�"), TEXT("ϵͳ����"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					std::string permission_name = GetPermissionName(hwnd);
// 					if (permission_name == "") {
// 						MessageBox(hwnd, TEXT("��ѡ���û�Ȩ�ޣ�"), TEXT("ϵͳ����"), MB_OK | MB_ICONINFORMATION);
// 						break;
// 					}
				
					LoginUser user;
					user.user_name = std::string(name);
					user.user_permission_name = permission_name;
					user.user_passwd = p1;
					
					if (false == login_form.InsertInfo(&user, error))
					{
						MessageBox(hwnd, error.c_str(), TEXT("�����û�ʧ�ܣ�"), MB_OK);
						break;
					}
					MessageBox(hwnd,TEXT("�����û��ɹ���"), TEXT("ϵͳ����"), MB_OK);
					EndDialog(hwnd, TRUE);
					break;
				}
			case IDC_E_MODIFY_USER:
				{
					CLoginForm login_form;
					std::string error;
					char name[20];
					GetDlgItemText(hwnd, IDC_E_USER_NAME, name, 32);
					char passwd1[30], passwd2[30];
					//passwd1 = new char[30];
					//passwd2 = new char[30];
					memset(passwd1, 0, sizeof(passwd1));
					memset(passwd2, 0, sizeof(passwd2));
					std::string p1, p2;
					GetDlgItemText(hwnd, IDC_E_USER_PASSWD, passwd1, 30);
					p1 = login_form.Encrypt(passwd1, strlen(passwd1)/2, strlen(passwd1));
					//	delete [] passwd1;
					GetDlgItemText(hwnd, IDC_E_CONFROM_PASSWD, passwd2, 30);
					p2 = login_form.Encrypt(passwd2, strlen(passwd2)/2, strlen(passwd2));
					//	delete [] passwd1;
					if (p1 != p2) {
						MessageBox(hwnd, TEXT("�������벻һ�£�"), TEXT("ϵͳ����"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					std::string permission_name = GetPermissionName(hwnd);
// 					if (permission_name == "") {
// 						MessageBox(hwnd, TEXT("��ѡ���û�Ȩ�ޣ�"), TEXT("ϵͳ����"), MB_OK | MB_ICONINFORMATION);
// 						break;
// 					}
					
					LoginUser user;
					user.user_name = std::string(name);
					user.user_permission_name = permission_name;
					user.user_passwd = p1;
					user.user_old_name  = login_user->user_old_name;
					if (false == login_form.UpdateInfo(&user, error))
					{
						MessageBox(hwnd, error.c_str(), TEXT("�޸��û���Ϣʧ�ܣ�"), MB_OK);
						break;
					}
					MessageBox(hwnd,TEXT("�޸��û���Ϣ�ɹ���"), TEXT("ϵͳ����"), MB_OK);
					EndDialog(hwnd, TRUE);
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
		data = "ǰ̨����";
	} else if (stock.IsChecked()) {
		data = "������";
	} else if (personnel.IsChecked()) {
		data = "���¹���";
	} else if (sys.IsChecked()) {
		data = "ϵͳ����";
	} else {
			data = "";
	}
	return data;
}


bool ShowLoginUser(HWND hwnd)
{
	CListView user;
	user.Initialization(hwnd, IDC_USER_LIST);
	user.DeleteAllItems();
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
	return true;
}