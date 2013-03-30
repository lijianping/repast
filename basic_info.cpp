#include "basic_info.h"
#include "Commodity.h"


BOOL CALLBACK BasicInfoProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static RECT tab_rect;
	
	static PageCtrl p_Commodiy;
	static HINSTANCE hInstance;
	switch (msg)
	{
	case WM_INITDIALOG:
		{
		    TreeCtrl category_tree;
			hInstance = (HINSTANCE)lParam;
			HTREEITEM tree_parent;
			std::string error;
			category_tree.Initialization(hwnd, IDC_TREE_COMMODITY);
			try {
				ComMainCateForm comodity_main;//����Ʒ����
				comodity_main.GetMainCateName();
				while(!comodity_main.IsEOF())
				{
					std::string main_name(comodity_main.name());
					tree_parent = category_tree.InsertRootItem(main_name.c_str()); // ����������ڵ�
					ChildCateForm comdity_child;//����Ʒ����
					if (comdity_child.GetChildCateName(comodity_main.name(), error)) {       // ��ȡ�������Ӧ���ӷ�������
						while(!comdity_child.IsEOF())
						{
							std::string child_name(comdity_child.cate_name());
							HTREEITEM child_node;
							// ������Ʒ�������Ʋ�ѯ��Ʒ���ٲ�����Ӧ�ĸ��ڵ���
							child_node = category_tree.InsertChildItem(tree_parent, child_name.c_str());
						}
					}
				} 
			} catch(Err &err) {
				MessageBox(hwnd, err.what(), TEXT("��Ʒ����"), MB_ICONERROR);
				return FALSE;
			}
			InitBasicInfoList(hwnd, IDC_BASIC_INFO);
//			ShowCommodity(hwnd);//ִ�в�ѯ����ʾ��ѯ���
		return TRUE;
		}
	case WM_NOTIFY:
		{
			switch(LOWORD(wParam))
			{
				case IDC_TREE_COMMODITY:
					{
						if (((LPNMHDR)lParam)->code == NM_DBLCLK)  { // ˫�����οؼ��е�һ��
							TreeCtrl basic_info(hwnd, IDC_TREE_COMMODITY);
							HTREEITEM select = basic_info.GetSelectedItem();
							if (!select) {   // Ϊ�գ��˳�
								break;
							}
							char current_item_text[512];
							basic_info.GetItem(select, 512, current_item_text);
							HTREEITEM parent_node = basic_info.GetParent(select);
							if (parent_node) {  // ��ʾ�η�������Ʒ��Ϣ
								char parent_item_text[512];
								basic_info.GetItem(parent_node, 512, parent_item_text);
								try {
									CCommodity commodity_info;
									commodity_info.GetCommodityNameSet(parent_item_text, current_item_text);
									CListView basic_list(hwnd, IDC_BASIC_INFO);
									basic_list.DeleteAllItems();
									int i = 0;
									while (!commodity_info.IsEOF()) {
										basic_list.InsertItem(i, commodity_info.no());
										basic_list.SetItem(i, 1, commodity_info.name());
										basic_list.SetItem(i, 2, commodity_info.purchase_price());
										basic_list.SetItem(i, 3, commodity_info.quantity());
										basic_list.SetItem(i, 4, commodity_info.unit());
										basic_list.SetItem(i, 5, commodity_info.sale_price());
										basic_list.SetItem(i, 6, commodity_info.register_date());
										i++;
									}
								} catch (Err &err) {
									MessageBox(hwnd, err.what(), TEXT("TABLE INFOR"), MB_ICONINFORMATION);
									return FALSE;
								}
							} else {   // ��ʾ����������Ʒ��Ϣ
								try {
									CCommodity commodity_info;
									commodity_info.GetCommodityNameSet(current_item_text);
									CListView basic_list(hwnd, IDC_BASIC_INFO);
									basic_list.DeleteAllItems();
									int i = 0;
									while (!commodity_info.IsEOF()) {
										basic_list.InsertItem(i, commodity_info.no());
										basic_list.SetItem(i, 1, commodity_info.name());
										basic_list.SetItem(i, 2, commodity_info.purchase_price());
										basic_list.SetItem(i, 3, commodity_info.quantity());
										basic_list.SetItem(i, 4, commodity_info.unit());
										basic_list.SetItem(i, 5, commodity_info.sale_price());
										basic_list.SetItem(i, 6, commodity_info.register_date());
										i++;
									}
								} catch (Err &err) {
									MessageBox(hwnd, err.what(), TEXT("TABLE INFOR"), MB_ICONINFORMATION);
									return FALSE;
								}
							} // end else
						}  // end first if
						break;
					}
			}  // end case IDC_TREE_COMMODITY
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case IDC_BASIC_INFO_ADD:
				{
					CommodityInfo commodity_info;
					commodity_info.menu_id = IDC_BASIC_INFO_MODIFY;
                    DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_EDIT_COMMODITY),hwnd,EditCommodityProc, (long)&commodity_info);
					break;
				}
			case IDC_BASIC_INFO_MODIFY:
				{
					CListView commodity_list(hwnd, IDC_BASIC_INFO);
					int select = commodity_list.GetSelectionMark();
					CommodityInfo commodity_info;
					commodity_info.menu_id = IDC_BASIC_INFO_MODIFY;
					commodity_info.commodity_no = commodity_list.GetItem(select, 0);
					commodity_info.commodity_name = commodity_list.GetItem(select, 1);
					commodity_info.commodity_purchase = commodity_list.GetItem(select, 2);
					commodity_info.commodity_sum = commodity_list.GetItem(select, 3);
					commodity_info.commodity_unit = commodity_list.GetItem(select, 4);
					commodity_info.commodity_category = commodity_list.GetItem(select, 5);
					commodity_info.commodity_sale = commodity_list.GetItem(select, 6);
					DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_EDIT_COMMODITY), hwnd, \
						           EditCommodityProc, (long)&commodity_info);
					break;
				}
			case IDC_BASIC_EDIT_CATEGORY:
				{
					DialogBox(hInstance, MAKEINTRESOURCE(IDD_EDIT_COMMODITY_CATEGORY),hwnd,EditCategoryProc);
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
	return false;
}

BOOL CALLBACK EditCategoryProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_INITDIALOG:
		{
			CListView category_list;
			category_list.Initialization(hwnd, IDC_E_COMMODITY_CATEGORY);
			category_list.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			if (-1 == category_list.InsertColumn(0, 100, "�����") ||
				-1 == category_list.InsertColumn(1, 100, "�������"))
			{
				MessageBox(hwnd, TEXT("��ʼ����Ʒ����б�ʧ�ܣ�"), TEXT("����"), MB_OK);
				EndDialog(hwnd,HIWORD(wParam));	
				return TRUE;
			}
/*			if (false == ShowCategoryList(hwnd,IDC_E_COMMODITY_CATEGORY))
			{
				MessageBox(hwnd, TEXT("��ʾ��Ʒ����б�ʧ�ܣ�"), TEXT("����"), MB_OK);
				EndDialog(hwnd,HIWORD(wParam));	
				return TRUE;
			}*/
		}
	case  WM_NOTIFY:
		{
			switch(LOWORD(wParam))
			{
			case IDC_E_COMMODITY_CATEGORY:
				{
					if (((LPNMHDR)lParam)->code == NM_CLICK)/*����б��е�һ��*/
					{
						int index=0;
						CEdit e_name,e_id;
						CListView category_list;
						category_list.Initialization(hwnd, IDC_E_COMMODITY_CATEGORY);
						e_id.Initialization(hwnd, IDC_E_CATEGORY_ID);
					    e_name.Initialization(hwnd, IDC_E_CATEGORY_NAME);
						index = category_list.GetSelectionMark();
						e_id.SetEditText(category_list.GetItem(index,0));
						e_name.SetEditText(category_list.GetItem(index,1));
					}
					break;
				}
			}
			return TRUE;
		}
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_CATEGORY_ADD:
			{
				CEdit e_name,e_id;
				std::string error;
				std:: string id;
				std::string name;
		
				e_id.Initialization(hwnd,IDC_E_CATEGORY_ID);
				e_name.Initialization(hwnd, IDC_E_CATEGORY_NAME);
				
				e_id.GetEditText(id);
				e_name.GetEditText(name);
				CCommodityCategoryForm category;
				if (category.InsertCategory(id,name,error))
				{
			    	MessageBox(hwnd, TEXT("�����Ʒ������Ϣ�ɹ���"), TEXT("�ɹ�"), MB_OK);
					e_id.SetEditText("");
					e_name.SetEditText("");
					ShowCategoryList(hwnd,IDC_E_COMMODITY_CATEGORY);
				}
				else
				{
					MessageBox(hwnd, error.c_str(), TEXT("����"), MB_OK);
				}
				break;
			}	/*TODO: ������������*/
		case IDC_CATEGORY_MODIFY:
			{
				CEdit e_name,e_id;
				CListView category_list;
				int list_index;
				std::string category_no;
				std::string category_old_no;
				std::string category_name;
				std::string error;

				category_list.Initialization(hwnd, IDC_E_COMMODITY_CATEGORY);
				list_index = category_list.GetSelectionMark();
				if (-1 == list_index)
				{
					MessageBox(hwnd, TEXT("�����б���ѡ��һ��"), TEXT("��ʾ"), MB_OK);
					break;
				}
				category_old_no = category_list.GetItem(list_index, 0);
				e_id.Initialization(hwnd,IDC_E_CATEGORY_ID);
				e_name.Initialization(hwnd, IDC_E_CATEGORY_NAME);
				e_id.GetEditText(category_no);
				e_name.GetEditText(category_name);
				CCommodityCategoryForm  category;
				if (category.UpdateCategory(category_old_no, category_no, category_name,error))
				{
					MessageBox(hwnd, TEXT("�޸���Ʒ������Ϣ�ɹ���"), TEXT("�ɹ�"), MB_OK);
					e_id.SetEditText("");
					e_name.SetEditText("");
					ShowCategoryList(hwnd,IDC_E_COMMODITY_CATEGORY);
				}
				else
				{
					MessageBox(hwnd, error.c_str(), TEXT("����"), MB_OK);
				}	
				break;
			}
		case IDC_CATEGORY_DELETE:
			{
		    	CEdit e_name,e_id;
		    	e_id.Initialization(hwnd,IDC_E_CATEGORY_ID);
				e_name.Initialization(hwnd, IDC_E_CATEGORY_NAME);

				CListView category_list;
				int list_index;
				std::string category_no;
				std::string error;
				category_list.Initialization(hwnd, IDC_E_COMMODITY_CATEGORY);
				list_index = category_list.GetSelectionMark();
				if (-1 == list_index)
				{
					MessageBox(hwnd, TEXT("�����б���ѡ��һ��"), TEXT("��ʾ"), MB_OK);
					break;
				}
				if (MessageBox(hwnd, TEXT("ɾ����Ʒ���ཫ��ɾ���˷��༰����������Ʒ��\n\n       ���ٴ�ȷ���Ƿ�ɾ����"),\
					TEXT("��Ҫ��ʾ"), MB_YESNOCANCEL)==IDYES)
				{
						category_no = category_list.GetItem(list_index,0);/*��ȡ�б���ѡ���һ�еĵ�һ���ֶ�*/
						CCommodityCategoryForm category;
						if (category.DeleteCategory(category_no,error))
						{
							MessageBox(hwnd, TEXT("ɾ����Ʒ������Ϣ�ɹ���"), TEXT("�ɹ�"), MB_OK);
							e_id.SetEditText("");
							e_name.SetEditText("");
							ShowCategoryList(hwnd,IDC_E_COMMODITY_CATEGORY);
						}
						else
						{
							MessageBox(hwnd, error.c_str(), TEXT("����"), MB_OK);
						}	
				}
				break;
			}
		case IDC_CATEGORY_CANCEL:
			{
				EndDialog(hwnd, HIWORD(wParam));
		    	return TRUE;
			}
		
		}
		return TRUE;
	case WM_CLOSE:
		{
			EndDialog(hwnd, HIWORD(wParam));
			return TRUE;
		}
	}
return FALSE;
}

BOOL CALLBACK EditCommodityProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static CommodityInfo commodity_info;
	switch(msg)
	{
	case WM_INITDIALOG:
		{
			CommodityInfo *info = (CommodityInfo *)lParam;
			commodity_info.menu_id = info->menu_id;
			if (info->menu_id == IDC_BASIC_INFO_MODIFY) {
				commodity_info.commodity_no = info->commodity_no;
				commodity_info.commodity_name = info->commodity_name;
				commodity_info.commodity_category = info->commodity_category;
				commodity_info.commodity_purchase = info->commodity_purchase;
				commodity_info.commodity_sale = info->commodity_sale;
				commodity_info.commodity_sum = info->commodity_sum;
				commodity_info.commodity_unit = info->commodity_unit;
				SetDlgItemText(hwnd, IDC_E_COMMODITY_ID, info->commodity_no.c_str());
				SetDlgItemText(hwnd, IDC_E_COMMODITY_NAME, info->commodity_name.c_str());
				SetDlgItemText(hwnd, IDC_E_COMMODITY_PURCHASE, info->commodity_purchase.c_str());
				SetDlgItemText(hwnd, IDC_E_COMMODITY_SUM, info->commodity_sum.c_str());
				SetDlgItemText(hwnd, IDC_E_COMMODITY_CATEGORY, info->commodity_category.c_str());
				SetDlgItemText(hwnd, IDC_E_COMMODITY_UNIT, info->commodity_unit.c_str());
				SetDlgItemText(hwnd, IDC_E_COMMODITY_SALE, info->commodity_sale.c_str());
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


bool InitCommodityTree(HWND parent_hwnd, UINT id)
{
	return true;
}

bool InitBasicInfoList(HWND parent_hwnd, UINT id)
{
	CListView staff_list;
	/* Initialization the list view */
	staff_list.Initialization(parent_hwnd, id);	
	/* Set the full row selected and grid lines */
	staff_list.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	/* Insert the list view's column title */
	if (-1 != staff_list.InsertColumn(0, 100, "��Ʒ���") &&
		-1 != staff_list.InsertColumn(1, 100, "��Ʒ����") &&
		-1 != staff_list.InsertColumn(2, 100, "��Ʒ����") &&
		-1 != staff_list.InsertColumn(3, 100, "��Ʒ����") &&
		-1 != staff_list.InsertColumn(4, 100, "��Ʒ��λ") &&
		-1 != staff_list.InsertColumn(6, 100, "��Ʒ����") &&
		-1 != staff_list.InsertColumn(7, 100, "�Ǽ�����"))
	{
		return true;
	}
		return false;
}



bool ShowCommodity(HWND hwnd)
{
	
	return true;
}

bool ShowCategoryList(HWND hwnd, UINT id)
{
	CListView category_list;
	category_list.Initialization(hwnd, IDC_E_COMMODITY_CATEGORY);
	category_list.DeleteAllItems();
	CCommodityCategoryForm comodity_category;/*��Ʒ����*/
	comodity_category.GetRecordSet();
	int item=0;
	while(!comodity_category.IsEOF())
	{
		category_list.InsertItem(item, comodity_category.no());
		category_list.SetItem(item, 1, comodity_category.name());
		item++;
	}
	return true;
}
