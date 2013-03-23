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
			CCommodity commodity;/*商品具体信息*/
			std::string error;
			commodity_tree.Initialization(hwnd, IDC_TREE_COMMODITY);
			CCommodityCategoryForm comodity_category;/*商品分类*/
			comodity_category.GetRecordSet();
			comodity_category.MoveFirst();
			while(!comodity_category.IsEOF())
			{
				tree_parent = commodity_tree.InsertRootItem(comodity_category.name());/*插入父节点*/
				commodity.SelectByName(comodity_category.name(), error);
				while(!commodity.IsEOF())
				{
					commodity_tree.InsertChildItem(tree_parent, commodity.name());/*根据商品分类名称查询商品，再插入相应的根节点下*/
					commodity.MoveNext();
				}
				comodity_category.MoveNext();
			}
	//		InitCommodityTree(hwnd, IDC_TREE_COMMODITY);/*TODO:尚未定义*/
			InitBasicInfoList(hwnd, IDC_BASIC_INFO);
			ShowCommodity(hwnd);/*执行查询，显示查询结果*/
		
		return TRUE;
		}
	case WM_NOTIFY:
		{
			switch(LOWORD(wParam))
			{
				case IDC_TREE_COMMODITY:
					{
						if (((LPNMHDR)lParam)->code == NM_DBLCLK) /*双击树形控件中的一项*/
						{
							HTREEITEM selection ;
							selection = commodity_tree.GetSelectedItem();
							commodity_tree.EnsureVisible(selection);
							char text[256];
							if (commodity_tree.GetItem(sizeof(text),text))
							{
								std::string error;
								CCommodity commodity;/*商品具体信息*/
								commodity.SelectByName(text, error);/*通过商品名称或商品分类名称查找具体商品*/
							
								CListView staff_list;
								staff_list.Initialization(hwnd, IDC_BASIC_INFO);
								staff_list.DeleteAllItems();
								int item = 0;
								while (!commodity.IsEOF())
								{
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
						break;
					}
			}
		}

	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case IDC_BASIC_INFO_ADD:
				{
                    DialogBox(hInstance, MAKEINTRESOURCE(IDD_EDIT_COMMODITY),hwnd,EditCommodityProc);
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
			if (-1 == category_list.InsertColumn(0, 100, "类别编号") ||
				-1 == category_list.InsertColumn(1, 100, "类别名称"))
			{
				MessageBox(hwnd, TEXT("初始化商品类别列表失败！"), TEXT("错误"), MB_OK);
				EndDialog(hwnd,HIWORD(wParam));	
				return TRUE;
			}
			if (false == ShowCategoryList(hwnd,IDC_E_COMMODITY_CATEGORY))
			{
				MessageBox(hwnd, TEXT("显示商品类别列表失败！"), TEXT("错误"), MB_OK);
				EndDialog(hwnd,HIWORD(wParam));	
				return TRUE;
			}
		}
	case  WM_NOTIFY:
		{
			switch(LOWORD(wParam))
			{
			case IDC_E_COMMODITY_CATEGORY:
				{
					if (((LPNMHDR)lParam)->code == NM_CLICK)/*点击列表中的一项*/
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
			    	MessageBox(hwnd, TEXT("添加商品分类信息成功！"), TEXT("成功"), MB_OK);
					e_id.SetEditText("");
					e_name.SetEditText("");
					ShowCategoryList(hwnd,IDC_E_COMMODITY_CATEGORY);
				}
				else
				{
					MessageBox(hwnd, error.c_str(), TEXT("错误"), MB_OK);
				}
				break;
			}	/*TODO: 增加其他功能*/
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
					MessageBox(hwnd, TEXT("请在列表中选择一项"), TEXT("提示"), MB_OK);
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
					MessageBox(hwnd, TEXT("修改商品分类信息成功！"), TEXT("成功"), MB_OK);
					e_id.SetEditText("");
					e_name.SetEditText("");
					ShowCategoryList(hwnd,IDC_E_COMMODITY_CATEGORY);
				}
				else
				{
					MessageBox(hwnd, error.c_str(), TEXT("错误"), MB_OK);
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
					MessageBox(hwnd, TEXT("请在列表中选择一项"), TEXT("提示"), MB_OK);
					break;
				}
				if (MessageBox(hwnd, TEXT("删除商品分类将会删除此分类及其所属的商品！\n\n       请再次确认是否删除？"),\
					TEXT("重要提示"), MB_YESNOCANCEL)==IDYES)
				{
						category_no = category_list.GetItem(list_index,0);/*获取列表中选择的一行的第一个字段*/
						CCommodityCategoryForm category;
						if (category.DeleteCategory(category_no,error))
						{
							MessageBox(hwnd, TEXT("删除商品分类信息成功！"), TEXT("成功"), MB_OK);
							e_id.SetEditText("");
							e_name.SetEditText("");
							ShowCategoryList(hwnd,IDC_E_COMMODITY_CATEGORY);
						}
						else
						{
							MessageBox(hwnd, error.c_str(), TEXT("错误"), MB_OK);
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
			commodity_info.commodity_no = info->commodity_no;
			commodity_info.commodity_name = info->commodity_name;
			commodity_info.commodity_category = info->commodity_category;
			commodity_info.commodity_purchase = info->commodity_purchase;
			commodity_info.commodity_sale = info->commodity_sale;
			commodity_info.commodity_sum = info->commodity_sum;
			commodity_info.commodity_unit = info->commodity_unit;
			if (info->menu_id == IDC_BASIC_INFO_MODIFY) {
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
	if (-1 != staff_list.InsertColumn(0, 100, "商品编号") &&
		-1 != staff_list.InsertColumn(1, 100, "商品名称") &&
		-1 != staff_list.InsertColumn(2, 100, "商品进价") &&
		-1 != staff_list.InsertColumn(3, 100, "商品数量") &&
		-1 != staff_list.InsertColumn(4, 100, "商品单位") &&
    	-1 != staff_list.InsertColumn(5, 100, "商品类别") &&
		-1 != staff_list.InsertColumn(6, 100, "商品卖价") &&
		-1 != staff_list.InsertColumn(7, 100, "登记日期"))
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
	//	error = "无匹配结果！";
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

bool ShowCategoryList(HWND hwnd, UINT id)
{
	CListView category_list;
	category_list.Initialization(hwnd, IDC_E_COMMODITY_CATEGORY);
	category_list.DeleteAllItems();
	CCommodityCategoryForm comodity_category;/*商品分类*/
	comodity_category.GetRecordSet();
	comodity_category.MoveFirst();
	int item=0;
	while(!comodity_category.IsEOF())
	{
		category_list.InsertItem(item, comodity_category.no());
		category_list.SetItem(item, 1, comodity_category.name());
		comodity_category.MoveNext();
		item++;
	}
	return true;
}
