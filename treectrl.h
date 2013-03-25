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
	HTREEITEM InsertRootItem(const char *text);
	HTREEITEM InsertChildItem(HTREEITEM select, const char *text);
	HTREEITEM GetSelectedItem();
	bool DeleteItem(HTREEITEM item);
	bool DeleteAllItems();
	bool GetItem(int len, char *text);
	bool GetItem(HTREEITEM select, int len, char *text);
	bool SelectDropTarget(HTREEITEM item);
	bool EnsureVisible(HTREEITEM item);
	HTREEITEM GetRoot();
	HTREEITEM GetChild(HTREEITEM parent);
	HTREEITEM GetNextSibling(HTREEITEM item);
	HTREEITEM FindItem(HTREEITEM item, const char *text);

private:
	HWND hwnd_;
	UINT id_;
};


#endif
