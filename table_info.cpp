#include "table_info.h"
#include "treectrl.h"
#include "ListView.h"
#include "resource.h"
#include "floorinfo.h"
#include "roominfo.h"


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
						info_tree.InsertChildItem(root_node, room_info.room_name());
					}  // end second while
				} // end first while 
			} catch(Err &err) {
				MessageBox(hwnd, err.what(), TEXT("TABLE INFO"), MB_ICONERROR);
				return FALSE;
			}
			return TRUE;
		}
	case WM_NOTIFY:
		{
			//			switch(LOWORD(wParam))
			//			{
			// 				case IDC_TREE_COMMODITY:
			// 					{
			// 						if (((LPNMHDR)lParam)->code == NM_DBLCLK) /*˫�����οؼ��е�һ��*/
			// 						{
			// 							HTREEITEM selection ;
			// 							selection = commodity_tree.GetSelectedItem();
			// 							commodity_tree.EnsureVisible(selection);
			// 							char text[256];
			// 							if (commodity_tree.GetItem(sizeof(text),text))
			// 							{
			// 								std::string error;
			// 								CCommodity commodity;/*��Ʒ������Ϣ*/
			// 								commodity.SelectByName(text, error);/*ͨ����Ʒ���ƻ���Ʒ�������Ʋ��Ҿ�����Ʒ*/
			// 							
			// 								CListView staff_list;
			// 								staff_list.Initialization(hwnd, IDC_BASIC_INFO);
			// 								staff_list.DeleteAllItems();
			// 								int item = 0;
			// 								while (!commodity.IsEOF())
			// 								{
			// 									staff_list.InsertItem(item, commodity.no());
			// 									staff_list.SetItem(item, 1, commodity.name());
			// 									staff_list.SetItem(item, 2, commodity.purchase_price());
			// 									staff_list.SetItem(item, 3, commodity.sum());
			// 									staff_list.SetItem(item, 4, commodity.unit());
			// 									staff_list.SetItem(item, 5, commodity.category());
			// 									staff_list.SetItem(item, 6, commodity.sale_price());
			// 									staff_list.SetItem(item, 7, commodity.register_date());
			// 									commodity.MoveNext();
			// 									item++;
			// 								}
			// 							}
			// 							else
			// 							{
			// 								MessageBox(hwnd, TEXT("Something Error!"), TEXT("HIT"), MB_ICONINFORMATION);
			// 							}	
			// 						}
			// 						break;
			// 					}
			//			}
			return TRUE;
		}
	}
	return FALSE;
}
