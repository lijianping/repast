/*
 * �ļ�: service.cpp
 * ˵��: ���ļ��Ƿ�������¼�ļ����Է������Ĳ����ڸ��ļ�����ɡ�
 **/


#include "service.h"
#include "TableInfo.h"
#include "Customer.h"
#include "CustomerMenuForm.h"
#include "LoginForm.h"
#include "Edit.h"
#include "tabctrl.h"
#include "treectrl.h"
#include "Commodity.h"
#include "CommodityCategoryForm.h"
#include "floorinfo.h"
#include "Edit.h"
#include "consumer_table.h"
#include <MATH.H>
#include <TIME.H>

WNDPROC g_old_list_processes; // ���Ի����е��б������ 
WNDPROC g_dialog_menu_proc;  // �Ի����еĲ˵��б�Ĵ��ڴ������ 
WNDPROC g_checkout_edit_proc;
WNDPROC g_change_table_list;
extern std::string g_login_name;

BOOL CALLBACK ServiceProcesses(HWND hwnd, UINT message,
                                  WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE hinstance;
	switch (message)
	{
	case WM_INITDIALOG:
		{
			hinstance = (HINSTANCE)lParam;
			// ��ʼ����̨list
			CListView table_list(hwnd, ID_SERVICE_LIST);
			table_list.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			table_list.InsertColumn(0, 150, "�˿ͱ��");
			table_list.InsertColumn(1, 80, "̨��");
			table_list.InsertColumn(2, 80, "����");
			table_list.InsertColumn(3, 80, "״̬");
			table_list.InsertColumn(4, 100, "�˿�����");
			table_list.InsertColumn(5, 150, "��̨/Ԥ��ʱ��");
			std::string error_info;
			try {
				InitComboBox(hwnd, ID_SERVICE_COMBO); // ��ʼ��¥��Combo box
			} catch (Err &err) {
				MessageBox(hwnd, err.what(), TEXT("SERVICE"), MB_ICONERROR);
				return FALSE;
			}
			CComboBox combo(hwnd, ID_SERVICE_COMBO);
			std::string floor_name;
			combo.GetComboBoxText(floor_name);
			if (!ShowConsumerTableInfo(hwnd, ID_SERVICE_LIST, floor_name.c_str())) {
				return FALSE;
			}
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
			case ID_SERVICE_REFRESH:   // ˢ��
				{
					CComboBox combo;
					combo.Initialization(hwnd, ID_SERVICE_COMBO);
					std::string floor_name;
					combo.GetComboBoxText(floor_name);
					if (!ShowConsumerTableInfo(hwnd, ID_SERVICE_LIST, floor_name.c_str())) {
						return FALSE;
					}
					break;
				}
			case ID_SERVICE_COMBO:
				{
					if (HIWORD(wParam) == CBN_SELCHANGE) {
						CComboBox combo;
						combo.Initialization(hwnd, ID_SERVICE_COMBO);
						std::string floor_name;
						combo.GetComboBoxText(floor_name);
						if (!ShowConsumerTableInfo(hwnd, ID_SERVICE_LIST, floor_name.c_str())) {
							return FALSE;
						}
					}
					break;
				}
			case ID_SERVICE_START:   // ��̨����
				{
					std::string error_information;  // ������Ϣ���� 
					CListView table_list;	
					CustomerTable table_info;
					table_info.menu_id = ID_SERVICE_START;
					DialogBoxParam(hinstance, MAKEINTRESOURCE(IDD_START_TABLE),
						           hwnd, (DLGPROC)StartTableProc, (long)&table_info);
					break;
				}
			case ID_SERVICE_BOOK:  // Ԥ������
				{
					std::string error_information;
					CustomerTable table_info;
					table_info.menu_id = ID_SERVICE_BOOK;
					DialogBoxParam(hinstance, MAKEINTRESOURCE(IDD_START_TABLE),
						hwnd, (DLGPROC)StartTableProc, (long)&table_info);
					break;
				}
			case ID_SERVICE_CHANGE:  // ��̨����
			{
				CListView table_list;
				table_list.Initialization(hwnd, ID_SERVICE_LIST);
				int select_row = table_list.GetSelectionMark();
				if (-1 == select_row) {
					MessageBox(hwnd, TEXT("����ѡ��̨�ţ�"), TEXT("�������"), MB_ICONINFORMATION);
					break;
				}
				std::string current_status = table_list.GetItem(select_row, 1);
				if (std::string(TableStatus[0]) == current_status) {
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
			case ID_SERVICE_ORDER: // ��˹���  
				{
					CListView table_list;    /* ̨����Ϣ�б� */
					table_list.Initialization(hwnd, ID_SERVICE_LIST);
					int select_row = table_list.GetSelectionMark();
					if (-1 == select_row) {
						MessageBox(hwnd, TEXT("����ѡ��̨�ţ�"), TEXT("�������"), MB_ICONINFORMATION);
						break;
					}
					std::string current_status = table_list.GetItem(select_row, 1);
					if (std::string(TableStatus[0]) == current_status) {
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
			case ID_SERVICE_CHECKOUT:   // ���˹���
				{
					CListView table_list;
					table_list.Initialization(hwnd, ID_SERVICE_LIST);
					int select_row = table_list.GetSelectionMark();
					if (-1 == select_row) {
						MessageBox(hwnd, TEXT("����ѡ��̨�ţ�"), TEXT("�������"), MB_ICONINFORMATION);
						break;
					}
					std::string current_status = table_list.GetItem(select_row, 1);
					if (std::string(TableStatus[0]) == current_status) {
						MessageBox(hwnd, TEXT("��̨��δ��̨��"), TEXT("�������"), MB_ICONINFORMATION);
						break;
					}
					CustomerTable table_info;
					table_info.table_no = table_list.GetItem(select_row, 0);              /* ��ȡ̨�� */
					table_info.customer_no = table_list.GetItem(select_row, 2);     /* ��ȡ�˿ͱ�� */
					DialogBoxParam(hinstance, MAKEINTRESOURCE(IDD_CUSTOM_CHECKOUT),
						      hwnd, (DLGPROC)CheckOutProc, (long)&table_info);
					break;
				}
			}  // end switch(LOWORD(wParam)
			CComboBox combo;   // ����
			combo.Initialization(hwnd, ID_SERVICE_COMBO);
			std::string floor_name;
			combo.GetComboBoxText(floor_name);
			if (!ShowConsumerTableInfo(hwnd, ID_SERVICE_LIST, floor_name.c_str())) {
				return FALSE;
			}
          	return TRUE;
        }  // end WM_COMMAND
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
	CComboBox combo(hwnd, id);
	FloorInfo floor_name;
	floor_name.GetFloorName();
	while (!floor_name.IsEOF()) {
		combo.AddString(floor_name.floor_name());
	}
	combo.SetCurSel(0);
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
			// ��ʼ���οؼ�
			TreeCtrl tree(hwnd, IDC_MENU_TREE);
			CCommodityCategoryForm comodity_category;/*��Ʒ����*/
			comodity_category.GetRecordSet();
			HTREEITEM tree_parent;
			std::string error;
			CCommodity commodity;/*��Ʒ������Ϣ*/
			while(!comodity_category.IsEOF())
			{
				tree_parent = tree.InsertRootItem(comodity_category.name());/*���븸�ڵ�*/

				while(!commodity.IsEOF())
				{
	
				}
			}  // �������οؼ���ʼ��
			CListView menu_list, custom_list;
			menu_list.Initialization(hwnd, IDC_REPAST_MENU);
			g_dialog_menu_proc = menu_list.SetListProc(OrderMenuListProc); /* ������Ĭ�ϵĴ��ڴ������ */
			menu_list.InsertColumn(0, 120, "����");
			menu_list.InsertColumn(1, 60, "����");
			menu_list.InsertColumn(2, 50, "��λ");
			menu_list.SetExtendStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

			custom_list.Initialization(hwnd, IDC_CUSTOM_MENU);
			custom_list.InsertColumn(0, 120, "����");
			custom_list.InsertColumn(1, 80, "����");
			custom_list.InsertColumn(2, 50, "����");
			custom_list.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			CCustomerMenuForm order_info;
			order_info.GetCustomerMenuSet(table->customer_no.c_str());
			int i = 0;
			while (!order_info.IsEOF()) {
				custom_list.InsertItem(i, order_info.dish_name());
				custom_list.SetItem(i, 1, order_info.dish_price());
				custom_list.SetItem(i, 2, order_info.dish_quantity());
				i++;
			}
			return TRUE;
		}
	case WM_NOTIFY:
		{
			switch(LOWORD(wParam))
			{
			case IDC_MENU_TREE:
				{
					if (((LPNMHDR)lParam)->code == NM_DBLCLK) /*˫�����οؼ��е�һ��*/
					{
						TreeCtrl commodity_tree(hwnd, IDC_MENU_TREE);
						char text[256];
						if (commodity_tree.GetItem(sizeof(text),text))
						{
							std::string error;
							CCommodity commodity; /*��Ʒ������Ϣ*/
							
							
							CListView staff_list;
							/* Initialization the list view object */
							staff_list.Initialization(hwnd, IDC_REPAST_MENU);
							/* Clean the list view */
							staff_list.DeleteAllItems();
							int item = 0;
							while (!commodity.IsEOF())
							{
								
								item++;
							}
						}
						else
						{
							MessageBox(hwnd, TEXT("Something Error!"), TEXT("HIT"), MB_ICONINFORMATION);
						}	
					}
					break;
				}
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
					if(0==count)
					{
						MessageBox(hwnd, TEXT("����û�е�ˣ��������"), TEXT("�����ʾ"), MB_OK);
						break;
					}
					char customer_no[16] = {0};
					GetDlgItemText(hwnd, IDC_CUSTOM_NUM, customer_no, 16);
					CCustomerMenuForm customer_menu_info;
					bool is_ok = false;
					for (int i = 0; i < count; ++i) {
						int quantity = atoi((customer_list.GetItem(i, 2)).c_str());
						is_ok = customer.InsertCustomerMenu(customer_no,
							                        customer_list.GetItem(i, 0).c_str(), 
													quantity);
						if (!is_ok) {
							customer_menu_info.DeleteAll(customer_no);
							break;
						}
					}
					if (is_ok) {
						MessageBox(hwnd, TEXT("��Ӳ˵��ɹ���"), TEXT("��ʾ"), MB_ICONINFORMATION);
					} else {
						MessageBox(hwnd, TEXT("��Ӳ˵�ʧ�ܣ�"), TEXT("��ʾ"), MB_ICONINFORMATION);
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
					customer_menu_info.DeleteAll(table->customer_no.c_str());/*ɾ���˿͵��*/
					CCustomer customer;
					CListView customer_list;
					customer_list.Initialization(hwnd, IDC_CUSTOM_MENU);
					int count = customer_list.GetItemCount();
					if(0==count)
					{
						MessageBox(hwnd, TEXT("����û�е�ˣ��������"), TEXT("�����ʾ"), MB_OK);
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
					MessageBox(parent, TEXT("��������"), TEXT("���˹���"), MB_OK | MB_ICONINFORMATION);
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
 * ˵��: ���˶Ի�������̺���
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
			custom_list.InsertColumn(0, 120, "����");
			custom_list.InsertColumn(1, 80, "����");
			custom_list.InsertColumn(2, 50, "����");
			custom_list.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			CCustomerMenuForm order_info;
			order_info.GetCustomerMenuSet(table_info->customer_no.c_str());  // ���ù˿ͱ��
			int i = 0;
			float totle_cash = 0;
			while (!order_info.IsEOF()) {
				custom_list.InsertItem(i, order_info.dish_name());
				custom_list.SetItem(i, 1, order_info.dish_price());
				custom_list.SetItem(i, 2, order_info.dish_quantity());
				totle_cash += order_info.dish_price() * order_info.dish_quantity();
				i++;
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
						MessageBox(hwnd, TEXT("��������"), TEXT("��ʾ"), MB_OK | MB_ICONINFORMATION);
						return FALSE;
					} 
					if (check_out < 0) {
						TCHAR info[128] = "\0";
						sprintf(info, "���� %0.2f Ԫ", fabs(check_out));
						MessageBox(hwnd, info, TEXT("��ʾ"), MB_OK | MB_ICONINFORMATION);
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
			table.InsertColumn(1, 50, "����");
			table.SetSelectAndGrid(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
			table.set_new_process(ChangeTableListProc);
			g_change_table_list = table.old_process();
//			InitAvailableTable(hwnd, IDC_TABLE_AVAILABLE);
// 			CComboBox postion;
// 			postion.Initialization(hwnd, IDC_FLOOR);
// 			postion.AddString("һ¥");
// 			postion.InsertString(1, "��¥");
// 			postion.InsertString(2, "��¥");
// 			postion.SetCurSel(0);
//			GetTableInfo(hwnd, IDC_TABLE_AVAILABLE, "01");
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
// 						if ("һ¥" == text) {
// 							const char floor[] = "01";
// 							GetTableInfo(hwnd, IDC_TABLE_AVAILABLE, floor);
// 						} else if ("��¥" == text) {
// 							const char floor[] = "02";
// 							GetTableInfo(hwnd, IDC_TABLE_AVAILABLE, floor);
// 						} else if ("��¥" == text) {
// 							const char floor[] = "03";
// 							GetTableInfo(hwnd, IDC_TABLE_AVAILABLE, floor);
// 						}
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
 *  ˵��: ��̨�Ի�������̺���
 **/
BOOL CALLBACK StartTableProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static int payable_num(0);
	static std::string table_no;
	static UINT menu_id;   // �ϲ�Ի��򣬴������ľ��id
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
			menu_id = table_info->menu_id;
			
			char customer_no[128] = "\0";
			try {
				InitComboBox(hwnd, IDC_COMBO1); // ��ʼ��¥����Ϣ 
				CDBForm DB_time;
				srand((int)time(NULL));         // ��ȡ���ݿ�ʱ�䣬���ɹ˿ͱ��
				int rand_dom = rand() % 10;
				sprintf(customer_no, "%s%s%s%s%s%s%d", DB_time.GetYearString().c_str(),
						DB_time.GetMonthString().c_str(), DB_time.GetDayString().c_str(), 
						DB_time.GetHourString().c_str(), DB_time.GetMinuteString().c_str(),
						DB_time.GetSecondString().c_str(), rand_dom);
			} catch (Err &err) {
				MessageBox(hwnd, err.what(), TEXT("START TABLE PROC"), MB_ICONERROR);
				return FALSE;
			}
			SetDlgItemText(hwnd, IDC_CUSTOMER_NO_START, customer_no);  // ��ʾ�˿ͱ��
			
			CListView table, cus;
			table.Initialization(hwnd, IDC_START_TABLE);
			cus.Initialization(hwnd, IDC_CUSTOMER_TABLE);
			table.InsertColumn(0, 100, "����");
			table.InsertColumn(1, 100, "̨��");
			table.InsertColumn(2, 50, "����");
			cus.InsertColumn(0, 100, "¥��");
			cus.InsertColumn(1, 100, "����");
			cus.InsertColumn(2, 100, "̨��");
			cus.InsertColumn(3, 50, "����");
			table.SetSelectAndGrid(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
			cus.SetSelectAndGrid(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
			CComboBox combo(hwnd, IDC_COMBO1);
			std::string floor_name;
			combo.GetComboBoxText(floor_name);   // ��ȡ��ǰ��¥����
			try {
				InitTableList(hwnd, IDC_START_TABLE, floor_name.c_str(), 0);
			} catch (Err &err) {
				MessageBox(hwnd, err.what(), TEXT("START TABLE PROC"), MB_ICONERROR);
				return FALSE;
			}
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case ID_START_OK:   // ��̨
				{
				    char cus_no[32];   // �˿ͱ��
					memset(cus_no, 0, sizeof(cus_no));
					GetDlgItemText(hwnd, IDC_CUSTOMER_NO_START, cus_no, 32);  // ��ȡ�˿ͱ����Ϣ
					CListView customer_table;
					customer_table.Initialization(hwnd,  IDC_CUSTOMER_TABLE);
					int count = customer_table.GetItemCount();   // ��ȡ̨������
					CDBForm db;
					char sql[256] = "\0";
					std::string error;
					
					int status;
					if (menu_id == ID_START_OK) {   // �ж��ϲ�Ի����µİ�ť
						status = 0;
					} else {
						status = 1;
					}
					try {
						CCustomer consumer;
						consumer.AddCustomer(cus_no);
						
						for (int i = 0; i < count; ++i) {
							int real_people = atoi(customer_table.GetItem(i, 3).c_str());
							// ѭ������˿�̨�ű�
							CCustomer cus;
							cus.AddCustomerTable(cus_no, customer_table.GetItem(i, 0).c_str(),\
								                      customer_table.GetItem(i, 1).c_str(),\
													  customer_table.GetItem(i, 2).c_str(),\
													  real_people, status); 
							
						}
					} catch (Err &err) {
						MessageBox(hwnd, err.what(), TEXT("START TABLE PROC"), MB_ICONERROR);
						return FALSE;
					}
				}
			case ID_START_CANCEL:  // ȡ��
				{
					EndDialog(hwnd, LOWORD(wParam));
					break;
				}
			case IDC_ADD_TABLE:  // ����̨��
				{
					CListView table;
					table.Initialization(hwnd, IDC_START_TABLE);
					int select_row = table.GetSelectionMark();
					if (-1 == select_row) {
						MessageBox(hwnd, TEXT("��ѡ��̨�ţ�"), TEXT("��̨����"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					std::string num = table.GetItem(select_row, 2);   // ��ȡ̨�ſ����ɵ�����
					BOOL is_success;
					int real_num = GetDlgItemInt(hwnd, IDC_REAL_NUM_START, &is_success, FALSE);
					if (!is_success) {
						MessageBox(hwnd, TEXT("������������"), TEXT("��̨����"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					int pay_num = atoi(num.c_str());
					if (pay_num < real_num) {
						MessageBox(hwnd, TEXT("�����������ƣ�"), TEXT("��̨����"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					CListView customer_table;
					CComboBox floor(hwnd, IDC_COMBO1);
					std::string floor_name;
					floor.GetComboBoxText(floor_name);
					std::string room_name = table.GetItem(select_row, 0);
					std::string table_number = table.GetItem(select_row, 1);
					customer_table.Initialization(hwnd, IDC_CUSTOMER_TABLE);
					int floor_flag = customer_table.FindItem(floor_name);
					int room_flag = customer_table.FindItem(1, room_name);
					int table_flag = customer_table.FindItem(2, table_number);
					if (-1 != floor_flag &&  -1 !=  room_flag && -1 != table_flag) {
							MessageBox(hwnd, TEXT("�Ѵ��ڸ�̨�ţ�"), TEXT("��̨����"), MB_ICONINFORMATION);
							return FALSE;
					}
					customer_table.InsertItem(0, floor_name);
					customer_table.SetItem(0, 1, room_name);
					customer_table.SetItem(0, 2, table_number);
					customer_table.SetItem(0, 3, real_num);
					break;
				}
			case IDC_DELETE_TABLE:  // ɾ��̨��
				{
				    CListView customer_table;
					customer_table.Initialization(hwnd, IDC_CUSTOMER_TABLE);
					int select_row = customer_table.GetSelectionMark();
					if (-1 == select_row) {
						MessageBox(hwnd, TEXT("��ѡ��̨�ţ�"), TEXT("��̨����"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					if (IDYES == MessageBox(hwnd, TEXT("ȷ��Ҫɾ����̨��?"), TEXT("��̨����"), MB_YESNO)) {
						customer_table.DeleteItem(select_row);
					}
					break; 
				}
			case IDC_COMBO1:   // ¥��ѡ��
				{
					if (HIWORD(wParam) == CBN_SELCHANGE) {
						CComboBox combo;
						combo.Initialization(hwnd, IDC_COMBO1);
						std::string text;
						combo.GetComboBoxText(text);
						InitTableList(hwnd, IDC_START_TABLE, text.c_str(), 0);
					}
				}
			}
			return TRUE;
		}
	case IDOK:
		{
			MessageBox(hwnd, TEXT("IDOK"), TEXT("START TABLE PROC"), MB_ICONINFORMATION);
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
bool SetListInfo(const HWND hwnd, const UINT id, 
				 const char *find, std::string &error)
{
	CTableInfo table_info;
	CCustomer customer;
	if (!customer.GetRecordSet())
	{
		error = "��ȡ��¼��ʧ�ܣ�";
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
		list.SetItem(i, 1, TableStatus[customer.table_state()]);
		list.SetItem(i, 2, customer.customer_no());
		list.SetItem(i, 3, customer.founding_time()); 
		/* TODO: Add data time at here. */
		i++;
	}
	return true;
}

/*
 * @ brief: ��ʼ��table list ̨���й���Ϣ
 * @ param: hwnd [in] ���ھ��
 * @ param: id [in] listview id
 * @ parma; floor_name [in] ¥������
 * @ param: status [in] ̨��״̬
 * @ return: ���ɹ�����true
 **/
bool InitTableList(const HWND hwnd, int id, const char *floor_name, short status) {
	
	CListView table_list(hwnd, id);
	table_list.DeleteAllItems();
	table_list.Initialization(hwnd, id);
	CTableInfo table_form;
	table_form.GetStartTableSet(floor_name, status);
	int i = 0;
	while (!table_form.IsEOF()) {
		table_list.InsertItem(i, table_form.room_name());
		table_list.SetItem(i, 1, table_form.table_no());
		table_list.SetItem(i, 2, table_form.payable());
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

LRESULT CALLBACK ChangeTableListProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HINSTANCE hinstance = (HINSTANCE)GetWindowLong(GetParent(hwnd), GWL_HINSTANCE);
	switch (msg)
	{
	case WM_LBUTTONUP:
		{  
			HWND parent = GetParent(hwnd);
			CListView list_view(parent, IDC_TABLE_AVAILABLE);
			int select = list_view.GetSelectionMark();
			SetDlgItemText(parent, IDC_TABLE_NUM_NEW, list_view.GetItem(select, 0).c_str());
			SetDlgItemText(parent, IDC_PAYABLE_NUM_NEW, list_view.GetItem(select, 1).c_str());
			break;
		}
	}
	return CallWindowProc(g_change_table_list, hwnd, msg, wParam, lParam);
}

/*
 * @ brief: ��ʾ�˿�̨����Ϣ
 * @ param: hwnd [in] �����ھ��
 * @ param: id [in] ListView ID
 * @ return: �ɹ�����true�����򷵻�false
 **/
bool ShowConsumerTableInfo(const HWND hwnd, const UINT id, const char *floor_name) {
	CListView consumer_table(hwnd, id);
	consumer_table.DeleteAllItems();
	try {
		ConsumerTable consumer;
		consumer.GetConsumerTable(floor_name);
		int i = 0;
		while (!consumer.IsEOF()) {
			consumer_table.InsertItem(i, consumer.consumer_no());
			consumer_table.SetItem(i, 1, consumer.table_no());
			consumer_table.SetItem(i, 2, consumer.room_name());
			consumer_table.SetItem(i, 3, TableStatus[consumer.table_status()]);
			consumer_table.SetItem(i, 4, consumer.consumer_num());
			consumer_table.SetItem(i, 5, consumer.start_time());
			i++;
		}
	} catch (Err &err) {
		MessageBox(hwnd, err.what(), TEXT("SERVICE"), MB_ICONERROR);
		return false;
	}
	return true;
}