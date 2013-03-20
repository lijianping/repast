#include "basic_info.h"



BOOL CALLBACK BasicInfoProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static TreeCtrl commodity_tree;
	static HINSTANCE hInstance = (HINSTANCE)lParam;
	switch (msg)
	{
	case WM_INITDIALOG:
		{
			HTREEITEM tree_parent;
			CCommodity commodity;/*��Ʒ������Ϣ*/
			std::string error;
			commodity_tree.Initialization(hwnd, IDC_TREE_COMMODITY);
			CCommodityCategoryForm comodity_category;/*��Ʒ����*/
			comodity_category.GetRecordSet();
			comodity_category.MoveFirst();
			while(!comodity_category.IsEOF())
			{
				tree_parent = commodity_tree.InsertRootItem(comodity_category.name());/*���븸�ڵ�*/
				commodity.SelectByName(comodity_category.name(), error);
				while(!commodity.IsEOF())
				{
					commodity_tree.InsertChildItem(tree_parent, commodity.name());/*������Ʒ�������Ʋ�ѯ��Ʒ���ٲ�����Ӧ�ĸ��ڵ���*/
					commodity.MoveNext();
				}
				comodity_category.MoveNext();
			}
	//		InitCommodityTree(hwnd, IDC_TREE_COMMODITY);/*TODO:��δ����*/
			InitBasicInfoList(hwnd, IDC_BASIC_INFO);
			ShowCommodity(hwnd);/*ִ�в�ѯ����ʾ��ѯ���*/
		
		return TRUE;
		}
	case WM_NOTIFY:
		{
		case IDC_TREE_COMMODITY:
			{
				if (((LPNMHDR)lParam)->code == NM_DBLCLK) 
				{
					HTREEITEM selection ;
					selection = commodity_tree.GetSelectedItem();
					commodity_tree.EnsureVisible(selection);
					char text[256];
					if (commodity_tree.GetItem(sizeof(text),text))
					{
						std::string error;
						CCommodity commodity;/*��Ʒ������Ϣ*/
						commodity.SelectByName(text, error);/*ͨ����Ʒ���ƻ���Ʒ�������Ʋ��Ҿ�����Ʒ*/
					
						CListView staff_list;
						/* Initialization the list view object */
						staff_list.Initialization(hwnd, IDC_BASIC_INFO);
						/* Clean the list view */
						staff_list.DeleteAllItems();
						int item = 0;
						while (!commodity.IsEOF())
						{
							/* Insert item(s) into the list view */
							staff_list.InsertItem(item, commodity.no());
							staff_list.SetItem(item, 1, commodity.name());
							staff_list.SetItem(item, 2, commodity.purchase_price());
							staff_list.SetItem(item, 3, commodity.sum());
							staff_list.SetItem(item, 4, commodity.unit());
							staff_list.SetItem(item, 5, commodity.category());
							staff_list.SetItem(item, 6, commodity.sale_price());
							staff_list.SetItem(item, 7, commodity.register_date());
							commodity.MoveNext();
							item++;
						}
					}
					else
					{
						MessageBox(hwnd, TEXT("Something Error!"), TEXT("HIT"), MB_ICONINFORMATION);
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
	return false;
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
    	-1 != staff_list.InsertColumn(5, 100, "��Ʒ���") &&
		-1 != staff_list.InsertColumn(6, 100, "��Ʒ����") &&
		-1 != staff_list.InsertColumn(7, 100, "�Ǽ�����"))
	{
		return true;
	}
		return false;
}



bool ShowCommodity(HWND hwnd)
{
	CCommodity commodity;
	commodity.GetRecordSet();
	/* Move to the first of the record set */
	commodity.MoveFirst();  
	if (0 == strcmp("",commodity.no()))
	{
		CListView staff_list;
		/* Initialization the list view object */
		staff_list.Initialization(hwnd, IDC_BASIC_INFO);
		/* Clean the list view */
		staff_list.DeleteAllItems();
	//	error = "��ƥ������";
		return false;
	}
	else
	{
		CListView staff_list;
		/* Initialization the list view object */
		staff_list.Initialization(hwnd, IDC_BASIC_INFO);
		/* Clean the list view */
		staff_list.DeleteAllItems();
		int item = 0;
		while (!commodity.IsEOF())
		{
			/* Insert item(s) into the list view */
			staff_list.InsertItem(item, commodity.no());
			staff_list.SetItem(item, 1, commodity.name());
			staff_list.SetItem(item, 2, commodity.purchase_price());
			staff_list.SetItem(item, 3, commodity.sum());
			staff_list.SetItem(item, 4, commodity.unit());
			staff_list.SetItem(item, 5, commodity.category());
			staff_list.SetItem(item, 6, commodity.sale_price());
			staff_list.SetItem(item, 7, commodity.register_date());
			commodity.MoveNext();
			item++;
		}
	}
	return true;
}


