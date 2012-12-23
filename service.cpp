/*
 * 文件: service.cpp
 * 说明: 该文件是服务管理登录文件，对服务管理的操作在该文件中完成。
 **/


#include "service.h"


WNDPROC g_old_list_processes;

LRESULT CALLBACK ServiceProcesses(HWND hwnd, UINT message,
                                  WPARAM wParam, LPARAM lParam)
{
    static HINSTANCE hinstance;
    switch (message)
    {
    case WM_CREATE:
        {
            hinstance = ((LPCREATESTRUCT)lParam)->hInstance;
			CreateGroupBox(hwnd);   /* Create the table information group box */
			CreateTableListView(hwnd); /* Create the table information list view */
			InitListView(hwnd, ID_SERVICE_LIST); /* Insert the list view's title */
			CreateComboBox(hwnd);
			InitComboBox(hwnd, ID_SERVICE_COMBO);
			CreateButton(hwnd);
            return 0;
        }
    case WM_SETFOCUS:
        {
            SetFocus(GetDlgItem(hwnd, ID_SERVICE_LIST));
            return 0;
        }
    case WM_LBUTTONDOWN:
        {
            return 0;
        }
    case WM_COMMAND:
        {
			switch (LOWORD(wParam))
			{
			case ID_SERVICE_COMBO:
				{
					if (HIWORD(wParam) == CBN_SELCHANGE)
					{
						/* 
						 * HIT: When you change the combo box item, if you want 
						 *      make some change, you can add it at here. 
						 */
						CComboBox combo;
						combo.Initialization(hwnd, ID_SERVICE_COMBO);
						std::string text;
						combo.GetComboBoxText(text);
						if ("大厅一楼" == text)
						{
							MessageBox(hwnd, TEXT("大厅一楼"), TEXT("combo"), MB_ICONINFORMATION);
						}
						if ("大厅二楼" == text)
						{
							MessageBox(hwnd, TEXT("大厅二楼"), TEXT("combo"), MB_ICONINFORMATION);
						}
						if ("大厅三楼" == text)
						{
							MessageBox(hwnd, TEXT("大厅三楼"), TEXT("combo"), MB_ICONINFORMATION);
						}	
					}
					break;
				}
			case ID_SERVICE_START:
				{
					SYSTEMTIME current_time;
					char time_str[512] = "\0";
					GetLocalTime(&current_time);   /* User can change the system time. */
					sprintf(time_str, "%d-%d-%d %d:%d", current_time.wYear, current_time.wMonth, 
						    current_time.wDay, current_time.wHour, current_time.wMinute);
					MessageBox(hwnd, time_str, TEXT("Current Time"), MB_ICONINFORMATION);
					break;
				}
			case ID_SERVICE_ORDER:
				{
					DialogBox(hinstance, MAKEINTRESOURCE(IDD_ORDER),
						           hwnd, (DLGPROC)OrderProc);
					break;
				}
			case ID_SERVICE_RETREAT:
				{
					DialogBox(hinstance, MAKEINTRESOURCE(IDD_RETREAT),
						      hwnd, (DLGPROC)RetreatProc);
					break;
				}
			case ID_SERVICE_CHECKOUT:
				{
					DialogBox(hinstance, MAKEINTRESOURCE(IDD_CUSTOM_CHECKOUT),
						      hwnd, (DLGPROC)CheckOutProc);
					break;
				}
			case ID_SERVICE_CHANGE:
				{
					DialogBox(hinstance, MAKEINTRESOURCE(IDD_CHANGE_TABLE),
						      hwnd, (DLGPROC)ChangeProc);
					break;
				}
			}
            return 0;
        }
    case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

/*
 * 说明: list view处理函数。
 *       该函数不能处理所有的消息(如WM_CREATE消息)，只能处理
 *       部分的消息。
 **/
LRESULT CALLBACK ListProcesses(HWND hwnd, UINT message,
                               WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_LBUTTONDBLCLK:
        {
//             CMyListView list_view;
//             list_view.set_hwnd(hwnd);
//             int index = list_view.GetCurSel();
//             char str[20];
//             sprintf(str, "You choiced %d", index);
//             MessageBox(hwnd, str, TEXT("list"), MB_ICONINFORMATION | MB_OK);
            break;
        }
    }
    return CallWindowProc(g_old_list_processes, hwnd, message, wParam, lParam);
}

/*
 * 说明: 创建list view窗口
 * 参数:
 *       hinstance [in] 程序实例句柄
 *       hwnd [in] 窗口句柄
 *       list_view [out] CMyListView对象，保存创建好的listview的参数
 * 返回值: 若成功返回ture,否则返回false。
 **/
bool CreateTableListView(const HWND hwnd)
{
    RECT table_rect;
	CListView list_view;
    GetWindowRect(hwnd, &table_rect);
    int width = table_rect.right - table_rect.left;
    int height = table_rect.bottom - table_rect.top;
	/* Set the table list start point */
	table_rect.left = 40;
	table_rect.top = 90;
	/* Set the staff list width and height */
	table_rect.right = 450;
	table_rect.bottom = height / 6 * 4;
	/* Set the list view's style */
	DWORD style = LVS_REPORT;
    bool is_ok = list_view.Create(style, table_rect, hwnd, ID_SERVICE_LIST);
    return is_ok;
}

/* 
 * @ Description: Initialization the list view.
 * @ Parameters:
 *		hwnd [in] Specifies the group box's parent window.
 *		id [in] the list view's ID.
 * @ Return Value:
 *		If it is success, the return value is true; otherwise, the return
 *		value is false.
 */
bool InitListView(const HWND hwnd, UINT id)
{
	CListView table_list;
	/* Initialization the list view */
	table_list.Initialization(hwnd, id);
	/* Set the full row selected and grid lines */
	table_list.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	if (-1 != table_list.InsertColumn(0, 150, "台号") &&
		-1 != table_list.InsertColumn(1, 150, "状态") &&
		-1 != table_list.InsertColumn(2, 150, "开台时间"))
	{
		return true;
	}
	return false;
}

/* 
 * @ Description: Initialization the group box.
 * @ Parameters:
 *		hwnd [in] Specifies the group box's parent window.
 * @ Return Value:
 *		If it is success, the return value is true; otherwise, the return
 *		value is false.
 */
bool CreateGroupBox(const HWND hwnd)
{
	CButton group;
	RECT group_rect;
	group_rect.left = 20;
	group_rect.top = 20;
	group_rect.right = 500;
	group_rect.bottom = 500;
	return group.Create("台号信息", BS_GROUPBOX, group_rect, hwnd, 0);
}

/* 
 * @ Description: Create the combo box.
 * @ Parameters:
 *		hwnd [in] Specifies the combo box's parent window.
 * @ Return Value:
 *		If it is success, the return value is true; otherwise, the return
 *		value is false.
 */
bool CreateComboBox(const HWND hwnd)
{
	CComboBox combo;
	RECT combo_rect;
	combo_rect.left = 40;
	combo_rect.top = 50;
	combo_rect.right = 120;
	combo_rect.bottom = 100;
	return combo.Create(ES_CENTER | CBS_DROPDOWNLIST | CBS_HASSTRINGS,
		                combo_rect, hwnd, ID_SERVICE_COMBO);
}

/* 
 * @ Description: Initialization the combo box.
 * @ Parameters:
 *		hwnd [in] Specifies the combo box's parent window.
 *		id [in] the combo box's ID.
 * @ Return Value:
 *		If it is success, the return value is true; otherwise, the return
 *		value is false.
 */
bool InitComboBox(const HWND hwnd, int id)
{
	HWND combo;
	combo = GetDlgItem(hwnd, id);
	if (CB_ERR == SendMessage(combo, CB_ADDSTRING, 0, (LPARAM)"大厅一楼") ||
		CB_ERR == SendMessage(combo, CB_ADDSTRING, 0, (LPARAM)"大厅二楼") ||
		CB_ERR == SendMessage(combo, CB_ADDSTRING, 0, (LPARAM)"大厅三楼"))
	{
		return false;
	}
	/* Set the first item into edit box of the combo box */
	SendMessage(combo, CB_SETCURSEL, 0, 0);
	return true;
}

bool CreateButton(const HWND hwnd)
{
	CButton button;
	RECT rect;
	rect.left = 600;
	rect.top = 20;
	rect.right = 140;
	rect.bottom = 280;
	if (!button.Create("前台操作", BS_GROUPBOX, rect, hwnd, 0))
	{
		return false;
	}
	rect.top = 340;
	rect.bottom = 80;
	if (!button.Create("账号管理", BS_GROUPBOX, rect, hwnd, 0))
	{
		return false;
	}
	rect.left += 30;
	rect.top = 50;
	rect.right = 80;
	rect.bottom = 30;
 	if (!button.Create("开  台", ES_CENTER | BS_PUSHBUTTON | WS_TABSTOP,
		               rect, hwnd, ID_SERVICE_START))
	{
		return false;
	}
	rect.top += 50;
	if (!button.Create("换  台", ES_CENTER | BS_PUSHBUTTON,
		               rect, hwnd, ID_SERVICE_CHANGE))
	{
		return false;
	}
	rect.top += 50;
	if (!button.Create("下  单", ES_CENTER | BS_PUSHBUTTON,
		               rect, hwnd, ID_SERVICE_ORDER))
	{
		return false;
	}
	rect.top += 50;
	if (!button.Create("退  单", ES_CENTER | BS_PUSHBUTTON,
		               rect, hwnd, ID_SERVICE_RETREAT))
	{
		return false;
	}
	rect.top += 50;
	if (!button.Create("结  账", ES_CENTER | BS_PUSHBUTTON,
		               rect, hwnd, ID_SERVICE_CHECKOUT))
	{
		return false;
	}
	rect.top = 370;
	if (!button.Create("修改密码", ES_CENTER | BS_PUSHBUTTON,
		     		   rect, hwnd, ID_SERVICE_CHANGE_PASSWD))
	{
		return false;
	}
	return true;
}

BOOL CALLBACK OrderProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
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
			CListView menu_list, custom_list;
			menu_list.Initialization(hwnd, IDC_REPAST_MENU);
			menu_list.InsertColumn(0, 100, "菜名");
			menu_list.InsertColumn(1, 100, "价格");
			menu_list.SetSelectAndGrid(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
			custom_list.Initialization(hwnd, IDC_CUSTOM_MENU);
			custom_list.InsertColumn(0, 100, "菜名");
			custom_list.InsertColumn(1, 100, "价格");
			custom_list.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_CANCEL_MENU:
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

BOOL CALLBACK CheckOutProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
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
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_CANCEL_CHECKOUT:
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


BOOL CALLBACK RetreatProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
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
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_TABLE_RETREAT_NUM:
				{
					if (LOWORD(wParam) == VK_RETURN)
					MessageBox(hwnd, TEXT("hello"), TEXT("Edit"), 0);
					break;
				}
			case ID_CANCEL_RETREAT:
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

BOOL CALLBACK ChangeProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
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
			/*HWND table_list = GetDlgItem(hwnd, IDC_TABLE_AVAILABLE);*/
			CListView table;
			table.Initialization(hwnd, IDC_TABLE_AVAILABLE);
			table.InsertColumn(0, 100, "可用台号");
			table.SetSelectAndGrid(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
			CComboBox postion;
			postion.Initialization(hwnd, IDC_FLOOR_NUM_AVAILABLE);
			postion.AddString("大厅一楼");
			postion.InsertString(1, "大厅二楼");
			postion.InsertString(2, "大厅三楼");
			postion.SetCurSel(0);
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_CANCLE_CHANGE:
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