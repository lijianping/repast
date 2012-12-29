#include "resource.h"

#include "StaffForm.h"
#include "childwindowid.h"
#include "Static.h"
#include "Button.h"
#include "ComboBox.h"
#include "ListView.h"

LRESULT CALLBACK ListProcesses(HWND hwnd, UINT message,
                               WPARAM wParam, LPARAM lParam);

bool CreateTableListView(const HWND hwnd);

bool InitListView(const HWND hwnd, UINT id);

bool CreateGroupBox(const HWND hwnd);

bool CreateComboBox(const HWND hwnd);

bool InitComboBox(const HWND hwnd, int id);

bool CreateButton(const HWND hwnd);

BOOL CALLBACK OrderProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK RetreatProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK CheckOutProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK ChangeProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void SetTableInfo();

/* Create list view */
/*bool CreateList(HINSTANCE hinstance, HWND hwnd, CMyListView &list_view);*/

bool CreateStartButton(HINSTANCE hinstance, HWND hwnd, std::string error_info);