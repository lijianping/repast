#include "resource.h"

#include "StaffForm.h"
#include "childwindowid.h"

LRESULT CALLBACK ListProcesses(HWND hwnd, UINT message,
                               WPARAM wParam, LPARAM lParam);
/* Create list view */
/*bool CreateList(HINSTANCE hinstance, HWND hwnd, CMyListView &list_view);*/

bool CreateStartButton(HINSTANCE hinstance, HWND hwnd, std::string error_info);