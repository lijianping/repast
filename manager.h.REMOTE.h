#ifndef REPAST_MANAGER_H_
#define REPAST_MANAGER_H_

#include "resource.h"
#include "childwindowid.h"
#include "LoginForm.h"
#include "Static.h"
#include "Button.h"
#include "ComboBox.h"
#include "ListView.h"
#include "Tab.h"
#include "StaffForm.h"


struct LoginUser
{
	std::string user_name;
	std::string user_old_name;
	std::string user_permission_name;
	std::string user_passwd;
	UINT menu_id;
};

BOOL CALLBACK ManagerProcesses(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK SysManagementProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK FinanceProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK EditUserProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK ConsumeDetailProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

std::string GetPermissionName(HWND hwnd);

#endif