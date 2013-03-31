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
			hInstance = (HINSTANCE)lParam;
			ShowCommodityTree(hwnd,IDC_TREE_COMMODITY);
			InitBasicInfoList(hwnd, IDC_BASIC_INFO);
		return TRUE;
		}
	case WM_NOTIFY:
		{
			switch(LOWORD(wParam))
			{
				case IDC_TREE_COMMODITY:
					{
						if (((LPNMHDR)lParam)->code == NM_DBLCLK)  { // 双击树形控件中的一项
							TreeCtrl basic_info(hwnd, IDC_TREE_COMMODITY);
							HTREEITEM select = basic_info.GetSelectedItem();
							if (!select) {   // 为空，退出
								break;
							}
							char current_item_text[512];
							basic_info.GetItem(select, 512, current_item_text);
							HTREEITEM parent_node = basic_info.GetParent(select);
							if (parent_node) {  // 显示次分类下商品信息
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
							} else {   // 显示主分类下商品信息
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
				    ShowCommodityTree(hwnd,IDC_TREE_COMMODITY);
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
			ShowCommodityTree(hwnd, IDC_E_COMMODITY_CATEGORY);
		}
	case  WM_NOTIFY:
		{
			//TODO:响应树形控件
			switch(LOWORD(wParam))
			{
			case IDC_E_COMMODITY_CATEGORY:
				{
					if (((LPNMHDR)lParam)->code == NM_DBLCLK)//点击树形控件中的一项
					{
						try
						{
							RespondTreeDBClick(hwnd);
						}
						catch (Err &err)
						{
							MessageBox(hwnd, err.what(), TEXT("点击树形控件出错"), MB_ICONINFORMATION);
							return false;
						}
					
					}
					break;
				}//end of "tree" case
			}
			return TRUE;
		}
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{

		case IDC_C_ADD_CHILD:
			{
				try
				{
					RespondTreeDBClick(hwnd);
				}
				catch (Err &err)
				{
					MessageBox(hwnd, err.what(), TEXT("点击树形控件出错"), MB_ICONINFORMATION);
					return false;
				}
				break;
			}
		case IDC_CATEGORY_ADD:
			{
				try
				{
					if (AddComCategory(hwnd))
					{
						MessageBox(hwnd, TEXT("添加商品分类信息成功！"), TEXT("成功"), MB_OK);
						ShowCommodityTree(hwnd, IDC_E_COMMODITY_CATEGORY);
					}
				}
				catch (Err &err)
				{
					MessageBox(hwnd, err.what(), TEXT("添加分类失败"), MB_ICONINFORMATION);
					return false;
				}
				break;
			}	
		case IDC_CATEGORY_MODIFY:
			{
				try
				{
					if (UpdateComCategory(hwnd))
					{
						MessageBox(hwnd, TEXT("修改商品分类信息成功！"), TEXT("成功"), MB_OK);
						ShowCommodityTree(hwnd, IDC_E_COMMODITY_CATEGORY);
					}
				}
				catch (Err &err)
				{
					MessageBox(hwnd, err.what(), TEXT("修改分类失败"), MB_ICONINFORMATION);
					return false;
				}
				break;
			}
		case IDC_CATEGORY_DELETE:
			{
				try
				{		
					if (DeleteComCategory(hwnd))
					{
						MessageBox(hwnd, TEXT("删除商品分类信息成功！"), TEXT("删除成功"), MB_OK);
						ShowCommodityTree(hwnd, IDC_E_COMMODITY_CATEGORY);
					}
				}
				catch (Err &err)
				{
					MessageBox(hwnd, err.what(), TEXT("删除分类失败"), MB_ICONINFORMATION);
					return false;
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
	if (-1 != staff_list.InsertColumn(0, 100, "商品编号") &&
		-1 != staff_list.InsertColumn(1, 100, "商品名称") &&
		-1 != staff_list.InsertColumn(2, 100, "商品进价") &&
		-1 != staff_list.InsertColumn(3, 100, "商品数量") &&
		-1 != staff_list.InsertColumn(4, 100, "商品单位") &&
		-1 != staff_list.InsertColumn(6, 100, "商品卖价") &&
		-1 != staff_list.InsertColumn(7, 100, "登记日期"))
	{
		return true;
	}
		return false;
}



bool ShowCommodity(HWND hwnd)
{
	
	return true;
}

/*
 * 说明：
 *     在树形控件上显示商品分类信息
 * 参数：
 *     parent_hwnd   [in] 父窗口句柄
 *     id            [in] 树形控件ID
 * 返回值：
 *     成功返回true,否则返回false
 */
bool ShowCommodityTree(HWND hwnd, UINT id)
{
	HTREEITEM tree_parent;
	HTREEITEM child_node;
	std::string error;
	TreeCtrl category_tree(hwnd,id);
	category_tree.DeleteAllItems();
		ComMainCateForm comodity_main;//主商品分类
		comodity_main.GetMainCateName();
		while(!comodity_main.IsEOF())
		{
			std::string main_name(comodity_main.name());
			tree_parent = category_tree.InsertRootItem(main_name.c_str()); // 插入主分类节点
			ChildCateForm comdity_child;//子商品分类
			if (comdity_child.GetChildCateName(comodity_main.name(), error)) {       // 获取主分类对应的子分类名称
				while(!comdity_child.IsEOF())
				{
					std::string child_name(comdity_child.cate_name());
					// 根据商品分类名称查询商品，再插入相应的根节点下
					child_node = category_tree.InsertChildItem(tree_parent, child_name.c_str());
				}
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
	int item=0;
	while(!comodity_category.IsEOF())
	{
		category_list.InsertItem(item, comodity_category.no());
		category_list.SetItem(item, 1, comodity_category.name());
		item++;
	}
	return true;
}


/*
 * 说明：
 *     响应双击树形控件消息，显示相应的分类信息
 * 参数：
 *     hwnd  [in] 父窗口句柄
 * 返回值：
 *     成功返回true,失败返回false
 **/
bool RespondTreeDBClick(HWND hwnd)
{
	char category_name[33];
	CEdit e_name,e_id,e_cate_cate,e_paren_cate_name;
	CButton add_child;
	add_child.Initialization(hwnd,IDC_C_ADD_CHILD);
	TreeCtrl category_tree(hwnd,IDC_E_COMMODITY_CATEGORY);
	e_id.Initialization(hwnd, IDC_E_CATEGORY_ID);
	e_name.Initialization(hwnd, IDC_E_CATEGORY_NAME);
	e_cate_cate.Initialization(hwnd, IDC_E_CATEGORY_CATE);
	e_paren_cate_name.Initialization(hwnd, IDC_E_PARENT_CATE_NAME);
	HTREEITEM select = category_tree.GetSelectedItem();
	if (!select) {   // 为空，退出
		MessageBox(hwnd, TEXT("请选中树形控件中的一项"), TEXT("提示"), MB_ICONINFORMATION);
		return false;
	}
	category_tree.GetItem(select,sizeof(category_name),category_name);
	HTREEITEM parent_node=category_tree.GetParent(select);//获取父节点
	if (parent_node)//有父节点，则当前选择的是次分类
	{
		add_child.EnableWindow(false);//禁用
			char category_id[17];
			e_cate_cate.SetEditText("子分类");
			char category_main_name[33];
			category_tree.GetItem(parent_node,sizeof(category_main_name),category_main_name);//获取主分类名称
			e_paren_cate_name.SetEditText(category_main_name);
			ChildCateForm child_cate;
			child_cate.GetChildCateByDname(category_main_name,category_name);//根据主分类和子分类名称获取子分类编号
			e_id.SetEditText(itoa(child_cate.cate_no(),category_id,10));
	}
	else//是父节点,显示主分类信息
	{
		add_child.EnableWindow(true);//起用
		 if (true == add_child.IsChecked())
		 {
			 e_cate_cate.SetEditText("子分类");
			 e_paren_cate_name.SetEditText(category_name);
			 e_id.Empty();
			 e_name.Empty();
			 return true;

		 }
			char main_no[17];
			e_cate_cate.SetEditText("主分类");
			e_paren_cate_name.SetEditText("无");
			ComMainCateForm main_cate;
			main_cate.GetMainCateByName(category_name);
			e_id.SetEditText(itoa(main_cate.no(),main_no,10));
	}
	e_name.SetEditText(category_name);
	return true;
}


/*
 * 说明：
 *     添加商品分类信息
 * 参数：
 *     hwnd  [in] 父窗口句柄
 * 返回值：
 *     成功返回true,失败返回false
 **/
bool AddComCategory(HWND hwnd)
{
		
		std::string cate_cate_name;
		CEdit e_name,e_id,e_cate_cate,e_parent_cate_name;
		e_id.Initialization(hwnd, IDC_E_CATEGORY_ID);
		e_name.Initialization(hwnd, IDC_E_CATEGORY_NAME);
		e_cate_cate.Initialization(hwnd, IDC_E_CATEGORY_CATE);
		e_parent_cate_name.Initialization(hwnd,IDC_E_PARENT_CATE_NAME);
		e_cate_cate.GetEditText(cate_cate_name);
		if (cate_cate_name=="")
		{
			MessageBox(hwnd, TEXT("请选中树形控件中的一项"), TEXT("提示"), MB_ICONINFORMATION);
			return false;
		}
		if (cate_cate_name=="主分类")
		{
			COMMAINCATE main_cate;
			e_id.GetEditText(main_cate.no);
			main_cate.old_no=main_cate.no;
			e_name.GetEditText(main_cate.name);
			ComMainCateForm main_cate_form;
			main_cate_form.AddMainCate(&main_cate);
			e_parent_cate_name.Empty();
			e_cate_cate.Empty();
			e_id.Empty();
			e_name.Empty();
		}
		else//子分类
		{
			COMCHILDCATE child_cate;
			e_id.GetEditText(child_cate.child_no);
			e_parent_cate_name.GetEditText(child_cate.main_name);
			child_cate.old_child_no=child_cate.child_no;
			e_name.GetEditText(child_cate.child_name);
			ChildCateForm child_cate_form;
			child_cate_form.AddChildCate(&child_cate);
			e_parent_cate_name.Empty();
			e_cate_cate.Empty();
			e_id.Empty();
			e_name.Empty();
			CButton add_child;
			add_child.Initialization(hwnd,IDC_C_ADD_CHILD);
			if (add_child.IsChecked())
			{
				add_child.SetChecked(FALSE);
			}
		}	
	return true;
}


/*
 * 说明：
 *     修改/更新商品分类信息
 * 参数：
 *     hwnd  [in] 父窗口句柄
 * 返回值：
 *     成功返回true,失败返回false
 **/
bool UpdateComCategory(HWND hwnd)
{
	CEdit e_name,e_id,e_cate_cate,e_parent_cate_name;
	e_id.Initialization(hwnd, IDC_E_CATEGORY_ID);
	e_name.Initialization(hwnd, IDC_E_CATEGORY_NAME);
	e_cate_cate.Initialization(hwnd, IDC_E_CATEGORY_CATE);
	e_parent_cate_name.Initialization(hwnd,IDC_E_PARENT_CATE_NAME);
	char category_name[33];
	TreeCtrl category_tree(hwnd,IDC_E_COMMODITY_CATEGORY);
	HTREEITEM select = category_tree.GetSelectedItem();
	if (!select) {
		MessageBox(hwnd, TEXT("请选中树形控件中的一项"), TEXT("提示"), MB_ICONINFORMATION);
		return false;
	}
	int ret=MessageBox(hwnd,TEXT("修改主分类的同时会修改此分类下所有的子分类和所属的商品信息\n 请确认是否修改？"),\
		TEXT("确认修改"),MB_YESNO);
	if(IDYES==ret)
	{
		category_tree.GetItem(select, sizeof(category_name),category_name);
		HTREEITEM parent_node=category_tree.GetParent(select);//获取父节点
		if (parent_node)//有父节点，则当前选择的是次分类
		{
			char main_cate_name[33];
			char tmp[17];
			category_tree.GetItem(parent_node,sizeof(main_cate_name),main_cate_name);//获取主分类名称
			ChildCateForm child_cate_form;
			child_cate_form.GetChildCateByDname(main_cate_name,category_name);//根据主分类和子分类名称获取子分类编号
			COMCHILDCATE struct_child_cate;
			struct_child_cate.main_name=main_cate_name;//保存主分类名称
			struct_child_cate.old_child_no = itoa(child_cate_form.cate_no(),tmp,10);//保存原来的子分类编号
			child_cate_form.CloseCursor();//关闭游标，以便下一次语句执行
			e_id.GetEditText(struct_child_cate.child_no);//获取子分类编号
			e_name.GetEditText(struct_child_cate.child_name);//获取子分类名称
			child_cate_form.UpdateChildCate(&struct_child_cate);//执行更新操作
			e_parent_cate_name.Empty();
			e_cate_cate.Empty();
			e_id.Empty();
			e_name.Empty();
		}
		else
		{
			char tmp[33];
			ComMainCateForm main_category;
			main_category.GetMainCateByName(category_name);
			main_category.CloseCursor();//关闭游标，再执行下一条语句
			COMMAINCATE st_main_cate;
			st_main_cate.old_no = itoa(main_category.no(),tmp,10);
			e_id.GetEditText(st_main_cate.no);
			e_name.GetEditText(st_main_cate.name);
			ComMainCateForm main_cate_info;
			main_cate_info.UpdateMainCate(&st_main_cate);
			e_parent_cate_name.Empty();
			e_cate_cate.Empty();
			e_id.Empty();
			e_name.Empty();
		}
	}
	return true;
}

/*
 * 说明：
 *     删除商品分类信息
 * 参数：
 *     hwnd  [in] 父窗口句柄
 * 返回值：
 *     成功返回true,失败返回false
 **/
bool DeleteComCategory(HWND hwnd)
{
	CEdit e_name,e_id,e_cate_cate,e_parent_cate_name;
	e_id.Initialization(hwnd, IDC_E_CATEGORY_ID);
	e_name.Initialization(hwnd, IDC_E_CATEGORY_NAME);
	e_cate_cate.Initialization(hwnd, IDC_E_CATEGORY_CATE);
	e_parent_cate_name.Initialization(hwnd,IDC_E_PARENT_CATE_NAME);
		char category_name[33];
		TreeCtrl category_tree(hwnd,IDC_E_COMMODITY_CATEGORY);
		HTREEITEM select = category_tree.GetSelectedItem();
		if (!select) {
			MessageBox(hwnd, TEXT("请选中树形控件中的一项"), TEXT("提示"), MB_ICONINFORMATION);
			return false;
		}
		int ret=MessageBox(hwnd,TEXT("删除主分类的同时会删除此分类下所有的子分类和所属的商品信息\n 请确认是否删除"),\
			TEXT("确认删除"),MB_YESNO);
		if(IDYES==ret)
		{
			category_tree.GetItem(select, sizeof(category_name),category_name);
			HTREEITEM parent_node=category_tree.GetParent(select);//获取父节点
			if (parent_node)//有父节点，则当前选择的是次分类
			{
				char main_cate_name[33];
				char tmp[17];
				category_tree.GetItem(parent_node,sizeof(main_cate_name),main_cate_name);//获取主分类名称
				ChildCateForm child_cate_form;
				child_cate_form.GetChildCateByDname(main_cate_name,category_name);//根据主分类和子分类名称获取子分类编号
				child_cate_form.CloseCursor();//关闭游标，以便下一次语句执行
				child_cate_form.DeleteChildCate(itoa(child_cate_form.cate_no(),tmp,10));//执行删除操作
				e_parent_cate_name.Empty();
				e_cate_cate.Empty();
				e_id.Empty();
				e_name.Empty();
			}
			else
			{
				char tmp[17];
				ComMainCateForm main_category;
				main_category.GetMainCateByName(category_name);
				main_category.CloseCursor();//关闭游标，在执行下一条语句
				main_category.DeleteMainCate(itoa(main_category.no(),tmp,10));
			}
			e_parent_cate_name.Empty();
			e_cate_cate.Empty();
			e_id.Empty();
			e_name.Empty();
		}
	return true;
}
