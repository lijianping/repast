#ifndef WIN32TEST_TREECTRL_H_
#define WIN32TEST_TREECTRL_H_
#include <Windows.h>
#include <assert.h>
#include <CommCtrl.h>
#include <string>
#pragma comment(lib, "comctl32.lib")

class TreeCtrl
{
public:
	TreeCtrl();
	TreeCtrl(HWND hwnd, UINT id);
	~TreeCtrl();
	bool Initialization(HWND hwnd, UINT id);
	HTREEITEM InsertRootItem(TCHAR *text);
	HTREEITEM InsertChildItem(HTREEITEM select, TCHAR *text);
	HTREEITEM GetSelectedItem();
	bool DeleteItem(HTREEITEM item);
	bool DeleteAllItems();
	bool GetItem(int len, char *text);
	bool GetItem(HTREEITEM select, int len, char *text);
	bool SelectDropTarget(HTREEITEM item);
	bool EnsureVisible(HTREEITEM item);


private:
	HWND hwnd_;
	UINT id_;
};


#endif
