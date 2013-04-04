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
			// 初始化Listview
			CListView table_list(hwnd, IDC_L_TABLE_INFO);
			table_list.InsertColumn(0, 100, "台号");
			table_list.InsertColumn(1, 100, "状态");
			table_list.InsertColumn(2, 100, "可容纳人数");
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
								info_tree.GetItem(info_tree.GetParent(select), 512, parent_item_text); // 获取父节点信息
								try {
									CTableInfo table_info;
									table_info.GetTableInfoSet(parent_item_text, item_text);
									CListView table_list(hwnd, IDC_L_TABLE_INFO);
									table_list.DeleteAllItems();  // 清空ListView
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
									table_list.DeleteAllItems();  // 清空ListView
									int i = 0;
									while (!table_info.IsEOF()) {   // 循环插入table信息
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
			case IDC_B_FLOOR://楼层管理
				{
	        		DialogBox(hInstance,MAKEINTRESOURCE(IDD_EDIT_FLOOR),hwnd,(DLGPROC)FloorInfoProc);
					InitFloorRoomInfo(hwnd,IDC_T_TABLE_INFO);
					break;
				}
			case IDC_B_ROOM://房间管理
				{
					DialogBox(hInstance, MAKEINTRESOURCE(IDD_EDIT_ROOM), hwnd, (DLGPROC)RoomInfoProc);
					InitFloorRoomInfo(hwnd,IDC_T_TABLE_INFO);
					break;
				}
			case IDC_B_TABLE://台号管理
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
			floor_list.InsertColumn(1,100,"楼层编号");
			floor_list.InsertColumn(2,100,"楼层名称");
			try {
			    ShowFloorList(hwnd);
			} catch (Err &err) {
				MessageBox(hwnd, err.what(), TEXT("基础信息管理"), MB_ICONERROR);
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
					if (((LPNMHDR)lParam)->code == NM_CLICK)/*点击列表中的一项*/
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
						MessageBox(hwnd, err.what(), TEXT("基础信息管理"), MB_ICONERROR);
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
						MessageBox(hwnd, err.what(), TEXT("基础信息管理"), MB_ICONERROR);
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
						MessageBox(hwnd, err.what(), TEXT("基础信息管理"), MB_ICONERROR);
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
	static std::string old_room_no;   // 原房间编号
	switch(msg)
	{
	case WM_INITDIALOG:
		{
			CListView floor_list(hwnd, IDC_L_ROOM_INFO);
			floor_list.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			floor_list.InsertColumn(1,80,"房间编号");
			floor_list.InsertColumn(2,100,"房间名称");
			try {
				InitFloorName(hwnd, IDC_FLOOR_COMBO);
				CComboBox combo(hwnd, IDC_FLOOR_COMBO);
				std::string floor_name;
				combo.GetComboBoxText(floor_name);
				ShowRoomInfo(hwnd, IDC_L_ROOM_INFO, floor_name.c_str());
			} catch (Err &err) {
				MessageBox(hwnd, err.what(), TEXT("基础信息管理"), MB_ICONERROR);
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
					if (((LPNMHDR)lParam)->code == NM_CLICK)/*点击列表中的一项*/
					{
						int index = -1;
						CEdit e_name,e_id;
						CListView room_list;
						room_list.Initialization(hwnd, IDC_L_ROOM_INFO);
						e_id.Initialization(hwnd, IDC_E_ROOM_NO);
						e_name.Initialization(hwnd, IDC_E_ROOM_NAME);
						index = room_list.GetSelectionMark();
						old_room_no = room_list.GetItem(index,0);   // 获取点中的房间编号，修改时用
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
						MessageBox(hwnd, TEXT("编号过长！\n仅允许两位！"), TEXT("基础信息管理"), MB_ICONINFORMATION);
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
						MessageBox(hwnd, TEXT("房间信息添加成功!"), TEXT("基础信息管理"), MB_ICONINFORMATION);
					} catch (Err &err) {
						MessageBox(hwnd, err.what(), TEXT("基础信息管理"), MB_ICONERROR);
						return FALSE;
					}
					break;
				}
			case IDC_B_MODITY_ROOM:
				{
					CListView room_list(hwnd, IDC_L_ROOM_INFO);
					int select = room_list.GetSelectionMark();
					if (-1 == select) {
						MessageBox(hwnd, TEXT("请在左侧列表款选择要删除的房间编号!"), TEXT("基础信息管理"), MB_ICONINFORMATION);
						break;
					}
					CComboBox combo(hwnd, IDC_FLOOR_COMBO);
					std::string floor_name, room_no, room_name;
					combo.GetComboBoxText(floor_name);
					CEdit edit(hwnd, IDC_E_ROOM_NO);
					edit.GetEditText(room_no);       // 获取修改的房间编号
					if (room_no.length() > 2) {
						MessageBox(hwnd, TEXT("编号过长！\n仅允许两位！"), TEXT("基础信息管理"), MB_ICONINFORMATION);
						break;
					}
					edit.Initialization(hwnd, IDC_E_ROOM_NAME);
					edit.GetEditText(room_name);   // 获取修改的房间名称
					try {
						RoomInfo room;
						room.ModifyRoom(floor_name.c_str(), old_room_no.c_str(), room_no.c_str(), room_name.c_str());
						CComboBox combo(hwnd, IDC_FLOOR_COMBO);
						std::string floor_name;
						combo.GetComboBoxText(floor_name);
						ShowRoomInfo(hwnd, IDC_L_ROOM_INFO, floor_name.c_str());
						MessageBox(hwnd, TEXT("房间信息修改成功!"), TEXT("基础信息管理"), MB_ICONINFORMATION);
					} catch (Err &err) {
						MessageBox(hwnd, err.what(), TEXT("基础信息管理"), MB_ICONERROR);
						return FALSE;
					}
					break;
				}
			case IDC_B_DELETE_ROOM:
				{
					CListView room_list(hwnd, IDC_L_ROOM_INFO);
					int select = room_list.GetSelectionMark();
					if (-1 == select) {
						MessageBox(hwnd, TEXT("请在左侧列表款选择要删除的房间编号!"), TEXT("基础信息管理"), MB_ICONINFORMATION);
						break;
					}
					std::string room_no, floor_name;
					room_no = room_list.GetItem(select, 0);    // 获取房间编号
					CComboBox combo(hwnd, IDC_FLOOR_COMBO);
					combo.GetComboBoxText(floor_name);         // 获取楼层名称
					try {
						RoomInfo room;
						room.DeleteRoom(floor_name.c_str(), room_no.c_str());
						CComboBox combo(hwnd, IDC_FLOOR_COMBO);
						std::string floor_name;
						combo.GetComboBoxText(floor_name);
						ShowRoomInfo(hwnd, IDC_L_ROOM_INFO, floor_name.c_str());
						MessageBox(hwnd, TEXT("房间信息删除成功!"), TEXT("基础信息管理"), MB_ICONINFORMATION);
					} catch (Err &err) {
						MessageBox(hwnd, err.what(), TEXT("基础信息管理"), MB_ICONERROR);
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
							MessageBox(hwnd, err.what(), TEXT("基础信息管理"), MB_ICONERROR);
							return FALSE;
						}
						CEdit edit(hwnd, IDC_E_ROOM_NO);   // 清空右侧编辑框数据
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
 * @ brief: 台号信息处理函数
 * @ param: hwnd [in] 窗口句柄
 * @ param: msg [in] 消息类型
 **/
BOOL CALLBACK ChildTableInfoProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_INITDIALOG:
		{
			CListView table_list(hwnd, IDC_L_TABLE_INFO);
			table_list.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			table_list.InsertColumn(1,80,"房间名称");
			table_list.InsertColumn(2,100,"台    号");
			table_list.InsertColumn(2,60,"人    数");
			try {

				InitFloorName(hwnd, IDC_TABLE_FLOOR_COMBO);//初始化左边第一个“楼层”下拉列表
				InitFloorName(hwnd, IDC_C_FLOOR_NAME);//初始化游标第二个“楼层”下拉列表
				CComboBox floor_combo(hwnd, IDC_TABLE_FLOOR_COMBO);
				std::string floor_name;
				floor_combo.GetComboBoxText(floor_name);
			    InitTableList(hwnd, IDC_L_TABLE_INFO, floor_name.c_str(), 0);
				InitRoomCombo(hwnd,floor_name.c_str(),IDC_C_ROOM_NAME);//根据楼层名，初始化房间下拉列表
			} catch (Err &err) {
				MessageBox(hwnd, err.what(), TEXT("基础信息管理"), MB_ICONERROR);
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
					if (((LPNMHDR)lParam)->code == NM_CLICK){      // 点击列表中的一项
						int index = -1;
						CEdit num, no;
						CComboBox room_name, floor_name;
						CListView table_list;
						table_list.Initialization(hwnd, IDC_L_TABLE_INFO);
						index = table_list.GetSelectionMark();
						if (-1 == index) {
							MessageBox(hwnd, TEXT("请先在左侧选择一个台号！"), TEXT("基础信息管理"), MB_ICONINFORMATION);
							break;
						}
						floor_name.Initialization(hwnd, IDC_C_FLOOR_NAME);
						room_name.Initialization(hwnd, IDC_C_ROOM_NAME);
						no.Initialization(hwnd, IDC_E_TABLE_NO);
						num.Initialization(hwnd, IDC_E_TABLE_NUM);
						CComboBox combo(hwnd, IDC_TABLE_FLOOR_COMBO);
						std::string name;
						combo.GetComboBoxText(name);
					    floor_name.SetCurSel(floor_name.FindString(name.c_str()));
						InitFloorName(hwnd,IDC_C_FLOOR_NAME);
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
							MessageBox(hwnd, TEXT("添加台号信息成功"), TEXT("基础信息管理 "), MB_ICONINFORMATION);
						}
					} catch (Err &err) {
						MessageBox(hwnd, err.what(), TEXT("基础信息管理 "), MB_ICONERROR);
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
							MessageBox(hwnd, TEXT("修改台号信息成功"), TEXT("基础信息管理"), MB_OK);
						}
					}
					catch (Err &err)
					{
						MessageBox(hwnd, err.what(), TEXT("基础信息管理"), MB_ICONERROR);
					}
					break;
				}
			case IDC_B_DELETE_TABLE:
				{
				try
					{
						if (DeleteTable(hwnd))
						{
								MessageBox(hwnd, TEXT("删除台号信息成功"), TEXT("基础信息管理"), MB_OK);
						}
					}
					catch (Err &err)
					{
						MessageBox(hwnd, err.what(), TEXT("基础信息管理"), MB_ICONERROR);
					}
					break;
				}
			case IDC_TABLE_FLOOR_COMBO://点击左边第一个”楼层“下拉列表
				{
					if (HIWORD(wParam) == CBN_SELCHANGE) {
						try {
							CComboBox combo(hwnd, IDC_TABLE_FLOOR_COMBO);
							std::string floor_name;
							combo.GetComboBoxText(floor_name);
							CComboBox room(hwnd, IDC_C_ROOM_NAME);
							room.DeleteAllString();//清空“房间”下拉列表，然后在插入新的数据
							InitTableList(hwnd, IDC_L_TABLE_INFO, floor_name.c_str(), 0);
						} catch (Err &err) {
							MessageBox(hwnd, err.what(), TEXT("基础信息管理"), MB_ICONERROR);
							return FALSE;
						}
					    CEdit edit;
						// 清空右侧编辑框数据
						edit.Initialization(hwnd, IDC_E_TABLE_NO);
						edit.Empty();
						edit.Initialization(hwnd, IDC_E_TABLE_NUM);
						edit.Empty();
					}
					break;
				}
			case IDC_C_FLOOR_NAME://点击第二个“楼层”下拉列表
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
							room_info.GetRoomName(floor_name_str.c_str());  // 获取楼层下的房间名称记录集
							room_name.DeleteAllString();
							while (!room_info.IsEOF())
							{
								room_name.AddString(room_info.room_name());
							} 
						}
						catch (Err &err)
						{
							MessageBox(hwnd, err.what(), TEXT("基础信息管理"), MB_ICONERROR);
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
 * 说明：
 *    添加楼层信息
 * 参数：
 *    hwnd [in] 主窗口句柄
 * 返回值
 *    成功返回true
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
	floor_info.old_no = floor_info.no;//设置"原来的编号相同",但"原来的编号"在执行"新增"功能时未用
	if(floor.AddFloor(&floor_info))
	{
		MessageBox(hwnd,TEXT("添加楼层信息成功"),TEXT("添加成功"),MB_OK);
		return true;
	}
	return false;
}

/*
 * 说明：
 *    更新选中的楼层信息
 * 参数：
 *    hwnd [in] 主窗口句柄
 * 返回值
 *    成功返回true
 */
bool UpdateFloor(HWND hwnd)
{
	int list_index;
	CListView floor_list(hwnd,IDC_L_FLOOR_INFO);
	list_index = floor_list.GetSelectionMark();
	if (-1 == list_index)
	{
		MessageBox(hwnd, TEXT("请在列表中选择一项"), TEXT("提示"), MB_OK);
		return false;
	}
	int mb_ret=MessageBox(hwnd,TEXT("修改楼层信息同时会修改改楼层下的所有房间和台号！\n 请确认是否修改？"),TEXT("是否删除"),MB_YESNO);
	if (IDYES == mb_ret)
	{
		
		FLOORINFO floor_info;
		FloorInfo floor;
		CEdit e_name,e_id;
		e_id.Initialization(hwnd, IDC_E_FLOOR_ID);
		e_name.Initialization(hwnd, IDC_E_FLOOR_NAME);
		e_id.GetEditText(floor_info.no);
		e_name.GetEditText(floor_info.name);
		floor_info.old_no = floor_list.GetItem(list_index,0);//获取列表中原来的楼层编号
		if(floor.UpdateFloor(&floor_info))
		{
			MessageBox(hwnd,TEXT("修改楼层信息成功"),TEXT("修改成功"),MB_OK);
			return true;
		}
	}
	return false;
}

/*
 * 说明：
 *    删除选中的楼层信息
 * 参数：
 *    hwnd [in] 主窗口句柄
 * 返回值
 *    成功返回true
 */
bool DeleteFloor(HWND hwnd)
{
	int list_index;
	CListView floor_list(hwnd,IDC_L_FLOOR_INFO);
	list_index = floor_list.GetSelectionMark();
	if (-1 == list_index)
	{
		MessageBox(hwnd, TEXT("请在列表中选择一项"), TEXT("提示"), MB_OK);
		return false;
	}
	int mb_ret=MessageBox(hwnd,TEXT("删除楼层也会删除改楼层下的所有房间和台号！\n 请确认是否删除？"),TEXT("是否删除"),MB_YESNO);
	if (IDYES == mb_ret)
	{
		FLOORINFO floor_info;
		FloorInfo floor;
		floor_info.no = floor_list.GetItem(list_index,0);//获取列表中原来的楼层编号
		floor_info.name = floor_list.GetItem(list_index,1);
		floor_info.old_no = floor_info.no;
		if(floor.DeleteFloor(&floor_info))
		{
			CEdit floor_no, floor_name;
			floor_no.Initialization(hwnd,IDC_E_FLOOR_ID);
			floor_name.Initialization(hwnd,IDC_E_FLOOR_NAME);
			MessageBox(hwnd,TEXT("删除楼层信息成功"),TEXT("删除成功"),MB_OK);
			floor_no.Empty();//清空楼层编号
			floor_name.Empty();//清空楼层名称
			return true;
		}
	}
	return false;
}

/*
 * @ brief: 显示房间信息
 * @ param: hwnd [in] 父窗口句柄
 * @ param: id [in] list view id
 * @ param: floor_name [in] 楼层名称
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
 * 说明：
 *    初始化楼层房间树形控件
 * 参数：
 *    hwnd [in] 主窗口句柄
 *    id   [in] tree控件id
 * 返回值
 *    成功返回true
 */
bool InitFloorRoomInfo(HWND hwnd,UINT id)
{
	TreeCtrl info_tree(hwnd,id);
	info_tree.DeleteAllItems();
	FloorInfo floor_info;
	floor_info.GetFloorName();     // 获取楼层名称记录集
	while (!floor_info.IsEOF()) {  // 循环取出数据
		std::string floor_name(floor_info.floor_name());  // 获取楼层名称
		HTREEITEM root_node = info_tree.InsertRootItem(floor_name.c_str());  // 插入根节点
		RoomInfo room_info;
		room_info.GetRoomName(floor_name.c_str());  // 获取楼层下的房间名称记录集
		while (!room_info.IsEOF()) {
			info_tree.InsertChildItem(root_node, room_info.room_name());  // 插入子节点
		}  // end second while
	} // end first while 
	return true;
}

/*
 * 说明：
 *    添加台号信息
 * 参数：
 *    hwnd [in] 主窗口句柄
 * 返回值
 *    成功返回true
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
	//显示添加的台号信息
	CComboBox left_combox_floor(hwnd,IDC_TABLE_FLOOR_COMBO);
	left_combox_floor.SetCurSel(left_combox_floor.FindString(floor.c_str()));
	InitTableList(hwnd, IDC_L_TABLE_INFO, floor.c_str(), 0);  // 更新
	return true;
}

/*
 * 说明：
 *    更新台号信息
 * 参数：
 *    hwnd [in] 主窗口句柄
 * 返回值
 *    成功返回true
 */
bool UpdateTable(HWND hwnd)
{
	CListView table_list(hwnd, IDC_L_TABLE_INFO);
	int select = table_list.GetSelectionMark();
	if (-1 == select) {
		MessageBox(hwnd, TEXT("请在左侧列表款选择要删除的房间编号!"), TEXT("基础信息管理"), MB_ICONINFORMATION);
		return false;
	}
	TABLEINFO table_info;//台号信息结构体
	CComboBox old_floor,new_floor,new_room;
	CEdit new_no,new_payable;
	old_floor.Initialization(hwnd,IDC_TABLE_FLOOR_COMBO);
	new_floor.Initialization(hwnd,IDC_C_FLOOR_NAME);
	new_room.Initialization(hwnd,IDC_C_ROOM_NAME);
	new_no.Initialization(hwnd,IDC_E_TABLE_NO);
	new_payable.Initialization(hwnd,IDC_E_TABLE_NUM);
	//获取更新的台号信息
	new_floor.GetComboBoxText(table_info.new_floor_name);
	new_room.GetComboBoxText(table_info.new_room_name);
	new_no.GetEditText(table_info.new_table_no);
	new_payable.GetEditText(table_info.new_table_payable);	
	//获取旧台号信息
	old_floor.GetComboBoxText(table_info.old_floor_name);
	table_info.old_room_name=table_list.GetItem(select,0);
	table_info.old_table_no=table_list.GetItem(select,1);

	CTableInfo table;
	table.UpdateTable(&table_info);
	//清空显示
	new_floor.DeleteAllString();
	new_room.DeleteAllString();
	new_no.Empty();
	new_payable.Empty();
	CComboBox floor_name;
	floor_name.Initialization(hwnd, IDC_TABLE_FLOOR_COMBO);
	std::string floor;
	floor_name.GetComboBoxText(floor);
	InitTableList(hwnd, IDC_L_TABLE_INFO, floor.c_str(), 0); 
	//刷新显示
	return true;
}

/*
 * 说明：
 *    删除台号信息
 * 参数：
 *    hwnd [in] 主窗口句柄
 * 返回值
 *    成功返回true
 */
bool DeleteTable(HWND hwnd)
{
	CListView table_list(hwnd, IDC_L_TABLE_INFO);
	int select = table_list.GetSelectionMark();
	if (-1 == select) {
		MessageBox(hwnd, TEXT("请在左侧列表款选择要删除的房间编号!"), TEXT("基础信息管理"), MB_ICONINFORMATION);
		return false;
	}
	std::string floor, room, table_no;
	CComboBox combo(hwnd, IDC_TABLE_FLOOR_COMBO);
	combo.GetComboBoxText(floor);              // 获取楼层名
	room = table_list.GetItem(select, 0);      // 获取房间名
	table_no = table_list.GetItem(select, 1);  // 获取台号
		CTableInfo table;
		table.DeleteTable(floor.c_str(), room.c_str(), table_no.c_str());
		CComboBox combox;
		//清空显示
		combox.Initialization(hwnd,IDC_C_FLOOR_NAME);
		combox.DeleteAllString();
		combox.Initialization(hwnd,IDC_C_ROOM_NAME);
		combox.DeleteAllString();
		CEdit edit;
		edit.Initialization(hwnd,IDC_E_TABLE_NO);
		edit.Empty();
		edit.Initialization(hwnd,IDC_E_TABLE_NUM);
		edit.Empty();
		InitTableList(hwnd, IDC_L_TABLE_INFO, floor.c_str(), 0);  // 更新
	return true;
}


/*
 * 说明：
 *     根据楼层名，初始化房间下拉列表，先该楼层下的房间信息
 * 参数：
 *    hwnd [in] 父窗口句柄
 *    floor_name [in] 楼层名称
 *    id   [in] 下拉列表的编号
 * 返回值：
 *    成功返回true,
 */
bool InitRoomCombo(HWND hwnd,const char *floor_name, UINT id)
{
	CComboBox room_name(hwnd, id);
	RoomInfo room_info;
	room_info.GetRoomName(floor_name);  // 获取楼层下的房间名称记录集
	room_name.DeleteAllString();
	while (!room_info.IsEOF())
	{
		room_name.AddString(room_info.room_name());
	} 
	return true;
}
