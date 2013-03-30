#include "table_info.h"
#include "treectrl.h"
#include "ListView.h"
#include "resource.h"
#include "floorinfo.h"
#include "roominfo.h"
#include "TableInfo.h"

extern HINSTANCE g_hinstance;
extern bool InitFloorName(const HWND hwnd, int id);
extern bool InitTableList(const HWND hwnd, int id, const char *floor_name, short status);

BOOL CALLBACK TableInfoProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE hInstance;
	switch (msg)
	{
	case WM_INITDIALOG:
		{
			hInstance = (HINSTANCE)lParam;
	//		hInstance = (HINSTANCE)GetWindowLong(GetParent(hwnd), GWL_HINSTANCE);
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
//								MessageBox(hwnd, TEXT("has parent!"), TEXT("TABLE INFOR"), MB_ICONINFORMATION);
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
//								MessageBox(hwnd, TEXT("no parent!"), TEXT("TABLE INFOR"), MB_ICONINFORMATION);
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
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_B_FLOOR://¥�����
				{
	        		DialogBox(hInstance,MAKEINTRESOURCE(IDD_EDIT_FLOOR),hwnd,(DLGPROC)FloorInfoProc);
					break;
				}
			case IDC_B_ROOM:
				{
					DialogBox(hInstance, MAKEINTRESOURCE(IDD_EDIT_ROOM), hwnd, (DLGPROC)RoomInfoProc);
					break;
				}
			}
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CALLBACK FloorInfoProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_INITDIALOG:
		{
	        CListView floor_list(hwnd, IDC_L_FLOOR_INFO);
			floor_list.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			floor_list.InsertColumn(1,100,"¥����");
			floor_list.InsertColumn(2,100,"¥������");
			try {
			    ShowFloorList(hwnd);
			} catch (Err &err) {
				MessageBox(hwnd, err.what(), TEXT("������Ϣ����"), MB_ICONERROR);
				return FALSE;
			}
			return TRUE;
		}
	case  WM_NOTIFY:
		{
			switch(LOWORD(wParam))
			{
			case IDC_L_FLOOR_INFO:
				{
					if (((LPNMHDR)lParam)->code == NM_CLICK)/*����б��е�һ��*/
					{
						int index=0;
						CEdit e_name,e_id;
						CListView floor_list;
						floor_list.Initialization(hwnd, IDC_L_FLOOR_INFO);
						e_id.Initialization(hwnd, IDC_E_FLOOR_ID);
						e_name.Initialization(hwnd, IDC_E_FLOOR_NAME);
						index = floor_list.GetSelectionMark();
						e_id.SetEditText(floor_list.GetItem(index,0));
						e_name.SetEditText(floor_list.GetItem(index,1));
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
			case IDC_B_FLOOR_ADD:
				{
					try {
						AddFloor(hwnd);
						ShowFloorList(hwnd);
					} catch (Err &err) {
						MessageBox(hwnd, err.what(), TEXT("������Ϣ����"), MB_ICONERROR);
						return FALSE;
					}
					break;
				}
			case IDC_B_FLOOR_MODIFY:
				{
					try {
						UpdateFloor(hwnd);
						ShowFloorList(hwnd);
					} catch (Err &err) {
						MessageBox(hwnd, err.what(), TEXT("������Ϣ����"), MB_ICONERROR);
						return FALSE;
					}
					break;
				}
			case IDC_B_FLOOR_DELETE:
				{
					try {
						DeleteFloor(hwnd);
						ShowFloorList(hwnd);
					} catch (Err &err) {
						MessageBox(hwnd, err.what(), TEXT("������Ϣ����"), MB_ICONERROR);
						return FALSE;
					}
					break;
				}
			case IDC_B_FLOOR_CANCEL:
				{
					EndDialog(hwnd,0);
					break;
				}
			}
			return TRUE;
		}
	case WM_CLOSE:
		{
			EndDialog(hwnd,0);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CALLBACK RoomInfoProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static std::string old_room_no;   // ԭ������
	switch(msg)
	{
	case WM_INITDIALOG:
		{
			CListView floor_list(hwnd, IDC_L_ROOM_INFO);
			floor_list.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			floor_list.InsertColumn(1,80,"������");
			floor_list.InsertColumn(2,100,"��������");
			try {
				InitFloorName(hwnd, IDC_FLOOR_COMBO);
				CComboBox combo(hwnd, IDC_FLOOR_COMBO);
				std::string floor_name;
				combo.GetComboBoxText(floor_name);
				ShowRoomInfo(hwnd, IDC_L_ROOM_INFO, floor_name.c_str());
			} catch (Err &err) {
				MessageBox(hwnd, err.what(), TEXT("������Ϣ����"), MB_ICONERROR);
				return FALSE;
			}
			return TRUE;
		}
	case  WM_NOTIFY:
		{
			switch(LOWORD(wParam))
			{
			case IDC_L_ROOM_INFO:
				{
					if (((LPNMHDR)lParam)->code == NM_CLICK)/*����б��е�һ��*/
					{
						int index=0;
						CEdit e_name,e_id;
						CListView room_list;
						room_list.Initialization(hwnd, IDC_L_ROOM_INFO);
						e_id.Initialization(hwnd, IDC_E_ROOM_NO);
						e_name.Initialization(hwnd, IDC_E_ROOM_NAME);
						index = room_list.GetSelectionMark();
						old_room_no = room_list.GetItem(index,0);   // ��ȡ���еķ����ţ��޸�ʱ��
						e_id.SetEditText(old_room_no);
						e_name.SetEditText(room_list.GetItem(index,1));
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
			case IDC_B_ADD_ROOM:
				{
					CComboBox combo(hwnd, IDC_FLOOR_COMBO);
					std::string floor_name, room_no, room_name;
					combo.GetComboBoxText(floor_name);
					CEdit edit(hwnd, IDC_E_ROOM_NO);
					edit.GetEditText(room_no);
					if (room_no.length() > 2) {
						MessageBox(hwnd, TEXT("��Ź�����\n��������λ��"), TEXT("������Ϣ����"), MB_ICONINFORMATION);
						break;
					}
					edit.Initialization(hwnd, IDC_E_ROOM_NAME);
					edit.GetEditText(room_name);
					try {
						RoomInfo room;
						room.AddRoom(floor_name.c_str(), room_no.c_str(), room_name.c_str());
						MessageBox(hwnd, TEXT("������Ϣ��ӳɹ�!"), TEXT("������Ϣ����"), MB_ICONINFORMATION);
					} catch (Err &err) {
						MessageBox(hwnd, err.what(), TEXT("������Ϣ����"), MB_ICONERROR);
						return FALSE;
					}
					break;
				}
			case IDC_B_MODITY_ROOM:
				{
					CComboBox combo(hwnd, IDC_FLOOR_COMBO);
					std::string floor_name, room_no, room_name;
					combo.GetComboBoxText(floor_name);
					CEdit edit(hwnd, IDC_E_ROOM_NO);
					edit.GetEditText(room_no);       // ��ȡ�޸ĵķ�����
					if (room_no.length() > 2) {
						MessageBox(hwnd, TEXT("��Ź�����\n��������λ��"), TEXT("������Ϣ����"), MB_ICONINFORMATION);
						break;
					}
					edit.Initialization(hwnd, IDC_E_ROOM_NAME);
					edit.GetEditText(room_name);   // ��ȡ�޸ĵķ�������
					try {
						RoomInfo room;
						room.ModifyRoom(floor_name.c_str(), old_room_no.c_str(), room_no.c_str(), room_name.c_str());
						MessageBox(hwnd, TEXT("������Ϣ�޸ĳɹ�!"), TEXT("������Ϣ����"), MB_ICONINFORMATION);
					} catch (Err &err) {
						MessageBox(hwnd, err.what(), TEXT("������Ϣ����"), MB_ICONERROR);
						return FALSE;
					}
					break;
				}
			case IDC_B_DELETE_ROOM:
				{
					CListView room_list(hwnd, IDC_L_ROOM_INFO);
					int select = room_list.GetSelectionMark();
					if (-1 == select) {
						MessageBox(hwnd, TEXT("��������б��ѡ��Ҫɾ���ķ�����!"), TEXT("������Ϣ����"), MB_ICONINFORMATION);
						break;
					}
					std::string room_no, floor_name;
					room_no = room_list.GetItem(select, 0);    // ��ȡ������
					CComboBox combo(hwnd, IDC_FLOOR_COMBO);
					combo.GetComboBoxText(floor_name);         // ��ȡ¥������
					try {
						RoomInfo room;
						room.DeleteRoom(floor_name.c_str(), room_no.c_str());
						MessageBox(hwnd, TEXT("������Ϣɾ���ɹ�!"), TEXT("������Ϣ����"), MB_ICONINFORMATION);
					} catch (Err &err) {
						MessageBox(hwnd, err.what(), TEXT("������Ϣ����"), MB_ICONERROR);
						return FALSE;
					}
					break;
				}
			case IDC_B_ROOM_CANCEL:
				{
					EndDialog(hwnd,0);
					break;
				}
			case IDC_FLOOR_COMBO:
				{
					if (HIWORD(wParam) == CBN_SELCHANGE) {
						try {
							CComboBox combo(hwnd, IDC_FLOOR_COMBO);
							std::string floor_name;
							combo.GetComboBoxText(floor_name);
							ShowRoomInfo(hwnd, IDC_L_ROOM_INFO, floor_name.c_str());
						} catch (Err &err) {
							MessageBox(hwnd, err.what(), TEXT("������Ϣ����"), MB_ICONERROR);
							return FALSE;
						}
						CEdit edit(hwnd, IDC_E_ROOM_NO);   // ����Ҳ�༭������
						edit.Empty();
						edit.Initialization(hwnd, IDC_E_ROOM_NAME);
						edit.Empty();
					}
					break;
				}
			}
			return TRUE;
		}
	case WM_CLOSE:
		{
			EndDialog(hwnd,0);
			return TRUE;
		}
	}
	return FALSE;
}

void ShowFloorList(HWND hwnd)
{
	CListView floor_list(hwnd,IDC_L_FLOOR_INFO);
	floor_list.DeleteAllItems();
	FloorInfo floor_info;
	floor_info.GetFloorSet();
	int index = 0;
	while(!floor_info.IsEOF())
	{
		floor_list.InsertItem(index,floor_info.floor_no());
		floor_list.SetItem(index,1,floor_info.floor_name());
		index++;
	}
}

bool AddFloor(HWND hwnd)
{
	FLOORINFO floor_info;
	FloorInfo floor;
	CEdit e_name,e_id;
	e_id.Initialization(hwnd, IDC_E_FLOOR_ID);
	e_name.Initialization(hwnd, IDC_E_FLOOR_NAME);
	e_id.GetEditText(floor_info.no);
	e_name.GetEditText(floor_info.name);
	floor_info.old_no = floor_info.no;//����"ԭ���ı����ͬ",��"ԭ���ı��"��ִ��"����"����ʱδ��
	if(floor.AddFloor(&floor_info))
	{
		MessageBox(hwnd,TEXT("���¥����Ϣ�ɹ�"),TEXT("��ӳɹ�"),MB_OK);
		return true;
	}
	return false;
}
bool UpdateFloor(HWND hwnd)
{
	int list_index;
	CListView floor_list(hwnd,IDC_L_FLOOR_INFO);
	list_index = floor_list.GetSelectionMark();
	if (-1 == list_index)
	{
		MessageBox(hwnd, TEXT("�����б���ѡ��һ��"), TEXT("��ʾ"), MB_OK);
		return false;
	}
	int mb_ret=MessageBox(hwnd,TEXT("�޸�¥����Ϣͬʱ���޸ĸ�¥���µ����з����̨�ţ�\n ��ȷ���Ƿ��޸ģ�"),TEXT("�Ƿ�ɾ��"),MB_YESNO);
	if (IDYES == mb_ret)
	{
		
		FLOORINFO floor_info;
		FloorInfo floor;
		CEdit e_name,e_id;
		e_id.Initialization(hwnd, IDC_E_FLOOR_ID);
		e_name.Initialization(hwnd, IDC_E_FLOOR_NAME);
		e_id.GetEditText(floor_info.no);
		e_name.GetEditText(floor_info.name);
		floor_info.old_no = floor_list.GetItem(list_index,0);//��ȡ�б���ԭ����¥����
		if(floor.UpdateFloor(&floor_info))
		{
			MessageBox(hwnd,TEXT("�޸�¥����Ϣ�ɹ�"),TEXT("�޸ĳɹ�"),MB_OK);
			return true;
		}
	}
	return false;
}
bool DeleteFloor(HWND hwnd)
{
	int list_index;
	CListView floor_list(hwnd,IDC_L_FLOOR_INFO);
	list_index = floor_list.GetSelectionMark();
	if (-1 == list_index)
	{
		MessageBox(hwnd, TEXT("�����б���ѡ��һ��"), TEXT("��ʾ"), MB_OK);
		return false;
	}
	int mb_ret=MessageBox(hwnd,TEXT("ɾ��¥��Ҳ��ɾ����¥���µ����з����̨�ţ�\n ��ȷ���Ƿ�ɾ����"),TEXT("�Ƿ�ɾ��"),MB_YESNO);
	if (IDYES == mb_ret)
	{
		FLOORINFO floor_info;
		FloorInfo floor;
		floor_info.no = floor_list.GetItem(list_index,0);//��ȡ�б���ԭ����¥����
		floor_info.name = floor_list.GetItem(list_index,1);
		floor_info.old_no = floor_info.no;
		if(floor.DeleteFloor(&floor_info))
		{
			MessageBox(hwnd,TEXT("ɾ��¥����Ϣ�ɹ�"),TEXT("ɾ���ɹ�"),MB_OK);
			return true;
		}
	}
	return false;
}

/*
 * @ brief: ��ʾ������Ϣ
 * @ param: hwnd [in] �����ھ��
 * @ param: id [in] list view id
 * @ param: floor_name [in] ¥������
 **/
void ShowRoomInfo(HWND hwnd, UINT id, const char *floor_name) {
	CListView room_list(hwnd, id);
	room_list.DeleteAllItems();
	RoomInfo room;
	room.GetRoomInfo(floor_name);
	int i = 0;
	while (!room.IsEOF()) {
		room_list.InsertItem(i, room.room_no());
		room_list.SetItem(i, 1, room.room_name());
		i++;
	}
}