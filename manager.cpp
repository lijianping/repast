#include "manager.h"


BOOL CALLBACK ManagerProcesses(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static RECT tab_rect;
	static HWND page1, page2;
	static HINSTANCE hinstance = (HINSTANCE)lParam;
	switch (msg)
	{
	case WM_INITDIALOG:
		{
			CTab tab;
			tab.Initialization(hwnd, IDC_TAB1);
			tab.InsertItem(0, "�û�����");
			tab.InsertItem(1, "�������");
			tab.InsertItem(2, "���ݿⱸ��");
			tab.InsertItem(3, "���ݿ⻹ԭ");
			tab.SetCurFocus(0);
			tab.GetClientRect(&tab_rect);
			tab_rect.top += 25;
			tab_rect.bottom -= 20;
			tab_rect.left += 1;
			tab_rect.right -= 2;
			HWND tab_hwnd = GetDlgItem(hwnd, IDC_TAB1);
			page1 = CreateDialog(hinstance, MAKEINTRESOURCE(IDD_TAB_CHILD1), tab_hwnd, (DLGPROC)Page1Proc);
			page2 = CreateDialog(hinstance, MAKEINTRESOURCE(IDD_TAB_CHILD2), tab_hwnd, (DLGPROC)Page2Proc);
			
			MoveWindow(page1, tab_rect.left, tab_rect.top, \
				       tab_rect.right - tab_rect.left, tab_rect.bottom - tab_rect.top, TRUE);
			MoveWindow(page2, tab_rect.left, tab_rect.top, \
				       tab_rect.right - tab_rect.left, tab_rect.bottom - tab_rect.top, TRUE);
			ShowWindow(page1, SW_NORMAL);
			return TRUE;
		}
	case WM_NOTIFY:
		{
			switch(((LPNMHDR)lParam)->code)
			{
			case TCN_SELCHANGE:
				ShowWindow(page1, SW_HIDE);
				ShowWindow(page2, SW_HIDE);
				CTab tab;
				tab.Initialization(hwnd, IDC_TAB1);
				int selected = tab.GetCurSel();
				if (0 == selected) {
					ShowWindow(page1, SW_NORMAL);
				}
				else{
					ShowWindow(page2, SW_NORMAL);
				}
				break;
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

BOOL CALLBACK Page1Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG:
		{
			CListView user;
			user.Initialization(hwnd, IDC_USER_LIST);
			user.InsertColumn(0, 100, "�û���");
			user.InsertColumn(1, 100, " Ȩ��");
			user.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			CLoginForm login;
			login.GetRecordSet();
			login.MoveFirst();
			int i = 0;
			while (!login.IsEOF()) {
				user.InsertItem(i, login.name());
				user.SetItem(i, 1, login.permission());
				login.MoveNext();
			}
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam)) {
			case IDC_ADD_USER:
				MessageBox(hwnd, TEXT("Add user!"), TEXT("MANAGER"), MB_ICONINFORMATION);
				break;
			}
		}
	}
	return FALSE;
}


BOOL CALLBACK Page2Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG:
		{
			CListView user;
			user.Initialization(hwnd, IDC_);
			user.InsertColumn(0, 150, "�˿ͱ��");
			user.InsertColumn(1, 150, "��̨ʱ��");
			user.InsertColumn(2, 100, " ���ѽ��");
			user.SetSelectAndGrid(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam)) {
			case IDC_BUTTON1:
				MessageBox(hwnd, TEXT("��������ϸ!"), TEXT("MANAGER"), MB_ICONINFORMATION);
				break;
			}
		}
	}
	return FALSE;
}