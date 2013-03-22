#include "ListView.h"
#include "Button.h"
#include "Static.h"
#include "ComboBox.h"
#include "Edit.h"
#include "treectrl.h"
#include "childwindowid.h"
#include "resource.h"
#include "Commodity.h"
#include "CommodityCategoryForm.h"

BOOL CALLBACK BasicInfoProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK EditCategoryProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK EditCommodityProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool InitBasicInfoList(HWND parent_hwnd, UINT id);
bool InitCommodityTree(HWND parent_hwnd, UINT id);
bool ShowCommodity(HWND hwnd);
bool ShowCategoryList(HWND hwnd, UINT id);
