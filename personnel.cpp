
#include "personnel.h"
#include "Commodity.h"

WNDPROC g_OldListProc;   /* The list view processes */

/*
 * 说明：人事部主窗口窗口处理函数
 */
BOOL CALLBACK PersonnelProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE hInstance = (HINSTANCE)lParam;
	switch (msg)
	{
	case WM_INITDIALOG:
		{
			std::string error;
 			CreateChildWindow(hwnd, error);
			InitListView(hwnd, ID_PERSONNEL_INFO);
			InitComboBox(hwnd, ID_PERSONNEL_DEPT_COMBO); /* Insert item to the combo box */
	    	OnStartQuery(hwnd);/*执行查询，显示查询结果*/
		}
		return TRUE;
	case WM_COMMAND:
		{
			bool is_check = false;
			switch (LOWORD(wParam))
			{
			case ID_PERSONNEL_NAME:
				{
					HWND name = GetDlgItem(hwnd, ID_PERSONNEL_STAFF_NAME);
					if (IsCheckName(hwnd))
					{
						EnableWindow(name, TRUE);
					}
					else
					{
						EnableWindow(name, FALSE);
					}
					break;
				}
			case ID_PERSONNEL_SEX:
				{
					HWND man = GetDlgItem(hwnd, ID_MAN);
					HWND woman = GetDlgItem(hwnd, ID_WOMAN);
					if (true == IsCheckSex(hwnd))
					{
						EnableWindow(man, TRUE);
						EnableWindow(woman, TRUE);
					}
					else
					{
						EnableWindow(man, FALSE);
						EnableWindow(woman, FALSE);
					}
					break;
				}
			case ID_PERSONNEL_DEPT:
				{
					HWND dept = GetDlgItem(hwnd, ID_PERSONNEL_DEPT_COMBO);
					if (true == IsCheckDept(hwnd))
					{
						EnableWindow(dept, TRUE); 
					}
					else
					{
						EnableWindow(dept, FALSE); 
					}
					break;
				}
			case ID_PERSONNEL_QUERY:
				{
					if (false == OnStartQuery(hwnd))
					{
						MessageBox(hwnd, TEXT("没有匹配的记录"), TEXT("查询结果"),
			           MB_ICONINFORMATION | MB_OK);
					}
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

/* 说明：显示员工信息的列表的窗口处理函数
 *
 */
LRESULT CALLBACK StaffListProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HMENU menu;
	HINSTANCE hinstance = (HINSTANCE)GetWindowLong(GetParent(hwnd), GWL_HINSTANCE);
	int select_row(0);
	switch (msg)
	{
	case WM_RBUTTONDOWN:
		{   /*弹出右键菜单*/
			menu = LoadMenu(hinstance, MAKEINTRESOURCE(IDR_PERSONNEL));
			menu = GetSubMenu(menu, 0);
			POINT point;
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			ClientToScreen(hwnd, &point);
			TrackPopupMenu(menu, TPM_RIGHTBUTTON,
				           point.x, point.y, 0, hwnd, NULL);
			break;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDR_ADD:
				{
					/*TODO:未检测返回值*/
					GetStaffToDialog(hinstance, hwnd, ADD_STAFF);					
					break;
				}
			case IDR_DELETE:
				{
// 					/*TODO:未检测返回值*/
					GetStaffToDialog(hinstance, hwnd, DELETE_STAFF);
 					break;
				}
			case IDR_MODIFY:
				{
					/*TODO:未检测返回值*/
					GetStaffToDialog(hinstance, hwnd, MODIFY_STAFF);
					break;
				}
			}
			return 0;
		}
	}
	return CallWindowProc(g_OldListProc, hwnd, msg, wParam, lParam);
}

/*
 *说明：编辑员工信息的对话框的窗口处理函数 
 **/
BOOL CALLBACK EditStaff(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static std::string user_old_id;
	switch (msg)
	{
	case WM_INITDIALOG:
		{
			RECT rect;
			if (!GetWindowRect(hwnd, &rect))
			{
				MessageBox(hwnd, TEXT("Get rect failed!"), TEXT("ERROR"), MB_ICONINFORMATION | MB_OK);
				return FALSE;
			}
			int width = rect.right - rect.left;
			int height = rect.bottom - rect.top;
			int screen_width = GetSystemMetrics(SM_CXFULLSCREEN);
			int screen_height = GetSystemMetrics(SM_CYFULLSCREEN);
			MoveWindow(hwnd, (screen_width - width) / 2,
				       (screen_height - height) / 2,
					   width, height, TRUE);
		     STAFFINFO *info = (STAFFINFO *)lParam;
			 user_old_id = info->old_id;
			/*根据从弹出对话框函数的附加消息判断用户在员工列表的右键菜单中选择了哪个选项*/
			switch(info->menu_id)
			{
			case ADD_STAFF:
				{
					SetAddFocus(hwnd);
				}
				break;
			case DELETE_STAFF:
				{
					SetDeleteFocus(hwnd, lParam);
				}
				break;
			case MODIFY_STAFF:
				{
					SetModifyFocus(hwnd, lParam);
				}
				break;
			default:
				MessageBox(hwnd, TEXT("菜单分类解析失败"), TEXT("错误"), MB_OK);
			}
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case ID_ADD_STAFF:
				{
					AddStaff(hwnd, user_old_id);
					break;
				}
			case ID_DELETE_STAFF:
				{
					if (true == DeleteStaff(hwnd, user_old_id))
					{
						EndDialog(hwnd, LOWORD(wParam));
					}
					break;
				}
			case ID_MOTIFY_STAFF:
				{
					if (true == ModifyStaff(hwnd, user_old_id))
					{
						EndDialog(hwnd, LOWORD(wParam));
					}
					break;
				}
			case ID_CANCEL_STAFF:
				{
					EndDialog(hwnd, LOWORD(wParam));
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
/* 
 * @ Description: Create the staffs list view in personnel main window.
 * @ Parameters:
 *		parent_hwnd [in] Specifies the list view's parent window.
 * @ Return Value:
		If it is success, the return value is true; otherwise, the return value is false.
 */
bool CreateStaffListView(HWND parent_hwnd)
{
	CListView staff_list;
	RECT window_rect, list_rect;
	GetWindowRect(parent_hwnd, &window_rect); /* Get the window rect */
	int width = window_rect.right - window_rect.left; /* Calculate the window width */
	int height = window_rect.bottom - window_rect.top; /* Calculate the window height */
	/* Set the staff list start point */
	list_rect.left = 20;
	list_rect.top = height / 4;
	/* Set the staff list width and height */
	list_rect.right = width - 40;
	list_rect.bottom = height / 4 * 3 - 40;
	DWORD style = LVS_REPORT | LVS_EDITLABELS; /* Set the list view's style */
	/* Set the new list view process */
//	staff_list.set_new_process(StaffListProc);
	bool is_ok = staff_list.Create(style, list_rect, parent_hwnd,
                                   ID_PERSONNEL_INFO);
	/* When the list view create successfully and
     * set the new list view process, save the old
     * list view process. 
	 */
	if (is_ok && staff_list.is_set_process())
	{
		g_OldListProc = staff_list.old_process();
	}
	return is_ok;
}

/* 
 * @ Description: Create the staffs list view in personnel main window.
 * @ Parameters:
 *		parent_hwnd [in] Specifies the list view's parent window.
 *      id [in] The list view's ID.
 * @ Return Value:
		If it is success, the return value is true; otherwise, the return value is false.
 */
bool InitListView(HWND parent_hwnd, UINT id)
{
	CListView staff_list;
	/* Initialization the list view */
	staff_list.Initialization(parent_hwnd, id);	
	staff_list.set_new_process(StaffListProc);
	g_OldListProc = staff_list.old_process();
	/* Set the full row selected and grid lines */
	staff_list.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	/* Insert the list view's column title */
	if (-1 != staff_list.InsertColumn(0, 80, "员工编号") &&
	    -1 != staff_list.InsertColumn(1, 100, "员工姓名") &&
		-1 != staff_list.InsertColumn(2, 45,  "性别") &&
		-1 != staff_list.InsertColumn(3, 45,  "年龄") &&
		-1 != staff_list.InsertColumn(4, 100, "员工工资") &&
		-1 != staff_list.InsertColumn(5, 80,  "员工部门") &&
		-1 != staff_list.InsertColumn(6, 100, "员工邮箱") &&
		-1 != staff_list.InsertColumn(7, 100, "员工电话") &&
		-1 != staff_list.InsertColumn(8, 100, "员工地址"))
	{
		return true;
	}
	return false;
}

/* 
 * @ Description: Set the list view's data.
 * @ Parameters:
 *		parent_hwnd [in] Specifies the list view's parent window.
 *      id [in] The list view's ID.
 */
void SetListViewData(HWND parent_hwnd, UINT id)
{
	CListView staff_list;
	/* Initialization the list view */
	staff_list.Initialization(parent_hwnd, id);
	CStaffForm staff_info;
	std::string error_information;
	/* Connect the database */
//	staff_info.Connect("repast", "repast", "repast", error_information);
	/* Get the record set */
	staff_info.GetRecordSet();
	/* Move to the first record */
	staff_info.MoveFirst();
	int i = 0;
	/* Get the record set data and insert into the list view */
	while (!staff_info.IsEOF())
	{
		/* Insert the item */
		staff_list.InsertItem(i, staff_info.id());
		/* Insert the subitem */
		staff_list.SetItem(i, 1, staff_info.name());
		staff_list.SetItem(i, 2, staff_info.sex());
		staff_list.SetItem(i, 3, staff_info.age());
		staff_list.SetItem(i, 4, staff_info.salary());
		staff_list.SetItem(i, 5, staff_info.dept_name());
		staff_list.SetItem(i, 6, staff_info.mailbox());
		staff_list.SetItem(i, 7, staff_info.phone_num());
		staff_list.SetItem(i, 8, staff_info.address());
		/* Move to the next record */	
		staff_info.MoveNext();
		i++;
	}
	/* Disconnect the link */
//	staff_info.Disconnect();
	/* The default selected line */
	staff_list.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
	int count = staff_list.GetItemCount();
	char number[10];
	sprintf(number, "%d 人", count);
	SetWindowText(GetDlgItem(parent_hwnd, ID_CURRENT_RECORD_SUM), number);
	staff_list.SetEditLabel(1);
}

/* 
 * @ Description: Create a group box.
 * @ Parameters:
 *		parent_hwnd [in] Specifies the list view's parent window.
 * @ Return Value:
 *		If it is success, the return value is true; otherwise, the return is false.
 */
bool CreateGroupBox(HWND parent_hwnd)
{
	CButton group;
	RECT group_rect;
	group_rect.left = 20;
	group_rect.top = 10;
	group_rect.right = 400;
	group_rect.bottom = 125;
	return group.Create("查询条件", BS_GROUPBOX,
		                group_rect, parent_hwnd, 0);
}

/* 
 * @ Description: Create child windows.
 * @ Parameters:
 *		parent_hwnd [in] Specifies the list view's parent window.
 *		error [out] Return the error information.
 * @ Return Value:
 *		If it is success, the return value is true; otherwise, the return is false.
 */
bool CreateChildWindow(HWND parent_hwnd, std::string &error)
{
	CEdit name_edit;
	name_edit.Initialization(parent_hwnd, ID_PERSONNEL_STAFF_NAME);
	/* By default, disable the name edit box */
	name_edit.EnableWindow(FALSE);
	/* Create sex check box and sex button */

	CButton man;
    man.Initialization(parent_hwnd, ID_MAN);
	/* By default, disable this child window and select it */
	man.EnableWindow(FALSE);
	man.SetChecked(TRUE);
	CButton woman;
	woman.Initialization(parent_hwnd, ID_WOMAN);
	/* By default, disable this child window */
	woman.EnableWindow(FALSE);
	/* Create the department check box and department combo box */
	CComboBox dept_combo;
    dept_combo.Initialization(parent_hwnd, ID_PERSONNEL_DEPT_COMBO);
	/* By default, disable the department combo box */
	dept_combo.EnableWindow(FALSE);
	/* Create the staff sum text and edit box which is read only */
	return true;
}


/* 
 * @ Description: Initialization the combo box.
 * @ Parameters:
 *		hwnd [in] Specifies the combo box's parent window.
 *		id [in] The combo box's ID.
 * @ Return Value:
 *		If it is success, the return value is true; otherwise, the return is false.
 */
bool InitComboBox(HWND hwnd, int id)
{
	HWND hwnd_combo;
    CDepartment cdept;
	hwnd_combo = GetDlgItem(hwnd, id);
	cdept.SetSQLStatement("select * from Dept");
	cdept.GetRecordSet();
	cdept.MoveFirst();
	while (!cdept.IsEOF())
	{
		if (CB_ERR == SendMessage(hwnd_combo, CB_ADDSTRING, 0, (LPARAM)cdept.name()))
		{
			return false;
		}
		cdept.MoveNext();
	}
	SendMessage(hwnd_combo, CB_SETCURSEL, 0, 0);
    return true;
}

/* 
 * @ Description: Judging whether the name is checked.
 * @ Parameters:
 *		hwnd [in] Specifies the name check box's parent window.
 * @ Return Value:
 *		If it is checked, the return value is true; otherwise, the return is false.
 */
bool IsCheckName(HWND parent_hwnd)
{
	HWND name = GetDlgItem(parent_hwnd, ID_PERSONNEL_NAME);
	long ret = SendMessage(name, BM_GETCHECK, 0, 0);
	if (BST_CHECKED == ret)
	{
		return true;
	}
	return false;
}

/* 
 * @ Description: Judging whether the sex is checked.
 * @ Parameters:
 *		hwnd [in] Specifies the sex check box's parent window.
 * @ Return Value:
 *		If it is checked, the return value is true; otherwise, the return is false.
 */
bool IsCheckSex(HWND parent_hwnd)
{
	HWND sex = GetDlgItem(parent_hwnd, ID_PERSONNEL_SEX);
	long ret = SendMessage(sex, BM_GETCHECK, 0, 0);
	if (BST_CHECKED == ret)
	{
		return true;
	}
	return false;
}
/* 
 * @ Description: Judging whether the department is checked.
 * @ Parameters:
 *		hwnd [in] Specifies the department check box's parent window.
 * @ Return Value:
 *		If it is checked, the return value is true; otherwise, the return is false.
 */
bool IsCheckDept(HWND parent_hwnd)
{
	HWND dept = GetDlgItem(parent_hwnd, ID_PERSONNEL_DEPT);
	long ret = SendMessage(dept, BM_GETCHECK, 0, 0);
	if (BST_CHECKED == ret)
	{
		return true;
	}
	return false;
}

/* 
 * @ Description: Get the staff's ID
 * @ Parameters:
 *		hwnd [in] Specifies the department check box's parent window.
 * @ Return Value:
 *		The return value is the staff's ID.
 */
std::string GetID(const HWND parent_hwnd)
{
	char id[10] = "\0";
	HWND id_hwnd;
	id_hwnd = GetDlgItem(parent_hwnd, ID_PERSONNEL_STAFF_ID);
	GetWindowText(id_hwnd, id, 10);
	return std::string(id);
}

/* 
 * @ Description: Get the staff's name.
 * @ Parameters:
 *		hwnd [in] Specifies the department check box's parent window.
 * @ Return Value:
 *		The return value is the staff's name.
 */
std::string GetName(const HWND parent_hwnd)
{
	char name[20] = "\0";
	HWND name_hwnd = GetDlgItem(parent_hwnd, ID_PERSONNEL_STAFF_NAME);
	GetWindowText(name_hwnd, name, 20);
	return std::string(name);
}

/* 
 * @ Description: Get the staff's sex
 * @ Parameters:
 *		hwnd [in] Specifies the department check box's parent window.
 * @ Return Value:
 *		The return value is the staff's sex.
 */
std::string GetSex(const HWND parent_hwnd)
{
	std::string sex;
	HWND man, woman;
	man = GetDlgItem(parent_hwnd, ID_MAN);
	woman = GetDlgItem(parent_hwnd, ID_WOMAN);
	if (BST_CHECKED == SendMessage(man, BM_GETCHECK, 0, 0))
	{
		sex = "男";
	}
	if (BST_CHECKED == SendMessage(woman, BM_GETCHECK, 0, 0))
	{
		sex = "女";
	}
	return sex;
}

/* 
 * @ Description: Get the staff's department name.
 * @ Parameters:
 *		hwnd [in] Specifies the department check box's parent window.
 * @ Return Value:
 *		The return value is the staff's department name.
 */
std::string GetDept(const HWND parent_hwnd)
{
	char dept[41] = "\0";
	HWND dept_hwnd;
	dept_hwnd = GetDlgItem(parent_hwnd, ID_PERSONNEL_DEPT_COMBO);
	int index = SendMessage(dept_hwnd, CB_GETCURSEL, 0, 0);
	SendMessage(dept_hwnd, CB_GETLBTEXT, index, (LPARAM)&dept);
	std::string dept_name(dept);
	int length = dept_name.length();
	std::string sub_string = dept_name.substr(0, length);
	return sub_string;
}


/* 
 * @ Description: Get the sql query statement .
 * @ Parameters:
 *		hwnd [in] Specifies the department check box's parent window.
 * @ Return Value:
 *		Return the sql statement.
 */
std::string GetQueryStatement(const HWND parent_hwnd)
{
	char sql_query[256] = "\0";
	std::string id = GetID(parent_hwnd);   /* Get the staff's id from id's edit box */
	/*注意：下句双引号内不可换行*/
	sprintf(sql_query, "select Sno,Sname,Ssex,Sage,Ssalary,Dname,Smailbox,Sphoneno,Saddress from Staff,Dept where Sno like '%c%s%c'",
		    '%', id.c_str(), '%');
	std::string sql_statement(sql_query);
	if (IsCheckName(parent_hwnd))
	{
		std::string name = GetName(parent_hwnd); /* Get the staff's name */
		sprintf(sql_query, " and Sname like '%c%s%c'", 
			    '%', name.c_str(), '%');
		std::string temp(sql_query);
		sql_statement += temp;  /* Add it into the sql_statement */
	}
	if (IsCheckSex(parent_hwnd))
	{
		std::string sex = GetSex(parent_hwnd); /* Get the staff's sex */
		sprintf(sql_query, " and Ssex='%s'", sex.c_str());
		std::string temp(sql_query);
		sql_statement += temp; /* Add it into the sql_statement */
	}
	if (IsCheckDept(parent_hwnd))
	{
		std::string dept = GetDept(parent_hwnd);
		sprintf(sql_query, " and Dname like '%c%s'", '%', dept.c_str());
		std::string temp(sql_query);
		sql_statement += temp;
	}
	sql_statement += " and Sdeptno=Dno";
	return sql_statement;
}

/* 
 * @ Description: Execute the query statement.
 * @ Parameters:
 *		hwnd [in] Specifies the department check box's parent window.
 *		sql_query [in] The address of a sql statement.
 *		error [out] if failed, this is filed can give some error information.
 * @ Return Value:
 *		If there has some record, the return value is true; otherwise, the 
 *		return value is false.
 */
bool ExecQuery(const HWND hwnd, UINT id, const char *sql_query, std::string &error)
{
	CStaffForm staff;
	staff.Connect("repast", "repast", "repast", error);
	if (!staff.ExecuteSQL(sql_query, error))
	{
	//	MessageBox(hwnd,error.c_str(),"error",MB_ICONINFORMATION|MB_OK);
		return false;
	}
	staff.BindingParameter();  /* In this function, there no error judge. */
	/* Move to the first of the record set */
	staff.MoveFirst();  
	/*TODO:此处判断无匹配的结果有问题*/
	if (0 == strcmp("",staff.id()))
	{
		CListView staff_list;
		/* Initialization the list view object */
		HWND list_hwnd = GetDlgItem(hwnd, id);
		staff_list.Initialization(hwnd, ID_PERSONNEL_INFO);
		/* Clean the list view */
		staff_list.DeleteAllItems();
		error = "无匹配结果！";
		return false;
	}
	else
	{
		CListView staff_list;
		/* Initialization the list view object */
		HWND list_hwnd = GetDlgItem(hwnd, id);
		staff_list.Initialization(hwnd, ID_PERSONNEL_INFO);
		/* Clean the list view */
		staff_list.DeleteAllItems();
		int item = 0;
		while (!staff.IsEOF())
		{
			/* Insert item(s) into the list view */
			staff_list.InsertItem(item, staff.id());
			staff_list.SetItem(item, 1, staff.name());
			staff_list.SetItem(item, 2, staff.sex());
			staff_list.SetItem(item, 3, staff.age());
			staff_list.SetItem(item, 4, staff.salary());
			staff_list.SetItem(item, 5, staff.dept_name());
			staff_list.SetItem(item, 6, staff.mailbox());
			staff_list.SetItem(item, 7, staff.phone_num());
			staff_list.SetItem(item, 8, staff.address());
			staff.MoveNext();
			item++;
		}
	}
	/* Disconnect from database */
	staff.Disconnect();
	return true;
}

/* 
 * @ Description: Start execute.
 * @ Parameters:
 *		hwnd [in] Specifies the check box's parent window.
 * @ Return Value:
 *		If succeed, the return value is true; otherwise, the return
 *		value is false.
 */
bool OnStartQuery(const HWND hwnd)
{
	bool ret_statu = true;
	std::string sql_statement = GetQueryStatement(hwnd);
	std::string error;
	if (!ExecQuery(hwnd, ID_PERSONNEL_INFO, sql_statement.c_str(), error))
	{
		/*已把提示“查询结果：无匹配结果”放到回调函数“开始查询下”*/
// 		MessageBox(hwnd, error.c_str(), TEXT("查询结果"),
// 			       MB_ICONINFORMATION | MB_OK);
		ret_statu = false;
	}
	CStaffForm cstaff;
	cstaff.Connect("repast", "repast", "repast", error);
	char staff_sum[15]={0};
	sprintf(staff_sum, "%d 人", cstaff.GetStaffSum());
	SetWindowText(GetDlgItem(hwnd, ID_PERSONNEL_STAFF_SUM), staff_sum);/*显示员工总数*/
	cstaff.Disconnect();

	CDepartment cdept;
	cdept.Connect("repast", "repast", "repast", error);
	char dept_sum[15]={0};
	sprintf(dept_sum,"%d 个",cdept.GetDeptSum());
	SetWindowText(GetDlgItem(hwnd, ID_PERSONNEL_DEPT_SUM), dept_sum);/*显示部门总数*/
	cdept.Disconnect();

	CListView list;
	list.Initialization(hwnd, ID_PERSONNEL_INFO);
	int count = list.GetItemCount();
	char number[10];
	sprintf(number, "%d 人", count);
	SetWindowText(GetDlgItem(hwnd, ID_CURRENT_RECORD_SUM), number);/*显示当前列表中员工数量*/
	return ret_statu;
}



/*
 * 说明：
 *       从主窗口员工信息的列表中获取员工信息
 *       传递到编辑员工信息的对话框中
 * 参数： 
 *       hinstance [in] 主窗口实例句柄
 *       hwnd [in] 主窗口句柄
 *	     m_id [in] 列表中右键菜单选项的编号
 * 返回值：
 *         成功返回ture
 */
bool GetStaffToDialog(const HINSTANCE hinstance, const HWND hwnd, const UINT m_id)
{
	int select_row(0);
	CListView list;
	STAFFINFO staff_info;
	list.Initialization(GetParent(hwnd), ID_PERSONNEL_INFO);
	select_row = list.GetSelectionMark();
	staff_info.menu_id= m_id;
	staff_info.id = list.GetItem(select_row, 0);
    staff_info.old_id = staff_info.id; /*保存员工原来的id,在修改员工信息时使用*/
	staff_info.name = list.GetItem(select_row, 1);
	staff_info.sex = list.GetItem(select_row, 2);
	staff_info.age = list.GetItem(select_row, 3);
	staff_info.salary = list.GetItem(select_row, 4);
	staff_info.department = list.GetItem(select_row, 5);
	staff_info.email_address = list.GetItem(select_row, 6);
	staff_info.phone = list.GetItem(select_row, 7);
	staff_info.address = list.GetItem(select_row, 8);
	DialogBoxParam(hinstance, MAKEINTRESOURCE(IDD_STAFF_EDIT), hwnd,
		(DLGPROC)EditStaff, (long)&staff_info);
	OnStartQuery(GetParent(hwnd));
	return true;
}

/*
 * 说明：
 *       设置“添加”按钮有效，隐藏其他按钮
 * 参数： 
 *       hwnd [in] 对话框句柄
 * 返回值：
 *         成功返回ture
 */
bool SetAddFocus(const HWND hwnd)
{
	/*根据功能隐藏其他功能按钮*/
	ShowWindow(GetDlgItem(hwnd, ID_DELETE_STAFF), SW_HIDE);
	ShowWindow(GetDlgItem(hwnd, ID_MOTIFY_STAFF), SW_HIDE);
	SendMessage(GetDlgItem(hwnd, IDC_SEX_MAN), BM_SETCHECK, BST_CHECKED, 0);/*默认选中男性*/
	InitComboBox(hwnd, IDC_STAFF_DEPT);/*初始化员工部门的下拉框*/
	return true;
}

/*
 * 说明：
 *       设置“删除”按钮有效，隐藏其他按钮
 * 参数： 
 *       hwnd [in] 对话框句柄
 *       lParam [in] 对话框消息的额外参数，其实是传递的员工信息
 * 返回值：
 *         成功返回ture
 */
bool SetDeleteFocus(const HWND hwnd, LPARAM lParam)
{
	ShowWindow(GetDlgItem(hwnd, ID_DELETE_STAFF), SW_NORMAL);
	/*禁用修改员工信息的按钮和编辑框*/
	EnableWindow(GetDlgItem(hwnd, IDC_STAFF_ID), FALSE);
	EnableWindow(GetDlgItem(hwnd, IDC_STAFF_NAME), FALSE);
	EnableWindow(GetDlgItem(hwnd, IDC_SEX_MAN), FALSE);
	EnableWindow(GetDlgItem(hwnd, IDC_SEX_WOMAN), FALSE);
	EnableWindow(GetDlgItem(hwnd, IDC_STAFF_AGE), FALSE);
	EnableWindow(GetDlgItem(hwnd, IDC_STAFF_SALARY), FALSE);
	EnableWindow(GetDlgItem(hwnd, IDC_STAFF_DEPT), FALSE);
	EnableWindow(GetDlgItem(hwnd, IDC_STAFF_EMAIL), FALSE);
	EnableWindow(GetDlgItem(hwnd, IDC_STAFF_PHONE), FALSE);
	EnableWindow(GetDlgItem(hwnd, IDC_STAFF_ADDRESS), FALSE);
	/*根据功能禁用其他功能按钮*/
	ShowWindow(GetDlgItem(hwnd, ID_ADD_STAFF), SW_HIDE);
	ShowWindow(GetDlgItem(hwnd, ID_MOTIFY_STAFF), SW_HIDE);
	ShowStaffDlg(hwnd, lParam);
	return true;
}

/*
 * 说明：
 *       设置“修改”按钮有效，隐藏其他按钮
 * 参数： 
 *       hwnd [in] 对话框句柄
 *       lParam [in] 对话框消息的额外参数，其实是传递的指向员工信息的指针
 * 返回值：
 *         成功返回ture
 */
bool SetModifyFocus(const HWND hwnd, LPARAM lParam)
{
	ShowWindow(GetDlgItem(hwnd, ID_MOTIFY_STAFF), SW_NORMAL);
	/*根据功能禁用其他功能按钮*/
	ShowWindow(GetDlgItem(hwnd, ID_ADD_STAFF), SW_HIDE);
	ShowWindow(GetDlgItem(hwnd, ID_DELETE_STAFF), SW_HIDE);
	ShowStaffDlg(hwnd, lParam);
	return true;
}

/*
 * 说明：
 *      添加员工信息
 * 参数： 
 *       hwnd [in] 对话框句柄
 * 返回值：
 *         成功返回ture, 否则返回false
 */
bool AddStaff(const HWND hwnd, std::string user_old_id)
{
	std::string error;
	STAFFINFO staff_info;
	GetStaffDlg(hwnd, &staff_info);/*获取对话框中的员工信息*/
	staff_info.old_id = user_old_id;
	CStaffForm staff_form;
	/*TODO:尚未检测编号是否重复*/
	if(false == staff_form.InsertInfo(&staff_info, error))
	{
		MessageBox(hwnd, error.c_str(), TEXT("添加员工数据失败"), MB_OK);
			staff_form.Disconnect();
		return false;
	}
	else
	{
		MessageBox(hwnd, TEXT("员工数据添加成功"), TEXT("成功"), MB_OK);
	}
	return true;
}

/*
 * 说明：
 *      删除员工信息
 * 参数： 
 *       hwnd [in] 对话框句柄
 * 返回值：
 *         成功返回ture, 否则返回false
 */
bool DeleteStaff(const HWND hwnd, std::string user_old_id)
{
	std::string error_info;
	STAFFINFO staff_info;
    GetStaffDlg(hwnd, &staff_info);/*获取对话框中的员工信息*/
	staff_info.old_id = user_old_id;
	CStaffForm staff_form;
	if (true == staff_form.DeleteInfo(staff_info.id.c_str(), error_info))
	{
		MessageBox(hwnd, TEXT("删除员工数据成功"), TEXT("成功"), MB_OK);
		return true;
	}
	else
	{
		MessageBox(hwnd, TEXT("删除员工数据失败, 请关掉对话框或稍后重试！"), TEXT("失败"), MB_OK);
		return false;
	}
}

/*
 * 说明：
 *      修改员工信息
 * 参数： 
 *       hwnd [in] 对话框句柄
 * 返回值：
 *         成功返回ture, 否则返回false
 */
bool ModifyStaff(const HWND hwnd, std::string user_old_id)
{
	std::string error;
	STAFFINFO staff_info;
	GetStaffDlg(hwnd, &staff_info);/*获取对话框中的员工信息*/
	staff_info.old_id = user_old_id;
	CStaffForm staff_form;
	/*TODO:尚未检测编号是否重复，无法更改主键 *///////////////////////
	if(false == staff_form.UpdateInfo(&staff_info, error))
	{
		MessageBox(hwnd, error.c_str(), TEXT("修改员工数据失败"), MB_OK);
		return false;
	}
	else
	{
		MessageBox(hwnd, TEXT("员工数据修改成功"), TEXT("成功"), MB_OK);
	}
	return true;
}


/*
 * 说明：
 *      在编辑员工信息对话框中显示员工信息
 * 参数： 
 *       hwnd [in] 对话框句柄，
 *       lParam [in] 对话框消息的额外参数，其实是传递的指向员工信息的指针
 * 返回值：
 *         成功返回ture, 否则返回false
 */
bool ShowStaffDlg(const HWND hwnd, LPARAM lParam)
{
	/* Get the staff's information */
	STAFFINFO *info = (STAFFINFO *)lParam;
	SetDlgItemText(hwnd, IDC_STAFF_ID, info->id.c_str());
	SetDlgItemText(hwnd, IDC_STAFF_NAME, info->name.c_str());
	if ("男"==info->sex)
	{
		SendMessage(GetDlgItem(hwnd, IDC_SEX_MAN), BM_SETCHECK, BST_CHECKED, 0);
	}
	else
	{
		SendMessage(GetDlgItem(hwnd, IDC_SEX_WOMAN), BM_SETCHECK, BST_CHECKED, 0);
	}
	InitComboBox(hwnd, IDC_STAFF_DEPT);/*初始化员工部门的下拉框*/
	int ret=SendMessage(GetDlgItem(hwnd, IDC_STAFF_DEPT), CB_FINDSTRING, 0, (long)info->department.c_str());
	SendMessage(GetDlgItem(hwnd, IDC_STAFF_DEPT), CB_SETCURSEL, ret, 0);
	SetDlgItemText(hwnd, IDC_STAFF_AGE, info->age.c_str());
	SetDlgItemText(hwnd, IDC_STAFF_SALARY, info->salary.c_str());
	SetDlgItemText(hwnd, IDC_STAFF_EMAIL, info->email_address.c_str());
	SetDlgItemText(hwnd, IDC_STAFF_PHONE, info->phone.c_str());
	SetDlgItemText(hwnd, IDC_STAFF_ADDRESS, info->address.c_str());
	return true;

}

/*
 * 说明：
 *      从编辑员工信息对话框中获取员工信息
 * 参数： 
 *       hwnd [in] 对话框句柄，
 *       info [in] 指向员工信息结构体的指针
 * 返回值：
 *         成功返回ture, 否则返回false
 */
bool GetStaffDlg(const HWND hwnd, STAFFINFO * info)
{
	CEdit staff_edit;
	CButton staff_button;
	CComboBox staff_conbobox;
	bool is_checked;
	info->menu_id=1023;
	staff_edit.Initialization(hwnd,IDC_STAFF_ID);
	staff_edit.GetEditText(info->id);
	staff_edit.Initialization(hwnd, IDC_STAFF_NAME);
	staff_edit.GetEditText(info->name);
    staff_button.Initialization(hwnd, IDC_SEX_MAN);
	is_checked = staff_button.IsChecked();
    if (true == is_checked)
    {
		info->sex="男";
    }
	else
	{
		info->sex="女";
	}
	staff_edit.Initialization(hwnd, IDC_STAFF_AGE);
	staff_edit.GetEditText(info->age);
	staff_edit.Initialization(hwnd, IDC_STAFF_SALARY);
	staff_edit.GetEditText(info->salary);
	staff_conbobox.Initialization(hwnd, IDC_STAFF_DEPT);
	staff_conbobox.GetComboBoxText(info->department);
	staff_edit.Initialization(hwnd, IDC_STAFF_EMAIL);
	staff_edit.GetEditText(info->email_address);
	staff_edit.Initialization(hwnd, IDC_STAFF_PHONE);
	staff_edit.GetEditText(info->phone);
	staff_edit.Initialization(hwnd, IDC_STAFF_ADDRESS);
	staff_edit.GetEditText(info->address);
	return true;
}
