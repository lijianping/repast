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
			//TODO:��Ӧ���οؼ�
			switch(LOWORD(wParam))
			{
			case IDC_E_COMMODITY_CATEGORY:
				{
					if (((LPNMHDR)lParam)->code == NM_DBLCLK)//������οؼ��е�һ��
					{
						try
						{
							RespondTreeDBClick(hwnd);
						}
						catch (Err &err)
						{
							MessageBox(hwnd, err.what(), TEXT("������οؼ�����"), MB_ICONINFORMATION);
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
					MessageBox(hwnd, err.what(), TEXT("������οؼ�����"), MB_ICONINFORMATION);
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
						MessageBox(hwnd, TEXT("�����Ʒ������Ϣ�ɹ���"), TEXT("�ɹ�"), MB_OK);
						ShowCommodityTree(hwnd, IDC_E_COMMODITY_CATEGORY);
					}
				}
				catch (Err &err)
				{
					MessageBox(hwnd, err.what(), TEXT("��ӷ���ʧ��"), MB_ICONINFORMATION);
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
						MessageBox(hwnd, TEXT("�޸���Ʒ������Ϣ�ɹ���"), TEXT("�ɹ�"), MB_OK);
						ShowCommodityTree(hwnd, IDC_E_COMMODITY_CATEGORY);
					}
				}
				catch (Err &err)
				{
					MessageBox(hwnd, err.what(), TEXT("�޸ķ���ʧ��"), MB_ICONINFORMATION);
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
						MessageBox(hwnd, TEXT("ɾ����Ʒ������Ϣ�ɹ���"), TEXT("ɾ���ɹ�"), MB_OK);
						ShowCommodityTree(hwnd, IDC_E_COMMODITY_CATEGORY);
					}
				}
				catch (Err &err)
				{
					MessageBox(hwnd, err.what(), TEXT("ɾ������ʧ��"), MB_ICONINFORMATION);
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

/*
 * ˵����
 *     �����οؼ�����ʾ��Ʒ������Ϣ
 * ������
 *     parent_hwnd   [in] �����ھ��
 *     id            [in] ���οؼ�ID
 * ����ֵ��
 *     �ɹ�����true,���򷵻�false
 */
bool ShowCommodityTree(HWND hwnd, UINT id)
{
	HTREEITEM tree_parent;
	HTREEITEM child_node;
	std::string error;
	TreeCtrl category_tree(hwnd,id);
	category_tree.DeleteAllItems();
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
					// ������Ʒ�������Ʋ�ѯ��Ʒ���ٲ�����Ӧ�ĸ��ڵ���
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


/*
 * ˵����
 *     ��Ӧ˫�����οؼ���Ϣ����ʾ��Ӧ�ķ�����Ϣ
 * ������
 *     hwnd  [in] �����ھ��
 * ����ֵ��
 *     �ɹ�����true,ʧ�ܷ���false
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
	if (!select) {   // Ϊ�գ��˳�
		MessageBox(hwnd, TEXT("��ѡ�����οؼ��е�һ��"), TEXT("��ʾ"), MB_ICONINFORMATION);
		return false;
	}
	category_tree.GetItem(select,sizeof(category_name),category_name);
	HTREEITEM parent_node=category_tree.GetParent(select);//��ȡ���ڵ�
	if (parent_node)//�и��ڵ㣬��ǰѡ����Ǵη���
	{
		add_child.EnableWindow(false);//����
			char category_id[17];
			e_cate_cate.SetEditText("�ӷ���");
			char category_main_name[33];
			category_tree.GetItem(parent_node,sizeof(category_main_name),category_main_name);//��ȡ����������
			e_paren_cate_name.SetEditText(category_main_name);
			ChildCateForm child_cate;
			child_cate.GetChildCateByDname(category_main_name,category_name);//������������ӷ������ƻ�ȡ�ӷ�����
			e_id.SetEditText(itoa(child_cate.cate_no(),category_id,10));
	}
	else//�Ǹ��ڵ�,��ʾ��������Ϣ
	{
		add_child.EnableWindow(true);//����
		 if (true == add_child.IsChecked())
		 {
			 e_cate_cate.SetEditText("�ӷ���");
			 e_paren_cate_name.SetEditText(category_name);
			 e_id.Empty();
			 e_name.Empty();
			 return true;

		 }
			char main_no[17];
			e_cate_cate.SetEditText("������");
			e_paren_cate_name.SetEditText("��");
			ComMainCateForm main_cate;
			main_cate.GetMainCateByName(category_name);
			e_id.SetEditText(itoa(main_cate.no(),main_no,10));
	}
	e_name.SetEditText(category_name);
	return true;
}


/*
 * ˵����
 *     �����Ʒ������Ϣ
 * ������
 *     hwnd  [in] �����ھ��
 * ����ֵ��
 *     �ɹ�����true,ʧ�ܷ���false
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
			MessageBox(hwnd, TEXT("��ѡ�����οؼ��е�һ��"), TEXT("��ʾ"), MB_ICONINFORMATION);
			return false;
		}
		if (cate_cate_name=="������")
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
		else//�ӷ���
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

		}	
	return true;
}


/*
 * ˵����
 *     �޸�/������Ʒ������Ϣ
 * ������
 *     hwnd  [in] �����ھ��
 * ����ֵ��
 *     �ɹ�����true,ʧ�ܷ���false
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
		MessageBox(hwnd, TEXT("��ѡ�����οؼ��е�һ��"), TEXT("��ʾ"), MB_ICONINFORMATION);
		return false;
	}
	int ret=MessageBox(hwnd,TEXT("�޸��������ͬʱ���޸Ĵ˷��������е��ӷ������������Ʒ��Ϣ\n ��ȷ���Ƿ��޸ģ�"),\
		TEXT("ȷ���޸�"),MB_YESNO);
	if(IDYES==ret)
	{
		category_tree.GetItem(select, sizeof(category_name),category_name);
		HTREEITEM parent_node=category_tree.GetParent(select);//��ȡ���ڵ�
		if (parent_node)//�и��ڵ㣬��ǰѡ����Ǵη���
		{
			char main_cate_name[33];
			category_tree.GetItem(parent_node,sizeof(main_cate_name),main_cate_name);//��ȡ����������
			ChildCateForm child_cate_form;
			child_cate_form.GetChildCateByDname(main_cate_name,category_name);//������������ӷ������ƻ�ȡ�ӷ�����
			COMCHILDCATE struct_child_cate;
			struct_child_cate.main_name=main_cate_name;//��������������
			struct_child_cate.old_child_no = child_cate_form.cate_no();//����ԭ�����ӷ�����
			child_cate_form.CloseCursor();//�ر��α꣬�Ա���һ�����ִ��
			e_id.GetEditText(struct_child_cate.child_no);//��ȡ�ӷ�����
			e_name.GetEditText(struct_child_cate.child_name);//��ȡ�ӷ�������
			child_cate_form.UpdateChildCate(&struct_child_cate);//ִ�и��²���
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
			main_category.CloseCursor();//�ر��α꣬��ִ����һ�����
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
 * ˵����
 *     ɾ����Ʒ������Ϣ
 * ������
 *     hwnd  [in] �����ھ��
 * ����ֵ��
 *     �ɹ�����true,ʧ�ܷ���false
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
			MessageBox(hwnd, TEXT("��ѡ�����οؼ��е�һ��"), TEXT("��ʾ"), MB_ICONINFORMATION);
			return false;
		}
		int ret=MessageBox(hwnd,TEXT("ɾ���������ͬʱ��ɾ���˷��������е��ӷ������������Ʒ��Ϣ\n ��ȷ���Ƿ�ɾ��"),\
			TEXT("ȷ��ɾ��"),MB_YESNO);
		if(IDYES==ret)
		{
			category_tree.GetItem(select, sizeof(category_name),category_name);
			HTREEITEM parent_node=category_tree.GetParent(select);//��ȡ���ڵ�
			if (parent_node)//�и��ڵ㣬��ǰѡ����Ǵη���
			{
				char main_cate_name[33];
				char tmp[17];
				category_tree.GetItem(parent_node,sizeof(main_cate_name),main_cate_name);//��ȡ����������
				ChildCateForm child_cate_form;
				child_cate_form.GetChildCateByDname(main_cate_name,category_name);//������������ӷ������ƻ�ȡ�ӷ�����
				child_cate_form.CloseCursor();//�ر��α꣬�Ա���һ�����ִ��
				child_cate_form.DeleteChildCate(itoa(child_cate_form.cate_no(),tmp,10));//ִ��ɾ������
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
				main_category.CloseCursor();//�ر��α꣬��ִ����һ�����
				main_category.DeleteMainCate(itoa(main_category.no(),tmp,10));
			}
			e_parent_cate_name.Empty();
			e_cate_cate.Empty();
			e_id.Empty();
			e_name.Empty();
		}
	return true;
}
