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
#include "CommodityCategoryForm.h"

BOOL CALLBACK BasicInfoProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK EditCategoryProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK EditCommodityProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool InitBasicInfoList(HWND parent_hwnd, UINT id);
bool InitCommodityTree(HWND parent_hwnd, UINT id);
bool ShowCommodity(HWND hwnd);
bool ShowCategoryList(HWND hwnd, UINT id);

/* ��Ʒ��Ϣ */
struct CommodityInfo {
	UINT menu_id;   // ��ťid
	std::string commodity_no;    // ��Ʒ���
	std::string commodity_name;  // ��Ʒ����
	std::string commodity_purchase; // ��Ʒ����
	std::string commodity_sum;    // ��Ʒ����
	std::string commodity_category; // ��Ʒ���
	std::string commodity_unit;   // ��Ʒ��λ
	std::string commodity_sale;   // ��Ʒ����
};

#endif