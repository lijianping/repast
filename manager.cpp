#include "manager.h"
#include "Button.h"



BOOL CALLBACK UserManagementProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HINSTANCE hinstance = (HINSTANCE)GetWindowLong(GetParent(hwnd), GWL_HINSTANCE);
	switch (msg) {
	case WM_INITDIALOG:
		{
			CListView user;
			user.Initialization(hwnd, IDC_USER_LIST);
			user.InsertColumn(0, 100, "���");
			user.InsertColumn(1, 100, "��¼��");
			user.InsertColumn(2, 100, "Ȩ��");
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
			user.InsertColumn(2, 100, "��̨/Ԥ��ʱ��");
			user.InsertColumn(3, 100, "����ʱ��");
			user.InsertColumn(4, 100, "ӪҵԱ");
			user.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			// TODO: ��ѯ���ݿ⣬��ʾʱ��ε������ߣ�Ĭ�ϵ���
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_CONSUMPTION_DETAIL: // ��������ϸ
				{
					CListView consumption(hwnd, IDC_CONSUMPTION);
					int select = consumption.GetSelectionMark();
// 					if (-1 == select) {
// 						MessageBox(hwnd, TEXT("��ѡ��һ��������"), TEXT("��ʾ"), MB_OK | MB_ICONINFORMATION);
// 						break;
// 					}
                    ConsumerInfo consumer_info;
					consumer_info.consumer_id = consumption.GetItem(select, 0);
					consumer_info.consumption_amount = consumption.GetItem(select, 1);
					consumer_info.start_time = consumption.GetItem(select, 2);
					consumer_info.end_time = consumption.GetItem(select, 3);
					consumer_info.clerk = consumption.GetItem(select, 4);
					DialogBoxParam(hinstance,  MAKEINTRESOURCE(IDD_CONSUMPTION_DETAIL), \
						hwnd, (DLGPROC)ConsumeDetailProc,(LONG)&consumer_info);
					break;
				}	
			case IDC_QUERY_DETAIL:  // ��ѯʱ����ڵ�������
				{
					TCHAR start_date[256], end_date[256];
					memset(start_date, 0, sizeof(start_date));
					memset(end_date, 0, sizeof(end_date));
					GetDlgItemText(hwnd, IDC_START_DATE,start_date, 256);  // ��ȡʱ��
					GetDlgItemText(hwnd, IDC_END_DATE, end_date, 256);
					TCHAR date[256];
					std::string start_date_str, end_date_str;
					// ת�����ڸ�ʽ
					int start_date_int = ConvertDate((const char *)start_date, start_date_str);
					int end_date_int = ConvertDate((const char *)end_date, end_date_str);
					sprintf(date, "start:%s--end:%s", start_date_str.c_str(), end_date_str.c_str());
					MessageBox(hwnd, date, TEXT("time"), MB_OK | MB_ICONINFORMATION);
					if (start_date_int > end_date_int) {
						MessageBox(hwnd, TEXT("Error"), TEXT("time"), MB_OK | MB_ICONINFORMATION);
					}
					// TODO: ��ѯ���ݿ⣬��ʾʱ��ε�������
					break;
				}
				break;
			}
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CALLBACK ConsumeDetailProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static ConsumerInfo consumer_info;
	switch (msg)
	{
		case WM_INITDIALOG:
			{
				ConsumerInfo *info = (ConsumerInfo *)lParam;         // ��������,��̬����
				consumer_info.consumer_id = info->consumer_id;
				consumer_info.consumption_amount = info->consumption_amount;
				consumer_info.start_time = info->start_time;
				consumer_info.end_time = info->end_time;
				consumer_info.clerk = info->clerk;
				CListView custom_list(hwnd, IDC_LIST1);
				custom_list.InsertColumn(0, 120, "����");
				custom_list.InsertColumn(1, 120, "����");
				custom_list.InsertColumn(2, 120, "����");
				custom_list.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
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
			CPermission all_permission;
			CComboBox permission_combo;
			permission_combo.Initialization(hwnd, IDC_E_USER_PERMISSION);
			all_permission.SetSQLStatement("exec SelectPermissionAll");
			all_permission.GetRecordSet();

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
				InitStaffNo(hwnd, IDC_E_USER_ID);
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
					memset(passwd1, 0, sizeof(passwd1));
					memset(passwd2, 0, sizeof(passwd2));
					std::string p1, p2;
					GetDlgItemText(hwnd, IDC_E_USER_PASSWD, passwd1, 30);
					p1 = login_form.Encrypt(passwd1, strlen(passwd1)/2, strlen(passwd1));	
					GetDlgItemText(hwnd, IDC_E_CONFROM_PASSWD, passwd2, 30);
					p2 = login_form.Encrypt(passwd2, strlen(passwd2)/2, strlen(passwd2));
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
	login_user.SetSQLStatement("exec GetLoginUserInfo");
	login_user.GetRecordSet();
	login_user.MoveFirst();
	int i=0;
	while(!login_user.IsEOF())
	{
		user.InsertItem(i, login_user.no());
		user.SetItem(i,1, login_user.name());
		user.SetItem(i, 2, login_user.permission_name());
		login_user.MoveNext();
		i++;
	}
	return true;
}

/*
 * @ brief: ת�����ڣ��罫 2012��12��20�� ת��Ϊ2012-12-20 �Լ������� 20121220
 * @ param: date [in] �����ַ���
 * @ param: out_date [out] yyyy-mm-dd���ַ�����
 * @ return: ����������
 **/
int ConvertDate(const char *date, std::string &out_date) {
	std::string in_date(date);
	std::string year("��");
	std::string month("��");
	std::string day("��");
	std::string data;
	size_t index = 0;
	size_t pos = in_date.find(year);
	data = in_date.substr(index, pos);
	in_date.replace(pos, year.length(), "-");
	index = pos + 1;
	pos = in_date.find(month);
	data += in_date.substr(index, pos - index);
	in_date.replace(pos, month.length(), "-");
	index = pos + 1;
	pos = in_date.find(day);
	data += in_date.substr(index, pos - index);
	in_date.erase(pos, day.length());
	out_date = in_date;
	return atoi(data.c_str());
}

bool InitStaffNo(HWND hwnd, UINT id) {
	CComboBox staff_no(hwnd, id);
	CStaffForm staff;
	std::string err_info;
	staff.GetStaffNo(err_info);
	while (!staff.IsEOF()) {
		staff_no.AddString(staff.id());
		staff.MoveNext();
	}
	return true;
}
