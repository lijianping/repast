#include "pagectrl.h"


PageCtrl::PageCtrl() {
}


PageCtrl::~PageCtrl() {
}

bool PageCtrl::CreatePage(HINSTANCE hInstance, HWND hwnd, UINT id, DLGPROC func) {
	hwnd_ = ::CreateDialog(/*(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE)*/hInstance, MAKEINTRESOURCE(id), hwnd, func);
	
	if (hwnd_ != NULL) {
		id_ = id;
		return true;
	}
	return false;
}

BOOL PageCtrl::MoveWindow(const RECT rect) {
	return ::MoveWindow(hwnd_, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE);
}

BOOL PageCtrl::ShowWindow(int show_state) {
	return ::ShowWindow(hwnd_, show_state);
}

HWND PageCtrl::hwnd() const {
	return hwnd_;
}

COLORREF PageCtrl::SetBKColor(COLORREF color) {
	HDC hdc = ::GetDC(hwnd_);
	COLORREF cr = ::SetBkColor(hdc, color);
	::ReleaseDC(hwnd_, hdc);
	return cr;
}