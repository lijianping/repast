#ifndef WIN32TEST_TABCTRL_H_
#define WIN32TEST_TABCTRL_H_
#include <Windows.h>
#include <assert.h>
#include <CommCtrl.h>
#pragma comment(lib, "comctl32.lib")

class TabCtrl
{
public:
	TabCtrl();
	TabCtrl(HWND hwnd, UINT id);
	~TabCtrl();
	bool CreateTab(HWND hwnd, UINT id, const RECT rect, const DWORD style);
	bool Initialization(HWND hwnd, UINT id);
	bool InsertItem(int index, TCHAR *text);
	int GetCurSel();
	int SetCurSel(int index);
	int GetCurFocus();
	void SetCurFocus(int index);
	BOOL GetClientRect(RECT *rect);
	bool HighlightItem(int index, bool highlight = true);
	void Highlight(int index);
	int GetItemCount();
	bool DeleteItem(int index);
	bool GetItem(int index, int len, char *text);

private:
	HWND hwnd_;   // ´°¿Ú¾ä±ú
	UINT id_;     // ´°¿ÚID
};

#endif 
