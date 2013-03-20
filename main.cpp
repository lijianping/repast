#include "Wind.h"
#include "resource.h"
#include "service.h"
#include "childwindowid.h"
#include "basic_info.h"
#include "manager.h"



bool CreateSysManagement(TabCtrl *tab, HWND tab_hwnd, RECT tab_rect);
bool SelectSysManagement(TabCtrl *tab, int selected);

/*#include <WINDOWS.H>*/

/* global variable */

// int g_user_permission = 0;
/*HINSTANCE g_hinstance;*/

/* The login window processes */
BOOL CALLBACK LoginProcesses(HWND hwnd, UINT message,
                                WPARAM wParam, LPARAM lParam);
/* The Service Management window processes */
//BOOL CALLBACK ServiceProcesses(HWND hwnd, UINT message,
//                                  WPARAM wParam, LPARAM lParam);
/* 
 * ˵��: ���²��Ŵ��ڹ��̴�����
 * The Personnel Management window process
 **/
//BOOL CALLBACK PersonnelProc(HWND hwnd, UINT message,
//                                  WPARAM wParam, LPARAM lParam);
//BOOL CALLBACK ListProcesses(HWND hwnd, UINT message,WPARAM wParam, LPARAM lParam);

static HINSTANCE g_hinstance;
static int g_user_permission = 0;  /* The user permission flag */
static PageCtrl h_server ,h_personnel, h_finance,  h_passwd, h_user, h_basic_info;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine, int nShowCmd)
{

	g_hinstance = hInstance;
    std::string information;

    g_user_permission = DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_LOGIN), NULL,
                                     (DLGPROC)LoginProcesses, (long)&hInstance);

	if ( 0 < g_user_permission && g_user_permission < 5)
	{
		DialogBox(hInstance, MAKEINTRESOURCE(IDD_SYS_MANAGEMENT), NULL, (DLGPROC)ManagerProcesses);
	}
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
			switch(g_user_permission)
			{
				/*TODO:��������ģ��*/
			case 1:
				{
					break;;
				}
			case 2:
				{
					break;
				}
			case 3:
				{
					break;

				}
			case  4:
				{
					CreateSysManagement(&tab, tab_hwnd, tab_rect);/*ϵͳ����*/
					break;
				}
			default:
				{
					MessageBox(hwnd, TEXT("��¼����"), TEXT("����"), MB_OK);
					break;
				}
			}
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
					
					TabCtrl tab;
					tab.Initialization(hwnd, IDC_TAB_MAIN);
					int selected = tab.GetCurSel();
					switch(g_user_permission)
					{
							/*TODO:��������ģ��*/
					case 1:
						{
							break;
						}
					case 2:
						{
							break;
						}
					case 3:
						{
							break;
						}
					case 4:
						{
							SelectSysManagement(&tab, selected);/*ϵͳ����*/
							break;
						}
					default:
						break;
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
	return FALSE;
}




bool CreateSysManagement(TabCtrl *tab, HWND tab_hwnd, RECT tab_rect)
{
	tab->InsertItem(0, "ǰ̨����");
	tab->InsertItem(1, "������Ϣ����");
	tab->InsertItem(2, "���¹���");
//	tab->InsertItem(3, "��������");
	tab->InsertItem(4, "�û�����");
	tab->InsertItem(5, "���ݿⱸ��");
	tab->InsertItem(6, "���ݿ⻹ԭ");
	tab->InsertItem(7, "ʹ�ð���");
			 
	h_server.CreatePage(g_hinstance, tab_hwnd, IDD_TAB_SERVER, (DLGPROC)ServiceProcesses);
	h_basic_info.CreatePage(g_hinstance, tab_hwnd, IDD_TAB_BASIC_INFO, (DLGPROC)BasicInfoProc);
	h_personnel.CreatePage(g_hinstance, tab_hwnd, IDD_TAB_PERSONNEL, (DLGPROC)PersonnelProc);
	h_finance.CreatePage(g_hinstance, tab_hwnd, IDD_TAB_FINANCE, (DLGPROC)FinanceProc);
	h_user.CreatePage(g_hinstance, tab_hwnd, IDD_TAB_USER, (DLGPROC)UserManagementProc);
	
	h_server.MoveWindow(tab_rect);
	h_basic_info.MoveWindow(tab_rect);
	h_personnel.MoveWindow(tab_rect);
	h_finance.MoveWindow(tab_rect);
	h_user.MoveWindow(tab_rect);
	
	h_server.ShowWindow(SW_NORMAL);
	h_basic_info.ShowWindow(SW_HIDE);
	h_personnel.ShowWindow(SW_HIDE);
	h_finance.ShowWindow(SW_HIDE);
	h_user.ShowWindow(SW_HIDE);
	
	tab->SetCurSel(0);
	tab->Highlight(0);
	return true;
}



bool SelectSysManagement(TabCtrl *tab, int selected)
{
	tab->HighlightItem(1, false);
	tab->HighlightItem(2, false);
	tab->HighlightItem(3, false);
	tab->HighlightItem(4, false);
	tab->HighlightItem(5, false);
	tab->HighlightItem(6, false);
	tab->HighlightItem(7, false);
	switch(selected)
	{
	case 0:/*ǰ̨����*/
		{
			tab->Highlight(selected);
			h_server.ShowWindow(SW_NORMAL);
		}
		break;
	case 1:/*������Ϣ����*/
		{
			tab->Highlight(selected);
			h_basic_info.ShowWindow(SW_NORMAL);
		}
		break;
	case 2:/*���¹���*/
		{
			tab->Highlight(selected);
			h_personnel.ShowWindow(SW_NORMAL);
		}
		break;
	case 3:	/*��������*/
		{
			tab->Highlight(selected);
			h_finance.ShowWindow(SW_NORMAL);
		}
		break;
	case 4:/*�û�����*/
		{
			tab->Highlight(selected);
			h_user.ShowWindow(SW_NORMAL);
		}
		break;
	case 5:/*���ݿⱸ��*/
		{
			tab->Highlight(selected);
			MessageBox(NULL, "��δ����", "��ʾ", 0);
		}
		break;
	case 6:/*���ݿ⻹ԭ*/
		{
			tab->Highlight(selected);
			MessageBox(NULL, "��δ����", "��ʾ", 0);
		}
		break;
	case 7:/*ʹ�ð���*/
		{
			tab->Highlight(selected);
			MessageBox(NULL, "��δ����", "��ʾ", 0);
		}
		break;
	default:
		MessageBox(NULL, "ѡ������", "��ʾ", 0);
		break;
	}
	return true;
}