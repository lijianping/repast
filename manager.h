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


// �˿���ϸ��Ϣ���ݴ���
struct ConsumerInfo {
	std::string consumer_id;          // �˿ͱ��
	std::string consumption_amount;   // ���ѽ��
	std::string start_time;           // ��̨/Ԥ��ʱ��
	std::string end_time;             // ����ʱ��
	std::string clerk;                // ӪҵԱ
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

void ShowConsumerRecord(HWND hwnd, UINT id, const char *start_time, const char *end_time);
#endif