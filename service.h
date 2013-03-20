#ifndef REPAST_SERVICE_H_
#define REPAST_SERVICE_H_

#include "resource.h"
#include "StaffForm.h"
#include "childwindowid.h"
#include "Static.h"
#include "Button.h"
#include "ComboBox.h"
#include "ListView.h"

LRESULT CALLBACK ListProcesses(HWND hwnd, UINT message,
                               WPARAM wParam, LPARAM lParam);


bool InitListView(const HWND hwnd, UINT id);


bool InitComboBox(const HWND hwnd, int id);


BOOL CALLBACK OrderProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


BOOL CALLBACK CheckOutProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK ChangeProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK StartTableProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool SetListInfo(const HWND hwnd, const UINT id, const char *find, std::string &error);

bool CreateRefeshButton(const HWND hwnd, const UINT id);

std::string GetFloor(std::string floor);
/*
 *  @ brief: 初始化换台对话框中的可用台号
 *  @ return: 若成功返回true，否则返回false
 **/
bool InitAvailableTable(const HWND hwnd, int id);

bool CreateStartButton(HINSTANCE hinstance, HWND hwnd, std::string error_info);

/*
 * @ 说明: 下单对话框中的菜单list view窗口处理过程函数
 **/
LRESULT CALLBACK OrderMenuListProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

/*
 * @ brief: 获取台号信息
 * @ param: hwnd [in] 父窗口句柄
 * @ param: id [in] 待显示台号信息的Listview的id
 * @ param: use [in] 台号是否使用 0 - 未使用 1 - 已开台 2 - 已预订
 * @ param: floor [in] 楼层编号
 **/
void GetTableInfo(const HWND hwnd, const int id, const char *floor = "01", int use = 0);
/* struct define */

/* 台号信息 */
struct CustomerTable {
	std::string table_no;
	std::string table_state;
	std::string customer_no;
	std::string founding_time;
};
#endif  