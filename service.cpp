/*
 * �ļ�: service.cpp
 * ˵��: ���ļ��Ƿ�������¼�ļ����Է������Ĳ����ڸ��ļ�����ɡ�
 **/


#include "service.h"
#include "TableInfo.h"
#include "Customer.h"
#include "MenuForm.h"
#include "CustomerMenuForm.h"

WNDPROC g_old_list_processes; /* ���Ի����е��б������ */
WNDPROC g_dialog_menu_proc;  /* �Ի����еĲ˵��б�Ĵ��ڴ������ */
char* status[3] = {"δ��̨", "�ѿ�̨", "��Ԥ��"};

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
			CreateRefeshButton(hwnd, ID_SERVICE_REFRESH);
			std::string error_info;
			SetListInfo(hwnd, ID_SERVICE_LIST, error_info);
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
			case ID_SERVICE_REFRESH:
				{
					std::string error;
					if (!SetListInfo(hwnd, ID_SERVICE_LIST, error))
					{
						MessageBox(hwnd, error.c_str(), TEXT("�������"), MB_ICONINFORMATION);
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
						if ("����һ¥" == text)
						{
							MessageBox(hwnd, TEXT("����һ¥"), TEXT("combo"), MB_ICONINFORMATION);
						}
						if ("������¥" == text)
						{
							MessageBox(hwnd, TEXT("������¥"), TEXT("combo"), MB_ICONINFORMATION);
						}
						if ("������¥" == text)
						{
							MessageBox(hwnd, TEXT("������¥"), TEXT("combo"), MB_ICONINFORMATION);
						}	
					}
					break;
				}
			case ID_SERVICE_START:
				{
					std::string error_information;  /* ������Ϣ���� */
					CListView table_list;
// 					table_list.Initialization(hwnd, ID_SERVICE_LIST);
// 					int select_row = table_list.GetSelectionMark();
// 					if (-1 == select_row)
// 					{
// 						MessageBox(hwnd, TEXT("����ѡ��̨��"), TEXT("�������"), MB_ICONINFORMATION);
// 						break;
// 					}
// 					std::string table_status = table_list.GetItem(select_row, 1);
// 					if (table_status == std::string(status[1]) ||
// 						table_status == std::string(status[2]))
// 					{
// 						MessageBox(hwnd, TEXT("��̨�����ڲ�����"), TEXT("�������"), MB_ICONINFORMATION);
// 						break;
// 					}	
					CustomerTable table_info;
// 					table_info.no = table_list.GetItem(select_row, 0);   /* ��ȡ̨�� */
// 					std::string num = table_list.GetItem(select_row, 2);     /* ��ȡ���������� */
// 					table_info.payable_num = atoi(num.c_str());   /* ��ע: ���Ǻܰ�ȫ */
					DialogBoxParam(hinstance, MAKEINTRESOURCE(IDD_START_TABLE),
						           hwnd, (DLGPROC)StartTableProc, (long)&table_info);
					SetListInfo(hwnd, ID_SERVICE_LIST, error_information);
					break;
				}
			case ID_SERVICE_ORDER:
				{
					CListView table_list;    /* ̨����Ϣ�б� */
					table_list.Initialization(hwnd, ID_SERVICE_LIST);
					int select_row = table_list.GetSelectionMark();
					if (-1 == select_row)
					{
						MessageBox(hwnd, TEXT("����ѡ��̨�ţ�"), TEXT("�������"), MB_ICONINFORMATION);
						break;
					}
					std::string current_status = table_list.GetItem(select_row, 1);
					if (std::string(status[0]) == current_status)
					{
						MessageBox(hwnd, TEXT("��̨��δ��̨��"), TEXT("�������"), MB_ICONINFORMATION);
						break;
					}
					CustomerTable table_info;  /* ̨����Ϣ */
					table_info.table_no = table_list.GetItem(select_row, 0);
					table_info.table_state = table_list.GetItem(select_row, 1);
					table_info.customer_no = table_list.GetItem(select_row, 2);
				//	table_info.founding_time = table_list.GetItem(select_row, 2);
					DialogBoxParam(hinstance, MAKEINTRESOURCE(IDD_ORDER),
						           hwnd, (DLGPROC)OrderProc, (long)&table_info);
					break;
				}
			case ID_SERVICE_RETREAT:
				{
					CListView table_list;
					table_list.Initialization(hwnd, ID_SERVICE_LIST);
					int select_row = table_list.GetSelectionMark();
					if (-1 == select_row)
					{
						MessageBox(hwnd, TEXT("����ѡ��̨�ţ�"), TEXT("�������"), MB_ICONINFORMATION);
						break;
					}
					std::string current_status = table_list.GetItem(select_row, 1);
					if (std::string(status[0]) == current_status)
					{
						MessageBox(hwnd, TEXT("��̨��δ��̨��"), TEXT("�������"), MB_ICONINFORMATION);
						break;
					}
					DialogBox(hinstance, MAKEINTRESOURCE(IDD_RETREAT),
						      hwnd, (DLGPROC)RetreatProc);
					break;
				}
			case ID_SERVICE_CHECKOUT:
				{
					CListView table_list;
					table_list.Initialization(hwnd, ID_SERVICE_LIST);
					int select_row = table_list.GetSelectionMark();
					if (-1 == select_row)
					{
						MessageBox(hwnd, TEXT("����ѡ��̨�ţ�"), TEXT("�������"), MB_ICONINFORMATION);
						break;
					}
					std::string current_status = table_list.GetItem(select_row, 1);
					if (std::string(status[0]) == current_status)
					{
						MessageBox(hwnd, TEXT("��̨��δ��̨��"), TEXT("�������"), MB_ICONINFORMATION);
						break;
					}
					DialogBox(hinstance, MAKEINTRESOURCE(IDD_CUSTOM_CHECKOUT),
						      hwnd, (DLGPROC)CheckOutProc);
					break;
				}
			case ID_SERVICE_CHANGE:
				{
					CListView table_list;
					table_list.Initialization(hwnd, ID_SERVICE_LIST);
					int select_row = table_list.GetSelectionMark();
					if (-1 == select_row)
					{
						MessageBox(hwnd, TEXT("����ѡ��̨�ţ�"), TEXT("�������"), MB_ICONINFORMATION);
						break;
					}
					std::string current_status = table_list.GetItem(select_row, 1);
					if (std::string(status[0]) == current_status)
					{
						MessageBox(hwnd, TEXT("��̨��δ��̨��Ԥ���� ���ɽ��л�̨��"), 
							       TEXT("�������"), MB_ICONINFORMATION);
						break;
					}
					CustomerTable table_info;
					table_info.table_no = table_list.GetItem(select_row, 0);              /* ��ȡ̨�� */
					table_info.customer_no = table_list.GetItem(select_row, 2);     /* ��ȡ�˿ͱ�� */
					table_info.founding_time = table_list.GetItem(select_row, 3);   /* ��ȡ��̨ʱ�� */
					DialogBoxParam(hinstance, MAKEINTRESOURCE(IDD_CHANGE_TABLE),
						           hwnd, (DLGPROC)ChangeProc, (long)&table_info);
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
 * ˵��: list view��������
 *       �ú������ܴ������е���Ϣ(��WM_CREATE��Ϣ)��ֻ�ܴ���
 *       ���ֵ���Ϣ��
 **/
LRESULT CALLBACK ListProcesses(HWND hwnd, UINT message,
                               WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_LBUTTONDBLCLK:
        {
            break;
        }
	case WM_LBUTTONDOWN:
		{
		
			break;
		}
    }
    return CallWindowProc(g_old_list_processes, hwnd, message, wParam, lParam);
}

/*
 * ˵��: ����list view����
 * ����:
 *       hinstance [in] ����ʵ�����
 *       hwnd [in] ���ھ��
 *       list_view [out] CMyListView���󣬱��洴���õ�listview�Ĳ���
 * ����ֵ: ���ɹ�����ture,���򷵻�false��
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
	list_view.set_new_process(ListProcesses);
    bool is_ok = list_view.Create(style, table_rect, hwnd, ID_SERVICE_LIST);
	if (is_ok && list_view.is_set_process())
	{
		g_old_list_processes = list_view.old_process();
	}
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
	if (-1 != table_list.InsertColumn(0, 80, "̨��") &&
		-1 != table_list.InsertColumn(1, 80, "״̬") &&
		-1 != table_list.InsertColumn(2, 150, "�˿ͱ��") &&
		-1 != table_list.InsertColumn(3, 150, "��̨ʱ��"))
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
	return group.Create("̨����Ϣ", BS_GROUPBOX, group_rect, hwnd, 0);
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
	CStatic floor;
	RECT floor_rect = {40, 50, 60, 25};
	if (!floor.Create("¥  ��", ES_CENTER, floor_rect, hwnd))
	{
		return false;
	}
	CComboBox combo;
	RECT combo_rect;
	combo_rect.left = 120;
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
	if (CB_ERR == SendMessage(combo, CB_ADDSTRING, 0, (LPARAM)"����һ¥") ||
		CB_ERR == SendMessage(combo, CB_ADDSTRING, 0, (LPARAM)"������¥") ||
		CB_ERR == SendMessage(combo, CB_ADDSTRING, 0, (LPARAM)"������¥"))
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
	if (!button.Create("ǰ̨����", BS_GROUPBOX, rect, hwnd, 0))
	{
		return false;
	}
	rect.top = 340;
	rect.bottom = 80;
	if (!button.Create("�˺Ź���", BS_GROUPBOX, rect, hwnd, 0))
	{
		return false;
	}
	rect.left += 30;
	rect.top = 60;
	rect.right = 80;
	rect.bottom = 30;
 	if (!button.Create("��  ̨", ES_CENTER | BS_PUSHBUTTON | WS_TABSTOP,
		               rect, hwnd, ID_SERVICE_START))
	{
		return false;
	}
	rect.top += 60;
	if (!button.Create("��  ̨", ES_CENTER | BS_PUSHBUTTON,
		               rect, hwnd, ID_SERVICE_CHANGE))
	{
		return false;
	}
	rect.top += 60;
	if (!button.Create("��  ��", ES_CENTER | BS_PUSHBUTTON,
		               rect, hwnd, ID_SERVICE_ORDER))
	{
		return false;
	}
	rect.top += 60;
	if (!button.Create("��  ��", ES_CENTER | BS_PUSHBUTTON,
		               rect, hwnd, ID_SERVICE_CHECKOUT))
	{
		return false;
	}
	rect.top = 370;
	if (!button.Create("�޸�����", ES_CENTER | BS_PUSHBUTTON,
		     		   rect, hwnd, ID_SERVICE_CHANGE_PASSWD))
	{
		return false;
	}
	return true;
}

/*
 * ˵��: �µ��Ի�������̺���
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
			g_dialog_menu_proc = menu_list.SetListProc(OrderMenuListProc); /* ������Ĭ�ϵĴ��ڴ������ */
			menu_list.InsertColumn(0, 120, "����");
			menu_list.InsertColumn(1, 80, "����");
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
			custom_list.InsertColumn(0, 120, "����");
			custom_list.InsertColumn(1, 80, "����");
			custom_list.InsertColumn(2, 50, "����");
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
					/* ��ʼ���б�ؼ� */
					CListView menu_list, customer_list;
					menu_list.Initialization(hwnd, IDC_REPAST_MENU);
					customer_list.Initialization(hwnd, IDC_CUSTOM_MENU);
					/* ��ȡ�˵��б��е��� */
					int select_row = menu_list.GetSelectionMark();
					if (-1 == select_row) {
						MessageBox(hwnd, TEXT("����ѡ��һ���"), TEXT("���"), MB_ICONINFORMATION);
						break;
					}
					BOOL is_ok;
					int num = GetDlgItemInt(hwnd, IDC_DISH_NUMBER, &is_ok, FALSE);
					if (!is_ok) {
						MessageBox(hwnd, TEXT("������������"), TEXT("���"), MB_ICONINFORMATION);
						break;
					}
					/* ��ȡ�˿͵����Ϣ������˿͵���б� */
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
						if (IDYES == MessageBox(hwnd, TEXT("�Ƴ����"), TEXT("���"), MB_YESNO)) {
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
// 					char customer_no[16] = {0};
// 					GetDlgItemText(hwnd, IDC_CUSTOM_NUM, customer_no, 16);
					for (int i = 0; i < count; ++i) {
						int quantity = atoi((customer_list.GetItem(i, 2)).c_str());
						
						customer.InsertCustomerMenu(table->customer_no.c_str(),
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
					customer_menu_info.DeleteAll(table->customer_no.c_str());
					CCustomer customer;
					CListView customer_list;
					customer_list.Initialization(hwnd, IDC_CUSTOM_MENU);
					int count = customer_list.GetItemCount();
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

/*
 * ˵��: ���˶Ի�������̺���
 **/
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

/*
 * ˵��: �˲˶Ի��������
 **/
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

/*
* ˵��: ��̨���ڴ�����̺��� 
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
			table.InsertColumn(0, 100, "̨��");
			table.SetSelectAndGrid(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
			InitAvailableTable(hwnd);
			CComboBox postion;
			postion.Initialization(hwnd, IDC_FLOOR_NUM_AVAILABLE);
			postion.AddString("����һ¥");
			postion.InsertString(1, "������¥");
			postion.InsertString(2, "������¥");
			postion.SetCurSel(0);
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
 *  ˵��: ��̨�Ի�������̺���
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
			SYSTEMTIME current_time;
			char customer_no[128] = "\0";
			GetLocalTime(&current_time);
			sprintf(customer_no, "%d%d%d%d%d%s", current_time.wYear, current_time.wMonth,
				    current_time.wDay, current_time.wHour, current_time.wMinute, table_info->table_no.c_str());
			
//			SetDlgItemText(hwnd, IDC_CUSTOMER_NO_START, customer_no);
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case ID_START_OK:
				{
					BOOL error;
					UINT real_num = GetDlgItemInt(hwnd, IDC_REAL_NUM_START, &error, FALSE);
					if (!error)
					{
						MessageBox(hwnd, TEXT("������������"), TEXT("��̨"), MB_ICONINFORMATION);
						break;
					}
					else if (real_num > payable_num)
					{
						MessageBox(hwnd, TEXT("�����������ƣ�"), TEXT("��̨"), MB_ICONINFORMATION);
						break;
					}
					/*
					 * TODO: Update database
					 **/
					CTableInfo table_info;
					std::string error_info;
//					if (table_info.Connect("repast", "repast", "repast", error_info))
					{
						SYSTEMTIME current_time;
						char time_str[128] = "\0";
						GetLocalTime(&current_time);
						sprintf(time_str, "%d-%d-%d %d:%d:%d", current_time.wYear, current_time.wMonth, 
							    current_time.wDay, current_time.wHour, current_time.wMinute, current_time.wSecond); 
						char sql[128] = "\0";
						sprintf(sql, "update TableInfo set Tstatus=1, Ttime='%s' where Ttableno='%s'",
						    time_str, table_no.c_str());
						if (!table_info.UpdateForm(sql, error_info))
						{
							MessageBox(hwnd, error_info.c_str(), TEXT("��̨"),
								MB_ICONINFORMATION);
							break;
						}
					}
//					else
// 					{
// 						MessageBox(hwnd, error_info.c_str(),
// 							TEXT("�������"), MB_ICONINFORMATION);
// 						break;
// 					}
				}
			case ID_START_CANCEL:
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
 * ˵��: ����̨����Ϣ
 * ����:
 *       hwnd [in] �����ھ��
 *       id [in] ����id
 *       error [out] ������Ϣ
 * ����ֵ: �ɹ�����true�����򷵻�false
 **/
bool SetListInfo(const HWND hwnd, const UINT id, std::string &error)
{
	CTableInfo table_info;
	CCustomer customer;
	customer.SetSQLStatement("execute SelectCustomer");
	if (!customer.GetRecordSet())
	{
		error = "��ȡ��¼��ʧ�ܣ�";
		return false;
	}
	if (!customer.MoveFirst())
	{
		error = "�ƶ�����һ����¼��ʧ�ܣ�";
		return false;
	}
	CListView list;
	if (!list.Initialization(hwnd, id))
	{
		error = "��ʼ��list viewʧ�ܣ�";
		return false;
	}
	if (!list.DeleteAllItems())
	{
		error = "���list viewʧ�ܣ�";
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
			error = "�ƶ�����һ����¼��ʧ�ܣ�";
			return false;
		}
	}
	return true;
}

/*
 *  @˵��: ����ˢ�°�ť
 *  @����: 
 *         hwnd [in] �����ھ��
 *         id [in] ���ڱ�ʶid
 *  @����ֵ: ���ɹ�����true�����򷵻�false
 **/
bool CreateRefeshButton(const HWND hwnd, const UINT id)
{
	CButton refresh;
	RECT refresh_rect;
	refresh_rect.left = 300;
	refresh_rect.top = 50;
	refresh_rect.right = 100;
	refresh_rect.bottom = 30;
	return refresh.Create("ˢ  ��", ES_CENTER | BS_PUSHBUTTON | WS_TABSTOP,
		                  refresh_rect, hwnd, id);
}

bool InitAvailableTable(const HWND hwnd)
{
	CTableInfo table_form;
	CListView table_list;
	table_list.Initialization(hwnd, IDC_TABLE_AVAILABLE);
	table_form.SetSQLStatement("select * from TableInfo");
	table_form.GetRecordSet();
	table_form.MoveFirst();
	int i(0);
	while (!table_form.IsEOF())
	{
		std::string temp = table_form.table_no();
		table_list.InsertItem(i, temp);
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
			HWND number_edit_hwnd = GetDlgItem(dialog_hwnd, IDC_DISH_NUMBER);  /* ��ȡ�����༭���� */
			SetDlgItemInt(dialog_hwnd, IDC_DISH_NUMBER, 1, FALSE);   /* ��ʼΪ1 */
			return 0;
		}
	}
	return CallWindowProc(g_dialog_menu_proc, hwnd, message, wParam, lParam);
}