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

BOOL CALLBACK StartTableProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool SetListInfo(const HWND hwnd, const UINT id, std::string &error);

bool CreateRefeshButton(const HWND hwnd, const UINT id);

/*
 *  @说明: 初始化换台对话框中的可用台号
 *  @返回值:
 *           若成功返回true，否则返回false
 **/
bool InitAvailableTable(const HWND hwnd);

bool CreateStartButton(HINSTANCE hinstance, HWND hwnd, std::string error_info);

/*
 * @ 说明: 下单对话框中的菜单list view窗口处理过程函数
 **/
LRESULT CALLBACK OrderMenuListProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

/* struct define */

/* 台号信息 */
struct CustomerTable {
	std::string table_no;
	int table_state;
	std::string customer_no;
	std::string founding_time;
};
#endif  