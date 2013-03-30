#ifndef REPAST_MANAGER_H_
#define REPAST_MANAGER_H_

#include "resource.h"
#include "LoginForm.h"
#include "Static.h"
#include "Button.h"
#include "ComboBox.h"
#include "ListView.h"
#include "Tab.h"
#include "StaffForm.h"
#include "service.h"
#include "personnel.h"
#include "tabctrl.h"
#include "pagectrl.h"
#include "Permission.h"


// 顾客详细信息数据传送
struct ConsumerInfo {
	std::string consumer_id;          // 顾客编号
	std::string consumption_amount;   // 消费金额
	std::string start_time;           // 开台/预定时间
	std::string end_time;             // 结束时间
	std::string clerk;                // 营业员
};

BOOL CALLBACK ServiceProcesses(HWND hwnd, UINT message,
                                  WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ManagerProcesses(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK UserManagementProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK FinanceProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK EditUserProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK ConsumeDetailProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK EditPermissionProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool ShowPermissionList(HWND hwnd);
bool AddPermission(HWND hwnd);
bool ModifyPermission(HWND hwnd);
bool DeletePermission(HWND hwnd);


int ConvertDate(const char *date, std::string &out_date);

bool ShowLoginUser(HWND hwnd);
bool InitStaffNo(HWND hwnd, UINT id);

bool GetLoginUserInfo(HWND hwnd, LoginUser *user, std::string &err_info);
#endif