#ifndef REPAST_BASIC_INFO_H_
#define REPAST_BASIC_INFO_H_

#include "ListView.h"
#include "Button.h"
#include "Static.h"
#include "ComboBox.h"
#include "Edit.h"
#include "treectrl.h"
#include "resource.h"
#include "Commodity.h"
#include "tabctrl.h"
#include "pagectrl.h"
#include "CommodityCategoryForm.h"//TODO:½«±»É¾³ý
#include "ComMainCateForm.h"
#include "hildCateForm.h"

BOOL CALLBACK BasicInfoProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK EditCategoryProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK EditCommodityProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool InitBasicInfoList(HWND parent_hwnd, UINT id);
bool InitCommodityTree(HWND parent_hwnd, UINT id);
bool ShowCommodityTree(HWND paren_hwnd, UINT id);
bool ShowCommodity(HWND hwnd);
bool RespondTreeDBClick(HWND hwnd);
bool AddComCategory(HWND hwnd);
bool UpdateComCategory(HWND hwnd);
bool DeleteComCategory(HWND hwnd);
bool GetCommodityInfoFromList(HWND hwnd,CommodityInfo &commodity_info);
bool InitMainCateComBox(HWND hwnd);
bool IsEnableWndChildCate(HWND hwnd);
bool ShowCommodityInfo(HWND hwnd,CommodityInfo &commodity_info);
bool GetComInfoFromDlg(HWND hwnd, CommodityInfo &com_info);


#endif
