#ifndef REPAST_TABLE_INFO_H_
#define REPAST_TABLE_INFO_H_
#include <Windows.h>
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

/*
 * @ brief: 台号管理处理信息
 **/
BOOL CALLBACK TableInfoProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

/*
 *说明：楼层信息管理
 */
BOOL CALLBACK FloorInfoProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void ShowFloorList(HWND hwnd);
bool AddFloor(HWND hwnd);
bool UpdateFloor(HWND hwnd);
bool DeleteFloor(HWND hwnd);
#endif