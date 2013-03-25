#include "manager.h"
#include "Button.h"



BOOL CALLBACK UserManagementProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HINSTANCE hinstance = (HINSTANCE)GetWindowLong(GetParent(hwnd), GWL_HINSTANCE);
	switch (msg) {
	case WM_INITDIALOG:
		{
			CListView user;
			user.Initialization(hwnd, IDC_USER_LIST);
			user.InsertColumn(0, 100, "Ա�����");
			user.InsertColumn(1, 100, "Ա������");
			user.InsertColumn(2, 100, "��¼��");
			user.InsertColumn(3, 100, "Ȩ��");
			user.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	        ShowLoginUser(hwnd);
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_ADD_USER:
				{
					LoginUser login_user;

					login_user.menu_id = IDC_ADD_USER;   // ���ӵ�¼�û� ֻ��Ҫ��ťid����
					DialogBoxParam(hinstance,  MAKEINTRESOURCE(IDD_EDIT_USER), \
								   hwnd, (DLGPROC)EditUserProc,(LONG)&login_user);
					ShowLoginUser(hwnd);
				}
				break;
			case IDC_MODIFY_USER:
				{
					CListView list;
					list.Initialization(hwnd, IDC_USER_LIST);
					int select_row = list.GetSelectionMark();
					if (-1 == select_row) {
						MessageBox(hwnd, TEXT("����ѡ���û���"), TEXT("ϵͳ����"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					LoginUser login_user;
					// Ա���������ӶԻ����н������ݿ������ȡ
					login_user.menu_id = IDC_MODIFY_USER;     // ��ťid
					login_user.staff_no = list.GetItem(select_row, 0);  // Ա�����
					login_user.new_login_name = list.GetItem(select_row, 2);  // �û���ǰ��¼��
					login_user.login_permission = list.GetItem(select_row, 3); // �û���ǰȨ��
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
					if (!login_form.DeleteUser(list.GetItem(select_row, 0).c_str(), error))
					{
						MessageBox(hwnd, error.c_str(), TEXT("ɾ���û�"), MB_OK);
						break;
					}
					MessageBox(hwnd, TEXT("ɾ���û��ɹ���"), TEXT("ɾ���û�"), MB_OK);
					ShowLoginUser(hwnd);
				}
				break;
			case IDC_EDIT_PERMISSION://�༭Ȩ��
				{
					DialogBox(hinstance, MAKEINTRESOURCE(IDD_EDIT_PERMISSION), hwnd, (DLGPROC)EditPermissionProc);
					break;
				}
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
					if (start_date_int > end_date_int) {  // ʱ�����벻�Ϸ�
						MessageBox(hwnd, TEXT("ʱ�����벻�Ϸ�"), TEXT("��ʾ"), MB_OK | MB_ICONINFORMATION);
						break;
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
	static LoginUser login_user_info;
	switch (msg)
	{
	case WM_INITDIALOG:
		{
			LoginUser *login_user = (LoginUser *)lParam;
			login_user_info.menu_id = login_user->menu_id;  // ��ťid ��ͬ�İ�ť��ʼֵʹ�ò�ͬ
			CButton button;
			CPermission all_permission;
			CComboBox permission_combo;
			permission_combo.Initialization(hwnd, IDC_E_USER_PERMISSION);
			all_permission.SetSQLStatement("exec SelectPermissionAll");
			all_permission.GetRecordSet();
			int index = 0;
			while(!all_permission.IsEOF())     // ��ʼ��Ȩ�ް�ť
			{
				permission_combo.AddString(all_permission.name());
				index++;
			}
			CEdit staff_name(hwnd, IDC_E_STAFF_NAME);
			staff_name.SetReadOnly();                //  ���������༭��Ϊֻ��ģʽ    
			if (login_user_info.menu_id == IDC_ADD_USER) {  // �����û�ʱ��ʾ����Ա�����
				InitStaffNo(hwnd, IDC_E_USER_ID);
				ShowWindow(GetDlgItem(hwnd, IDC_E_MODIFY_USER), SW_HIDE);  // �����޸İ�ť
				
			} else {
				login_user_info.staff_no = login_user->staff_no;    // �û����
				login_user_info.new_login_name = login_user->new_login_name;  // �û���ǰ��¼��
				login_user_info.login_permission = login_user->login_permission;  // �û���ǰ��¼Ȩ��
				int index = permission_combo.FindString(login_user_info.login_permission.c_str());
				if (-1 != index) {
					permission_combo.SetCurSel(index);   // ��ʾ�û�Ȩ��
				}
				CComboBox staff_no(hwnd, IDC_E_USER_ID);    // ��ʾ�û�Ա�����
				staff_no.AddString(login_user_info.staff_no);
				staff_no.SetCurSel(0);    // Ĭ��ѡ��
				CStaffForm staff;
				std::string err_info;   
				// ��ȡԱ������
				if (staff.GetStaffName(login_user_info.staff_no.c_str(), err_info)) {	
					staff_name.SetEditText(staff.name());  // ��Ų��ظ���ֻ��һ����¼
				}
				CEdit login_name(hwnd, IDC_E_LOGIN_NAME);
				login_name.SetEditText(login_user_info.new_login_name);  // ��ʾ��½�û���
				ShowWindow(GetDlgItem(hwnd, IDC_E_ADD_USER), SW_HIDE); // �������Ӱ�ť
			}
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case IDC_E_ADD_USER:
				{
					LoginUser user;
					std::string err_info;
					if (!GetLoginUserInfo(hwnd, &user, err_info)) {
						MessageBox(hwnd, err_info.c_str(), TEXT("ϵͳ����"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					CLoginForm login;
					if (!login.AddUser(&user, err_info)) {
						MessageBox(hwnd, err_info.c_str(), TEXT("ϵͳ����"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					MessageBox(hwnd, TEXT("����û��ɹ���"), TEXT("ϵͳ����"), MB_OK | MB_ICONINFORMATION);
					EndDialog(hwnd, TRUE);
					break;
				}   // end IDC_E_ADD_USER
			case IDC_E_MODIFY_USER:
				{
					LoginUser user;
					std::string err_info;
					if (!GetLoginUserInfo(hwnd, &user, err_info)) {
						MessageBox(hwnd, err_info.c_str(), TEXT("ϵͳ����"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					CLoginForm login;
					if (!login.ModifyUser(&user, err_info)) {
						MessageBox(hwnd, err_info.c_str(), TEXT("ϵͳ����"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					MessageBox(hwnd, TEXT("�޸��û���Ϣ�ɹ���"), TEXT("ϵͳ����"), MB_OK | MB_ICONINFORMATION);
					EndDialog(hwnd, TRUE);
					break;
				}
			case IDC_E_USER_ID:  // Ա�����������
			{
				if (HIWORD(wParam) == CBN_SELCHANGE)
				{
					CComboBox staff_no(hwnd, IDC_E_USER_ID);
					std::string number;
					staff_no.GetComboBoxText(number);
					CStaffForm staff;
					std::string err_info;   
					// ����ѡ���Ա����Ż�ȡԱ������
					if (staff.GetStaffName(number.c_str(), err_info)) {
						CEdit staff_name(hwnd, IDC_E_STAFF_NAME);
						staff_name.SetEditText(staff.name());  // ��Ų��ظ���ֻ��һ����¼
					}
				}
				break;
			}  // end IDC_E_USER_ID
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



BOOL CALLBACK EditPermissionProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		{
			CListView permission_list;
			permission_list.Initialization(hwnd, IDC_USER_PERMISSION);
			permission_list.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			if (-1 == permission_list.InsertColumn(0, 100, "Ȩ�ޱ��") ||
				-1 == permission_list.InsertColumn(1, 100, "Ȩ������"))
			{
				MessageBox(hwnd, TEXT("��ʼ��Ȩ����Ϣ�б�ʧ�ܣ�"), TEXT("����"), MB_OK);
				EndDialog(hwnd,HIWORD(wParam));	
				return TRUE;
			}
			if(!ShowPermissionList(hwnd))//��ʾ���е�Ȩ����Ϣ
			{
				MessageBox(hwnd, TEXT("��ʾȨ����Ϣ�б�ʧ�ܣ�"), TEXT("����"), MB_OK);
				EndDialog(hwnd,HIWORD(wParam));	
				return TRUE;
			}
			return TRUE;
		}
	case  WM_NOTIFY:
		{
			switch(LOWORD(wParam))
			{
			case IDC_USER_PERMISSION:
				{
					if (((LPNMHDR)lParam)->code == NM_CLICK)/*���Ȩ���б��е�һ��*/
					{
						int index=0;
						CEdit e_name,e_id;
						CListView permission_list;
						permission_list.Initialization(hwnd, IDC_USER_PERMISSION);
						e_id.Initialization(hwnd, IDC_E_PERMISSION_NO);
						e_name.Initialization(hwnd, IDC_E_PERMISSION_NAME);
						index = permission_list.GetSelectionMark();
						e_id.SetEditText(permission_list.GetItem(index,0));
						e_name.SetEditText(permission_list.GetItem(index,1));
					}
					break;
				}
			}
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case IDC_E_PERMISSION_ADD:
				{
                    AddPermission(hwnd);
					break;
				}
			case IDC_E_PERMISSION_MODIFY:
				{
					ModifyPermission(hwnd);
					break;
				}
			case IDC_E_PERMISSION_DELETE:
				{
					DeletePermission(hwnd);
					break;
				}
			case IDC_E_PERMISSION_CANCEL:
				{
					EndDialog(hwnd, HIWORD(wParam));
					break;
				}
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

bool ShowLoginUser(HWND hwnd)
{
	CListView user;
	user.Initialization(hwnd, IDC_USER_LIST);
	user.DeleteAllItems();
	CLoginForm login_user;
	login_user.SetSQLStatement("exec GetLoginUserInfo");
	login_user.GetRecordSet();
	int i=0;
	while(!login_user.IsEOF())
	{
		user.InsertItem(i, login_user.no());
		user.SetItem(i, 1,login_user.staff_name());
		user.SetItem(i, 2, login_user.name());
		user.SetItem(i, 3, login_user.permission_name());
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
	}
	return true;
}



/*
 * ˵����
 *     ��ʾ���е�Ȩ����Ϣ
 * ������
 *      hwnd   [in] ��list_view�����ĶԻ�����
 * ����ֵ��
 *      �ɹ�����true, ���򷵻�false
 */
bool ShowPermissionList(HWND hwnd)
{
	CListView permission_list;
	if(!permission_list.Initialization(hwnd, IDC_USER_PERMISSION))
	{
		return false;
	}
	if(!permission_list.DeleteAllItems())
	{
		return false;
	}
	CPermission all_permission;
	all_permission.SetSQLStatement("exec SelectPermissionAll");
	if(!all_permission.GetRecordSet())
	{
		return false;
	}
	int list_index=0;
	while(!all_permission.IsEOF())
	{
		if(-1 == permission_list.InsertItem(list_index, all_permission.no()))
		{
			return false;
		}
		if(!permission_list.SetItem(list_index,1, all_permission.name()))
		{
			return false;
		}
		list_index++;
	}
	return true;
}

bool AddPermission(HWND hwnd)
{
	CEdit e_name,e_id;
	std::string error;
	PERMISSION permission_info;
	CPermission permission;

	e_id.Initialization(hwnd,IDC_E_PERMISSION_NO);
	e_name.Initialization(hwnd, IDC_E_PERMISSION_NAME);
	
	e_id.GetEditText(permission_info.no);
	e_name.GetEditText(permission_info.name);
	permission_info.old_no = permission_info.no;
    if (permission.InsertPermission(&permission_info, error))
    {
		MessageBox(hwnd, TEXT("���Ȩ�޳ɹ���"), TEXT("�ɹ�"), MB_OK);
		e_id.SetEditText("");
		e_name.SetEditText("");
		ShowPermissionList(hwnd);
		return true;
    }
	else
	{
		MessageBox(hwnd, error.c_str(), TEXT("ʧ��"), MB_OK);
		ShowPermissionList(hwnd);
		return false;
	}
	return true;
}

bool ModifyPermission(HWND hwnd)
{
	CEdit e_id, e_name;
	PERMISSION permissioin_data;
	CListView permission_list;
	CPermission permissioin;
	int list_index;
	std::string category_no;
	std::string error;
	
	e_id.Initialization(hwnd, IDC_E_PERMISSION_NO);
	e_name.Initialization(hwnd, IDC_E_PERMISSION_NAME);
	
	permission_list.Initialization(hwnd, IDC_USER_PERMISSION);
	list_index = permission_list.GetSelectionMark();
	if (-1 == list_index)
	{
		MessageBox(hwnd, TEXT("�����б���ѡ��һ��"), TEXT("��ʾ"), MB_OK);
		return false;
	}
	if (MessageBox(hwnd, TEXT("�޸�Ȩ�޽����޸Ĵ�Ȩ�޺��������ĵ�¼�û���\n\n       ���ٴ�ȷ���Ƿ��޸ģ�"),\
		TEXT("��Ҫ��ʾ"), MB_YESNOCANCEL)==IDYES)
	{
		permissioin_data.old_no = permission_list.GetItem(list_index,0);/*��ȡ�б���ѡ���һ�еĵ�һ���ֶ�*/
		e_id.GetEditText(permissioin_data.no);
		e_name.GetEditText(permissioin_data.name);
	
		if (permissioin.UpdatePermission(&permissioin_data,error))
		{
			MessageBox(hwnd, TEXT("�޸Ĵ�Ȩ����Ϣ�ɹ���"), TEXT("�ɹ�"), MB_OK);
			e_id.SetEditText("");
			e_name.SetEditText("");
			ShowPermissionList(hwnd);
			return true;
		}
		else
		{
			MessageBox(hwnd, error.c_str(), TEXT("����"), MB_OK);
			ShowPermissionList(hwnd);
			return false;
		}
	}
	ShowPermissionList(hwnd);
	return false;
}

bool DeletePermission(HWND hwnd)
{	
	CEdit e_id, e_name;
	PERMISSION permissioin_data;
	CListView permission_list;
	CPermission permissioin;
	int list_index;
	std::string category_no;
	std::string error;
	
	e_id.Initialization(hwnd, IDC_E_PERMISSION_NO);
	e_name.Initialization(hwnd, IDC_E_PERMISSION_NAME);

	permission_list.Initialization(hwnd, IDC_USER_PERMISSION);
	list_index = permission_list.GetSelectionMark();
	if (-1 == list_index)
	{
		MessageBox(hwnd, TEXT("�����б���ѡ��һ��"), TEXT("��ʾ"), MB_OK);
		return false;
	}
	if (MessageBox(hwnd, TEXT("ɾ��Ȩ�޽���ɾ����Ȩ�޺��������ĵ�¼�û���\n\n       ���ٴ�ȷ���Ƿ�ɾ����"),\
		TEXT("��Ҫ��ʾ"), MB_YESNOCANCEL)==IDYES)
	{
		permissioin_data.no = permission_list.GetItem(list_index,0);/*��ȡ�б���ѡ���һ�еĵ�һ���ֶ�*/
		permissioin_data.name = permission_list.GetItem(list_index,1);
		permissioin_data.old_no = permissioin_data.no;
		if (permissioin.DeletePermission(&permissioin_data,error))
		{
			MessageBox(hwnd, TEXT("ɾ����Ȩ����Ϣ�ɹ���"), TEXT("�ɹ�"), MB_OK);
			e_id.SetEditText("");
			e_name.SetEditText("");
			ShowPermissionList(hwnd);
			return true;
		}
		else
		{
			MessageBox(hwnd, error.c_str(), TEXT("����"), MB_OK);
			ShowPermissionList(hwnd);
			return false;
		}
	}
	ShowPermissionList(hwnd);
	return false;
}
/*
 * @ brief: ��ȡ�༭��¼�û��Ի�������
 * @ param: hwnd [in] ���ھ��
 * @ param: user [out] ָ���¼�û��Ľṹ��ָ�룬�������ʹ����
 *                     staff_no, login_permission, new_login_name, password1�ĸ��ֶ�
 * @ param: err_info [out] ������Ϣ����
 * @ return: ���ɹ�����true�����򷵻�false
 **/
bool GetLoginUserInfo(HWND hwnd, LoginUser *user, std::string &err_info) {
	CComboBox combo(hwnd, IDC_E_USER_ID);   // ��ʼ��Ա�����combo box
	std::string staff_no, permission_name;
	if (!combo.GetComboBoxText(staff_no)) {  // ��ȡԱ�����
		err_info = "��ȡԱ�����ʧ��";
		return false;
	}
	user->staff_no = staff_no; 
	combo.Initialization(hwnd, IDC_E_USER_PERMISSION); // ��ʼ���û�Ȩ��combo box
	if (!combo.GetComboBoxText(permission_name)) { // ��ȡ�û�Ȩ��
		err_info = "��ȡ�û�Ȩ��ʧ��";
		return false;
	}
	user->login_permission = permission_name;
	CEdit edit(hwnd, IDC_E_LOGIN_NAME);  // ��ʼ���û����༭��
	std::string login_name, password1, password2, p1, p2;
	if (!edit.GetEditText(login_name)) {  // ��ȡ�û���¼��
		err_info = "��ȡ�û���¼��ʧ��";
		return false;
	}
	user->new_login_name = login_name;   // ������µ�¼���У��Ա��޸Ŀɹ�ͬʹ��
	edit.Initialization(hwnd, IDC_E_USER_PASSWD); // ��ȡ�û�����
	if (!edit.GetEditText(password1)) {
		err_info = "��ȡ�û�����ʧ��";
		return false;
	}
	CLoginForm lo;
	p1 = lo.Encrypt(password1.c_str(), password1.length() / 2, password1.length());
	edit.Initialization(hwnd, IDC_E_CONFROM_PASSWD); // ��ȡ�û�ȷ������
	if (!edit.GetEditText(password2)) {
		err_info = "��ȡ�û�ȷ������ʧ��";
		return false;
	}
	p2 = lo.Encrypt(password2.c_str(), password2.length() / 2, password2.length());
	if (p1 != p2) {
		err_info = "�����������벻һ��";
		return false;
	}
	user->password1 = p1;
	return true;
}