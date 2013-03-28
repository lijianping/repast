#include "Wind.h"
#include "resource.h"
#include "service.h"
#include "childwindowid.h"
#include "basic_info.h"
#include "manager.h"
#include "basic_manager.h"
//#include <SkinPPWTL.h>


HINSTANCE g_hinstance;
static int g_user_permission = 0;  /* The user permission flag */
static PageCtrl h_server ,h_personnel, h_finance,  h_passwd, h_user, h_basic_info, h_help;
extern std::string g_login_name;

bool CreateSysManagement(TabCtrl *tab, HWND tab_hwnd, RECT tab_rect);
BOOL CALLBACK ChangePasswdProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// ��½�Ի�������̺��� 
BOOL CALLBACK LoginProcesses(HWND hwnd, UINT message,
                                WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine, int nShowCmd)
{
//	skinppLoadSkin(TEXT("skin/Royale.ssk"));  // ����Ƥ��
	g_hinstance = hInstance;
    std::string information;

    g_user_permission = DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_LOGIN), NULL,
                                     (DLGPROC)LoginProcesses, (long)&hInstance);

	if ( 0 < g_user_permission && g_user_permission < 5)
	{
		DialogBox(hInstance, MAKEINTRESOURCE(IDD_SYS_MANAGEMENT), NULL, (DLGPROC)ManagerProcesses);
	}
//	skinppExitSkin();  // �˳�
    return 0;
}


BOOL CALLBACK ManagerProcesses(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static RECT tab_rect;
   
	switch (msg)
	{
	case WM_INITDIALOG:
		{
			InitCommonControls();
			TabCtrl tab;
			HWND tab_hwnd = GetDlgItem(hwnd, IDC_TAB_MAIN);
			tab.Initialization(hwnd, IDC_TAB_MAIN);
			tab.GetClientRect(&tab_rect);
			tab_rect.top += 25;
			tab_rect.bottom -= 20;
			tab_rect.left += 1;
			tab_rect.right -= 2;
			CreateSysManagement(&tab, tab_hwnd, tab_rect);/*ϵͳ����*/
			return TRUE;
		}
	case WM_NOTIFY:
		{
			switch(((LPNMHDR)lParam)->code)
			{
			case TCN_SELCHANGE:
				{
					h_server.ShowWindow(SW_HIDE);
					h_basic_info.ShowWindow(SW_HIDE);
					h_personnel.ShowWindow(SW_HIDE);
					h_finance.ShowWindow(SW_HIDE);
					h_user.ShowWindow(SW_HIDE);
					h_passwd.ShowWindow(SW_HIDE);
					h_help.ShowWindow(SW_HIDE);
					
					TabCtrl tab;
					tab.Initialization(hwnd, IDC_TAB_MAIN);
					int selected = tab.GetCurSel();
					tab.Highlight(selected);
					char tab_title[256];
					tab.GetItem(selected, 256, tab_title);
					if (0 == strcmp(tab_title, "ǰ̨����")) {
						h_server.ShowWindow(SW_NORMAL);
						
					} else if (0 == strcmp(tab_title, "������Ϣ����")) {
						h_basic_info.ShowWindow(SW_NORMAL);
						
					} else if (0 == strcmp(tab_title, "���¹���")) {
						h_personnel.ShowWindow(SW_NORMAL);
					} else if (0 == strcmp(tab_title, "��������")) {
						h_finance.ShowWindow(SW_NORMAL);
					} else if (0 == strcmp(tab_title, "ϵͳ����")) {
						h_user.ShowWindow(SW_NORMAL);
					} else if (0 == strcmp(tab_title, "ʹ�ð���")) {
						MessageBox(hwnd, TEXT("��δ��ӣ������ڴ���"), TEXT("��ʾ"), MB_ICONINFORMATION);
					} else if (0 == strcmp(tab_title, "�������")) {
						h_passwd.ShowWindow(SW_NORMAL);
						HWND passwd_hwnd = h_passwd.hwnd();
						CEdit old_passwd(passwd_hwnd, IDC_OLD_PASSWD);   // ���л�tabʱ��ձ༭������
						CEdit new_passwd(passwd_hwnd, IDC_NEW_PASSWD);
						CEdit confirm(passwd_hwnd, IDC_CONFIRM);
						old_passwd.Empty();
						new_passwd.Empty();
						confirm.Empty();
					}
				}
			}
			return TRUE;
		}
	case WM_CLOSE:
		{
			if (IDYES == MessageBox(hwnd, TEXT("�Ƿ��˳�ϵͳ��"), TEXT("��ʾ"), MB_YESNOCANCEL | MB_ICONINFORMATION)) {
				EndDialog(hwnd, HIWORD(wParam));
			}
			return TRUE;
		}
	}
	return FALSE;
}

bool CreateSysManagement(TabCtrl *tab, HWND tab_hwnd, RECT tab_rect)
{
	h_server.CreatePage(g_hinstance, tab_hwnd, IDD_TAB_SERVER, (DLGPROC)ServiceProcesses);
	h_basic_info.CreatePage(g_hinstance, tab_hwnd, IDD_TAB_BASIC_INFO, (DLGPROC)BasicManagerProc);
	h_personnel.CreatePage(g_hinstance, tab_hwnd, IDD_TAB_PERSONNEL, (DLGPROC)PersonnelProc);
	h_finance.CreatePage(g_hinstance, tab_hwnd, IDD_TAB_FINANCE, (DLGPROC)FinanceProc);
	h_user.CreatePage(g_hinstance, tab_hwnd, IDD_TAB_USER, (DLGPROC)UserManagementProc);
	h_passwd.CreatePage(g_hinstance, tab_hwnd, IDD_TAB_PASSWD, (DLGPROC)ChangePasswdProc);
	h_server.MoveWindow(tab_rect);
	h_basic_info.MoveWindow(tab_rect);
	h_personnel.MoveWindow(tab_rect);
	h_finance.MoveWindow(tab_rect);
	h_user.MoveWindow(tab_rect);
	h_passwd.MoveWindow(tab_rect);
	
	h_server.ShowWindow(SW_HIDE);
	h_basic_info.ShowWindow(SW_HIDE);
	h_personnel.ShowWindow(SW_HIDE);
	h_finance.ShowWindow(SW_HIDE);
	h_user.ShowWindow(SW_HIDE);
	if (1== g_user_permission) {
		tab->InsertItem(0, "ǰ̨����");
		tab->InsertItem(1, "�������");
		tab->InsertItem(2, "ʹ�ð���");
		h_server.ShowWindow(SW_NORMAL);

	} else if (2 == g_user_permission) {
		tab->InsertItem(0, "������Ϣ����");
		tab->InsertItem(1, "�������");
		tab->InsertItem(2, "ʹ�ð���");
		h_basic_info.ShowWindow(SW_NORMAL);

	} else if (3 == g_user_permission) {
		tab->InsertItem(0, "���¹���");
		tab->InsertItem(1, "�������");
		tab->InsertItem(2, "ʹ�ð���");
		h_personnel.ShowWindow(SW_NORMAL);
	} else {
		tab->InsertItem(0, "ǰ̨����");
		tab->InsertItem(1, "������Ϣ����");
		tab->InsertItem(2, "���¹���");
		tab->InsertItem(3, "��������");
		tab->InsertItem(4, "ϵͳ����");
		tab->InsertItem(5, "ʹ�ð���");
		h_server.ShowWindow(SW_NORMAL);
	} 
	tab->SetCurSel(0);
	tab->Highlight(0);
	return true;
}

BOOL CALLBACK ChangePasswdProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		{
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDOK:
				{
					TCHAR new_passwd[64] = "\0", confirm[64] = "\0";
					int ret = GetDlgItemText(hwnd, IDC_NEW_PASSWD, new_passwd, 64);
					int ret1 = GetDlgItemText(hwnd, IDC_CONFIRM, confirm, 64);
					std::string password1(new_passwd), password2(confirm);
					if (password1 != password2) {
						MessageBox(hwnd, TEXT("�����������벻һ�£�"), TEXT("��ʾ"), MB_OK | MB_ICONINFORMATION);
						return FALSE;
					} 
					if (!ret || !ret1) {
						MessageBox(hwnd, TEXT("���벻��Ϊ�գ�"), TEXT("��ʾ"), MB_OK | MB_ICONINFORMATION);
						return FALSE;
					}
					TCHAR old_passwd[64] = "\0";
					GetDlgItemText(hwnd, IDC_OLD_PASSWD, old_passwd, 64);
					std::string password(old_passwd), error;
					CLoginForm modify_passwd;
					std::string pw = modify_passwd.Encrypt(password.c_str(), password.length() / 2, password.length());
					std::string pw1 = modify_passwd.Encrypt(password1.c_str(), password1.length() / 2, password1.length());
					// �ж��û������Ƿ���ȷ
					if (-1 == modify_passwd.GetUserPermission(g_login_name, pw, error)) {
						MessageBox(hwnd, TEXT("�û��������"), TEXT("��ʾ"), MB_OK | MB_ICONINFORMATION);
						return FALSE;
					}
					if (!modify_passwd.ModifyPasswd(g_login_name, pw1))
					{
						MessageBox(hwnd, TEXT("�޸��û�����ʧ�ܣ�"), TEXT("��ʾ"), MB_OK | MB_ICONINFORMATION);
						break;
					}
					MessageBox(hwnd, TEXT("�����޸ĳɹ���"), TEXT("��ʾ"), MB_OK);
				}
			case IDCANCEL:
				{
					CEdit old, new_passwd, confirm;
					old.Initialization(hwnd, IDC_OLD_PASSWD);
					new_passwd.Initialization(hwnd, IDC_NEW_PASSWD);
					confirm.Initialization(hwnd, IDC_CONFIRM);
					old.Empty();
					new_passwd.Empty();
					confirm.Empty();
				}
			}
			return TRUE;
		}
	}
	return FALSE;
}
