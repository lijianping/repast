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
			try {
				InitFloorRoomInfo(hwnd,IDC_T_TABLE_INFO);
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
					InitFloorRoomInfo(hwnd,IDC_T_TABLE_INFO);
					break;
				}
			case IDC_B_ROOM://�������
				{
					DialogBox(hInstance, MAKEINTRESOURCE(IDD_EDIT_ROOM), hwnd, (DLGPROC)RoomInfoProc);
					InitFloorRoomInfo(hwnd,IDC_T_TABLE_INFO);
					break;
				}
			case IDC_B_TABLE://̨�Ź���
				{
					DialogBox(hInstance, MAKEINTRESOURCE(IDD_EDIT_TABLE), hwnd, (DLGPROC)ChildTableInfoProc);
					InitFloorRoomInfo(hwnd,IDC_T_TABLE_INFO);
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
						int index = -1;
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
						CComboBox combo(hwnd, IDC_FLOOR_COMBO);
						std::string floor_name;
						combo.GetComboBoxText(floor_name);
						ShowRoomInfo(hwnd, IDC_L_ROOM_INFO, floor_name.c_str());
						MessageBox(hwnd, TEXT("������Ϣ��ӳɹ�!"), TEXT("������Ϣ����"), MB_ICONINFORMATION);
					} catch (Err &err) {
						MessageBox(hwnd, err.what(), TEXT("������Ϣ����"), MB_ICONERROR);
						return FALSE;
					}
					break;
				}
			case IDC_B_MODITY_ROOM:
				{
					CListView room_list(hwnd, IDC_L_ROOM_INFO);
					int select = room_list.GetSelectionMark();
					if (-1 == select) {
						MessageBox(hwnd, TEXT("��������б��ѡ��Ҫɾ���ķ�����!"), TEXT("������Ϣ����"), MB_ICONINFORMATION);
						break;
					}
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
						CComboBox combo(hwnd, IDC_FLOOR_COMBO);
						std::string floor_name;
						combo.GetComboBoxText(floor_name);
						ShowRoomInfo(hwnd, IDC_L_ROOM_INFO, floor_name.c_str());
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
						CComboBox combo(hwnd, IDC_FLOOR_COMBO);
						std::string floor_name;
						combo.GetComboBoxText(floor_name);
						ShowRoomInfo(hwnd, IDC_L_ROOM_INFO, floor_name.c_str());
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

/*
 * @ brief: ̨����Ϣ������
 * @ param: hwnd [in] ���ھ��
 * @ param: msg [in] ��Ϣ����
 **/
BOOL CALLBACK ChildTableInfoProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_INITDIALOG:
		{
			CListView table_list(hwnd, IDC_L_TABLE_INFO);
			table_list.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			table_list.InsertColumn(1,80,"��������");
			table_list.InsertColumn(2,100,"̨    ��");
			table_list.InsertColumn(2,60,"��    ��");
			try {

				InitFloorName(hwnd, IDC_TABLE_FLOOR_COMBO);//��ʼ����ߵ�һ����¥�㡱�����б�
				InitFloorName(hwnd, IDC_C_FLOOR_NAME);//��ʼ���α�ڶ�����¥�㡱�����б�
				CComboBox floor_combo(hwnd, IDC_TABLE_FLOOR_COMBO);
				std::string floor_name;
				floor_combo.GetComboBoxText(floor_name);
			    InitTableList(hwnd, IDC_L_TABLE_INFO, floor_name.c_str(), 0);
				InitRoomCombo(hwnd,floor_name.c_str(),IDC_C_ROOM_NAME);//����¥��������ʼ�����������б�
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
			case IDC_L_TABLE_INFO:
				{
					if (((LPNMHDR)lParam)->code == NM_CLICK){      // ����б��е�һ��
						int index = -1;
						CEdit num, no;
						CComboBox room_name, floor_name;
						CListView table_list;
						table_list.Initialization(hwnd, IDC_L_TABLE_INFO);
						index = table_list.GetSelectionMark();
						if (-1 == index) {
							MessageBox(hwnd, TEXT("���������ѡ��һ��̨�ţ�"), TEXT("������Ϣ����"), MB_ICONINFORMATION);
							break;
						}
						
						room_name.Initialization(hwnd, IDC_C_ROOM_NAME);
						no.Initialization(hwnd, IDC_E_TABLE_NO);
						num.Initialization(hwnd, IDC_E_TABLE_NUM);
						CComboBox combo(hwnd, IDC_TABLE_FLOOR_COMBO);
						std::string name;
						combo.GetComboBoxText(name);
						floor_name.Initialization(hwnd, IDC_C_FLOOR_NAME);
						floor_name.DeleteAllString();
						InitFloorName(hwnd,IDC_C_FLOOR_NAME);
					    floor_name.SetCurSel(floor_name.FindString(name.c_str()));
						
						InitRoomCombo(hwnd,name.c_str(),IDC_C_ROOM_NAME);
						room_name.SetCurSel(room_name.FindString(table_list.GetItem(index, 0).c_str()));
						no.SetEditText(table_list.GetItem(index, 1).c_str());
						num.SetEditText(table_list.GetItem(index, 2).c_str());
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
			case IDC_B_ADD_TABLE:
				{
					try {
					    if(AddTable(hwnd))
						{
							MessageBox(hwnd, TEXT("���̨����Ϣ�ɹ�"), TEXT("������Ϣ���� "), MB_ICONINFORMATION);
						}
					} catch (Err &err) {
						MessageBox(hwnd, err.what(), TEXT("������Ϣ���� "), MB_ICONERROR);
						return FALSE;
					}
					break;
				}
			case IDC_B_DISHPATCH_TABLE:
				{
					try
					{
						if (UpdateTable(hwnd))
						{
							MessageBox(hwnd, TEXT("�޸�̨����Ϣ�ɹ�"), TEXT("������Ϣ����"), MB_OK);
						}
					}
					catch (Err &err)
					{
						MessageBox(hwnd, err.what(), TEXT("������Ϣ����"), MB_ICONERROR);
					}
					break;
				}
			case IDC_B_DELETE_TABLE:
				{
				try
					{
						if (DeleteTable(hwnd))
						{
								MessageBox(hwnd, TEXT("ɾ��̨����Ϣ�ɹ�"), TEXT("������Ϣ����"), MB_OK);
						}
					}
					catch (Err &err)
					{
						MessageBox(hwnd, err.what(), TEXT("������Ϣ����"), MB_ICONERROR);
					}
					break;
				}
			case IDC_TABLE_FLOOR_COMBO://�����ߵ�һ����¥�㡰�����б�
				{
					if (HIWORD(wParam) == CBN_SELCHANGE) {
						try {
							CComboBox combo(hwnd, IDC_TABLE_FLOOR_COMBO);
							std::string floor_name;
							combo.GetComboBoxText(floor_name);
							CComboBox room(hwnd, IDC_C_ROOM_NAME);
							room.DeleteAllString();//��ա����䡱�����б�Ȼ���ڲ����µ�����
							InitTableList(hwnd, IDC_L_TABLE_INFO, floor_name.c_str(), 0);
						} catch (Err &err) {
							MessageBox(hwnd, err.what(), TEXT("������Ϣ����"), MB_ICONERROR);
							return FALSE;
						}
					    CEdit edit;
						// ����Ҳ�༭������
						edit.Initialization(hwnd, IDC_E_TABLE_NO);
						edit.Empty();
						edit.Initialization(hwnd, IDC_E_TABLE_NUM);
						edit.Empty();
					}
					break;
				}
			case IDC_C_FLOOR_NAME://����ڶ�����¥�㡱�����б�
				{
					if (HIWORD(wParam) == CBN_SELCHANGE)
					{
						try
						{
							CComboBox combo(hwnd, IDC_C_FLOOR_NAME);
							std::string floor_name_str;
							combo.GetComboBoxText(floor_name_str);
							CComboBox room_name(hwnd, IDC_C_ROOM_NAME);
							RoomInfo room_info;
							room_info.GetRoomName(floor_name_str.c_str());  // ��ȡ¥���µķ������Ƽ�¼��
							room_name.DeleteAllString();
							while (!room_info.IsEOF())
							{
								room_name.AddString(room_info.room_name());
							} 
						}
						catch (Err &err)
						{
							MessageBox(hwnd, err.what(), TEXT("������Ϣ����"), MB_ICONERROR);
							return FALSE;
						}			
					}
					break;
				}	
			case IDC_B_TABLE_CANCLE:
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

/*
 * ˵����
 *    ���¥����Ϣ
 * ������
 *    hwnd [in] �����ھ��
 * ����ֵ
 *    �ɹ�����true
 */
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

/*
 * ˵����
 *    ����ѡ�е�¥����Ϣ
 * ������
 *    hwnd [in] �����ھ��
 * ����ֵ
 *    �ɹ�����true
 */
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

/*
 * ˵����
 *    ɾ��ѡ�е�¥����Ϣ
 * ������
 *    hwnd [in] �����ھ��
 * ����ֵ
 *    �ɹ�����true
 */
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
			CEdit floor_no, floor_name;
			floor_no.Initialization(hwnd,IDC_E_FLOOR_ID);
			floor_name.Initialization(hwnd,IDC_E_FLOOR_NAME);
			MessageBox(hwnd,TEXT("ɾ��¥����Ϣ�ɹ�"),TEXT("ɾ���ɹ�"),MB_OK);
			floor_no.Empty();//���¥����
			floor_name.Empty();//���¥������
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


/*
 * ˵����
 *    ��ʼ��¥�㷿�����οؼ�
 * ������
 *    hwnd [in] �����ھ��
 *    id   [in] tree�ؼ�id
 * ����ֵ
 *    �ɹ�����true
 */
bool InitFloorRoomInfo(HWND hwnd,UINT id)
{
	TreeCtrl info_tree(hwnd,id);
	info_tree.DeleteAllItems();
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
	return true;
}

/*
 * ˵����
 *    ���̨����Ϣ
 * ������
 *    hwnd [in] �����ھ��
 * ����ֵ
 *    �ɹ�����true
 */

bool AddTable(HWND hwnd)
{
	std::string floor, room, table_no, sum_str;
	CComboBox floor_combox(hwnd, IDC_C_FLOOR_NAME);
	CComboBox room_combox(hwnd, IDC_C_ROOM_NAME);
	floor_combox.GetComboBoxText(floor);
	room_combox.GetComboBoxText(room);
	CEdit edit;
	edit.Initialization(hwnd, IDC_E_TABLE_NO);
	edit.GetEditText(table_no);
	edit.Initialization(hwnd, IDC_E_TABLE_NUM);
	edit.GetEditText(sum_str);

	CTableInfo table;
	table.AddTable(floor.c_str(), room.c_str(), table_no.c_str(), atoi(sum_str.c_str()));
	//��ʾ��ӵ�̨����Ϣ
	CComboBox left_combox_floor(hwnd,IDC_TABLE_FLOOR_COMBO);
	left_combox_floor.SetCurSel(left_combox_floor.FindString(floor.c_str()));
	InitTableList(hwnd, IDC_L_TABLE_INFO, floor.c_str(), 0);  // ����
	return true;
}

/*
 * ˵����
 *    ����̨����Ϣ
 * ������
 *    hwnd [in] �����ھ��
 * ����ֵ
 *    �ɹ�����true
 */
bool UpdateTable(HWND hwnd)
{
	CListView table_list(hwnd, IDC_L_TABLE_INFO);
	int select = table_list.GetSelectionMark();
	if (-1 == select) {
		MessageBox(hwnd, TEXT("��������б��ѡ��Ҫɾ���ķ�����!"), TEXT("������Ϣ����"), MB_ICONINFORMATION);
		return false;
	}
	TABLEINFO table_info;//̨����Ϣ�ṹ��
	CComboBox old_floor,new_floor,new_room;
	CEdit new_no,new_payable;
	old_floor.Initialization(hwnd,IDC_TABLE_FLOOR_COMBO);
	new_floor.Initialization(hwnd,IDC_C_FLOOR_NAME);
	new_room.Initialization(hwnd,IDC_C_ROOM_NAME);
	new_no.Initialization(hwnd,IDC_E_TABLE_NO);
	new_payable.Initialization(hwnd,IDC_E_TABLE_NUM);
	//��ȡ���µ�̨����Ϣ
	new_floor.GetComboBoxText(table_info.new_floor_name);
	new_room.GetComboBoxText(table_info.new_room_name);
	new_no.GetEditText(table_info.new_table_no);
	new_payable.GetEditText(table_info.new_table_payable);	
	//��ȡ��̨����Ϣ
	old_floor.GetComboBoxText(table_info.old_floor_name);
	table_info.old_room_name=table_list.GetItem(select,0);
	table_info.old_table_no=table_list.GetItem(select,1);

	CTableInfo table;
	table.UpdateTable(&table_info);
	//�����ʾ
	new_floor.DeleteAllString();
	new_room.DeleteAllString();
	new_no.Empty();
	new_payable.Empty();
	CComboBox floor_name;
	floor_name.Initialization(hwnd, IDC_TABLE_FLOOR_COMBO);
	std::string floor;
	floor_name.GetComboBoxText(floor);
	InitTableList(hwnd, IDC_L_TABLE_INFO, floor.c_str(), 0); 
	//ˢ����ʾ
	return true;
}

/*
 * ˵����
 *    ɾ��̨����Ϣ
 * ������
 *    hwnd [in] �����ھ��
 * ����ֵ
 *    �ɹ�����true
 */
bool DeleteTable(HWND hwnd)
{
	CListView table_list(hwnd, IDC_L_TABLE_INFO);
	int select = table_list.GetSelectionMark();
	if (-1 == select) {
		MessageBox(hwnd, TEXT("��������б��ѡ��Ҫɾ���ķ�����!"), TEXT("������Ϣ����"), MB_ICONINFORMATION);
		return false;
	}
	std::string floor, room, table_no;
	CComboBox combo(hwnd, IDC_TABLE_FLOOR_COMBO);
	combo.GetComboBoxText(floor);              // ��ȡ¥����
	room = table_list.GetItem(select, 0);      // ��ȡ������
	table_no = table_list.GetItem(select, 1);  // ��ȡ̨��
		CTableInfo table;
		table.DeleteTable(floor.c_str(), room.c_str(), table_no.c_str());
		CComboBox combox;
		//�����ʾ
		combox.Initialization(hwnd,IDC_C_FLOOR_NAME);
		combox.DeleteAllString();
		combox.Initialization(hwnd,IDC_C_ROOM_NAME);
		combox.DeleteAllString();
		CEdit edit;
		edit.Initialization(hwnd,IDC_E_TABLE_NO);
		edit.Empty();
		edit.Initialization(hwnd,IDC_E_TABLE_NUM);
		edit.Empty();
		InitTableList(hwnd, IDC_L_TABLE_INFO, floor.c_str(), 0);  // ����
	return true;
}


/*
 * ˵����
 *     ����¥��������ʼ�����������б��ȸ�¥���µķ�����Ϣ
 * ������
 *    hwnd [in] �����ھ��
 *    floor_name [in] ¥������
 *    id   [in] �����б�ı��
 * ����ֵ��
 *    �ɹ�����true,
 */
bool InitRoomCombo(HWND hwnd,const char *floor_name, UINT id)
{
	CComboBox room_name(hwnd, id);
	RoomInfo room_info;
	room_info.GetRoomName(floor_name);  // ��ȡ¥���µķ������Ƽ�¼��
	room_name.DeleteAllString();
	while (!room_info.IsEOF())
	{
		room_name.AddString(room_info.room_name());
	} 
	return true;
}
