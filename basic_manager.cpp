
#include "basic_manager.h"
#include "table_info.h"

BOOL CALLBACK BasicManagerProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static RECT tab_rect;
	static PageCtrl p_commodity, p_utensil, p_desk; // p_utensil:�;߹���
	static HINSTANCE hInstance;
	switch(msg)
	{
	case WM_INITDIALOG:
		{
		hInstance = (HINSTANCE)lParam;
		InitCommonControls();
		TabCtrl tab(hwnd, IDC_CHILD_TAB);
	    tab.InsertItem(0,"��Ʒ��Ϣ");
		tab.InsertItem(1,"̨����Ϣ");
		tab.InsertItem(2,"�;���Ϣ");

		HWND tab_hwnd = GetDlgItem(hwnd, IDC_CHILD_TAB);
		tab.GetClientRect(&tab_rect);
		tab_rect.top += 25;
		tab_rect.bottom -= 15;
		tab_rect.left += 1;
		tab_rect.right -= 2;
		p_commodity.CreatePage(hInstance, tab_hwnd, IDD_BASIC_COMMODITY,(DLGPROC)BasicInfoProc);
		p_desk.CreatePage(hInstance, tab_hwnd, IDD_BASIC_TABLE,(DLGPROC)TableInfoProc);
        p_utensil.CreatePage(hInstance, tab_hwnd, IDD_BASIC_UNTENSIL, NULL);
		p_commodity.MoveWindow(tab_rect);
		p_desk.MoveWindow(tab_rect);
		p_utensil.MoveWindow(tab_rect);
		p_commodity.ShowWindow(SW_NORMAL);
		p_desk.ShowWindow(SW_HIDE);
		p_utensil.ShowWindow(SW_HIDE);
		tab.Highlight(0);
			return TRUE;
		}
	case WM_NOTIFY:
		{
			switch (((LPNMHDR)lParam)->code)
			{
			case TCN_SELCHANGE:
				{
					p_commodity.ShowWindow(SW_HIDE);
					p_desk.ShowWindow(SW_HIDE);
					p_utensil.ShowWindow(SW_HIDE);
					TabCtrl tab(hwnd, IDC_CHILD_TAB);
					int select = tab.GetCurSel();
					tab.Highlight(select);
					switch(select)
					{
					case 0:
						{
							p_commodity.ShowWindow(SW_NORMAL);
							break;
						}
					case 1:
						{
							p_desk.ShowWindow(SW_NORMAL);
							break;
						}
					case 2:
						{
							p_utensil.ShowWindow(SW_NORMAL);
							break;
						}
					}
					break;
				}
			}
			return TRUE;
		}
	case WM_COMMAND:
		{
			return TRUE;
		}
	}
	return FALSE;
}