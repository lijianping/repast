#include "manager.h"
#include "Button.h"



BOOL CALLBACK UserManagementProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HINSTANCE hinstance = (HINSTANCE)GetWindowLong(GetParent(hwnd), GWL_HINSTANCE);
	switch (msg) {
	case WM_INITDIALOG:
		{
			CListView user;
			user.Initialization(hwnd, IDC_USER_LIST);
			user.InsertColumn(0, 100, "员工编号");
			user.InsertColumn(1, 100, "员工姓名");
			user.InsertColumn(2, 100, "登录名");
			user.InsertColumn(3, 100, "权限");
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

					login_user.menu_id = IDC_ADD_USER;   // 增加登录用户 只需要按钮id即可
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
						MessageBox(hwnd, TEXT("请先选择用户！"), TEXT("系统管理"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					LoginUser login_user;
					// 员工姓名在子对话框中进行数据库操作获取
					login_user.menu_id = IDC_MODIFY_USER;     // 按钮id
					login_user.staff_no = list.GetItem(select_row, 0);  // 员工编号
					login_user.new_login_name = list.GetItem(select_row, 2);  // 用户当前登录名
					login_user.login_permission = list.GetItem(select_row, 3); // 用户当前权限
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
						MessageBox(hwnd, TEXT("请先选择用户！"), TEXT("系统管理"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					if (IDNO ==MessageBox(hwnd, TEXT("确定删除该用户吗？"), \
						TEXT("删除用户"), MB_YESNO))
					{
						break;
					}
					CLoginForm login_form;
					std::string error;
					if (!login_form.DeleteUser(list.GetItem(select_row, 0).c_str(), error))
					{
						MessageBox(hwnd, error.c_str(), TEXT("删除用户"), MB_OK);
						break;
					}
					MessageBox(hwnd, TEXT("删除用户成功！"), TEXT("删除用户"), MB_OK);
					ShowLoginUser(hwnd);
				}
				break;
			case IDC_EDIT_PERMISSION://编辑权限
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
			user.InsertColumn(0, 100, "消费者编号");
			user.InsertColumn(1, 100, "消费金额");
			user.InsertColumn(2, 100, "开台/预定时间");
			user.InsertColumn(3, 100, "结束时间");
			user.InsertColumn(4, 100, "营业员");
			user.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			// TODO: 查询数据库，显示时间段的消费者，默认当天
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_CONSUMPTION_DETAIL: // 消费者明细
				{
					CListView consumption(hwnd, IDC_CONSUMPTION);
					int select = consumption.GetSelectionMark();
// 					if (-1 == select) {
// 						MessageBox(hwnd, TEXT("请选择一个消费者"), TEXT("提示"), MB_OK | MB_ICONINFORMATION);
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
			case IDC_QUERY_DETAIL:  // 查询时间段内的消费者
				{
					TCHAR start_date[256], end_date[256];
					memset(start_date, 0, sizeof(start_date));
					memset(end_date, 0, sizeof(end_date));
					GetDlgItemText(hwnd, IDC_START_DATE,start_date, 256);  // 获取时间
					GetDlgItemText(hwnd, IDC_END_DATE, end_date, 256);
					TCHAR date[256];
					std::string start_date_str, end_date_str;
					// 转换日期格式
					int start_date_int = ConvertDate((const char *)start_date, start_date_str);
					int end_date_int = ConvertDate((const char *)end_date, end_date_str);
					sprintf(date, "start:%s--end:%s", start_date_str.c_str(), end_date_str.c_str());
					MessageBox(hwnd, date, TEXT("time"), MB_OK | MB_ICONINFORMATION);
					if (start_date_int > end_date_int) {  // 时间输入不合法
						MessageBox(hwnd, TEXT("时间输入不合法"), TEXT("提示"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					// TODO: 查询数据库，显示时间段的消费者
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
				ConsumerInfo *info = (ConsumerInfo *)lParam;         // 接收数据,静态保存
				consumer_info.consumer_id = info->consumer_id;
				consumer_info.consumption_amount = info->consumption_amount;
				consumer_info.start_time = info->start_time;
				consumer_info.end_time = info->end_time;
				consumer_info.clerk = info->clerk;
				CListView custom_list(hwnd, IDC_LIST1);
				custom_list.InsertColumn(0, 120, "名称");
				custom_list.InsertColumn(1, 120, "单价");
				custom_list.InsertColumn(2, 120, "数量");
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
			login_user_info.menu_id = login_user->menu_id;  // 按钮id 不同的按钮初始值使用不同
			CButton button;
			CPermission all_permission;
			CComboBox permission_combo;
			permission_combo.Initialization(hwnd, IDC_E_USER_PERMISSION);
			all_permission.SetSQLStatement("exec SelectPermissionAll");
			all_permission.GetRecordSet();
			all_permission.MoveFirst();
			int index = 0;
			while(!all_permission.IsEOF())     // 初始化权限按钮
			{
				permission_combo.AddString(all_permission.name());
				all_permission.MoveNext();
				index++;
			}
			CEdit staff_name(hwnd, IDC_E_STAFF_NAME);
			staff_name.SetReadOnly();                //  设置姓名编辑框为只读模式    
			if (login_user_info.menu_id == IDC_ADD_USER) {  // 增加用户时显示所有员工编号
				InitStaffNo(hwnd, IDC_E_USER_ID);
				ShowWindow(GetDlgItem(hwnd, IDC_E_MODIFY_USER), SW_HIDE);  // 隐藏修改按钮
				
			} else {
				login_user_info.staff_no = login_user->staff_no;    // 用户编号
				login_user_info.new_login_name = login_user->new_login_name;  // 用户当前登录名
				login_user_info.login_permission = login_user->login_permission;  // 用户当前登录权限
				int index = permission_combo.FindString(login_user_info.login_permission.c_str());
				if (-1 != index) {
					permission_combo.SetCurSel(index);   // 显示用户权限
				}
				CComboBox staff_no(hwnd, IDC_E_USER_ID);    // 显示用户员工编号
				staff_no.AddString(login_user_info.staff_no);
				staff_no.SetCurSel(0);    // 默认选中
				CStaffForm staff;
				std::string err_info;   
				// 获取员工姓名
				if (staff.GetStaffName(login_user_info.staff_no.c_str(), err_info)) {	
					staff_name.SetEditText(staff.name());  // 编号不重复，只有一条记录
				}
				CEdit login_name(hwnd, IDC_E_LOGIN_NAME);
				login_name.SetEditText(login_user_info.new_login_name);  // 显示登陆用户名
				ShowWindow(GetDlgItem(hwnd, IDC_E_ADD_USER), SW_HIDE); // 隐藏增加按钮
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
						MessageBox(hwnd, err_info.c_str(), TEXT("系统管理"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					CLoginForm login;
					if (!login.AddUser(&user, err_info)) {
						MessageBox(hwnd, err_info.c_str(), TEXT("系统管理"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					MessageBox(hwnd, TEXT("添加用户成功！"), TEXT("系统管理"), MB_OK | MB_ICONINFORMATION);
					EndDialog(hwnd, TRUE);
					break;
				}   // end IDC_E_ADD_USER
			case IDC_E_MODIFY_USER:
				{
					LoginUser user;
					std::string err_info;
					if (!GetLoginUserInfo(hwnd, &user, err_info)) {
						MessageBox(hwnd, err_info.c_str(), TEXT("系统管理"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					CLoginForm login;
					if (!login.ModifyUser(&user, err_info)) {
						MessageBox(hwnd, err_info.c_str(), TEXT("系统管理"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					MessageBox(hwnd, TEXT("修改用户信息成功！"), TEXT("系统管理"), MB_OK | MB_ICONINFORMATION);
					EndDialog(hwnd, TRUE);
					break;
				}
			case IDC_E_USER_ID:  // 员工编号下拉框
			{
				if (HIWORD(wParam) == CBN_SELCHANGE)
				{
					CComboBox staff_no(hwnd, IDC_E_USER_ID);
					std::string number;
					staff_no.GetComboBoxText(number);
					CStaffForm staff;
					std::string err_info;   
					// 根据选择的员工编号获取员工姓名
					if (staff.GetStaffName(number.c_str(), err_info)) {
						CEdit staff_name(hwnd, IDC_E_STAFF_NAME);
						staff_name.SetEditText(staff.name());  // 编号不重复，只有一条记录
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
			if (-1 == permission_list.InsertColumn(0, 100, "权限编号") ||
				-1 == permission_list.InsertColumn(1, 100, "权限名称"))
			{
				MessageBox(hwnd, TEXT("初始化权限信息列表失败！"), TEXT("错误"), MB_OK);
				EndDialog(hwnd,HIWORD(wParam));	
				return TRUE;
			}
			if(!ShowPermissionList(hwnd))//显示所有的权限信息
			{
				MessageBox(hwnd, TEXT("显示权限信息列表失败！"), TEXT("错误"), MB_OK);
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
					if (((LPNMHDR)lParam)->code == NM_CLICK)/*点击权限列表中的一项*/
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
	login_user.MoveFirst();
	int i=0;
	while(!login_user.IsEOF())
	{
		user.InsertItem(i, login_user.no());
		user.SetItem(i, 1,login_user.staff_name());
		user.SetItem(i, 2, login_user.name());
		user.SetItem(i, 3, login_user.permission_name());
		login_user.MoveNext();
		i++;
	}
	return true;
}

/*
 * @ brief: 转换日期，如将 2012年12月20日 转换为2012-12-20 以及数字型 20121220
 * @ param: date [in] 日期字符串
 * @ param: out_date [out] yyyy-mm-dd型字符日期
 * @ return: 数字型日期
 **/
int ConvertDate(const char *date, std::string &out_date) {
	std::string in_date(date);
	std::string year("年");
	std::string month("月");
	std::string day("日");
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



/*
 * 说明：
 *     显示所有的权限信息
 * 参数：
 *      hwnd   [in] 此list_view所属的对话框句柄
 * 返回值：
 *      成功返回true, 否则返回false
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
	if(!all_permission.MoveFirst())
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
		if(!all_permission.MoveNext())
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
		MessageBox(hwnd, TEXT("添加权限成功！"), TEXT("成功"), MB_OK);
		e_id.SetEditText("");
		e_name.SetEditText("");
		ShowPermissionList(hwnd);
		return true;
    }
	else
	{
		MessageBox(hwnd, error.c_str(), TEXT("失败"), MB_OK);
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
		MessageBox(hwnd, TEXT("请在列表中选择一项"), TEXT("提示"), MB_OK);
		return false;
	}
	if (MessageBox(hwnd, TEXT("修改权限将会修改此权限和其所属的登录用户！\n\n       请再次确认是否修改？"),\
		TEXT("重要提示"), MB_YESNOCANCEL)==IDYES)
	{
		permissioin_data.old_no = permission_list.GetItem(list_index,0);/*获取列表中选择的一行的第一个字段*/
		e_id.GetEditText(permissioin_data.no);
		e_name.GetEditText(permissioin_data.name);
	
		if (permissioin.UpdatePermission(&permissioin_data,error))
		{
			MessageBox(hwnd, TEXT("修改此权限信息成功！"), TEXT("成功"), MB_OK);
			e_id.SetEditText("");
			e_name.SetEditText("");
			ShowPermissionList(hwnd);
			return true;
		}
		else
		{
			MessageBox(hwnd, error.c_str(), TEXT("错误"), MB_OK);
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
		MessageBox(hwnd, TEXT("请在列表中选择一项"), TEXT("提示"), MB_OK);
		return false;
	}
	if (MessageBox(hwnd, TEXT("删除权限将会删除此权限和其所属的登录用户！\n\n       请再次确认是否删除？"),\
		TEXT("重要提示"), MB_YESNOCANCEL)==IDYES)
	{
		permissioin_data.no = permission_list.GetItem(list_index,0);/*获取列表中选择的一行的第一个字段*/
		permissioin_data.name = permission_list.GetItem(list_index,1);
		permissioin_data.old_no = permissioin_data.no;
		if (permissioin.DeletePermission(&permissioin_data,error))
		{
			MessageBox(hwnd, TEXT("删除此权限信息成功！"), TEXT("成功"), MB_OK);
			e_id.SetEditText("");
			e_name.SetEditText("");
			ShowPermissionList(hwnd);
			return true;
		}
		else
		{
			MessageBox(hwnd, error.c_str(), TEXT("错误"), MB_OK);
			ShowPermissionList(hwnd);
			return false;
		}
	}
	ShowPermissionList(hwnd);
	return false;
}
/*
 * @ brief: 获取编辑登录用户对话框数据
 * @ param: hwnd [in] 窗口句柄
 * @ param: user [out] 指向登录用户的结构体指针，在这里仅使用了
 *                     staff_no, login_permission, new_login_name, password1四个字段
 * @ param: err_info [out] 错误信息返回
 * @ return: 若成功返回true，否则返回false
 **/
bool GetLoginUserInfo(HWND hwnd, LoginUser *user, std::string &err_info) {
	CComboBox combo(hwnd, IDC_E_USER_ID);   // 初始化员工编号combo box
	std::string staff_no, permission_name;
	if (!combo.GetComboBoxText(staff_no)) {  // 获取员工编号
		err_info = "获取员工编号失败";
		return false;
	}
	user->staff_no = staff_no; 
	combo.Initialization(hwnd, IDC_E_USER_PERMISSION); // 初始化用户权限combo box
	if (!combo.GetComboBoxText(permission_name)) { // 获取用户权限
		err_info = "获取用户权限失败";
		return false;
	}
	user->login_permission = permission_name;
	CEdit edit(hwnd, IDC_E_LOGIN_NAME);  // 初始化用户名编辑框
	std::string login_name, password1, password2, p1, p2;
	if (!edit.GetEditText(login_name)) {  // 获取用户登录名
		err_info = "获取用户登录名失败";
		return false;
	}
	user->new_login_name = login_name;   // 存放在新登录名中，以备修改可共同使用
	edit.Initialization(hwnd, IDC_E_USER_PASSWD); // 获取用户密码
	if (!edit.GetEditText(password1)) {
		err_info = "获取用户密码失败";
		return false;
	}
	CLoginForm lo;
	p1 = lo.Encrypt(password1.c_str(), password1.length() / 2, password1.length());
	edit.Initialization(hwnd, IDC_E_CONFROM_PASSWD); // 获取用户确认密码
	if (!edit.GetEditText(password2)) {
		err_info = "获取用户确认密码失败";
		return false;
	}
	p2 = lo.Encrypt(password2.c_str(), password2.length() / 2, password2.length());
	if (p1 != p2) {
		err_info = "两次输入密码不一致";
		return false;
	}
	user->password1 = p1;
	return true;
}