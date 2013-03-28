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

bool ShowConsumerTableInfo(const HWND hwnd, const UINT id, const char *floor_name);
bool InitComboBox(const HWND hwnd, int id);


BOOL CALLBACK OrderProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


BOOL CALLBACK CheckOutProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK ChangeProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK StartTableProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool SetListInfo(const HWND hwnd, const UINT id, const char *find, std::string &error);

bool CreateRefeshButton(const HWND hwnd, const UINT id);

bool InitTableList(const HWND hwnd, int id, const char *floor_name, short status);

bool CreateStartButton(HINSTANCE hinstance, HWND hwnd, std::string error_info);

/*
 * @ 说明: 下单对话框中的菜单list view窗口处理过程函数
 **/
LRESULT CALLBACK OrderMenuListProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK ChangeTableListProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
/* struct define */

/* 台号信息 */
struct CustomerTable {
	UINT menu_id;
	std::string table_no;
	std::string table_state;
	std::string customer_no;
	std::string founding_time;
};
#endif  