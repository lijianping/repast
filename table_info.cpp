#include "table_info.h"
#include "treectrl.h"
#include "ListView.h"
#include "resource.h"
#include "floorinfo.h"
#include "roominfo.h"
#include "TableInfo.h"


BOOL CALLBACK TableInfoProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE hInstance;
	switch (msg)
	{
	case WM_INITDIALOG:
		{
			hInstance = (HINSTANCE)lParam;
			TreeCtrl info_tree(hwnd, IDC_T_TABLE_INFO);
			try {
				FloorInfo floor_info;
				floor_info.GetFloorName();     // ��ȡ¥�����Ƽ�¼��
				while (!floor_info.IsEOF()) {  // ѭ��ȡ������
					std::string floor_name(floor_info.floor_name());  // ��ȡ¥������
					HTREEITEM root_node = info_tree.InsertRootItem(floor_name.c_str());  // ������ڵ�
					RoomInfo room_info;
					room_info.GetRoomName(floor_name.c_str());  // ��ȡ¥���µķ������Ƽ�¼��
					while (!room_info.IsEOF()) {
						info_tree.InsertChildItem(root_node, room_info.room_name());  // �����ӽڵ�
					}  // end second while
				} // end first while 
			} catch(Err &err) {
				MessageBox(hwnd, err.what(), TEXT("TABLE INFO"), MB_ICONERROR);
				return FALSE;
			}
			// ��ʼ��Listview
			CListView table_list(hwnd, IDC_L_TABLE_INFO);
			table_list.InsertColumn(0, 100, "̨��");
			table_list.InsertColumn(1, 100, "״̬");
			table_list.InsertColumn(2, 100, "����������");
			table_list.SetExtendStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			return TRUE;
		}
	case WM_NOTIFY:
		{
			switch (LOWORD(wParam)) {
			case IDC_T_TABLE_INFO:
				{
					if (((LPNMHDR)lParam)->code == NM_DBLCLK) {
						TreeCtrl info_tree(hwnd, IDC_T_TABLE_INFO);
						HTREEITEM select = info_tree.GetSelectedItem();
						if (select) {
							char item_text[512];
							info_tree.GetItem(select, 512, item_text);
							if (info_tree.GetParent(select)) {
							//	MessageBox(hwnd, TEXT("has parent!"), TEXT("TABLE INFOR"), MB_ICONINFORMATION);
								char parent_item_text[512];
								info_tree.GetItem(info_tree.GetParent(select), 512, parent_item_text); // ��ȡ���ڵ���Ϣ
								try {
									CTableInfo table_info;
									table_info.GetTableInfoSet(parent_item_text, item_text);
									CListView table_list(hwnd, IDC_L_TABLE_INFO);
									table_list.DeleteAllItems();  // ���ListView
									int i = 0;
									while (!table_info.IsEOF()) {
										table_list.InsertItem(i, table_info.table_no());
										table_list.SetItem(i, 1, TableStatus[table_info.status()]);
										table_list.SetItem(i, 2, table_info.payable());
										i++;
									}
								} catch (Err &err) {
									MessageBox(hwnd, err.what(), TEXT("TABLE INFOR"), MB_ICONINFORMATION);
									return FALSE;
								}
							} else {
							//	MessageBox(hwnd, TEXT("no parent!"), TEXT("TABLE INFOR"), MB_ICONINFORMATION);
								try {
									CTableInfo table_info;
									table_info.GetTableInfoSet(item_text);
									CListView table_list(hwnd, IDC_L_TABLE_INFO);
									table_list.DeleteAllItems();  // ���ListView
									int i = 0;
									while (!table_info.IsEOF()) {   // ѭ������table��Ϣ
										table_list.InsertItem(i, table_info.table_no());
										table_list.SetItem(i, 1, TableStatus[table_info.status()]);
										table_list.SetItem(i, 2, table_info.payable());
										i++;
									}
								} catch (Err &err) {
									MessageBox(hwnd, err.what(), TEXT("TABLE INFOR"), MB_ICONINFORMATION);
									return FALSE;
								}
							} // end else
						}  // end  second if
					}  // end first if
				}
				break;
			}
			return TRUE;
		}
	}
	return FALSE;
}