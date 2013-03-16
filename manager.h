#ifndef REPAST_MANAGER_H_
#define REPAST_MANAGER_H_

#include "resource.h"
#include "StaffForm.h"
#include "childwindowid.h"
#include "Static.h"
#include "Button.h"
#include "ComboBox.h"
#include "ListView.h"
#include "Tab.h"
#include "LoginForm.h"

struct LoginUser
{
	std::string user_name;
	std::string user_old_name;
	std::string user_permission_name;
	UINT menu_id;
};

std::string permission[]={"", "前台管理", "仓库管理", "人事管理", "系统管理"};

BOOL CALLBACK ManagerProcesses(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK SysManagementProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK FinanceProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK EditUserProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK ConsumeDetailProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif