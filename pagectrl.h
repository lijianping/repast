#ifndef WIN32TEST_PAGECTRL_H_
#define WIN32TEST_PAGECTRL_H_
#include <Windows.h>
#include <assert.h>
#include <CommCtrl.h>
#pragma comment(lib, "comctl32.lib")

class PageCtrl
{
public:
	PageCtrl();
	~PageCtrl();
	bool CreatePage(HINSTANCE hInstance, HWND hwnd, UINT id, DLGPROC func);
	BOOL MoveWindow(const RECT rect);
	BOOL ShowWindow(int show_state);
	COLORREF SetBKColor(COLORREF color);
	HWND hwnd() const;

private:
	HWND hwnd_;
	UINT id_;
};

#endif
