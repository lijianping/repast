/*
 * 文件: service.cpp
 * 说明: 该文件是服务管理登录文件，对服务管理的操作在该文件中完成。
 **/


#include "service.h"
#include "TableInfo.h"
#include "Customer.h"
#include "MenuForm.h"
#include "CustomerMenuForm.h"
#include "LoginForm.h"
#include "Edit.h"
#include <MATH.H>
#include <TIME.H>

WNDPROC g_old_list_processes; /* 主对话框中的列表处理过程 */
WNDPROC g_dialog_menu_proc;  /* 对话框中的菜单列表的窗口处理过程 */
WNDPROC g_checkout_edit_proc;
extern std::string g_login_name;

char* status[3] = {"未开台", "已开台", "已预订"};

BOOL CALLBACK ServiceProcesses(HWND hwnd, UINT message,
                                  WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE hinstance = (HINSTANCE)lParam;
	switch (message)
	{
	case WM_INITDIALOG:
		{
			InitListView(hwnd, ID_SERVICE_LIST); /* Insert the list view's title */
			InitComboBox(hwnd, ID_SERVICE_COMBO);
			std::string error_info;
			SetListInfo(hwnd, ID_SERVICE_LIST, "01", error_info);
			return TRUE;
		}
    case WM_SETFOCUS:
        {
            SetFocus(GetDlgItem(hwnd, ID_SERVICE_LIST));
            return TRUE;
        }
    case WM_COMMAND:
        {
			switch (LOWORD(wParam))
			{
			case ID_SERVICE_REFRESH:
				{
					std::string error;
					CComboBox combox(hwnd, ID_SERVICE_COMBO);
					std::string text;
					combox.GetComboBoxText(text);
					if (!SetListInfo(hwnd, ID_SERVICE_LIST, GetFloor(text).c_str(), error))
					{
						MessageBox(hwnd, error.c_str(), TEXT("服务管理"), MB_ICONINFORMATION);
						break;
					}
					break;
				}
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
						std::string err;
						SetListInfo(hwnd, ID_SERVICE_LIST, GetFloor(text).c_str(), err);
					}
					break;
				}
			case ID_SERVICE_START:   // 开台管理
				{
					std::string error_information;  /* 错误信息返回 */
					CListView table_list;	
					CustomerTable table_info;
// 					table_info.no = table_list.GetItem(select_row, 0);   /* 获取台号 */
// 					std::string num = table_list.GetItem(select_row, 2);     /* 获取可容纳人数 */
// 					table_info.payable_num = atoi(num.c_str());   /* 备注: 不是很安全 */
					DialogBoxParam(hinstance, MAKEINTRESOURCE(IDD_START_TABLE),
						           hwnd, (DLGPROC)StartTableProc, (long)&table_info);
					SetListInfo(hwnd, ID_SERVICE_LIST, "01", error_information);
					break;
				}
			case ID_SERVICE_CHANGE:  // 换台管理
			{
				CListView table_list;
				table_list.Initialization(hwnd, ID_SERVICE_LIST);
				int select_row = table_list.GetSelectionMark();
				if (-1 == select_row)
				{
					MessageBox(hwnd, TEXT("请先选择台号！"), TEXT("服务管理"), MB_ICONINFORMATION);
					break;
				}
				std::string current_status = table_list.GetItem(select_row, 1);
				if (std::string(status[0]) == current_status)
				{
					MessageBox(hwnd, TEXT("该台尚未开台或预订， 不可进行换台！"), 
							   TEXT("服务管理"), MB_ICONINFORMATION);
					break;
				}
				CustomerTable table_info;
				table_info.table_no = table_list.GetItem(select_row, 0);              /* 获取台号 */
				table_info.customer_no = table_list.GetItem(select_row, 2);     /* 获取顾客编号 */
				table_info.founding_time = table_list.GetItem(select_row, 3);   /* 获取开台时间 */
				DialogBoxParam(hinstance, MAKEINTRESOURCE(IDD_CHANGE_TABLE),
							   hwnd, (DLGPROC)ChangeProc, (long)&table_info);
				break;
			}
			case ID_SERVICE_ORDER: // 点菜管理  
				{
					CListView table_list;    /* 台号信息列表 */
					table_list.Initialization(hwnd, ID_SERVICE_LIST);
					int select_row = table_list.GetSelectionMark();
					if (-1 == select_row)
					{
						MessageBox(hwnd, TEXT("请先选择台号！"), TEXT("服务管理"), MB_ICONINFORMATION);
						break;
					}
					std::string current_status = table_list.GetItem(select_row, 1);
					if (std::string(status[0]) == current_status)
					{
						MessageBox(hwnd, TEXT("该台尚未开台！"), TEXT("服务管理"), MB_ICONINFORMATION);
						break;
					}
					CustomerTable table_info;  /* 台号信息 */
					table_info.table_no = table_list.GetItem(select_row, 0);
					table_info.table_state = table_list.GetItem(select_row, 1);
					table_info.customer_no = table_list.GetItem(select_row, 2);
				//	table_info.founding_time = table_list.GetItem(select_row, 2);
					DialogBoxParam(hinstance, MAKEINTRESOURCE(IDD_ORDER),
						           hwnd, (DLGPROC)OrderProc, (long)&table_info);
					break;
				}
			case ID_SERVICE_CHECKOUT:   // 结账功能
				{
					CListView table_list;
					table_list.Initialization(hwnd, ID_SERVICE_LIST);
					int select_row = table_list.GetSelectionMark();
					if (-1 == select_row)
					{
						MessageBox(hwnd, TEXT("请先选择台号！"), TEXT("服务管理"), MB_ICONINFORMATION);
						break;
					}
					std::string current_status = table_list.GetItem(select_row, 1);
					if (std::string(status[0]) == current_status)
					{
						MessageBox(hwnd, TEXT("该台尚未开台！"), TEXT("服务管理"), MB_ICONINFORMATION);
						break;
					}
					CustomerTable table_info;
					table_info.table_no = table_list.GetItem(select_row, 0);              /* 获取台号 */
					table_info.customer_no = table_list.GetItem(select_row, 2);     /* 获取顾客编号 */
					DialogBoxParam(hinstance, MAKEINTRESOURCE(IDD_CUSTOM_CHECKOUT),
						      hwnd, (DLGPROC)CheckOutProc, (long)&table_info);
					break;
				}
			}
          		return TRUE;
        }
    case WM_CLOSE:
        {
			EndDialog(hwnd, LOWORD(wParam));
         //   PostQuitMessage(0);
           		return TRUE;
        }
    }
	return FALSE;
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
	if (-1 != table_list.InsertColumn(0, 80, "台号") &&
		-1 != table_list.InsertColumn(1, 80, "状态") &&
		-1 != table_list.InsertColumn(2, 150, "顾客编号") &&
		-1 != table_list.InsertColumn(3, 150, "开台时间"))
	{
		return true;
	}
	return false;
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
	if (CB_ERR == SendMessage(combo, CB_ADDSTRING, 0, (LPARAM)"一楼") ||
		CB_ERR == SendMessage(combo, CB_ADDSTRING, 0, (LPARAM)"二楼") ||
		CB_ERR == SendMessage(combo, CB_ADDSTRING, 0, (LPARAM)"三楼"))
	{
		return false;
	}
	/* Set the first item into edit box of the combo box */
	SendMessage(combo, CB_SETCURSEL, 0, 0);
	return true;
}

/*
 * 说明: 下单对话框处理过程函数
 **/
BOOL CALLBACK OrderProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static CustomerTable *table;
    static bool is_change = false;
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
			table = (CustomerTable *)lParam;
			SetDlgItemText(hwnd, IDC_TABLE_NUM, table->table_no.c_str());
			SetDlgItemText(hwnd, IDC_STATE_ORDER, table->table_state.c_str());
			SetDlgItemText(hwnd, IDC_CUSTOM_NUM, table->customer_no.c_str());
			
			CListView menu_list, custom_list;
			menu_list.Initialization(hwnd, IDC_REPAST_MENU);
			g_dialog_menu_proc = menu_list.SetListProc(OrderMenuListProc); /* 更改其默认的窗口处理过程 */
			menu_list.InsertColumn(0, 120, "菜名");
			menu_list.InsertColumn(1, 80, "单价");
			menu_list.SetExtendStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
			CMenuForm menu_form;
			menu_form.SetSQLStatement("select * from Menu");
			menu_form.GetRecordSet();
			menu_form.MoveFirst();
			int i(0);
			while (!menu_form.IsEOF())
			{
				menu_list.InsertItem(i, menu_form.dish_name());
				menu_list.SetItem(i, 1, menu_form.dish_price());
				i++;
				menu_form.MoveNext();
			}
			custom_list.Initialization(hwnd, IDC_CUSTOM_MENU);
			custom_list.InsertColumn(0, 120, "菜名");
			custom_list.InsertColumn(1, 80, "单价");
			custom_list.InsertColumn(2, 50, "数量");
			custom_list.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			CCustomerMenuForm order_info;
			order_info.GetCustomerMenuSet(table->customer_no.c_str());
			order_info.MoveFirst();
			i = 0;
			while (!order_info.IsEOF()) {
				custom_list.InsertItem(i, order_info.dish_name());
				custom_list.SetItem(i, 1, order_info.dish_price());
				custom_list.SetItem(i, 2, order_info.dish_quantity());
				i++;
				order_info.MoveNext();
			}
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_ADD_DISH:
				{
					/* 初始化列表控件 */
					CListView menu_list, customer_list;
					menu_list.Initialization(hwnd, IDC_REPAST_MENU);
					customer_list.Initialization(hwnd, IDC_CUSTOM_MENU);
					/* 获取菜单列表中的项 */
					int select_row = menu_list.GetSelectionMark();
					if (-1 == select_row) {
						MessageBox(hwnd, TEXT("请先选择一个项！"), TEXT("点菜"), MB_ICONINFORMATION);
						break;
					}
					BOOL is_ok;
					int num = GetDlgItemInt(hwnd, IDC_DISH_NUMBER, &is_ok, FALSE);
					if (!is_ok) {
						MessageBox(hwnd, TEXT("数量输入有误！"), TEXT("点菜"), MB_ICONINFORMATION);
						break;
					}
					/* 获取顾客点菜信息并放入顾客点菜列表 */
					std::string dish_name = menu_list.GetItem(select_row, 0);
					int ret = customer_list.FindItem(dish_name);
					if (-1 == customer_list.FindItem(dish_name)) {
						customer_list.InsertItem(0, dish_name); 
						customer_list.SetItem(0, 1, menu_list.GetItem(select_row, 1));
						customer_list.SetItem(0, 2, num);
						is_change = true;   /* modify the customer menu */
					} else {
						MessageBox(hwnd, TEXT("You have order this dish!"),
							       TEXT("ORDER"), MB_ICONINFORMATION);
					}
					break;
				}
			case IDC_DELETE_DISH:
				{
					CListView customer_list;
					CCustomerMenuForm customer_menu;
					customer_list.Initialization(hwnd, IDC_CUSTOM_MENU);
					int select_row = customer_list.GetSelectionMark();
					if (-1 != select_row) {
						if (IDYES == MessageBox(hwnd, TEXT("移除该项？"), TEXT("点菜"), MB_YESNO)) {
				//			customer_menu.DeleteDish(table->customer_no.c_str(), customer_list.GetItem(select_row, 0).c_str());
							customer_list.DeleteItem(select_row);
							is_change = true; /* modify the customer menu */
						}
					}
					break;
				}
			case IDC_SAVE_MENU:
				{
					CCustomer customer;
					CListView customer_list;
					customer_list.Initialization(hwnd, IDC_CUSTOM_MENU);
					int count = customer_list.GetItemCount();
					if(0==count)
					{
						MessageBox(hwnd, TEXT("您还没有点菜，请您点菜"), TEXT("点菜提示"), MB_OK);
						break;
					}
					char customer_no[16] = {0};
					GetDlgItemText(hwnd, IDC_CUSTOM_NUM, customer_no, 16);
					CCustomerMenuForm customer_menu_info;
					customer_menu_info.DeleteAll(table->customer_no.c_str());/*删除顾客点菜*/
					for (int i = 0; i < count; ++i) {
						int quantity = atoi((customer_list.GetItem(i, 2)).c_str());
						customer.InsertCustomerMenu(customer_no,
							                        customer_list.GetItem(i, 0).c_str(), 
													quantity);
					}
					is_change = false; /* save the change and set the is_change false */
					break;
				}
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
			if (true == is_change) {
				int ret = MessageBox(hwnd, TEXT("Save the change!"), 
					                 TEXT("ORDER"), MB_YESNOCANCEL);
				if (IDYES == ret) {
					CCustomerMenuForm customer_menu_info;
					customer_menu_info.DeleteAll(table->customer_no.c_str());/*删除顾客点菜*/
					CCustomer customer;
					CListView customer_list;
					customer_list.Initialization(hwnd, IDC_CUSTOM_MENU);
					int count = customer_list.GetItemCount();
					if(0==count)
					{
						MessageBox(hwnd, TEXT("您还没有点菜，请您点菜"), TEXT("点菜提示"), MB_OK);
						break;
					}
					char customer_no[16] = {0};
					GetDlgItemText(hwnd, IDC_CUSTOM_NUM, customer_no, 16);
					for (int i = 0; i < count; ++i) {
						int quantity = atoi((customer_list.GetItem(i, 2)).c_str());
						customer.InsertCustomerMenu(customer_no,
													customer_list.GetItem(i, 0).c_str(), 
													quantity);
					}
					is_change = false;

				} else if (IDCANCEL == ret) {
					break;
				}
			}
			EndDialog(hwnd, HIWORD(wParam));
			return TRUE;
		}
	}
	return FALSE;
}


LRESULT CALLBACK EditProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	switch(msg) {
	case WM_KEYDOWN:
		{
			if (wParam == VK_RETURN) {
				HWND parent = GetParent(hwnd);
				char totle[64] = "\0", paidin[64] = "\0";
				GetDlgItemText(parent, IDC_RECEIVALBE_CHECKOUT, totle, 64);
				GetDlgItemText(parent, IDC_PAIDIN_CHECKOUT,paidin, 64);
				float totle_cash = atof(totle);
				float pay = atof(paidin);
				if (0.0 == pay) {
					MessageBox(parent, TEXT("输入有误！"), TEXT("结账管理"), MB_OK | MB_ICONINFORMATION);
					break;
				}
				float check = pay - totle_cash;
				char temp[32];
				sprintf(temp, "%0.2f", check);
				SetDlgItemText(parent, IDC_GIVECHANGE_CHECKOUT, temp);
				SetFocus(GetDlgItem(parent, IDC_SAVE_CHECKOUT));
			}
		}
	}
	return CallWindowProc(g_checkout_edit_proc, hwnd, msg, wParam, lParam);
}
/*
 * 说明: 结账对话框处理过程函数
 **/
BOOL CALLBACK CheckOutProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static CustomerTable *table_info;
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
			table_info = (CustomerTable *)lParam;
			SetDlgItemText(hwnd, IDC_TABLE_NUM_CHECKOUT, table_info->table_no.c_str());
			SetDlgItemText(hwnd, IDC_CUSTOM_NUM_CHECKOUT, table_info->customer_no.c_str());
			CListView custom_list;
			custom_list.Initialization(hwnd, IDC_MENU_CHEKOUT);
			custom_list.InsertColumn(0, 120, "菜名");
			custom_list.InsertColumn(1, 80, "单价");
			custom_list.InsertColumn(2, 50, "数量");
			custom_list.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			CCustomerMenuForm order_info;
			order_info.GetCustomerMenuSet(table_info->customer_no.c_str());
			order_info.MoveFirst();
			int i = 0;
			float totle_cash = 0;
			while (!order_info.IsEOF()) {
				custom_list.InsertItem(i, order_info.dish_name());
				custom_list.SetItem(i, 1, order_info.dish_price());
				custom_list.SetItem(i, 2, order_info.dish_quantity());
				totle_cash += order_info.dish_price() * order_info.dish_quantity();
				i++;
				order_info.MoveNext();
			}
			char temp[64] = "\0";
			sprintf(temp, "%0.2f", totle_cash);
			SetDlgItemText(hwnd, IDC_RECEIVALBE_CHECKOUT, temp);

			HWND edit = GetDlgItem(hwnd, IDC_PAIDIN_CHECKOUT);
			SetFocus(edit);
			g_checkout_edit_proc = (WNDPROC)SetWindowLong(edit, GWL_WNDPROC, (LONG)EditProc);
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_SAVE_CHECKOUT: 
				{
					TCHAR totle[64] = "\0", more[64] = "\0";
					int ret1 = GetDlgItemText(hwnd, IDC_RECEIVALBE_CHECKOUT, totle, 64);
					int ret2 = GetDlgItemText(hwnd, IDC_GIVECHANGE_CHECKOUT, more, 64);
					float check_in = atof(totle);
					float check_out = atof(more);
					if (!ret1 || !ret2) {
						MessageBox(hwnd, TEXT("输入有误！"), TEXT("提示"), MB_OK | MB_ICONINFORMATION);
						return FALSE;
					} 
					if (check_out < 0) {
						TCHAR info[128] = "\0";
						sprintf(info, "还差 %0.2f 元", fabs(check_out));
						MessageBox(hwnd, info, TEXT("提示"), MB_OK | MB_ICONINFORMATION);
						return FALSE;
					}
				}
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

/*
 * 说明: 换台窗口处理过程函数 
 **/
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
	
			CustomerTable *table_info = (CustomerTable *)lParam;
			SetDlgItemText(hwnd, IDC_TABLE_NUM_OLD, table_info->table_no.c_str());
			
			SetDlgItemText(hwnd, IDC_TABLE_TIME_OLD, table_info->founding_time.c_str());
			CListView table;
			table.Initialization(hwnd, IDC_TABLE_AVAILABLE);
			table.InsertColumn(0, 100, "台号");
			table.InsertColumn(1, 50, "人数");
			table.SetSelectAndGrid(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
			InitAvailableTable(hwnd, IDC_TABLE_AVAILABLE);
			CComboBox postion;
			postion.Initialization(hwnd, IDC_FLOOR);
			postion.AddString("一楼");
			postion.InsertString(1, "二楼");
			postion.InsertString(2, "三楼");
			postion.SetCurSel(0);
			GetTableInfo(hwnd, IDC_TABLE_AVAILABLE, "01");
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_SAVE_CHANGE:
				{
					break;
				}
			case IDC_CANCLE_CHANGE:
				{
					EndDialog(hwnd, LOWORD(wParam));
					break;
				}
			case IDC_FLOOR:
				{
					if (HIWORD(wParam) == CBN_SELCHANGE) {
						CComboBox combo;
						combo.Initialization(hwnd, IDC_FLOOR);
						std::string text;
						combo.GetComboBoxText(text);
						if ("一楼" == text) {
							const char floor[] = "01";
							GetTableInfo(hwnd, IDC_TABLE_AVAILABLE, floor);
						} else if ("二楼" == text) {
							const char floor[] = "02";
							GetTableInfo(hwnd, IDC_TABLE_AVAILABLE, floor);
						} else if ("三楼" == text) {
							const char floor[] = "03";
							GetTableInfo(hwnd, IDC_TABLE_AVAILABLE, floor);
						}
/*						break;*/
					}
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
 *  说明: 开台对话框处理过程函数
 **/
BOOL CALLBACK StartTableProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static int payable_num(0);
	static std::string table_no;
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
			CustomerTable *table_info = (CustomerTable *)lParam;
			table_no = table_info->table_no;
			
//			SetDlgItemText(hwnd, IDC_TABLE_NO_START, table_info->no.c_str());
			char customer_no[128] = "\0";
			CDBForm DB_time;
		//	GetLocalTime(&current_time);
			srand((int)time(NULL));
			int rand_dom = rand() % 10;
			sprintf(customer_no, "%s%s%s%s%s%s%d", DB_time.GetYearString().c_str(),
				    DB_time.GetMonthString().c_str(), DB_time.GetDayString().c_str(), 
					DB_time.GetHourString().c_str(), DB_time.GetMinuteString().c_str(),
					DB_time.GetSecondString().c_str(), rand_dom);
			
			SetDlgItemText(hwnd, IDC_CUSTOMER_NO_START, customer_no);  // 显示顾客编号
			
			CListView table, cus;
			table.Initialization(hwnd, IDC_START_TABLE);
			cus.Initialization(hwnd, IDC_CUSTOMER_TABLE);
			table.InsertColumn(0, 100, "台号");
			cus.InsertColumn(0, 100, "台号");
			table.InsertColumn(1, 50, "人数");
			cus.InsertColumn(1, 50, "人数");
			table.SetSelectAndGrid(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
			cus.SetSelectAndGrid(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
			GetTableInfo(hwnd, IDC_START_TABLE);
			InitComboBox(hwnd, IDC_COMBO1);
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case ID_START_OK:
				{
					char cus_no[32] = "\0";
					GetDlgItemText(hwnd, IDC_CUSTOMER_NO_START, cus_no, 32);  // 获取顾客编号信息
					MessageBox(hwnd, cus_no, TEXT("开台管理"), MB_OK | MB_ICONINFORMATION);
					CListView customer_table;
					customer_table.Initialization(hwnd,  IDC_CUSTOMER_TABLE);
					int count = customer_table.GetItemCount();   // 获取台号数量
					CDBForm db;
					char sql[256] = "\0";
					std::string error;
					sprintf(sql, "exec InsertCustomer '%s'", cus_no);
					db.ExecuteSQL(sql, error);
					for (int i = 0; i < count; ++i) 
					{
						std::string no = customer_table.GetItem(i, 0);
						std::string num = customer_table.GetItem(i, 1);
						memset(sql, 0, 256);
						sprintf(sql, "exec InsertCustomerTable '%s', %d, '%s', 0", cus_no, atoi(num.c_str()), no.c_str());
						db.ExecuteSQL(sql, error);
					}
				}
			case ID_START_CANCEL:
				{
					EndDialog(hwnd, LOWORD(wParam));
					break;
				}
			case IDC_ADD_TABLE:
				{
					CListView table;
					table.Initialization(hwnd, IDC_START_TABLE);
					int select_row = table.GetSelectionMark();
					if (-1 == select_row) {
						MessageBox(hwnd, TEXT("请选择台号！"), TEXT("开台管理"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					std::string num = table.GetItem(select_row, 1);   // 获取台号可容纳的人数
					BOOL is_success;
					int real_num = GetDlgItemInt(hwnd, IDC_REAL_NUM_START, &is_success, FALSE);
					if (!is_success) {
						MessageBox(hwnd, TEXT("输入人数有误！"), TEXT("开台管理"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					int pay_num = atoi(num.c_str());
					if (pay_num < real_num) {
						MessageBox(hwnd, TEXT("人数超过限制！"), TEXT("开台管理"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					CListView customer_table;
					customer_table.Initialization(hwnd, IDC_CUSTOMER_TABLE);
					customer_table.InsertItem(0, table.GetItem(select_row, 0));
					customer_table.SetItem(0, 1, real_num);
					break;
				}
			case IDC_DELETE_TABLE:
				{
					CListView customer_table;
					customer_table.Initialization(hwnd, IDC_CUSTOMER_TABLE);
					int select_row = customer_table.GetSelectionMark();
					if (-1 == select_row) {
						MessageBox(hwnd, TEXT("请选择台号！"), TEXT("开台管理"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					if (IDYES == MessageBox(hwnd, TEXT("确定要删除该台号?"), TEXT("开台管理"), MB_YESNO)) 
					{
						customer_table.DeleteItem(select_row);
					}
					break;
				}
			case IDC_COMBO1:
				{
					if (HIWORD(wParam) == CBN_SELCHANGE)
					{
						/* 
						 * HIT: When you change the combo box item, if you want 
						 *      make some change, you can add it at here. 
						 */
						CComboBox combo;
						combo.Initialization(hwnd, IDC_COMBO1);
						std::string text;
						combo.GetComboBoxText(text);
						GetTableInfo(hwnd, IDC_START_TABLE, GetFloor(text).c_str());	
					}
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
 * 说明: 设置台号信息
 * 参数:
 *       hwnd [in] 父窗口句柄
 *       id [in] 窗口id
 *       error [out] 错误信息
 * 返回值: 成功返回true，否则返回false
 **/
bool SetListInfo(const HWND hwnd, const UINT id, 
				 const char *find, std::string &error)
{
	CTableInfo table_info;
	CCustomer customer;
	char sql[256];
// 	sprintf(sql, "select Tno,Cno,Tstatus,Ctime from Customer,TableInfo,CustomerTable \
// 		    where Cno=Ccustomerno and Ctableno=Tno and Ctableno like '%s%c'", find, '%');
// 	customer.SetSQLStatement(sql);
//	customer.SetSQLStatement("execute SelectCustomer");
	if (!customer.GetRecordSet())
	{
		error = "获取记录集失败！";
		return false;
	}
	if (!customer.MoveFirst())
	{
		error = "移动到第一条记录集失败！";
		return false;
	}
	CListView list;
	if (!list.Initialization(hwnd, id))
	{
		error = "初始化list view失败！";
		return false;
	}
	if (!list.DeleteAllItems())
	{
		error = "清空list view失败！";
		return false;
	}
	int i(0);
	while (!customer.IsEOF()) 
	{
		list.InsertItem(i, customer.table_no());
		list.SetItem(i, 1, status[customer.table_state()]);
		list.SetItem(i, 2, customer.customer_no());
		list.SetItem(i, 3, customer.founding_time()); 
		/* TODO: Add data time at here. */
		i++;
		if (!customer.MoveNext())
		{
			error = "移动到下一条记录集失败！";
			return false;
		}
	}
	return true;
}

bool InitAvailableTable(const HWND hwnd, int id)
{
	CTableInfo table_form;
	CListView table_list;
	table_list.Initialization(hwnd, id);
	table_form.SetSQLStatement("select * from TableInfo");
	table_form.GetRecordSet();
	table_form.MoveFirst();
	int i(0);
	while (!table_form.IsEOF())
	{
		std::string temp = table_form.table_no();
		short num = table_form.payable_num();
		table_list.InsertItem(i, temp);
		table_list.SetItem(i, 1, num);
		table_form.MoveNext();
		i++;
	}
	return true;
}

LRESULT CALLBACK OrderMenuListProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_LBUTTONUP:
		{
			HWND dialog_hwnd = GetParent(hwnd);
			HWND number_edit_hwnd = GetDlgItem(dialog_hwnd, IDC_DISH_NUMBER);  /* 获取数量编辑框句柄 */
			SetDlgItemInt(dialog_hwnd, IDC_DISH_NUMBER, 1, FALSE);   /* 初始为1 */
			return 0;
		}
	}
	return CallWindowProc(g_dialog_menu_proc, hwnd, message, wParam, lParam);
}

void GetTableInfo(const HWND hwnd, const int id, const char *floor, int use) {
	CTableInfo table_form;
	CListView table_list;
	table_list.Initialization(hwnd, id);
	table_list.DeleteAllItems();
	char sql[128] = "\0";
	sprintf(sql, "select * from TableInfo where Tstatus = %d and Tno like '%s%c'", use, floor, '%');
	table_form.SetSQLStatement(sql);
	table_form.GetRecordSet();
	table_form.MoveFirst();
	int i(0);
	while (!table_form.IsEOF())
	{
		std::string temp = table_form.table_no();
		short num = table_form.payable_num();
		table_list.InsertItem(i, temp);
		table_list.SetItem(i, 1, num);
		table_form.MoveNext();
		i++;
	}
}
/*
 * @ brief: 将中文的楼层信息转化为数字字符型
 * @ param: text [in] 中文楼层信息
 * @ return: 数字字符型楼层信息
 **/
std::string GetFloor(std::string text) {
	std::string num;
	if ("一楼" == text)
	{
		num = "01";
	}
	if ("二楼" == text)
	{
		num = "02";
	}
	if ("三楼" == text)
	{
		num = "03";
	}	
	return num;
}