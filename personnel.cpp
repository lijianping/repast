#include <string>
#include "resource.h"
#include "MyListView.h"
#include "StaffForm.h"
#include "childwindowid.h"
#include "personnel.h"




/* only used in this file */
WNDPROC old_list_processes;



LRESULT CALLBACK PersonnelProcesses(HWND hwnd, UINT message,
                                  WPARAM wParam, LPARAM lParam)
{
    static HINSTANCE hinstance;
    switch (message)
    {
    case WM_CREATE:
        {
            hinstance = ((LPCREATESTRUCT)lParam)->hInstance;
            std::string error_info;
            if (!CreateStaffListView(hinstance, hwnd, error_info))
            {
                MessageBox(hwnd, error_info.c_str(),
                           TEXT("PERSONNEL"), MB_OK | MB_ICONERROR);
                return 0;
            }
            if (!InitWindow(hinstance, hwnd, error_info) ||
                !ShowInfo(hinstance, hwnd, error_info))
            {
                MessageBox(hwnd, error_info.c_str(),
                    TEXT("PERSONNEL"), MB_OK | MB_ICONERROR);
                return 0;
            }
            EnableWindow(GetDlgItem(hwnd, ID_MAN), FALSE);
            EnableWindow(GetDlgItem(hwnd, ID_WOMAN), FALSE);
            InitComboBox(hwnd, ID_PERSONNEL_DEPT_COMBO);
            /* Select the first item */
            SendMessage(GetDlgItem(hwnd, ID_PERSONNEL_DEPT_COMBO), CB_SETCURSEL, 0, 0);
            return 0;
        }
    case WM_SETFOCUS:
        {
            SetFocus(GetDlgItem(hwnd, ID_PERSONNEL_INFO));
            return 0;
        }
    case WM_LBUTTONDOWN:
        {
            /* Get the content which is in the combo box's edit box */
            
            return 0;
        }
    case WM_COMMAND:
        {
			bool is_check = false;
            switch(LOWORD(wParam))  
            {
			case ID_PERSONNEL_NAME:
				{
					is_check = IsCheckName(hwnd);
					if (true == is_check)
					{
						EnableWindow (GetDlgItem(hwnd, ID_PERSONNEL_STAFF_NAME), TRUE);
					}
					else
					{
						EnableWindow (GetDlgItem(hwnd, ID_PERSONNEL_STAFF_NAME), FALSE);
					}
					break;
				}
			case ID_PERSONNEL_SEX:
				{
					is_check = IsCheckSex(hwnd);
					if (true == is_check)
					{
						EnableWindow (GetDlgItem(hwnd, ID_MAN), TRUE);
						EnableWindow (GetDlgItem(hwnd, ID_WOMAN), TRUE);
					}
					else
					{
						EnableWindow (GetDlgItem(hwnd, ID_MAN), FALSE);
						EnableWindow (GetDlgItem(hwnd, ID_WOMAN), FALSE);
					}
					break;
				}
			case ID_PERSONNEL_DEPT:
				{
					is_check = IsCheckDept(hwnd);
					if (true == is_check)
					{
						EnableWindow (GetDlgItem(hwnd, ID_PERSONNEL_DEPT_COMBO), TRUE);
					}
					else
					{
						EnableWindow (GetDlgItem(hwnd, ID_PERSONNEL_DEPT_COMBO), FALSE);
					}
					break;
				}
             case ID_PERSONNEL_QUERY:
				 {
				     std::string error_info;
					 if (false == OnStartQuery(hwnd, error_info))
					 {
						 MessageBox(hwnd, error_info.c_str(), TEXT("����"), MB_OK | MB_ICONINFORMATION);
					 }
                     break;
				 }
            }
            return 0;
        }
	case WM_NOTIFY:
		{
			switch (LOWORD(wParam))
			{
			case ID_PERSONNEL_INFO:
				{
					if (((LPNMHDR)lParam)->code == NM_RCLICK)
					{
						CMyListView list;
						list.set_hwnd(GetDlgItem(hwnd, ID_PERSONNEL_INFO));
						int index = list.GetCurSel();
						list.SetSelectd(index);
					}
					break;
				}
		
			}
			return 0;
		}
 
    case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

/*
 * ˵��: list view��������
 *       �ú������ܴ������е���Ϣ(��WM_CREATE��Ϣ)��ֻ�ܴ���
 *       ���ֵ���Ϣ��
 **/
LRESULT CALLBACK PersonnelList(HWND hwnd, UINT message,
                               WPARAM wParam, LPARAM lParam)
{
    HMENU menu;
    HINSTANCE hinstance = (HINSTANCE)GetWindowLong(GetParent(hwnd), GWL_HINSTANCE);
    int selected_row; /* current selected row */
    switch (message)
    {
    case WM_LBUTTONDOWN:
        {
            break;
        }
    case WM_RBUTTONDOWN:
        {
            menu = LoadMenu(hinstance, MAKEINTRESOURCE(IDR_PERSONNEL));
            menu = GetSubMenu(menu, 0);
            CMyListView list;
            list.set_hwnd(hwnd);
            POINT point;
            point.x = LOWORD(lParam);
            point.y = HIWORD(lParam);
            ClientToScreen(hwnd, &point);
            TrackPopupMenu(menu, TPM_RIGHTBUTTON, point.x, point.y,
                           0, hwnd, NULL);
            break;
        }
    case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
            case IDR_ADD:
                /* TODO: send the list view content to dialog */
                {
                    MessageBox(hwnd, TEXT("You choiced delete staff"), TEXT("PERSONNEL"), MB_OK | MB_ICONINFORMATION);
                    break;
                }
                
            case IDR_DELETE:
				{
					CMyListView list;
                    STAFFINFO staff_info;
                    list.set_hwnd(hwnd);
					selected_row = list.GetCurSel();
                    list.GetItem(selected_row, 0, staff_info.id);      /* Get staff's id */
                    list.GetItem(selected_row, 1, staff_info.name);    /* Get staff's name */
                    list.GetItem(selected_row, 2, staff_info.sex);     /* Get staff's sex */
                    list.GetItem(selected_row, 3, staff_info.age);     /* Get staff's age */
                    list.GetItem(1, 4, staff_info.salary);             /* Get staff's salary */
					DialogBoxParam(hinstance, MAKEINTRESOURCE(IDD_STAFF_EDIT), hwnd,
                              (DLGPROC)EditStaff, (long)&staff_info);
					break;
				}
			case IDR_MODIFY:
                {
					CMyListView list;
                    STAFFINFO staff_info;
                    list.set_hwnd(hwnd);
					selected_row = list.GetCurSel();
                    list.GetItem(selected_row, 0, staff_info.id);      /* Get staff's id */
                    list.GetItem(selected_row, 1, staff_info.name);    /* Get staff's name */
                    list.GetItem(selected_row, 2, staff_info.sex);     /* Get staff's sex */
                    list.GetItem(selected_row, 3, staff_info.age);     /* Get staff's age */
                    list.GetItem(1, 4, staff_info.salary);             /* Get staff's salary */
					DialogBoxParam(hinstance, MAKEINTRESOURCE(IDD_STAFF_EDIT), hwnd,
                              (DLGPROC)EditStaff, (long)&staff_info);
					break;
				}
            }
            return 0;
        }
    }
    return CallWindowProc(old_list_processes, hwnd, message, wParam, lParam);
}


BOOL CALLBACK EditStaff(HWND hwnd, UINT message,
                             WPARAM wParam, LPARAM lParam)
{
    
    switch (message)
    {
      case WM_INITDIALOG:
        {
            RECT login_rect;
            if (!GetWindowRect(hwnd, &login_rect))
            {
                MessageBox(hwnd, TEXT("Get dialog rect failed!"),
                    TEXT("ERROR"), MB_ICONINFORMATION | MB_OK);
                return FALSE;
            }
            int login_width = login_rect.right - login_rect.left;
            int login_height = login_rect.bottom - login_rect.top;
            int screen_width = GetSystemMetrics(SM_CXFULLSCREEN);
            int screen_height = GetSystemMetrics(SM_CYFULLSCREEN);
            MoveWindow(hwnd, (screen_width - login_width) / 2,
                      (screen_height - login_height) / 2, login_width,
                      login_height, TRUE);
            STAFFINFO *info = (STAFFINFO *)lParam;
            SetDlgItemText(hwnd, IDC_STAFF_ID, info->id.c_str());
            SetDlgItemText(hwnd, IDC_STAFF_NAME, info->name.c_str());
            SetDlgItemText(hwnd, IDC_STAFF_AGE, info->age.c_str());
            SetDlgItemText(hwnd, IDC_STAFF_SALARY, info->salary.c_str());
//            SetDlgItemText(hwnd, IDC_STAFF_AGE, info->age);
            /* HIT: This is used to modify windows icon. */
//             HICON login_icon = LoadIcon(g_hinstance, MAKEINTRESOURCE(IDI_ICONLOGIN));
//             if (login_icon)
//             {
//                 SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)login_icon);
//                 SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)login_icon);
//             }
            return TRUE;
        }
    case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                /*TODO: add staff add function, delete function,
                 *      modify function and update database.
                 **/
			case ID_ADD_STAFF:
				{
				/*just for test*/	
				std::string error_info;
				StaffForm sf;
				sf.Connect("repast", "repast", "repast", error_info);
				if(false == sf.InsertInfo("20100004", "frank", "",34, 3432, "05", error_info))
				{
					MessageBox(hwnd, error_info.c_str(), TEXT("����"), MB_OK);
				}
					sf.Disconnect();		
					MessageBox(hwnd, "you selected add option", "add",MB_OK);
					break;
				}
			case ID_DELETE_STAFF:
				{	
						/*just for test*/
					MessageBox(hwnd, "you selected delete option", "delete", MB_OK);
					std::string error_info;
					StaffForm sf;
					sf.Connect("repast", "repast", "repast", error_info);
					if(false == sf.DeleteInfo("20101001", error_info))
					{
						MessageBox(hwnd, error_info.c_str(), TEXT("����"), MB_OK);
					}
					sf.Disconnect();		
					break;
				}
            case ID_CANCEL_STAFF:
                EndDialog(hwnd,  LOWORD(wParam));
                break;
            }
            return TRUE;
        }
    case WM_CLOSE:
        EndDialog(hwnd, LOWORD(wParam));
        return TRUE;
    }
    return FALSE;
}


bool CreateStaffListView(HINSTANCE hinstance, HWND hwnd, std::string &information)
{
    CMyListView list_view;
    RECT service_rect;
    GetWindowRect(hwnd, &service_rect);
    int width = service_rect.right - service_rect.left;
    int height = service_rect.bottom - service_rect.top;
    list_view.set_list_view_id(ID_PERSONNEL_INFO);
    list_view.set_list_view_height(height / 4 * 3 - 40);
    list_view.set_list_view_width(width - 40 );
    list_view.set_hinstance(hinstance);
    list_view.set_parent_hwnd(hwnd);
    POINT origin;
    origin.x = 20;
    origin.y = height / 4;
    list_view.set_origin_point(origin);
    list_view.set_process(PersonnelList);
    if (!list_view.CreateListView())
    {
        information = "����list viewʧ��!";
        return false;
    }
    old_list_processes = list_view.old_process();
    list_view.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    if (!list_view.InsertColumn("Ա�����", 0, width / 6) ||
        !list_view.InsertColumn("Ա������", 1, width / 6) ||
        !list_view.InsertColumn("Ա���Ա�", 2, width / 6) ||
        !list_view.InsertColumn("Ա������", 3, width / 6) ||
        !list_view.InsertColumn("Ա������", 4, width / 6) ||
        !list_view.InsertColumn("Ա������", 5, width / 6) ||
		!list_view.InsertColumn("Ա������", 6, width / 6) ||
		!list_view.InsertColumn("Ա���绰", 7, width / 6) ||
		!list_view.InsertColumn("Ա��סַ", 8, width / 6))
    {
        information = "�����ͷʧ��!";
        return false;
    }
    list_view.SetSelectd(0);
    /* Get staff's information from Staff form in database. */
    StaffForm staff;
    std::string error_information;
	staff.Connect("repast", "repast", "repast", error_information);
    staff.GetRecordSet();
    staff.MoveFirst();
    int i = 0;
    while (!staff.IsEOF())
    {
        list_view.InsertItem(staff.id(), i);
        list_view.SetItem(staff.name(), i, 1);
        list_view.SetItem(staff.sex(), i, 2);
        list_view.SetItem(staff.age(), i, 3);
        list_view.SetItem(staff.salary(), i, 4);
        list_view.SetItem(staff.dept_num(), i, 5);
		list_view.SetItem(staff.mailbox(), i, 6);
		list_view.SetItem(staff.phone_num(), i, 7);
		list_view.SetItem(staff.address(), i, 8);
        staff.MoveNext();
        i++;
    }
	staff.Disconnect();
    list_view.SetSelectd(0);
    return true;
 }

/*
 * ˵��: ��ȡ�ַ������߶�
 * ����:
 *       hwnd [in] ���ھ��
 *       width [out] �ַ����
 *       height [out] �ַ��߶�
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 */
bool GetTextInfo(HWND hwnd, int &width, int &height)
{
	HDC hdc;
	TEXTMETRIC text_metric;
	BOOL is_ok;
	hdc = GetDC(hwnd);
	is_ok = GetTextMetrics(hdc, &text_metric);
	ReleaseDC(hwnd, hdc);
	if (FALSE == is_ok)
	{
		return false;
	}
	width = (text_metric.tmPitchAndFamily & 1 ? 3 : 2) *
           	text_metric.tmAveCharWidth / 2;
	height = text_metric.tmHeight + text_metric.tmExternalLeading;
	return true;
}

/*
 * ˵��: ��������ѯ��������Ͽ�
 * ����:
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 */
bool CreateGroupBox(HINSTANCE hinstance, HWND hwnd, std::string &error_info)
{
	HWND group_hwnd;
	bool is_ok = true;
	group_hwnd = CreateWindow(TEXT("button"), TEXT("��ѯ����"), 
                              WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                              20, 10, 400, 125, hwnd, NULL,
                              hinstance, NULL);
	if (NULL == group_hwnd)
	{
		error_info = "��������ѯ��������Ͽ�ʧ�ܣ�";
		is_ok = false;
	}
	return is_ok;
}

/*
 * ˵��: ��������š���ѯ����ѡ��
 * ����:
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 */
bool CreateNumEdit(HINSTANCE hinstance, HWND hwnd, std::string &error_info)
{
	int width(0), height(0);
	if (!GetTextInfo(hwnd, width, height))
	{
		error_info = "��ȡ�ַ���Ϣʧ�ܣ�";
		return false;
	}
	HWND number_hwnd(NULL);
	number_hwnd = CreateWindow(TEXT("static"), TEXT("���"), WS_CHILD | WS_BORDER |
                               ES_CENTER | WS_VISIBLE, 30, 50, 4 * width, height + 5, hwnd,
                               NULL, hinstance, NULL);
	if (NULL == number_hwnd)
	{
		error_info = "��������š���ʾʧ�ܣ�";
		return false;
	}
	number_hwnd = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE |
                               WS_BORDER | WS_TABSTOP | ES_LEFT, 100, 50,
							   10 * width, height + 5, hwnd, 
							   (HMENU)ID_PERSONNEL_STAFF_ID, hinstance, NULL);
	if (NULL == number_hwnd)
	{
		error_info = "��������š��༭��ʧ�ܣ�";
		return false;
	}
	return true;
}

/*
 * ˵��: ��������������ѯ����ѡ��
 * ����:
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 */
bool CreateNameEdit(HINSTANCE hinstance, HWND hwnd, std::string &error_info)
{
	int width(0), height(0);
	if (!GetTextInfo(hwnd, width, height))
	{
		error_info = "��ȡ�ַ���Ϣʧ�ܣ�";
		return false;
	}
	HWND name_hwnd(NULL);
	name_hwnd = CreateWindow(TEXT("button"), TEXT("����"),WS_CHILD | /*WS_BORDER |*/
                             ES_CENTER | WS_TABSTOP | WS_VISIBLE | BS_AUTOCHECKBOX, 225, 50,
							 6 * width, height + 5, hwnd, (HMENU)ID_PERSONNEL_NAME, hinstance, NULL);
	if (NULL == name_hwnd)
	{
		error_info = "��������������ѡ��ʧ�ܣ�";
		return false;
	}
	name_hwnd = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
                          	 WS_TABSTOP | ES_LEFT, 295, 50, 10 * width, height + 5,
							 hwnd, (HMENU)ID_PERSONNEL_STAFF_NAME, hinstance, NULL);
	if (NULL == name_hwnd)
	{
		error_info = "�������������༭��ʧ�ܣ�";
		return false;
	}
	return true;
}

/*
 * ˵��: �������Ա𡯲�ѯ����ѡ��
 * ����:
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 */
bool CreateSexBox(HINSTANCE hinstance, HWND hwnd, std::string &error_info)
{
	int width(0), height(0);
	if (!GetTextInfo(hwnd, width, height))
	{
		error_info = "��ȡ�ַ���Ϣʧ�ܣ�";
		return false;
	}
	HWND sex_hwnd(NULL);
	sex_hwnd = CreateWindow(TEXT("button"), TEXT("�Ա�"),WS_CHILD | /*WS_BORDER |*/
                            ES_CENTER | WS_VISIBLE | BS_AUTOCHECKBOX, 30, 90, 6 * width,
                            height + 5, hwnd, (HMENU)ID_PERSONNEL_SEX, hinstance, NULL);
    if (NULL == sex_hwnd)
	{
		error_info = "�������Ա𡱸�ѡ��ʧ�ܣ�";
		return false;
	}
	sex_hwnd = CreateWindow(TEXT("button"), TEXT("��"), WS_CHILD | WS_VISIBLE | ES_CENTER |
							WS_TABSTOP | /*WS_BORDER |*/ BS_AUTORADIOBUTTON, 100,
							90, 4 * width, height + 5, hwnd,(HMENU)ID_MAN,
							hinstance, NULL);
	if (NULL == sex_hwnd)
	{
		error_info = "�������С�ѡ��ťʧ�ܣ�";
		return false;
	}
	sex_hwnd = CreateWindow(TEXT("button"), TEXT("Ů"), WS_CHILD | WS_VISIBLE | WS_TABSTOP |
                              ES_CENTER | /*WS_BORDER |*/ BS_AUTORADIOBUTTON, 100 + 4 * width + 10,
							  90, 4 * width, height + 5, hwnd, (HMENU)ID_WOMAN,
							  hinstance, NULL);
    if (NULL == sex_hwnd)
    {
        error_info = "������Ů��ѡ��ťʧ�ܣ�";
        return false;
    }
	return true;
}

/*
 * ˵��: ���������š���ѯ����ѡ��
 * ����:
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 */
bool CreateDeptCombo(HINSTANCE hinstance, HWND hwnd, std::string &error_info)
{
	int width(0), height(0);
	if (!GetTextInfo(hwnd, width, height))
	{
		error_info = "��ȡ�ַ���Ϣʧ�ܣ�";
		return false;
	}
	HWND dept_hwnd(NULL);
	dept_hwnd = CreateWindow(TEXT("button"), TEXT("����"),WS_CHILD | /*WS_BORDER |*/
                             ES_CENTER | WS_TABSTOP | WS_VISIBLE | BS_AUTOCHECKBOX, 225, 90,
							 6 * width, height + 5, hwnd, (HMENU)ID_PERSONNEL_DEPT,
							 hinstance, NULL);
    if (NULL == dept_hwnd)
    {
		error_info = "���������š���ѡ��ʧ�ܣ�";
		return false;
	}	
	dept_hwnd = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE |/* WS_BORDER |*/ 
                             ES_CENTER | WS_TABSTOP | CBS_DROPDOWN | CBS_HASSTRINGS |
                             CBS_AUTOHSCROLL | CBS_DISABLENOSCROLL, 295, 90, 10 * width,
                             100, hwnd, (HMENU)ID_PERSONNEL_DEPT_COMBO,
                             hinstance, NULL);
    if (NULL == dept_hwnd)
    {
        error_info = "���������š�������ʧ�ܣ�";
        return false;	
    }
	return true;
}

/*
 * ˵��: ������Ա����������ѯ��ʾ
 * ����:
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 */
bool CreateStaffSum(HINSTANCE hinstance, HWND hwnd, std::string &error_info)
{
	int width(0), height(0);
	if (!GetTextInfo(hwnd, width, height))
	{
		error_info = "��ȡ�ַ���Ϣʧ�ܣ�";
		return false;
	}
	HWND sum_hwnd(NULL);
	sum_hwnd = CreateWindow(TEXT("static"), TEXT("Ա������"),WS_CHILD  | WS_VISIBLE | 
							ES_CENTER | WS_BORDER, 600, 10, 7 * width, height + 5, hwnd,
							NULL, hinstance, NULL);
	if (NULL == sum_hwnd)
	{
		error_info = "������Ա����������ʾʧ�ܣ�";
		return false;
	}
	sum_hwnd = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
							WS_TABSTOP | ES_READONLY | ES_LEFT, 680, 10, 10 * width,
							height + 5, hwnd, (HMENU)ID_PERSONNEL_STAFF_SUM,
							hinstance, NULL);
	if (NULL == sum_hwnd)
	{
		error_info = "������Ա���������༭��ʧ�ܣ�";
		return false;
	}
	return true;
}

/*
 * ˵��: ������������������ѯ��ʾ
 * ����:
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 */
bool CreateDeptSum(HINSTANCE hinstance, HWND hwnd, std::string &error_info)
{
	int width(0), height(0);
	if (!GetTextInfo(hwnd, width, height))
	{
		error_info = "��ȡ�ַ���Ϣʧ�ܣ�";
		return false;
	}
	HWND sum_hwnd(NULL);
	sum_hwnd = CreateWindow(TEXT("static"), TEXT("��������"), WS_CHILD | WS_VISIBLE |
							ES_CENTER | WS_BORDER, 600, 50, 7 * width, height + 5, hwnd,
							NULL, hinstance, NULL);
	if (NULL == sum_hwnd)
	{
		error_info = "������������������ʾʧ�ܣ�";
		return false;
	}
	sum_hwnd = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
							WS_TABSTOP | ES_READONLY | ES_LEFT, 680, 50, 10 * width,
							height + 5, hwnd, (HMENU)ID_PERSONNEL_DEPT_SUM,
							hinstance, NULL);
	if (NULL == sum_hwnd)
	{
		error_info = "�����������������༭��ʧ�ܣ�";
		return false;
	}
	return true;
}

/*
 * ˵��: ��������ǰ��������ѯ��ʾ
 * ����:
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 */
bool CreateCurrentSum(HINSTANCE hinstance, HWND hwnd, std::string &error_info)
{
	int width(0), height(0);
	if (!GetTextInfo(hwnd, width, height))
	{
		error_info = "��ȡ�ַ���Ϣʧ�ܣ�";
		return false;
	}
	HWND sum_hwnd(NULL);
	sum_hwnd = CreateWindow(TEXT("static"), TEXT("��ǰ����"), WS_CHILD  | WS_VISIBLE |
							ES_CENTER | WS_BORDER, 600, 90, 7 * width, height + 5, hwnd, NULL,
							hinstance, NULL);
	if (NULL == sum_hwnd)
	{
		error_info = "��������ǰ��������ʾʧ�ܣ�";
		return false;
	}
	sum_hwnd = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
							WS_TABSTOP | ES_READONLY | ES_LEFT, 680, 90, 10 * width,
							height + 5, hwnd, (HMENU)ID_CURRENT_RECORD_SUM,
							hinstance, NULL);
	if (NULL == sum_hwnd)
	{
		error_info = "��������ǰ�������༭��ʧ�ܣ�";
		return false;
	}
	return true;
}

bool CreatePersonnelQuery(HINSTANCE hinstance, HWND hwnd, std::string &error_info)
{
    int width(0), height(0);
    if (!GetTextInfo(hwnd, width, height))
    {
        error_info = "��ȡ�ַ���Ϣʧ�ܣ�";
        return false;
    }
    HWND query_hwnd(NULL);
    query_hwnd = CreateWindow(TEXT("button"), TEXT("��ʼ��ѯ"), WS_CHILD | WS_VISIBLE | WS_TABSTOP |
                              ES_CENTER | BS_PUSHBUTTON, 450, 50, 8 * width,
                              height + 10, hwnd, (HMENU)ID_PERSONNEL_QUERY,
                              hinstance, NULL);
    if (NULL == query_hwnd)
    {
        error_info = "��������ʼ��ѯ����ťʧ�ܣ�";
        return false;
    }
    return true;
}

/*
 * ˵��: ��ʼ������
 * ����:
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 **/
bool InitWindow(HINSTANCE hinstance, HWND hwnd, std::string &error_info)
{
    if (CreateGroupBox(hinstance, hwnd, error_info) &&
		CreateNumEdit(hinstance, hwnd, error_info) &&
		CreateNameEdit(hinstance, hwnd, error_info) &&
		CreateSexBox(hinstance, hwnd, error_info) &&
		CreateDeptCombo(hinstance, hwnd, error_info) &&
		CreateStaffSum(hinstance, hwnd, error_info) &&
		CreateDeptSum(hinstance, hwnd, error_info) &&
		CreateCurrentSum(hinstance, hwnd, error_info) &&
		CreatePersonnelQuery(hinstance, hwnd, error_info))
    {
		InitChildWind(hwnd);
        return true;
    }
    return false;
}



bool ShowInfo(HINSTANCE hinstance, HWND hwnd, std::string &error_info)
{
    CMyListView list;
    list.set_hwnd(GetDlgItem(hwnd, ID_PERSONNEL_INFO));
    int number = list.GetItemCount();
    TCHAR sum[10];
    sprintf(sum, "%d ��", number); 
    if (!SetDlgItemText(hwnd, ID_CURRENT_RECORD_SUM, sum))
    {
        error_info = "���á���ǰ�������ı�ʧ�ܣ�";
        return false;
    }
    return true;
}


bool InitComboBox(HWND hwnd, int id)
{
    if (CB_ERR == SendMessage(GetDlgItem(hwnd, id), CB_ADDSTRING, 0, (LPARAM)"���²�") ||
        CB_ERR == SendMessage(GetDlgItem(hwnd, id), CB_ADDSTRING, 0, (LPARAM)"����") ||
        CB_ERR == SendMessage(GetDlgItem(hwnd, id), CB_ADDSTRING, 0, (LPARAM)"���ڲ�"))
    {
        return false;
    }
    return true;
}
bool OnStartQuery(HWND hwnd, std::string &error_info)
{
	char sql_query[500];
	char Sno[20] = "\0";
	std::string id, name, sex, dept;
	id = GetID(hwnd);/* ��ȡ�༭��������id */
    sprintf(sql_query, TEXT("select * from Staff where Sno like '%c%s%c'"), '%',id.c_str(), '%');
	std::string sql_str(sql_query);
	if (IsCheckName(hwnd))
	{
		name = GetName(hwnd);/* ��ȡ�༭������������� */
		sprintf(sql_query, " and Sname like '%c%s%c'", '%', name.c_str(), '%');
		std::string tmp(sql_query);
	      sql_str += tmp;/*��׷���ڲ�ѯ����� */
	}
	if (IsCheckSex(hwnd))
	{
		sex = GetSex(hwnd);  
		sprintf(sql_query, " and Ssex='%s'", sex.c_str());
		std::string tmp(sql_query);
	      sql_str += tmp;/*��׷���ڲ�ѯ����� */
		
	}
	if (IsCheckDept(hwnd))
	{
		dept = GetDept(hwnd); 
		sprintf(sql_query, " and Sdept='%s'", dept.c_str());
		std::string tmp(sql_query);
	    sql_str += tmp;/*��׷���ڲ�ѯ����� */
	}
	MessageBox(hwnd, sql_str.c_str(), "result", MB_OK);
	return ExecQuery(sql_str.c_str(), error_info);
}

bool ExecQuery(const char * sql_query, std::string &error_info)
{
	StaffForm staff;
	staff.Connect("repast", "repast", "repast", error_info);
	if (false == staff.ExecuteSQL(sql_query, error_info))
	{
		return false;
	}
	staff.BindingParameter();
	staff.MoveFirst();
	if (0 ==strcmp("",staff.id()))
	{
		error_info = TEXT("��ƥ����");
		return false;
	}
	else
	{
		while (!staff.IsEOF())
		{
			char result[100];
			sprintf(result, TEXT("%s %s %s"), staff.id(), staff.name(), staff.sex());
			MessageBox(NULL, result, TEXT("��ѯ���"), MB_OK);
			staff.MoveNext();
		}
	}
		staff.Disconnect();
	return true;
}

std::string GetID(HWND hwnd)
{
	char id[10];
	GetWindowText(GetDlgItem(hwnd, ID_PERSONNEL_STAFF_ID), id, 8+1);
	return std::string(id);
}
std::string GetName(HWND hwnd)
{
	char name[20] = "\0";
	GetWindowText(GetDlgItem(hwnd, ID_PERSONNEL_STAFF_NAME), name, 9+1);
	return std::string(name);
}
std::string GetSex(HWND hwnd)
{
	char sex[2] = "\0";
    if (BST_CHECKED == SendMessage(GetDlgItem(hwnd, ID_MAN), BM_GETCHECK, 0, 0))
    {
        strcpy(sex, "��");
    }
    if (BST_CHECKED == SendMessage(GetDlgItem(hwnd, ID_WOMAN), BM_GETCHECK, 0, 0))
    {
        strcpy(sex, "Ů");
    }
	return std::string(sex);
}
std::string GetDept(HWND hwnd)
{
	char dept[40] = "\0";
    int index = SendMessage(GetDlgItem(hwnd, ID_PERSONNEL_DEPT_COMBO), CB_GETCURSEL,0, 0);
    SendMessage(GetDlgItem(hwnd, ID_PERSONNEL_DEPT_COMBO), CB_GETLBTEXT, index, (LPARAM)&dept);
	return std::string(dept);
}

bool IsCheckName(HWND hwnd)
{
    long ret = SendMessage(GetDlgItem(hwnd, ID_PERSONNEL_NAME), BM_GETCHECK, 0, 0);
	if (BST_CHECKED == ret)
	{
        return true;
	}
    return false;
}
	
bool IsCheckSex(HWND hwnd)
{
    long ret = SendMessage(GetDlgItem(hwnd, ID_PERSONNEL_SEX), BM_GETCHECK, 0, 0);
    if (BST_CHECKED == ret)
    {
        return true;
    }
    return false;
}
bool IsCheckDept(HWND hwnd)
{
    long ret = SendMessage(GetDlgItem(hwnd, ID_PERSONNEL_DEPT), BM_GETCHECK, 0, 0);
    if (BST_CHECKED == ret)
    {
        return true;
    }
    return false;
}

bool InitChildWind(HWND hwnd)
{
	SendMessage(GetDlgItem(hwnd, ID_MAN), BM_SETCHECK, 1, 0);        /* ѡ�С��С���ť */
	EnableWindow(GetDlgItem(hwnd, ID_PERSONNEL_STAFF_NAME), FALSE);  /* ���������༭�� */
	EnableWindow(GetDlgItem(hwnd, ID_MAN), FALSE);                   /* �����������С� */
	EnableWindow(GetDlgItem(hwnd, ID_WOMAN), FALSE);                 /* ����������Ů�� */
	EnableWindow(GetDlgItem(hwnd, ID_PERSONNEL_DEPT_COMBO), FALSE);  /* ���ò��������б� */	
	return true;
}