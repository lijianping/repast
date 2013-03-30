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
#include "hildCateForm.h"
#include "ComMainCateForm.h"
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
				InitFloorName(hwnd, ID_SERVICE_COMBO); // ��ʼ��¥��Combo box
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
				table_info.customer_no = table_list.GetItem(select_row, 0);        // ��ȡ�˿ͱ��
				table_info.table_no = table_list.GetItem(select_row, 1);           // ��ȡ̨��
				table_info.room_name = table_list.GetItem(select_row, 2);          // ��ȡ��������
				table_info.table_state = table_list.GetItem(select_row, 3);        // ��ȡ̨��״̬
				table_info.customer_num = table_list.GetItem(select_row, 4);       // ��ȡ�˿�����
				table_info.start_time = table_list.GetItem(select_row, 5);         // ��ȡ��̨ʱ��
				CComboBox combo(hwnd, ID_SERVICE_COMBO);
				combo.GetComboBoxText(table_info.floor_name);                      // ��ȡ¥������
				DialogBoxParam(hinstance, MAKEINTRESOURCE(IDD_CHANGE_TABLE),
							   hwnd, (DLGPROC)ChangeTableProc, (long)&table_info);
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
					CustomerTable table_info;
					table_info.customer_no = table_list.GetItem(select_row, 0);        // ��ȡ�˿ͱ��
					table_info.table_no = table_list.GetItem(select_row, 1);           // ��ȡ̨��
					table_info.room_name = table_list.GetItem(select_row, 2);          // ��ȡ��������
					table_info.table_state = table_list.GetItem(select_row, 3);        // ��ȡ̨��״̬
					table_info.customer_num = table_list.GetItem(select_row, 4);       // ��ȡ�˿�����
					table_info.start_time = table_list.GetItem(select_row, 5);         // ��ȡ��̨ʱ��
					CComboBox combo(hwnd, ID_SERVICE_COMBO);
					combo.GetComboBoxText(table_info.floor_name);                      // ��ȡ¥������
				
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
					table_info.customer_no = table_list.GetItem(select_row, 0);        // ��ȡ�˿ͱ��
					table_info.table_no = table_list.GetItem(select_row, 1);           // ��ȡ̨��
					table_info.room_name = table_list.GetItem(select_row, 2);          // ��ȡ��������
					table_info.table_state = table_list.GetItem(select_row, 3);        // ��ȡ̨��״̬
					table_info.customer_num = table_list.GetItem(select_row, 4);       // ��ȡ�˿�����
					table_info.start_time = table_list.GetItem(select_row, 5);         // ��ȡ��̨ʱ��
					CComboBox combo(hwnd, ID_SERVICE_COMBO);
					combo.GetComboBoxText(table_info.floor_name);                      // ��ȡ¥������
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
 * @ brief: ��ʼ��¥����Ϣ������
 * @ param: hwnd [in] �����ھ��
 * @ param: id [in] ����id
 * @ return: �ɹ�����true
 */
bool InitFloorName(const HWND hwnd, int id)
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
	static PCUSTOMERTABLE table;
    static bool is_change = false;   // �˿Ͳ˵��Ƿ��ţ���Ϊtrue����ʾ�˵��ѱ仯
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
			table = (PCUSTOMERTABLE)lParam;
			CEdit cus_no(hwnd, IDC_CUSTOM_NUM);
			cus_no.SetEditText(table->customer_no);  // ��ʾ�˿ͱ��
			CListView menu_list, custom_list;
			menu_list.Initialization(hwnd, IDC_REPAST_MENU);
			g_dialog_menu_proc = menu_list.SetListProc(OrderMenuListProc); // ������Ĭ�ϵĴ��ڴ������ 
			menu_list.InsertColumn(0, 100, "����");
			menu_list.InsertColumn(1, 60, "����");
			menu_list.InsertColumn(2, 50, "��λ");
			menu_list.SetExtendStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

			custom_list.Initialization(hwnd, IDC_CUSTOM_MENU);
			custom_list.InsertColumn(0, 100, "����");
			custom_list.InsertColumn(1, 60, "����");
			custom_list.InsertColumn(2, 50, "����");
			custom_list.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			// ��ʼ���οؼ�
			TreeCtrl tree(hwnd, IDC_MENU_TREE);
			HTREEITEM tree_parent;
			std::string error;
			try {
				ComMainCateForm comodity_main;//����Ʒ����
				comodity_main.GetMainCateName();
				while(!comodity_main.IsEOF())
				{
					std::string main_name(comodity_main.name());
					tree_parent = tree.InsertRootItem(main_name.c_str()); // ����������ڵ�
					ChildCateForm comdity_child;//����Ʒ����
					if (comdity_child.GetChildCateName(comodity_main.name(), error)) {       // ��ȡ�������Ӧ���ӷ�������
						while(!comdity_child.IsEOF()) {
							std::string child_name(comdity_child.cate_name());
							HTREEITEM child_node;
							// ������Ʒ�������Ʋ�ѯ��Ʒ���ٲ�����Ӧ�ĸ��ڵ���
							child_node = tree.InsertChildItem(tree_parent, child_name.c_str());
						}
					}
				} 
				CCustomerMenuForm consumer_menu;
				consumer_menu.GetCustomerMenuSet(table->customer_no.c_str());
				int i = 0;
				while (!consumer_menu.IsEOF()) {
					custom_list.InsertItem(i, consumer_menu.commodity_name());
					custom_list.SetItem(i, 1, consumer_menu.commodity_price());
					custom_list.SetItem(i, 2, consumer_menu.quantity());
					i++;
				}
			} catch(Err &err) {
				MessageBox(hwnd, err.what(), TEXT("��Ʒ����"), MB_ICONERROR);
				return FALSE;
			}
			return TRUE;
		}
	case WM_NOTIFY:
		{
			switch(LOWORD(wParam))
			{
			case IDC_MENU_TREE:
				{
					if (((LPNMHDR)lParam)->code == NM_DBLCLK) {  // ˫�����οؼ��е�һ��
						TreeCtrl commodity_tree(hwnd, IDC_MENU_TREE);
						HTREEITEM select = commodity_tree.GetSelectedItem();
						if (!select) {  // Ϊ�գ��˳�
							break;
						}
						char select_item_text[512];
						commodity_tree.GetItem(select, 512, select_item_text);
						HTREEITEM parent_node = commodity_tree.GetParent(select);   // ��ȡ���ڵ�
						if (parent_node) {  // ��ʾ�η���������
							char parent_item_text[512];
							commodity_tree.GetItem(parent_node, 512, parent_item_text); // ��ȡ���ڵ�����
							try {
								CCommodity commodity_info;
								commodity_info.GetCommodityNameSet(parent_item_text, select_item_text);
								CListView menu_list(hwnd, IDC_REPAST_MENU);
								menu_list.DeleteAllItems();
								int i = 0;
								while (!commodity_info.IsEOF()) {
									menu_list.InsertItem(i, commodity_info.name());
									menu_list.SetItem(i, 1, commodity_info.sale_price());
									menu_list.SetItem(i, 2, commodity_info.unit());
									i++;
								}
							} catch (Err &err) {
								MessageBox(hwnd, err.what(), TEXT("SERVICE"), MB_ICONINFORMATION);
								return FALSE;
							}  
						} else {   // ��ʾ������������
							try {
								CCommodity commodity_info;
								commodity_info.GetCommodityNameSet(select_item_text);
								CListView menu_list(hwnd, IDC_REPAST_MENU);
								menu_list.DeleteAllItems();
								int i = 0;
								while (!commodity_info.IsEOF()) {
									menu_list.InsertItem(i, commodity_info.name());
									menu_list.SetItem(i, 1, commodity_info.sale_price());
									menu_list.SetItem(i, 2, commodity_info.unit());
									i++;
								}
							} catch (Err &err) {
								MessageBox(hwnd, err.what(), TEXT("SERVICE"), MB_ICONINFORMATION);
								return FALSE;
							} 
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
			case IDC_ADD_DISH:  // �����Ʒ
				{
					// ��ʼ���б�ؼ� 
					CListView menu_list(hwnd, IDC_REPAST_MENU), customer_list(hwnd, IDC_CUSTOM_MENU);
					// ��ȡ�˵��б��е��� 
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
					// ��ȡ�˿͵����Ϣ������˿͵���б� */
					std::string dish_name = menu_list.GetItem(select_row, 0);
					int ret = customer_list.FindItem(dish_name);
					if (-1 == customer_list.FindItem(dish_name)) {
						customer_list.InsertItem(0, dish_name);   // ��ȡ����
						customer_list.SetItem(0, 1, menu_list.GetItem(select_row, 1)); // ��ȡ����
						customer_list.SetItem(0, 2, num);  // ��ȡ����
						is_change = true;   // �˿Ͳ˵��Ƿ�仯��־
					} else {
						MessageBox(hwnd, TEXT("���Ѿ��������Ʒ��"), TEXT("ǰ̨����"), MB_ICONINFORMATION);
					}
					break;
				}
			case IDC_DELETE_DISH:  // ɾ����Ʒ
				{
					CListView customer_list;
					CCustomerMenuForm customer_menu;
					customer_list.Initialization(hwnd, IDC_CUSTOM_MENU);
					int select_row = customer_list.GetSelectionMark();
					if (-1 == select_row) {
						MessageBox(hwnd, TEXT("����ѡ����Ҫɾ������Ʒ��"), TEXT("ǰ̨����"), MB_ICONINFORMATION);
						break;
					} 
					if (IDYES == MessageBox(hwnd, TEXT("�Ƿ�Ҫ�Ƴ�����Ʒ��"), TEXT("ǰ̨����"), MB_YESNO)) {
						customer_list.DeleteItem(select_row);
						is_change = true;    // �˿Ͳ˵��Ƿ�仯��־
					}
					break;
				}
			case IDC_SAVE_MENU:  // �������
				{
					CListView customer_list(hwnd, IDC_CUSTOM_MENU);
					int count = customer_list.GetItemCount();  // ��Ʒ������
					if (!is_change) {
						MessageBox(hwnd, TEXT("��δ�����κ��޸ģ�"), TEXT("�����ʾ"), MB_OK);
						break;
					}
					CEdit cus_no(hwnd, IDC_CUSTOM_NUM);
					std::string customer_no;  // �˿ͱ��
					cus_no.GetEditText(customer_no);   // ��ȡ�˿ͱ��
					if(count) {
						bool is_ok = false;     // �����Ƿ�ɹ�
						try {
							CCustomerMenuForm customer_info;
							customer_info.DeleteCustomerMenu(customer_no.c_str());   // ɾ���û��˵�
							for (int i = 0; i < count; ++i) {
								CCustomerMenuForm test;
								std::string commodity_name = customer_list.GetItem(i, 0);  // ��ȡ��Ʒ����
								std::string quantity_str = customer_list.GetItem(i, 2);    // ��ȡ��Ʒ����
								int quantity = atoi(quantity_str.c_str());
								is_ok = test.AddCustomerMenu(customer_no.c_str(), commodity_name.c_str(), quantity);
								if (!is_ok) {
									break;
								}
							}
							if (is_ok) {
								MessageBox(hwnd, TEXT("��˳ɹ���"), TEXT("ǰ̨����"), MB_ICONINFORMATION);
							} else {
								MessageBox(hwnd, TEXT("�˵�����ʧ�ܣ�"), TEXT("ǰ̨����"), MB_ICONINFORMATION);
							}
						} catch (Err &err) {
							MessageBox(hwnd, err.what(), TEXT("ǰ̨����"), MB_ICONERROR);
							return FALSE;
						}  
					} else {
						try {
						CCustomerMenuForm customer_info;
						customer_info.DeleteCustomerMenu(customer_no.c_str());   // ɾ���û��˵�
						} catch (Err &err) {
							MessageBox(hwnd, err.what(), TEXT("ǰ̨����"), MB_ICONERROR);
							return FALSE;
						}
						MessageBox(hwnd, TEXT("����ɹ���"), TEXT("ǰ̨����"), MB_ICONINFORMATION);
					}
					is_change = false; // ����
					
					break;
				}
			case IDC_CANCEL_MENU:  // ȡ������
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
				MessageBox(hwnd, TEXT("���ȱ�������!"), TEXT("ǰ̨����"), MB_ICONINFORMATION);
				return FALSE;
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
	static CUSTOMERTABLE send_in;
	switch (msg)
	{
	case WM_INITDIALOG:
		{
			RECT rect;
			if (!GetWindowRect(hwnd, &rect)) {
				MessageBox(hwnd, TEXT("Get rect failed!"), TEXT("ERROR"), MB_ICONINFORMATION | MB_OK);
				return FALSE;
			}
			int width = rect.right - rect.left;
			int height = rect.bottom - rect.top;
			int screen_width = GetSystemMetrics(SM_CXFULLSCREEN);
			int screen_height = GetSystemMetrics(SM_CYFULLSCREEN);
			MoveWindow(hwnd, (screen_width - width) / 2, (screen_height - height) / 2, width, height, TRUE);
			PCUSTOMERTABLE table_info;
			table_info = (PCUSTOMERTABLE)lParam;
			send_in.customer_no = table_info->customer_no;
			CEdit cus_no(hwnd, IDC_CUSTOM_NUM_CHECKOUT);
			cus_no.SetEditText(table_info->customer_no);   // ��ʾ�˿ͱ��
			
			CListView custom_list;
			custom_list.Initialization(hwnd, IDC_MENU_CHEKOUT);
			custom_list.InsertColumn(0, 120, "����");
			custom_list.InsertColumn(1, 80, "����");
			custom_list.InsertColumn(2, 50, "����");
			custom_list.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		
			// TODO: ��ѯ���ݿ⣬��ȡ�˿͵����Ϣ
			HWND edit = GetDlgItem(hwnd, IDC_PAIDIN_CHECKOUT);
			SetFocus(edit);
			g_checkout_edit_proc = (WNDPROC)SetWindowLong(edit, GWL_WNDPROC, (LONG)EditProc);
			float totle_cash = 0;
			try {
				CCustomerMenuForm consumer_menu;
				consumer_menu.GetCustomerMenuSet(table_info->customer_no.c_str());
				int i = 0;
				while (!consumer_menu.IsEOF()) {
					float price = consumer_menu.commodity_price();
					short quantity = consumer_menu.quantity();
					custom_list.InsertItem(i, consumer_menu.commodity_name());
					custom_list.SetItem(i, 1, price);
					custom_list.SetItem(i, 2, quantity);
					totle_cash += quantity * price;
					i++;
				}
			} catch (Err &err) {
				MessageBox(hwnd, err.what(), TEXT("ǰ̨����"), MB_ICONERROR);
				return FALSE;
			}
			CEdit totle(hwnd, IDC_RECEIVALBE_CHECKOUT);
			char temp[64];
			sprintf(temp, "%0.2f", totle_cash);
			totle.SetEditText(temp);
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_SAVE_CHECKOUT: 
				{
					HWND pad_hwnd = GetDlgItem(hwnd, IDC_PAIDIN_CHECKOUT);
					PostMessage(pad_hwnd, WM_KEYDOWN, VK_F5, 1);
					TCHAR totle[64] = "\0", more[64] = "\0";
					int ret1 = GetDlgItemText(hwnd, IDC_RECEIVALBE_CHECKOUT, totle, 64);  // ��ȡ����
					int ret2 = GetDlgItemText(hwnd, IDC_GIVECHANGE_CHECKOUT, more, 64);
					float check_in = atof(totle);
					float check_out = atof(more);
					if (!ret1 || !ret2) {
						MessageBox(hwnd, TEXT("��������"), TEXT("ǰ̨����"), MB_OK | MB_ICONINFORMATION);
						return FALSE;
					} 
					if (check_out < 0) {
						TCHAR info[128] = "\0";
						sprintf(info, "���� %0.2f Ԫ", fabs(check_out));
						MessageBox(hwnd, info, TEXT("ǰ̨����"), MB_OK | MB_ICONINFORMATION);
						return FALSE;
					} else if (check_out > 0) {
						TCHAR info[128] = "\0";
						sprintf(info, "���� %0.2f Ԫ",check_out);
						MessageBox(hwnd, info, TEXT("ǰ̨����"), MB_OK | MB_ICONINFORMATION);
					}
					try {   // ��������
						CCustomer consumer;
						consumer.CheckOut(send_in.customer_no.c_str() ,g_login_name.c_str(), check_in);
					} catch (Err &err) {
						MessageBox(hwnd, err.what(), TEXT("ǰ̨����"), MB_ICONERROR);
						return FALSE;
					}
					MessageBox(hwnd, TEXT("���ʳɹ���"), TEXT("ǰ̨����"), MB_ICONINFORMATION);
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
BOOL CALLBACK ChangeTableProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static CUSTOMERTABLE recive;  // ���յ��Ĺ˿���Ϣ
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
			ReciveConsumerTableInfo((PCUSTOMERTABLE)lParam, &recive);
			SetDlgItemText(hwnd, IDC_OLD_FLOOR, recive.floor_name.c_str());  // ¥����Ϣ
			SetDlgItemText(hwnd, IDC_OLD_ROOM, recive.room_name.c_str());    // ������Ϣ
			SetDlgItemText(hwnd, IDC_TABLE_NUM_OLD, recive.table_no.c_str());// ̨����Ϣ
			SetDlgItemText(hwnd, IDC_OLD_PEOPLE_NUM, recive.customer_num.c_str());  // �˿�����
			CListView table;
			table.Initialization(hwnd, IDC_TABLE_AVAILABLE);
			table.InsertColumn(0, 100, "����");
			table.InsertColumn(1, 100, "̨��");
			table.InsertColumn(2, 50, "����");
			table.SetSelectAndGrid(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
			table.set_new_process(ChangeTableListProc);
			g_change_table_list = table.old_process();
			try {
				InitFloorName(hwnd, IDC_FLOOR);
			} catch (Err &err) {
				MessageBox(hwnd, err.what(), TEXT("CHANGE TABLE"), MB_ICONERROR);
				return FALSE;
			}
			CComboBox combo(hwnd, IDC_FLOOR);
			std::string floor_name;
			combo.GetComboBoxText(floor_name);   // ��ȡ��ǰ��¥����
			try {
				InitTableList(hwnd, IDC_TABLE_AVAILABLE, floor_name.c_str(), 0);
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
			case IDC_SAVE_CHANGE:
				{
					CEdit edit(hwnd, IDC_NEW_FLOOR);
					std::string floor_name, room_name, table_no;
					edit.GetEditText(floor_name);
					edit.Initialization(hwnd, IDC_NEW_ROOM);
					edit.GetEditText(room_name);
					edit.Initialization(hwnd, IDC_NEW_TABLE_NO);
					edit.GetEditText(table_no);
					std::string old_floor_name, old_room_name, old_table_no;
					edit.Initialization(hwnd, IDC_OLD_FLOOR);
					edit.GetEditText(old_floor_name);
					edit.Initialization(hwnd, IDC_OLD_ROOM);
					edit.GetEditText(old_room_name);
					edit.Initialization(hwnd, IDC_OLD_TABLE_NO);
					edit.GetEditText(old_table_no);
					BOOL is_ok;
					int people_num = GetDlgItemInt(hwnd, IDC_NEW_PEOPLE_NUM, &is_ok, FALSE);
					if (!is_ok) {
						MessageBox(hwnd, TEXT("��ȡ����ʧ�ܣ�"), TEXT("ǰ̨����"), MB_ICONINFORMATION);
						return FALSE;
					}
					int payable = GetDlgItemInt(hwnd, IDC_NEW_PEOPLE_NUM2, &is_ok, FALSE);
					if (people_num > payable) {
						MessageBox(hwnd, TEXT("�����������ƣ�"), TEXT("ǰ̨����"), MB_ICONINFORMATION);
						return FALSE;
					}
					int table_state;
					if (recive.table_state == "�ѿ�̨") {
						table_state = 1;
					} else {
						table_state = 2;
					}
					try {
						CCustomer consumer;
						consumer.ChangeTable(old_floor_name.c_str(), old_room_name.c_str(), old_table_no.c_str(),\
							                 floor_name.c_str(), room_name.c_str(), table_no.c_str(),\
											 recive.customer_no.c_str(), people_num, table_state);
					} catch(Err &err) {
						MessageBox(hwnd, err.what(), TEXT("ǰ̨����"), MB_ICONERROR);
						return FALSE;
					}
					MessageBox(hwnd, TEXT("��̨�ɹ�"), TEXT("ǰ̨����"), MB_ICONINFORMATION);
				}
			case IDC_CANCLE_CHANGE:
				{
					EndDialog(hwnd, LOWORD(wParam));
					break;
				}
			case IDC_FLOOR:   // ��̨�Ի���¥������
				{
					if (HIWORD(wParam) == CBN_SELCHANGE) {
						CComboBox combo;
						combo.Initialization(hwnd, IDC_FLOOR);
						std::string floor_name;
						combo.GetComboBoxText(floor_name);
						try {
							InitTableList(hwnd, IDC_TABLE_AVAILABLE, floor_name.c_str(), 0);
						} catch (Err &err) {
							MessageBox(hwnd, err.what(), TEXT("START TABLE PROC"), MB_ICONERROR);
							return FALSE;
						}
						break;
					}  // end if
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
				InitFloorName(hwnd, IDC_COMBO1); // ��ʼ��¥����Ϣ 
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
			CComboBox combo(parent, IDC_FLOOR);
			std::string floor_name;
			combo.GetComboBoxText(floor_name);
			SetDlgItemText(parent, IDC_NEW_FLOOR, floor_name.c_str());
			CListView list_view(parent, IDC_TABLE_AVAILABLE);
			int select = list_view.GetSelectionMark();
			SetDlgItemText(parent, IDC_NEW_ROOM, list_view.GetItem(select, 0).c_str());
			SetDlgItemText(parent, IDC_NEW_TABLE_NO, list_view.GetItem(select, 1).c_str());
			SetDlgItemInt(parent, IDC_NEW_PEOPLE_NUM2, atoi(list_view.GetItem(select, 2).c_str()), FALSE);
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

/*
 * @ brief: ���ո����ڴ����Ĺ˿�̨����Ϣ
 * @ param: send_in [in] �����Ĺ˿�̨����Ϣ
 * @ param: revice [out] ���յĹ˿�̨����Ϣ
 **/
void ReciveConsumerTableInfo(PCUSTOMERTABLE send_in, PCUSTOMERTABLE revice) {
	revice->customer_no = send_in->customer_no;
	revice->customer_num = send_in->customer_num;
	revice->floor_name = send_in->floor_name;
	revice->menu_id = send_in->menu_id;
	revice->room_name = send_in->room_name;
	revice->start_time = send_in->start_time;
	revice->table_no =send_in->table_no;
	revice->table_state =send_in->table_state;
}