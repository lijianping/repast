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
            InitWindow(hinstance, hwnd, error_info);
            return 0;
        }
    case WM_SETFOCUS:
        {
            SetFocus(GetDlgItem(hwnd, ID_PERSONNEL_INFO));
            return 0;
        }
    case WM_LBUTTONDOWN:
        {
            MessageBox(hwnd, TEXT("Left button down!"), TEXT("personnel"), MB_ICONINFORMATION | MB_OK);
                break;
            return 0;
        }
    case WM_COMMAND:
        {
            switch(LOWORD(wParam))  
            {
             case ID_PERSONNEL_QUERY:
                MessageBox(hwnd, TEXT("Start query!"), TEXT("personnel"), MB_ICONINFORMATION | MB_OK);
                break;
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
    static int selected_row; /* current selected row */
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
            selected_row = list.GetCurSel();
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
                    CMyListView list;
                    STAFFINFO staff_info;
                    list.set_hwnd(hwnd);
                    std::string text;
                    list.GetItem(selected_row, 0, text); /* Get staff's id */
                    staff_info.id = text; 
                    list.GetItem(selected_row, 1, text); /* Get staff's name */
                    staff_info.name = text;
                    list.GetItem(selected_row, 2, text); /* Get staff's sex */
                    staff_info.sex = text;
                    list.GetItem(selected_row, 3, text); /* Get staff's age */
                    staff_info.age = text;
                    list.GetItem(1, 4, text); /* Get staff's salary */
                    staff_info.salary = text;
  
                    DialogBoxParam(hinstance, MAKEINTRESOURCE(IDD_STAFF_EDIT), hwnd,
                              (DLGPROC)EditStaff, (long)&staff_info);
                    break;
                }
                
            case IDR_DELETE:
                MessageBox(hwnd, TEXT("You choiced delete staff"), TEXT("PERSONNEL"), MB_OK | MB_ICONINFORMATION);
                break;
            case IDR_MODIFY:
                MessageBox(hwnd, TEXT("You choiced modify staff"), TEXT("PERSONNEL"), MB_OK | MB_ICONINFORMATION);
                break;
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
        !list_view.InsertColumn("Ա������", 5, width / 6))
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
							 6 * width, height + 5, hwnd, NULL, hinstance, NULL);
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
                            height + 5, hwnd, NULL, hinstance, NULL);
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
                             ES_CENTER | WS_TABSTOP | CBS_DROPDOWNLIST | CBS_HASSTRINGS |
                             CBS_AUTOHSCROLL | CBS_DISABLENOSCROLL, 295, 90, 10 * width,
                             height + 5, hwnd, (HMENU)ID_PERSONNEL_DEPT_COMBO,
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
    if (!CreateGroupBox(hinstance, hwnd, error_info))
    {
        return false;
    }
    if (!CreateNumEdit(hinstance, hwnd, error_info))
    {
        return false;
    }
    if (!CreateNameEdit(hinstance, hwnd, error_info))
    {
        return false;
    }
    if (!CreateSexBox(hinstance, hwnd, error_info))
    {
        return false;
    }
    if (!CreateDeptCombo(hinstance, hwnd, error_info))
    {
        return false;
    }
    if (!CreateStaffSum(hinstance, hwnd, error_info))
    {
        return false;
    }
    if (!CreateDeptSum(hinstance, hwnd, error_info))
    {
        return false;
    }
    if (!CreateCurrentSum(hinstance, hwnd, error_info))
    {
        return false;
    }
    if (!CreatePersonnelQuery(hinstance, hwnd, error_info))
    {
        return false;
    }
    return true;
}