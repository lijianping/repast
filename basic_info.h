#ifndef REPAST_BASIC_INFO_H_
#define REPAST_BASIC_INFO_H_

#include "ListView.h"
#include "Button.h"
#include "Static.h"
#include "ComboBox.h"
#include "Edit.h"
#include "treectrl.h"
#include "childwindowid.h"
#include "resource.h"
#include "Commodity.h"
#include "tabctrl.h"
#include "pagectrl.h"
#include "CommodityCategoryForm.h"//TODO:将被删除
#include "ComMainCateForm.h"
#include "hildCateForm.h"

BOOL CALLBACK BasicInfoProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK EditCategoryProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK EditCommodityProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool InitBasicInfoList(HWND parent_hwnd, UINT id);
bool InitCommodityTree(HWND parent_hwnd, UINT id);
bool ShowCommodityTree(HWND paren_hwnd, UINT id);
bool ShowCommodity(HWND hwnd);
bool ShowCategoryList(HWND hwnd, UINT id);
bool RespondTreeDBClick(HWND hwnd);
bool AddComCategory(HWND hwnd);
bool UpdateComCategory(HWND hwnd);
bool DeleteComCategory(HWND hwnd);


/* 商品信息 */
struct CommodityInfo {
	UINT menu_id;   // 按钮id
	std::string commodity_no;    // 商品编号
	std::string commodity_name;  // 商品名称
	std::string commodity_purchase; // 商品进价
	std::string commodity_sum;    // 商品总量
	std::string commodity_category; // 商品类别
	std::string commodity_unit;   // 商品单位
	std::string commodity_sale;   // 商品卖价
};

#endif
