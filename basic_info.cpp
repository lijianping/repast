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
			case IDC_BASIC_INFO_ADD://����ӡ�����
				{
					CommodityInfo commodity_info;
					commodity_info.menu_id = IDC_BASIC_INFO_ADD;
                    DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_EDIT_COMMODITY),hwnd,EditCommodityProc, (long)&commodity_info);
					break;
				}
			case IDC_BASIC_INFO_MODIFY://���޸ġ�����
				{
					CListView com_list;
					com_list.Initialization(hwnd,IDC_BASIC_INFO);
					int index=com_list.GetSelectionMark();
					if(-1==index)
					{
						MessageBox(hwnd,TEXT("��ѡ���б��е�һ�"),TEXT("��ʾ��"), MB_ICONINFORMATION);
					}
					else
					{
						CommodityInfo commodity_info;
						commodity_info.menu_id = IDC_BASIC_INFO_MODIFY;
						GetCommodityInfoFromList(hwnd,commodity_info);
						DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_EDIT_COMMODITY), hwnd, \
									   EditCommodityProc, (long)&commodity_info);
					}
					break;
				}
			case IDC_BASIC_INFO_DELETE://"ɾ��"����
				{
					try
					{
						if (MessageBox(hwnd,TEXT("��Ҫ����ɾ����������ȷ���Ƿ�ɾ��?"),TEXT("ɾ��ȷ��"),MB_YESNO)
							==IDYES)
						{
							CListView com_list;
							com_list.Initialization(hwnd,IDC_BASIC_INFO);
							int index=com_list.GetSelectionMark();
							if(-1==index)
							{
								MessageBox(hwnd,TEXT("��ѡ���б��е�һ�"),TEXT("��ʾ��"), MB_ICONINFORMATION);
							}
							else
							{
								std::string com_no;
								com_no = com_list.GetItem(index,0);
								CCommodity commodity;
								commodity.DeleteCom(com_no);
								MessageBox(hwnd,TEXT("ɾ������Ʒ��Ϣ�ɹ�"), TEXT("ɾ���ɹ�"), MB_ICONINFORMATION);
							}
						}		
					}	
					catch (Err &err)
					{
						MessageBox(hwnd,err.what(),TEXT("ɾ��ʧ��"),MB_ICONINFORMATION);
					}
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



BOOL CALLBACK EditCommodityProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static CommodityInfo commodity_info;
	switch(msg)
	{
	case WM_INITDIALOG:
		{
			std::string main_cate_name,child_cate_name;
			InitMainCateComBox(hwnd);//��ʼ����Ʒ����Ի���	
			EnableWindow(GetDlgItem(hwnd,IDC_E_COM_REGISTER_DATE),false);//���á��Ǽ����ڡ��༭��
			CommodityInfo *info = (CommodityInfo *)lParam;
			CCommodity com_from;
			com_from.GetCategoryByComNO(info->commodity_no.c_str());//������Ʒ��Ż�ȡ�����ķ�����Ϣ
			main_cate_name = com_from.main_name();
			child_cate_name = com_from.child_name();
			commodity_info.menu_id = info->menu_id;
			commodity_info.commodity_no = info->commodity_no;
			commodity_info.com_old_no = info->com_old_no;
			commodity_info.commodity_name = info->commodity_name;
			commodity_info.commodity_purchase = info->commodity_purchase;
			commodity_info.commodity_sum = info->commodity_sum;
			commodity_info.commodity_main_category =main_cate_name;
			commodity_info.commodity_child_category = child_cate_name;
			commodity_info.commodity_unit = info->commodity_unit;
			commodity_info.commodity_sale = info->commodity_sale;
			commodity_info.commodity_register_date = info->commodity_register_date;
			ShowCommodityInfo(hwnd,commodity_info);
			IsEnableWndChildCate(hwnd);//�Ƿ���á��ӷ��������б�
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case IDC_E_COM_ADD:
				{
					try
					{
						CommodityInfo com_info;
						GetComInfoFromDlg(hwnd,com_info);
						CCommodity commodity;
						commodity.AddCom(&com_info);
						MessageBox(hwnd,TEXT("�����Ʒ��Ϣ�ɹ�"),TEXT("��ӳɹ�"),MB_ICONINFORMATION);
					}
					catch (Err &err)
					{
						MessageBox(hwnd,err.what(),TEXT("�����Ʒ��Ϣʧ��"),MB_ICONINFORMATION);
					}
					break;
				}
			case  IDC_E_COM_MODIFY:
				{
					try
					{
						CommodityInfo com_info;
						com_info.com_old_no=commodity_info.com_old_no;//������Ʒԭ���ı��
						GetComInfoFromDlg(hwnd,com_info);
						CCommodity commodity;
						commodity.UpdateCom(&com_info);
						MessageBox(hwnd,TEXT("�޸���Ʒ��Ϣ�ɹ�"),TEXT("�޸ĳɹ�"),MB_ICONINFORMATION);
					}
					catch (Err &err)
					{
						MessageBox(hwnd,err.what(),TEXT("�޸���Ʒ��Ϣʧ��"),MB_ICONINFORMATION);
					}
					break;
				}
			case IDC_E_COM_MAIN_CATE://������
				{
					if (HIWORD(wParam)==CBN_SELCHANGE)//��������������б�
					{
						IsEnableWndChildCate(hwnd);//�Ƿ�����ӷ��������б�
						CComboBox main_cate,child_cate;
						std::string main_name,error;
						main_cate.Initialization(hwnd, IDC_E_COM_MAIN_CATE);
						child_cate.Initialization(hwnd, IDC_E_COM_CHILD_CATE);
						main_cate.GetComboBoxText(main_name);
						ChildCateForm form_child_cate;
						child_cate.DeleteAllString();//ɾ�������б��е�������
						child_cate.AddString("");//��ӿ���
						child_cate.SetCurSel(0);//ѡ������������б��edit
						child_cate.DeleteString(0);//��ɾ������
						form_child_cate.GetChildCateName(main_name.c_str(),error);//��ѯ��ǰ�������µ��ӷ���
						while(!form_child_cate.IsEOF())
						{
							child_cate.AddString(form_child_cate.cate_name());
						}
					}
					break;
				}
			case IDC_COMMODITY_CANCEL:
				{
					EndDialog(hwnd, HIWORD(wParam));
					return TRUE;
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
	return FALSE;
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
			char tmp[17];
			category_tree.GetItem(parent_node,sizeof(main_cate_name),main_cate_name);//��ȡ����������
			ChildCateForm child_cate_form;
			child_cate_form.GetChildCateByDname(main_cate_name,category_name);//������������ӷ������ƻ�ȡ�ӷ�����
			COMCHILDCATE struct_child_cate;
			struct_child_cate.main_name=main_cate_name;//��������������
			struct_child_cate.old_child_no = itoa(child_cate_form.cate_no(),tmp,10);//����ԭ�����ӷ�����
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
	else{
		return false;
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
		else{
			return false;
		}
	return true;
}


/*
 * ˵����
 *     ��ListView�л�ȡ��Ʒ����ϸ��Ϣ
 * ������
 *     commodigy_info  [out] ��Ʒ��Ϣ������
 * ����ֵ��
 *     �ɹ�����true, ���򷵻�false
 */
bool GetCommodityInfoFromList(HWND hwnd,CommodityInfo &commodity_info)
{
	CListView commodity_list(hwnd, IDC_BASIC_INFO);
	int select = commodity_list.GetSelectionMark();
	commodity_info.menu_id = IDC_BASIC_INFO_MODIFY;
	commodity_info.commodity_no = commodity_list.GetItem(select, 0);
	commodity_info.com_old_no=commodity_info.commodity_no;
	commodity_info.commodity_name = commodity_list.GetItem(select, 1);
	commodity_info.commodity_purchase = commodity_list.GetItem(select, 2);
	commodity_info.commodity_sum = commodity_list.GetItem(select, 3);
	commodity_info.commodity_unit = commodity_list.GetItem(select, 4);
	commodity_info.commodity_sale = commodity_list.GetItem(select, 5);
	commodity_info.commodity_register_date = commodity_list.GetItem(select, 6);
	return true;
}


/*
 * ˵����
 *     ��ʼ�������������б�
 * ������
 *     hwnd  [in]���ھ��
 * ����ֵ��
 *     �ɹ�����true,ʧ�ܷ���false
 */
bool InitMainCateComBox(HWND hwnd)
{
	CComboBox main_cate,child_cate;
	main_cate.Initialization(hwnd,IDC_E_COM_MAIN_CATE);
	ComMainCateForm form_main_cate;
	form_main_cate.GetMainCateName();//��ѯ���е���Ʒ��������Ϣ
	while (!form_main_cate.IsEOF())
	{
		main_cate.AddString(form_main_cate.name());
	}
	return true;
}

/*
 * ˵����
 *     ���������������б��ѡ���ж��Ƿ�����ӷ��������б�
 *     ��������Ϊ�գ�����ã���������
 * ������
 *     hwnd  [in]���ھ��
 * ����ֵ��
 *     �ɹ�����true,ʧ�ܷ���false
 */
bool IsEnableWndChildCate(HWND hwnd)
{
	CComboBox main_cate,child_cate;
	std::string main_name;
	main_cate.Initialization(hwnd,IDC_E_COM_MAIN_CATE);
	child_cate.Initialization(hwnd,IDC_E_COM_CHILD_CATE);
	main_cate.GetComboBoxText(main_name);
	if (main_name=="")
	{
		if(!child_cate.EnableWindow(false))//�����ӷ���������
		{
			return false;
		}
	}
	else
	{
		if(!child_cate.EnableWindow(true))//�����ӷ���������
		{
			return false;
		}
	}
	return true;
}

/*
 * ˵����
 *     ��ʾ��Ʒ��Ϣ
 * ������
 *     hwnd  [in]���ھ��
 *     commodity_info [out] ��Ʒ��Ϣ������
 * ����ֵ��
 *     �ɹ�����true,ʧ�ܷ���false
 */
bool ShowCommodityInfo(HWND hwnd,CommodityInfo &commodity_info)
{
	HWND com_add,com_modity;
	com_add=GetDlgItem(hwnd,IDC_E_COM_ADD);
	com_modity=GetDlgItem(hwnd,IDC_E_COM_MODIFY);
	if (commodity_info.menu_id == IDC_BASIC_INFO_MODIFY)
	{
		ShowWindow(com_add,SW_HIDE);//���ء���ӡ���ť
		ShowWindow(com_modity,SW_NORMAL);
		SetDlgItemText(hwnd, IDC_E_COMMODITY_ID, commodity_info.commodity_no.c_str());
		SetDlgItemText(hwnd, IDC_E_COMMODITY_NAME, commodity_info.commodity_name.c_str());
		SetDlgItemText(hwnd, IDC_E_COMMODITY_PURCHASE, commodity_info.commodity_purchase.c_str());
		SetDlgItemText(hwnd, IDC_E_COMMODITY_SUM, commodity_info.commodity_sum.c_str());
		CComboBox main_cate,child_cate;
		main_cate.Initialization(hwnd, IDC_E_COM_MAIN_CATE);
		child_cate.Initialization(hwnd, IDC_E_COM_CHILD_CATE);
		int index;
	    index = main_cate.FindString(commodity_info.commodity_main_category.c_str());//�������б��в��ҵ���Ӧ���ַ���
		ChildCateForm form_child_cate;
		std::string error;
		form_child_cate.GetChildCateName(commodity_info.commodity_main_category.c_str(),error);//��ѯ��ǰ�������µ��ӷ���
		while(!form_child_cate.IsEOF())
		{
			child_cate.AddString(form_child_cate.cate_name());
		}
		main_cate.SetCurSel(index);//ѡ����Ӧ��������
		index = child_cate.FindString(commodity_info.commodity_child_category.c_str());
		child_cate.SetCurSel(index);//ѡ����Ӧ���ӷ���
		SetDlgItemText(hwnd, IDC_E_COMMODITY_UNIT, commodity_info.commodity_unit.c_str());
		SetDlgItemText(hwnd, IDC_E_COMMODITY_SALE, commodity_info.commodity_sale.c_str());
		SetDlgItemText(hwnd, IDC_E_COM_REGISTER_DATE,commodity_info.commodity_register_date.c_str());
	}
	else if (commodity_info.menu_id == IDC_BASIC_INFO_ADD)
	{
		ShowWindow(com_add,SW_NORMAL);
		ShowWindow(com_modity,SW_HIDE);//���ء��޸ġ���ť
		CDBForm server_time;
		SetDlgItemText(hwnd, IDC_E_COM_REGISTER_DATE,server_time.GetServerDateTime());//ͨ����ȡ������ʱ������ʾĬ�ϵ�ʱ��
	}
	return true;
}

/*
 * ˵����
 *    �ӶԻ����л�ȡ��Ʒ����ϸ��Ϣ
 * ������
 *    hwnd     [in] �༭��Ʒ��Ϣ�Ի�����
 *    com_info [out] ��Ʒ��Ϣ������
 * ����ֵ��
 *    �ɹ�����true,���򷵻�false
 */
bool GetComInfoFromDlg(HWND hwnd, CommodityInfo &com_info)
{
	CEdit no,name,purchase_price,quantity,unit,sale_price,register_date;
	CComboBox main_name,child_name;
	if(!no.Initialization(hwnd,IDC_E_COMMODITY_ID)||
	!name.Initialization(hwnd,IDC_E_COMMODITY_NAME)||
	!purchase_price.Initialization(hwnd,IDC_E_COMMODITY_PURCHASE)||
	!quantity.Initialization(hwnd,IDC_E_COMMODITY_SUM)||
	!unit.Initialization(hwnd,IDC_E_COMMODITY_UNIT)||
	!sale_price.Initialization(hwnd,IDC_E_COMMODITY_SALE)||
	!main_name.Initialization(hwnd,IDC_E_COM_MAIN_CATE)||
	!child_name.Initialization(hwnd,IDC_E_COM_CHILD_CATE)||
	!register_date.Initialization(hwnd,IDC_E_COM_REGISTER_DATE))
	{
		return false;
	}
	if(no.GetEditText(com_info.commodity_no)&&
	name.GetEditText(com_info.commodity_name)&&
	purchase_price.GetEditText(com_info.commodity_purchase)&&
	quantity.GetEditText(com_info.commodity_sum)&&
	unit.GetEditText(com_info.commodity_unit)&&
	sale_price.GetEditText(com_info.commodity_sale)&&
	main_name.GetComboBoxText(com_info.commodity_main_category)&&
	child_name.GetComboBoxText(com_info.commodity_child_category)&&
	register_date.GetEditText(com_info.commodity_register_date))
	{
		return true;
	}
	return false;
}